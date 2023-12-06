#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

void signal_handler(int signum) {
    printf("Handler for signal %d\n", signum);
    sleep(1);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <number_of_handlers>\n", argv[0]);
        return 1;
    }

    int num_handlers = atoi(argv[1]);

    if (num_handlers <= 0) {
        printf("Invalid number of handlers\n");
        return 1;
    }

    for (int i = 1; i <= num_handlers; i++) {
        if (signal(SIGINT, signal_handler) == SIG_ERR) {
            perror("Failed to register signal handler");
            return 1;
        }
    }

    printf("Registered %d signal handlers. Waiting for signals...\n", num_handlers);

    while (1) {
        // Очікуємо на сигнали
        pause();
    }

    return 0;
}
