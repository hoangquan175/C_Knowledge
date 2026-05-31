/*
Exercises:
6-5 Write a function undef that will remove a name and definition from the table 
maintained by lookup and install.
*/


#include <stdio.h>
#include "header.h"
#include <stdlib.h>
#include <string.h>

char *strdup(const char *s);
unsigned hash(const char *s);
struct nlist *lookup(const char *s);
struct nlist *install(const char *name, const char *defn);

#define HASHTAB_SIZE 101

struct nlist { /* table entry: */
    struct nlist *next; /* next entry in chain */
    char *name; /* defined name */
    char *defn; /* replacement text */
};

static struct nlist *hashtab[HASHTAB_SIZE]; /* pointer table */

// install: put (name, defn) in hashtable
struct nlist *install(const char *name, const char *defn) {
    struct nlist *np;
    unsigned hashval;
    if ((np = lookup(name)) == NULL) { /* not found */
        np = (struct nlist *)malloc(sizeof(*np));
        if (np == NULL || (np->name = strdup(name)) == NULL) {
            return NULL;
        }
        hashval = hash(name);
        np->next = hashtab[hashval];
        hashtab[hashval] = np;
    } else { /* already there */
        free((void *)np->defn); /* free previous defn */
    }
    if ((np->defn = strdup(defn)) == NULL) {
        return NULL;
    }
    return np;
}

// hash: form hash value for string s
unsigned hash(const char *s) {
    unsigned hashval;
    for (hashval = 0; *s != '\0'; s++)
        hashval = *s + 31 * hashval;
    return hashval % 101;
}

// lookup: look for s in hashtable
struct nlist *lookup(const char *s) {
    struct nlist *np;
    for (np = hashtab[hash(s)]; np != NULL; np = np->next) {
        if (strcmp(s, np->name) == 0)
            return np; /* found */
    }
    return NULL; /* not found */
}

// Write a function undef that will remove a name and definition from the table maintained by lookup and install.
void undef(const char *name) {
    unsigned hashval = hash(name);
    struct nlist *np = hashtab[hashval];
    struct nlist *prev = NULL;

    while (np != NULL) {
        if (strcmp(name, np->name) == 0) {
            if (prev == NULL) {
                hashtab[hashval] = np->next; // Remove the first node in the chain
            } else {
                prev->next = np->next; // Bypass the node to be removed
            }
            free(np->name); // Free the name string
            free(np->defn); // Free the definition string
            free(np); // Free the node itself
            return;
        }
        prev = np;
        np = np->next;
    }
    // If we reach here, the name was not found in the table
    fprintf(stderr, "undef: name '%s' not found in table\n", name);
}

int main(void) {
    // Example usage of undef function
    install("PI", "3.14");
    struct nlist *np = lookup("PI");
    if (np) {
        printf("PI: %s\n", np->defn);
    } else {
        printf("PI not found\n");
    }
    undef("PI"); // Remove the PI entry
    np = lookup("PI"); // Try to look up PI again
    if (np) {
        printf("PI: %s\n", np->defn);
    } else {
        printf("PI not found\n");
    }
    return 0;
}
