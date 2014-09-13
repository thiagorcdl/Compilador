/* Erros */
#define JA_DECL 104
#define NAO_DECL 103
#define INCOMPT 102


/* Tipos */
#define TVOID   0
#define TBOOL   1
#define TINT    2
#define TREAL   3
#define TCHAR   4
#define TSTR    5

enum enum_pass {
        PVAL=0, PREF=1
};

enum enum_cat {
        CVAR, CPROC, CPARAM, CLABEL
};

typedef struct Var{
    int tipo = TVOID;
    enum_pass pass = PVAL;
    int desloc;
} Var;

typedef struct Simbolo{
    char *ident;
    enum_cat cat;
    int nivel;

    union{
        Var var;
        struct{
            char *label;
            int n_param;
            Var *params;
        };
    };
    Simbolo *abaixo = NULL;
} Simbolo;

typedef struct Pilha{
    int val;
    Pilha *abaixo;
} Pilha;

void push(Pilha *, int);
int pop(Pilha *);
void cmpT(int);
Simbolo* insereS(Simbolo *, Simbolo *);
Simbolo* eliminaS(Simbolo *, int);
Simbolo* buscaS(Simbolo *, char *);
void erro(int,char *);
