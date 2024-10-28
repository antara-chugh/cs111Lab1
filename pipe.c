#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <errno.h>

int main(int argc, char *argv[])
{
	// TODO: it's all yours
  int num_cmds=argc-1;
  
   if(num_cmds==0){
    
    return EINVAL;
  }
   

  int prev_output;
  for(int i=1; i<argc; i++){

    int pipefd[2];
    if(pipe(pipefd)<0){

      return -1;
    }

    if(i<(argc-1)){

      pid_t pid=fork();
      if(pid==0){
	//child process
	if(i>1){

	  dup2(prev_output, 0);
	  close(prev_output);
	}
	dup2(pipefd[1], 1);
	close(pipefd[1]);
	close(pipefd[0]);
	execlp(argv[i], argv[i], (char *)NULL);
	
      }else{
	int status;
	wait(&status);
	if(errno<0){
	  return errno;
	}
	prev_output=pipefd[0];
	close(pipefd[1]);
      }
    }else{
      dup2(prev_output,0);
      close(prev_output);
      execlp(argv[i], argv[i], (char *)NULL); 
      if(errno!=0){
	return errno;
      }


    }

  }
  return 0;
}
  
