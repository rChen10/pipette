#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

int main(){
  int descriptorsPC[2];
  int descriptorsCP[2];
  int READ = 0;
  int WRITE = 1;

  if (pipe(descriptorsPC)){
    printf("%s\n", strerror(errno));
    exit(1);
  }
  if (pipe(descriptorsCP)){
    printf("%s\n", strerror(errno));
    exit(1);
  }

  int f = fork();

  if (f){
    close(descriptorsPC[READ]);
    close(descriptorsCP[WRITE]);
    int status;

    srandom(getpid());
    int send = random() % 27;
    printf("[parent] sending: %d\n", send);
    write(descriptorsPC[WRITE], &send, sizeof(send));
    wait(&status);
    int recieve = 0;
    read(descriptorsCP[READ], &recieve, sizeof(recieve));
    printf("[parent] received: %d\n", recieve);
    
  }

  else{
    close(descriptorsPC[WRITE]);
    close(descriptorsCP[READ]);

    int num = 0;
    read(descriptorsPC[READ], &num, sizeof(num));
    printf("[child] adding one to: %d\n", num);
    num += 1;
    write(descriptorsCP[WRITE], &num, sizeof(num));
    exit(0);
  }
}
