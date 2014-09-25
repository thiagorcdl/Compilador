/*
 *  Thiago Roscia Cerdeiro de Lima
 *  GRR20105251
 *  trcl10@inf
 *
 */

%{
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include "pilhas.h"
#include "compilador.h"


#define argCodigo(str,a)    sprintf(cod,"%s %d",str,a);\
                            geraCodigo(NULL,cod)

#define argsCodigo(str,a1,a2)   sprintf(cod,"%s %d,%d",str,a1,a2);\
                                geraCodigo(NULL,cod)

#define rotCodigo(r)    sprintf(cod,"R%02d",r);\
                        geraCodigo(cod,"NADA")

#define desvCodigo(str,r)   sprintf(cod,"%s R%02d",str,r);\
                            geraCodigo(NULL,cod)
                        

int num_idents, num_params;
int i, j, rotulo, len;
Simbolo *tabela, *s, *p, *esq;
char cod[32],rot[16];
int desloc = 0, nivel_lexico = 0;


void varCodigo(Simbolo *s, int param){
    if(!param){
        if(s->var.pass == PREF)
            argsCodigo("CRVI",s->nivel,s->var.desloc);
        else
            argsCodigo("CRVL",s->nivel,s->var.desloc);
    } else {
        if(param > p->num_params) 
            erro(NPARAM);
        param--;
        if(s->var.pass == PREF){
            if(p->params[param] == PREF)
                argsCodigo("CRVL",s->nivel,s->var.desloc);
            else
                argsCodigo("CRVI",s->nivel,s->var.desloc);
        } else {
            if(p->params[param] == PREF)
                argsCodigo("CREN",s->nivel,s->var.desloc);
            else
                argsCodigo("CRVL",s->nivel,s->var.desloc);
        }
    }
    return;
}

%}

%token PROGRAM ABRE_PARENTESES FECHA_PARENTESES 
%token VIRGULA PONTO_E_VIRGULA DOIS_PONTOS PONTO
%token T_BEGIN T_END VAR IDENT ATRIBUICAO

%token LABEL TYPE ARRAY OF PROCEDURE FUNCTION 
%token GOTO IF THEN ELSE WHILE DO OR AND NUMERO
%token NOT DIV MULT MAIS MENOS T_TRUE T_FALSE
%token MAIOR MENOR MAIOR_IGUAL MENOR_IGUAL DIFF
%token INT STR CHAR BOOL IGUAL READ WRITELN ASPAS

%%

programa:   {   rotulo = 0; nl=1;
                tabela = NULL; tipos = NULL; string = NULL;
                geraCodigo(NULL, "INPP");
                desvCodigo("DSVS",rotulo); push(&rotulos,rotulo++);}
                PROGRAM IDENT 
                ABRE_PARENTESES lista_idents FECHA_PARENTESES PONTO_E_VIRGULA
                bloco PONTO { geraCodigo (NULL, "PARA"); }
;

bloco:      {  }
                parte_declara_vars
                comando_composto
            {   argCodigo("DMEM",pop(&nvars));}
;


parte_declara_vars:     VAR { desloc=0; }
                        declara_vars
                    {   argCodigo("AMEM",desloc);
                        push(&nvars,desloc);}
                    |
;

declara_vars: declara_vars declara_var 
            | declara_var 
;

declara_var : { num_idents=0;} 
              lista_id_var DOIS_PONTOS 
              tipo { s = tabela; 
                     for(i=0; i < num_idents; i++){
                        s->var.tipo = (!strcmp("integer",token)?TINT:TBOOL);
                        s = s->abaixo;
                     }}
              PONTO_E_VIRGULA
;

tipo        :   BOOL
            |   INT
            |   CHAR
            |   STR
;

lista_id_var: lista_id_var VIRGULA IDENT 
              { s = criaS();
                s->cat = CVAR;
                s->var.desloc = desloc++;
                tabela = insereS(tabela,s);
                num_idents++;}
            | IDENT {   s = criaS();
                        s->cat = CVAR;
                        s->var.desloc = desloc++;
                        tabela = insereS(tabela,s);
                        num_idents++;}
;

lista_idents: lista_idents VIRGULA IDENT  
            | IDENT
;

if     : if_then cond_else { rotCodigo(pop(&rotulos)); }
;

if_then     :   IF expr { desvCodigo("DSVF",rotulo++); push(&rotulos,rotulo++);}
                THEN comando_sem_rotulo { desvCodigo("DSVS",rotulos->val);
                                          rotCodigo(rotulos->val-1);}
;

cond_else   :   ELSE { }
                comando_sem_rotulo
                | 
;

while:  WHILE { rotCodigo(rotulo++); }
        expr { desvCodigo("DSVF",rotulo); push(&rotulos,rotulo++);}
        DO comando_sem_rotulo { desvCodigo("DSVS",rotulos->val - 1);
                                rotCodigo(pop(&rotulos));}
;

comando_composto: T_BEGIN comandos T_END 
;

comandos:   comandos PONTO_E_VIRGULA comando
            | comando
;

comando:    numero comando_sem_rotulo
            | comando_composto 
;

numero:     NUMERO DOIS_PONTOS
            |
;

comando_goto:   GOTO IDENT
;

comando_sem_rotulo : atrib
                   | while
                   | if
                   | comando_goto
                   | comando_composto
                   | ch_proc
                   | io
;

atrib:  var {esq = s; }
        ATRIBUICAO exprs {  cmpT(TVOID);
                            argsCodigo("ARMZ",esq->nivel,esq->var.desloc);}
;

expr:       exprs DIFF exprs    {   cmpT(TVOID); push(&tipos,TBOOL);
                                    geraCodigo(NULL,"CMDG");}
        |   exprs IGUAL exprs   {   cmpT(TVOID); push(&tipos,TBOOL);
                                    geraCodigo(NULL,"CMIG");}
        |   exprs MENOR exprs   {   cmpT(TINT);  push(&tipos,TBOOL);
                                    geraCodigo(NULL,"CMME");}
        |   exprs MAIOR exprs   {   cmpT(TINT);  push(&tipos,TBOOL);
                                    geraCodigo(NULL,"CMMA");}
        |   exprs MENOR_IGUAL exprs   { cmpT(TINT); push(&tipos,TBOOL);
                                        geraCodigo(NULL,"CMEG");}
        |   exprs MAIOR_IGUAL exprs   { cmpT(TINT); push(&tipos,TBOOL);
                                        geraCodigo(NULL,"CMAG");}
        |   exprs
;

exprs:      exprs MAIS termo    {   cmpT(TINT); push(&tipos,TINT);
                                    geraCodigo(NULL,"SOMA");}
        |   exprs MENOS termo   {   cmpT(TINT); push(&tipos,TINT);
                                    geraCodigo(NULL,"SUBT");}
        |   exprs OR termo      {   cmpT(TBOOL); push(&tipos,TBOOL);
                                    geraCodigo(NULL,"CONJ");} 
        |   termo
;

termo:      NOT fator           {   push(&tipos,TBOOL); cmpT(TBOOL);
                                    push(&tipos,TBOOL); geraCodigo(NULL,"NEGA");}  
        |   fator MULT fator    {   cmpT(TINT); push(&tipos,TINT);
                                    geraCodigo(NULL,"MULT");}
        |   fator DIV fator     {   cmpT(TINT); push(&tipos,TINT);
                                    geraCodigo(NULL,"DIVI");}
        |   fator AND fator     {   cmpT(TBOOL); push(&tipos,TBOOL);
                                    geraCodigo(NULL,"DISJ");}
        |   fator
;


fator:      ABRE_PARENTESES expr FECHA_PARENTESES
        |   var     { varCodigo(s,0);}
        |   proc
        |   T_TRUE    { geraCodigo(NULL,"CRCT 1"); push(&tipos,TBOOL);}
        |   T_FALSE   { geraCodigo(NULL,"CRCT 0"); push(&tipos,TBOOL);}
        |   NUMERO  { argCodigo("CRCT",atoi(token));  push(&tipos,TINT);}
        
;


io:       read
        |   writeln
        |
;

read:   READ ABRE_PARENTESES var FECHA_PARENTESES
        {   pop(&tipos); geraCodigo(NULL,"LEIT");
            if(s->cat == CVAR)
                argsCodigo("ARMZ",s->nivel,s->var.desloc);
            else()}
;

writeln:  WRITELN ABRE_PARENTESES writelist FECHA_PARENTESES
        { argCodigo("CRCT",(int)'\n');
          argCodigo("TEXT",1);}
;

writelist:   writelist VIRGULA expr {pop(&tipos); geraCodigo(NULL,"IMPR");}
            | writelist VIRGULA string
            | string
            | expr {pop(&tipos); geraCodigo(NULL,"IMPR");}
;

string:  {len = 0;} texto 
        { for(i=0; i < len; i++){
              j = pop(&string);
              argCodigo("CRCT",j);
          }
          argCodigo("TEXT",len);}
;



texto:    STR { for(i=0; i < strlen(texto); i++){
                    len++;
                    if(texto[i]=='\\' && i < strlen(texto)-1){
                        i++;
                        if(texto[i] == 'n')
                            push(&string,(int)'\n');
                        else if(texto[i] == 't')
                            push(&string,(int)'\t');
                        else if(texto[i] == '0'){
                            push(&string,(int)'\0');
                            break;
                        } else if(texto[i] == '\'')
                            push(&string,(int)'\'');
                        else if(texto[i] == '\"')
                            push(&string,(int)'\"');
                        else if(texto[i] == '\\')
                            push(&string,(int)'\\');
                        else {
                            push(&string,(int)'\\');
                            i--;
                        }
                    } else if (texto[i] == '\"')
                        len--;
                    else
                        push(&string,(int)texto[i]);
                }}
;


subrotina: decl_proc | decl_func
;

decl_proc:      PROCEDURE {     geraCodigo(rotulo,"NADA");
                                nivel_lexico++;
                                p = criaS();
                                p->cat = CPROC;
                                p->label = rotulo++;
                                insereS(tabela,p);
                                argCodigo("ENPR",nivel_lexico);} 
                IDENT params 
                PONTO_E_VIRGULA bloco
                {   s = tabela;
                    // Remove local vars, params e procedures de nl maior
                    while(s->cat != CPROC || s->nivel > nivel_lexico)
                        s = s->abaixo;
                    tabela = s;
                    argCodigo("DMEM",nvars->val);
                    argsCodigo("RTPR",nivel_lexico,pop(&nvars));
                    }
;


decl_func:
;

params_formais:     ABRE_PARENTESES {   desloc = 0; }
                    decl_params FECHA_PARENTESES
                    {   s = tabela; 
                        p->params = malloc(desloc * sizeof(Var));
                        for(i=0; i < desloc; i++){
                            s->desloc = -(4 + i);
                            p->params[i].desloc = s->desloc;
                            p->params[i].pass = s->pass;
                            p->params[i].tipo = s->tipo;
                            s = s->abaixo;
                        }
                        p->num_params = desloc;
                        }
                |   
;

decl_params:        decl_params PONTO_E_VIRGULA params
                |   params
;

params:         {num_idents = 0;}  VAR lista_id_vars DOIS_PONTOS IDENT
                { // por ref
                 s = tabela; 
                 for(i=0; i < num_idents; i++){
                    s->cat = CPARAM;
                    s->var.pass = PREF;
                    s->var.tipo = (!strcmp("integer",token)?TINT:TBOOL);
                    s = s->abaixo;
                 }}
            |   {num_idents = 0;}  lista_id_vars DOIS_PONTOS IDENT
                { // por valor
                 s = tabela; 
                 for(i=0; i < num_idents; i++){
                    s->cat = CPARAM;
                    s->var.pass = PVAL;
                    s->var.tipo = (!strcmp("integer",token)?TINT:TBOOL);
                    s = s->abaixo;
                 }}
;

ch_proc: IDENT {    p = buscaS(tabela,token);
                    if ( p == NULL ) erro(PN_DECL);
                    sprintf(cod,"CHPR R%02d",p->label);
                    argCodigo(cod,p->nivel); }
         ABRE_PARENTESES passa_params FECHA_PARENTESES PONTO_E_VIRGULA
;

var: IDENT { s = buscaS(tabela,token); 
             if ( s == NULL ) erro(PN_DECL);
             if (s->cat != CVAR && s->cat != CPARAM) erro(ATRIB);
             push(&tipos,s->var.tipo);}
;

%%

main (int argc, char** argv) {
   FILE* fp;
   extern FILE* yyin;

   if (argc<2 || argc>2) {
         printf("Usage:\n\t$ %s <file.pas>\n", argv[0]);
         return(100);
      }

   fp=fopen (argv[1], "r");
   if (fp == NULL) {
      printf("Usage:\n\t$ %s <file.pas>\n", argv[0]);
      return(100);
   }
    
    strcpy(codigo,argv[1]);

   yyin=fp;
   yyparse();

   return 0;
}

