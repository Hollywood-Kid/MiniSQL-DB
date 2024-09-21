#include "hashtab.h"

// Создание новой хэш-таблицы
extern HashTab *new_hashtab(size_t size, vtype_tree_t key, vtype_tree_t value) {
    // Проверка типа ключа
    switch (key) {
        case DECIMAL_ELEM:
        case STRING_ELEM:
            break;
        default:
            fprintf(stderr, "Тип ключа не поддерживается\n");
            return NULL;
    }

    // Проверка типа значения
    switch (value) {
        case DECIMAL_ELEM:
        case REAL_ELEM:
        case STRING_ELEM:
            break;
        default:
            fprintf(stderr, "Тип значения не поддерживается\n");
            return NULL;
    }

    // Выделение памяти для хэш-таблицы
    HashTab *hashtab = (HashTab *)malloc(sizeof(HashTab));
    hashtab->table = (Tree **)malloc(size * sizeof(Tree *));
    for (size_t i = 0; i < size; ++i) {
        hashtab->table[i] = new_tree(key, value);
    }
    hashtab->size = size;
    hashtab->type.key = key;
    hashtab->type.value = value;
    return hashtab;
}

// Удаление элемента из хэш-таблицы
extern void del_hashtab(HashTab *hashtab, void *key) {
    uint32_t hash;
    switch (hashtab->type.key) {
        case DECIMAL_ELEM:
            hash = (uint64_t)key % hashtab->size;
            break;
        case STRING_ELEM:
            hash = _strhash((uint8_t *)key, hashtab->size);
            break;
    }
    del_tree(hashtab->table[hash], key);
}

// Проверка наличия ключа в хэш-таблице
extern _Bool in_hashtab(HashTab *hashtab, void *key) {
    uint32_t hash;
    switch (hashtab->type.key) {
        case DECIMAL_ELEM:
            hash = (uint64_t)key % hashtab->size;
            break;
        case STRING_ELEM:
            hash = _strhash((uint8_t *)key, hashtab->size);
            break;
    }
    return in_tree(hashtab->table[hash], key);
}

// Получение значения по ключу
extern value_tree_t get_hashtab(HashTab *hashtab, void *key) {
    uint32_t hash;
    switch (hashtab->type.key) {
        case DECIMAL_ELEM:
            hash = (uint64_t)key % hashtab->size;
            break;
        case STRING_ELEM:
            hash = _strhash((uint8_t *)key, hashtab->size);
            break;
    }
    return get_tree(hashtab->table[hash], key);
}

// Установка значения по ключу
extern void set_hashtab(HashTab *hashtab, void *key, void *value) {
    uint32_t hash;
    switch (hashtab->type.key) {
        case DECIMAL_ELEM:
            hash = (uint64_t)key % hashtab->size;
            break;
        case STRING_ELEM:
            hash = _strhash((uint8_t *)key, hashtab->size);
            break;
    }
    set_tree(hashtab->table[hash], key, value);
}

// Освобождение памяти хэш-таблицы
extern void free_hashtab(HashTab *hashtab) {
    for (size_t i = 0; i < hashtab->size; ++i) {
        free_tree(hashtab->table[i]);
    }
    free(hashtab->table);
    free(hashtab);
}

// Печать хэш-таблицы
extern void print_hashtab(HashTab *hashtab) {
    printf("{\n");
    for (size_t i = 0; i < hashtab->size; ++i) {
        if (hashtab->table[i]->node == NULL) {
            continue;
        }

        printf("\t%zu => ", i);
        print_tree_as_list(hashtab->table[i]);
    }
    printf("}\n");
}

// Внутренняя функция для хэширования строк
static uint32_t _strhash(uint8_t *s, size_t size) {
    uint32_t hashval = 0;
    for (; *s != '\0'; ++s) {
        hashval = *s + 31 * hashval;
    }
    return hashval % size;
}