#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

FILE* files[100];
volatile sig_atomic_t must_exit = 0;
volatile sig_atomic_t flag = 0;

void handle_sigmin(int signum)
{
    must_exit = 1;
}

void handle_sig(int signum)
{
    flag = signum;

}

int main(int argc, char* argv[])
{
    struct sigaction action_min;
    memset(&action_min, 0, sizeof(action_min));
    action_min.sa_handler = handle_sigmin;
    action_min.sa_flags = SA_RESTART;
    sigaction(SIGRTMIN, &action_min, NULL);

    struct sigaction action;
    memset(&action, 0, sizeof(action));
    action.sa_handler = handle_sig;
    action.sa_flags = SA_RESTART;
    for (int i = SIGRTMIN + 1; i <= SIGRTMAX; i++) {
        sigaction(i, &action, NULL);
    }
    for (int i = 1; i < argc; i++) {
        files[i] = fopen(argv[i], "r");
    }
    while (!must_exit) {
      if (flag != 0) {
        int number_file = flag - SIGRTMIN;
        char* line = NULL;
        size_t len = 0;
        if (getline(&line, &len, files[number_file]) != -1) {
          printf("%s", line);
          fflush(stdout);
          free(line);
        }
        flag = 0;
      }
        pause();
    }

    for (int i = 1; i < argc; i++) {
        fclose(files[i]);
    }

    return 0;
}
