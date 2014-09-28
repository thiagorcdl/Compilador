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
#include "compilador.h"
#include "pilhas.h"


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
char cod[32],rot[16];
int desloc = 0, nivel_lexico = 0;

/* Decide tipo de empilhamento baseado na variavel e param esperado*/
void varCodigo(Simbolo *s, int param){
    if(!param){
        if(s->var.pass == PREF){
            argsCodigo("CRVI",s->nivel,s->var.desloc);
        } else {
            argsCodigo("CRVL",s->nivel,s->var.desloc);
        }
    } else {
        if(param > p->num_params) 
            erro(NPARAM);
        param--;
        if(s->var.pass == PREF){
            if(p->params[param].pass == PREF){
                argsCodigo("CRVL",s->nivel,s->var.desloc);
            } else {
                argsCodigo("CRVI",s->nivel,s->var.desloc);
            }
        } else {
            if(p->params[param].pass == PREF){
                argsCodigo("CREN",s->nivel,s->var.desloc);
            } else {
                argsCodigo("CRVL",s->nivel,s->var.desloc);
            }
        }
    }
    return;
}


%}

%token PROGRAM ABRE_PARENTESES FECHA_PARENTESES 
%token VIRGULA PONTO_E_VIRGULA DOIS_PONTOS PONTO
%token T_BEGIN T_END VAR IDENT ATRIBUICAO ASPAS

%token LABEL TYPE ARRAY OF PROCEDURE FUNCTION 
%token GOTO IF THEN ELSE WHILE DO OR AND NUMERO
%token NOT DIV MULT MAIS MENOS T_TRUE T_FALSE
%token MAIOR MENOR MAIOR_IGUAL MENOR_IGUAL DIFF
%token INT STR CHAR BOOL IGUAL READ WRITE WRITELN

%%

/* Inicializa variaveis globais */
programa:   {   rotulo = 0; nl=1;
                tabela = NULL; tipos = NULL; string = NULL;
                geraCodigo(NULL, "INPP");}
                PROGRAM IDENT 
                ABRE_PARENTESES lista_idents FECHA_PARENTESES PONTO_E_VIRGULA
                bloco PONTO {   argCodigo("DMEM",popInt(&nvars));
                                geraCodigo (NULL, "PARA"); }
;

bloco:      {  }
                parte_declara_vars 
            {   desvCodigo("DSVS",rotulo); pushInt(&rotulos,rotulo++);}
                parte_declara_proc
            {   rotCodigo(popInt(&rotulos));}
                comando_composto 
;

/* DECLARAÇÃO DE VARIÁVEIS */
parte_declara_vars:     VAR { desloc=0; }
                        declara_vars
                    {   argCodigo("AMEM",desloc);
                        pushInt(&nvars,desloc);}
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
              { s = criaSimb();
                s->cat = CVAR;
                s->var.desloc = desloc++;
                tabela = pushSimb(tabela,s);
                num_idents++;}
            | IDENT {   s = criaSimb();
                        s->cat = CVAR;
                        s->var.desloc = desloc++;
                        tabela = pushSimb(tabela,s);
                        num_idents++;}
;

lista_idents: lista_idents VIRGULA IDENT  
            | IDENT
;


/* DESVIO CONDICIONAL */
if     : if_then cond_else { rotCodigo(popInt(&rotulos)); }
;

if_then     :   IF expr { desvCodigo("DSVF",rotulo++); pushInt(&rotulos,rotulo++);}
                THEN comando_sem_rotulo { desvCodigo("DSVS",rotulos->val);
                                          rotCodigo(rotulos->val-1);}
;

cond_else   :   ELSE { }
                comando_sem_rotulo
                | 
;


/* WHILE */
while:  WHILE { rotCodigo(rotulo++); }
        expr { desvCodigo("DSVF",rotulo); pushInt(&rotulos,rotulo++);}
        DO comando_sem_rotulo { desvCodigo("DSVS",rotulos->val - 1);
                                rotCodigo(popInt(&rotulos));}
;


/* COMANDOS */
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

comando_goto:   GOTO IDENT {sprintf(cod,"DSVS %s",token);
                            geraCodigo(NULL,cod);}
;

comando_sem_rotulo : atrib 
                   | while
                   | if
                   | comando_goto
                   | comando_composto
                   | ch_proc
                   | io
;

atrib:  var { esq = s; 
              if (s->cat != CVAR && s->cat != CPARAM)
                  erro(ATRIB);}
        ATRIBUICAO exprs {  cmpTipo(TVOID);
                            argsCodigo("ARMZ",esq->nivel,esq->var.desloc);}
;

/* EXPRESSÕES */
expr:       exprs DIFF exprs    {   cmpTipo(TVOID); pushInt(&tipos,TBOOL);
                                    geraCodigo(NULL,"CMDG");}
        |   exprs IGUAL exprs   {   cmpTipo(TVOID); pushInt(&tipos,TBOOL);
                                    geraCodigo(NULL,"CMIG");}
        |   exprs MENOR exprs   {   cmpTipo(TINT);  pushInt(&tipos,TBOOL);
                                    geraCodigo(NULL,"CMME");}
        |   exprs MAIOR exprs   {   cmpTipo(TINT);  pushInt(&tipos,TBOOL);
                                    geraCodigo(NULL,"CMMA");}
        |   exprs MENOR_IGUAL exprs   { cmpTipo(TINT); pushInt(&tipos,TBOOL);
                                        geraCodigo(NULL,"CMEG");}
        |   exprs MAIOR_IGUAL exprs   { cmpTipo(TINT); pushInt(&tipos,TBOOL);
                                        geraCodigo(NULL,"CMAG");}
        |   exprs
;

exprs:      exprs MAIS termo    {   cmpTipo(TINT); pushInt(&tipos,TINT);
                                    geraCodigo(NULL,"SOMA");}
        |   exprs MENOS termo   {   cmpTipo(TINT); pushInt(&tipos,TINT);
                                    geraCodigo(NULL,"SUBT");}
        |   exprs OR termo      {   cmpTipo(TBOOL); pushInt(&tipos,TBOOL);
                                    geraCodigo(NULL,"CONJ");} 
        |   termo
;

termo:      NOT fator           {   pushInt(&tipos,TBOOL); cmpTipo(TBOOL);
                                    pushInt(&tipos,TBOOL); geraCodigo(NULL,"NEGA");}  
        |   fator MULT fator    {   cmpTipo(TINT); pushInt(&tipos,TINT);
                                    geraCodigo(NULL,"MULT");}
        |   fator DIV fator     {   cmpTipo(TINT); pushInt(&tipos,TINT);
                                    geraCodigo(NULL,"DIVI");}
        |   fator AND fator     {   cmpTipo(TBOOL); pushInt(&tipos,TBOOL);
                                    geraCodigo(NULL,"DISJ");}
        |   fator
;


fator:      ABRE_PARENTESES expr FECHA_PARENTESES
        |   var     {   // Checa se variável está sendo passada para procedure
                        if (procs == NULL)
                            varCodigo(s,0);
                        else
                            varCodigo(s,nparams->val+1);}
        |   ch_proc
        |   T_TRUE    { geraCodigo(NULL,"CRCT 1"); pushInt(&tipos,TBOOL);}
        |   T_FALSE   { geraCodigo(NULL,"CRCT 0"); pushInt(&tipos,TBOOL);}
        |   NUMERO  { argCodigo("CRCT",atoi(token));  pushInt(&tipos,TINT);}
        
;

var: IDENT { s = buscaSimb(tabela,token);   
             if ( s == NULL ) erro(VN_DECL);
             pushInt(&tipos,s->var.tipo);}
;

/* DECLARAÇÃO DE PROCEDIMENTOS */
parte_declara_proc:    parte_declara_proc decl_proc
                    |
;

decl_proc:      PROCEDURE {     rotCodigo(rotulo); 
                                nivel_lexico++;
                                // Adiciona procedimento p à tabela
                                p = criaSimb();
                                p->cat = CPROC;
                                p->label = rotulo++;
                                tabela = pushSimb(tabela,p);
                                argCodigo("ENPR",nivel_lexico);} 
                IDENT params_formais
                PONTO_E_VIRGULA bloco
                {   s = tabela;
                    // Remove local vars, params e procedures de nl maior
                    while(s->cat != CPROC || s->nivel > nivel_lexico)
                        s = s->abaixo;
                    tabela = s; 
                    argCodigo("DMEM",nvars->val);
                    argsCodigo("RTPR",nivel_lexico,popInt(&nvars)); }
;


params_formais:     ABRE_PARENTESES {   desloc = 0; }
                    decl_params FECHA_PARENTESES
                    {   s = tabela; 
                        p->params = malloc(desloc * sizeof(Var));
                        // Copia params da tabela para a lista do procedimento
                        for(i=0; i < desloc; i++){
                            s->var.desloc = -(4 + i);
                            p->params[i].desloc = s->var.desloc;
                            p->params[i].pass = s->var.pass;
                            p->params[i].tipo = s->var.tipo;
                            s = s->abaixo;
                        }
                        p->num_params = desloc; }
                |   // Procedimento sem parametros
                |   ABRE_PARENTESES FECHA_PARENTESES
;

decl_params:        decl_params PONTO_E_VIRGULA params
                |   params
;

params:         {num_idents = 0;}  VAR lista_id_var DOIS_PONTOS IDENT
                { // Recebe por ref
                 s = tabela; 
                 for(i=0; i < num_idents; i++){
                    s->cat = CPARAM;
                    s->var.pass = PREF;
                    s->var.tipo = (!strcmp("integer",token)?TINT:TBOOL);
                    s = s->abaixo;
                 }}
            |   {num_idents = 0;}  lista_id_var DOIS_PONTOS IDENT
                { // Recebe por valor
                 s = tabela; 
                 for(i=0; i < num_idents; i++){
                    s->cat = CPARAM;
                    s->var.pass = PVAL;
                    s->var.tipo = (!strcmp("integer",token)?TINT:TBOOL);
                    s = s->abaixo;
                 }}
;


/* CHAMADA DE PROCEDIMENTOS */
ch_proc: IDENT  {   p = buscaSimb(tabela,token); 
                    if ( p == NULL ) erro(PN_DECL);
                    pushProc(p);
                    pushInt(&nparams,0);}
         ABRE_PARENTESES passa_ou_nao FECHA_PARENTESES
                {   p = popProc();
                    num_params = popInt(&nparams);
                    if (num_params < p->num_params)
                        erro(NPARAM);
                    sprintf(cod,"CHPR R%02d",p->label);
                    argCodigo(cod,p->nivel);
                    num_params = 0;}
;

passa_ou_nao:    passa_param 
            |
;

passa_param:    passa_param VIRGULA param { popInt(&tipos); }
            |   param { popInt(&tipos); }
;

param   :   expr     {  p = popProc();
                        num_params = popInt(&nparams);
                        if(p->params[num_params++].pass == PREF)
                            erro(num_params);
                        // Caso seja por valor, nao precisa fazer nada
                        // porque a expressao ja teve resultado empilhado
                        pushProc(p);  
                        pushInt(&nparams,num_params);}
;


/* ENTRADA E SAIDA */
io:         read
        |   write
        |   writeln
;

read:   READ ABRE_PARENTESES var FECHA_PARENTESES
        {   popInt(&tipos); geraCodigo(NULL,"LEIT");
            if(s->cat == CVAR){
                argsCodigo("ARMZ",s->nivel,s->var.desloc);
            } else erro(ATRIB); }
;

write:  WRITE ABRE_PARENTESES expr FECHA_PARENTESES
        { popInt(&tipos); geraCodigo(NULL,"IMPR");}
;

writeln:  WRITELN ABRE_PARENTESES writelist FECHA_PARENTESES
        { argCodigo("CRCT",(int)'\n');
          argCodigo("TEXT",1);}
;

writelist:   writelist VIRGULA expr {popInt(&tipos); geraCodigo(NULL,"IMPR");}
            | writelist VIRGULA string
            | string
            | expr {popInt(&tipos); geraCodigo(NULL,"IMPR");}
;

string:  {len = 0;} texto 
        { for(i=0; i < len; i++){
              j = popInt(&string);
              argCodigo("CRCT",j);
          }
          argCodigo("TEXT",len);}
;



texto:    STR { for(i=0; i < strlen(texto); i++){
                    len++;
                    if(texto[i]=='\\' && i < strlen(texto)-1){
                        i++;
                        if(texto[i] == 'n')
                            pushInt(&string,(int)'\n');
                        else if(texto[i] == 't')
                            pushInt(&string,(int)'\t');
                        else if(texto[i] == '0'){
                            pushInt(&string,(int)'\0');
                            break;
                        } else if(texto[i] == '\'')
                            pushInt(&string,(int)'\'');
                        else if(texto[i] == '\"')
                            pushInt(&string,(int)'\"');
                        else if(texto[i] == '\\')
                            pushInt(&string,(int)'\\');
                        else {
                            pushInt(&string,(int)'\\');
                            i--;
                        }
                    } else if (texto[i] == '\"')
                        len--;
                    else
                        pushInt(&string,(int)texto[i]);
                }}
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

