#ifndef BIN_TREE_
#define BIN_TREE_

typedef struct bTree btree;

/*
 */

// returns a pointer to a new Binary Tree
// d is how you want to destroy the data, it is
// called whenever a node is deleted
struct bTree *new_bTree(void(*d)(void*/*data*/));

// deletes a binary tree cleanly
void delete_bTree(struct bTree*);

// insert a node with key key and data data
// the key is copied into the data structure
// returns 0 upon success and -1 on failure:
// i.e there is already a node that exist with
// that given key or you ran out of memory
int bTree_Insert(struct bTree*, const void* /*key*/,
                 unsigned int /*length*/, void* /*data*/);

// returns 0 if nothing is found
// must be passed the data structure you wish to search
void *bTree_Search(struct bTree*, const void* /*key*/, unsigned int /*length*/);

// executes func in order at every entry in the tree
// passes data as the first argument and info as the second
void bTree_ExecAll(struct bTree*,
                   void(*/*func*/)(void*/*data*/,void*/*info*/), void* /*info*/);

// search for a node with key key
// 0 upon success -1 on failure
int bTree_Delete(struct bTree*, void* /*key*/, unsigned int /*length*/);

// deletes all nodes in the tree
void bTree_DeleteAll(struct bTree*);

// search for a node with key key
// removes the node, but returns the data
void* bTree_Extract(struct bTree*, void* /*key*/, unsigned int /*length*/);

#ifdef __cplusplus
// binary tree class for c++
class BTree
{
private:
    btree* tree;

public:
    BTree(void(*dest)(void*)){ tree = new_bTree(dest);}
    ~BTree(){delete_bTree(tree); tree = 0;}

    int insert(const void* k, unsigned int l, void* d){ return bTree_Insert(tree, k, l, d);}
    void* search(void* k, unsigned int l){return bTree_Search(tree, k, l);}
    void execAll(void(*f)(void*,void*), void* inf){bTree_ExecAll(tree, f, inf);}
    int remove(void* k, unsigned int l){return bTree_Delete(tree, k, l);}
    void removeAll() { bTree_DeleteAll(tree);}

};

#endif

#endif
