#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define MAXWORD 100

struct tnode
{
    char *word;
    int count;
    struct tnode *left;
    struct tnode *right;
};

struct tnode *addtree(struct tnode *, char *);
void treeprint(struct tnode *);
int getword(char *, int);

/* General word frequency count (case-sensitive) */
int main(void)
{
    struct tnode *root;
    char word[MAXWORD];

    root = NULL;
    while(getword(word, MAXWORD)!=EOF)
    {
        if(isalpha(word[0]))
        {
            root = addtree(root, word);
        }
    }
    treeprint(root);
    return 0;
}

struct tnode *talloc(void);
char *duplicate_str(char *);

/* addtree: add a node with w, at or below p */
struct tnode *addtree(struct tnode *p, char *w)
{
    int cond;

    if(p==NULL) /* new word has arrived */
    {
        p = talloc(); /* make a new node */
        p->word = duplicate_str(w);
        p->count = 1;
        p->left = p->right = NULL;
    }
    else if((cond=strcmp(w, p->word))==0)
    {
        p->count++;
    }
    else if(cond<0)
    {
        p->left = addtree(p->left, w);
    }
    else p->right = addtree(p->right, w);
    return p;
}

/* treeprint: in-order print of tree p */
void treeprint(struct tnode *p)
{
    if(p!=NULL)
    {
        treeprint(p->left);
        printf("%4d %s\n", p->count, p->word);
        treeprint(p->right);
    }
}

/* talloc: make a tnode */
struct tnode *talloc(void)
{
    return (struct tnode *) malloc(sizeof(struct tnode));
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
void skip_irregular_text(int);
void skip_comment(void);
void skip_preprocessor(void);

/* getword: get next word or character from input */
int getword(char *word, int lim)
{
    int c;
    char *w = word;

    /* ignore white space and other irregular text */
    while(isspace(c = getch()));
    if(c!=EOF)
    {
        *w++ = c;
    }
    if(!isalpha(c))
    {
        skip_irregular_text(c);
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

/* skip_irregular_text: causes getch() to skip over underscored words, string constants, comments and
    preprocessor control lines */
void skip_irregular_text(int c)
{
    switch(c) {
    case '_':
        while(isalnum(c=getch()));
        ungetch(c);
        break;
    case '"':
        while((c=getch())!='"');
        break;
    case '/':
        if((c=getch())=='*')
        {
            skip_comment();
        }
        else ungetch(c);
        break;
    case '#':
        skip_preprocessor();
        break;
    default:
        break;
    }
}

/* skip_comment: causes getch() to skip over all text through end of comment */
void skip_comment(void)
{
    int c;

    while((c=getch())!=EOF)
    {
        if(c=='*')
        {
            if((c=getch())=='/') return;
            ungetch(c);
        }
    }
    ungetch(c);
}

/* skip_preprocessor: causes getch() to skip over all text through end of preprocessor control line(s) */
void skip_preprocessor(void)
{
    int c, temp;

    while((c=getch())!=EOF)
    {
        temp = c;
        if((c=getch())=='\n')
        {
            if(temp!='\\') return;
        }
        ungetch(c);
    }
    ungetch(c);
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