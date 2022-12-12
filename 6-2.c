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

char *basic_datatypes[] = {"char", "int", "float", "double"};
#define NUMBER_DATATYPES ((sizeof basic_datatypes)/(sizeof basic_datatypes[0]))

struct tnode
{
    char *var_name;
    int is_identical;
    struct tnode *left;
    struct tnode *right;
};

struct tnode *addtree(struct tnode *, char *);
void treeprint_twins(struct tnode *);
int is_variable(char *, int);

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

    const int character_match = atoi(argv[1]);
    if(character_match<1)
    {
        PRINT_USAGE_ERROR;
        return 0;
    }

    root = NULL;
    while((c=getword(word, MAXWORD))!=EOF)
    {
        if(is_variable(word, c))
        {
            root = addtree(root, word);
        }
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

int getword(char *, int);
int getch(void);
void ungetch(int);

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