
// Testar se funciona corretamente o empilhamento de parâmetros
// passados por valor ou por referência.


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
                        

int nvars, i, j, rotulo;
Simbolo *topo, *s, *esq;
char cod[32],rot[16];
int desloc = 0;
int nivel_lexico = -1;
%}

%token PROGRAM ABRE_PARENTESES FECHA_PARENTESES 
%token VIRGULA PONTO_E_VIRGULA DOIS_PONTOS PONTO
%token T_BEGIN T_END VAR IDENT ATRIBUICAO

%token LABEL TYPE ARRAY OF PROCEDURE FUNCTION 
%token GOTO IF THEN ELSE WHILE DO OR AND NUMERO
%token NOT DIV MULT MAIS MENOS T_TRUE T_FALSE
%token MAIOR MENOR MAIOR_IGUAL MENOR_IGUAL DIFF
%token INT STR CHAR BOOL IGUAL READ WRITE

%%

programa    :{  geraCodigo (NULL, "INPP");
                rotulo = 0;
                topo = NULL; tipos = NULL; }
             PROGRAM IDENT 
             ABRE_PARENTESES lista_idents FECHA_PARENTESES PONTO_E_VIRGULA
             bloco PONTO { geraCodigo (NULL, "PARA"); }
;

bloco       : {nivel_lexico++;} parte_declara_vars
              comando_composto {nivel_lexico--; argCodigo("DMEM",desloc);}
;


parte_declara_vars: VAR { desloc=0; }
                    declara_vars { argCodigo("AMEM",desloc);}
                    |
;

declara_vars: declara_vars declara_var 
            | declara_var 
;

declara_var : { nvars=0;} 
              lista_id_var DOIS_PONTOS 
              tipo { s = topo; 
                     for(i=0; i < nvars; i++){
                        s->var.tipo = (!strcmp("integer",token)?2:1);
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
                topo = insereS(topo,s);
                nvars++;}
            | IDENT {   s = criaS();
                        s->cat = CVAR;
                        s->var.desloc = desloc++;
                        topo = insereS(topo,s);
                        nvars++;}
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
                   | proc
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
        |   var     { argsCodigo("CRVL",s->nivel,s->var.desloc);}
        |   proc
        |   T_TRUE    { geraCodigo(NULL,"CRCT 1"); push(&tipos,TBOOL);}
        |   T_FALSE   { geraCodigo(NULL,"CRCT 0"); push(&tipos,TBOOL);}
        |   NUMERO  { argCodigo("CRCT",atoi(token));  push(&tipos,TINT);}
        
;


read:   READ ABRE_PARENTESES var FECHA_PARENTESES
        {   pop(&tipos); geraCodigo(NULL,"LEIT");
            argsCodigo("ARMZ",s->nivel,s->var.desloc);}
;

write:  WRITE ABRE_PARENTESES expr FECHA_PARENTESES
        {pop(&tipos); geraCodigo(NULL,"IMPR");}
;

proc:       read
        |   write
        |
;

var: IDENT { s = buscaS(topo,token); 
             if ( s == NULL ) erro(NAO_DECL);
             push(&tipos,s->var.tipo);}
;

%%

main (int argc, char** argv) {
   FILE* fp;
   extern FILE* yyin;

   if (argc<2 || argc>2) {
         printf("Usage:\n\t$ %s <file.pas>\n", argv[0]);
         return(-1);
      }

   fp=fopen (argv[1], "r");
   if (fp == NULL) {
      printf("Usage:\n\t$ %s <file.pas>\n", argv[0]);
      return(-1);
   }


/* -------------------------------------------------------------------
 *  Inicia a Tabela de Símbolos
 * ------------------------------------------------------------------- */

   yyin=fp;
   yyparse();

   return 0;
}

