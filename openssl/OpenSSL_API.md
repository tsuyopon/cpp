# 概要
OpenSSLのライブラリAPIについては以下のリンクから全体像を確認することができます。
opensslコマンドについては「Commands」リンクを参照のこと、opensslのライブラリAPIの使い方については「Libraries」を参照すると良い。
- https://www.openssl.org/docs/man1.0.2/
- https://www.openssl.org/docs/man1.1.0/
- https://www.openssl.org/docs/man1.1.1/

次のように命名規則が決まっているので覚えておくのが良い。この他にもいろいろありますが省略。
- BIO_*     バイナリ入出力ストリームを扱う関数 
- BN_*      不定長整数BIGNUMを扱う関数 
- MD_*      ハッシュ関数を扱う関数 
- OBJ_*     オブジェクト識別子OIDを扱う関数 
- RSA_*     RSA鍵を扱う関数 
- d2i_*     バイナリデータから構造体への変換 
- d2i_*_bio バイナリストリームから構造体の生成 
- i2d_*     構造体からバイト列への変換
- X509_*    証明書の規格(X509)関連


# SSL_CTX構造体生成

- SSL_CTX_new() 
  - SSLの構造体を生成する
```
ctx = SSL_CTX_new(SSLv23_client_method());
```
- SSL_CTX_newの引数には次のような関数を指定できます。 
```
const SSL_METHOD *SSLv3_client_method(void);
const SSL_METHOD *SSLv3_server_method(void);
const SSL_METHOD *SSLv3_method(void);

const SSL_METHOD *TLSv1_client_method(void);
const SSL_METHOD *TLSv1_server_method(void);
const SSL_METHOD *TLSv1_method(void);

const SSL_METHOD *SSLv23_client_method(void);
const SSL_METHOD *SSLv23_server_method(void);
const SSL_METHOD *SSLv23_method(void);
```


# データインタフェース
```
int SSL_read(SSL *ssl, void *buf, int num);
int SSL_write(SSL *ssl, const void *buf, int num);
```

# 鍵関連処理

### サーバ証明書をロード
```
SSL_CTX_use_certificate(SSL_CTX *, X509 *)
SSL_CTX_use_certificate_ASN1(SSL_CTX *ctx, int len, unsigned char *d);
SSL_CTX_use_certificate_file(SSL_CTX *ctx, const char *file, int type);
```

### 秘密鍵をロードする関数
```
SSL_CTX_use_PrivateKey(SSL_CTX *ctx, EVP_PKEY *pkey);
SSL_CTX_use_PrivateKey_ASN1(int pk, SSL_CTX *ctx, unsigned char *d, long len);
SSL_CTX_use_PrivateKey_file(SSL_CTX *ctx, const char *file, int type);
SSL_CTX_use_RSAPrivateKey(SSL_CTX *ctx, RSA *rsa);
SSL_CTX_use_RSAPrivateKey_ASN1(SSL_CTX *ctx, unsigned char *d, long len);
SSL_CTX_use_RSAPrivateKey_file(SSL_CTX *ctx, const char *file, int type);
```

### 信頼する証明書の組み込み
```
int SSL_CTX_load_verify_locations(SSL_CTX *ctx, const char *CAfile, const char *CApath);
```

# セッション情報

### ALPN
- クライアントから送付されてきたALPNを取得する
```
void SSL_SESSION_get0_alpn_selected(const SSL_SESSION *s, const unsigned char **alpn, size_t *len);
```
- ALPNを設定する
``` 
int SSL_SESSION_set1_alpn_selected(SSL_SESSION *s, const unsigned char *alpn, size_t len); 
```

### SNI
- クライアントから送付されてきたSNIを取得する
```
const char *SSL_SESSION_get0_hostname(const SSL_SESSION *s);
```
- SNIを設定する
```
int SSL_SESSION_set1_hostname(SSL_SESSION *s, const char *hostname);
```

### Reuseかどうかを取得する
```
int SSL_session_reused(SSL *ssl);
```


