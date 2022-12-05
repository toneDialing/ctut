#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAXTOKEN 100

/* Added error recovery, so program can properly handle next input line upon encountering an error.
*   Error messaging is mildly redundant, but I don't think that's a problem. Cascading errors
*   are normal in compiling anyway. */
/* Added const qualifiers */

/* Expand to handle declarations with function argument types and const qualifiers */
/* Create new main()-like function just for function parameters; don't alter dcl/dirdcl */

enum {NAME, PARENS, BRACKETS};

void dcl(void);
void dirdcl(void);
void function_parameter(void);

int gettoken(void);
int getch(void);
void ungetch(int);
int tokentype;              /* type of last token */
int error;                  /* notifies presence of syntax error */
int var_name_found;         /* indicates whether variable name has been found yet */
char token[MAXTOKEN];       /* last token string */
char name[MAXTOKEN];        /* identifier name */
char datatype[MAXTOKEN];    /* data type = char, int, etc. */
char out[1000];             /* output string */
char *func_parameter_out[100]; /* array of strings for function parameters */
char **static_fp;                  /* pointer for func_parameter_out */
char *func_datatype[100];   /* array of strings for function datatypes */
char **static_fd;                  /* pointer for func_datatype */

/* Convert declaration syntax into plain words */
int main(void)
{
    while(gettoken() != EOF)
    {
        static_fp = func_parameter_out; //NEED TO REFRESH THIS EACH TIME
        static_fd = func_datatype;
        strcpy(datatype, token);    /* 1st token on line is the data type */
        if(strcmp(datatype, "const")==0)
        {
            if(gettoken()==NAME)
            {
                strcat(datatype, " ");
                strcat(datatype, token);
            }
            else
            {
                printf("error: datatype must be a valid variable name\n");
                error = 1;
            }
        }
        if(!isalpha(datatype[0]))   /* if datatype isn't a variable name, process error */
        {
            printf("error: datatype must be a valid variable name\n");
            error = 1;
        }
        out[0] = '\0';
        dcl();                      /* parse rest of line */
        while(tokentype == ' ' || tokentype == '\t')
        {
            tokentype = getch();
        }
        if(tokentype != '\n' || error > 0)
        {
            while(tokentype!='\n')
            {
                tokentype = getch();
            }
            printf("syntax error\n");
            error = 0;
        }
        else
        {
            printf("%s: %s %s\n", name, out, datatype);
        }
        token[0] = '\0';            /* refresh token for next input line */
    }
    return 0;
}

void function_parameter(void)
{
    char **fp = ++static_fp;
    char **fd = ++static_fd;
    strcat(out, " function {");
    strcpy(*fd, token);
    if(strcmp(*fd, "const")==0)
    {
        if(gettoken()==NAME)
        {
            strcat(*fd, " ");
            strcat(*fd, token);
        }
        else
        {
            printf("error: datatype must be a valid variable name\n");
            error = 1;
        }
    }
    if(!isalpha((*fd)[0]))   /* if datatype isn't a variable name, process error */
    {
        printf("error: datatype must be a valid variable name\n");
        error = 1;
    }
    dcl();
    if(tokentype == ',')
    {
        strcat(*fp, ", ");
        function_parameter();
    }
    if(tokentype != ')')
    {
            printf("error: missing )\n");
            error = 1;
            return;
    }
    strcat(out, *fp);
    strcat(out, "} returning");
}

/* dcl: parse a declarator */
void dcl(void)
{
    int ns;

    for(ns=0; gettoken()=='*'; ) /* count # of *'s */
    {
        ns++;
    }
    dirdcl();
    while(ns-- > 0)
    {
        strcat((var_name_found ? *static_fp : out), " pointer to");
    }
}

/* dirdcl: parse a direct declarator */
void dirdcl(void)
{
    int type;

    if(tokentype == '(') /* (dcl) */
    {
        dcl();
        if(tokentype != ')')
        {
            printf("error: missing )\n");
            error = 1;
            return;     /* don't allow dirdcl() to continue calling gettoken() below */
        }
    }
    else if(tokentype == NAME) /* variable name */
    {
        // if(var_name == 1) then run function_parameter()
            // at end of function_parameter(), need to strcat(out, " function i returning")
            // later, printf("function i:\n\t[parameter]\n\t[parameter]\n");
            // need to store the parameter strings in an array
        // else do this:
        if(var_name_found)
        {
            function_parameter();
        }
        else
        {
            strcpy(name, token);
            var_name_found = 1;
        }
        // var_name = 1;
        // PROBLEM: function_parameter() will call dirdcl() and overwrite name
        // Solution: replace name with "function ? name : *p"
    }
    else
    {
        printf("error: expected name or (dcl)\n");
        error = 1;
        return;         /* don't allow dirdcl() to continue calling gettoken() below */
    }

    while((type = gettoken()) == PARENS || type == BRACKETS)
    {
        if(type == PARENS)
        {
            strcat((var_name_found ? *static_fp : out), " function returning");
        }
        else
        {
            strcat((var_name_found ? *static_fp : out), " array");
            strcat((var_name_found ? *static_fp : out), token);
            strcat((var_name_found ? *static_fp : out), " of");
        }
    }
}

/* gettoken: return next token */
int gettoken(void)
{
    int c, getch(void);
    void ungetch(int);
    char *p = token;

    while((c=getch()) == ' ' || c == '\t')
    {
        ;
    }
    if(c=='(')
    {
        if((c=getch()) == ')')
        {
            strcpy(token, "()");
            return tokentype = PARENS;
        }
        else
        {
            ungetch(c);
            return tokentype = '(';
        }
    }
    else if(c == '[')
    {
        for(*p++ = c; (*p++ = getch()) != ']'; )
        {
            ;
        }
        *p = '\0';
        return tokentype = BRACKETS;
    }
    else if(isalpha(c))
    {
        for(*p++ = c; isalnum(c=getch()); )
        {
            *p++ = c;
        }
        *p = '\0';
        ungetch(c);
        return tokentype = NAME;
    }
    else return tokentype = c;
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