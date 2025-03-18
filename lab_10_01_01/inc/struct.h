#ifndef STRUCT_H__
#define STRUCT_H__

// Структура ноды

typedef struct node node_t;

struct node
{
    void *data;
    node_t *next;
};


#endif // #ifndef STRUCT_H__
