#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>

/*Brainfuck*/
#define MEM_LEN 30000
/*Terminal*/
#define RED "\x1B[1;31m"
#define RST "\x1B[0m" //Reset text color

typedef enum ErrorCode {
    ERR_NO_INPUT_FILE,
    ERR_FILE_NOT_FOUND, //arg: file
    ERR_INVALID_INPUT,
    ERR_WRITING_OUT,
    ERR_UNEXP_CHAR,
    ERR_COUNT
} ErrorCode;

const char* errorMessage[] = {
    RED"[ERROR] " RST "no input file to read\n",
    RED"[ERROR] " RST "%s: no such file\n",
    RED"[ERROR] " RST "invalid input entry\n",
    RED"[ERROR] " RST "unexpected failure at writing\n",
    RED"[ERROR] " RST "'%c' (%d): unexpected character in source code\n",
};