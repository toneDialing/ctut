#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_WORD_LENGTH 100

struct nlist
{
    struct nlist *next;
    char *name;
    char *defn;
};

#define HASHSIZE 101

static struct nlist *hashtab[HASHSIZE];

unsigned hash(char *);
struct nlist *lookup(char *);
struct nlist *install(char *, char *);
char *duplicate_string(char *);
int getword(char *, int);
int getch(void);
void ungetch(int);

/* Implement a simple version of the #define processor (i.e., no arguments) suitable for use with C programs,
    based on the routines of this section. You may also find getch() and ungetch() helpful. */

/* All the necessary hashmap functions are already written as install() and lookup() etc.,
    so I should only need to use getch()/ungetch() to search for '#'s followed by "define" */
/* Use if for '#' then loop along to match chars to "define" */

/* Thus far this code puts names and definitions in table, but doesn't replace them in source code */

int main(void)
{
    int c;
    char word[MAX_WORD_LENGTH];
    char name[MAX_WORD_LENGTH];
    char defn[MAX_WORD_LENGTH];

    while(isspace(c=getch()));
    while(c=='#')
    {
        c = getword(word, MAX_WORD_LENGTH);

    }

    while(getword(word, MAX_WORD_LENGTH)!=EOF)
    {
        if(strcmp(word, "#define")!=0) continue;

        if(getword(name, MAX_WORD_LENGTH)!=EOF && getword(defn, MAX_WORD_LENGTH)!=EOF)
        {
            install(name, defn);
        }
    }

    /* this installation loop needs to end before I can begin replacing text */

    /* note this only prints first entry in linked list for each hash value */
    for(int i=0; i<HASHSIZE; i++)
    {
        if(hashtab[i]!=NULL)
        {
            printf("%s: %s\n", hashtab[i]->name, hashtab[i]->defn);
        }
    }

    return 0;
}

void preprocess(void)
{
    int c;
    char word[MAX_WORD_LENGTH];
    char name[MAX_WORD_LENGTH];
    char defn[MAX_WORD_LENGTH];

    while(isspace((c=getch())));
    if(c!='#') return;

    if(getword(word, MAX_WORD_LENGTH)==EOF) return;

    if(strcmp(word, "define")==0)
    {
        if(getword(name, MAX_WORD_LENGTH)!=EOF && getword(defn, MAX_WORD_LENGTH)!=EOF)
        {
            install(name, defn);
        }
    }
}

/* install: put (name, defn) in hashtab */
struct nlist *install(char *name, char *defn)
{
    struct nlist *np;
    unsigned hashval;

    if((np = lookup(name)) == NULL) /* name not found */
    {
        np = (struct nlist *) malloc(sizeof(*np));
        if(np == NULL || (np->name = duplicate_string(name)) == NULL)
        {
            return NULL;
        }
        hashval = hash(name);
        np->next = hashtab[hashval];
        hashtab[hashval] = np;
    }
    else /* name already exists */
    {
        free((void *) np->defn); /* free previous definition */
    }
    
    if((np->defn = duplicate_string(defn)) == NULL)
    {
        return NULL;
    }

    return np;
}

/* lookup: look for s in hashtab */
struct nlist *lookup(char *s)
{
    struct nlist *np;

    for(np = hashtab[hash(s)]; np!=NULL; np = np->next)
    {
        if(strcmp(s, np->name)==0)
        {
            return np;
        }
    }
    return NULL;
}

/* hash: form hash value for string s */
unsigned hash(char *s)
{
    unsigned hashval;

    for(hashval = 0; *s!='\0'; s++)
    {
        hashval = *s + 31*hashval;
    }
    return hashval % HASHSIZE;
}

/* duplicate_string: make a duplicate of s */
char *duplicate_string(char *s)
{
    char *p;

    p = (char *) malloc(strlen(s)+1); // +1 for '\0'
    if(p!=NULL)
    {
        strcpy(p, s);
    }
    return p;
}

/* getword: get next word or character from input
    Here, a word is defined as any collection of characters separated by spaces */
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
    else return c;

    for(; --lim>0; w++)
    {
        if(isspace(*w = getch()) || *w == EOF)
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