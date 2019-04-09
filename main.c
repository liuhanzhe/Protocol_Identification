
#include <pcap.h>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>

#include "header.h"

unsigned short hanlde_ether(const u_char * packet)
{
	struct ether_header *ethernet_protocol;
	unsigned char *p_mac_string = NULL;
	unsigned short ethernet_type;

	ethernet_protocol = (struct ether_header *)packet;
	p_mac_string = (unsigned char *)ethernet_protocol->ether_shost;//获取源mac
	printf("Mac Source Address is %02x:%02x:%02x:%02x:%02x:%02x\n",*(p_mac_string+0),*(p_mac_string+1),*(p_mac_string+2),*(p_mac_string+3),*(p_mac_string+4),*(p_mac_string+5));
	p_mac_string = (unsigned char *)ethernet_protocol->ether_dhost;//获取目的mac
	printf("Mac Destination Address is %02x:%02x:%02x:%02x:%02x:%02x\n",*(p_mac_string+0),*(p_mac_string+1),*(p_mac_string+2),*(p_mac_string+3),*(p_mac_string+4),*(p_mac_string+5));
	ethernet_type = ntohs(ethernet_protocol->ether_type);
	printf("Ethernet type is :%04x\n",ethernet_type);
	return ethernet_type;
}

void handle_ip()
{

}

void handle_arp()
{

}

void handle_rarp()
{

}

void handle_packet(u_char * arg, const struct pcap_pkthdr * pkthdr, const u_char * packet)
{
	unsigned short ethernet_type = hanlde_ether(packet);
	if(ethernet_type == 0x0800)
	{
		handle_ip();
	}
	else if(ethernet_type == 0x0806)
	{
		handle_arp();
	}
	else if(ethernet_type == 0x0835)
	{
		handle_rarp();
	}
}

//void load_protocol_config()
//{
    
//}

pcap_t* pcap_init()
{
	char errBuf[PCAP_ERRBUF_SIZE], * p_net_interface_name;

    //load_protocol_config();

    p_net_interface_name = pcap_lookupdev(errBuf);

    if(NULL == p_net_interface_name)
	{
		perror("pcap_lookupdev");
		exit(-1);
	}

    printf("open device: %s\n", p_net_interface_name);

    pcap_t *pcap_handle = pcap_open_live(p_net_interface_name, 65535, 1, 0, errBuf); 

    return pcap_handle;
}

int main()
{
    
    pcap_t *pcap_handle = pcap_init();

    int count = 0;
    pcap_loop(pcap_handle, -1, handle_packet, (u_char *)&count); 
   
    pcap_close(pcap_handle);
 
	return 0;
}
