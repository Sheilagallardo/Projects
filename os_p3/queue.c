//OS-P3 2022-2023

#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>
#include "queue.h"


//To create a queue
queue* queue_init(int size){ /* size: size of the circular buffer */

	queue * q = (queue *)malloc(sizeof(queue));
	q->items = malloc(sizeof(struct element) * size);
	q -> size = 0;
	q -> capacity = size;
	q -> head = 0;
	q -> tail = 0;

	return q;
}


// To Enqueue an element
int queue_put(queue *q, struct element* x) { /* function that inserts elements in the circular queue*/
	int q_tail = q->tail;
	int q_cap = q->capacity;
	while(queue_full(q)==1){}/* circular buffer is full -> WAIT*/
	(q->items)[q_tail] = *x; /* inserts new element to the end of cicrular buffer bc it's FIFO */
	q->tail = (q_tail+1) % (q_cap);
	(q -> size) ++;
	return 0;
}


// To Dequeue an element.
struct element* queue_get(queue *q) { /*function that extracts elements from the queue (operations) --> returns a structure*/
	int q_head = q->head;
	int q_cap = q->capacity;
	struct element* element = malloc(sizeof(struct element));
	while (queue_empty(q) == 1){}/*circular buffer is empty -> WAIT*/
	*element = (q->items)[q_head]; /* gets first element from circular buffer bc it's FIFO */
	q->head =(q_head+1)% (q_cap);
	q->size--;
	return element;
}


//To check queue state
int queue_empty(queue *q){ /* returns 1 --> queue is EMPTY; 0 --> not empty*/
	if (q-> size == 0){
		return 1;
	}
	return 0;
}

int queue_full(queue *q){ /* returns 1 --> queue is FULL; 0 --> not full */
	if (q->size == q->capacity){
		return 1;
	}
	return 0;
}

//To destroy the queue and free the resources
int queue_destroy(queue *q){ /* frees up ALL spaces from the circular buffer*/
	while(queue_empty== 0){
		free(queue_get(q));
	}
	free(q);
	return 0;
}
