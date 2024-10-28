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
   /*
  if(num_cmds==1){
    pid_t pid=fork();
    if(pid<0){
      
      return errno;
    }else if(pid==0){
      execlp(argv[1], argv[1], (char *)NULL);
      
      return errno;
    }else{
      waitpid(pid, NULL, 0);
    }
    return 0;
  }
  */

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
/*
  
    for(int i=0;i<num_cmds; i++){
     pid_t pid= fork();
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
	printf("bogus argument shouldn't pass");
	exit(1);
	
	return errno;


      }
      else{

	int status;
	wait(&status);
	if(WIFEXITED(status)){
	  return -1;
	}
	if(i>0){
	close(pipes[i-1][0]);
	close(pipes[i-1][1]);
	}


      }
    }
    return 0;
      

      //parent process
    /* for(int i=0; i<num_cmds-1; i++){

	close(pipes[i][0]);
	close(pipes[i][1]);
      }

      for(int i=0; i<num_cmds; i++){
	int status;
	wait(&status);
	if(WIFEXITED(status)){
	  return -1;
	}
	
	
      }

      printf("ran");
      return 0;
    
    
    
}
*/
  
