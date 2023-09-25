//OS-P3 2022-2023

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <stddef.h>
#include <sys/stat.h>
#include <pthread.h>
#include "queue.h"
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <math.h>

#define buff_size 1



/**
 * Entry point
 * @param argc
 * @param argv
 * @return
 */
/* GLOBAL VARIABLES */
int client_numop;
int bank_numop;
int global_balance;
int *account_balance;
struct element *list_client_ops; /* array of elements of type struct element */
pthread_mutex_t mut_buffer; /* MUTEX TO CONTROL THE BUFFER*/
// pthread_mutex_t mut_global; /* MUTEX TO CONTROL THE GLOBAL BALANCE */ 
void* ATM_function(void* args_atm);
void* worker_function(void* args_worker);



int main (int argc, const char * argv[] ) {
    if (argc > 6){
        perror("Too many arguments");
        return -1;
    }
    int max_accounts = atoi(argv[4]); /* We get the max. number of accounts from the input command */
    account_balance = malloc(max_accounts * sizeof(int)); /* Allocate memory for the number of accounts given */  
    if (account_balance == NULL){ //check that malloc works well
        perror("malloc was unsuccessfull");
        return -1;
    }
    memset(account_balance, -1, max_accounts * sizeof(int)); // To inicialize the account_balance to 0
    global_balance = 0;

    char buffer[buff_size];
    char num[5]; /* store the max. no. of operations as a character */
    int i = 0;
    int fd, n; 
    fd = open(argv[1], O_RDONLY); //open the file with the operations

    if(fd < 0){ // check if there is any error
        perror("Error opening the file");
        return -1;
    }
    
    while(buffer[0] !='\n'){ /* we want to read the first no. from the file which corresponds to the max. number of operations */
        if(n = read(fd, buffer, buff_size)>0){
            num[i] = buffer[0]; /* We store the number of operations in num vector */
            i++; /* We store the number of operations in num vector */
        }
    }
    if (n<0){  //check if there is any error reading the first line of the file
        perror("Error reading the file");
        close(fd);
        return -1;
    }

    num[-1]='\0'; /* to let know it's a string of characters*/
    int max_operations = atoi(num); /* transform the character into the actual integer corresponding to the max. number of operations */
    if (max_operations > 200){
        perror("Error: number of operations out of range");
        return -1;
    }
    char vect[20];  // array to store each word of the file
    char x[20]; 
    int j = 0; /* to keep track of the operators in the main operation*/
    int k =0; // auxiliar variable to help us to store the buffer content in vect
    list_client_ops = malloc(max_operations * sizeof(struct element));  //asing space to the operation vector
    if (list_client_ops == NULL){ //check that malloc works well
        perror("Error in malloc");
        return -1;
    }

    memset(buffer, ' ', 1); //reset the buffer to ' '

    for(int i = 0; i<max_operations; i++){ // since each line is an operation this loop is to keep track of it
    struct element* op = malloc(sizeof(struct element)); /* store operations from file */
    j = 0; //variable to keep track of each element of the line
        while(((n = read(fd, buffer, buff_size))>0)&&(buffer[0] != '\n')){ //loop to read each line
            if(buffer[0] != ' '){ // if we find any space the word has ended
                vect[k] = buffer[0]; /* we store each word/number in the vector vect*/
                k++;

            }else{
                vect[k] = '\0'; /* to know it's a string of characters */
                if (j == 0){  // if its the first word of a line it is the operation name
                    strcpy(op->operation_name, vect); //store it in the structure
                }
                if (j == 1){ // if it is the second word, it is the first account ID
                    op->account_ID1 = atoi(vect); //store it in the structure
                }
                if (j==2){ //if it is the third word we dont know if it is the second ID or the money -> store it in an auxiliar variable and check it later
                    strcpy(x, vect);
                }

                j++; 
                memset(vect, ' ', 20);
                k = 0;
            }
        }
        if (n==0){
            perror("Error: few operations than expected");
            close(fd);
            return -1;
        }
        // do the same that when we find ' ' but with '\n' 
        vect[-1] = '\0'; /* to know it's a string of characters */
        if (j == 1){
            op->account_ID1 = atoi(vect);
        }
        if (j == 2){
            op->money = atof(vect);
        }
        if (j == 3){
            op->money= atof(vect); 
            op->account_ID2 = atoi(x);                   
        }
        memset(vect, ' ', 20);
        k = 0;
        op->operation_num = i; // take the operation ID from the for loop
        list_client_ops[i] = *op; // stoere the structure in the corresponding position of the vector list_client_ops
        memset(op, 0, sizeof(struct element)); // reset the structure element to 0
    }

    n=read(fd, buffer, buff_size);
    if (n<0){
        perror("Error reading the file");
        close(fd);
        return -1;
    }
    if (n>0){
        perror("Error: more operations than expected");
        close(fd);
        return -1;
        }

    close(fd);
    int num_workers = atoi(argv[3]); 
    int num_ATMs = atoi(argv[2]); 
    if (num_workers < 0){
        perror("Error: invalid number of workers");
        return -1;
    }
    if (num_ATMs < 0){
        perror("Error: invalid number of ATMs");
        return -1;
    }
    pthread_t workers_threads[num_workers]; // to create the same number of ATMs threads as the one given as an argument
    pthread_t ATM_threads[num_ATMs]; // to create the same number of workers threads as the one given as an argument
    // initialice global variables to 0
    client_numop = 0;
    bank_numop = 0;
    // create the circular buffer with the queue structure and initialice it with the given capacity
    queue *circular_buffer;
    int capacity = atoi(argv[5]);
    circular_buffer = queue_init(capacity);


    /* INITIALIZING THE MUTEX */
    if (pthread_mutex_init(&mut_buffer, NULL) <0){
        perror("Error initializing the mutex");
    }

     /* CREATING WORKER AND ATMs THREADS */

    void* args_worker[3] = {circular_buffer, &max_operations, &max_accounts}; // arguments that the workers threads receive

    for(int j=0; j < num_workers; j++){ /* Create a thread for each worker */
       pthread_create(&workers_threads[j], NULL, worker_function, (void*)args_worker); 
    }

    void* args_atm[3] = {circular_buffer, list_client_ops, &max_operations}; //arguments that the ATMs threads receive

    for(int l=0; l < num_ATMs; l++){ /* Create a thread for each ATM */
        pthread_create(&ATM_threads[l], NULL, ATM_function, (void*)args_atm);
    }

    for(int j=0; j < num_workers; j++){ /* joining threads for each worker */
       pthread_join(workers_threads[j], NULL); 
    }
    for(int l=0; l < num_ATMs; l++){ /* joining threads for each ATM */
        pthread_join(ATM_threads[l], NULL);
    }
    if (queue_destroy(circular_buffer) != 0){
        perror("Error destroying the circular buffer");
        return -1;
    }
    pthread_mutex_destroy(&mut_buffer);
    return 0;
}


/* ATM_funtion: obtains operations from the array list_client_ops one by one, increment the number of
customer operations (client numop), and insert the operation into the circular queue.*/

void* ATM_function(void* args_atm){
    // obtain the arguments given to the thread
    queue *circular_buffer = ((queue**)args_atm)[0];
    struct element *list_client_ops = ((struct element**)args_atm)[1];
    int *max_op = ((int**)args_atm)[2];

    while(client_numop<(*max_op)){ // The ATMs stop working when they have stored in the circular buffer all the operations
        pthread_mutex_lock(&mut_buffer); // control a critical section (circular_buffer and global variables)
        if(queue_full(circular_buffer)==0){ // the circular buffer is not full
            if (client_numop == list_client_ops[client_numop].operation_num){ // this condition allows the ATMs to store the operations in order
                queue_put(circular_buffer, &list_client_ops[client_numop]); //store the corresponding operation in the buffer
                client_numop++; //move to the next operation
            }
        }
        pthread_mutex_unlock(&mut_buffer);
    }
    pthread_exit(0);
}


void* worker_function(void* args_worker){
    // obtain the arguments given to the thread
    queue *circular_buffer = ((queue**)args_worker)[0];
    int *max_op = ((int**)args_worker)[1];
    int *max_acc = ((int**)args_worker)[2];

    while(bank_numop<(*max_op)){  // the workers stop when they have performed all the operations
        pthread_mutex_lock(&mut_buffer); // control a critical section (circular_buffer and global variables)
        if(queue_empty(circular_buffer) == 0){ /* Circular buffer is not empty */
        struct element* element_buffer = queue_get(circular_buffer); // get the corresponding operation from the buffer
            if (bank_numop == element_buffer->operation_num){ // check that the oreder is correct
                if(strcmp((element_buffer -> operation_name), "CREATE")== 0){
                    if(element_buffer -> account_ID1 > *max_acc){
                        perror("Error: exceeded the maximun number of accounts");
                    }else if(account_balance[element_buffer->account_ID1 - 1] == -1){
                        account_balance[(element_buffer -> account_ID1) -1] = 0;
                        printf("%d CREATE %d BALANCE=%d TOTAL=%d\n", (element_buffer-> operation_num) + 1, element_buffer->account_ID1, account_balance[(element_buffer -> account_ID1) -1], global_balance);
                    }else{
                        perror("Error: Account already created");
                    }
                }
                if(strcmp((element_buffer -> operation_name), "DEPOSIT")== 0){
                    if((account_balance[(element_buffer -> account_ID1) -1] == -1)||(element_buffer -> account_ID1 > *max_acc)){
                        perror("Error: Account hasn't been created yet");
                    }else{
                        account_balance[(element_buffer -> account_ID1) -1] += element_buffer -> money;
                        global_balance += element_buffer -> money;
                        printf("%d DEPOSIT %d %d BALANCE=%d TOTAL=%d\n", (element_buffer-> operation_num) + 1, element_buffer->account_ID1,  element_buffer->money, account_balance[(element_buffer -> account_ID1) -1], global_balance);
                    }
                }
                if(strcmp((element_buffer -> operation_name), "WITHDRAW")== 0){
                    if((account_balance[(element_buffer -> account_ID1) -1] == -1)||(element_buffer -> account_ID1 > *max_acc)){
                        perror("Error: Account hasn't been created yet");
                    // }else if(account_balance[(element_buffer -> account_ID1) -1] < element_buffer -> money){
                    //     perror("Error: not enough money in the Account");
                    }else{
                        account_balance[(element_buffer -> account_ID1) -1] -= element_buffer -> money;
                        global_balance -= element_buffer -> money;
                        printf("%d WITHDRAW %d %d BALANCE=%d TOTAL=%d\n", (element_buffer-> operation_num) + 1, element_buffer->account_ID1,  element_buffer->money, account_balance[(element_buffer -> account_ID1) -1], global_balance);
                    }
                }
                if(strcmp((element_buffer -> operation_name), "BALANCE")== 0){
                    if((account_balance[(element_buffer -> account_ID1) -1] == -1)||(element_buffer -> account_ID1 > *max_acc)){
                        perror("Error: Account hasn't been created yet");
                    }else{
                        printf("%d BALANCE %d BALANCE=%d TOTAL=%d\n", (element_buffer-> operation_num) + 1, element_buffer->account_ID1, account_balance[(element_buffer -> account_ID1) -1], global_balance);
                    }   
                }
                if(strcmp((element_buffer -> operation_name), "TRANSFER")== 0){
                    if((account_balance[(element_buffer -> account_ID1) -1] == -1)||(element_buffer -> account_ID1 > *max_acc)){
                        perror("Error: Account1 hasn't been created yet");
                    }else if(account_balance[(element_buffer -> account_ID2) -1] == -1){
                        perror("Error: Account2 hasn't been created yet");
                    }//else if(account_balance[(element_buffer -> account_ID1) -1] < element_buffer -> money){
                    //     perror("Error: not enough money in Account1");
                    // }
                    else{
                        account_balance[(element_buffer -> account_ID1) -1] -= element_buffer -> money;
                        account_balance[(element_buffer -> account_ID2) -1] += element_buffer -> money;
                        printf("%d TRANSFER %d %d %d BALANCE=%d TOTAL=%d\n", (element_buffer-> operation_num) + 1, element_buffer->account_ID1, element_buffer->account_ID2, element_buffer->money, account_balance[(element_buffer -> account_ID2) -1], global_balance);
                    }
                }
                bank_numop++; //move to the next operation
            }
        }
        pthread_mutex_unlock(&mut_buffer);
    }
    pthread_exit(0);
}


/* Bank (main thread): responsible for creating the ATMs and worker threads */
/* ATM (N: no. of producers (of ATMs)):  functions executed by the threads responsible for reading the operations from the file and add them to the circular buffer*/
/* workers (M: no. of consumers (of workers)): function executed by the threads responsible for extracting the operations from the circular buffer*/
/* Circular buffer: stores the operations the clients want to perform */
/* Create 3 global variables: 
-client_numop --> initialized to zero, incremented each time a customer performs an operation from a ATM (THE ORDER OF THE OPERATION)
-bank_numop --> initialized to zero, incremeted each time a worker performs an operation taken from the circular queue
-global_balance (GLOBAL BANK BALANCE) --> initialized to zero, updated with the operations that are performed (can be +ve or -ve) 
- account_balance[i](for each account) --> i: account ID and index of the account_balance vector */
/*PRODUCER THREAD:*/
/* Load list of operations from the file into memory, in an array list_client_ops */
/* Obtain operations from list_client_ops one by one --> increment the client_numop each time AND insert the operation in the circular queue together with the current client_numop */
/*CONSUMER THREAD:*/
/* increment the bank operation no. (bank_numop) AND extract the operation from the circular queue with that no. */
/* For each extracted element, perform the corresponding operation */
/*ONLY ONE OPERATION PER LINE*/
/* Each line from the file: operation type followed by the account no. on which to perform that operation*/
/* Every time the bank (a worker) performs an operation --> increment the bank operation counter (bank_numop)*/
/* CONCURRENCY : Mutex and condition variables */
