//P2-SSOO-22/23

// MSH main file
// Write your msh source code here

//#include "parser.h"
#include <stddef.h>			/* NULL */
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>
#include <time.h>
#include <pthread.h>
#include <errno.h> /* To control the errors */

#define MAX_COMMANDS 8


// files in case of redirection
char filev[3][64];

//to store the execvp second parameter
char *argv_execvp[8];

 /* argvv is a matrix: each row is the command followed by its arguments; first element of the row is the command, and next columns are its arguments; each time we arrive to a pipe ('|') we jump to next row*/


void siginthandler(int param)
{
	printf("****  Exiting MSH **** \n");
	//signal(SIGINT, siginthandler);
	exit(0);
}


/* Timer */
pthread_t timer_thread;
unsigned long  mytime = 0;

void* timer_run ( )
{
	while (1)
	{
		usleep(1000);
		mytime++;
	}
}

/**
 * Get the command with its parameters for execvp
 * Execute this instruction before run an execvp to obtain the complete command
 * @param argvv
 * @param num_command 	
 * @return
 */
/* num_command tells to which command we want to access */

void getCompleteCommand(char*** argvv, int num_command) {
	//reset first
	for(int j = 0; j < 8; j++)
		argv_execvp[j] = NULL; /* erase the contents of argv_execvp to store new parameters corresponding to another command */

	int i = 0;
	for ( i = 0; argvv[num_command][i] != NULL; i++) /* stores command and corresponding parameters we want to execute in argv_execvp */
		argv_execvp[i] = argvv[num_command][i];  /* the num_command tells the row ( which command we want to access) and [i] are the columns we want to store (parameters) corresponding to this command*/
}
/* Function to write message in the file */
int write_err(int fd, char *message){
	if (write(fd,message, strlen(message)) < 0){
		return -1;
	}else{
		return 0;
	}
}


/**
 * Main sheell  Loop  
 */
int main(int argc, char* argv[]) {

	/**** Do not delete this code.****/
	int end = 0; 
	int executed_cmd_lines = -1;
	char *cmd_line = NULL;
	char *cmd_lines[10];

	/* We define the Acc environment variable: name of the variable, initial value and 1 to specify we want to overwrite this global variable*/
	if (setenv("Acc", "0", 1) <0){
		perror("Cannot define the environment variable\n");
	}

	if (!isatty(STDIN_FILENO)) {
		cmd_line = (char*)malloc(100);
		while (scanf(" %[^\n]", cmd_line) != EOF){
			if(strlen(cmd_line) <= 0) return 0;
			cmd_lines[end] = (char*)malloc(strlen(cmd_line)+1);
			strcpy(cmd_lines[end], cmd_line);
			end++;
			fflush (stdin);
			fflush(stdout);
		}
	}

	pthread_create(&timer_thread,NULL,timer_run, NULL);

	/*********************************/

	char ***argvv = NULL;
	int num_commands;
	int fd_pipe[2];


	while (1) { /* Inserts new command*/
		int status = 0;
		int command_counter = 0;
		int in_background = 0;
		signal(SIGINT, siginthandler);

		// Prompt 
		write(STDERR_FILENO, "MSH>>", strlen("MSH>>"));

		// Get command
		//********** DO NOT MODIFY THIS PART. IT DISTINGUISH BETWEEN NORMAL/CORRECTION MODE***************
		executed_cmd_lines++;
		if( end != 0 && executed_cmd_lines < end) {
			command_counter = read_command_correction(&argvv, filev, &in_background, cmd_lines[executed_cmd_lines]); 
		} /* command_counter = number of commands entered by the user --> number of rows in our matrix argvv */
		else if( end != 0 && executed_cmd_lines == end) {
			return 0;
		}
		else {
			command_counter = read_command(&argvv, filev, &in_background); //NORMAL MODE
		}
	
		//************************************************************************************************


		/************************ STUDENTS CODE ********************************/
		if (command_counter > 0) {
			if (command_counter > MAX_COMMANDS){
				printf("Error: Maximum number of commands is %d \n", MAX_COMMANDS);
			} else {
				
				// Print command
				//print_command(argvv, filev, in_background);

				for (int i = 0; i<command_counter; i++){
					getCompleteCommand(argvv, i);
					
					if (strcmp(argv_execvp[0],"mycalc") == 0){
						if ((argv_execvp[1]!= NULL) && (argv_execvp[2]!= NULL) && (argv_execvp[3] != NULL)){
							int operand1 = atoi(argv_execvp[1]);
							int operand2 = atoi(argv_execvp[3]);
							char *operation = argv_execvp[2];
							char buffer[200] = ""; /* buffer to store the formatted string */ 

							/* check syntax of command */
							if((argv_execvp[1] != "0") && (operand1 == 0)){
								write_err(STDOUT_FILENO, "[ ERROR ] The structure of the command is mycalc < operand_1 > <add / mul / div > < operand_2 >\n");
								return -1;
							}else if((argv_execvp[3] != "0") && (operand2 == 0)){
								write_err(STDOUT_FILENO,"[ ERROR ] The structure of the command is mycalc < operand_1 > <add / mul / div > < operand_2 >\n");
								return -1;
							}else if((strcmp("add", operation)!= 0) && (strcmp("mul", operation)!= 0) &&(strcmp("div", operation)!= 0)){
								write_err(STDOUT_FILENO,"[ ERROR ] The structure of the command is mycalc < operand_1 > <add / mul / div > < operand_2 >\n");
								return -1;
							} else if (argv_execvp[4] != NULL){
								write_err(STDOUT_FILENO,"[ ERROR ] The structure of the command is mycalc < operand_1 > <add / mul / div > < operand_2 >\n"); /* Errors will be shown in the terminal by the standard output */
								return -1;
							} else if(strcmp("add", operation) == 0){
								int result = operand1 + operand2;
								int acc = atoi(getenv("Acc")); /* Convert the value stored in the global variable (chararcter) to an integer */
								acc = acc + result; /* Update accumulated result */
								snprintf(buffer, sizeof(buffer), "%d", acc); /* Converts the integer acc into a string and stores it in the buffer */
								if(setenv("Acc", buffer, 1)<0){ /* Assigning the value stored in the buffer to the environment variable */
									write_err(STDOUT_FILENO,"Error setting the environment value\n");
									return -1;
								}
								snprintf(buffer, sizeof(buffer), "[OK] %d + %d = %d; Acc %d\n", operand1, operand2, result, acc);
								if(write_err(STDERR_FILENO, buffer) < 0){; /* Outputs will be shown in the terminal by the standard error output*/
									return -1;
								}
							}else if(strcmp("mul", operation) == 0){
								int result = operand1*operand2;
								snprintf(buffer, sizeof(buffer), "[OK] %d * %d = %d \n", operand1, operand2, result);
								if(write_err(STDERR_FILENO, buffer)<0){;
									return -1;
								}
							}else if(strcmp("div", operation) == 0){
								int result = operand1/operand2;
								int remainder = operand1%operand2; /* remainder */
								snprintf(buffer, sizeof(buffer), "[OK] %d / %d = %d; Remainder %d \n", operand1, operand2, result, remainder);
								if(write_err(STDERR_FILENO, buffer)<0){;
									return -1;
								}
							}
						} else{ /* In case the user enters less arguments than the expected */
							if(write_err(STDOUT_FILENO, "[ ERROR ] The structure of the command is mycalc < operand_1 > <add / mul / div > < operand_2 >\n")<0){
								return -1;
							}
						}
					} else if(strcmp(argv_execvp[0], "mytime")== 0){
						/* Checking that the syntax is correct */ 
						if (argv_execvp[1] == NULL){
							char buffer1[200]; /* Create another to store the time as a string */
							int hours, minutes, seconds;
							int time_shell = mytime/1000;
							hours = (time_shell/360); 
							minutes = (time_shell%360) / 60;
							seconds = (time_shell%360)%60;
							snprintf(buffer1, sizeof(buffer1), "%02d:%02d:%02d\n", hours, minutes, seconds); /* We print the time in the format asked, and used %02 to pad with zeros in case the number is of less than two digits*/
							if(write_err(STDERR_FILENO, buffer1)<0){
								return -1;
							}							
						}else{
							if(write_err(STDOUT_FILENO, "[ ERROR ] The structure of the command is mytime \n")<0){ /* Errors will be shown in the terminal by the standard output */
								return -1;
							}
						}

					} else{ /* Execute internal commands */

					/* Create the fd´s associated to the pipes. */
						int fd_pipe[2];
						/* Store the output of the previous command in previous_output */
						int previous_output;
 						/* Create a pipe so that this command's output can be read as the input for the next command if necessary. */
						if( i != (num_commands -1)){
							if (pipe(fd_pipe) < 0){
								perror("Error creating the pipe");
								return -1;
							}
						}

						/* Parent process (the terminal) invokes a fork to create a child which will execute the command entered by the user*/
						int pid_child;
						pid_child = fork();

						if(pid_child == -1){
							perror("Error in fork");
							return -1;
						}

						else if (pid_child == 0){ /* CHILD PROCESS */						

							if (i == 0){ /* The input redirection (<) only affects the first command (first element of our matrix)*/
						
								if(strcmp(filev[0], "0") != 0 ){/* There´s REDIRECTION FOR THE INPUT, receives input data from a file */
									int fd_in = dup(STDIN_FILENO); /* Store original input file descriptor in order to restore it after */
									if (close(STDIN_FILENO) <0){ /* So that it doesn´t receive the input from the keyboard*/
										perror("Error closing STDIN");
										return -1;
									}
								
									if (open(filev[0], O_RDONLY) < 0){ /* Opens file with name given at the first row of filev[] and with read permissions only */
										perror("Error opening the file for STDIN");
										return -1;
									}
								}
								/* Process input now comes from the given file */
							}else {
								if (close (0) < 0){
									perror("Error closing the STDIN");
									return -1;
								}
								if(dup2(previous_output, 0) <0) { /* Interchange the standard input for next command with the output of previous command.*/
									perror("Error dup the input for next command");
									return -1;
								}
							}
							


							if (i == command_counter -1){  /*The output redirection (>) only redirects the last command ( first element of last row of our matrix)*/
						
								if(strcmp(filev[1], "0") != 0 ){/* There´s REDIRECTION FOR THE OUTPUT (sends data to the output file instead to the terminal)*/
									int fd_out = dup(STDOUT_FILENO); /* Store original output file descriptor in order to restore it after */
									if(close(STDOUT_FILENO) < 0){ /* So that it doesn´t send data to the terminal but to the output file*/
										perror("Error closing STDOUT");
										return -1;
									}

									if(open(filev[1], O_CREAT|O_WRONLY, 0666)<0){ /* creats file with name given at the second row of filev[] and with read and write permissions */
										perror("Error opening the file for STDOUT");
										return -1;
									}
								}
								/* Process output now goes to the given file */
							} else{
								if (close (1) < 0){
									perror("Error closing the STDOUT");
									return -1;
								}
								if(dup2(fd_pipe[1], 1) <0) { /* Interchange the standard output of command by the actual output contained in the pipe.*/
									perror("Error dup the output of the command");
									return -1;
								} 
							}

							if(strcmp(filev[2], "0") != 0 ){ /* There´s REDIRECTION FOR THE ERROR */
								int fd_err = dup(STDERR_FILENO); /* Store original error file descriptor in order to restore it after */
								if (close(STDERR_FILENO)<0){
									perror("Error closing STDERR");
									return -1;
								}

								if (open(filev[2], O_CREAT|O_WRONLY, 0666)<0){
									perror("Error opening the file for STDERR");
									return -1;
								} 
							}
							/* Standard error now refers to the given file */
						
							execvp( argv_execvp[0], argv_execvp);
							perror("Error in exec"); /* if the execution is correct this will never be executed*/
							return -1;
			
						} else { 	/* PARENT PROCESS */
							if(in_background==0){ 
								if(wait(&status) == -1){
									perror("Error waiting for the child");
									return -1;
								}
							}else if ((in_background==1) && (i== num_commands -1)){
								printf("The PID from the command executed in background: %d\n", pid_child);
							}
								
							if (close(fd_pipe[1])<0){
								perror("Error closing the write end of the current pipe");
								return -1;
							}

							if ( i != 0){
								if(close(previous_output) < 0){
									perror("Error closing the previous output");
									return -1;
								}
							}
							/* Assigns next command´s input with the previous command´s output */
							previous_output = fd_pipe[0];
						}
					}
				}
			}
		}
	}

	return 0;
}