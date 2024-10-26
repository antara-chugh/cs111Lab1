#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char *argv[])
{
	// TODO: it's all yours
  int num_cmds=argc-1;
  int pipes [num_cmds-1][2];
  if(num_cmds==1){
    pid_t pid=fork();
    if(pid==-1){
      perror("fork");
      exit(1);
    }else if(pid==0){
      execlp(argv[1], argv[1], (char *)NULL);
      perror("execlp");
      exit(1);
    }else{
      waitpid(pid, NULL, 0);
    }
    return 0;
  }

  for(int i=0; i<num_cmds-1; i++){
    if(pipe(pipes[i])==-1){
	perror("pipe");
	exit(1);
      }


  }

    for(int i=0;i<num_cmds; i++){
      pid_t pid=fork();
      if(pid==-1){
	perror("fork");
	exit(1);

      }else if(pid==0){
	if(i>0){

	  if(dup2(pipes[i-1][0], STDIN_FILENO)==-1){
	    perror("dup2");
	    exit(1);
	  }

	}
	if(i<num_cmds-1){
	  if(dup2(pipes[i][1], STDOUT_FILENO)==-1){
	    perror("dup2");
	    exit(1);
	  }
	}

	for(int j=0; j<num_cmds-1; j++){
	  close(pipes[j][0]);
	  close(pipes[j][1]);
	}

	execlp(argv[i+1], argv[i+1], (char *)NULL);
	perror("execlp");
	exit(1);


      }
    }

      

      //parent process
      for(int i=0; i<num_cmds-1; i++){

	close(pipes[i][0]);
	close(pipes[i][1]);
      }

      for(int i=0; i<num_cmds; i++){
	wait(NULL);
	
      }

      return 0;

    
    
}

  
