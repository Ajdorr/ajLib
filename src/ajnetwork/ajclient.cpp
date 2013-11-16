#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include "ajutil.h"
#include "jclient.h"

jclient::jclient()
{
    hsnm = NULL;
    prt = NULL;
    type = -1;

    soc = -1;
}

jclient::jclient(char* hostname, char* port) {
    // copy hostname and port
    hsnm = new char[strlen(hostname) + 1];
    strcpy(hsnm, hostname);
    prt = new char[strlen(port) +1];
    strcpy(prt, port);

    soc = -1;
    type = -1;
}

jclient::jclient(char* hostname, unsigned int port) {
    // copy hostname
    hsnm = new char[strlen(hostname) + 1];
    strcpy(hsnm, hostname);

    // copy port
    prt = itoa(port, 10);

    // default to invalid
    soc = -1;
    type = -1;
    this->tcp();
}

void jclient::init(char* hostname, char* port) {
    // copy hostname
    if (hsnm != NULL) {
        delete hsnm;
        hsnm = NULL;
    }
    hsnm = new char[strlen(hostname) + 1];
    strcpy(hsnm, hostname);

    // copy port
    if (prt != NULL) {
        delete prt;
        prt = NULL;
    }
    prt = new char[strlen(port) +1];
    strcpy(prt, port);
    this->tcp();
}

void jclient::init(char* hostname, unsigned int port) {
    // copy hostname
    if (hsnm != NULL) {
        delete hsnm;
        hsnm = NULL;
    }
    hsnm = new char[strlen(hostname) + 1];
    strcpy(hsnm, hostname);

    // copy port
    if (prt != NULL) {
        delete prt;
        prt = NULL;
    }
    prt = itoa((int)port, 10);
}

void jclient::tcp() {
    type = TCP;
    memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
}

void jclient::udp() {
    type = UDP;
    memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_DGRAM;
}

int jclient::connecttcp() {
    struct addrinfo *addrs, *p;

    // get the address info and pass some hints
    if (getaddrinfo(hsnm, prt, &hints, &addrs) < 0) {
        return -1;
    }

    // loop through all possibilities
    for (p = addrs; p != NULL; p = p->ai_next) {
        // create a socket file descriptor
        if ( (soc = socket(p->ai_family, p->ai_socktype, p->ai_protocol)) < 0 ) {
            continue;
        // try to connect over it
        } else if (connect(soc, p->ai_addr, p->ai_addrlen) < 0) {
            close(soc);
            continue;
        }
        break;
    }

    // check if we failed
    if (p == NULL) {
        soc = -1;
        return -1;
    }

    // done with this now
    freeaddrinfo(addrs);
    p = NULL;

    return 0;
}

int jclient::isConnected() {
    if (soc == -1) {
        return 1;
    }

    return 0;
}


