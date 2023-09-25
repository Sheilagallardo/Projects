//P1-SSOO-22/23

#include <stdio.h>		// Header file for system call printf
#include <unistd.h>		// Header file for system call gtcwd
#include <sys/types.h>	// Header file for system calls opendir, readdir y closedir
#include <dirent.h>
#include <string.h>
#include <limits.h>     //To be able to use PATH_MAX

int main(int argc, char *argv[])
{
	char *dirname;  //Name of the directory we want to access
	DIR *dir;  //DIR --> data type for the directory. dir --> directory descriptor
	char buffer[PATH_MAX];  //PATH_MAX --> a constant that specifies the maximun size that the directory path can have
	struct dirent *read;  //Struct dirent --> to access the content of the directory


	if(argc < 2)  //The name of the directory is not an argument so we take the current directory
    {
    	dirname = getcwd(buffer, PATH_MAX);  //To get the name of the directory to list from the current directory
		dir = opendir(dirname);  //To open the directory which name is saved at dirname

    }else{
		//The name of the directory is specified and so passed as an argument
		dirname = argv[1]; // Takes the name of the directory passed by argument to dirname
		dir = opendir(dirname);  //To open the directory which name is saved at dirname

	}

	//Check if the directory can be open (returns -1 in case of error)
	if (dir == NULL){
		printf("Error opening the directory\n");
		return -1;
	}else{


	// If no error opening the directory --> it reads each of the directory contents 
	while (read = readdir(dir)){
		printf("%s\n", read->d_name);  //Gets the name of the entries inside the read structure and prints it
	}

	closedir(dir);  //Close the directory descriptor after being use
	}
	return 0;  // returns 0 if everything has worked well and finish the program
}

