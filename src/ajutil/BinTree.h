#ifndef BIN_TREE_
#define BIN_TREE_

typedef struct BinTree btree;

/*
 *
 * WARNING! Do not change the value of key after it has been inserted into the tree
 * Bad things will happen and people will beat you with sticks
 *
 */

// returns a pointer to a new Binary Tree
// d is how you want to destroy the key and data, it is called whenever a node is deleted
struct BinTree *new_BinTree(void(*d)(void*/*key*/, void*/*data*/));

// deletes a binary tree cleanly
void delete_BinTree(struct BinTree*);

// insert a node with key key and data data
// returns 0 upon success and -1 on failure:
// i.e there is already a node that exist with that given key or you ran out of memory
int BinTree_Insert(struct BinTree*, void* /*key*/, unsigned int /*length*/, void* /*data*/);

// returns 0 if nothing is found
// must be passed the data structure you wish to search
void *BinTree_Search(struct BinTree*, void* /*key*/, unsigned int /*length*/);

// executes func in order at every entry in the tree
// passes data as the first argument and info as the second
void BinTree_ExecAll(struct BinTree*, void(*/*func*/)(void*/*data*/,void*/*info*/), void* /*info*/);

// search for a node with key key
// 0 upon success -1 on failure
int BinTree_Delete(struct BinTree*, void* /*key*/, unsigned int /*length*/);

#endif
