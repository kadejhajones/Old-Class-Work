#include <stdio.h>	//for printf
#include <string.h> //memset
#include <sys/socket.h>	//for socket ofcourse
#include <stdlib.h> //for exit(0);
#include <errno.h> //For errno - the error number
#include <netinet/tcp.h>	//Provides declarations for tcp header
#include <netinet/ip.h>	//Provides declarations for ip header
#include <arpa/inet.h> // inet_addr
#include <unistd.h> // sleep()

/*
	96 bit (12 bytes) pseudo header needed for tcp header checksum calculation
*/
struct pseudo_header
{
	u_int32_t source_address;
	u_int32_t dest_address;
	u_int8_t placeholder;
	u_int8_t protocol;
	u_int16_t tcp_length;
};

/*
	Generic checksum calculation function
*/
unsigned short csum(unsigned short *ptr,int nbytes)
{
	register long sum;
	unsigned short oddbyte;
	register short answer;

	sum=0;
	while(nbytes>1) {
		sum+=*ptr++;
		nbytes-=2;
	}
	if(nbytes==1) {
		oddbyte=0;
		*((u_char*)&oddbyte)=*(u_char*)ptr;
		sum+=oddbyte;
	}

	sum = (sum>>16)+(sum & 0xffff);
	sum = sum + (sum>>16);
	answer=(short)~sum;

	return(answer);
}

int main(int argc, char** argv)
{
	// usage
	if( argc != 2 ) {
		printf("Usage: %sockfd IP_ADDRESS\n\tIP_ADDRESS must be in dotted-decimal format\nq", argv[0]);
		exit(EXIT_FAILURE);
	}

	// make a socket
	int sockfd = socket(AF_INET, SOCK_RAW, IPPROTO_TCP);
	if( sockfd < 0 ) {
		perror("Couldn't open socket");
		return EXIT_FAILURE;
	}

	// scan ports!
	printf("port/tcp - status\n");
	printf("-------------\n");


	//Datagram to represent the packet
	char datagram[4096] , source_ip[32] , *data , *pseudogram;

	//zero out the packet buffer
	memset (datagram, 0, 4096);

	//IP header
	struct iphdr *iph = (struct iphdr *) datagram;

	//TCP header
	struct tcphdr *tcph = (struct tcphdr *) (datagram + sizeof (struct ip));
	struct sockaddr_in sin;
	struct pseudo_header psh;

	//Data part
	data = datagram + sizeof(struct iphdr) + sizeof(struct tcphdr);
	strcpy(data , "ABCDEFGHIJKLMNOPQRSTUVWXYZ");

	//some address resolution
	strcpy(source_ip , "10.100.100.140");
	sin.sin_family = AF_INET;
	if( inet_pton(AF_INET, argv[1], &sin.sin_addr) <= 0 ) {
		fprintf(stderr, "Invalid address, must be an IPv4 dotted-decimal address\n");
		return EXIT_FAILURE;
	}

	//Fill in the IP Header
	iph->ihl = 5;
	iph->version = 4;
	iph->tos = 0;
	iph->tot_len = sizeof (struct iphdr) + sizeof (struct tcphdr) + strlen(data);
	iph->id = htonl (54321);	//Id of this packet
	iph->frag_off = 0;
	iph->ttl = 255;
	iph->protocol = IPPROTO_TCP;
	iph->check = 0;		//Set to 0 before calculating checksum
	iph->saddr = inet_addr ( source_ip );	//Spoof the source ip address
	iph->daddr = sin.sin_addr.s_addr;

	//Ip checksum
	iph->check = csum ((unsigned short *) datagram, iph->tot_len);

	//TCP Header
	tcph->source = htons (1234);
	tcph->dest = htons (80);
	tcph->seq = 1;
	tcph->ack_seq = 0;
	tcph->doff = 5;	//tcp header size
	tcph->fin=0;
	tcph->syn=1;
	tcph->rst=0;
	tcph->psh=0;
	tcph->ack=0;
	tcph->urg=0;
	tcph->window = htons (5840);	/* maximum allowed window size */
	tcph->check = 0;	//leave checksum 0 now, filled later by pseudo header
	tcph->urg_ptr = 0;

	//Now the TCP checksum
	psh.source_address = inet_addr( source_ip );
	psh.dest_address = sin.sin_addr.s_addr;
	psh.placeholder = 0;
	psh.protocol = IPPROTO_TCP;
	psh.tcp_length = htons(sizeof(struct tcphdr) + strlen(data) );

	int psize = sizeof(struct pseudo_header) + sizeof(struct tcphdr) + strlen(data);
	pseudogram = malloc(psize);

	memcpy(pseudogram , (char*) &psh , sizeof (struct pseudo_header));
	memcpy(pseudogram + sizeof(struct pseudo_header) , tcph , sizeof(struct tcphdr) + strlen(data));

	tcph->check = csum( (unsigned short*) pseudogram , psize);

	//IP_HDRINCL to tell the kernel that headers are included in the packet
	int one = 1;
	const int *val = &one;

	if (setsockopt (sockfd, IPPROTO_IP, IP_HDRINCL, val, sizeof (one)) < 0)
	{
		perror("Error setting IP_HDRINCL");
		exit(0);
	}

	//loop if you want to flood :)
	for(int port = 20; port <= 23; port++)
	{
		//Send the packet
		sin.sin_port = htons(port);
		tcph->dest = sin.sin_port;
		if (sendto (sockfd, datagram, iph->tot_len ,	0, (struct sockaddr *) &sin, sizeof (sin)) < 0)
		{
			perror("Couldn't send");
			exit(1);
		}
		char str[4096];
		int bytes_read;
		socklen_t *addrlen = 0;
		if ( (bytes_read = recv(sockfd, str, 4096, 0)) < 0 ) {
			perror("Couldn't read");
			exit(1);
		}
		for(int i = 0; i < bytes_read; i++) {
			printf("%x ", str[i]);
		}
		putchar('\n');
		// printf("%d\n", bytes_read);
		struct tcphdr *t = (struct tcphdr *) (str + sizeof (struct ip));
		if(t->syn == 1 && t->ack == 1) {
			printf("%4d/tcp - OPEN\n", port);
		}
	}

	return 0;
}
