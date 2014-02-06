#ifndef JCLIENT_H
#define JCLIENT_H
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>

#define TCP 0
#define UDP 1

class jclient
{
private:
    int type;
    int soc; // socket
    char *hsnm, *prt; // hostname and port
    struct addrinfo hints; // address info and hints and stuff

    int connecttcp();
    int connectudp();

public:
    jclient();
    jclient(char*,char*);
    jclient(char*,unsigned int);

    void init(char* hostname, char* port);
    void init(char* hostname, unsigned int port);

    void tcp();
    void udp();

    int isConnected();
};

#endif // JCLIENT_H
