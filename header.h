#ifndef _HEADER_H_
#define _HEADER_H_

#include <pcap.h>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <arpa/inet.h>

#include <string>
	


#define ETHER_ADDR_LEN 6
#define ETHER_HEADER_LEN 14
#define IP_HEADER_LEN 20
#define TCP_HEADER_LEN 20



struct ether_header
{
	unsigned char ether_dhost[ETHER_ADDR_LEN];	//目的mac
	unsigned char ether_shost[ETHER_ADDR_LEN];	//源mac
	unsigned short ether_type;		//以太网类型
};	

/*IP头*/ //假设没有选项字段，长度20字节
struct IP_HEAD
{
	u_char ip_vhl;
	u_char ip_tos;
	u_short ip_len;
	u_short ip_id;
	u_short ip_off;
	#define IP_RF 0x8000
	#define IP_DF 0x4000
	#define IP_MF 0x2000
	#define IP_OFFMASK 0x1fff
	u_char ip_ttl;
	u_char ip_p;
	u_short ip_sum;
	struct in_addr ip_src,ip_dst;
};
/*UDP报头*/
struct UDP_HEAD
{
	u_short udp_sport;
	u_short udp_dport;
	u_short udp_len;
	u_short udp_sum;
};

struct TCP_HEAD
{
    u_short tcp_sport;    // 源端口号16bit
    u_short tcp_dport;    // 目的端口号16bit
    unsigned int tcp_seq;   // 序列号32bit
    unsigned int tcp_ack;    // 确认号32bit
    u_short tcp_headlen_flag;    // 前4位：TCP头长度；中6位：保留；后6位：标志位
    u_short tcp_winsize;  // 窗口大小16bit
    u_short tcp_chksum;    // 检验和16bit
    u_short tcp_surgen_pointer;   // 紧急数据偏移量16bit
};

struct ICMP_HEAD  
{  
    unsigned char icmp_type;   //类型  
    unsigned char code;        //代码  
    unsigned short chk_sum;    //16位检验和  
};
#endif
