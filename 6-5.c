#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
void undef(char *);
char *duplicate_string(char *);

/* Write a function undef() that will remove a name and definition from the table maintained
    by lookup() and install() */

int main(void)
{
    char *name1 = "IN";
    char *defn1 = "1";
    char *name2 = "OUT";
    char *defn2 = "0";

    install(name1, defn1);
    install(name2, defn2);

    undef(name1);

    for(int i=0; i<HASHSIZE; i++)
    {
        if(hashtab[i]!=NULL)
        {
            printf("%s: %s\n", hashtab[i]->name, hashtab[i]->defn);
        }
    }

    return 0;
}

/* undef: remove (name, defn) from hashtab
    Removes entire block containing (name, defn) from linked list, freeing its memory.
    Only uses name to search for name and defn, since there exists only one defn per name.
    Does nothing if name isn't found. User isn't alerted of redundancy since the goal is to
    remove the name anyway. */
void undef(char *name)
{
    struct nlist *np;
    struct nlist *previous_struct;
    unsigned hashval = hash(name);
    int linked_list_position = 0;

    for(np = previous_struct = hashtab[hashval]; np != NULL; np = np->next)
    {
        if(strcmp(name, np->name)==0)
        {
            break;
        }
        linked_list_position++;
        previous_struct = np;
    }
    if(np==NULL) return;

    if(linked_list_position)
    {
        previous_struct->next = np->next;
    }
    else
    {
        hashtab[hashval] = np->next;
    }

    free((void *) np->name);
    free((void *) np->defn);
    free((void *) np);
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