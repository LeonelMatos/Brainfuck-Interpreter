#include "brain.h"

void interrupt(int *fd, char *source, int ex_status) {
    close(fd);
    free(source);
    exit(ex_status);
}

int interpreter(int *src_fd) {
    char ch;
    int mem_ptr = 0;
    int src_ptr = 0;


    char p_memory [MEM_LEN+1];
    for (int i=0; i<MEM_LEN; i++)
        p_memory[i] = 0;

    //Get source length
    off_t src_len = lseek(src_fd, 0, SEEK_END);
    if (src_len < 0) {
        perror("Interpreter seek_end");
        close(src_fd);
        return 1;
    }
    //Create Array
    char *src_cpy = (char*) malloc(src_len);
    if (src_cpy == NULL) {
        perror("Allocating memory");
        close(src_fd);
        return 1;
    }
    //Return to start
    if (lseek(src_fd, 0, SEEK_SET) < 0) {
        perror("Interpreter seek_set");
        close(src_fd);
        return 1;
    }
    //Copy from src to src_cpy
    int src_bytesRead = read(src_fd, src_cpy, src_len);
    if (src_bytesRead < 0) {
        perror("Reading from file");
        close(src_fd);
        free(src_cpy);
        return 1;
    }

    


    close(src_fd);
    free(src_cpy);
    return 0;
}

int main (int argc, char *argv[]) {

    //0 Succ, 1 Err
    int run_status = 0;

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

    run_status = interpreter(&source_fd);

    return run_status;
}