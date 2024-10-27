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
  int pipes [num_cmds-1][2];
  if(num_cmds==0){
    printf("%d", errno);
    return errno;
  }
  if(num_cmds==1){
    pid_t pid=fork();
    if(pid==-1){
      
      return errno;
    }else if(pid==0){
      execlp(argv[1], argv[1], (char *)NULL);
      printf("%d", errno);
      return -1;
    }else{
      waitpid(pid, NULL, 0);
    }
    return 0;
  }

  for(int i=0; i<num_cmds-1; i++){
    if(pipe(pipes[i])!=0){
	
      return errno;
      }


  }

    for(int i=0;i<num_cmds; i++){
      pid_t pid=fork();
      if(pid<0){
	
	return errno;

      }else if(pid==0){
	if(i>0){

	  if(dup2(pipes[i-1][0], STDIN_FILENO)==-1){
	    
	    return errno;
	  }
	  

	}
	if(i<num_cmds-1){
	  if(dup2(pipes[i][1], STDOUT_FILENO)==-1){
	    
	    return errno;
	  }
	}

	for(int j=0; j<num_cmds-1; j++){
	  close(pipes[j][0]);
	  close(pipes[j][1]);

	}

	execlp(argv[i+1], argv[i+1], (char *)NULL);
	printf("%d", errno);
	return -1;


      }
    }

      

      //parent process
      for(int i=0; i<num_cmds-1; i++){

	close(pipes[i][0]);
	close(pipes[i][1]);
      }

      for(int i=0; i<num_cmds; i++){
	if(wait(NULL)==-1){
	  printf("%d", errno);
	  return -1;
	}
	
	
      }

      return 0;

    
    
}

  
