#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#include "db.h"

#define DB_FILE_PATH "/Users/rohansatapathy/code/rohansatapathy/textdb/db.txt"

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

bool is_flag(char* input, char* short_opt, char* long_opt) {
    int short_len = strlen(short_opt);
    int long_len = strlen(long_opt);
    return strncmp(input, short_opt, short_len) == 0 ||
           strncmp(input, long_opt, long_len) == 0;
}

int main(int argc, char* argv[]) {
    if (argc != 2 && argc != 3) {
        print_help_text();
        return 0;
    }

    if (is_flag(argv[1], "-h", "--help")) {
        print_help_text();
        return 0;
    }

    FILE* fp = fopen(DB_FILE_PATH, "r");
    if (fp == NULL) {
        printf("Unable to open db.txt!\n");
        return 1;
    }

    struct db* db = db_init(fp);
    fclose(fp);
    if (db == NULL) {
        printf("Invalid db.txt file!\n");
        return 1;
    }

    if (is_flag(argv[1], "-a", "--all")) {
        db_print(db);
        db_delete(db);
        return 0;
    }

    if (argc == 2) {
        char* val = db_get(db, argv[1]);
        if (val != NULL) {
            printf("%s: %s\n", argv[1], val);
        } else {
            printf("Key '%s' not found.\n", argv[1]);
        }
        return 0;
    }

    if (argc == 3) {
        db_put(db, argv[1], argv[2]);
        fp = fopen(DB_FILE_PATH, "w");
        if (fp == NULL) {
            printf("Unable to open db.txt!\n");
            return 1;
        }
        db_write(db, fp);
        db_delete(db);
        return 0;
    }

    return 0;
}
