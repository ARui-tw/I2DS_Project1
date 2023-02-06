/*
 * This is sample code generated by rpcgen.
 * These are only templates and you can use them
 * as a guideline for developing your own functions.
 */

#include <arpa/inet.h>
#include <errno.h>
#include <netdb.h>
#include <netinet/in.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>  //memset
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#include "communicate.h"

#define BUFLEN 512

void die(char *s) {
    perror(s);
    exit(1);
}

// This function returns host name for local computer
void check_host_name(int hostname) {
    if (hostname == -1) {
        perror("gethostname");
        exit(1);
    }
}

// find host info from host name
void check_host_entry(struct hostent *hostentry) {
    if (hostentry == NULL) {
        perror("gethostbyname");
        exit(1);
    }
}

// convert IP string to dotted decimal format
void IP_formatter(char *IPbuffer) {
    if (NULL == IPbuffer) {
        perror("inet_ntoa");
        exit(1);
    }
}

char *get_current_ip() {
    char client[256];
    char *client_IP;
    struct hostent *host_entry;
    int hostname;

    hostname = gethostname(client, sizeof(client));  // find the host name
    check_host_name(hostname);
    host_entry = gethostbyname(client);  // find host information
    check_host_entry(host_entry);

    client_IP = inet_ntoa(
        *((struct in_addr *)
              host_entry->h_addr_list[0]));  // Convert into client_IP string

    return client_IP;
}

void *startUPServer(void *a) {
    int *s;
    int recv_len;
    struct sockaddr_in si_other;
    char buf[BUFLEN];
    socklen_t slen = sizeof(si_other);
    s = (int *)a;

    while (1) {
        printf("Waiting for data...");
        fflush(stdout);

        // try to receive some data, this is a blocking call
        if ((recv_len = recvfrom(*s, buf, BUFLEN, 0,
                                 (struct sockaddr *)&si_other, &slen)) == -1) {
            die("recvfrom()");
        }

        // print details of the client/peer and the data received
        printf("Received packet from %s:%d\n", inet_ntoa(si_other.sin_addr),
               ntohs(si_other.sin_port));
        printf("Data: %s\n", buf);

        // now reply the client with the same data
        if (sendto(*s, buf, recv_len, 0, (struct sockaddr *)&si_other, slen) ==
            -1) {
            die("sendto()");
        }
    }

    close(*s);
}

void communicate_prog_1(char *host) {
    CLIENT *clnt;
    bool_t *result_1;
    char *join_1_IP;
    int join_1_Port;
    bool_t *result_2;
    char *leave_1_IP;
    int leave_1_Port;
    bool_t *result_3;
    char *subscribe_1_IP;
    int subscribe_1_Port;
    char *subscribe_1_Article;
    bool_t *result_4;
    char *unsubscribe_1_IP;
    int unsubscribe_1_Port;
    char *unsubscribe_1_Article;
    bool_t *result_5;
    char *publish_1_Article;
    char *publish_1_IP;
    int publish_1_Port;
    bool_t *result_6;

#ifndef DEBUG
    clnt = clnt_create(host, COMMUNICATE_PROG, COMMUNICATE_VERSION, "udp");
    if (clnt == NULL) {
        clnt_pcreateerror(host);
        exit(1);
    }
#endif /* DEBUG */

    char *client_IP = get_current_ip();

    printf("Client IP: %s\n", client_IP);

    //--------
    char myIP[16];
    unsigned int myPort;
    struct sockaddr_in si_me, si_other;

    int s, i;

    // create a UDP socket
    if ((s = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == -1) {
        die("socket");
    }

    // zero out the structure
    memset((char *)&si_me, 0, sizeof(si_me));

    si_me.sin_family = AF_INET;
    si_me.sin_port = htons(0);
    si_me.sin_addr.s_addr = htonl(INADDR_ANY);

    if (bind(s, (struct sockaddr *)&si_me, sizeof(si_me)) == -1) {
        die("bind");
    }

    struct sockaddr_in my_addr;
    bzero(&my_addr, sizeof(my_addr));
    socklen_t len = sizeof(my_addr);
    getsockname(s, (struct sockaddr *)&my_addr, &len);
    myPort = ntohs(my_addr.sin_port);

    printf("Local port : %u\n", myPort);

    //-----

    pthread_t t;

    int rc;

    rc = pthread_create(&t, NULL, startUPServer, (void *)&s);

    result_1 = join_1(client_IP, myPort, clnt);
    if (result_1 == (bool_t *)NULL) {
        clnt_perror(clnt, "call failed");
    }

    // Keep the server up
    pthread_join(t, NULL);

    // result_2 = leave_1(leave_1_IP, leave_1_Port, clnt);
    // if (result_2 == (bool_t *) NULL) {
    // 	clnt_perror (clnt, "call failed");
    // }
    // result_3 = subscribe_1(subscribe_1_IP, subscribe_1_Port,
    // subscribe_1_Article, clnt); if (result_3 == (bool_t *) NULL) {
    // 	clnt_perror (clnt, "call failed");
    // }
    // result_4 = unsubscribe_1(unsubscribe_1_IP, unsubscribe_1_Port,
    // unsubscribe_1_Article, clnt); if (result_4 == (bool_t *) NULL) {
    // 	clnt_perror (clnt, "call failed");
    // }
    // result_5 = publish_1(publish_1_Article, publish_1_IP, publish_1_Port,
    // clnt); if (result_5 == (bool_t *) NULL) { 	clnt_perror (clnt, "call
    // failed");
    // }
    // result_6 = ping_1(clnt);
    // if (result_6 == (bool_t *) NULL) {
    // 	clnt_perror (clnt, "call failed");
    // }
#ifndef DEBUG
    clnt_destroy(clnt);
#endif /* DEBUG */
}

int main(int argc, char *argv[]) {
    char *host;

    if (argc < 2) {
        printf("usage: %s server_host\n", argv[0]);
        exit(1);
    }
    host = argv[1];
    communicate_prog_1(host);
    exit(0);
}
