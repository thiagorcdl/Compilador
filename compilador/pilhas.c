#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "tabela.h"
#include "compilador.h"

void push(Pilha *p, int val){
    Pilha *topo;
    topo->val = val;
    topo->abaixo = p;
    p = topo;
    return;
}

int pop(Pilha *p){
    Pilha *tmp;
    int val;
    tmp = p;
    val = p.val;
    p = p->abaixo;
    free(tmp);
    return val;
}

void cmpT(int operador){
    int a,b;
    a = pop(tipos);
    b = pop(tipos);
    if ((a != b) || (a != operador && operador))
        erro(INCOMPT);
    return;
}

Simbolo* insereS(Simbolo *pilha, Simbolo *s){
    Simbolo *exist;
    exist = busca(pilha,s->ident);
    if(exist && exist.cat == s.cat && exist.nivel == s.nivel)
        erro(JA_DECL);
    s->abaixo = pilha;
    return s;
}

Simbolo* eliminaS(Simbolo *pilha, int n){
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

Simbolo* buscaS(Simbolo *pilha, char *ident){
    Simbolo *atual;
    atual = pilha;
    do{
        if(!strcmp(atual->ident,ident))
            return atual;
        atual = atual->abaixo;
    }while(atual->abaixo != NULL);
    return NULL;
}

void erro(int e){
    char msg[64];
    switch (e):
        case JA_DECL:   sprintf(msg,"Variável \"%s\" já declarada.",token);
                        break;
        case NAO_DECL:  sprintf(msg,"Variável \"%s\" não declarada.",token);
                        break;
        case INCOMPT:   sprintf(msg,"Operação com tipos incompatíveis.");
                        break;
    fprintf(stderr,"Erro de compilação:\t%s\nAbortando.\n",msg);
    exit(1);
    return;
}

