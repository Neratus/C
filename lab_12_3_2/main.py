import ctypes
import os

if not os.path.exists('./libarr.so'):
    raise FileNotFoundError(f"Library ./libarr.so not found!")

lib = ctypes.CDLL('./libarr.so')

lib.fill_prime.argtypes = [ctypes.POINTER(ctypes.c_int), ctypes.c_size_t]
lib.fill_prime.restype = None

lib.cnt_nums_for_add_oddargtypes = [ctypes.POINTER(ctypes.c_int), ctypes.c_size_t]
lib.cnt_nums_for_add_odd.restype = ctypes.c_int

lib.add_odd_nums.argtypes = [
    ctypes.POINTER(ctypes.c_int), ctypes.c_size_t,
    ctypes.POINTER(ctypes.c_int), ctypes.c_size_t,
    ctypes.POINTER(ctypes.c_size_t), ctypes.c_int
]
lib.add_odd_nums.restype = ctypes.c_int

option = int(input("Введите требуемую операцию: заполнение массива простыми числами(1) или копирование(2): "))
if option != 1 and option!=2:
    raise ValueError(f"Опция {option} невалидна!")
    
if (option == 1):
    size = int(input("Введите размер массива: "))
    if (size <= 0):
        raise ValueError("Размер должен быть больше нуля!")

    arr = (ctypes.c_int * size)()
    lib.fill_prime(arr, size)

    print("Заполненный простыми числами массив:", [arr[i] for i in range(len(arr))])

else:
    mem_option = int(input("Введите тип выделения памяти: c запасом(1) или точный размер(2): "))
    if mem_option != 1 and mem_option!=2:
        raise ValueError(f"Опция {mem_option} невалидна!")

    print("Введите элементы массива через пробел: ")
    my_list = [int(el) for el in input().split()]

    num_to_add = int(input("Введите число для добавления: "))

    arr_size = len(my_list)
    arr = (ctypes.c_int * arr_size)(*my_list)

    if (mem_option == 1):
        buf_size = arr_size * 2
        dest_arr = (ctypes.c_int * buf_size)()
    else:
        buf_size = lib.cnt_nums_for_add_odd(arr, arr_size)
        dest_arr = (ctypes.c_int * buf_size)()

    dest_size = ctypes.c_size_t()
    result = lib.add_odd_nums(arr, arr_size, dest_arr, buf_size, ctypes.byref(dest_size), num_to_add)
    if result == 0:
        print("Новый массив:", [dest_arr[i] for i in range(dest_size.value)])
    else:
        print("Ошибка при добавлении чисел.")

    

