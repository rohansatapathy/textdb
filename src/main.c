#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#include "db.h"

#define DB_FILE_PATH "/Users/rohansatapathy/code/rohansatapathy/textdb/db.txt"

void print_help_text(void) {
    char* msg =
        "Usage:\n"
        "    db <db-file-path> <key>             # Read a key\n"
        "    db <db-file-path> <key> <value>     # Set a key-value pair\n"
        "    db <db-file-path> [-a | --all]      # List all database items\n"
        "    db [-h | --help]                    # Print the help menu\n"
        "\n"
        "Options:\n"
        "    -h, --help  Show this screen.\n"
        "    -a, --all   Display all key-value pairs.\n";
    printf("%s", msg);
}

bool is_flag(char* input, char* short_opt, char* long_opt) {
    int short_len = strlen(short_opt);
    int long_len = strlen(long_opt);
    return strncmp(input, short_opt, short_len) == 0 ||
           strncmp(input, long_opt, long_len) == 0;
}

int main(int argc, char* argv[]) {
    if (argc != 3 && argc != 4) {
        print_help_text();
        return 0;
    }

    if (is_flag(argv[1], "-h", "--help")) {
        print_help_text();
        return 0;
    }

    FILE* fp = fopen(argv[1], "r");
    if (fp == NULL) {
        printf("Unable to open '%s'.\n", argv[1]);
        return 1;
    }

    struct db* db = db_init(fp);
    fclose(fp);
    if (db == NULL) {
        printf("Invalid db.txt file.\n");
        return 1;
    }

    if (is_flag(argv[2], "-a", "--all")) {
        db_print(db);
        db_delete(db);
        return 0;
    }

    if (argc == 3) {
        char* val = db_get(db, argv[2]);
        if (val != NULL) {
            printf("%s: %s\n", argv[2], val);
        } else {
            printf("Key '%s' not found.\n", argv[2]);
        }
        return 0;
    }

    if (argc == 4) {
        db_put(db, argv[2], argv[3]);
        fp = fopen(argv[1], "w");
        if (fp == NULL) {
            printf("Unable to open %s.\n", argv[1]);
            return 1;
        }
        db_write(db, fp);
        fclose(fp);
        db_delete(db);
        return 0;
    }

    return 0;
}
