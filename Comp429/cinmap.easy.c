#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char** argv) {
	// usage
	if( argc != 2 ) {
		printf("Usage: %s IP_ADDRESS\n\tIP_ADDRESS must be in dotted-decimal format\nq", argv[0]);
		exit(EXIT_FAILURE);
	}

	// make a socket
	int sockfd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if( sockfd < 0 ) {
		perror("Couldn't open socket");
		return EXIT_FAILURE;
	}

	// scan ports!
	printf("port/tcp - status\n");
	printf("-------------\n");

	struct sockaddr_in saddr = { .sin_family = AF_INET };
	if( inet_pton(AF_INET, argv[1], &saddr.sin_addr) <= 0 ) {
		fprintf(stderr, "Invalid address, must be an IPv4 dotted-decimal address\n");
		return EXIT_FAILURE;
	}

	for(int port = 1; port <= 4096; port++) {
		saddr.sin_port = htons(port);
		if( connect(sockfd, (struct sockaddr*) &saddr, sizeof(saddr)) == 0 ) {
			printf("%4d/tcp - OPEN\n", port);
			close(sockfd);
			sockfd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
			if( sockfd < 0 ) {
				perror("Couldn't open socket");
				return EXIT_FAILURE;
			}
		}
	}

	return EXIT_SUCCESS;
}
