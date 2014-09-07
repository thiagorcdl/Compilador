
// Testar se funciona corretamente o empilhamento de par�metros
// passados por valor ou por refer�ncia.


%{
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include "compilador.h"

int num_vars;

%}

%token PROGRAM ABRE_PARENTESES FECHA_PARENTESES 
%token VIRGULA PONTO_E_VIRGULA DOIS_PONTOS PONTO
%token T_BEGIN T_END VAR IDENT ATRIBUICAO

%token LABEL TYPE ARRAY OF PROCEDURE FUNCTION 
%token GOTO IF THEN ELSE WHILE DO OR AND
%token NOT DIV MULT MAIS MENOS T_BOOL

%nonassoc LOWER_THAN_ELSE
%nonassoc ELSE
%%

programa    :{ 
             geraCodigo (NULL, "INPP"); 
             }
             PROGRAM IDENT 
             ABRE_PARENTESES lista_idents FECHA_PARENTESES PONTO_E_VIRGULA
             bloco PONTO {
             geraCodigo (NULL, "PARA"); 
             }
;

bloco       : 
              parte_declara_vars
              { 
              }

              comando_composto 
              ;




parte_declara_vars:  var 
;


var         : { } VAR declara_vars
            |
;

declara_vars: declara_vars declara_var 
            | declara_var 
;

declara_var : { } 
              lista_id_var DOIS_PONTOS 
              tipo 
              { /* AMEM */
              }
              PONTO_E_VIRGULA
;

tipo        : IDENT
;

lista_id_var: lista_id_var VIRGULA IDENT 
              { /* insere �ltima vars na tabela de s�mbolos */ }
            | IDENT { /* insere vars na tabela de s�mbolos */}
;

lista_idents: lista_idents VIRGULA IDENT  
            | IDENT
;
/*
cond_if     : if_then cond_else 
            { 
              em_if_finaliza (); 
            }
;

if_then     : IF expressao 
            {
              em_if_apos_expr ();
            }
             THEN comando_sem_rotulo
            {
              em_if_apos_then ();
            }
;

cond_else   : ELSE comando_sem_rotulo
            | %prec LOWER_THAN_ELSE
;*/

comando_composto: T_BEGIN comandos T_END 

comandos:    
;
/*
comando_sem_rotulo : atrib_ou_cp
                   | rep_while
                   | cond_if
                   | comando_goto
                   | comando_composto
;
*/
%%

main (int argc, char** argv) {
   FILE* fp;
   extern FILE* yyin;

   if (argc<2 || argc>2) {
         printf("usage compilador <arq>a %d\n", argc);
         return(-1);
      }

   fp=fopen (argv[1], "r");
   if (fp == NULL) {
      printf("usage compilador <arq>b\n");
      return(-1);
   }


/* -------------------------------------------------------------------
 *  Inicia a Tabela de S�mbolos
 * ------------------------------------------------------------------- */

   yyin=fp;
   yyparse();

   return 0;
}

