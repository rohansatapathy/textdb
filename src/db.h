#ifndef TEXTDB_DB_H_
#define TEXTDB_DB_H_

#include <stdio.h>

#define MAX_ITEM_LENGTH 1024

struct dbitem {
    char* key;
    char* value;
};

struct db {
    struct dbitem* items;
    int size;
    int capacity;
};

/*
 * Return a pointer to a new db by reading the given file.
 *
 * Return NULL if the file is in an invalid format.
 */
struct db* db_init(FILE* fp);

/*
 * Print the contents of db to stdout in the following format:
 *
 * key1: value1
 * key2: value2
 * ...
 */
void db_print(struct db* db);

/*
 * Return a pointer to the value associated with the given key. If the key
 * doesn't exist, return NULL;
 */
char* db_get(struct db* db, char key[]);

/*
 * If key doesn't exist in db already, create a new item with the given
 * key and value. Otherwise, overwrite the value of the given key.
 *
 * NOTE: This function allocates new memory for the key if it doesn't
 * already exist, and it always allocates new memory for the value.
 */
void db_put(struct db* db, char key[], char value[]);

/*
 * Remove the item corresponding to the given key. If the key doesn't
 * exist, do nothing.
 */
void db_remove(struct db* db, char key[]);

/*
 * Write out the contents of db into the given file in the correct format
 * (see README.md).
 */
void db_write(struct db* db, FILE* fp);

/*
 * Free all memory used by db.
 */
void db_delete(struct db* db);

#endif // !TEXTDB_DB_H_
