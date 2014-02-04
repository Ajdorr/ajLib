#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bTree.h"


struct btn {
    void *key;
    void *data;

    unsigned int klen;

    struct btn *l,*r;
};

typedef struct bTree {
    struct btn* head;

    void(*dest)(void*, void*);
} btree;

// create a new node
struct btn* new_btn(void *k, unsigned int len, void* d) {
    struct btn *p;
    p = (struct btn*)malloc(sizeof(struct btn));

    if (p == NULL) {
        return(p);
    }
	
    p->key = k;
    p->klen = len;
    p->data = d;
    p->l = NULL;
    p->r = NULL;

    return p;
}

// recursively delete an entry
void delete_btn(struct btn *n, void(*del)(void*,void*)) {
    if (n == NULL) {
        return;
    }

    del(n->key, n->data);
    free(n);
}

struct bTree *new_bTree(void(*d)(void*, void*)) {
    struct bTree *p = (struct bTree*)malloc(sizeof(struct bTree));

    p->head = NULL;
    p->dest = d;

    return(p);
}

void btn_deleteSub(struct btn *n, void(*d)(void*,void*)) {
    if (n == NULL) {
        return;
    }

    btn_deleteSub(n->l, d);
    btn_deleteSub(n->r, d);
    delete_btn(n, d);

    return;
}

void delete_bTree(struct bTree* tree) {
    if (tree == NULL) {
        return;
    }
    btn_deleteSub(tree->head, tree->dest);

    free(tree);
}

// search through the tree and return the node, or the pointer to where it should go
struct btn **btnSearch(struct btn **s, void *k, unsigned int len) {
    int t;
    unsigned int l;

    while ((*s) != NULL) {
        if (len == (*s)->klen) {
            t = memcmp(k, (*s)->key, len);
            if (t == 0) {
                return s;
            }
            if (t > 0) {
                s = &((*s)->r);
            }
            else {
                s = &((*s)->l);
            }
        }
        else {
            l = (len < (*s)->klen) ? len : (*s)->klen; // get the minimum
            t = memcmp(k, (*s)->key, l);
            if ( t > 0) {
                s = &((*s)->r);
            }
            else {
                s = &((*s)->l);
            }
        }
    }

    // in the case that this points to the null pointer
    return s;
}

int bTree_Insert(struct bTree* tree, void *key, unsigned int l, void *data) {
    struct btn **n;

    n = btnSearch(&(tree->head), key, l);

    if (*n == NULL) {
        *n = new_btn(key, l, data);
        if ( *n != NULL) {
            return 0;
        }
    }
    return(-1);
}

// search through tree for a node with key
void *bTree_Search(struct bTree *tree, void *key, unsigned int len) {
    struct btn **n;

    n = btnSearch(&(tree->head), key, len);
	
    if (*n == NULL) {
        return(NULL);
	}
	else {
		return((*n)->data);
	}
}


struct btn **btn_GetRightMost(struct btn **vic) {
    if (*vic == NULL) {
        return vic;
    }

    while ((*vic)->r != NULL) {
        vic = &((*vic)->r);
    }
    return vic;
}

int bTree_Delete(struct bTree* tree, void *key, unsigned int l)  {
    struct btn **vic, **fix, *rep;

    vic = btnSearch(&(tree->head), key, l);

    // can't find what you're looking for
    if (*vic == NULL) {
		return(-1);
	}

    if ((*vic)->l == NULL) {
        rep = (*vic)->r;
        delete_btn(*vic, tree->dest);
        *vic  = rep;
    }
    else {
        fix = btn_GetRightMost(&((*vic)->l));

        rep = *fix;
        *fix = rep->l;

        rep->l = (*vic)->l;
        rep->r = (*vic)->r;
        delete_btn(*vic, tree->dest);
        *vic  = rep;
    }


	return(0);
}

void btn_ExecAll(struct btn *n, void(*f)(void*,void*), void *info) {
    if (n == NULL) {
        return;
    }

    btn_ExecAll(n->l, f, info);
    f(n->data, info);
    btn_ExecAll(n->r, f, info);

    return;
}

void bTree_ExecAll(struct bTree *t, void(*f)(void*,void*), void* info) {
    btn_ExecAll(t->head, f, info);
}


