//P1-SSOO-22/23

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#define Perm 0644  //Here we define the permissions of the output file --> User: rw-, Group: r--, Other: r-- 

#define N 1

int main(int argc, char *argv[])
{
    /* If less than two arguments (argv[0] -> program, argv[1] -> file to save environment) print an error y return -1 */
    if(argc < 3)
    {
    	printf("Too few arguments\n");
    	return -1;
    }

    char env[30];  
    int fd, out, n, i;
    char buffer[N];
    char vect[30];  //Create a string to store the variables (before the '=') that we are going to read from env.txt
    //We have assigned a value of 30 as maximun size because there is no variable in env.txt greater than this size

    //This loop is to assign the variable passed as an argument to the constant size string env
    for (i=0; i<30; i++){
        env[i] = *(argv[1]+i);
    }

    // open the env.txt file
    fd = open("env.txt", O_RDONLY);

    //Checks if there is any error opening the file by checking if the fd value is negative (Returns -1 in case of error)
    if (fd < 0) {
	    printf("Error opening the file\n");
	    return -1;
	}

    //Creates the output file or if there is already a file with that name it truncates the file (overwrites)
    out = creat(argv[2], Perm); //Recives the output file name (argv[2]) and the permissions defined above (Perm)

    //Checks if there is any error creating the file by checking if the out value is negative (Returns -1 in case of error)
    if (out < 0) {
	    printf("Error creating the file\n");
        close(fd);
	    return -1;
	}


    i = 0;  //counter to store characters we are reading from buffer to vect
    //This loop reads all the env.txt file. While n (number of bytes read) is greater than 0 which means that it is reading something
    while (n=read(fd, buffer, N)>0) {  //fd: input file. buffer: where we want to copy the contents. N: number of bytes we want to read.
        
        //To store all characters before the '=' into vect
        if (buffer[0] != '='){
            vect[i] = buffer[0];
            i++;
        }else{
            // It has arrived to the '=' so we have already the variable of the each line in vect
            if (strcmp(vect, env) == 0){ // Compares the string stored in vect with the one we have passed as an argument (env). If they are the same --> copy the whole line into the output file
                //Checks if there is an error writing into the file (Returns -1 in case of error). If there is no error it writes the content of vect into the output file
                if(write(out, vect, i) < i){  //out: output file. vect: from where do we want to copy. i: number of bytes we want to copy.
                    printf("Error writing the file\n");
                    close(fd);
                    close(out);
                    return -1;
                }else{
                    //If there is no error it writes the '=' stored in the buffer
                    if (write(out, buffer, N)<N){
                        printf("Error writing the file\n");
                        close(fd);
                        close(out);
                    return -1;
                    }else{
                        //If there is no error this loop reads the rest of the line
                        while (n=read(fd, buffer, N)>0){
                            if (buffer[0]=='\n'){  //When we find '\n' we write it into the file
                                if (write(out, buffer, N)<N){
                                    printf("Error writing the file\n");
                                    close(fd);
                                    close(out);
                                }
                                i = 0;  //To restart the counter
                                memset(vect, 0, 30);  //To emppty all possitions of vect.
                                break;  //Starts again the first while to do the same with the next lines
                            }else{
                                //If everything is okay it writes the rest of that line
                                if(write(out, buffer, N) < N){
                                    printf("Error writing the file\n");
                                    close(fd);
                                    close(out);
                                    return -1;
                                }
                            }
                        }
                    }
                }


            }else{  //If the string in vect is different from the one passed as an argument (env) then it reads the rest of the line until it finds '\n'
                while (n=read(fd, buffer, N)>0){
                    if (buffer[0]=='\n'){
                        i=0;  //To restart the counter
                        memset(vect, 0, 30);  //To emppty all possitions of vect.
                        break;  //Starts again the first while to do the same with the next lines
                    }
                }
            }

        }
    }
    close(fd);
    close(out);
    
    return 0;  //If everything work correctly it returns 0 and finishes the program
}
