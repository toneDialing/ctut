#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define MAXWORD 100

struct tnode
{
    char *word;
    int line_number;
    struct line_node *next_line;
    struct tnode *left;
    struct tnode *right;
};

struct line_node
{
    int line_number;
    struct line_node *next_line;
};

int line_count = 1;

struct tnode *addtree(struct tnode *, char *);
void treeprint(struct tnode *);
int getword(char *, int);

/* The groundwork for this code is from the book, but it doesn't free() the storage it allocates
    with malloc() because they haven't properly discussed those functions yet. */

/* Prints all words (case-sensitive) in a document, along with the line number(s) they appear on */
int main(void)
{
    struct tnode *root;
    char word[MAXWORD];

    root = NULL;
    while(getword(word, MAXWORD)!=EOF)
    {
        if(word[0]=='\n')
        {
            line_count++;
        }
        else if(isalpha(word[0]))
        {
            root = addtree(root, word);
        }
    }
    treeprint(root);
    return 0;
}

struct tnode *talloc(void);
struct line_node *lalloc(void);
struct line_node *addtree_line(struct line_node *);
char *duplicate_str(char *);

/* addtree: add a node with w, at or below p */
struct tnode *addtree(struct tnode *p, char *w)
{
    int cond;

    if(p==NULL) /* new word has arrived */
    {
        p = talloc(); /* make a new node */
        p->word = duplicate_str(w);
        p->line_number = line_count;
        p->left = p->right = NULL;
        p->next_line = NULL;
    }
    else if((cond=strcmp(w, p->word))==0)
    {
        if(line_count > p->line_number)
        {
            p->next_line = addtree_line(p->next_line);
        }
    }
    else if(cond<0)
    {
        p->left = addtree(p->left, w);
    }
    else p->right = addtree(p->right, w);
    return p;
}

/* addtree_line: adds a new line_node to store line_count if line_count is unique */
struct line_node *addtree_line(struct line_node *p)
{
    if(p==NULL)
    {
        p = lalloc();
        p->line_number = line_count;
        p->next_line = NULL;
    }
    else if(line_count > p->line_number)
    {
        p->next_line = addtree_line(p->next_line);
    }
    return p;
}

void lineprint(struct line_node *);

/* treeprint: in-order print of tree p */
void treeprint(struct tnode *p)
{
    if(p!=NULL)
    {
        treeprint(p->left);
        printf("\t%s: %d", p->word, p->line_number);
        if(p->next_line!=NULL) lineprint(p->next_line);
        printf("\n");
        treeprint(p->right);
    }
}

/* lineprint: prints increasing line numbers for a given word */
void lineprint(struct line_node *p)
{
    printf(", %d", p->line_number);
    if(p->next_line!=NULL) lineprint(p->next_line);
}

/* talloc: make a tnode */
struct tnode *talloc(void)
{
    return (struct tnode *) malloc(sizeof(struct tnode));
}

/* lalloc: make a line_node */
struct line_node *lalloc(void)
{
    return (struct line_node *) malloc(sizeof(struct line_node));
}

/* duplicate_str: make a duplicate of s */
char *duplicate_str(char *s)
{
    char *p;

    p = (char *) malloc(strlen(s)+1); // +1 for '\0'
    if(p!=NULL)
    {
        strcpy(p, s);
    }
    return p;
}

int getch(void);
void ungetch(int);

/* getword: get next word or character from input */
int getword(char *word, int lim)
{
    int c;
    char *w = word;

    /* ignore literal space characters */
    while((c = getch())==' ');
    if(c!=EOF)
    {
        *w++ = c;
    }
    if(!isalpha(c))
    {
        *w = '\0';
        return c;
    }

    for(; --lim>0; w++)
    {
        if(!isalnum(*w = getch()))
        {
            ungetch(*w);
            break;
        }
    }
    *w = '\0';
    return word[0];
}

#define BUFSIZE 100

int buf[BUFSIZE]; // Buffer for ungetch, changed to type int to handle EOF
int bufp = 0; // Next free position in buf

/* Get a (possibly pushed back) character */
int getch(void)
{
    return (bufp > 0) ? buf[--bufp] : getchar();
}

/* Push character back on input */
void ungetch(int c)
{
    if(bufp>=BUFSIZE)
    {
        printf("ungetch: too many characters\n");
    }
    else buf[bufp++] = c;
}