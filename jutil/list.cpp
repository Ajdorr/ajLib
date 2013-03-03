#include <stdlib.h>
#include "list.h"

struct ln {
    void *data;

    struct ln* n;
};

typedef struct listStruct {
    struct ln *head, *tail, **it;
    void (*dest)(void*);
} list;


list* new_list(void (*d)(void*)) {
    list* fng = malloc(sizeof(list));

    if (fng) {
        fng->head = NULL;
        fng->tail = NULL;
        fng->dest = d;
        fng->it = &(fng->head);
    }
    return fng;
}

void delete_list(list* vic) {
    if (vic == NULL)
        return;
    else if (vic->head == NULL);
    else {
        struct ln *v;
        for (v = vic->head->n; v != NULL; v=v->n) {
            vic->dest(vic->head->data);
            free(vic->head);
            vic->head = v;
        }
        vic->dest(vic->head->data);
        free(vic->head);
    }
    free(vic);
}

int list_Push(list *L, void *d){
    struct ln* fng = malloc(sizeof(struct ln));
    if (fng == NULL) {
        return -1;
    }

    fng->data = d;
    fng->n = L->head;
    L->head = fng;
    if (L->tail == NULL) {
        L->tail = fng;
    }

    return 0;
}

void *list_Pop(list *L) {
    struct ln *vic;
    void *d;

    if (L->head == NULL) {
        return NULL;
    }

    vic = L->head;
    L->head = vic->n;
    d = vic->data;

    if ( &(vic->n) == L->it) {
        L->it = &(L->head);
    }
    free(vic);

    return d;
}

int list_Enqueue(list *L, void *d) {
    struct ln *fng = malloc(sizeof(struct ln));
    if (fng == NULL) {
        return -1;
    }
    fng->n = NULL;
    fng->data = d;
    if (L->head == NULL) {
        L->head = fng;
        L->tail = fng;
    }
    else if (L->tail != NULL) {
        L->tail->n = fng;
        L->tail = fng;
    }
    else {
        free(fng);
        return -2;
    }

    return 0;

}

void *list_Iterate(list* L, unsigned int i) {
    void* ret;
    if (L->head == NULL) {
        return NULL;
    }
    while (i > 0) {
        L->it = &((*(L->it))->n);
        if (*(L->it) == NULL) {
            L->it = &(L->head);
        }
        i--;
    }
    ret = (*(L->it))->data;
    return ret;
}

void *list_Extract(list* L) {
    struct ln *vic;
    void* ret;
    if (L->head == NULL) {
        return NULL;
    }

    vic = *(L->it);
    ret = vic->data;
    *(L->it) = vic->n;

    if (*(L->it) == NULL) {
        L->it = &(L->head);
    }
    free(vic);

    return ret;
}

int list_Insert(list* L, void* d) {
    struct ln *fng = malloc(sizeof(struct ln));
    if (fng == NULL) {
        return -1;
    }

    fng->data = d;
    fng->n = *(L->it);
    *(L->it) = fng;

    return 0;
}
