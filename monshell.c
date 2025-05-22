#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define MAX_ARGS 64

void execute_command(char *input) {
    char *args[MAX_ARGS];
    int i = 0;

    
    char *token = strtok(input, " ");
    while (token != NULL && i < MAX_ARGS - 1) {
        args[i++] = token;
        token = strtok(NULL, " ");
    }
    args[i] = NULL; 

    
    pid_t pid = fork();
    if (pid == 0) {
        execvp(args[0], args);
        perror("execvp");
        exit(EXIT_FAILURE);
    } else if (pid > 0) {
        wait(NULL);
    } else {
        perror("fork");
    }
}

int main() {
    

	printf("   ___    ____   \n");
	printf("  / _ \\  | ___| \n");
	printf(" | | | | |___ \\ \n");
	printf(" | |_| |  ___) | \n");
	printf("  \\___/  |____/ \n");
                
    
    char line[1024];                                                 
    while (1) {
        char cwd[1024];
        if (getcwd(cwd, sizeof(cwd))) {
           printf("☠️ minishell@%s ☠️ > ",cwd);
        }
        if (!fgets(line, sizeof(line), stdin)) break;

        line[strcspn(line, "\n")] = '\0';  

        if (strcmp(line, "exit") == 0) {
            break;
        } else if (strcmp(line, "pwd") == 0) {
            char cwd[1024];
            if (getcwd(cwd, sizeof(cwd))) {
                printf("%s\n", cwd);
            } else {
                perror("getcwd");
            }
        } else if (strncmp(line, "cd ", 3) == 0) {
            if (chdir(line + 3) != 0) {
                perror("chdir");
            }
        } else {
            execute_command(line);
        }
    }

    return 0;
}
