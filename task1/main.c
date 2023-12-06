#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Usage: %s <commands>\n", argv[0]);
        return 1;
    }

    char command[1024] = "";
    for (int i = 1; i < argc; i++) {
        strcat(command, argv[i]);
        strcat(command, " ");
    }

    char *token = strtok(command, ";");
    while (token != NULL) {
        int ret_code = system(token);

        printf("Command: %s\nExit code: %d\n", token, ret_code);

        token = strtok(NULL, ";");
    }

    return 0;
}