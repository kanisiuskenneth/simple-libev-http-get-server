#include <iostream>
#include <string>
#include <unistd.h>
#include <stdlib.h>
#include <ev.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <netdb.h>
#include <sys/types.h>
#include <request.h>
#include <response.h>
#define PORT 8080

int main() {
	int server_fd, client_socket, valread;
	struct sockaddr_in client_address;
	int client_addrlen = sizeof(client_address);
	char buffer[1024] = {0}; 
	int opt = 1;
	char *msg = "<html><body><h1>HelloWorld</h1></body></html>";

	if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
		std::cout << "Socket failed" << std::endl;
		exit(EXIT_FAILURE);
	}

	// if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) {
	// 	perror("setsockopt");
	// 	exit(EXIT_FAILURE);
	// }

	client_address.sin_family = AF_INET;
	client_address.sin_addr.s_addr = INADDR_ANY;
	client_address.sin_port = htons(PORT);

	if (bind(server_fd, (struct sockaddr*)&client_address, sizeof(client_address)) < 0) {
		perror("bind");
		exit(EXIT_FAILURE);
	}

	if (listen(server_fd, 3) < 0) {
		perror("listen");
		exit(EXIT_FAILURE);
	}

	if ((client_socket = accept(server_fd, (struct sockaddr*)&client_address, (socklen_t*)&client_addrlen)) < 0) {
		perror("accept");
		exit(EXIT_FAILURE);
	}
	
	valread = read( client_socket , buffer, 1024); 
	HTTPRequest request = HTTPRequest(buffer);
	std::cout << request.GetHost() << request.GetMethod() << request.GetPath() << std::endl;
	HTTPResponse response = HTTPResponse(200, "OK", msg);
	const char *response_string = response.ToString().c_str();
	std::cout << response_string << std::endl;

    send(client_socket , response_string, strlen(response_string), 0 ); 
    printf("Hello message sent\n"); 

	return 0;
}