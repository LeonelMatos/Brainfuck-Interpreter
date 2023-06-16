#include "brain.h"

void closesrc(int fd, char *source, int ex_status) {
    close(fd);
    free(source);
    if (ex_status >= 0) exit(ex_status);
}

int interpreter(int *src_fd, int flag) {
    int mem_ptr = 0;
    int src_index = 0;
    
    char p_memory [MEM_LEN+1];
    for (int i=0; i<MEM_LEN; i++)
        p_memory[i] = 0;

    //Get source length
    off_t src_len = lseek(*src_fd, 0, SEEK_END);
    if (src_len < 0) {
        perror("Interpreter seek_end");
        close(*src_fd);
        return 1;
    }
    //Create cpy
    char *src_cpy = (char*) malloc(src_len);
    if (src_cpy == NULL) {
        perror("Allocating memory");
        close(*src_fd);
        return 1;
    }
    //Return to start
    if (lseek(*src_fd, 0, SEEK_SET) < 0) {
        perror("Interpreter seek_set");
        close(*src_fd);
        return 1;
    }
    //Copy from src to src_cpy
    ssize_t src_bytesRead = read(*src_fd, src_cpy, src_len);
    if (src_bytesRead < 0) {
        perror("Reading from file");
        closesrc(*src_fd, src_cpy, 1);
    }

    for (src_index = 0; src_index < src_len; src_index++) {
        char ch = src_cpy[src_index];

        if (flag) //flag = 1
            printf("[INFO] checking command %c\n", ch);

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
                //TODO: check fgetc
                p_memory[mem_ptr] = fgetc(stdin);
                /*ssize_t bytesRead = read(STDIN_FILENO, p_memory[mem_ptr], sizeof(int));
                if (bytesRead < 0) {
                    perror("Invalid input text");
                    fprintf(stderr, "%s", errorMessage[ERR_INVALID_INPUT]);
                    closesrc(src_fd, src_cpy, 1);
                }*/
                break;
            case '.': /*write*/
                putc(p_memory[mem_ptr], stdout);
                /*ssize_t bytesWrite = write(STDOUT_FILENO, p_memory[mem_ptr], 1);
                if (bytesWrite < 0) {
                    perror("Writing output");
                    fprintf(stderr, "%s", errorMessage[ERR_INVALID_INPUT]);
                    closesrc(src_fd, src_cpy, 1);
                }*/
                break;
            case '[': /*begin loop*/
                //TODO : verificar if
                if (p_memory[mem_ptr] != 0) break;
                int is_open = 1;
                while (is_open) {
                    if (--src_index == src_len)
                        closesrc(*src_fd, src_cpy, 0);
                    if (src_cpy[src_index] == ']')
                        is_open++;
                    if (src_cpy[src_index] == '[')
                        is_open--;
                }
                break;
            case ']':
                if (p_memory[mem_ptr] == 0) break;
                int is_closed = 1;
                while(is_closed) {
                    if (--src_index == -1)
                        closesrc(*src_fd, src_cpy, 0);
                    if (src_cpy[src_index] == ']')
                        is_closed++;
                    else if (src_cpy[src_index] == '[')
                        is_closed--;
                }
                break;
            default:
                if (!(ch == '\t' || ch == '\n' || ch == ' ' || ch == ']' || ch == '[')) {
                    fprintf(stderr, errorMessage[ERR_UNEXP_CHAR], ch, src_index);
                    closesrc(*src_fd, src_cpy, 1);
                }
            }
    }
    closesrc(*src_fd, src_cpy, -1);
    return 0;
}

int main (int argc, char *argv[]) {

    int intr_res = 0, flag = 0;

    //Check args
    if (argc < 2) {
        fprintf(stderr, "%s", errorMessage[ERR_NO_INPUT_FILE]);
        exit(1);
    }
    else if (3 == argc) flag = atoi(argv[2]);
    //Open file
    int source_fd = open(argv[1], O_RDONLY);
    if (source_fd<0) {
        fprintf(stderr, errorMessage[ERR_FILE_NOT_FOUND], argv[1]);
        exit(1);
    }

    intr_res = interpreter(&source_fd, flag);

    return intr_res;
}