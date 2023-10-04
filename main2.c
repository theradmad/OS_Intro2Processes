#include <stdio.h>
#include <sys/types.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <time.h>
#include  <string.h>

#define   MAX_COUNT  200
#define   BUF_SIZE   100

void  ChildProcess(void);                /* child process prototype  */
void  ParentProcess(void);               /* parent process prototype */
pid_t pid1, pid2;
void  main(void)
{
  
  pid1 = fork();
    if (pid1 == 0) {
      ChildProcess();
    }
    else if (pid1 > 0){
    	pid2 = fork();
      if (pid2 == 0){
          ChildProcess();
        }
        else if (pid2 < 0) {
          perror("Error forking the second child");
          exit(EXIT_FAILURE);
        }
      ParentProcess();
    }
  else {
    perror("Error forking the first child");
    exit(EXIT_FAILURE);
  }

}

void  ChildProcess(void)
{
    int iter = rand() % 30 + 1;
    int i;
    char   buf[BUF_SIZE];

    for (i = 0; i < iter; i++) {
        sprintf(buf, "Child Pid: %d is going to sleep!\n", getpid());
        write(1, buf, strlen(buf));
        int sleep_time = rand() % 10 + 1;
        sleep(sleep_time);
        sprintf(buf, "Child Pid: %d is awake! \nWhere is my Parent: %d?\n", getpid(), getppid());
        write(1, buf, strlen(buf));

    }
}
void ParentProcess(void)
{
    int status1, status2;
    char buf[BUF_SIZE];

    waitpid(pid1, &status1, 0);
    sprintf(buf, "Child Pid: %d has completed\n", pid1);
    write(1, buf, strlen(buf));

    waitpid(pid2, &status2, 0);
    sprintf(buf, "Child Pid: %d has completed\n", pid2);
    write(1, buf, strlen(buf));
}

