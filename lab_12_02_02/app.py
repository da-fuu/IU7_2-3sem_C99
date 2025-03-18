import ctypes
import tkinter as tk
import tkinter.ttk as ttk

# Класс для использования библиотеки на Си
class ArrayLib:
    #  Инициализация
    def __init__(self, dll: ctypes.CDLL):                    
        self._fill_fib = dll.fill_fib
        self._fill_fib.argtypes = (ctypes.POINTER(ctypes.c_int), ctypes.c_size_t)
        self._fill_fib.restype = ctypes.c_int
        
        self._copy_uniq_elems = dll.copy_uniq_elems
        self._copy_uniq_elems.argtypes = (ctypes.POINTER(ctypes.c_int), ctypes.c_size_t, ctypes.POINTER(ctypes.c_int), ctypes.POINTER(ctypes.c_size_t))
        self._copy_uniq_elems.restype = ctypes.c_int
        
    # Обертка для функции fill_fib
    def fill_fib(self, array_len: int) -> list[int]:
        if array_len < 0:
            raise ValueError
        if array_len == 0:
            return []
        c_arr = (ctypes.c_int * array_len)()
        self._fill_fib(c_arr, array_len)
        return list(c_arr)

    # Обертка для функции copy_uniq_elems
    def copy_uniq_elems(self, list_in: list[int], *, double_calling: bool) -> list[int]:
        len_in = len(list_in)
        if len_in == 0:
            return []
        c_arr_in = (ctypes.c_int * len_in)(*list_in)
        c_out_len = ctypes.c_size_t()
        if double_calling:
            self._copy_uniq_elems(c_arr_in, len_in, None, ctypes.byref(c_out_len))
            len_out = c_out_len.value
        else:
            len_out = len_in
        c_arr_out = (ctypes.c_int * len_out)()
            
        self._copy_uniq_elems(c_arr_in, len_in, c_arr_out, ctypes.byref(c_out_len))
        
        len_out = c_out_len.value
        list_out = []
        for i in range(len_out):
            list_out.append(c_arr_out[i])
        return list_out
            
            
# Класс для работы с tkinter
class Application:
    # Функция инициализации окна
    def __init__(self, window: tk.Tk, lib: ArrayLib):
        self.root = window
        self.root.title('Приложение, использующее динамическую библиотеку на языке Си')
        self.root.geometry('825x415+300+150')
        self.root.resizable(False, False)
        
        self.lib = lib

        params = {'padx': 5, 'pady': 5, 'sticky': 'nsew'}

        fib_frame = ttk.LabelFrame(self.root, text="Заполнение массива числами Фибоначчи")
        fib_frame.pack(padx=10, pady=10, fill=tk.X)
    
        len_label = ttk.Label(fib_frame, text="Длина массива:")
        len_label.grid(row=0, column=0, **params)
        
        self.len_entry = ttk.Entry(fib_frame)
        self.len_entry.grid(row=0, column=1, **params)
    
        fib_button = ttk.Button(fib_frame, text="Заполнить", command=self.fill_fibonacci)
        fib_button.grid(row=1, column=1, **params)

        fib_out_label = ttk.Label(fib_frame, text="Выходной массив:")
        fib_out_label.grid(row=2, column=0, **params)
    
        self.fib_out_arr_label = ttk.Label(fib_frame, width=62)
        self.fib_out_arr_label.grid(row=2, column=1, columnspan=100, **params)
    
        copy_uniq_frame = ttk.LabelFrame(self.root, text="Скопировать уникальные элемента из одного массива в другой")
        copy_uniq_frame.pack(padx=10, pady=10, fill=tk.X)

        copy_uniq_in_label = ttk.Label(copy_uniq_frame, text="Исходный массив (через пробел):")
        copy_uniq_in_label.grid(row=0, column=0, **params)
        self.copy_uniq_in_entry = ttk.Entry(copy_uniq_frame)
        self.copy_uniq_in_entry.grid(row=0, column=1, columnspan=2, **params)
    
        copy_uniq_memory_label = ttk.Label(copy_uniq_frame, text="Метод выделения памяти:")
        copy_uniq_memory_label.grid(row=1, column=0, rowspan=2, **params)
    
        self.method_var = tk.IntVar(value=1)
        method_1_radiobutton = ttk.Radiobutton(copy_uniq_frame, text="Выделение массива максимально возможного размера", variable=self.method_var, value=1)
        method_1_radiobutton.grid(row=1, column=1, **params)
        method_2_radiobutton = ttk.Radiobutton(copy_uniq_frame, text="Двойной вызов функции", variable=self.method_var, value=2)
        method_2_radiobutton.grid(row=2, column=1, **params)
    
        copy_uniq_button = ttk.Button(copy_uniq_frame, text="Скопировать", command=self.copy_uniq)
        copy_uniq_button.grid(row=3, column=1, **params)

        copy_uniq_out_label = ttk.Label(copy_uniq_frame, text="Выходной массив:")
        copy_uniq_out_label.grid(row=4, column=0, **params)
    
        self.copy_uniq_out_arr_label = ttk.Label(copy_uniq_frame)
        self.copy_uniq_out_arr_label.grid(row=4, column=1, **params)
    
    # Функция вызываемая при нажатии на кнопку заполнения массива
    def fill_fibonacci(self):
        try:
            length = int(self.len_entry.get())
        except ValueError:
            self.fib_out_arr_label['text'] = 'Ошибка: Введите целое положительное число!'
            return 
        try:
            array = self.lib.fill_fib(length)
        except ValueError:
            self.fib_out_arr_label['text'] = 'Ошибка: Введите положительное число!'
            return
        self.fib_out_arr_label['text'] = str(array)

    # Функция вызываемая при нажатии на кнопку копирования уникальных элементов
    def copy_uniq(self):
        array: list[int] = []
        array_elems = self.copy_uniq_in_entry.get().split()
        for elem in array_elems:
            try:
                elem = int(elem)
            except ValueError:
                self.copy_uniq_out_arr_label['text'] = 'Ошибка: Введите массив целых чисел!'
                return
            array.append(elem)

        double_calling = self.method_var == 2
        array = self.lib.copy_uniq_elems(array, double_calling=double_calling)
        self.copy_uniq_out_arr_label['text'] = str(array)
        
    # Запуск основного цикла окна
    def run(self):
        self.root.mainloop()


# Основная функция программы
def main():
    try:
        dll = ctypes.CDLL('./out/libarray.so')
    except OSError as exc:
        print('Ошибка загрузки библиотеки', exc.args[0].split()[0][:-1])
        exit(1)
    
    lib = ArrayLib(dll)
    
    window = tk.Tk()
    gui = Application(window, lib)
    gui.run()

if __name__ == '__main__':
    main()
