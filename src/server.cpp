#include <iostream>
#include <string>
#include <unistd.h>
#include <stdlib.h>
#include <ev.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <netdb.h>
#include <sys/types.h>

#define PORT 8080

int main() {
	int server_fd, client_socket;
	struct sockaddr_in client_address;
	int client_addrlen = sizeof(client_address);
	int opt = 1;
	char *msg = "Hello, World!";

	if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
		std::cout << "Socket failed" << std::endl;
		exit(EXIT_FAILURE);
	}

	if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) {
		std::cout << "Cannot bind port" << std::endl;
		exit(EXIT_FAILURE);
	}

	client_address.sin_family = AF_INET;
	client_address.sin_addr.s_addr = INADDR_ANY;
	client_address.sin_port = htons(PORT);

	if (bind(server_fd, (struct sockaddr*)&client_address, sizeof(client_address)) < 0) {
		std::cout << "Cannot bind port to server" << std::endl;
		exit(EXIT_FAILURE);
	}

	if (listen(server_fd, 3) < 0) {
		std::cout << "Listen failed" << std::endl;
		exit(EXIT_FAILURE);
	}

	if ((client_socket = accept(server_fd, (struct sockaddr*)&client_address, (socklen_t*)&client_addrlen)) < 0) {
		std::cout << "Accepting new socket error" << std::endl;
		exit(EXIT_FAILURE);
	}
	
	send(client_socket, msg, strlen(msg), 0);
	std::cout << "message sent" << std::endl;

	return 0;
}