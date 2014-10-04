#define debug(STR) printf("@ %s \n", STR); fflush(stdout)
#define TAM_TOKEN 16

/* Erros */
#define INCOMPT 108
#define ATRIB 107
#define TPARAM 106
#define NPARAM 105
#define JA_DECL 104
#define VN_DECL 103
#define PN_DECL 102
#define FN_DECL 101


/* Tipos */
#define TVOID   0
#define TBOOL   1
#define TINT    2
#define TREAL   3
#define TCHAR   4
#define TSTR    5

typedef enum enum_pass {
        PVAL=0, PREF=1
}enum_pass;

typedef enum enum_cat {
        CVAR, CPROC, CFUNC, CPARAM, CLABEL
}enum_cat;

typedef struct Var{
    int tipo;
    enum_pass pass;
    int desloc;
} Var;

typedef struct Simbolo{
    char ident[TAM_TOKEN];
    enum_cat cat;
    int nivel;

    union{
        // Vars e params usam:
        Var var;
        // Procedures usam:
        struct{
            int label;
            int num_params;
            Var *params;
        };
    };
    struct Simbolo *abaixo;
} Simbolo;

typedef struct PilhaInt{
    int val;
    struct PilhaInt *abaixo;
} PilhaInt;


typedef struct PilhaProc{
    Simbolo *proc;
    struct PilhaProc *abaixo;
} PilhaProc;


/* Simbolos */
Simbolo* pushSimb(Simbolo *, Simbolo *);
Simbolo* rmSimb(Simbolo *, int);
Simbolo* buscaSimb(Simbolo *, char *);
Simbolo* criaSimb(char *ident);

/* Integer (labels, tipos)*/
void pushInt(PilhaInt **, int);
int popInt(PilhaInt **);
void cmpTipo(int);

/* Procedures e functions */
void pushProc(Simbolo* p);
Simbolo* popProc();

void erro(int);


Simbolo *tabela, *s, *p, *esq;
PilhaInt *tipos, *rotulos, *string, *nvars, *nparams;
PilhaProc *procs;
