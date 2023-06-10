#include <stdio.h>
#include <stdlib.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>

/*Brainfuck*/
#define MEM_LEN 3000
/*Terminal*/
#define RED "\x1B[1;31m"
#define RST "\x1B[0m" //Reset text color

typedef enum {
    ERR_NO_INPUT_FILE,
    ERR_FILE_NOT_FOUND, //arg: file
    ERR_COUNT
} ErrorCode;

const char* errorMessage[] = {
    RED"[ERROR] " RST "no input file to read\n",
    RED"[ERROR] " RST "%s: no such file\n",
};