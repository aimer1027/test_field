#include <sys/socket.h>
#include <sys/ioctl.h>
#include <linux/if.h>
#include <linux/if_ether.h>
#include <netinet/in.h>
#include <linux/ip.h>
#include <linux/udp.h>
#include <linux/tcp.h>
#include <linux/if_arp.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// the ARP_packet is the user defined ARP protocol packet
// which without including ether-net header 

struct ARP_packet 
{
	unsigned short 		ar_hrd ;		 // arp hardware type 		  : 2 bytes
	unsigned short 		ar_pro ; 		// arp protocol 	   	  : 2 bytes
	unsigned char  		ar_hin ; 		// arp hard address length  	  : 1 bytes
	unsigned char  		ar_pin ; 		// arp protocol length 		  : 1 bytes
	unsigned char  		ar_op  ; 		// arp operation code 		  : 1 bytes 
	unsigned char  		ar_sha[ETH_ALEN] ;	 // this is the send's mac address : 6 bytes
	unsigned char 	 	ar_sip [4] ; 		// this is the source ip address        : 4 bytes
	unsigned char 		 ar_dha[ETH_ALEN] ;	 // destination mac address		: 6 bytes
	unsigned char 		 ar_dip[4] ; 		  // destination ip  address 		: 4 bytes

	char pad[18]  ;				// 18 byte length , to satisfy ether-net 's 
						// miximum frame 64 bytes with 4 bytes checksum : 18 bytes
} ;


int main ( int argc , char * argv [] )
{

   char ef[ETH_FRAME_LEN]  ;			// here we create a piece of ether-net frame 
  
   struct ethhdr  *p_ethhdr ;                  // and we create a ether-net pointer 

  // destination mac address : 6 bytes 
   char eth_dest [ETH_ALEN ] ={0x08,0x00,0x27,0xEC, 0xEB , 0xF2} ;
// {0xFF, 0xFF ,0xFF , 0xFF , 0xFF , 0xFF } ;

 // self-designed source mac address 
   char eth_source [ETH_ALEN] = {0x1F , 0x1F , 0x1F , 0x1F , 0x1F , 0x1F } ;

   char eth_arpmac [ETH_ALEN] = {0x00 , 0x00 , 0x00 , 0x00 , 0x00 , 0x00 } ;

   int n , fd , i ;

   fd = socket (AF_INET , SOCK_PACKET , htons(ETH_P_ARP)) ;

   p_ethhdr = (struct ethhdr*) ef ;

   memcpy (p_ethhdr->h_dest , eth_dest , ETH_ALEN ) ;
  
   memcpy (p_ethhdr->h_source , eth_source , ETH_ALEN ) ;

  // here we set the ether-net header protocol type value as 0x0806 which means 
  // this is the protocol of ARP
  p_ethhdr->h_proto = htons (0x0806) ;

 
  struct ARP_packet *p_arp ;

  struct in_addr in ;

  p_arp = ef + ETH_HLEN ; // let ef which points to the header of ether-net frame move a ether-net head place 
			// to point to the arp 's header
 
 p_arp->ar_hrd = htons (0x01 ) ;  // and we use the arp pointer set this arp packet is under ether-net 

 p_arp->ar_pro = htons (0x800) ; // set the protocol of ip 

 p_arp->ar_hin = 6 ; // this means the length of the ether-net address is 6

 p_arp->ar_pin = 4 ; // this means the length of ip address is 4

 p_arp->ar_op = htons (ARPOP_REQUEST) ; // set the option of the arp

 memcpy (p_arp->ar_sha , eth_source , ETH_ALEN ) ;

 memcpy ( p_arp->ar_dha , eth_dest , ETH_ALEN ) ;

 if ( ( in.s_addr = inet_addr("10.0.2.15")) == -1 )
 {
	perror ("something wrong with inet_addr method ") ;
        return -1 ;
 }

 memcpy (p_arp->ar_sip , &in.s_addr , 4 ) ;
 
 if (( in.s_addr = inet_addr ("10.2.0.37")) == -1 )
 {
	perror ("something wrong with inet_addr") ;
        return -1 ;
 }

 memcpy (p_arp->ar_dip , &in.s_addr , 4 ) ;

// bzero (p_arp->pad , 18 ) ;

// allocate it all 1 
memset (p_arp->pad , 1 ,sizeof(p_arp->pad) ) ;

 struct sockaddr to ;

 strcpy (to.sa_data , "eth0") ;

 for ( i = 0 ; i < 8 ; i++ )
 {
	if ( sendto( fd , &ef , 64 , 0 , &to , sizeof(to)) < 0 )
        {
		perror ("sendto method goes wrong") ;
		return -1 ;
        }

	printf ("send a simulate arp packet ") ;
	sleep(10) ; 
 }




	return 0 ;
}
