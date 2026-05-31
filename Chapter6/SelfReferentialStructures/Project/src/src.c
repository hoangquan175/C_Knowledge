/*
Exercises:
6-3 Write a program that prints the distinct words in its input sorted into decreasing 
order of frequency of occurrence. Precede each word by its count.
*/

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "header.h"

#define MAXWORD 100

struct word_node {
    char *word;
    int count;
    struct word_node *next;
};

static char *duplicate_string(const char *source) {
    size_t size = strlen(source) + 1;
    char *copy = malloc(size);
    if (!copy) {
        perror("malloc");
        exit(EXIT_FAILURE);
    }
    memcpy(copy, source, size);
    return copy;
}

static struct word_node *add_word(struct word_node *root, const char *word) {
    struct word_node *node = root;
    while (node) {
        if (strcmp(node->word, word) == 0) {
            node->count++;
            return root;
        }
        node = node->next;
    }

    struct word_node *new_node = malloc(sizeof(struct word_node));
    if (!new_node) {
        perror("malloc");
        exit(EXIT_FAILURE);
    }

    new_node->word = duplicate_string(word);

    new_node->count = 1;
    new_node->next = root;
    return new_node;
}

static int compare_counts(const void *a, const void *b) {
    const struct word_node * const *node_a = a;
    const struct word_node * const *node_b = b;
    return (*node_b)->count - (*node_a)->count;
}

static void print_word_frequencies(void) {
    char word[MAXWORD];
    struct word_node *root = NULL;
    int word_len;
    int node_count = 0;

    while ((word_len = getword(word, sizeof(word))) != EOF) {
        if (word_len > 0) {
            root = add_word(root, word);
            node_count++;
        }
    }

    if (!root) {
        return;
    }

    struct word_node **nodes = malloc(node_count * sizeof(struct word_node *));
    if (!nodes) {
        perror("malloc");
        exit(EXIT_FAILURE);
    }

    int index = 0;
    for (struct word_node *node = root; node; node = node->next) {
        nodes[index++] = node;
    }

    qsort(nodes, index, sizeof(struct word_node *), compare_counts);

    for (int i = 0; i < index; i++) {
        printf("%d %s\n", nodes[i]->count, nodes[i]->word);
    }

    for (int i = 0; i < index; i++) {
        free(nodes[i]->word);
        free(nodes[i]);
    }
    free(nodes);
}

int getword(char *word, int lim) {
    int c;
    char *w = word;

    while ((c = getchar()) != EOF && !isalpha(c)) {
        ;
    }

    if (c == EOF) {
        return EOF;
    }

    *w++ = tolower(c);
    while (--lim > 0 && (c = getchar()) != EOF && isalnum(c)) {
        *w++ = tolower(c);
    }
    *w = '\0';

    if (c != EOF && !isalnum(c)) {
        ungetc(c, stdin);
    }

    return (int)strlen(word);
}

int main(void) {
    print_word_frequencies();
    return 0;
}
