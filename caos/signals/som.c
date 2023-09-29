#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

volatile sig_atomic_t must_exit = 0;


void handle_sig(int signum, siginfo_t *info, void* context)
{
  //si_sigval
  if (info->si_int == -3) {
    must_exit = 1;
    printf("wtf");
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
  //sigfillset(&action.sa_mask);
  //sigdelset(&action.sa_mask, SIGRTMIN);
  sigaction(SIGRTMIN, &action, NULL);
  printf("%d\n", getpid());
  sigqueue(2556907, SIGRTMIN, (sigval_t)(6));
  printf("som");
  while (!must_exit) {
    pause();
  }

  return 0;
}