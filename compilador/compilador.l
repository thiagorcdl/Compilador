%{


#include<stdio.h>
#include<string.h>

#include "compilador.h"
#include "compilador.tab.h"

//#define IMPRIME(STR) {};
#define IMPRIME(STR) printf("%s    # %s \n", STR, token); fflush(stdout)

int nl = 1;  

%}

%option noyywrap

pulo_linha [\n]

descarte [\t ]+

ident [a-zA-Z][a-zA-Z1-9]*

numero [0-9]+

comentario "(*".*"*)"

texto "\""[a-zAZ0-9 \'\\\.\:\=\;\,\|\[\]\{\}\*\+\-\<\>\(\)\%\$\#\@\!]*"\""

%%

{texto} { simbolo  = simb_str;  
          strncpy (texto, yytext, TAM_TEXT);
          IMPRIME(texto);
          return STR;
}

{pulo_linha} {nl++;} 

{descarte}

{comentario}

program { simbolo  = simb_program;   
          strncpy (token2, token, TAM_TOKEN);
          strncpy (token, yytext, TAM_TOKEN);
          IMPRIME("program ");
          return PROGRAM;
 }

var      { simbolo = simb_var;   
          strncpy (token2, token, TAM_TOKEN);
          strncpy (token, yytext, TAM_TOKEN);
          IMPRIME("var  ");
          return VAR;
 }

begin { simbolo = simb_begin; 
          strncpy (token2, token, TAM_TOKEN);
          strncpy (token, yytext, TAM_TOKEN);
          IMPRIME("begin ");
          return T_BEGIN;
 }

end { simbolo = simb_end; 
          strncpy (token2, token, TAM_TOKEN);
          strncpy (token, yytext, TAM_TOKEN);
          IMPRIME("end  ");
          return T_END;
 }

label { simbolo = simb_label; 
          strncpy (token2, token, TAM_TOKEN);
          strncpy (token, yytext, TAM_TOKEN);
          IMPRIME("label  ");
          return LABEL;
 }

type { simbolo = simb_type; 
          strncpy (token2, token, TAM_TOKEN);
          strncpy (token, yytext, TAM_TOKEN);
          IMPRIME("type  ");
          return TYPE;
 }

array { simbolo = simb_array; 
          strncpy (token2, token, TAM_TOKEN);
          strncpy (token, yytext, TAM_TOKEN);
          IMPRIME("array  ");
          return ARRAY;
 }

of { simbolo = simb_of; 
          strncpy (token2, token, TAM_TOKEN);
          strncpy (token, yytext, TAM_TOKEN);
          IMPRIME("of  ");
          return OF;
 }

procedure { simbolo = simb_procedure; 
          strncpy (token2, token, TAM_TOKEN);
          strncpy (token, yytext, TAM_TOKEN);
          IMPRIME("procedure  ");
          return PROCEDURE;
 }

function { simbolo = simb_function; 
          strncpy (token2, token, TAM_TOKEN);
          strncpy (token, yytext, TAM_TOKEN);
          IMPRIME("function  ");
          return FUNCTION;
 }

goto { simbolo = simb_goto; 
          strncpy (token2, token, TAM_TOKEN);
          strncpy (token, yytext, TAM_TOKEN);
          IMPRIME("goto  ");
          return GOTO;
 }

if { simbolo = simb_if; 
          strncpy (token2, token, TAM_TOKEN);
          strncpy (token, yytext, TAM_TOKEN);
          IMPRIME("if  ");
          return IF;
 }

then { simbolo = simb_then; 
          strncpy (token2, token, TAM_TOKEN);
          strncpy (token, yytext, TAM_TOKEN);
          IMPRIME("then  ");
          return THEN;
 }

else { simbolo = simb_else; 
          strncpy (token2, token, TAM_TOKEN);
          strncpy (token, yytext, TAM_TOKEN);
          IMPRIME("else  ");
          return ELSE;
 }

while { simbolo = simb_while; 
          strncpy (token2, token, TAM_TOKEN);
          strncpy (token, yytext, TAM_TOKEN);
          IMPRIME("while  ");
          return WHILE;
 }

do { simbolo = simb_do; 
          strncpy (token2, token, TAM_TOKEN);
          strncpy (token, yytext, TAM_TOKEN);
          IMPRIME("do  ");
          return DO;
 }

or { simbolo = simb_or; 
          strncpy (token2, token, TAM_TOKEN);
          strncpy (token, yytext, TAM_TOKEN);
          IMPRIME(" or ");
          return OR;
 }

and { simbolo = simb_and; 
          strncpy (token2, token, TAM_TOKEN);
          strncpy (token, yytext, TAM_TOKEN);
          IMPRIME(" and ");
          return AND;
 }

div { simbolo = simb_div; 
          strncpy (token2, token, TAM_TOKEN);
          strncpy (token, yytext, TAM_TOKEN);
          IMPRIME(" div ");
          return DIV;
 }

not { simbolo = simb_not; 
          strncpy (token2, token, TAM_TOKEN);
          strncpy (token, yytext, TAM_TOKEN);
          IMPRIME("not ");
          return NOT;
 }

boolean { simbolo = simb_bool; 
          strncpy (token2, token, TAM_TOKEN);
          strncpy (token, yytext, TAM_TOKEN);
          IMPRIME("boolean ");
          return BOOL;
 }

true { simbolo = simb_true; 
          strncpy (token2, token, TAM_TOKEN);
          strncpy (token, yytext, TAM_TOKEN);
          IMPRIME("true ");
          return T_TRUE;
 }

false { simbolo = simb_false; 
          strncpy (token2, token, TAM_TOKEN);
          strncpy (token, yytext, TAM_TOKEN);
          IMPRIME("false ");
          return T_FALSE;
 }

integer { simbolo = simb_int; 
          strncpy (token2, token, TAM_TOKEN);
          strncpy (token, yytext, TAM_TOKEN);
          IMPRIME("integer ");
          return INT;
 }

char { simbolo = simb_char; 
          strncpy (token2, token, TAM_TOKEN);
          strncpy (token, yytext, TAM_TOKEN);
          IMPRIME("character ");
          return CHAR;
 }

string { simbolo = simb_str; 
          strncpy (token2, token, TAM_TOKEN);
          strncpy (token, yytext, TAM_TOKEN);
          IMPRIME("string ");
          return STR;
 }

read { simbolo = simb_read; 
          strncpy (token2, token, TAM_TOKEN);
          strncpy (token, yytext, TAM_TOKEN);
          IMPRIME("le ");
          return READ;
 }

writeln { simbolo = simb_writeln; 
          strncpy (token2, token, TAM_TOKEN);
          strncpy (token, yytext, TAM_TOKEN);
          IMPRIME("escreve ");
          return WRITELN;
 }


write { simbolo = simb_write; 
          strncpy (token2, token, TAM_TOKEN);
          strncpy (token, yytext, TAM_TOKEN);
          IMPRIME("escreve ");
          return WRITE;
 }


\* { simbolo = simb_mult; 
          strncpy (token2, token, TAM_TOKEN);
          strncpy (token, yytext, TAM_TOKEN);
          IMPRIME(" * ");
          return MULT;
 }

\+ { simbolo = simb_mais; 
          strncpy (token2, token, TAM_TOKEN);
          strncpy (token, yytext, TAM_TOKEN);
          IMPRIME(" + ");
          return MAIS;
 }

\- { simbolo = simb_menos; 
          strncpy (token2, token, TAM_TOKEN);
          strncpy (token, yytext, TAM_TOKEN);
          IMPRIME(" - ");
          return MENOS;
 }


\>  { simbolo = simb_maior;
  strncpy (token, yytext, TAM_TOKEN);
  IMPRIME(" > ");
  return MAIOR;
}

\<  { simbolo = simb_menor;
  strncpy (token, yytext, TAM_TOKEN);
  IMPRIME(" < ");
  return MENOR;
}

\>=  { simbolo = simb_maior_igual;
  strncpy (token, yytext, TAM_TOKEN);
  IMPRIME(" >=");
  return MAIOR_IGUAL;
}

\<=  { simbolo = simb_menor_igual;
  strncpy (token, yytext, TAM_TOKEN);
  IMPRIME(" <= ");
  return MENOR_IGUAL;
}

\<> { simbolo = simb_diff;
  strncpy (token, yytext, TAM_TOKEN);
  IMPRIME(" <> ");
  return DIFF;
}

\=  { simbolo = simb_igual;
  strncpy (token, yytext, TAM_TOKEN);
  IMPRIME(" == ");
  return IGUAL;
}

\"  { simbolo = simb_aspas;
  strncpy (token, yytext, TAM_TOKEN);
  IMPRIME(" aspas ");
  return ASPAS;
}

\'  { simbolo = simb_aspas;
  strncpy (token, yytext, TAM_TOKEN);
  IMPRIME(" aspas ");
  return ASPAS;
}

:= { simbolo = simb_atribuicao;   
          strncpy (token2, token, TAM_TOKEN);
          strncpy (token, yytext, TAM_TOKEN);
          IMPRIME(" atribuicao  ");
          return ATRIBUICAO;  
 }

\; { simbolo = simb_ponto_e_virgula;   
          strncpy (token2, token, TAM_TOKEN);
          strncpy (token, yytext, TAM_TOKEN);
          IMPRIME(" pt_virgula  ");
          return PONTO_E_VIRGULA;
 }

\: { simbolo = simb_dois_pontos;   
          strncpy (token2, token, TAM_TOKEN);
          strncpy (token, yytext, TAM_TOKEN);
          IMPRIME(" dois pontos ");
          return DOIS_PONTOS;
 }

\, { simbolo = simb_virgula;   
          strncpy (token2, token, TAM_TOKEN);
          strncpy (token, yytext, TAM_TOKEN);
          IMPRIME(" virgula  ");
          return VIRGULA;
 }


\. { simbolo = simb_ponto;   
          strncpy (token2, token, TAM_TOKEN);
          strncpy (token, yytext, TAM_TOKEN);
          IMPRIME(" ponto  ");
          return PONTO; 
    }

\(  { simbolo = simb_abre_parenteses;   
          strncpy (token2, token, TAM_TOKEN);
          strncpy (token, yytext, TAM_TOKEN);
          IMPRIME(" abre_parenteses  ");
          return ABRE_PARENTESES;
    }

\)  {     simbolo = simb_fecha_parenteses;  
          strncpy (token2, token, TAM_TOKEN);
          strncpy (token, yytext, TAM_TOKEN);
          IMPRIME(" fecha_parenteses ");
          return FECHA_PARENTESES;
 }

{numero} { simbolo = simb_numero;
  strncpy (token, yytext, TAM_TOKEN);
  IMPRIME(" numero");
  return NUMERO;
}

{ident} { simbolo = simb_identificador;  
          strncpy (token, yytext, TAM_TOKEN);
          strncpy (token2, token, TAM_TOKEN);
          IMPRIME(" ident  ");
          return IDENT;
        }


%%

