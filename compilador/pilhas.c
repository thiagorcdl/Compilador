#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "pilhas.h"
#include "compilador.h"

void pushInt(PilhaInt **p, int val){
    PilhaInt *topo;
    topo = malloc(sizeof(PilhaInt));
    topo->val = val;
    topo->abaixo = (*p);
    *p = topo;
    return;
}

int popInt(PilhaInt **p){
    PilhaInt *tmp;
    int val;
    tmp = (*p);
    val = (*p)->val;
    *p = (*p)->abaixo;
    free(tmp);
    return val;
}

void cmpTipo(int operador){
    int a,b;
    a = popInt(&tipos);
    b = popInt(&tipos);
    if ((a != b) || (a != operador && operador))
        erro(INCOMPT);
    return;
}

Simbolo* pushSimb(Simbolo *pilha, Simbolo *s){
    Simbolo *exist;
    if (pilha){
        exist = buscaSimb(pilha,s->ident);
        if(exist && exist->cat == s->cat && exist->nivel == s->nivel)
            erro(JA_DECL);
    }
    s->abaixo = pilha;
    return s;
}

Simbolo* rmSimb(Simbolo *pilha, int n){
    int i;
    Simbolo *topo, *atual;
    atual = pilha;
    for (i=0; i < n; i++){
        topo = atual;
        atual = topo->abaixo;  
        free(topo);  
    }
    return atual;
}

Simbolo* buscaSimb(Simbolo *pilha, char *ident){
    Simbolo *atual;
    if(pilha == NULL) return NULL;
    atual = pilha;
    do{
        if(!strcmp(atual->ident,ident))
            return atual;
        atual = atual->abaixo;
    } while(atual != NULL);
    return NULL;
}

Simbolo *criaSimb(){
    Simbolo *s;
    s = malloc(sizeof(Simbolo));
    strcpy(s->ident,token); 
    s->nivel = nivel_lexico; 
    s->abaixo = NULL;
    s->var.tipo = TVOID;
    s->var.pass = PVAL;
    return s;
}

void pushProc(Simbolo* p){
    PilhaProc *topo;
    topo = malloc(sizeof(PilhaProc));
    topo->proc = p;
    topo->abaixo = procs;
    procs = topo;
    return;
}

Simbolo* popProc(){
    PilhaProc *tmp;
    Simbolo* p;
    tmp = procs;
    p = tmp->proc;
    procs = procs->abaixo;
    free(tmp);
    return p;
}

void erro(int e){
    char msg[64], cmd[64];
    if (e < 100){
         sprintf(msg,"Parâmetro %d de \"%s\" deve ser endereço válido."
                    ,e,p->ident);
        e = 110;
    }
    switch (e){
        case ATRIB:     sprintf(msg,"Recipiente \"%s\" inválido para\
                                     atribuição.",token);
                        break;
        case TPARAM:    sprintf(msg,"Tipo do parâmetro \"%s\" não compatível\
                                    com assinatura de \"%s\".",token,p->ident);
                        break;
        case NPARAM:    sprintf(msg,"Número de parâmetros não coincide\
                                    com assinatura de \"%s\".",p->ident);
                        break;
        case JA_DECL:   sprintf(msg,"Identificador \"%s\" já declarado.",token);
                        break;
        case VN_DECL:  sprintf(msg,"Variável \"%s\" não declarada.",token);
                        break;
        case PN_DECL:  sprintf(msg,"Variável \"%s\" não declarada.",token);
                        break;
        case INCOMPT:   sprintf(msg,"Operação com tipos incompatíveis.");
                        break;
    }
    sprintf(cmd,"tail -%d %s | head -1 | tr -s \" \" | tr -s \"\\t\" >&2",
            nl,codigo);
    fprintf(stderr,"\n!# Erro de compilação (linha %d):\n",nl);
    system(cmd);
    fprintf(stderr,"\n#\t%s\n# Abortando.\n\n",msg);
    exit(e);
    return;
}

