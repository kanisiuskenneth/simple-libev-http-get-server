#include <iostream>
#include <string>
#include <unistd.h>
#include <stdlib.h>
#include <event.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <netdb.h>
#include <sys/types.h>
#include <http/request.h>
#include <http/response.h>
#include <utils/file.h>
#include <sstream>
#include <fstream>
#include <fcntl.h>
#include <err.h>
#include <errno.h>
#include <cstring>

#define PORT 8080

struct client {
	struct event ev_read;
};

int setnonblock(int fd) {
	int flags;

	flags = fcntl(fd, F_GETFL);
	if (flags < 0) {
		return flags;
	}

	flags |= O_NONBLOCK;
	if (fcntl(fd, F_SETFL, flags) < 0) {
		return -1;
	}

	return 0;
}

void socket_read(int fd, short ev, void *arg) {
	struct client *client = (struct client *) arg;

	char buffer[8196] = {0};
	int len;

	std::cout << "Processing request..." << std::endl;
	len = read(fd, buffer, sizeof(buffer));

	if (len == 0) {
		printf("Client disconnected.\n");
        close(fd);
		event_del(&client->ev_read);
		free(client);
		return;
	} else if (len < 0) {
		printf("Socket failure, disconnecting client: %s", strerror(errno));
		close(fd);
		event_del(&client->ev_read);
		free(client);
		return;
	}

	HTTPRequest request = HTTPRequest(buffer);
	std::string msg = File("assets"+request.GetPath()).GetContent();
	std::cout << request.GetHost() << " " << request.GetMethod() << " " << request.GetPath() << std::endl;
	HTTPResponse response = HTTPResponse(200, "OK", msg);
	const char *response_string = response.ToString().c_str();

	send(fd, response_string, strlen(response_string), 0); 
	close(fd);
	event_del(&client->ev_read);
	free(client);
}

void accept_socket(int fd, short ev, void* arg) {
	int client_fd;
	struct sockaddr_in client_address;
	socklen_t client_len = sizeof(client_address);
	struct client* client;

	client_fd = accept(fd, (struct sockaddr*)&client_address, &client_len);
	if (client_fd == -1) {
		warn("accept failed");
		return;
	}

	if (setnonblock(client_fd) < 0) {
		warn("failed to set client socket nonblock");
	}

	client = (struct client*)malloc(sizeof(*client));
	if (client == NULL) {
		err(1, "malloc failed");
	}

	event_set(&client->ev_read, client_fd, EV_READ|EV_PERSIST, socket_read, &client->ev_read);
	event_add(&client->ev_read, NULL);

	printf("Accepted connection from %s\n", inet_ntoa(client_address.sin_addr));
}

int main() {
	int server_fd;
	struct sockaddr_in server_address;
	int reuseaddr_on = 1;

	struct event ev_accept;

	event_init();

	if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
		std::cout << "Socket failed" << std::endl;
		exit(EXIT_FAILURE);
	}
	
	if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &reuseaddr_on, sizeof(reuseaddr_on))) {
		perror("setsockopt");
		exit(EXIT_FAILURE);
	}

	server_address.sin_family = AF_INET;
	server_address.sin_addr.s_addr = INADDR_ANY;
	server_address.sin_port = htons(PORT);

	if (bind(server_fd, (struct sockaddr*)&server_address, sizeof(server_address)) < 0) {
		perror("bind error");
		exit(EXIT_FAILURE);
	}

	if (listen(server_fd, 3) < 0) {
		perror("listen error");
		exit(EXIT_FAILURE);
	}

	if (setnonblock(server_fd) < 0) {
		err(1, "server cannot be set to non-blocking");
	}

	std::cout << "Server is running..." << std::endl;

	event_set(&ev_accept, server_fd, EV_READ | EV_PERSIST, accept_socket, NULL);
	event_add(&ev_accept, NULL);

	event_dispatch();
	return 0;
}