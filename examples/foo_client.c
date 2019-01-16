/*
 * Copyright (c) 2016, Juniper Networks, Inc.
 * All rights reserved.
 */

#include <stdio.h>
#include "foo.grpc-c.h"

/*
 * Takes as argument the socket name
 */
int 
main (int argc, char **argv) 
{
    if (argc < 2) {
        fprintf(stderr, "Too few arguments\n");
        exit(1);
    }

    /*
     * Initialize grpc-c library to be used with vanilla grpc
     */
    grpc_c_init(GRPC_THREADS, NULL);

    /*
     * Create a client object with client name as foo client to be talking to
     * a insecure server
     */
    grpc_c_client_t *client = grpc_c_client_init(argv[1], "foo client", NULL, NULL);

    /*
     * Create a hello request message and call RPC
     */
    foo__HelloRequest input;
    foo__hello_request__init(&input);
    foo__HelloReply *output;

    char str[BUFSIZ];
    snprintf(str, BUFSIZ, "world");
    input.name = str;

    /*
     * This will invoke a blocking RPC
     */
    int status = foo__greeter__say_hello(client, NULL, 0, &input, &output, NULL, 5000);
    if (output) {
        printf("\n\nGot back: %s\n\n", output->message);
    }
    printf("\n\nFinished with %d\n\n", status);
}
