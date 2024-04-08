#include <stdio.h>

#include "db.h"

void print_help_text(void) {
    char* msg = "Usage:\n"
                "  db <key>\n"
                "  db <key> <value>\n"
                "  db [OPTION]\n\n"

                "Options:\n"
                "  -h, --help  Show this screen.\n"
                "  -a, --all   Display all key-value pairs.\n";
    printf("%s", msg);
}

int main(int argc, char* argv[]) {
    FILE* fp =
        fopen("/Users/rohansatapathy/code/rohansatapathy/textdb/db.txt", "r");
    if (fp == NULL) {
        printf("Unable to open db.txt!");
        return 1;
    }

    struct db* db = db_init(fp);
    fclose(fp);
    if (db == NULL) {
        printf("Invalid db.txt file!");
        return 1;
    }

    db_print(db);
    printf("\n");
    db_remove(db, "water");
    printf("Removed water melon\n\n");
    db_print(db);

    fp = fopen("/Users/rohansatapathy/code/rohansatapathy/textdb/db.txt", "w");
    if (fp == NULL) {
        printf("Unable to open db.txt!");
        return 1;
    }

    db_write(db, fp);
    db_delete(db);
    db = NULL;

    return 0;
}
