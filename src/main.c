#include "brain.h"

int main (int argc, char *argv[]) {

    //Check args
    if (2 != argc) {
        fprintf(stderr, "%s", errorMessage[ERR_NO_INPUT_FILE]);
        exit(1);
    }
    //Open file
    int source_fd = open(argv[1], O_RDONLY);
    if (source_fd<0) {
        fprintf(stderr, errorMessage[ERR_FILE_NOT_FOUND], argv[1]);
        exit(1);
    }
    
    close(source_fd);

    return 0;
}