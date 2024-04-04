#include "db.h"

#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
 * Resize the underlying dbitem array to the new size. Requires that the
 * current size of the db is less than or equal to the new size.
 *
 * new_capacity: the maximum number of items that can be stored in the
 * newly allocated array.
 */
void db_resize(struct db* db, int new_capacity) {
    assert(db->size <= new_capacity);
    db->items = realloc(db->items, new_capacity * sizeof(struct dbitem));
    db->capacity = new_capacity;
}

/*
 * Return a pointer to the dbitem with the given key. Returns NULL if the key
 * couldn't be found.
 */
struct dbitem* db_find(struct db* db, char key[]) {
    bool key_found;
    for (struct dbitem* i = db->items; i < db->items + db->size; i++) {
        if (strcmp(key, i->key) == 0) {
            return i;
        }
    }
    return NULL;
}

void db_put(struct db* db, char key[], char value[]) {
    char* v = malloc(sizeof(char) * strlen(value));
    strncpy(v, value, strlen(value));

    // Check if the key already exists
    struct dbitem* item = db_find(db, key);
    if (item != NULL) {
        free(item->value);
        item->value = v;
        return;
    }

    // Key not found, so create new dbitem
    char* k = malloc(sizeof(char) * strlen(key));
    k = strncpy(k, key, strlen(key));
    struct dbitem new_item = {.key = k, .value = v};
    if (db->size == db->capacity) {
        db_resize(db, 2 * db->size);
    }
    db->items[db->size] = new_item;
    db->size++;
}

void db_delete(struct db* db) {
    for (int i = 0; i < db->size; i++) {
        free(db->items[i].key);
        free(db->items[i].value);
    }
    free(db->items);
    free(db);
}

/*
 * Return a pointer to a db with size 0 and capacity 4.
 */
struct db* empty_db_init(void) {
    struct db* db = malloc(sizeof(struct db));
    db->size = 0;
    db->capacity = 4;
    db->items = malloc(sizeof(struct dbitem) * db->capacity);
    return db;
}

struct db* db_init(FILE* fp) {
    struct db* db = empty_db_init();

    // Load each line into a dbitem and add it to the db.
    char line[MAX_ITEM_LENGTH];
    while (fgets(line, sizeof(line), fp) != NULL) {
        char* key = line;
        char* value = NULL;
        for (char* i = line; *i != '\0'; i++) {
            if (*i == ' ') {
                // Replace space with sentinel to separate key and value
                *i = '\0';
                value = ++i;

                // Replace trailing newline with sentinel
                while (*i != '\n' && *i != '\0') {
                    i++;
                }
                *i = '\0';

                db_put(db, key, value);
            }
        }
        if (value == NULL) {
            // Invalid file format
            db_delete(db);
            return NULL;
        }
    }

    return db;
}

void db_print(struct db* db) {
    for (int i = 0; i < db->size; i++) {
        printf("%s: %s\n", db->items[i].key, db->items[i].value);
    }
}

char* db_get(struct db* db, char key[]) {
    for (int i = 0; i < db->size; i++) {
        if (strcmp(key, db->items[i].key) == 0) {
            return db->items[i].value;
        }
    }
    return NULL;
}

void db_remove(struct db* db, char key[]) { assert(false); }

void db_write(struct db* db, FILE* fp) { assert(false); }
