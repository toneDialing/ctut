#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAXTOKEN 100
#define MAXPARAMETER 100
#define MAXOUTPUT 10000

/* Added error recovery, so program can properly handle next input line upon encountering an error.
*   Error messaging is mildly redundant, but I don't think that's a problem. Cascading errors
*   are normal in compiling anyway. */
/* Added const qualifiers */
/* Added function argument types */

enum {NAME, PARENS, BRACKETS, PARAMETER};

/* Functions listed in order of descending nesting */
void dcl(void);
void dirdcl(void);
void parameter(void);
void para_dcl(void);
void dirpara_dcl(void);

int gettoken(void);
int getch(void);
void ungetch(int);
int tokentype;              /* type of last token */
int error;                  /* notifies presence of syntax error */
int name_found;             /* notifies whether variable name is already found */
int parameter_call;         /* notifies whether parameter() has been called */
int parameter_count;        /* tracks which parameter is being evaluated */
char token[MAXTOKEN];       /* last token string */
char name[MAXTOKEN];        /* identifier name */
char datatype[MAXTOKEN];    /* data type = char, int, etc. */
char out[MAXOUTPUT];        /* output string */
char *p_datatype[MAXPARAMETER];      /* array of strings for parameter datatypes */
char *p_out[MAXPARAMETER];           /* array of strings for parameter output */

/* Convert declaration syntax into plain words */
int main(void)
{
    while(gettoken() != EOF)
    {
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
        token[0] = '\0';            /* refresh tokens etc. for next input line */
        for(int i=0; parameter_call && i<=parameter_count; i++)
        {
            /* If i>parameter_count this would cause a segmentation fault, since those elements of
                p_datatype and p_out were never defined. And if parameter_call were 0, then no
                elements of p_datatype and p_out would have been defined in the first place. */
            *p_datatype[i] = '\0';
            *p_out[i] = '\0';
        }
        parameter_count = 0;
        parameter_call = 0;
        name_found = 0;
    }
    return 0;
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
        strcat(out, " pointer to");
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
        strcpy(name, token);
        name_found = 1;
    }
    else
    {
        printf("error: expected name or (dcl)\n");
        error = 1;
        return;         /* don't allow dirdcl() to continue calling gettoken() below */
    }

    while((type = gettoken()) == PARENS || type == BRACKETS || type == PARAMETER)
    {
        if(type == PARENS)
        {
            strcat(out, " function returning");
        }
        else if(type == PARAMETER)
        {
            strcat(out, " function {");
            parameter_call = 1; /* parameter_call only exists to avoid seg faults; see main() */
            int bookmark = parameter_count; /* temp tracker of parameter_count at this moment */
            parameter();
            strcat(out, p_out[bookmark]);
            strcat(out, "} returning");
        }
        else
        {
            strcat(out, " array");
            strcat(out, token);
            strcat(out, " of");
        }
    }
}

void parameter(void)
{
    int local_parameter_count = parameter_count;
        /* keeps track of parameter_count within this specific call */
    char alloc_data[MAXTOKEN], alloc_out[MAXTOKEN];
    p_datatype[parameter_count] = alloc_data;
    p_out[parameter_count] = alloc_out;

    gettoken();
    strcpy(p_datatype[parameter_count], token);    /* 1st token on line is the data type */
    if(strcmp(p_datatype[parameter_count], "const")==0)
    {
        if(gettoken()==NAME)
        {
            strcat(p_datatype[parameter_count], " ");
            strcat(p_datatype[parameter_count], token);
        }
        else
        {
            printf("error: datatype must be a valid variable name\n");
            error = 1;
        }
    }
    if(!isalpha(*p_datatype[parameter_count]))   /* if datatype isn't a variable name, process error */
    {
        printf("error: datatype must be a valid variable name\n");
        error = 1;
    }
    *p_out[parameter_count] = '\0';
    para_dcl();
    while(tokentype == ' ' || tokentype == '\t')
    {
        tokentype = getch();
    }
    if(tokentype == ',')
    {
        parameter_count++;
        int next_parameter = parameter_count;
        parameter();
        strcat(p_out[local_parameter_count], p_datatype[local_parameter_count]);
        strcat(p_out[local_parameter_count], ", ");
        strcat(p_out[local_parameter_count], p_out[next_parameter]);
    }
    else
    {
        strcat(p_out[local_parameter_count], p_datatype[local_parameter_count]);
    }
    if(tokentype != ')')
    {
        printf("error: expected ')' in function parameter\n");
        error = 1;
    }
}

void para_dcl(void)
{
    int ns;

    for(ns=0; gettoken()=='*'; ) /* count # of *'s */
    {
        ns++;
    }
    dirpara_dcl();
    while(ns-- > 0)
    {
        strcat(p_out[parameter_count], "pointer to ");
    }
}

void dirpara_dcl(void)
{
    int type;

    if(tokentype == '(') /* (para_dcl) */
    {
        para_dcl();
        if(tokentype != ')')
        {
            printf("error: missing )\n");
            error = 1;
            return;     /* don't allow dirpara_dcl() to continue calling gettoken() below */
        }
    }
    /* Because dirpara_dcl can be empty, we must check for each condition in the while loop below
        before calling gettoken() again */
    else if(tokentype == PARENS)
    {
        strcat(p_out[parameter_count], "function returning ");
    }
    else if(tokentype == PARAMETER)
    {
        strcat(p_out[parameter_count], "function {");
        int bookmark = parameter_count; /* temp tracker of parameter_count at this moment */
        parameter_count++;
        parameter();
        strcat(p_out[bookmark], p_out[bookmark+1]);
        strcat(p_out[bookmark], "} returning ");
    }
    else if(tokentype == BRACKETS)
    {
        strcat(p_out[parameter_count], "array");
        strcat(p_out[parameter_count], token);
        strcat(p_out[parameter_count], " of ");
    }
    else if(tokentype == ')' || tokentype == ',') /* dirpara_dcl is empty */
    {
        return;
    }

    while((type=gettoken()) == PARENS || type == BRACKETS || type == PARAMETER)
    {
        if(type == PARENS)
        {
            strcat(p_out[parameter_count], "function returning ");
        }
        else if(type == BRACKETS)
        {
            strcat(p_out[parameter_count], "array");
            strcat(p_out[parameter_count], token);
            strcat(p_out[parameter_count], " of ");
        }
        else
        {
            strcat(p_out[parameter_count], "function {");
            int bookmark = parameter_count; /* temp tracker of parameter_count at this moment */
            parameter_count++;
            parameter();
            strcat(p_out[bookmark], p_out[bookmark+1]);
            strcat(p_out[bookmark], "} returning ");
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
        else if(name_found && isalpha(c))
        {
            ungetch(c);
            return tokentype = PARAMETER;
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