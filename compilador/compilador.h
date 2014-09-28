/* -------------------------------------------------------------------
 *            Arquivo: compilaodr.h
 * -------------------------------------------------------------------
 *                Autor: Bruno Muller Junior
 *                 Data: 08/2007
 *        Atualizado em: [15/03/2012, 08h:22m]
 *
 * -------------------------------------------------------------------
 *
 * Tipos, protótipos e vaiáveis globais do compilador
 *
 * ------------------------------------------------------------------- */

#define TAM_TOKEN 32
#define TAM_TEXT    256

typedef enum simbolos { 
    simb_program, simb_var, simb_begin, simb_end, 
    // Adicionados
    simb_label, simb_type, simb_array, simb_of, 
    simb_procedure, simb_function, simb_goto, simb_if, 
    simb_then, simb_else, simb_while, simb_do, 
    simb_or, simb_and, simb_div, simb_mult, simb_aspas,
    simb_mais, simb_menos, simb_not, simb_bool, simb_write,
    simb_maior, simb_menor, simb_menor_igual, simb_diff,
    simb_maior_igual, simb_igual, simb_true, simb_false,
    simb_int, simb_char, simb_str, simb_read, simb_writeln,
    // ---
    simb_identificador, simb_numero,
    simb_ponto, simb_virgula, simb_ponto_e_virgula, simb_dois_pontos,
    simb_atribuicao, simb_abre_parenteses, simb_fecha_parenteses,
} simbolos;



/* -------------------------------------------------------------------
 * variáveis globais
 * ------------------------------------------------------------------- */

extern simbolos simbolo, relacao;
extern char token[TAM_TOKEN], texto[TAM_TEXT];
extern int nivel_lexico;
extern int desloc;
extern int nl;


simbolos simbolo, relacao;
char token[TAM_TOKEN];
char texto[TAM_TEXT];
char codigo[TAM_TOKEN];



