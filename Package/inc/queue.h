#ifndef QUEUE_H
#define QUEUE_H

#define QUEUE_SIZE 256

class Queue
{
public:
    Queue();
    int head,tail;
    unsigned char arr[QUEUE_SIZE];
public:
    unsigned char getData(void);
    void putData(unsigned char ch);
    unsigned char  emptyCheck(void);
    unsigned char  fullCheck(void);
private:
};

extern Queue queue;
 
#endif 
