/*
 * IRC Client prototype 2
 * - OOP, modularity
 * - handle 1 connection at once
 * - send IRC messages
 * - print recieved messages
 * - encode and decode commands and messages
 */
#include <iostream>  // cin; cout
#include <string>    // std::string
#include <stdexcept> // throwing exceptions
#include <string.h>  // memset()
#include <unistd.h>  // close()
// multithreading
#include <mutex>
#include <thread>
// socket & networking headers
#include <sys/socket.h>
#include <sys/types.h>
#include <netdb.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define MAXMSGLEN 512 // max message length specified by IRC protocol

#define PORT_PLAIN "6667" // TCP/6667 port for plaintext connection

using SA = struct sockaddr;
using SA_in = struct sockaddr_in;
using SA_in6 = struct sockaddr_in6;
using AI = struct addrinfo;

namespace Client {
	// convert sockaddr to sockaddr_in or sockaddr_in6 (IPv4 or IPv6)
	void *getInAddr(SA *sa);

	// closed connection message
	void connectionClosed(int connection); 

	void getUserInput(std::string& message);

	/* Command: PRIVMSG
	   Parameters: <target>{,<target>} <text to be sent> */
	void prepareMessage(std::string data);

	class Connection {
	public:
		// constructor
		Connection();
		// establish new connection
		void connectToServer(char *hstnm);
		// send data
		void sendData(const char *data, int data_size);
		// recieve data
		void recieveData(std::mutex *mtx);
	private:
		// socket file descriptor
		int sockfd = 0;
		// server host name
		std::string host_name;
		// connection specification
		AI hints;
	};
}



