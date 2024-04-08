# TextDB

TextDB is a (bad) database system that stores key-value pairs in a text file.
Each key-value pair is stored on a separate line in the text file, and
keys and values are strings separated by a space. The following is an example
of a properly formatted TextDB database file:

```
apple orange
water melon
lets go blue
```
The first space is interpreted as the separator between the key and value,
and all subsequent spaces are treated as part of the value. For example,
the third item has key "lets" and value "go blue".

TextDB can be accessed from the command line through the `db` command, which
contains the following help text.

```
Usage:
    db <db-file-path> <key>             # Read a key
    db <db-file-path> <key> <value>     # Set a key-value pair
    db <db-file-path> [-a | --all]      # List all database items
    db [-h | --help]                    # Print the help menu

Options:
    -h, --help  Show this screen.
    -a, --all   Display all key-value pairs.
```

While in use, this database is meant to be stored on the heap instead of the
stack because its size can't be known at compile time. Each item is stored
in a `dbitem` struct, which contains a `char*` pointing to the key and the
value, both of which are heap-allocated. These `dbitem` structs are stored in
a `db` struct, which maintains a pointer to the beginning of a `dbitem[]`
array, the size of the database (number of items), and the capacity of the
currently allocated `dbitem` array.

Whenever items are added or removed from the list, the underlying `dbitem[]`
array could be reallocated. If the newly added item makes the array reach
capacity, the `dbitem`s will be moved to a new array of twice the size. If
removing an item from the database causes the size to shrink to less than
1/4 of the capacity, the `dbitem`s will be moved to a new array of 1/2 the
original capacity.

