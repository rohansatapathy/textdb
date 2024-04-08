# TextDB

TextDB is an in-memory database system that tracks key-value pairs. It persists
data in a text file, where each key-value pair is stored on a separate line 
in the text file, and keys and values are strings separated by a space. 

```
apple orange
water melon
lets go blue
```

The first space is interpreted as the separator between the key and value,
and all subsequent spaces are treated as part of the value. For example,
the third item has key "lets" and value "go blue". Each item has a maximum
size of 1023 bytes, including the trailing newline.

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

## Installation

To install TextDB, you will need to compile from source. To do so, make sure
you have `git` and a C11-compatible compiler (e.g. `clang`) installed, then run 
the following commands.

```console
$ git clone https://github.com/rohansatapathy/textdb.git
$ cd textdb
$ mkdir bin
$ make build
```

The `db` binary will be available as `./bin/db`.

## How does it work?

When the `db` command is run, the entire database is loaded into memory.
Internally, the database is stored as a heap-allocated array of `dbitem`
structs, which themselves contain pointers to the item's key and value.

Adding items to the array has an amortized time complexity of $O(1)$. If adding
the new item causes the array to reach its capacity, then it will be 
reallocated to double its original capacity.

Searching for a key has a time complexity of $O(n)$ because the keys are
stored in an unordered list.

Removing items from the array has an amortized time complexity of $O(n)$,
because searching for the item is $O(n)$ and because removing an item requires 
shifting all subsequent elements back to ensure the array remains contiguous. 
If the new size of the array is less than or equal to 1/4 its capacity, then 
it will be reallocated to half its original capacity.

## FAQ

 - Q: Why not use a data structure that's more efficient than an unordered
   list?

   A: If there's anything that I've learned over the past few years, it's that
   efficiency is overrated. Why is everyone so obsessed with hash maps and
   RB trees and "cOnStAnT tImE sEaRcH"? If you ask me, TextDB is a win for
   developers -- if you don't feel like doing work, just load up a particularly
   large database, then when your boss asks you what you're doing, just tell
   them that your database query is still running ([relevant xkcd](https://xkcd.com/303/)).

 - Q: Is TextDB ready to use in production?

   A: Yes! TextDB's single-threaded, blocking design makes it ideal for highly 
   parallel, distributed environments. 

   (Note: for legal reasons, I'm not responsible if someone corrupts your data
   by gaining root access to your server and modifying your plain-text database
   file.)

 - Q: Why does TextDB exist?

   A: Literally for no other reason than for me to learn C.

 
