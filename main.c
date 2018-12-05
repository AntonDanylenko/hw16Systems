#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/shm.h>

int main(){
  key_t key = ftok("/main.c", 'c');
  int shmid = shmget(key, 200, 0777 | IPC_CREAT);
  char *data = shmat(shmid, (void *)0, 0);
  //show contents of shared memory
  if(data){
    printf("Shared contents: %s\n", data);
  }
  else{
    printf("Segment was just created, no contents\n");
  }
  //ask to change contents
  char *response = malloc(10);
  int unanswered = 1;
  while(unanswered){
    printf("Would you like to change the data? ");
    fgets(response, 9, stdin);
    strcpy(response, strsep(&response, "\n"));
    //printf("Response: %s\n", response);
    if(!strcmp(response,"y") || !strcmp(response, "yes")){
      printf("Enter a string: ");
      fgets(data,200,stdin);
      strcpy(data, strsep(&data, "\n"));
      unanswered = 0;
    }
    else if(!strcmp(response,"n") || !strcmp(response, "no")){
      unanswered = 0;
    }
    else{
      printf("Please enter valid response.\n");
    }
  }
  printf("shared contents: %s\n", data);
}
