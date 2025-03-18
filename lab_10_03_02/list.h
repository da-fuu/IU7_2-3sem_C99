#ifndef LIST_H__
#define LIST_H__


// Структура ноды
typedef struct node
{
    char *key;
    int value;
    struct node *next;
} node_t;

struct assoc_array_type
{
    node_t *head;
};


// Функция освобождения списка
void free_list(node_t *head);

// Функция поиска в списке
node_t *find_list(node_t *head, const char *key);

// Функция удаления ноды из списка
void remove_node(node_t **head, node_t *node);


#endif // LIST_H__
