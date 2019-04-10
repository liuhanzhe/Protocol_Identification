#include "header.h"

using namespace std;

map<int, string> map_tcp_protocol;
map<int, string> map_udp_protocol;

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

//16位16进制转10进制端口
int byte_to_port(u_short bport)
{
    int port = ((u_char*)&bport)[0]*256 + ((u_char*)&bport)[1];
    return port;
}


/**
    type: 0: tcp 
          1: udp
**/
string find_protocol_from_config(int type, int sport, int dport)
{
    map<int, string> map_protocol;
    if(type == 0)
    {
        map_protocol = map_tcp_protocol;
    }
    else if (type == 1)
    {
        map_protocol = map_udp_protocol;
    }   
    
    string protocol_name = "";
    map<int, string>::iterator siter = map_protocol.find(sport);
    map<int, string>::iterator piter = map_protocol.find(dport);
    if(siter != map_protocol.end())
    {
        protocol_name = siter->second;
    }
    else if(piter != map_protocol.end())
    {
        protocol_name = piter->second;
    }
    return protocol_name;
}

void handle_udp()
{

}

void handle_tcp(const u_char * packet)
{
    int sport = byte_to_port(((struct TCP_HEAD*)(packet+ETHER_HEADER_LEN+IP_HEADER_LEN))->tcp_sport);
    int dport = byte_to_port(((struct TCP_HEAD*)(packet+ETHER_HEADER_LEN+IP_HEADER_LEN))->tcp_dport);
}


void handle_ip(const u_char * packet)
{
    if(0x11==((struct IP_HEAD*)(packet+ETHER_HEADER_LEN))->ip_p)
    {
       //udp
    }
    else if(0x06==((struct IP_HEAD*)(packet+ETHER_HEADER_LEN))->ip_p)
    {
        //tcp
        handle_tcp(packet);
    }
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
		handle_ip(packet);
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

void load_protocol_config()
{
    
}

pcap_t* pcap_init()
{
	char errBuf[PCAP_ERRBUF_SIZE], * p_net_interface_name;

    load_protocol_config();

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
