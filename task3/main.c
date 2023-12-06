#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define DEFAULT_BUFFER_SIZE 127

void printWelcomeMessage(char *username) {
    printf("Welcome, %s!\n", username);
    printf("[%s]$: ", username);
}

void printHelp() {
    printf("C Command Processor\n");
    printf("Available commands:\n");
    printf("1. stop - exit the program\n");
    printf("Available options:\n");
    printf("-h or --help - display this help message\n");
    printf("-b or --buffer <size> - set the command buffer size (default %d)\n", DEFAULT_BUFFER_SIZE);
}

int main(int argc, char *argv[]) {
    char username[256];  // String to store the username
    char inputBuffer[DEFAULT_BUFFER_SIZE];  // Buffer for user commands
    int buffer_size = DEFAULT_BUFFER_SIZE;
    int help_requested = 0;

    // Check command line options
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-h") == 0 || strcmp(argv[i], "--help") == 0) {
            printHelp();
            return 0;
        } else if ((strcmp(argv[i], "-b") == 0 || strcmp(argv[i], "--buffer") == 0) && i + 1 < argc) {
            buffer_size = atoi(argv[i + 1]);
            return 0;
        }
    }

    // Get the username
    printf("Please enter your name: ");
    fgets(username, sizeof(username), stdin);
    username[strcspn(username, "\n")] = '\0';  // Remove the newline character

    // Display welcome message
    printWelcomeMessage(username);

    while (1) {
        // Get user command
        if (fgets(inputBuffer, buffer_size, stdin) == NULL) {
            perror("Error reading command");
            break;
        }

        // Remove newline character from the command
        inputBuffer[strcspn(inputBuffer, "\n")] = '\0';

        // Execute the command
        if (strcmp(inputBuffer, "stop") == 0) {
            break;  // Exit the program
        } else {
            // Execute the command using a system call
            int result = system(inputBuffer);
            if (result != 0) {
                printf("Error executing command\n");
            }
        }

        // Display message and clear the screen
        printf("Exiting...\n");
        sleep(3);
        system("clear");
        printf("[%s]$: ", username);
    }

    return 0;
}

