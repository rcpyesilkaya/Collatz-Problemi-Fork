#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {

    if (argc == 1) {
        fprintf(stderr,"Usage: ./a.out <starting value>\n");
        return EXIT_FAILURE;
    }

    int j;
    printf ("How many times would you like this to run?\n");
    scanf ("%d", &j);
    (void) fpurge(stdin);

    printf("\nMain program's process ID: %d\n", getpid());

    int n = atoi(argv[1]);

    for (int x = 1; x <= j; x++) {
        pid_t pid = fork();

        if (pid == -1) {
            fprintf(stderr, "Unable to fork child\n");
            return EXIT_FAILURE;
        } else if (pid == 0) { /* child process */
            pid_t child_pid = getpid();

            printf("\nChild %d (ID: %d)\n", x, child_pid);
            printf("\nStart sequence at: %d\n", n);
            while (n != 1) {
                n = n % 2 ? 3 * n + 1 : n / 2;
                printf("\n(Child %d) %d ", x, n);
            }

            printf("\n\nAbout to end execution (I'm process %d).\n", child_pid);

            return EXIT_SUCCESS; /* child terminates */
        }
        else { /* parent process */
            n = n + 3;
        }
    }

    for (int x = 1; x <= j; x++) {
        wait(NULL);
    }

    return EXIT_SUCCESS;
}