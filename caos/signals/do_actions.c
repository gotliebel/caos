#include <signal.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

volatile sig_atomic_t number = 0;
volatile sig_atomic_t must_exit = 0;

void handle_sigusr1(int signum)
{
    ++number;
    printf("%d\n", number);
    fflush(stdout);
}

void handle_sigusr2(int signum)
{
    number *= -1;
    printf("%d\n", number);
    fflush(stdout);
}

void handle_sig(int signum)
{
    must_exit = 1;
}

int main()
{
    struct sigaction action;
    memset(&action, 0, sizeof(action));
    action.sa_handler = handle_sig;
    action.sa_flags = SA_RESTART;
    sigaction(SIGINT, &action, NULL);

    sigaction(SIGTERM, &action, NULL);

    struct sigaction action_usr1;
    memset(&action_usr1, 0, sizeof(action_usr1));
    action_usr1.sa_handler = handle_sigusr1;
    action_usr1.sa_flags = SA_RESTART;
    sigaction(SIGUSR1, &action_usr1, NULL);

    struct sigaction action_usr2;
    memset(&action_usr2, 0, sizeof(action_usr2));
    action_usr2.sa_handler = handle_sigusr2;
    action_usr2.sa_flags = SA_RESTART;
    sigaction(SIGUSR2, &action_usr2, NULL);

    printf("%d\n", getpid());
    fflush(stdout);

    scanf("%d", &number);

    while (!must_exit) {
        pause();
    }

    return 0;
}