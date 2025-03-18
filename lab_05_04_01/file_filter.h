#ifndef FILEFILTER_H__

#define FILEFILTER_H__

// Заголовочный файл файла для фильтрации файла в другой файл по заданию


// Функция фильтрации студентов по фамилии
// Принимает имя входного файла, имя выходного файла и подстроку для фильтрации
// Возвращает код ошибки
int filter_file(char *file_name_in, char *file_name_out, char *name_substr);


#endif	// #ifndef FILEFILTER_H__
