/* A Bison parser, made by GNU Bison 3.0.2.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2013 Free Software Foundation, Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "3.0.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* Copy the first part of user declarations.  */
#line 8 "compilador.y" /* yacc.c:339  */

#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include "compilador.h"
#include "pilhas.h"


#define argCodigo(str,a)    sprintf(cod,"%s%d",str,a);\
                            if (usa_rot) { \
                                geraCodigo(rot,cod);\
                                usa_rot=0;\
                            } else  geraCodigo(NULL,cod)

#define argsCodigo(str,a1,a2)   if(str[strlen(str)-1]=='R')\
                                    sprintf(cod,"%s%02d, %d",str,a1,a2);\
                                else\
                                    sprintf(cod,"%s%d, %d",str,a1,a2);\
                                if (usa_rot) { \
                                    geraCodigo(rot,cod);\
                                    usa_rot=0;\
                                } else  geraCodigo(NULL,cod)

#define rotCodigo(r)    if (usa_rot) { \
                            geraCodigo(rot,"NADA");\
                            usa_rot=0;\
                        } sprintf(rot,"R%02d",r);\
                          geraCodigo(rot,"NADA")

#define desvCodigo(str,r)   sprintf(cod,"%s R%02d",str,r);\
                            if (usa_rot) { \
                                geraCodigo(rot,cod);\
                                usa_rot=0;\
                            } else  geraCodigo(NULL,cod)


int num_idents, num_params, flag_var;
int i, j, rotulo, usa_rot, len;
char cod[32],rot[16];
int desloc = 0, nivel_lexico = 0;

/* Decide tipo de empilhamento baseado na variavel e param esperado*/
void varCodigo(Simbolo *s, int param){
    if(!param){
        if(s->var.pass == PREF){
            argsCodigo("CRVI ",s->nivel,s->var.desloc);
        } else {
            argsCodigo("CRVL ",s->nivel,s->var.desloc);
        }
    } else {
        if(param > p->num_params)
            erro(NPARAM);
        param--;
        if(s->var.pass == PREF){
            if(p->params[param].pass == PREF){
                argsCodigo("CRVL ",s->nivel,s->var.desloc);
            } else {
                argsCodigo("CRVI ",s->nivel,s->var.desloc);
            }
        } else {
            //printf("@@@ s: %d p[%d]: %d\n",s->var.pass,param,p->params[param].pass);
            if(p->params[param].pass == PREF){
                argsCodigo("CREN ",s->nivel,s->var.desloc);
            } else {
                argsCodigo("CRVL ",s->nivel,s->var.desloc);
            }
        }
    }
    return;
}

void armzCodigo(Simbolo *s){
    if( s->cat == CFUNC){           // Função recebendo valor de retorno
        argsCodigo("ARMZ ",s->nivel,s->params[s->num_params].desloc);
    } else if(s->var.pass == PREF){ // Param por referência
        argsCodigo("ARMI ",s->nivel,s->var.desloc);
    } else {                        // Var simples ou param por valor
        argsCodigo("ARMZ ",s->nivel,s->var.desloc);
    }
    return;
}

void updateRotulo(int r){
    if (r>=0){
        usa_rot = 1;
        sprintf(rot,"R%02d",r);
    } else usa_rot = 0;
    return;
}



#line 160 "compilador.tab.c" /* yacc.c:339  */

# ifndef YY_NULLPTR
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULLPTR nullptr
#  else
#   define YY_NULLPTR 0
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* In a future release of Bison, this section will be replaced
   by #include "compilador.tab.h".  */
#ifndef YY_YY_COMPILADOR_TAB_H_INCLUDED
# define YY_YY_COMPILADOR_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    PROGRAM = 258,
    ABRE_PARENTESES = 259,
    FECHA_PARENTESES = 260,
    VIRGULA = 261,
    PONTO_E_VIRGULA = 262,
    DOIS_PONTOS = 263,
    PONTO = 264,
    T_BEGIN = 265,
    T_END = 266,
    VAR = 267,
    IDENT = 268,
    ATRIBUICAO = 269,
    ASPAS = 270,
    LABEL = 271,
    TYPE = 272,
    ARRAY = 273,
    OF = 274,
    PROCEDURE = 275,
    FUNCTION = 276,
    GOTO = 277,
    IF = 278,
    THEN = 279,
    ELSE = 280,
    WHILE = 281,
    DO = 282,
    OR = 283,
    AND = 284,
    NUMERO = 285,
    NOT = 286,
    DIV = 287,
    MULT = 288,
    MAIS = 289,
    MENOS = 290,
    T_TRUE = 291,
    T_FALSE = 292,
    MAIOR = 293,
    MENOR = 294,
    MAIOR_IGUAL = 295,
    MENOR_IGUAL = 296,
    DIFF = 297,
    INT = 298,
    STR = 299,
    CHAR = 300,
    BOOL = 301,
    IGUAL = 302,
    READ = 303,
    WRITE = 304,
    WRITELN = 305
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef int YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_COMPILADOR_TAB_H_INCLUDED  */

/* Copy the second part of user declarations.  */

#line 262 "compilador.tab.c" /* yacc.c:358  */

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif

#ifndef YY_ATTRIBUTE
# if (defined __GNUC__                                               \
      && (2 < __GNUC__ || (__GNUC__ == 2 && 96 <= __GNUC_MINOR__)))  \
     || defined __SUNPRO_C && 0x5110 <= __SUNPRO_C
#  define YY_ATTRIBUTE(Spec) __attribute__(Spec)
# else
#  define YY_ATTRIBUTE(Spec) /* empty */
# endif
#endif

#ifndef YY_ATTRIBUTE_PURE
# define YY_ATTRIBUTE_PURE   YY_ATTRIBUTE ((__pure__))
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# define YY_ATTRIBUTE_UNUSED YY_ATTRIBUTE ((__unused__))
#endif

#if !defined _Noreturn \
     && (!defined __STDC_VERSION__ || __STDC_VERSION__ < 201112)
# if defined _MSC_VER && 1200 <= _MSC_VER
#  define _Noreturn __declspec (noreturn)
# else
#  define _Noreturn YY_ATTRIBUTE ((__noreturn__))
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN \
    _Pragma ("GCC diagnostic push") \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")\
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif


#if ! defined yyoverflow || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYSIZE_T yynewbytes;                                            \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / sizeof (*yyptr);                          \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, (Count) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYSIZE_T yyi;                         \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  3
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   152

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  51
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  70
/* YYNRULES -- Number of rules.  */
#define YYNRULES  121
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  200

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   305

#define YYTRANSLATE(YYX)                                                \
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, without out-of-bounds checking.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   115,   115,   115,   125,   127,   124,   132,   132,   136,
     139,   140,   143,   145,   143,   153,   154,   155,   156,   159,
     165,   172,   173,   178,   181,   181,   186,   186,   188,   193,
     194,   193,   201,   202,   205,   206,   209,   210,   211,   212,
     213,   214,   215,   218,   223,   224,   227,   228,   231,   239,
     239,   246,   249,   260,   264,   276,   278,   280,   282,   284,
     286,   288,   291,   293,   295,   297,   300,   302,   304,   306,
     308,   312,   313,   318,   319,   320,   321,   325,   333,   334,
     335,   338,   338,   357,   366,   357,   384,   386,   384,   398,
     399,   402,   402,   403,   403,   406,   415,   428,   428,   442,
     442,   459,   460,   461,   464,   464,   465,   465,   468,   481,
     482,   483,   486,   494,   498,   503,   504,   505,   506,   509,
     509,   519
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "PROGRAM", "ABRE_PARENTESES",
  "FECHA_PARENTESES", "VIRGULA", "PONTO_E_VIRGULA", "DOIS_PONTOS", "PONTO",
  "T_BEGIN", "T_END", "VAR", "IDENT", "ATRIBUICAO", "ASPAS", "LABEL",
  "TYPE", "ARRAY", "OF", "PROCEDURE", "FUNCTION", "GOTO", "IF", "THEN",
  "ELSE", "WHILE", "DO", "OR", "AND", "NUMERO", "NOT", "DIV", "MULT",
  "MAIS", "MENOS", "T_TRUE", "T_FALSE", "MAIOR", "MENOR", "MAIOR_IGUAL",
  "MENOR_IGUAL", "DIFF", "INT", "STR", "CHAR", "BOOL", "IGUAL", "READ",
  "WRITE", "WRITELN", "$accept", "programa", "$@1", "bloco", "$@2", "$@3",
  "parte_declara_vars", "$@4", "declara_vars", "declara_var", "$@5", "$@6",
  "tipo", "lista_id_var", "lista_idents", "if", "if_then", "$@7",
  "cond_else", "$@8", "while", "$@9", "$@10", "comandos", "comando",
  "comando_sem_rotulo", "comando_composto", "parte_decl_labels",
  "decl_labels", "decl_label", "poe_label", "$@11", "comando_goto",
  "atrib", "recipiente", "expr", "exprs", "termo", "fator", "var",
  "declara_subrot", "decl_proc", "$@12", "decl_func", "$@13", "$@14",
  "params_formais", "$@15", "$@16", "decl_params", "$@17", "$@18",
  "params", "ch_proc", "$@19", "ch_func", "$@20", "passa_ou_nao",
  "passa_param", "$@21", "$@22", "param", "io", "read", "write", "writeln",
  "writelist", "string", "$@23", "texto", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305
};
# endif

#define YYPACT_NINF -100

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-100)))

#define YYTABLE_NINF -100

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int8 yypact[] =
{
    -100,     8,     7,  -100,     4,    18,    22,  -100,    48,    51,
      54,    74,  -100,    61,    86,    80,  -100,    58,  -100,  -100,
    -100,  -100,    61,  -100,  -100,  -100,  -100,    85,  -100,    87,
      62,  -100,  -100,    17,    88,    89,    93,    92,    97,    94,
      34,  -100,  -100,    -4,  -100,  -100,  -100,  -100,  -100,  -100,
    -100,  -100,  -100,   102,   102,  -100,     2,  -100,  -100,    -2,
     103,    91,   104,   101,   105,    -4,  -100,    98,    84,     1,
    -100,   111,   112,   113,  -100,    95,  -100,  -100,  -100,  -100,
     107,  -100,  -100,  -100,  -100,  -100,  -100,  -100,  -100,  -100,
      74,    34,  -100,  -100,   114,   114,  -100,     1,   115,  -100,
       3,  -100,  -100,  -100,    21,  -100,    37,  -100,  -100,     1,
     110,     1,     1,  -100,  -100,     1,   118,    72,  -100,  -100,
     121,  -100,  -100,   122,  -100,   106,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     3,     3,     3,  -100,  -100,
     123,   124,  -100,    81,  -100,    90,    -4,   -16,  -100,   126,
      87,    28,  -100,   125,  -100,    83,     1,  -100,    -4,  -100,
    -100,  -100,   -16,   -16,   -16,   -16,   -16,   -16,  -100,  -100,
    -100,   108,  -100,  -100,  -100,     1,  -100,  -100,  -100,    72,
    -100,    35,    34,    74,  -100,  -100,  -100,  -100,  -100,    -4,
    -100,  -100,  -100,    34,  -100,  -100,     1,  -100,  -100,  -100
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       2,     0,     0,     1,     0,     0,     0,    22,     0,     0,
       0,    45,    21,     0,     0,     9,    48,     0,    47,     3,
       7,     4,     0,    44,    12,    80,    46,     8,    11,     0,
       5,    10,    20,     0,     0,     0,     0,     0,     0,     0,
       0,    81,    83,    51,     6,    78,    79,    19,    16,    18,
      17,    15,    13,    89,    89,    49,     0,    33,    35,     0,
       0,    86,     0,     0,     0,    51,    43,    97,     0,     0,
      29,     0,     0,     0,    38,    28,    37,    34,    39,    36,
       0,    40,    41,    42,   109,   110,   111,    14,    90,    93,
      45,     0,    50,    32,   103,   103,    52,     0,    77,    76,
       0,    74,    75,    24,    61,    65,    70,    72,    73,     0,
       0,     0,   119,    26,    23,     0,    87,     0,    82,    84,
     106,    98,   100,     0,    66,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    30,    77,
       0,     0,   118,     0,   117,     0,    51,    53,    91,     0,
       0,     0,    94,     0,   102,     0,     0,    71,    51,    64,
      62,    63,    58,    57,    60,    59,    55,    56,    69,    68,
      67,     0,   112,   113,   114,   119,   121,   120,    27,     0,
      88,     0,     0,    45,   101,   104,   108,   107,    25,    51,
     115,   116,    92,     0,    96,    85,     0,    31,    95,   105
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
    -100,  -100,  -100,   -86,  -100,  -100,  -100,  -100,  -100,   109,
    -100,  -100,   -88,   -28,  -100,  -100,  -100,  -100,  -100,  -100,
    -100,  -100,  -100,  -100,   -65,  -100,   116,  -100,  -100,   117,
    -100,  -100,  -100,  -100,  -100,   -67,   -58,   -99,   -85,    23,
    -100,  -100,  -100,  -100,  -100,  -100,    96,  -100,  -100,  -100,
    -100,  -100,   -42,  -100,  -100,    79,  -100,    45,  -100,  -100,
    -100,   -55,  -100,  -100,  -100,  -100,  -100,   -33,  -100,  -100
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     1,     2,    14,    25,    36,    21,    24,    27,    28,
      29,    60,    52,   151,     8,    74,    75,   125,   114,   146,
      76,   109,   171,    56,    57,    77,    58,    15,    17,    18,
      59,    64,    78,    79,    80,   186,   104,   105,   106,   107,
      30,    37,    53,    38,    54,   153,    62,    89,   149,   116,
     179,   117,   152,    81,    94,   108,    95,   121,   155,   196,
     156,   187,    83,    84,    85,    86,   143,   144,   145,   177
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      93,    33,   103,   119,   118,    97,    43,    97,     3,    65,
       4,    67,   126,    66,    98,   124,    98,     5,   127,   128,
      68,    69,     6,    39,    70,    40,    55,   159,   160,   161,
     123,    99,   100,    99,    39,     7,   182,   101,   102,   101,
     102,    39,   138,   193,   141,   142,    71,    72,    73,   126,
     168,   169,   170,     9,    10,   127,   128,   147,    11,   129,
     130,   131,   132,   133,    22,    23,   135,    12,   134,   136,
     137,   162,   163,   164,   165,   166,   167,    48,    49,    50,
      51,   178,    34,    35,   150,    32,   174,   175,   184,   185,
      13,    16,    20,   188,   194,    19,    88,   195,   -12,    45,
      32,    41,    42,    43,    46,   198,    61,    47,   190,    91,
      87,    90,   -54,    92,    96,   110,   111,   112,   120,   -99,
     113,   115,   181,   139,   197,   148,   154,   157,   172,   173,
     158,   180,   183,   140,   176,   189,    31,   192,    82,    26,
     122,   199,   191,     0,     0,     0,     0,     0,     0,     0,
      63,     0,    44
};

static const yytype_int16 yycheck[] =
{
      65,    29,    69,    91,    90,     4,    10,     4,     0,     7,
       3,    13,    28,    11,    13,   100,    13,    13,    34,    35,
      22,    23,     4,     6,    26,     8,    30,   126,   127,   128,
      97,    30,    31,    30,     6,    13,     8,    36,    37,    36,
      37,     6,   109,     8,   111,   112,    48,    49,    50,    28,
     135,   136,   137,     5,     6,    34,    35,   115,     7,    38,
      39,    40,    41,    42,     6,     7,    29,    13,    47,    32,
      33,   129,   130,   131,   132,   133,   134,    43,    44,    45,
      46,   146,    20,    21,    12,    13,     5,     6,     5,     6,
      16,    30,    12,   158,   182,     9,     5,   183,    13,     7,
      13,    13,    13,    10,     7,   193,     4,    13,   175,     8,
       7,     7,    14,     8,    30,     4,     4,     4,     4,     4,
      25,    14,   150,    13,   189,     7,     5,     5,     5,     5,
      24,     5,     7,   110,    44,    27,    27,   179,    59,    22,
      95,   196,   175,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      54,    -1,    36
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    52,    53,     0,     3,    13,     4,    13,    65,     5,
       6,     7,    13,    16,    54,    78,    30,    79,    80,     9,
      12,    57,     6,     7,    58,    55,    80,    59,    60,    61,
      91,    60,    13,    64,    20,    21,    56,    92,    94,     6,
       8,    13,    13,    10,    77,     7,     7,    13,    43,    44,
      45,    46,    63,    93,    95,    30,    74,    75,    77,    81,
      62,     4,    97,    97,    82,     7,    11,    13,    22,    23,
      26,    48,    49,    50,    66,    67,    71,    76,    83,    84,
      85,   104,   106,   113,   114,   115,   116,     7,     5,    98,
       7,     8,     8,    75,   105,   107,    30,     4,    13,    30,
      31,    36,    37,    86,    87,    88,    89,    90,   106,    72,
       4,     4,     4,    25,    69,    14,   100,   102,    54,    63,
       4,   108,   108,    86,    89,    68,    28,    34,    35,    38,
      39,    40,    41,    42,    47,    29,    32,    33,    86,    13,
      90,    86,    86,   117,   118,   119,    70,    87,     7,    99,
      12,    64,   103,    96,     5,   109,   111,     5,    24,    88,
      88,    88,    87,    87,    87,    87,    87,    87,    89,    89,
      89,    73,     5,     5,     5,     6,    44,   120,    75,   101,
       5,    64,     8,     7,     5,     6,    86,   112,    75,    27,
      86,   118,   103,     8,    63,    54,   110,    75,    63,   112
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    51,    53,    52,    55,    56,    54,    58,    57,    57,
      59,    59,    61,    62,    60,    63,    63,    63,    63,    64,
      64,    65,    65,    66,    68,    67,    70,    69,    69,    72,
      73,    71,    74,    74,    75,    75,    76,    76,    76,    76,
      76,    76,    76,    77,    78,    78,    79,    79,    80,    82,
      81,    81,    83,    84,    85,    86,    86,    86,    86,    86,
      86,    86,    87,    87,    87,    87,    88,    88,    88,    88,
      88,    89,    89,    89,    89,    89,    89,    90,    91,    91,
      91,    93,    92,    95,    96,    94,    98,    99,    97,    97,
      97,   101,   100,   102,   100,   103,   103,   105,   104,   107,
     106,   108,   108,   108,   110,   109,   111,   109,   112,   113,
     113,   113,   114,   115,   116,   117,   117,   117,   117,   119,
     118,   120
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     0,     9,     0,     0,     6,     0,     3,     0,
       2,     1,     0,     0,     6,     1,     1,     1,     1,     3,
       1,     3,     1,     2,     0,     5,     0,     3,     0,     0,
       0,     6,     3,     1,     2,     1,     1,     1,     1,     1,
       1,     1,     1,     3,     3,     0,     3,     1,     1,     0,
       3,     0,     2,     3,     1,     3,     3,     3,     3,     3,
       3,     1,     3,     3,     3,     1,     2,     3,     3,     3,
       1,     3,     1,     1,     1,     1,     1,     1,     3,     3,
       0,     0,     6,     0,     0,     9,     0,     0,     5,     0,
       2,     0,     4,     0,     2,     4,     3,     0,     3,     0,
       3,     3,     2,     0,     0,     4,     0,     2,     1,     1,
       1,     1,     4,     4,     4,     3,     3,     1,     1,     0,
       2,     1
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                  \
do                                                              \
  if (yychar == YYEMPTY)                                        \
    {                                                           \
      yychar = (Token);                                         \
      yylval = (Value);                                         \
      YYPOPSTACK (yylen);                                       \
      yystate = *yyssp;                                         \
      goto yybackup;                                            \
    }                                                           \
  else                                                          \
    {                                                           \
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;                                                  \
    }                                                           \
while (0)

/* Error token number */
#define YYTERROR        1
#define YYERRCODE       256



/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)

/* This macro is provided for backward compatibility. */
#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#endif


# define YY_SYMBOL_PRINT(Title, Type, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Type, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*----------------------------------------.
| Print this symbol's value on YYOUTPUT.  |
`----------------------------------------*/

static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  FILE *yyo = yyoutput;
  YYUSE (yyo);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# endif
  YYUSE (yytype);
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyoutput, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yytype_int16 *yyssp, YYSTYPE *yyvsp, int yyrule)
{
  unsigned long int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       yystos[yyssp[yyi + 1 - yynrhs]],
                       &(yyvsp[(yyi + 1) - (yynrhs)])
                                              );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif


#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
static YYSIZE_T
yystrlen (const char *yystr)
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
static char *
yystpcpy (char *yydest, const char *yysrc)
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
        switch (*++yyp)
          {
          case '\'':
          case ',':
            goto do_not_strip_quotes;

          case '\\':
            if (*++yyp != '\\')
              goto do_not_strip_quotes;
            /* Fall through.  */
          default:
            if (yyres)
              yyres[yyn] = *yyp;
            yyn++;
            break;

          case '"':
            if (yyres)
              yyres[yyn] = '\0';
            return yyn;
          }
    do_not_strip_quotes: ;
    }

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYSIZE_T *yymsg_alloc, char **yymsg,
                yytype_int16 *yyssp, int yytoken)
{
  YYSIZE_T yysize0 = yytnamerr (YY_NULLPTR, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
  int yycount = 0;

  /* There are many possibilities here to consider:
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yytoken != YYEMPTY)
    {
      int yyn = yypact[*yyssp];
      yyarg[yycount++] = yytname[yytoken];
      if (!yypact_value_is_default (yyn))
        {
          /* Start YYX at -YYN if negative to avoid negative indexes in
             YYCHECK.  In other words, skip the first -YYN actions for
             this state because they are default actions.  */
          int yyxbegin = yyn < 0 ? -yyn : 0;
          /* Stay within bounds of both yycheck and yytname.  */
          int yychecklim = YYLAST - yyn + 1;
          int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
          int yyx;

          for (yyx = yyxbegin; yyx < yyxend; ++yyx)
            if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR
                && !yytable_value_is_error (yytable[yyx + yyn]))
              {
                if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                  {
                    yycount = 1;
                    yysize = yysize0;
                    break;
                  }
                yyarg[yycount++] = yytname[yyx];
                {
                  YYSIZE_T yysize1 = yysize + yytnamerr (YY_NULLPTR, yytname[yyx]);
                  if (! (yysize <= yysize1
                         && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
                    return 2;
                  yysize = yysize1;
                }
              }
        }
    }

  switch (yycount)
    {
# define YYCASE_(N, S)                      \
      case N:                               \
        yyformat = S;                       \
      break
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  {
    YYSIZE_T yysize1 = yysize + yystrlen (yyformat);
    if (! (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
      return 2;
    yysize = yysize1;
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return 1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yyarg[yyi++]);
          yyformat += 2;
        }
      else
        {
          yyp++;
          yyformat++;
        }
  }
  return 0;
}
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
{
  YYUSE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}




/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;


/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */
  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        YYSTYPE *yyvs1 = yyvs;
        yytype_int16 *yyss1 = yyss;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * sizeof (*yyssp),
                    &yyvs1, yysize * sizeof (*yyvsp),
                    &yystacksize);

        yyss = yyss1;
        yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yytype_int16 *yyss1 = yyss;
        union yyalloc *yyptr =
          (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
        if (! yyptr)
          goto yyexhaustedlab;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
                  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- Do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 2:
#line 115 "compilador.y" /* yacc.c:1646  */
    {   rotulo = 0; nl=1; flag_var=0;
                tabela = NULL; tipos = NULL; string = NULL; rotulos = NULL;
                geraCodigo(NULL, "INPP");}
#line 1491 "compilador.tab.c" /* yacc.c:1646  */
    break;

  case 3:
#line 120 "compilador.y" /* yacc.c:1646  */
    {   argCodigo("DMEM ",popInt(&nvars));
                                geraCodigo (NULL, "PARA"); }
#line 1498 "compilador.tab.c" /* yacc.c:1646  */
    break;

  case 4:
#line 125 "compilador.y" /* yacc.c:1646  */
    {   desvCodigo("DSVS",rotulo); pushInt(&rotulos,rotulo++);}
#line 1504 "compilador.tab.c" /* yacc.c:1646  */
    break;

  case 5:
#line 127 "compilador.y" /* yacc.c:1646  */
    {   rotCodigo(popInt(&rotulos));}
#line 1510 "compilador.tab.c" /* yacc.c:1646  */
    break;

  case 7:
#line 132 "compilador.y" /* yacc.c:1646  */
    { desloc=0; }
#line 1516 "compilador.tab.c" /* yacc.c:1646  */
    break;

  case 8:
#line 134 "compilador.y" /* yacc.c:1646  */
    {   argCodigo("AMEM ",desloc);
                        pushInt(&nvars,desloc);}
#line 1523 "compilador.tab.c" /* yacc.c:1646  */
    break;

  case 12:
#line 143 "compilador.y" /* yacc.c:1646  */
    { num_idents=0;}
#line 1529 "compilador.tab.c" /* yacc.c:1646  */
    break;

  case 13:
#line 145 "compilador.y" /* yacc.c:1646  */
    { s = tabela;
                     for(i=0; i < num_idents; i++){
                        s->var.tipo = (!strcmp("integer",token)?TINT:TBOOL);
                        s = s->abaixo;
                     }}
#line 1539 "compilador.tab.c" /* yacc.c:1646  */
    break;

  case 19:
#line 160 "compilador.y" /* yacc.c:1646  */
    { s = criaSimb(token);
                s->cat = CVAR;
                s->var.desloc = desloc++;
                tabela = pushSimb(tabela,s);
                num_idents++;}
#line 1549 "compilador.tab.c" /* yacc.c:1646  */
    break;

  case 20:
#line 165 "compilador.y" /* yacc.c:1646  */
    {   s = criaSimb(token);
                        s->cat = CVAR;
                        s->var.desloc = desloc++;
                        tabela = pushSimb(tabela,s);
                        num_idents++;}
#line 1559 "compilador.tab.c" /* yacc.c:1646  */
    break;

  case 23:
#line 178 "compilador.y" /* yacc.c:1646  */
    { rotCodigo(popInt(&rotulos)); }
#line 1565 "compilador.tab.c" /* yacc.c:1646  */
    break;

  case 24:
#line 181 "compilador.y" /* yacc.c:1646  */
    { desvCodigo("DSVF",rotulo++); pushInt(&rotulos,rotulo++);}
#line 1571 "compilador.tab.c" /* yacc.c:1646  */
    break;

  case 25:
#line 182 "compilador.y" /* yacc.c:1646  */
    { desvCodigo("DSVS",rotulos->val);
                               rotCodigo(rotulos->val-1);}
#line 1578 "compilador.tab.c" /* yacc.c:1646  */
    break;

  case 26:
#line 186 "compilador.y" /* yacc.c:1646  */
    { }
#line 1584 "compilador.tab.c" /* yacc.c:1646  */
    break;

  case 29:
#line 193 "compilador.y" /* yacc.c:1646  */
    { rotCodigo(rotulo++); }
#line 1590 "compilador.tab.c" /* yacc.c:1646  */
    break;

  case 30:
#line 194 "compilador.y" /* yacc.c:1646  */
    { desvCodigo("DSVF",rotulo); pushInt(&rotulos,rotulo++);}
#line 1596 "compilador.tab.c" /* yacc.c:1646  */
    break;

  case 31:
#line 195 "compilador.y" /* yacc.c:1646  */
    { desvCodigo("DSVS",rotulos->val - 1);
                                rotCodigo(popInt(&rotulos));}
#line 1603 "compilador.tab.c" /* yacc.c:1646  */
    break;

  case 36:
#line 209 "compilador.y" /* yacc.c:1646  */
    {printf("atribuiu\n\n");fflush(stdout);}
#line 1609 "compilador.tab.c" /* yacc.c:1646  */
    break;

  case 48:
#line 231 "compilador.y" /* yacc.c:1646  */
    {    s = criaSimb(token);
                        s->cat = CLABEL;
                        //printf("@@@@@@\nlabel \'%s\' rot MEPA: %d\n@@@@@@@\n",s->ident,rotulo);
                        fflush(stdout);
                        s->label = rotulo++;
                        tabela = pushSimb(tabela,s);}
#line 1620 "compilador.tab.c" /* yacc.c:1646  */
    break;

  case 49:
#line 239 "compilador.y" /* yacc.c:1646  */
    {    s = buscaSimb(tabela,token);
                        if ( s == NULL ) erro(RN_DECL);
                        //printf("@@@@@@\nlabel \'%s\' rot MEPA: %d\n@@@@@@@\n",s->ident,s->label);
                        fflush(stdout);
                        updateRotulo(s->label);
                        argsCodigo("ENRT ",nivel_lexico,nvars->val); }
#line 1631 "compilador.tab.c" /* yacc.c:1646  */
    break;

  case 52:
#line 249 "compilador.y" /* yacc.c:1646  */
    {   s = buscaSimb(tabela,token);
                                if ( s == NULL ) erro(RN_DECL);
                                sprintf(cod,"DSVR R%02d, %d, %d",s->label,s->nivel,nivel_lexico);
                                if (usa_rot) {
                                    geraCodigo(rot,cod);
                                    usa_rot=0;
                                } else geraCodigo(NULL,cod);}
#line 1643 "compilador.tab.c" /* yacc.c:1646  */
    break;

  case 53:
#line 260 "compilador.y" /* yacc.c:1646  */
    {   cmpTipo(TVOID);
                                            armzCodigo(esq);}
#line 1650 "compilador.tab.c" /* yacc.c:1646  */
    break;

  case 54:
#line 264 "compilador.y" /* yacc.c:1646  */
    {   s = buscaSimb(tabela,token2);
                        if ( s == NULL ) erro(VN_DECL);
                        else if ( s->cat == CVAR || s->cat == CPARAM){
                            pushInt(&tipos,s->var.tipo);
                        } else if ( s->cat == CFUNC ){
                            pushInt(&tipos,p->params[p->num_params].tipo);
                        } else erro(ATRIB);
                        esq = s;
                      }
#line 1664 "compilador.tab.c" /* yacc.c:1646  */
    break;

  case 55:
#line 276 "compilador.y" /* yacc.c:1646  */
    {   cmpTipo(TVOID); pushInt(&tipos,TBOOL);
                                    geraCodigo(NULL,"CMDG");}
#line 1671 "compilador.tab.c" /* yacc.c:1646  */
    break;

  case 56:
#line 278 "compilador.y" /* yacc.c:1646  */
    {   cmpTipo(TVOID); pushInt(&tipos,TBOOL);
                                    geraCodigo(NULL,"CMIG");}
#line 1678 "compilador.tab.c" /* yacc.c:1646  */
    break;

  case 57:
#line 280 "compilador.y" /* yacc.c:1646  */
    {   cmpTipo(TINT);  pushInt(&tipos,TBOOL);
                                    geraCodigo(NULL,"CMME");}
#line 1685 "compilador.tab.c" /* yacc.c:1646  */
    break;

  case 58:
#line 282 "compilador.y" /* yacc.c:1646  */
    {   cmpTipo(TINT);  pushInt(&tipos,TBOOL);
                                    geraCodigo(NULL,"CMMA");}
#line 1692 "compilador.tab.c" /* yacc.c:1646  */
    break;

  case 59:
#line 284 "compilador.y" /* yacc.c:1646  */
    { cmpTipo(TINT); pushInt(&tipos,TBOOL);
                                        geraCodigo(NULL,"CMEG");}
#line 1699 "compilador.tab.c" /* yacc.c:1646  */
    break;

  case 60:
#line 286 "compilador.y" /* yacc.c:1646  */
    { cmpTipo(TINT); pushInt(&tipos,TBOOL);
                                        geraCodigo(NULL,"CMAG");}
#line 1706 "compilador.tab.c" /* yacc.c:1646  */
    break;

  case 62:
#line 291 "compilador.y" /* yacc.c:1646  */
    {   cmpTipo(TINT); pushInt(&tipos,TINT);
                                    geraCodigo(NULL,"SOMA");}
#line 1713 "compilador.tab.c" /* yacc.c:1646  */
    break;

  case 63:
#line 293 "compilador.y" /* yacc.c:1646  */
    {   cmpTipo(TINT); pushInt(&tipos,TINT);
                                    geraCodigo(NULL,"SUBT");}
#line 1720 "compilador.tab.c" /* yacc.c:1646  */
    break;

  case 64:
#line 295 "compilador.y" /* yacc.c:1646  */
    {   cmpTipo(TBOOL); pushInt(&tipos,TBOOL);
                                    geraCodigo(NULL,"CONJ");}
#line 1727 "compilador.tab.c" /* yacc.c:1646  */
    break;

  case 66:
#line 300 "compilador.y" /* yacc.c:1646  */
    {   pushInt(&tipos,TBOOL); cmpTipo(TBOOL);
                                    pushInt(&tipos,TBOOL); geraCodigo(NULL,"NEGA");}
#line 1734 "compilador.tab.c" /* yacc.c:1646  */
    break;

  case 67:
#line 302 "compilador.y" /* yacc.c:1646  */
    {   cmpTipo(TINT); pushInt(&tipos,TINT);
                                    geraCodigo(NULL,"MULT");}
#line 1741 "compilador.tab.c" /* yacc.c:1646  */
    break;

  case 68:
#line 304 "compilador.y" /* yacc.c:1646  */
    {   cmpTipo(TINT); pushInt(&tipos,TINT);
                                    geraCodigo(NULL,"DIVI");}
#line 1748 "compilador.tab.c" /* yacc.c:1646  */
    break;

  case 69:
#line 306 "compilador.y" /* yacc.c:1646  */
    {   cmpTipo(TBOOL); pushInt(&tipos,TBOOL);
                                    geraCodigo(NULL,"DISJ");}
#line 1755 "compilador.tab.c" /* yacc.c:1646  */
    break;

  case 72:
#line 313 "compilador.y" /* yacc.c:1646  */
    {   // Checa se variável está sendo passada para procedure
                        if (procs == NULL)
                            varCodigo(s,0);
                        else
                            varCodigo(s,nparams->val+1);}
#line 1765 "compilador.tab.c" /* yacc.c:1646  */
    break;

  case 74:
#line 319 "compilador.y" /* yacc.c:1646  */
    { geraCodigo(NULL,"CRCT 1"); pushInt(&tipos,TBOOL);}
#line 1771 "compilador.tab.c" /* yacc.c:1646  */
    break;

  case 75:
#line 320 "compilador.y" /* yacc.c:1646  */
    { geraCodigo(NULL,"CRCT 0"); pushInt(&tipos,TBOOL);}
#line 1777 "compilador.tab.c" /* yacc.c:1646  */
    break;

  case 76:
#line 321 "compilador.y" /* yacc.c:1646  */
    { argCodigo("CRCT ",atoi(token));  pushInt(&tipos,TINT);}
#line 1783 "compilador.tab.c" /* yacc.c:1646  */
    break;

  case 77:
#line 325 "compilador.y" /* yacc.c:1646  */
    { s = buscaSimb(tabela,token2);
             if ( s == NULL ) erro(VN_DECL);
             else if ( s->cat != CVAR && s->cat != CPARAM) erro(VN_DECL);
             pushInt(&tipos,s->var.tipo);
             flag_var =1;}
#line 1793 "compilador.tab.c" /* yacc.c:1646  */
    break;

  case 81:
#line 338 "compilador.y" /* yacc.c:1646  */
    {   updateRotulo(rotulo);
                                    nivel_lexico++;
                                    // Adiciona procedimento p à tabela
                                    p = criaSimb(token);
                                    p->cat = CPROC;
                                    p->label = rotulo++;
                                    tabela = pushSimb(tabela,p);
                                    argCodigo("ENPR ",nivel_lexico);}
#line 1806 "compilador.tab.c" /* yacc.c:1646  */
    break;

  case 82:
#line 348 "compilador.y" /* yacc.c:1646  */
    {   s = tabela;
                    // Remove local vars, params e procedures de nl maior
                    while(s->cat != CPROC || s->nivel > nivel_lexico)
                        s = s->abaixo;
                    tabela = s;
                    argCodigo("DMEM ",popInt(&nvars));
                    argsCodigo("RTPR ",nivel_lexico--,p->num_params);}
#line 1818 "compilador.tab.c" /* yacc.c:1646  */
    break;

  case 83:
#line 357 "compilador.y" /* yacc.c:1646  */
    {    updateRotulo(rotulo);
                                    nivel_lexico++;
                                    // Adiciona função p à tabela
                                    p = criaSimb(token);
                                    p->cat = CFUNC;
                                    p->label = rotulo++;
                                    tabela = pushSimb(tabela,p);
                                    argCodigo("ENPR ",nivel_lexico);}
#line 1831 "compilador.tab.c" /* yacc.c:1646  */
    break;

  case 84:
#line 366 "compilador.y" /* yacc.c:1646  */
    {
                    // Considera a "variável" p como um parâmetro
                    p->params[p->num_params].pass = PVAL;
                    p->params[p->num_params].desloc = -(4 + p->num_params);
                    p->params[p->num_params].tipo = (!strcmp("integer",token)?
                                                     TINT:TBOOL);
                }
#line 1843 "compilador.tab.c" /* yacc.c:1646  */
    break;

  case 85:
#line 374 "compilador.y" /* yacc.c:1646  */
    {   s = tabela;
                    // Remove local vars, params e procedures de nl maior
                    while(s->cat != CFUNC || s->nivel > nivel_lexico)
                        s = s->abaixo;
                    tabela = s;
                    argCodigo("DMEM ",popInt(&nvars));
                    argsCodigo("RTPR ",nivel_lexico--,p->num_params);}
#line 1855 "compilador.tab.c" /* yacc.c:1646  */
    break;

  case 86:
#line 384 "compilador.y" /* yacc.c:1646  */
    {   desloc = 0; }
#line 1861 "compilador.tab.c" /* yacc.c:1646  */
    break;

  case 87:
#line 386 "compilador.y" /* yacc.c:1646  */
    {   s = tabela;
                        p->params = malloc((desloc+1) * sizeof(Var));
                        // Copia params da tabela para a lista do procedimento
                        for(i=1; i <= desloc; i++){
                            s->var.desloc = -(3 + i);
                            p->params[desloc - i].desloc = s->var.desloc;
                            p->params[desloc - i].pass = s->var.pass;
                            p->params[desloc - i].tipo = s->var.tipo;
                            s = s->abaixo;
                        }
                        p->num_params = desloc; }
#line 1877 "compilador.tab.c" /* yacc.c:1646  */
    break;

  case 91:
#line 402 "compilador.y" /* yacc.c:1646  */
    {num_idents = 0;}
#line 1883 "compilador.tab.c" /* yacc.c:1646  */
    break;

  case 93:
#line 403 "compilador.y" /* yacc.c:1646  */
    {num_idents = 0;}
#line 1889 "compilador.tab.c" /* yacc.c:1646  */
    break;

  case 95:
#line 407 "compilador.y" /* yacc.c:1646  */
    { // Recebe por ref
                 s = tabela;
                 for(i=0; i < num_idents; i++){
                    s->cat = CPARAM;
                    s->var.pass = PREF;
                    s->var.tipo = (!strcmp("integer",token)?TINT:TBOOL);
                    s = s->abaixo;
                 }}
#line 1902 "compilador.tab.c" /* yacc.c:1646  */
    break;

  case 96:
#line 416 "compilador.y" /* yacc.c:1646  */
    { // Recebe por valor
                 s = tabela;
                 for(i=0; i < num_idents; i++){
                    s->cat = CPARAM;
                    s->var.pass = PVAL;
                    s->var.tipo = (!strcmp("integer",token)?TINT:TBOOL);
                    s = s->abaixo;
                 }}
#line 1915 "compilador.tab.c" /* yacc.c:1646  */
    break;

  case 97:
#line 428 "compilador.y" /* yacc.c:1646  */
    {   p = buscaSimb(tabela,token2);  debug(token2);
                    if ( p == NULL ) erro(PN_DECL);
                    else if ( p->cat != CPROC ) erro(PN_DECL);
                    pushProc(p);
                    pushInt(&nparams,0);}
#line 1925 "compilador.tab.c" /* yacc.c:1646  */
    break;

  case 98:
#line 434 "compilador.y" /* yacc.c:1646  */
    {   p = popProc();
                    num_params = popInt(&nparams);
                    if (num_params < p->num_params)
                        erro(NPARAM);
                    argsCodigo("CHPR R",p->label,nivel_lexico);
                    //printf("rotulo atual: %s\n\n",rotulos->val); fflush(stdout);
                    num_params = 0;}
#line 1937 "compilador.tab.c" /* yacc.c:1646  */
    break;

  case 99:
#line 442 "compilador.y" /* yacc.c:1646  */
    {   p = buscaSimb(tabela,token2);  debug(token2);
                    if ( p == NULL ) erro(PN_DECL);
                    else if ( p->cat != CFUNC ) erro(FN_DECL);
                    pushProc(p);
                    pushInt(&nparams,0);
                    // Abre espaço para valor de retorno
                    geraCodigo(NULL,"AMEM 1");
                    pushInt(&tipos,p->params[0].tipo);}
#line 1950 "compilador.tab.c" /* yacc.c:1646  */
    break;

  case 100:
#line 451 "compilador.y" /* yacc.c:1646  */
    {   p = popProc();
                    num_params = popInt(&nparams);
                    if (num_params < p->num_params)
                        erro(NPARAM);
                    argsCodigo("CHPR R",p->label,nivel_lexico);
                    num_params = 0;}
#line 1961 "compilador.tab.c" /* yacc.c:1646  */
    break;

  case 104:
#line 464 "compilador.y" /* yacc.c:1646  */
    {flag_var = 0;}
#line 1967 "compilador.tab.c" /* yacc.c:1646  */
    break;

  case 105:
#line 464 "compilador.y" /* yacc.c:1646  */
    { popInt(&tipos); }
#line 1973 "compilador.tab.c" /* yacc.c:1646  */
    break;

  case 106:
#line 465 "compilador.y" /* yacc.c:1646  */
    {flag_var = 0;}
#line 1979 "compilador.tab.c" /* yacc.c:1646  */
    break;

  case 107:
#line 465 "compilador.y" /* yacc.c:1646  */
    { popInt(&tipos); }
#line 1985 "compilador.tab.c" /* yacc.c:1646  */
    break;

  case 108:
#line 468 "compilador.y" /* yacc.c:1646  */
    {  p = popProc();
                        num_params = popInt(&nparams);
                        if(p->params[num_params++].pass == PREF && !flag_var)
                            erro(num_params);
                        flag_var=0;
                        // Caso seja por valor, nao precisa fazer nada
                        // porque a expressao ja teve resultado empilhado
                        pushProc(p);
                        pushInt(&nparams,num_params);}
#line 1999 "compilador.tab.c" /* yacc.c:1646  */
    break;

  case 112:
#line 487 "compilador.y" /* yacc.c:1646  */
    {   popInt(&tipos); geraCodigo(NULL,"LEIT");
            if(s->cat == CVAR)
                armzCodigo(s);
            else
                erro(ATRIB); }
#line 2009 "compilador.tab.c" /* yacc.c:1646  */
    break;

  case 113:
#line 495 "compilador.y" /* yacc.c:1646  */
    { popInt(&tipos); geraCodigo(NULL,"IMPR");}
#line 2015 "compilador.tab.c" /* yacc.c:1646  */
    break;

  case 114:
#line 499 "compilador.y" /* yacc.c:1646  */
    { argCodigo("CRCT ",(int)'\n');
          argCodigo("IMPS ",1);}
#line 2022 "compilador.tab.c" /* yacc.c:1646  */
    break;

  case 115:
#line 503 "compilador.y" /* yacc.c:1646  */
    {popInt(&tipos); geraCodigo(NULL,"IMPI");}
#line 2028 "compilador.tab.c" /* yacc.c:1646  */
    break;

  case 118:
#line 506 "compilador.y" /* yacc.c:1646  */
    {popInt(&tipos); geraCodigo(NULL,"IMPI");}
#line 2034 "compilador.tab.c" /* yacc.c:1646  */
    break;

  case 119:
#line 509 "compilador.y" /* yacc.c:1646  */
    {len = 0;}
#line 2040 "compilador.tab.c" /* yacc.c:1646  */
    break;

  case 120:
#line 510 "compilador.y" /* yacc.c:1646  */
    { for(i=0; i < len; i++){
              j = popInt(&string);
              argCodigo("CRCT ",j);
          }
          argCodigo("IMPS ",len);}
#line 2050 "compilador.tab.c" /* yacc.c:1646  */
    break;

  case 121:
#line 519 "compilador.y" /* yacc.c:1646  */
    { for(i=0; i < strlen(texto); i++){
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
#line 2081 "compilador.tab.c" /* yacc.c:1646  */
    break;


#line 2085 "compilador.tab.c" /* yacc.c:1646  */
      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
# define YYSYNTAX_ERROR yysyntax_error (&yymsg_alloc, &yymsg, \
                                        yyssp, yytoken)
      {
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = YYSYNTAX_ERROR;
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == 1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = (char *) YYSTACK_ALLOC (yymsg_alloc);
            if (!yymsg)
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = 2;
              }
            else
              {
                yysyntax_error_status = YYSYNTAX_ERROR;
                yymsgp = yymsg;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
#endif
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYTERROR;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;


      yydestruct ("Error: popping",
                  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;

#if !defined yyoverflow || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  yystos[*yyssp], yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  return yyresult;
}
#line 548 "compilador.y" /* yacc.c:1906  */


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

