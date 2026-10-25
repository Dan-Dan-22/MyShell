#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

struct Comando{
	char *nome;
	int (*funzione)(char **args);
	};

int comando_quit(char **args){
		return 1;
	}
int comando_help(char **args){
		printf("Comandi: cd, help, exit\n");
	}
int comando_cd(char **args){
		char *destinazione = args[1];
		if(destinazione == NULL){
			destinazione = getenv("HOME");
		}
		if(destinazione == NULL){
			fprintf(stderr, "cd: HOME non impostata\n");
		}
		if(chdir(destinazione) == -1){
				perror("cd");
		}
		return 0;
	}

int main(){
	struct Comando comandi[] = {
		{"quit", comando_quit},
		{"help", comando_help},
		{"cd", comando_cd},
	};
	int esci = 0;
	int n_comandi = sizeof(comandi)/sizeof(comandi[0]);
	while(!esci){
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
		int interno = 0;
		for(int k=0; k<n_comandi; k++){
			if(strcmp(args[0], comandi[k].nome) == 0){
				interno = 1;
				if(comandi[k].funzione(args) == 1){
					esci = 1;
				}
				break;
			}
		}
		if(interno){
			continue;
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