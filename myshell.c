#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

int main(){
	while(1){
		char riga[1024]; 
		char *args[64];
		printf("myshell> ");
		fflush(stdout);
		if(fgets(riga, sizeof(riga), stdin) == NULL){
			break;
		}
		riga[strcspn(riga, "\n")] = '\0';
		char *token = strtok(riga, " ");
		int i=0;
		while(token != NULL && i < 63){
			args[i] = token;
			i++;
			token = strtok(NULL, " ");
		}
		args[i] = NULL;
		if(args[0] == NULL){
			continue;
		}
		if(strcmp(args[0], "quit") == 0){
			break;
		}
		pid_t pid = fork();
		if(pid == 0){
			execvp(args[0], args);
			perror("execvp");
			exit(1);
		}
		int status;
		waitpid(pid, &status, 0);
	}
}