# Тесты для лабораторной работы №1 задание №7

## Входные данные
- Вещественное число x, |x| <= 1
- Вещественное число epsi, 0 < epsi <= 1


## Выходные данные
- Точное значение функции f(x)
- Приближенное значение функции s(x)
- Абсолютная погрешность
- Относительная погрешность

## Позитивные тесты:
- 01 - 0 < x < 1; 0 < epsi < 1
- 02 - x = 1;0 < epsi < 1
- 03 - x = 0;0 < epsi < 1 
- 04 -  0 < x < 1; epsi = 1


## Негативные тесты:
- 01 - Введен текст
- 02 - Ничего не введено
- 03 - x >1
- 04 - x < -1
- 05 - epsi = 0
- 06 - epsi > 1
