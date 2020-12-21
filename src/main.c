#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include "utils.h"

#define MSG_S		60
#define MSG_L		1024
#define PORT_NUM	3655

void main(void)
{
	int server_sockfd, client_sockfd;
	int server_len, client_len;
	struct sockaddr_in server_address;
	struct sockaddr_in client_address;
	char Msg1[MSG_S] = "You Chose Number [1] -> Check LED!\n";
	char Msg2[MSG_L];
	char Msg3[MSG_S] = "You Chose Number [3] -> http://192.168.219.104/log.html\n"; // local ip address
	char Msg4[MSG_S] = "You Chose Number [4] -> End Connection\n";
	char Msgd[MSG_S] = "Err - Wrong Number -> Try Again\n";
	int strlen;
	int t, h, d;

	unlink("server_socket");
	server_sockfd = socket(AF_INET, SOCK_STREAM, 0);

	server_address.sin_family = AF_INET;
	server_address.sin_addr.s_addr = htonl(INADDR_ANY);
	server_address.sin_port = htons(PORT_NUM);
	server_len = sizeof(server_address);
	bind(server_sockfd, (struct sockaddr *)&server_address, server_len);

	listen(server_sockfd, 5);

	while(1) {
		char num;
		printf("Server On!\n");
		client_len = sizeof(client_address);
		client_sockfd = accept(server_sockfd, (struct sockaddr *)&client_address, &client_len);
		recv(client_sockfd, &num, 1, 0);
		switch(num) {
		case '1':
			use_thread();
			send(client_sockfd, Msg1, MSG_S, 0); 
			t = temp_out();
			h = humid_out();
			d = dust_data;
			printf("LED LIGHTING\n");
			t_led(t);
			h_led(h);
			d_led(d);
			break;
		case '2':
			use_thread();
			d = dust_data;
			t = temp_out();
			h = humid_out();
			sprintf(Msg2, "You Chose Number [2] -> Temperature:%d℃ , Humidity:%d%c, Air Pollution:%d㎍/㎥\n", t, h, '%', d); 
			send(client_sockfd, Msg2, MSG_L, 0);
			break;
		case '3':
			use_thread();
			send(client_sockfd, Msg3, MSG_S, 0);
			t = temp_out();
			h = humid_out();
			d = dust_data;
			upload_html(t, h, d);
			break;
		case '4':
			send(client_sockfd, Msg4, MSG_S, 0);
			printf("Server OFF\n");
			exit(0);
		default:
			send(client_sockfd, Msgd, MSG_S, 0);
		}
		close(client_sockfd);
	}
}

