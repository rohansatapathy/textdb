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
    if (db == NULL) {
        printf("Invalid db.txt file!");
        return 1;
    }
    db_print(db);
    db_delete(db);
    return 0;
}
