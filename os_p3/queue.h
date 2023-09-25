#ifndef HEADER_FILE
#define HEADER_FILE


struct element {	/* Elements inside the circular buffer are of type struct */
	int operation_num;	/* The order of the operation */
	char operation_name[20];	/* Operation name */
	int account_ID1;
	int account_ID2;	/* In case we have a TRANSFER operation, we have two IDs */
	int money;	/* Amount of money for the operation */
};

typedef struct queue {	/* We define the circular buffer as a structure */
	int size;	/* actual size of the circular buffer */
	int capacity;	/* max. capacity */
	struct element *items;	/* stores address of elements from the circular buffer */
	int head;	/* index of first element from the buffer */
	int tail;	/* index of last element from the buffer */


}queue;

queue* queue_init (int size);
int queue_destroy (queue *q);
int queue_put (queue *q, struct element* elem);
struct element * queue_get(queue *q);
int queue_empty (queue *q);
int queue_full(queue *q);

#endif
