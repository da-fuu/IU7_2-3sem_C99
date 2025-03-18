#ifndef STRUCT_H__
#define STRUCT_H__

// Структуры списка

typedef struct data
{
    int row;
    int col;
    int val;
} data_t;

typedef struct node
{
    data_t data;
    struct node *next;
} node_t;


#endif // #ifndef STRUCT_H__
