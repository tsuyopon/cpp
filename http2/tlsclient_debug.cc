//
// HTTP/2クライアントの最小実装サンプル
// 
// 接続先はhttps://www.yahoo.co.jp/
//
// コンパイル: $ g++ -lssl -lcrypto -lstdc++ tlsclient.cc  
//
//*****************************************************
// OpenSSL1.0.2以上を使用.
//*****************************************************

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string>

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <netdb.h>
#include <fcntl.h>
#include <signal.h>
#include <unistd.h>
#define SOCKET int
#define SD_BOTH SHUT_WR

#include <openssl/ssl.h>
#include <openssl/err.h>

#define READ_BUF_SIZE 4096
#define BUF_SIZE 4097
#define PORT 443
#define BINARY_FRAME_LENGTH 9


// ALPN識別子. h2
static const unsigned char protos[] = { 0x02, 0x68, 0x32 };
static const char cmp_protos[] = { 0x68, 0x32 };
static int protos_len = 3;

//ドラフト14を使う場合
// ALPN識別子. h2-14
//static const uint8_t protos[] = { 0x05, 0x68, 0x32, 0x2d, 0x31, 0x36 };
//static const uint8_t cmp_protos[] = { 0x68, 0x32, 0x2d, 0x31, 0x36 };
//static int protos_len = 6;

#define CLIENT_CONNECTION_PREFACE "PRI * HTTP/2.0\r\n\r\nSM\r\n\r\n"

// 3バイトのネットワークオーダーを4バイト整数へ変換する関数.
char* to_framedata3byte(char *p, int &n);
int get_error();
void close_socket(SOCKET socket, SSL_CTX *_ctx, SSL *_ssl);
static ssize_t to_hex(unsigned char *dst, size_t dst_len, unsigned char *src, size_t src_len);

int main(int argc, char **argv)
{

    //------------------------------------------------------------
    // 接続先ホスト名.
    //------------------------------------------------------------
    std::string host = "www.yahoo.co.jp";
    //std::string host = "www.google.com";

    //------------------------------------------------------------
    // SSLの準備.
    //------------------------------------------------------------
    SSL *_ssl;
    SSL_CTX *_ctx;

    // SSLライブラリの初期化.
    SSL_library_init();

    // エラーを文字列化するための準備.
    SSL_load_error_strings();

    // グローバルコンテキスト初期化.
    const SSL_METHOD *meth = TLSv1_2_method();
    //const SSL_METHOD *meth = TLSv1_method();
    //const SSL_METHOD *meth = SSLv23_method();
    _ctx = SSL_CTX_new(meth);

    int error = 0;
    struct hostent *hp;
    struct sockaddr_in addr;
    SOCKET _socket;

    if (!(hp = gethostbyname(host.c_str()))){
        printf("Error Occured: gethostbyname");
        return -1;
    }
    memset(&addr, 0, sizeof(addr));
    addr.sin_addr = *(struct in_addr*)hp->h_addr_list[0];
    addr.sin_family = AF_INET;
    addr.sin_port = htons(PORT);

    if ((_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP))<0){
        printf("Error Occured: socket");
        return -1;
    }
    if (connect(_socket, (struct sockaddr *)&addr, sizeof(addr))<0){
        printf("Error Occured: connect");
        return -1;
    }

    // sslセッションオブジェクトを作成する.
    _ssl = SSL_new(_ctx);

    // ソケットと関連づける.
    SSL_set_fd(_ssl, _socket);

    //------------------------------------------------------------
    // HTTP2の準備.
    //
    // プロトコルのネゴシエーションにALPNという方法を使います。
    // 具体的にはTLSのClientHelloのALPN拡張領域ににこれから使うプロトコル名を記述します.
    // SPDYではNPNという方法が使われましたが、現在のHTTP2仕様ではNPNは廃止されています.
    //
    // protosには文字列ではなくバイナリで、「0x02, 'h','2'」と指定する。
    // 最初の0x02は「h2」の長さを表している.
    //------------------------------------------------------------
    SSL_set_alpn_protos(_ssl, protos, protos_len);

    // SSL接続.
    if (SSL_connect(_ssl) <= 0){
        printf("Error Occured: SSL_connect");
        error = get_error();
        ::shutdown(_socket, SD_BOTH);
        close_socket(_socket, _ctx, _ssl);
        return 0;
    }

    // 採用されたALPNを確認する.
    const unsigned char  *ret_alpn;
    unsigned int  alpn_len;
    SSL_get0_alpn_selected(_ssl, &ret_alpn, &alpn_len);

    if ((int)alpn_len < protos_len - 1){
        printf("Error Occured: alpn_len");
        error = get_error();
        close_socket(_socket, _ctx, _ssl);
        return 0;
    }

    if (memcmp(ret_alpn, cmp_protos, alpn_len) != 0){
        printf("Error Occured: alpn selection");
        error = get_error();
        close_socket(_socket, _ctx, _ssl);
        return 0;
    }

    //------------------------------------------------------------
    // wiresharkにTLSを解読させるための出力を行う。
    //------------------------------------------------------------
    unsigned char buf_raw_r[SSL3_RANDOM_SIZE];
    unsigned char buf_client_random[SSL3_RANDOM_SIZE*2+10];
    unsigned char buf_raw_m[SSL_MAX_MASTER_KEY_LENGTH];
    unsigned char buf_master_key[SSL_MAX_MASTER_KEY_LENGTH*2+10];
    ssize_t res;

    FILE *outputfile;         // 出力ストリーム
    outputfile = fopen("/Users/tsuyoshi/Desktop/tls_key.log", "a");

    size_t ssl_client_r = SSL_get_client_random(_ssl, buf_raw_r, SSL3_RANDOM_SIZE);
    res = to_hex(buf_client_random, sizeof(buf_client_random), buf_raw_r, ssl_client_r);
    res = fprintf(outputfile, "CLIENT_RANDOM %s ", buf_client_random);

    size_t ssl_client_m = SSL_SESSION_get_master_key(SSL_get_session(_ssl), buf_raw_m, SSL_MAX_MASTER_KEY_LENGTH);
    res = to_hex(buf_master_key, sizeof(buf_master_key), buf_raw_m, ssl_client_m);
    res = fprintf(outputfile, "%s\n", buf_master_key);

    fclose(outputfile);          // ファイルをクローズ(閉じる)

    //------------------------------------------------------------
    // これからHTTP2通信を開始する合図.
    //
    // 24オクテットのバイナリを送信します
    // PRI * HTTP/2.0\r\n\r\nSM\r\n\r\n
    //------------------------------------------------------------
    int r = 0;
    char buf[BUF_SIZE] = { 0 };
    char* p = buf;
    bool b = false;
    int payload_length = 0;
    int frame_type = 0;
    int ret = 0;
    int remaining_size = 0;

    printf("=== Start write HTTP/2 Preface string\n");
    while (1){

        r = SSL_write(_ssl, CLIENT_CONNECTION_PREFACE, (int)strlen(CLIENT_CONNECTION_PREFACE));
        ret = SSL_get_error(_ssl, r);
        switch (ret){
            case SSL_ERROR_NONE:
                b = true;
                break;
            case SSL_ERROR_WANT_WRITE:
                continue;
            default:
                if (r == -1){
                    printf("Error Occured: Preface SSL_write");
                    error = get_error();
                    close_socket(_socket, _ctx, _ssl);
                    return 0;
                }
        }
        if (b) break;
    }


    //------------------------------------------------------------
    // 全てのデータはバイナリフレームで送受信される
    // バイナリフレームは共通の9バイトヘッダと、データ本体であるpayloadを持つ
    //
    // ●ヘッダ部分のフォーマット
    //
    //   1-3バイト目  payloadの長さ。長さにヘッダの9バイトは含まれない。.
    //   4バイト目　フレームのタイプ.
    //   5バイト目　フラグ.
    //   6-9バイト目　ストリームID.(最初の1bitは予約で必ず0)
    //
    //  |Length(24bit)|Type(8bit)|Flags(8bit)|Reserve(1bit)|Stream Identifier(31bit)|
    //  |Frame Payload(Lengthバイト分)|
    //
    //
    // [フレームのタイプ]
    //
    // DATA(0x00)  リクエストボディや、レスポンスボディを転送する
    // HEADERS(0x01)  圧縮済みのHTTPヘッダーを転送する
    // PRIORITY(0x02)  ストリームの優先度を変更する
    // RST_STREAM(0x03)  ストリームの終了を通知する
    // SETTINGS(0x04)  接続に関する設定を変更する
    // PUSH_PROMISE(0x05)  サーバーからのリソースのプッシュを通知する
    // PING(0x06)  接続状況を確認する
    // GOAWAY(0x07)  接続の終了を通知する
    // WINDOW_UPDATE(0x08)   フロー制御ウィンドウを更新する
    // CONTINUATION(0x09)  HEADERSフレームやPUSH_PROMISEフレームの続きのデータを転送する
    //
    // それぞれのリクエストやレスポンスにはストリームIDが付与される.
    // クライアントから発行されるストリームIDは奇数.
    // サーバーから発行されるストリームIDは偶数.
    // ストリームには優先順位が付けられています.
    // 今回はストリームID「1」だけを使用します.
    //------------------------------------------------------------

    //------------------------------------------------------------
    // HTTP2通信のフロー
    //
    // まず最初にSettingフレームを必ず交換します.
    // Settingフレームを交換したら、設定を適用したことを伝えるために必ずACKを送ります.
    //
    // Client -> Server  SettingFrame
    // Client <- Server  SettingFrame
    // Client -> Server  ACK
    // Client <- Server  ACK
    //
    // Client -> Server  HEADERS_FRAME (GETなど)
    // Client <- Server  HEADERS_FRAME (ステータスコードなど)
    // Client <- Server  DATA_FRAME (Body)
    // 
    // Client -> Server  GOAWAY_FRAME (送信終了)
    //------------------------------------------------------------

    //------------------------------------------------------------
    // Settingフレームの送信.
    // フレームタイプは「0x04」
    // 全てデフォルト値を採用するためpayloadは空です。
    // SettingフレームのストリームIDは0です.
    //
    // 今回は空ですがSettingフレームのpayloadは次のフォーマットです.
    //
    // |Identifer(16bit)|Value(32bit)|
    // 上記を設定値の数だけ連結させ、最終的な長さをヘッダフレームのLengthに記述します.
    //
    // Identiferは次のものが定義されています。
    // SETTINGS_HEADER_TABLE_SIZE (0x1)  初期値は 4,096 オクテット
    // SETTINGS_ENABLE_PUSH (0x2)  初期値は1
    // SETTINGS_MAX_CONCURRENT_STREAMS (0x3)  初期状態では無制限
    // SETTINGS_INITIAL_WINDOW_SIZE (0x4)   初期値は 2^16-1 (65,535)
    // SETTINGS_MAX_FRAME_SIZE (0x5)    初期値は 2^24-1 (16777215)
    // SETTINGS_MAX_HEADER_LIST_SIZE (0x6)   初期値は無制限
    //------------------------------------------------------------
    const unsigned char settingframe[BINARY_FRAME_LENGTH] = { 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00};

    printf("=== Start write SETTINGS frame\n");
    while (1){

        r = SSL_write(_ssl, settingframe, BINARY_FRAME_LENGTH);

        ret = SSL_get_error(_ssl, r);
        switch (ret){
            case SSL_ERROR_NONE:
                b = true;
                break;
            case SSL_ERROR_WANT_WRITE:
                continue;
            default:
                if (r == -1){
                    printf("Error Occured: SETTINGS frame SSL_write");
                    error = get_error();
                    close_socket(_socket, _ctx, _ssl);
                    return 0;
                }
        }
        if (b) break;
    }

    //------------------------------------------------------------
    // Settingフレームの受信.
    //------------------------------------------------------------
    memset(buf, 0x00, BUF_SIZE);
    p = buf;

    printf("=== Start recv SETTINGS frame\n");
    sleep(1);

    int init = 1;
    while (1){

        r = SSL_read(_ssl, p, READ_BUF_SIZE);
        printf("%d\n", r);
        printf("READ_BUFF_SIZE %02x %02x %02x %02x %02x %02x %02x %02x %02x\n", p[0], p[1], p[2], p[3], p[4], p[5], p[6], p[7], p[8]);
        ret = SSL_get_error(_ssl, r);
        switch (ret){
            case SSL_ERROR_NONE:
                b = true;
                break;
            case SSL_ERROR_WANT_READ:
                continue;
            default:
                if (r == -1){
                    printf("Error Occured: SETTINGS Frame SSL_read");
                    error = get_error();
                    close_socket(_socket, _ctx, _ssl);
                    return 0;
                }
        }

        if(init == 1){
            p = to_framedata3byte(p, payload_length);
            printf("Payload_length: %d\n", payload_length);
            remaining_size = payload_length;
            init = 0;
        }
        remaining_size -= r;
        
        if (remaining_size && b) break;
    }

    //------------------------------------------------------------
    // ACKの送信.
    // ACKはSettingフレームを受け取った側が送る必要がある.
    // ACKはSettingフレームのフラグに0x01を立ててpayloadを空にしたもの.
    //
    // フレームタイプは「0x04」
    // 5バイト目にフラグ0x01を立てます。
    //------------------------------------------------------------
    const unsigned char settingframeAck[BINARY_FRAME_LENGTH] = { 0x00, 0x00, 0x00, 0x04, 0x01, 0x00, 0x00, 0x00, 0x00 };
    printf("=== Start write SETTINGS frame ACK flags\n");
    while (1){

        r = SSL_write(_ssl, settingframeAck, BINARY_FRAME_LENGTH);

        ret = SSL_get_error(_ssl, r);
        switch (ret){
            case SSL_ERROR_NONE:
                b = true;
                break;
            case SSL_ERROR_WANT_WRITE:
                continue;
            default:
                if (r == -1){
                    printf("Error Occured: SETTINGS Frame Ack Flag SSL_write");
                    error = get_error();
                    close_socket(_socket, _ctx, _ssl);
                    return 0;
                }
        }
        if (b) break;
    }

    // サーバーからのACKの受信は下でやります..

    //------------------------------------------------------------
    // HEADERSフレームの送信.
    //
    // フレームタイプは「0x01」
    // このフレームに必要なヘッダがすべて含まれていてこれでストリームを終わらせることを示すために、
    // END_STREAM(0x1)とEND_HEADERS(0x4)を有効にします。
    // 具体的には5バイト目のフラグに「0x05」を立てます。
    // ストリームIDは「0x01」を使います.
    //
    // ここまででヘッダフレームは「ペイロードの長さ(3バイト), 0x01, 0x05, 0x00, 0x00, 0x00, 0x01」になります.
    //
    //
    // ●HTTP1.1でのセマンティクス
    // 　　"GET / HTTP1/1"
    // 　　"Host: nghttp2.org
    //
    // ●HTTP2でのセマンティクス
    //      :method GET
    //      :path /
    //      :scheme https
    //      :authority nghttp2.org
    //
    // 本来HTTP2はHPACKという方法で圧縮します.
    // 今回は上記のHTTP2のセマンティクスを圧縮なしで記述します.
    //
    // 一つのヘッダフィールドの記述例
    //
    // |0|0|0|0|      0|   // 最初の4ビットは圧縮に関する情報、次の4ビットはヘッダテーブルのインデクス.(今回は圧縮しないのですべて0)
    // |0|            7|   // 最初の1bitは圧縮に関する情報(今回は0)、次の7bitはフィールドの長さ
    // |:method|           // フィールドをそのままASCIIのオクテットで書く。
    // |0|            3|   // 最初の1bitは圧縮に関する情報(今回は0)、次の7bitはフィールドの長さ
    // |GET|               // 値をそのままASCIIのオクテットで書く。
    //
    // 上記が一つのヘッダフィールドの記述例で、ヘッダーフィールドの数だけこれを繰り返す.
    //
    // See: https://tools.ietf.org/html/rfc7541#appendix-B
    //------------------------------------------------------------

    // バイト数を変更したら配列数を変更してください、また、SSL_wirteにわたすバイト数も変更してください。
    // フレームの先頭3byteはフレームに含まれるバイト数です。全体で74ならば、そこからヘッダフレーム9byteを引いた64(0x00, 0x00, 0x41)を指定します。
    const unsigned char headersframe[74] = {
        0x00, 0x00, 0x41, 0x01, 0x05, 0x00, 0x00, 0x00, 0x01,   // ヘッダフレーム(**バイト数を変更したら上位３ビットを変更してください**)
        0x00,                                                   // 圧縮情報
        0x07, 0x3a, 0x6d, 0x65, 0x74, 0x68, 0x6f, 0x64,         // 7 :method
        0x03, 0x47, 0x45, 0x54,                                 // 3 GET
        0x00,                                                   // 圧縮情報
        0x05, 0x3a, 0x70, 0x61, 0x74, 0x68,                     // 5 :path
        0x01, 0x2f,                                             // 1 /
        0x00,                                                   // 圧縮情報
        0x07, 0x3a, 0x73, 0x63, 0x68, 0x65, 0x6d, 0x65,         // 7 :scheme
        0x05, 0x68, 0x74, 0x74, 0x70, 0x73,                     // 5 https
        0x00,                                                   // 圧縮情報
        0x0a, 0x3a, 0x61, 0x75, 0x74, 0x68, 0x6f, 0x72, 0x69, 0x74, 0x79,           // 10 :authority
        0x0f, 0x77, 0x77, 0x77, 0x2e, 0x79, 0x61, 0x68, 0x6f, 0x6f, 0x2e, 0x63, 0x6f, 0x2e, 0x6a, 0x70 };  // 15.www.yahoo.co.jp

    printf("=== Start write HEADERS frame\n");
    while (1){

        r = SSL_write(_ssl, headersframe, 74);

        ret = SSL_get_error(_ssl, r);
        switch (ret){
            case SSL_ERROR_NONE:
                b = true;
                break;
            case SSL_ERROR_WANT_WRITE:
                continue;
            default:
                if (r == -1){
                    printf("Error Occured: Writing Header Frame SSL_write");
                    error = get_error();
                    close_socket(_socket, _ctx, _ssl);
                    return 0;
                }
        }
        if (b) break;
    }

    //------------------------------------------------------------
    // HEADERSフレームの受信.
    //------------------------------------------------------------

    // まずはヘッダフレームを受信してpayloadのlengthを取得する。
    printf("=== Start recv HEADERS frame\n");
    while (1){

        memset(buf, 0x00, BINARY_FRAME_LENGTH);
        p = buf;

        while (1){

            r = SSL_read(_ssl, p, BINARY_FRAME_LENGTH);
            printf("BINARY_FRAME: %02x %02x %02x %02x %02x %02x %02x %02x %02x\n", p[0], p[1], p[2], p[3], p[4], p[5], p[6], p[7], p[8]);
            ret = SSL_get_error(_ssl, r);
            switch (ret){
                case SSL_ERROR_NONE:
                    b = true;
                    break;
                case SSL_ERROR_WANT_READ:
                    continue;
                default:
                    if (r == -1){
                        printf("Error Occured: HEADER_FRAME SSL_read");
                        error = get_error();
                        close_socket(_socket, _ctx, _ssl);
                        return 0;
                    }
            }
            if (b) break;
        }

        if (r == 0) continue;

        // ACKが返ってくる場合があるのでACKなら無視して次を読む。
        if (memcmp(buf, settingframeAck, BINARY_FRAME_LENGTH) == 0){
            printf("===== Received Ack Ignored\n");
            continue;
        }
        else{

            printf("===== Start recv payload length\n");
            // payloadの長さを取得する。
            p = to_framedata3byte(p, payload_length);
            printf("\nlength: %d\n", payload_length);

            // フレームタイプがHEADERS_FRAMEではなかったら読み飛ばす。
            memcpy(&frame_type, p, 1);
            if (frame_type != 1){

                while (payload_length > 0){
                    printf("===== Start recv payload contents\n");

                    r = SSL_read(_ssl, p, payload_length);
                    ret = SSL_get_error(_ssl, r);
                    switch (ret){
                        case SSL_ERROR_NONE:
                            b = true;
                            break;
                        case SSL_ERROR_WANT_READ:
                            continue;
                        default:
                            if (r == -1){
                                printf("Error Occured: recv payload contents SSL_read");
                                error = get_error();
                                close_socket(_socket, _ctx, _ssl);
                                return 0;
                            }
                    }
                    payload_length -= r;
                }
                continue;
            }
            break;
        }
    }

    //------------------------------------------------------------
    // HEADERSフレームのpayloadの受信.
    //------------------------------------------------------------
    printf("=== Start read HEADERS frame payload\n");
    while (payload_length > 0){

        memset(buf, 0x00, BUF_SIZE);
        p = buf;

        r = SSL_read(_ssl, p, payload_length);
        ret = SSL_get_error(_ssl, r);
        switch (ret){
            case SSL_ERROR_NONE:
                break;
            case SSL_ERROR_WANT_READ:
                continue;
            default:
                if (r == -1){
                    printf("Error Occured: recv payload SSL_read");
                    error = get_error();
                    close_socket(_socket, _ctx, _ssl);
                    return 0;
                }
        }
        payload_length -= r;
    }

    //------------------------------------------------------------
    // DATAフレームの受信.
    //------------------------------------------------------------

    // まずはヘッダフレームを受信してpayloadのlengthを取得する。
    printf("=== Start read DATA frame\n");
    while (1){

        memset(buf, 0x00, BUF_SIZE);
        p = buf;

        r = SSL_read(_ssl, p, BINARY_FRAME_LENGTH);
        ret = SSL_get_error(_ssl, r);
        switch (ret){
            case SSL_ERROR_NONE:
                break;
            case SSL_ERROR_WANT_READ:
                continue;
            default:
                if (r == -1){
                    printf("Error Occured: Header Framme payload_length SSL_read");
                    error = get_error();
                    close_socket(_socket, _ctx, _ssl);
                    return 0;
                }
        }
        if (b) break;
    }

    to_framedata3byte(p, payload_length);
    printf("Received FramePayloadSize: %d\n", payload_length);

    // 次にpayloadを受信する。
    while (payload_length > 0){

        memset(buf, 0x00, BUF_SIZE);
        p = buf;

        r = SSL_read(_ssl, p, READ_BUF_SIZE);
        ret = SSL_get_error(_ssl, r);
        switch (ret){
            case SSL_ERROR_NONE:
                break;
            case SSL_ERROR_WANT_READ:
                continue;
            default:
                if (r == -1){
                    printf("Error Occured: payload contents SSL_read");
                    error = get_error();
                    close_socket(_socket, _ctx, _ssl);
                    return 0;
                }
        }

        payload_length -= r;

        printf("%s", p);
    }


    //------------------------------------------------------------
    // GOAWAYの送信.
    //
    // これ以上データを送受信しない場合はGOAWAYフレームを送信します.
    // フレームタイプは「0x07」
    // ストリームIDは「0x00」(コネクション全体に適用するため)
    //------------------------------------------------------------
    const char goawayframe[17] = { 0x00, 0x00, 0x00, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00 };

    printf("=== Start write GOAWAY frame\n");
    while (1){

        r = SSL_write(_ssl, goawayframe, 17);

        ret = SSL_get_error(_ssl, r);
        switch (ret){
            case SSL_ERROR_NONE:
                b = true;
                break;
            case SSL_ERROR_WANT_WRITE:
                continue;
            default:
                if (r == -1){
                    printf("Error Occured: GOAWAY SSL_write");
                    error = get_error();
                    close_socket(_socket, _ctx, _ssl);
                    return 0;
                }
        }
        if (b) break;
    }

    close_socket(_socket, _ctx, _ssl);
    return 0;
}

void close_socket(SOCKET socket, SSL_CTX *_ctx, SSL *_ssl){

    SSL_shutdown(_ssl);
    SSL_free(_ssl);

    ::shutdown(socket, SD_BOTH);
    ::close(socket);

    SSL_CTX_free(_ctx);
    ERR_free_strings();

}

int get_error(){
    return errno;
}

char* to_framedata3byte(char *p, int &n){
    u_char buf[4] = {0};      // bufを4byte初期化
    memcpy(&(buf[1]), p, 3);  // bufの2byte目から4byteめまでをコピー
    memcpy(&n, buf, 4);       // buf領域を全てコピー
    n = ntohl(n);             // ネットワークバイトオーダーを変換
    p += 3;                   // 読み込んだ3byteをスキップする
    return p;
}

static ssize_t to_hex(unsigned char *dst, size_t dst_len, unsigned char *src, size_t src_len) {
	ssize_t wr = 0;
	for (size_t i = 0; i < src_len; i++) {
		int w = snprintf((char *) dst + wr, dst_len - (size_t) wr, "%02x", src[i]);
		if (w <= 0)
			return -1;
		wr += (ssize_t) w;
	}
	return wr;
}


