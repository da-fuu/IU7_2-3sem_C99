#ifndef LIST_H__
#define LIST_H__

// Заголовочный файл файла для работы со списком

// Структура данных для студента
typedef struct
{
    char *name;
    int mark;
} student_t;

// Функция освобождения студента
void free_student(student_t *student);

// Функция освобождения списка
void free_list(node_t *head);

// Функция компаратора студентов по оценкам
int compare_marks(const void *student_ptr1, const void *student_ptr2);

// Функция вставки элемента в конец списка
int push_end(node_t **end, void *data);


#endif // #ifndef LIST_H__
