#ifndef HASHTAB_H
#define HASHTAB_H

#include <stdio.h>
#include <stdlib.h>

#include "number571/tree.h"

// Структура для хэш-таблицы
typedef struct HashTab {
    struct {
        vtype_tree_t key;   // Тип ключа
        vtype_tree_t value; // Тип значения
    } type;
    size_t size;   // Размер таблицы
    Tree **table;  // Массив деревьев (для разрешения коллизий)
} HashTab;

// Функции для работы с хэш-таблицей

// Создание новой хэш-таблицы
extern HashTab *new_hashtab(size_t size, vtype_tree_t key, vtype_tree_t value);

// Освобождение памяти хэш-таблицы
extern void free_hashtab(HashTab *hashtab);

// Получение значения по ключу
extern value_tree_t get_hashtab(HashTab *hashtab, void *key);

// Установка значения по ключу
extern void set_hashtab(HashTab *hashtab, void *key, void *value);

// Удаление элемента по ключу
extern void del_hashtab(HashTab *hashtab, void *key);

// Проверка наличия ключа в хэш-таблице
extern _Bool in_hashtab(HashTab *hashtab, void *key);

// Печать содержимого хэш-таблицы
extern void print_hashtab(HashTab *hashtab);

// Внутренняя функция для хэширования строк
static uint32_t _strhash(uint8_t *s, size_t size);

#endif // HASHTAB_H