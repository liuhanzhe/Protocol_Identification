
#include <pcap.h>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>


void handle_packet(u_char * arg, const struct pcap_pkthdr * pkthdr, const u_char * packet)
{
  int * id = (int *)arg;
  
  printf("id: %d\n", ++(*id));
  printf("Packet length: %d\n", pkthdr->len);
  printf("Number of bytes: %d\n", pkthdr->caplen);
  printf("Recieved time: %s", ctime((const time_t *)&pkthdr->ts.tv_sec)); 
  
  int i;
  for(i=0; i<pkthdr->len; ++i)
  {
    printf(" %02x", packet[i]);
    if( (i + 1) % 16 == 0 )
    {
      printf("\n");
    }
  }
  
  printf("\n\n");
}

void load_protocol_config()
{
    
}

int main()
{
    
    char errBuf[PCAP_ERRBUF_SIZE], * device;

    load_protocol_config();

    device = pcap_lookupdev(errBuf);

    printf("open device: %s\n", device);

    pcap_t *descr = pcap_open_live(device, 65535, 1, 0, errBuf);  

    int count = 0;
    pcap_loop(descr, -1, handle_packet, (u_char *)&count); 
   
    pcap_close(descr);
 
	return 0;
}
