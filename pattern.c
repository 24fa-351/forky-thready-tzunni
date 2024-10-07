#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <time.h>

void parallel( int things ) {
  srand(time(NULL)); // seed rng
  pid_t pids[things]; // create an array of pids
  for (int ix = 0; ix < things; ++ix) // loop through our children, calling each begin
  {
    pids[ix] = fork();
    if (pids[ix] == 0)
    {
      printf("Process %d (%d) is beginning\n", ix + 1, getpid());
      sleep(1 + (rand() % 8)); // sleep for 1-8 seconds
      printf("Process %d (%d) is ending\n", ix + 1, getpid());
      exit(EXIT_SUCCESS);
    }
  }
  for (int ix = 0; ix < things; ++ix)
  {
    waitpid(pids[ix], 0, 0);
  }
}

void sequential( int things ) {
  srand(time(NULL)); // seed rng
  pid_t pids[things]; // create an array of pids
  for (int ix = 1; ix <= things; ++ix) // loop through our children, calling each parent and begin
  {
    pids[ix] = fork();
    if (pids[ix] == 0)
    {
      printf("Process %d (%d) creating Process %d (%d)\n", ix - 1, getppid(), ix, getpid());
      printf("Process %d (%d) is beginning\n", ix, getpid());
      sleep(1 + (rand() % 8)); // sleep for 1-8 seconds
    } else {
      waitpid(pids[ix], 0, 0);
      printf("Process %d (%d) is ending\n", ix, pids[ix]); // as our parents wait, call each end
      exit(EXIT_SUCCESS);
    }
  }
}
