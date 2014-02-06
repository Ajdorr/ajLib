#ifndef DLIST_H
#define DLIST_H

// WIP
// TODO make this a double linked dlist!

typedef struct dlistStruct dlist;

// creates a new dlist and returns a pointer to it
// requires a destructor for the data
// the void * passed to the function is the data
// if it fails it returns NULL
dlist* new_dlist(void(*)(void*));

// deletes a dlist
void delete_dlist(dlist*);

// pushes data into the dlist like a stack
// returns 0 if successful and -1 if it fails
// data must be malloced, it is not copied
int dlist_Push(dlist* /*dlist*/,void* /*data*/);

// pops data off of the dlist like a stack or a queue
// returns NULL if there is nothing on the stack
void* dlist_Pop(dlist */*dlist*/);

// appends data to the last element of the dlist
int dlist_Enqueue(dlist* /*dlist*/, void* /*data*/);

// moves the iterator i times
// then returns the data that is at that node
void* dlist_Iterate(dlist* /*dlist*/, unsigned int /*i*/);

// returns the data at the current iterator and removes the entry
// moves the iterator i places after
// if i = 0, it wont move the iterator but the iterator will point to the next entry
void* dlist_Extract(dlist* /*dlist*/);

// inserts data wherever the iterator is and then moves the iterator i times
int dlist_Insert(dlist* /*dlist*/, void* /*data*/);

#endif // LIST_H
