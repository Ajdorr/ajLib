#ifndef LIST_H
#define LIST_H

typedef struct listStruct list;

// creates a new list and returns a pointer to it
// requires a destructor for the data
// the void * passed to the function is the data
// if it fails it returns NULL
list* new_list(void(*)(void*));

// deletes a list
void delete_list(list*);

// pushes data into the list like a stack
// returns 0 if successful and -1 if it fails
// data must be malloced, it is not copied
int list_Push(list* /*list*/,void* /*data*/);

// pops data off of the list like a stack or a queue
// returns NULL if there is nothing on the stack
void* list_Pop(list */*list*/);

// appends data to the last element of the list
int list_Enqueue(list* /*list*/, void* /*data*/);

// moves the iterator i times
// then returns the data that is at that node
void* list_Iterate(list* /*list*/, unsigned int /*i*/);

// returns the data at the current iterator and removes the entry
// moves the iterator i places after
// if i = 0, it wont move the iterator but the iterator will point to the next entry
void* list_Extract(list* /*list*/);

// inserts data wherever the iterator is and then moves the iterator i times
int list_Insert(list* /*list*/, void* /*data*/);

#endif // LIST_H
