//P1-SSOO-22/23

#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

#define N 1  //Buffer size

int main(int argc, char *argv[])
{
    int fd;
    int n;
    //We initialize the variables to 0
    int bytes = 0;
    int lines = 0;
    int words = 0;
    char buffer[N];

	//If less than two arguments (argv[0] -> program, argv[1] -> file to process) print an error y return -1
	if(argc < 2)
	{
		printf("Too few arguments\n");
		return -1;
	}
	
	//To open the file
	fd = open(argv[1], O_RDONLY);
	//Check if there is an error opening the file
	if (fd < 0) {
	    printf("Error opening the file");
	    return -1;
	}
	
	//Loop to count the number of ' ' and '\t' which gives us the number of words and '\n' to get the number lines. 
    while (n=read(fd, buffer, N)>0) { //If it is grater than 0 it means that it is reading the file -->  no error
    //It stores in buffer[0] the current caracter being read.
        if (buffer[0]==' ' & bytes>1) { //If the buffer contains ' ' it has read a word
            words++;  //add one word
        }
        
        if (buffer[0]=='\t' & bytes>1){  //If the buffer contains '\t' it has read a word
            words++;  //add one word
        }
        
        if (buffer[0]=='\n' & bytes>1){  //If the buffer contains '\n' it has read a word and a line
            lines++;  //add one line
            words++;  //add one word
        }
        
        bytes++;  //adds one byte for every character read in each iteration
    }

    if (bytes > 0){
        if ((buffer[0] !=' ') & (buffer[0] !='\t') & (buffer[0] !='\n')){
            words++;  //adds one word for the last word of last line if it does not have a ' ', '\n' or '\t' at the end
        }  
    }
 
    //n would be 0 when the file could be read and it has finished.
    
    //To check if there was an error reading --> When n is negative
    if (n<0){
        printf("Read error ocurred");
        return -1;
    }else{
        //If everything is okay, it prints the results, returns 0 and finishes the program
        printf("%d %d %d %s\n", lines, words, bytes, argv[1]);
        close(fd);
        return 0;
    }
    
}
