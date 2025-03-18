#ifndef BINWORK_H__

#define BINWORK_H__

// Заголовочный файл файла для импорта и экспорта бинарных файлов


#include <stdio.h>
#include <inttypes.h>


#define SURNAME_LEN 25
#define NAME_LEN 10
#define MARKS_N 4

// Структура студента
struct student 
{
    char surname[SURNAME_LEN + 1];
    char name[NAME_LEN + 1];
    uint32_t marks[MARKS_N];
};

#define STRUCT_SIZE sizeof(struct student)


// Функция импорта данных из текстового файла в бинарный
// Принимает имя текстового файла и имя бинарного файла
// Возвращает код ошибки
int import_file(char *text_name, char *bin_name);

// Функция экспорта данных из бинарного файла в текстовый
// Принимает имя бинарного файла и имя текстового файла
// Возвращает код ошибки
int export_file(char *bin_name, char *text_name);

// Функция нахождения длины файла в элементах
// В случае ошибки возвращает 0
size_t find_file_len(FILE *file);

// Функция записи данных из бинарного файла в текстовый поток(файл)
// Принимает файловые переменные открытого на чтение бинарного файла,
// открытого на запись текстового файла и длину файла в элементах
void write_file_to_stream(FILE *in_file, FILE *out_file, size_t file_len);


#endif	// #ifndef BINWORK_H__
