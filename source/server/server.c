#include <enet/enet.h>
#include <stdio.h>

int main(int argsCount, char ** arguments){
        if (enet_initialize() != 0) {
        fprintf(stderr, "An error occurred while initializing ENet.\n");
        exit(EXIT_FAILURE);
    }else {
        printf("ENet initialized\n");
    }


    enet_deinitialize();
    return 0;
}
