/****************************************************************/
/* This file provides the funtions used for deal with the queue */
/****************************************************************/

#include "queue.h"

Queue queue;
/*data queue constructor*/
Queue::Queue()
{
    arr[0]=0;
    head=0;
    tail=0;
}
/*get data from queue*/
unsigned char Queue::getData(void)
{
    unsigned char data;
    data = arr[head];
    head++;
    if(head >= QUEUE_SIZE) head=0;
    return data;
}
/*put data to queue*/
void Queue::putData(unsigned char ch)
{
    arr[tail] = ch;
    tail++;
    if(tail >= QUEUE_SIZE) tail=0;
}
/*check the queue empty or not*/
unsigned char Queue::emptyCheck(void)
{
    if( head == tail )
        return 1;
    else
        return 0;
}
/*check the queue full or not*/
unsigned char Queue::fullCheck(void)
{
    if( tail + 1 == head )
        return 1;
    else
        return 0;
}

