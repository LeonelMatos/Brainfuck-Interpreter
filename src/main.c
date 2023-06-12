#include "brain.h"

void closesrc(int *fd, char *source, int ex_status) {
    close(fd);
    free(source);
    exit(ex_status);
}

void interpreter(int *src_fd) {
    int mem_ptr = 0;
    int src_index = 0;

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
    //Create cpy
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
    ssize_t src_bytesRead = read(src_fd, src_cpy, src_len);
    if (src_bytesRead < 0) {
        perror("Reading from file");
        close(src_fd);
        free(src_cpy);
        return 1;
    }

    for (src_index = 0; src_index < src_len; src_index++) {
        char ch = src_cpy[src_index];

        switch (ch) {
            case '>': /*move right*/
                if (++mem_ptr == MEM_LEN)
                    mem_ptr = 0;
                break;
            case '<': /*move left*/
                if (!(mem_ptr--))
                    mem_ptr = MEM_LEN -1;
                break;
            case '+': /*increment*/
                p_memory[mem_ptr]++;
                break;
            case '-': /*decrement*/
                p_memory[mem_ptr]--;
                break;
            case ',': /*read*/
                ssize_t bytesRead;
                bytesRead = read(STDIN_FILENO, p_memory[mem_ptr], 1);
                if (bytesRead < 0) {
                    perror("Invalid input text");
                    fprintf(stderr, "%s", errorMessage[ERR_INVALID_INPUT]);
                    closesrc(&src_fd, src_cpy, 1);
                }
                break;
            case '.': /*write*/
                ssize_t bytesWrite;
                bytesWrite = write(STDOUT_FILENO, p_memory[mem_ptr], sizeof(p_memory[mem_ptr]));
                if (bytesWrite < 0) {
                    perror("Writing output");
                    fprintf(stderr, "%s", errorMessage[ERR_INVALID_INPUT]);
                    closesrc(&src_fd, src_cpy, 1);
                }
                break;
            case '[': /*begin loop*/
                if (p_memory[mem_ptr] != 0) break;
                short int is_open = 1;
                while (is_open) {
                    if (++src_index == src_len)
                        closesrc(&src_fd, src_cpy, 1);
                    /*to continue*/
                }

        }
    }


    close(src_fd);
    free(src_cpy);
}

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

    interpreter(&source_fd);

    return run_status;
}