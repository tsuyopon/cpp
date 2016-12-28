/*
 * 概要: rawdump1.cに加えてdumpmsg関数を追加した。これによってパケット情報をdumpするようにしました。
 *
 * [使い方]
 *   $ ./a.out    // この後にエンターが押下されて初めてキャプチャーが開始されます。
 *
 *  sample program
 *  RAW socket test program
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <arpa/inet.h>
#include <net/ethernet.h>
#include <errno.h>

static void dumpmsg(void *, int);

int main(void) {
	struct ether_header *eth;
	struct iphdr *ip;
	char buf[ETHER_MAX_LEN] = {0};
	char smac[20], dmac[20];
	char sip[16], dip[16];
	int sockfd = 0, len = 0, protocol = 0;

	// SOCK_RAWを指定することによりRAWを受信することができる。
	// htons(ETH_P_ALL)が指定されると全てのプロトコルが指定されたのと同様　
	sockfd = socket(PF_PACKET, SOCK_RAW, htons(ETH_P_ALL));
	if(sockfd < 0){
		perror("socket error");
		return -1;
	}

	while(1){
		len = recv(sockfd, buf, sizeof(buf), 0);
		if(len < 0){
			perror("recv error");
			break;
		}
		eth = (struct ether_header *)buf;
		sprintf(dmac, "%02x:%02x:%02x,%02x:%02x:%02x",
			eth->ether_dhost[0], eth->ether_dhost[1],
			eth->ether_dhost[2], eth->ether_dhost[3],
			eth->ether_dhost[4], eth->ether_dhost[5]);
		sprintf(smac, "%02x:%02x:%02x,%02x:%02x:%02x",
			eth->ether_shost[0], eth->ether_shost[1],
			eth->ether_shost[2], eth->ether_shost[3],
			eth->ether_shost[4], eth->ether_shost[5]);
		protocol = ntohs(eth->ether_type);
		fprintf(stdout, "\nMAC : %s >> %s (Protocol = %04x, size = %dbyte)\n",
			smac, dmac, protocol, len);
		switch(protocol){
		case ETHERTYPE_IP:
			ip = (struct iphdr *)(buf + sizeof(struct ether_header));
			sprintf(sip, "%s", inet_ntoa(*(struct in_addr *)&(ip->saddr)));
			sprintf(dip, "%s", inet_ntoa(*(struct in_addr *)&(ip->daddr)));
			fprintf(stdout, "IP %s > %s (%dbyte)\n",
				sip, dip, ntohs(ip->tot_len));
			break;
		case ETHERTYPE_ARP:
			fprintf(stdout, "ARP\n");
			break;
		case ETHERTYPE_REVARP:
			fprintf(stdout, "Reverse ARP\n");
			break;
		default:
			fprintf(stdout, "other protocol\n");
			break;
		}

		dumpmsg(buf, len);
		memset(buf, 0, len);
	}
	close(sockfd);
	return 0;
}

static void dumpmsg(void *buf, int size)
{
	unsigned char *pbuf, *px, *pc;
	int i = 0;
	char outbuf[80];
	char *pout;

	px = pc = pbuf = (unsigned char *)buf;
	while((px - pbuf) < size){
		memset(outbuf, 0, sizeof(outbuf));
		pout = outbuf;
		sprintf(pout, "%04d : ", (px - pbuf));
		pout += 7;
		/* print hex */
		for(i=0 ; i<16 && (px - pbuf) < size ; i++, px++){
			sprintf(pout, "%02x ", *px);
			pout += 3;
 			if(i==7){
				sprintf(pout++, " ");
			}
		}
		/* add space */
 		if(i != 16){
 			if(i < 8){
				sprintf(pout++, " ");
			}
			for( ; i<16 ; i++){
				sprintf(pout, "   ");
				pout += 3;
			}
		}
		sprintf(pout, "    ");
		pout += 4;
		/* print ascii */
 		for(i=0 ; i<16 && (pc - pbuf) < size ; i++, pc++){
			if((*pc < 0x20) || (*pc > 0x7f)){
				sprintf(pout++, ".");
			}else{
				sprintf(pout++, "%c", *pc);
			}
			if(i==7){
				sprintf(pout++, " ");
			}
		}
		fprintf(stdout, "%s\n", outbuf);
	}
	return;
}

