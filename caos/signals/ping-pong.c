#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

volatile sig_atomic_t must_exit = 0;

void handle_sig(int signum, siginfo_t* info, void* context)
{
    if (info->si_int == 0) {
        must_exit = 1;
        exit(0);
    } else {
        sigqueue(info->si_pid, signum, (sigval_t)(info->si_int - 1));
    }
}

int main()
{
    struct sigaction action;
    memset(&action, 0, sizeof(action));
    action.sa_flags = SA_SIGINFO;
    action.sa_sigaction = handle_sig;
    sigfillset(&action.sa_mask);
    sigdelset(&action.sa_mask, SIGRTMIN);
    sigaction(SIGRTMIN, &action, NULL);

    while (!must_exit) {
        pause();
    }

    return 0;
}