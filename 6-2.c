#include <stdio.h>
#include <stdlib.h>

#define MAXWORD 100
#define PRINT_USAGE_ERROR printf("Error: must specify # of matching characters \
for program to group variable names together by\n\t\
E.g.: './6-2 x' where x specifies # of characters\n\t\
The command-line argument x must be a positive integer\n")

/* Write a program that reads a C program and prints in alphabetical order each group of variable names
    that are identical in the first 6 characters, but different somewhere thereafter. Don't count words
    within strings and comments. Make 6 a parameter that can be set from the command line. */

/* Only put variable names in binary tree */

/* Create indicator is_identical, set = 1 for variable names that have at least one 6-character twin.
    Put is_identical in binary tree and when printing alphabetically, only print those valus for which
    is_identical is true.
        This will require backtracking one node to set is_identical = 1 whenever first twin is found */

/* How to find variable names:
    Look for data type, and valid word that follows is a variable unless it is immediately followed by '('
    Data types:
        char
        int
        float
        double
        short   (if encountered, check if next word is also data type)
        long    (if encountered, check if next word is also data type)
        void *
            In all cases, check for subsequent *'s (potentially multiple)
        
        struct is a little more complicated. It could be:
            struct tag x
            struct tag {...} x
            struct {...} x
        All with potential subsequent *'s
*/

struct tnode
{
    char *var_name;
    int is_identical;
    struct tnode *left;
    struct tnode *right;
};

struct tnode *addtree(struct tnode *, char *);
void treeprint_twins(struct tnode *);
int get_variable(char *, int);

int main(int argc, char *argv[])
{
    struct tnode *root;
    char word[MAXWORD];

    if(argc!=2)
    {
        PRINT_USAGE_ERROR;
        return 0;
    }

    const int character_match = atoi(argv[1]);
    if(character_match<1)
    {
        PRINT_USAGE_ERROR;
        return 0;
    }

    root = NULL;
    while(get_variable(word, MAXWORD)!=EOF)
    {
        root = addtree(root, word);
    }
    treeprint_twins(root);
    return 0;
}

struct tnode *addtree(struct tnode *p, char *w)
{
    return p;
}

void treeprint_twins(struct tnode *p)
{

}

int get_variable(char *w, int n)
{
    return n;
}