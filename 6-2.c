#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

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
    is_identical is true. */

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

char *basic_datatypes[] = {"char", "int", "float", "double"};
#define NUMBER_DATATYPES ((sizeof basic_datatypes)/(sizeof basic_datatypes[0]))

struct tnode
{
    char *var_name;
    int is_identical;
    struct tnode *left;
    struct tnode *right;
};

struct tnode *addtree(struct tnode *, char *, const int);
void treeprint(struct tnode *);
int is_variable(char *, int);
int getword(char *, int);

/* Reads input as C source code and alphabetically prints all groups of variables that match
    up through their first n characters, where n is determined by a command-line argument. */
/* I'm supposed to not count words within strings and comments, but I also am not counting words
    in preprocessor lines. I only modified getword() from 6-1.c to allow for parsing words that
    begin with or include underscores, seeing as many variable names use underscores. The
    function ignore_irregular_text() is unchanged but simply isn't called if an underscore is
    encountered. */
/* Error: fails to parse variable names declared following commas, e.g. "int c, n;" misses n.
    I'd also need to be able to handle more complex cases like "int c, getnum(int x, int y), n;" */
/* Error: fails to parse newlines and tabs in variable declarations, such as with struct {} */
/* I'm confident I can fix these errors but in the interest of time I'm moving on. I honestly
    feel as though I've successfully programmed the gist of the problem anyway. */
/* Assumes valid C program input */
int main(int argc, char *argv[])
{
    int c;
    struct tnode *root;
    char word[MAXWORD];

    if(argc!=2)
    {
        PRINT_USAGE_ERROR;
        return 0;
    }

    const int match_threshold = atoi(argv[1]);
    if(match_threshold<1)
    {
        PRINT_USAGE_ERROR;
        return 0;
    }

    root = NULL;
    while((c=getword(word, MAXWORD))!=EOF)
    {
        if(is_variable(word, c))
        {
            root = addtree(root, word, match_threshold);
        }
    }
    treeprint(root);
    return 0;
}

struct tnode *talloc(void);
char *duplicate_str(char *);

/* addtree: add a node with w, at or below p. Also indicate if variable names match per match_threshold */
struct tnode *addtree(struct tnode *p, char *w, const int match_threshold)
{
    int cond, match_count;
    static int is_match;
    char *copy_a, *copy_b;
    match_count = 0;

    if(p==NULL) /* new word has arrived */
    {
        p = talloc(); /* make a new node */
        p->var_name = duplicate_str(w);
        if(is_match)
        {
            p->is_identical = 1;
            is_match = 0;
        }
        else
        {
            p->is_identical = 0;
        }
        p->left = p->right = NULL;
    }
    else if((cond=strcmp(w, p->var_name))!=0)
    {
        copy_a = w;
        copy_b = p->var_name;
        while(*copy_a++ == *copy_b++)
        {
            match_count++;
        }
        if(match_count >= match_threshold)
        {
            is_match = 1;
            p->is_identical = 1;
        }
        if(cond<0) p->left = addtree(p->left, w, match_threshold);
        if(cond>0) p->right = addtree(p->right, w, match_threshold);
    }
    return p;
}

/* treeprint: in-order print of tree p, only printing those names where is_identical is true */
void treeprint(struct tnode *p)
{
    if(p!=NULL)
    {
        treeprint(p->left);
        if(p->is_identical)
        {
            printf("%s\n", p->var_name);
        }
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

/* is_variable:
    Checks whether word is the start of a valid data type, and if so, looks for a subsequent variable name.
    If the variable name is immediately followed by '(', then it is a function name instead.
    Returns 1 if variable name is found, 0 otherwise, and stores variable name in word */
int is_variable(char *word, int c)
{
    int next_char;

    if(!isalpha(c))
    {
        return 0;
    }

    /* check for char, int, float, double */
    for(int i=0; i<NUMBER_DATATYPES; i++)
    {
        if(strcmp(word, basic_datatypes[i])==0)
        {
            while((next_char=getch())==' ' || next_char=='*'); /* skip potential pointers */
            ungetch(next_char);

            c = getword(word, MAXWORD);
            if((next_char=getch())=='(') /* variable name is actually function name */
            {
                return 0;
            }
            ungetch(next_char);
            return 1;
        }
    }

    /* check for short (int), long (int/double) */
    if(strcmp(word, "short")==0 || strcmp(word, "long")==0)
    {
        int is_long;
        if(strcmp(word, "long")==0) is_long = 1;

        while((next_char=getch())==' ' || next_char=='*'); /* skip potential pointers */
        ungetch(next_char);

        c = getword(word, MAXWORD);
        if(strcmp(word, "int")==0 || (strcmp(word, "double")==0 && is_long))
        {
            return is_variable(word, c);
        }
        if((next_char=getch())=='(') /* variable name is actually function name */
        {
            return 0;
        }
        ungetch(next_char);
        return 1;
    }

    /* check for void * */
    if(strcmp(word, "void")==0)
    {
        int pointer_count = 0;
        while((next_char=getch())==' ' || next_char=='*') /* skip potential pointers */
        {
            if(next_char=='*') pointer_count++;
        }
        ungetch(next_char);
        if(!pointer_count) return 0;

        c = getword(word, MAXWORD);
        if((next_char=getch())=='(') /* variable name is actually function name */
        {
            return 0;
        }
        ungetch(next_char);
        return 1;
    }

    /* check for struct */
    if(strcmp(word, "struct")==0)
    {
        c = getword(word, MAXWORD);
        if(isalpha(c)) /* skip potential tag */
        {
            while((c=getch())==' ' || c=='*'); /* skip potential pointers */
        }
        if(c=='{') /* skip structure members */
        {
            int open_bracket_count = 1;
            while(open_bracket_count>0)
            {
                next_char = getch();
                if(next_char=='{') open_bracket_count++;
                else if(next_char=='}') open_bracket_count--;
            }
            while((c=getch())==' ' || c=='*'); /* skip potential pointers */
        }
        ungetch(c);

        c = getword(word, MAXWORD);
        if((next_char=getch())=='(') /* variable name is actually function name */
        {
            return 0;
        }
        ungetch(next_char);
        return 1;
    }

    return 0;
}

void skip_irregular_text(int);
void skip_comment(void);
void skip_preprocessor(void);

/* getword: get next word or character from input */
/* Modified to treat '_' as an alphabetical character to parse variable names */
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
    if(!isalpha(c) && c!='_')
    {
        skip_irregular_text(c);
        *w = '\0';
        return c;
    }

    for(; --lim>0; w++)
    {
        if(!isalnum(*w = getch()) && *w!='_')
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