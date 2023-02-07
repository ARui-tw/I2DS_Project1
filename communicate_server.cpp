/*
 * This is sample code generated by rpcgen.
 * These are only templates and you can use them
 * as a guideline for developing your own functions.
 */

#include <iostream>

#include "communicate.h"

#define MAXCLIENT 7;

bool_t *join_1_svc(char *IP, int Port, struct svc_req *rqstp) {
    static bool_t result;

    /*
     * insert server code here
     */
    std::cout << "In join_1_svc\n";
    std::cout << IP << std::endl;
    std::cout << Port << std::endl;
    std::cout << std::endl;

    return &result;
}

bool_t *leave_1_svc(char *IP, int Port, struct svc_req *rqstp) {
    static bool_t result;

    /*
     * insert server code here
     */
    std::cout << "In leave_1_svc\n";
    std::cout << IP << std::endl;
    std::cout << Port << std::endl;
    std::cout << std::endl;

    return &result;
}

bool_t *subscribe_1_svc(char *IP, int Port, char *Article,
                        struct svc_req *rqstp) {
    static bool_t result;

    /*
     * insert server code here
     */

    return &result;
}

bool_t *unsubscribe_1_svc(char *IP, int Port, char *Article,
                          struct svc_req *rqstp) {
    static bool_t result;

    /*
     * insert server code here
     */

    return &result;
}

bool_t *publish_1_svc(char *Article, char *IP, int Port,
                      struct svc_req *rqstp) {
    static bool_t result;

    /*
     * insert server code here
     */

    return &result;
}

bool_t *ping_1_svc(struct svc_req *rqstp) {
    static bool_t result;

    /*
     * insert server code here
     */

    return &result;
}
