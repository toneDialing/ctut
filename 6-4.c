#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define MAXWORD 100

/* Write a program that prints the distinct words in its input sorted into decreasing order
    of frequency of occurrence. Precede each word by its count. */

struct tnode
{
    char *word;
    int count;
    struct tnode *left;
    struct tnode *right;
};

struct wordcount_unit
{
    char *word;
    int count;
};

int total_word_count;

struct tnode *addtree(struct tnode *, char *);
void fill_array(struct tnode *, struct wordcount_unit *);
void treeprint(struct tnode *);
void q_sort(struct wordcount_unit [], int, int);
int getword(char *, int);

/* This code is partially from the book, but it doesn't free() the storage it allocates with malloc()
    because they haven't properly discussed those functions yet. */

/* I'm well aware this algorithm is terrible, but it gets the job done and is built upon algorithms and
    structures I already know. Once I know more about structures and algorithms, I'm sure I can rewrite
    this better. At any rate it is still satisfying to know I got everything to work on the first try,
    confirming that I understand the material thus far. */

/* General word frequency count (case-sensitive); prints words in decreasing order of frequency */
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
    struct wordcount_unit allwords[total_word_count];
    fill_array(root, allwords);
    q_sort(allwords, 0, total_word_count-1);
    for(int i=0; i<total_word_count; i++)
    {
        printf("%4d %s\n", allwords[i].count, allwords[i].word);
    }
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
        total_word_count++;
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

void fill_array(struct tnode *p, struct wordcount_unit *q)
{
    static int i;

    if(p!=NULL)
    {
        fill_array(p->left, q);
        q[i].word = p->word;
        q[i].count = p->count;
        i++;
        fill_array(p->right, q);
    }
}

void q_sort(struct wordcount_unit v[], int left, int right)
{
    int i, last;
    void swap(struct wordcount_unit [], int, int);

    if(left>=right) return;
    swap(v, left, (left+right)/2);
    last = left;
    for(i=left+1; i<=right; i++)
    {
        if(v[i].count>v[left].count)
        {
            swap(v, ++last, i);
        }
    }
    swap(v, left, last);
    q_sort(v, left, last-1);
    q_sort(v, last+1, right);
}

void swap(struct wordcount_unit v[], int i, int j)
{
    struct wordcount_unit temp;

    temp = v[i];
    v[i] = v[j];
    v[j] = temp;
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

/* NOTE: getword() doesn't account for words with apostrophes or hyphens etc. */
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