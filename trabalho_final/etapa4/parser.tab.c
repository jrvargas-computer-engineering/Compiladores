/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

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

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output, and Bison version.  */
#define YYBISON 30802

/* Bison version string.  */
#define YYBISON_VERSION "3.8.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 5 "parser.y"

#include <stdio.h>
#include <stdlib.h>
#include "asd.h"
#include "tabela.h"
int yylex(void);
void yyerror (char const *mensagem);
void yyerror_semantic(const char *mensagem, int line, int error_code);
extern asd_tree_t *arvore;

#line 82 "parser.tab.c"

# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

#include "parser.tab.h"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_TK_ID = 3,                      /* TK_ID  */
  YYSYMBOL_TK_LI_INTEIRO = 4,              /* TK_LI_INTEIRO  */
  YYSYMBOL_TK_LI_DECIMAL = 5,              /* TK_LI_DECIMAL  */
  YYSYMBOL_TK_SENAO = 6,                   /* TK_SENAO  */
  YYSYMBOL_TK_SE = 7,                      /* TK_SE  */
  YYSYMBOL_TK_RETORNA = 8,                 /* TK_RETORNA  */
  YYSYMBOL_TK_ATRIB = 9,                   /* TK_ATRIB  */
  YYSYMBOL_TK_ENQUANTO = 10,               /* TK_ENQUANTO  */
  YYSYMBOL_TK_COM = 11,                    /* TK_COM  */
  YYSYMBOL_TK_SETA = 12,                   /* TK_SETA  */
  YYSYMBOL_TK_TIPO = 13,                   /* TK_TIPO  */
  YYSYMBOL_TK_VAR = 14,                    /* TK_VAR  */
  YYSYMBOL_TK_DECIMAL = 15,                /* TK_DECIMAL  */
  YYSYMBOL_TK_INTEIRO = 16,                /* TK_INTEIRO  */
  YYSYMBOL_TK_OC_LE = 17,                  /* TK_OC_LE  */
  YYSYMBOL_TK_OC_GE = 18,                  /* TK_OC_GE  */
  YYSYMBOL_TK_OC_EQ = 19,                  /* TK_OC_EQ  */
  YYSYMBOL_TK_OC_NE = 20,                  /* TK_OC_NE  */
  YYSYMBOL_TK_ER = 21,                     /* TK_ER  */
  YYSYMBOL_22_ = 22,                       /* ';'  */
  YYSYMBOL_23_ = 23,                       /* ','  */
  YYSYMBOL_24_ = 24,                       /* '['  */
  YYSYMBOL_25_ = 25,                       /* ']'  */
  YYSYMBOL_26_ = 26,                       /* '('  */
  YYSYMBOL_27_ = 27,                       /* ')'  */
  YYSYMBOL_28_ = 28,                       /* '|'  */
  YYSYMBOL_29_ = 29,                       /* '&'  */
  YYSYMBOL_30_ = 30,                       /* '<'  */
  YYSYMBOL_31_ = 31,                       /* '>'  */
  YYSYMBOL_32_ = 32,                       /* '+'  */
  YYSYMBOL_33_ = 33,                       /* '-'  */
  YYSYMBOL_34_ = 34,                       /* '*'  */
  YYSYMBOL_35_ = 35,                       /* '/'  */
  YYSYMBOL_36_ = 36,                       /* '%'  */
  YYSYMBOL_37_ = 37,                       /* '!'  */
  YYSYMBOL_YYACCEPT = 38,                  /* $accept  */
  YYSYMBOL_programa = 39,                  /* programa  */
  YYSYMBOL_escopo_ini = 40,                /* escopo_ini  */
  YYSYMBOL_escopo_fim = 41,                /* escopo_fim  */
  YYSYMBOL_lista_elementos = 42,           /* lista_elementos  */
  YYSYMBOL_elemento = 43,                  /* elemento  */
  YYSYMBOL_definicao_funcao = 44,          /* definicao_funcao  */
  YYSYMBOL_cabecalho_funcao = 45,          /* cabecalho_funcao  */
  YYSYMBOL_lista_opicional_parametros = 46, /* lista_opicional_parametros  */
  YYSYMBOL_lista_parametros = 47,          /* lista_parametros  */
  YYSYMBOL_parametro = 48,                 /* parametro  */
  YYSYMBOL_corpo_funcao = 49,              /* corpo_funcao  */
  YYSYMBOL_declaracao_variavel_s_ini = 50, /* declaracao_variavel_s_ini  */
  YYSYMBOL_tipo = 51,                      /* tipo  */
  YYSYMBOL_declaracao_variavel_c_ini_opcional = 52, /* declaracao_variavel_c_ini_opcional  */
  YYSYMBOL_inicializacao_inteiro_opcional = 53, /* inicializacao_inteiro_opcional  */
  YYSYMBOL_inicializacao_decimal_opcional = 54, /* inicializacao_decimal_opcional  */
  YYSYMBOL_literal = 55,                   /* literal  */
  YYSYMBOL_comando_simples = 56,           /* comando_simples  */
  YYSYMBOL_bloco_comandos = 57,            /* bloco_comandos  */
  YYSYMBOL_escopo_bloco_ini = 58,          /* escopo_bloco_ini  */
  YYSYMBOL_escopo_bloco_fim = 59,          /* escopo_bloco_fim  */
  YYSYMBOL_lista_comando_simples_opcionais = 60, /* lista_comando_simples_opcionais  */
  YYSYMBOL_lista_comando_simples = 61,     /* lista_comando_simples  */
  YYSYMBOL_comando_atribuicao = 62,        /* comando_atribuicao  */
  YYSYMBOL_chamada_funcao = 63,            /* chamada_funcao  */
  YYSYMBOL_lista_argumentos_opcional = 64, /* lista_argumentos_opcional  */
  YYSYMBOL_lista_argumentos = 65,          /* lista_argumentos  */
  YYSYMBOL_comando_retorno = 66,           /* comando_retorno  */
  YYSYMBOL_construcoes_fluxo_controle = 67, /* construcoes_fluxo_controle  */
  YYSYMBOL_comando_condicional = 68,       /* comando_condicional  */
  YYSYMBOL_senao_opcional = 69,            /* senao_opcional  */
  YYSYMBOL_comando_enquanto = 70,          /* comando_enquanto  */
  YYSYMBOL_expressao = 71,                 /* expressao  */
  YYSYMBOL_expr_nivel7 = 72,               /* expr_nivel7  */
  YYSYMBOL_expr_nivel6 = 73,               /* expr_nivel6  */
  YYSYMBOL_expr_nivel5 = 74,               /* expr_nivel5  */
  YYSYMBOL_expr_nivel4 = 75,               /* expr_nivel4  */
  YYSYMBOL_expr_nivel3 = 76,               /* expr_nivel3  */
  YYSYMBOL_expr_nivel2 = 77,               /* expr_nivel2  */
  YYSYMBOL_expr_nivel1 = 78,               /* expr_nivel1  */
  YYSYMBOL_fator = 79                      /* fator  */
};
typedef enum yysymbol_kind_t yysymbol_kind_t;




#ifdef short
# undef short
#endif

/* On compilers that do not define __PTRDIFF_MAX__ etc., make sure
   <limits.h> and (if available) <stdint.h> are included
   so that the code can choose integer types of a good width.  */

#ifndef __PTRDIFF_MAX__
# include <limits.h> /* INFRINGES ON USER NAME SPACE */
# if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stdint.h> /* INFRINGES ON USER NAME SPACE */
#  define YY_STDINT_H
# endif
#endif

/* Narrow types that promote to a signed type and that can represent a
   signed or unsigned integer of at least N bits.  In tables they can
   save space and decrease cache pressure.  Promoting to a signed type
   helps avoid bugs in integer arithmetic.  */

#ifdef __INT_LEAST8_MAX__
typedef __INT_LEAST8_TYPE__ yytype_int8;
#elif defined YY_STDINT_H
typedef int_least8_t yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef __INT_LEAST16_MAX__
typedef __INT_LEAST16_TYPE__ yytype_int16;
#elif defined YY_STDINT_H
typedef int_least16_t yytype_int16;
#else
typedef short yytype_int16;
#endif

/* Work around bug in HP-UX 11.23, which defines these macros
   incorrectly for preprocessor constants.  This workaround can likely
   be removed in 2023, as HPE has promised support for HP-UX 11.23
   (aka HP-UX 11i v2) only through the end of 2022; see Table 2 of
   <https://h20195.www2.hpe.com/V2/getpdf.aspx/4AA4-7673ENW.pdf>.  */
#ifdef __hpux
# undef UINT_LEAST8_MAX
# undef UINT_LEAST16_MAX
# define UINT_LEAST8_MAX 255
# define UINT_LEAST16_MAX 65535
#endif

#if defined __UINT_LEAST8_MAX__ && __UINT_LEAST8_MAX__ <= __INT_MAX__
typedef __UINT_LEAST8_TYPE__ yytype_uint8;
#elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST8_MAX <= INT_MAX)
typedef uint_least8_t yytype_uint8;
#elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
typedef unsigned char yytype_uint8;
#else
typedef short yytype_uint8;
#endif

#if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
typedef __UINT_LEAST16_TYPE__ yytype_uint16;
#elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST16_MAX <= INT_MAX)
typedef uint_least16_t yytype_uint16;
#elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
typedef unsigned short yytype_uint16;
#else
typedef int yytype_uint16;
#endif

#ifndef YYPTRDIFF_T
# if defined __PTRDIFF_TYPE__ && defined __PTRDIFF_MAX__
#  define YYPTRDIFF_T __PTRDIFF_TYPE__
#  define YYPTRDIFF_MAXIMUM __PTRDIFF_MAX__
# elif defined PTRDIFF_MAX
#  ifndef ptrdiff_t
#   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  endif
#  define YYPTRDIFF_T ptrdiff_t
#  define YYPTRDIFF_MAXIMUM PTRDIFF_MAX
# else
#  define YYPTRDIFF_T long
#  define YYPTRDIFF_MAXIMUM LONG_MAX
# endif
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM                                  \
  YY_CAST (YYPTRDIFF_T,                                 \
           (YYPTRDIFF_MAXIMUM < YY_CAST (YYSIZE_T, -1)  \
            ? YYPTRDIFF_MAXIMUM                         \
            : YY_CAST (YYSIZE_T, -1)))

#define YYSIZEOF(X) YY_CAST (YYPTRDIFF_T, sizeof (X))


/* Stored state numbers (used for stacks). */
typedef yytype_uint8 yy_state_t;

/* State numbers in computations.  */
typedef int yy_state_fast_t;

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


#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YY_USE(E) ((void) (E))
#else
# define YY_USE(E) /* empty */
#endif

/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
#if defined __GNUC__ && ! defined __ICC && 406 <= __GNUC__ * 100 + __GNUC_MINOR__
# if __GNUC__ * 100 + __GNUC_MINOR__ < 407
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")
# else
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# endif
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
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

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif


#define YY_ASSERT(E) ((void) (0 && (E)))

#if 1

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
#endif /* 1 */

#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE)) \
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
        YYPTRDIFF_T yynewbytes;                                         \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * YYSIZEOF (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / YYSIZEOF (*yyptr);                        \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, YY_CAST (YYSIZE_T, (Count)) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYPTRDIFF_T yyi;                      \
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
#define YYLAST   123

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  38
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  42
/* YYNRULES -- Number of rules.  */
#define YYNRULES  84
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  138

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   276


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK                     \
   ? YY_CAST (yysymbol_kind_t, yytranslate[YYX])        \
   : YYSYMBOL_YYUNDEF)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    37,     2,     2,     2,    36,    29,     2,
      26,    27,    34,    32,    23,    33,     2,    35,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,    22,
      30,     2,    31,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    24,     2,    25,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,    28,     2,     2,     2,     2,     2,
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
      15,    16,    17,    18,    19,    20,    21
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,    88,    88,    93,   100,   108,   117,   120,   134,   137,
     145,   157,   199,   200,   203,   209,   212,   223,   233,   240,
     260,   261,   269,   295,   328,   329,   337,   339,   344,   351,
     355,   368,   369,   370,   371,   372,   373,   383,   389,   397,
     405,   406,   410,   413,   426,   455,   495,   496,   502,   505,
     515,   525,   526,   530,   541,   542,   546,   557,   562,   565,
     570,   573,   578,   582,   586,   591,   595,   599,   603,   607,
     612,   615,   619,   624,   627,   630,   636,   643,   647,   651,
     658,   664,   675,   676,   677
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if 1
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "\"invalid token\"", "TK_ID",
  "TK_LI_INTEIRO", "TK_LI_DECIMAL", "TK_SENAO", "TK_SE", "TK_RETORNA",
  "TK_ATRIB", "TK_ENQUANTO", "TK_COM", "TK_SETA", "TK_TIPO", "TK_VAR",
  "TK_DECIMAL", "TK_INTEIRO", "TK_OC_LE", "TK_OC_GE", "TK_OC_EQ",
  "TK_OC_NE", "TK_ER", "';'", "','", "'['", "']'", "'('", "')'", "'|'",
  "'&'", "'<'", "'>'", "'+'", "'-'", "'*'", "'/'", "'%'", "'!'", "$accept",
  "programa", "escopo_ini", "escopo_fim", "lista_elementos", "elemento",
  "definicao_funcao", "cabecalho_funcao", "lista_opicional_parametros",
  "lista_parametros", "parametro", "corpo_funcao",
  "declaracao_variavel_s_ini", "tipo",
  "declaracao_variavel_c_ini_opcional", "inicializacao_inteiro_opcional",
  "inicializacao_decimal_opcional", "literal", "comando_simples",
  "bloco_comandos", "escopo_bloco_ini", "escopo_bloco_fim",
  "lista_comando_simples_opcionais", "lista_comando_simples",
  "comando_atribuicao", "chamada_funcao", "lista_argumentos_opcional",
  "lista_argumentos", "comando_retorno", "construcoes_fluxo_controle",
  "comando_condicional", "senao_opcional", "comando_enquanto", "expressao",
  "expr_nivel7", "expr_nivel6", "expr_nivel5", "expr_nivel4",
  "expr_nivel3", "expr_nivel2", "expr_nivel1", "fator", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-57)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-3)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int8 yypact[] =
{
      16,    31,    34,   -57,    24,    35,   -57,    11,   -57,    17,
     -57,    -4,    41,    48,    34,   -57,   -57,   -57,   -57,   -57,
      10,    -4,   -57,   -57,    25,    62,    69,    64,   -57,    51,
     -57,    -1,    49,    14,    50,    74,   -57,    25,   -57,   -57,
     -57,   -57,   -57,   -57,   -57,   -57,   -57,    -4,   -57,   -57,
      69,    14,    14,    14,    52,   -57,   -57,    14,    14,    14,
      14,   -57,   -57,    70,    53,    54,    -5,    -8,    27,    22,
     -57,   -57,    14,    71,   -57,    57,   -57,   -57,   -57,    58,
     -57,    61,    60,    63,   -57,   -57,   -57,    -4,    14,    14,
      14,    14,    14,    14,    14,    14,    14,    14,    14,    14,
      14,    65,    46,   -57,   -57,    14,    17,   -57,   -57,    54,
      -5,    -8,    -8,    27,    27,    27,    27,    22,    22,   -57,
     -57,   -57,    17,    75,    77,   -57,    83,   -57,    59,   -57,
      87,   -57,    17,   -57,   -57,   -57,   -57,   -57
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       4,     0,     0,     1,     0,     0,     5,     6,     8,     0,
       9,     0,     0,     0,     0,    38,    10,    18,    20,    21,
      12,     0,     3,     7,    40,     0,     0,     0,    14,    15,
      19,     0,     0,     0,     0,     0,    32,    42,    31,    39,
      41,    33,    34,    35,    36,    51,    52,     0,    13,    11,
       0,     0,    46,     0,    81,    29,    30,     0,     0,     0,
       0,    82,    83,     0,    57,    59,    61,    64,    69,    72,
      76,    80,     0,     0,    43,     0,    17,    16,    44,     0,
      47,    48,     0,     0,    77,    78,    79,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    37,    45,     0,     0,    84,    50,    58,
      60,    62,    63,    67,    68,    65,    66,    70,    71,    73,
      74,    75,     0,    26,    24,    49,    54,    56,     0,    23,
       0,    22,     0,    53,    28,    27,    25,    55
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -57,   -57,   -57,   -57,    79,   -57,   -57,   -57,   -57,   -21,
     -57,   -57,   -57,   -20,   -57,   -57,   -57,   -57,   -57,    -9,
     -57,   -57,   -57,    66,   -57,   -17,   -57,   -11,   -57,   -57,
     -57,   -57,   -57,   -27,   -57,     7,     9,   -25,   -40,   -28,
     -56,   -57
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_uint8 yydefgoto[] =
{
       0,     1,     2,    13,     6,     7,     8,     9,    27,    28,
      29,    16,    10,    20,    36,   131,   129,    61,    37,    38,
      24,    75,    39,    40,    41,    62,    79,    80,    43,    44,
      45,   133,    46,    81,    64,    65,    66,    67,    68,    69,
      70,    71
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      17,    30,    84,    85,    86,    48,    63,    42,    51,    92,
      93,    18,    19,    25,    90,    91,    -2,    54,    55,    56,
      42,    26,    94,    95,    78,    52,    82,    76,    31,    77,
      83,     3,    32,    33,    14,    34,    11,     4,    12,    35,
      57,    15,   119,   120,   121,   101,    58,    59,     5,    15,
      21,    60,   113,   114,   115,   116,    98,    99,   100,    96,
      97,   123,   124,   134,   135,   111,   112,   108,   117,   118,
      22,    47,    25,    49,    50,    53,    72,    73,    52,    87,
     102,    88,   103,    89,   105,   104,   128,   106,   130,   132,
     107,   136,   122,    23,   125,   109,     0,   126,   110,     0,
       0,     0,     0,    74,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   127,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   137
};

static const yytype_int16 yycheck[] =
{
       9,    21,    58,    59,    60,    26,    33,    24,     9,    17,
      18,    15,    16,     3,    19,    20,     0,     3,     4,     5,
      37,    11,    30,    31,    51,    26,    53,    47,     3,    50,
      57,     0,     7,     8,    23,    10,    12,     3,     3,    14,
      26,    24,    98,    99,   100,    72,    32,    33,    14,    24,
       9,    37,    92,    93,    94,    95,    34,    35,    36,    32,
      33,    15,    16,     4,     5,    90,    91,    87,    96,    97,
      22,     9,     3,     9,    23,    26,    26,     3,    26,     9,
       9,    28,    25,    29,    23,    27,    11,    27,    11,     6,
      27,     4,    27,    14,   105,    88,    -1,   106,    89,    -1,
      -1,    -1,    -1,    37,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   122,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   132
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,    39,    40,     0,     3,    14,    42,    43,    44,    45,
      50,    12,     3,    41,    23,    24,    49,    57,    15,    16,
      51,     9,    22,    42,    58,     3,    11,    46,    47,    48,
      51,     3,     7,     8,    10,    14,    52,    56,    57,    60,
      61,    62,    63,    66,    67,    68,    70,     9,    47,     9,
      23,     9,    26,    26,     3,     4,     5,    26,    32,    33,
      37,    55,    63,    71,    72,    73,    74,    75,    76,    77,
      78,    79,    26,     3,    61,    59,    51,    47,    71,    64,
      65,    71,    71,    71,    78,    78,    78,     9,    28,    29,
      19,    20,    17,    18,    30,    31,    32,    33,    34,    35,
      36,    71,     9,    25,    27,    23,    27,    27,    51,    73,
      74,    75,    75,    76,    76,    76,    76,    77,    77,    78,
      78,    78,    27,    15,    16,    65,    57,    57,    11,    54,
      11,    53,     6,    69,     4,     5,     4,    57
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    38,    39,    39,    40,    41,    42,    42,    43,    43,
      44,    45,    46,    46,    46,    47,    47,    48,    49,    50,
      51,    51,    52,    52,    53,    53,    54,    54,    54,    55,
      55,    56,    56,    56,    56,    56,    56,    57,    58,    59,
      60,    60,    61,    61,    62,    63,    64,    64,    65,    65,
      66,    67,    67,    68,    69,    69,    70,    71,    72,    72,
      73,    73,    74,    74,    74,    75,    75,    75,    75,    75,
      76,    76,    76,    77,    77,    77,    77,    78,    78,    78,
      78,    79,    79,    79,    79
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     0,     4,     0,     0,     1,     3,     1,     1,
       2,     5,     0,     2,     1,     1,     3,     3,     1,     4,
       1,     1,     5,     5,     0,     2,     0,     2,     2,     1,
       1,     1,     1,     1,     1,     1,     1,     5,     0,     0,
       0,     1,     1,     2,     3,     4,     0,     1,     1,     3,
       4,     1,     1,     6,     0,     2,     5,     1,     3,     1,
       3,     1,     3,     3,     1,     3,     3,     3,     3,     1,
       3,     3,     1,     3,     3,     3,     1,     2,     2,     2,
       1,     1,     1,     1,     3
};


enum { YYENOMEM = -2 };

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYNOMEM         goto yyexhaustedlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
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

/* Backward compatibility with an undocumented macro.
   Use YYerror or YYUNDEF. */
#define YYERRCODE YYUNDEF


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




# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  FILE *yyoutput = yyo;
  YY_USE (yyoutput);
  if (!yyvaluep)
    return;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo,
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  yy_symbol_value_print (yyo, yykind, yyvaluep);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yy_state_t *yybottom, yy_state_t *yytop)
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
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp,
                 int yyrule)
{
  int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %d):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       YY_ACCESSING_SYMBOL (+yyssp[yyi + 1 - yynrhs]),
                       &yyvsp[(yyi + 1) - (yynrhs)]);
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
# define YYDPRINTF(Args) ((void) 0)
# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)
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


/* Context of a parse error.  */
typedef struct
{
  yy_state_t *yyssp;
  yysymbol_kind_t yytoken;
} yypcontext_t;

/* Put in YYARG at most YYARGN of the expected tokens given the
   current YYCTX, and return the number of tokens stored in YYARG.  If
   YYARG is null, return the number of expected tokens (guaranteed to
   be less than YYNTOKENS).  Return YYENOMEM on memory exhaustion.
   Return 0 if there are more than YYARGN expected tokens, yet fill
   YYARG up to YYARGN. */
static int
yypcontext_expected_tokens (const yypcontext_t *yyctx,
                            yysymbol_kind_t yyarg[], int yyargn)
{
  /* Actual size of YYARG. */
  int yycount = 0;
  int yyn = yypact[+*yyctx->yyssp];
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
        if (yycheck[yyx + yyn] == yyx && yyx != YYSYMBOL_YYerror
            && !yytable_value_is_error (yytable[yyx + yyn]))
          {
            if (!yyarg)
              ++yycount;
            else if (yycount == yyargn)
              return 0;
            else
              yyarg[yycount++] = YY_CAST (yysymbol_kind_t, yyx);
          }
    }
  if (yyarg && yycount == 0 && 0 < yyargn)
    yyarg[0] = YYSYMBOL_YYEMPTY;
  return yycount;
}




#ifndef yystrlen
# if defined __GLIBC__ && defined _STRING_H
#  define yystrlen(S) (YY_CAST (YYPTRDIFF_T, strlen (S)))
# else
/* Return the length of YYSTR.  */
static YYPTRDIFF_T
yystrlen (const char *yystr)
{
  YYPTRDIFF_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
# endif
#endif

#ifndef yystpcpy
# if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#  define yystpcpy stpcpy
# else
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
# endif
#endif

#ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYPTRDIFF_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYPTRDIFF_T yyn = 0;
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
            else
              goto append;

          append:
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

  if (yyres)
    return yystpcpy (yyres, yystr) - yyres;
  else
    return yystrlen (yystr);
}
#endif


static int
yy_syntax_error_arguments (const yypcontext_t *yyctx,
                           yysymbol_kind_t yyarg[], int yyargn)
{
  /* Actual size of YYARG. */
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
  if (yyctx->yytoken != YYSYMBOL_YYEMPTY)
    {
      int yyn;
      if (yyarg)
        yyarg[yycount] = yyctx->yytoken;
      ++yycount;
      yyn = yypcontext_expected_tokens (yyctx,
                                        yyarg ? yyarg + 1 : yyarg, yyargn - 1);
      if (yyn == YYENOMEM)
        return YYENOMEM;
      else
        yycount += yyn;
    }
  return yycount;
}

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return -1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return YYENOMEM if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYPTRDIFF_T *yymsg_alloc, char **yymsg,
                const yypcontext_t *yyctx)
{
  enum { YYARGS_MAX = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat: reported tokens (one for the "unexpected",
     one per "expected"). */
  yysymbol_kind_t yyarg[YYARGS_MAX];
  /* Cumulated lengths of YYARG.  */
  YYPTRDIFF_T yysize = 0;

  /* Actual size of YYARG. */
  int yycount = yy_syntax_error_arguments (yyctx, yyarg, YYARGS_MAX);
  if (yycount == YYENOMEM)
    return YYENOMEM;

  switch (yycount)
    {
#define YYCASE_(N, S)                       \
      case N:                               \
        yyformat = S;                       \
        break
    default: /* Avoid compiler warnings. */
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
#undef YYCASE_
    }

  /* Compute error message size.  Don't count the "%s"s, but reserve
     room for the terminator.  */
  yysize = yystrlen (yyformat) - 2 * yycount + 1;
  {
    int yyi;
    for (yyi = 0; yyi < yycount; ++yyi)
      {
        YYPTRDIFF_T yysize1
          = yysize + yytnamerr (YY_NULLPTR, yytname[yyarg[yyi]]);
        if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
          yysize = yysize1;
        else
          return YYENOMEM;
      }
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return -1;
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
          yyp += yytnamerr (yyp, yytname[yyarg[yyi++]]);
          yyformat += 2;
        }
      else
        {
          ++yyp;
          ++yyformat;
        }
  }
  return 0;
}


/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg,
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep)
{
  YY_USE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/* Lookahead token kind.  */
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
    yy_state_fast_t yystate = 0;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus = 0;

    /* Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* Their size.  */
    YYPTRDIFF_T yystacksize = YYINITDEPTH;

    /* The state stack: array, bottom, top.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss = yyssa;
    yy_state_t *yyssp = yyss;

    /* The semantic value stack: array, bottom, top.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs = yyvsa;
    YYSTYPE *yyvsp = yyvs;

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYPTRDIFF_T yymsg_alloc = sizeof yymsgbuf;

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yychar = YYEMPTY; /* Cause a token to be read.  */

  goto yysetstate;


/*------------------------------------------------------------.
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yysetstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
  YY_IGNORE_USELESS_CAST_BEGIN
  *yyssp = YY_CAST (yy_state_t, yystate);
  YY_IGNORE_USELESS_CAST_END
  YY_STACK_PRINT (yyss, yyssp);

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    YYNOMEM;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYPTRDIFF_T yysize = yyssp - yyss + 1;

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        yy_state_t *yyss1 = yyss;
        YYSTYPE *yyvs1 = yyvs;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        YYNOMEM;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          YYNOMEM;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YY_IGNORE_USELESS_CAST_BEGIN
      YYDPRINTF ((stderr, "Stack size increased to %ld\n",
                  YY_CAST (long, yystacksize)));
      YY_IGNORE_USELESS_CAST_END

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */


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

  /* YYCHAR is either empty, or end-of-input, or a valid lookahead.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token\n"));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = YYEOF;
      yytoken = YYSYMBOL_YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else if (yychar == YYerror)
    {
      /* The scanner already issued an error message, process directly
         to error recovery.  But do not keep the error token as
         lookahead, it is too special and may lead us to an endless
         loop in error recovery. */
      yychar = YYUNDEF;
      yytoken = YYSYMBOL_YYerror;
      goto yyerrlab1;
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
  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  /* Discard the shifted token.  */
  yychar = YYEMPTY;
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
| yyreduce -- do a reduction.  |
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
  case 2: /* programa: %empty  */
#line 88 "parser.y"
           { 
        (yyval.arvore) = NULL;
        arvore = (yyval.arvore);
    }
#line 1521 "parser.tab.c"
    break;

  case 3: /* programa: escopo_ini lista_elementos escopo_fim ';'  */
#line 93 "parser.y"
                                                {
        (yyval.arvore) = (yyvsp[-2].arvore);
        arvore = (yyval.arvore);
    }
#line 1530 "parser.tab.c"
    break;

  case 4: /* escopo_ini: %empty  */
#line 100 "parser.y"
           {
        table_t* tabela_global = table_create(); 
        scope_stack_push(tabela_global);
        (yyval.arvore) = NULL;
    }
#line 1540 "parser.tab.c"
    break;

  case 5: /* escopo_fim: %empty  */
#line 108 "parser.y"
           {
        table_t* tabela_global = scope_stack_pop();
        table_free(tabela_global);
        (yyval.arvore) = NULL; 
    }
#line 1550 "parser.tab.c"
    break;

  case 6: /* lista_elementos: elemento  */
#line 117 "parser.y"
            {
        (yyval.arvore) = (yyvsp[0].arvore); //primeiro elemento
    }
#line 1558 "parser.tab.c"
    break;

  case 7: /* lista_elementos: elemento ',' lista_elementos  */
#line 120 "parser.y"
                                    { //fix:mudei para poder ter null 
        if((yyvsp[-2].arvore) != NULL){
            (yyval.arvore) = (yyvsp[-2].arvore); 
            if((yyvsp[0].arvore) != NULL){
                asd_add_child((yyval.arvore), (yyvsp[0].arvore));
            }
        }
        else {
           (yyval.arvore) = (yyvsp[0].arvore); 
        }
    }
#line 1574 "parser.tab.c"
    break;

  case 8: /* elemento: definicao_funcao  */
#line 134 "parser.y"
                     {
        (yyval.arvore) = (yyvsp[0].arvore);
    }
#line 1582 "parser.tab.c"
    break;

  case 9: /* elemento: declaracao_variavel_s_ini  */
#line 137 "parser.y"
                                { //fix: mudei para null, para nao por na arvore
        (yyval.arvore) = NULL; 
    }
#line 1590 "parser.tab.c"
    break;

  case 10: /* definicao_funcao: cabecalho_funcao corpo_funcao  */
#line 145 "parser.y"
                                  {
        (yyval.arvore) = (yyvsp[-1].arvore);
        if((yyvsp[0].arvore) != NULL)
            asd_add_child((yyval.arvore), (yyvsp[0].arvore)); 

        //definicao funcao eh onde escopo eh destruido
        table_t* tabela_funcao = scope_stack_pop();
        table_free(tabela_funcao);
    }
#line 1604 "parser.tab.c"
    break;

  case 11: /* cabecalho_funcao: TK_ID TK_SETA tipo lista_opicional_parametros TK_ATRIB  */
#line 157 "parser.y"
                                                          {
        //$$ = new_node_from_lexval($1); 

        (yyval.arvore) = asd_new((yyvsp[-4].valor_lex)->value); 
        (yyval.arvore)->data_type = (yyvsp[-2].semantic_type); 

        //$4 NAO DEVE SER adicionada na arvore
        //pensar sobre depois
        //if ($4 != NULL) {
        //    asd_add_child($$, $4);
        //}    

        /* CRIAR ESCOPO DA FUNCAO */
        table_t* tabela_funcao = table_create();


        int num_args = 0;
        semantic_type_t* arg_types = extract_and_store_params(tabela_funcao, (yyvsp[-1].arvore), &num_args);
        
        //aqui os parametros serao colocados na tabela ($4)
        table_t* escopo_pai = scope_stack_peek();
        
        if (table_find(escopo_pai, (yyvsp[-4].valor_lex)->value) != NULL) {
            yyerror_semantic("Funcao ja declarada.", (yyvsp[-4].valor_lex)->line, ERR_DECLARED);
        }
        symbol_t* func_symbol = symbol_create_func((yyvsp[-4].valor_lex), (yyvsp[-2].semantic_type), num_args, arg_types); 
        table_insert(escopo_pai, func_symbol); 
        

        scope_stack_push(tabela_funcao);
        free(arg_types);
        //asd_free($4);
        //free($1->value);
        //free($1);    

    }
#line 1645 "parser.tab.c"
    break;

  case 12: /* lista_opicional_parametros: %empty  */
#line 199 "parser.y"
           {(yyval.arvore) = NULL;}
#line 1651 "parser.tab.c"
    break;

  case 13: /* lista_opicional_parametros: TK_COM lista_parametros  */
#line 200 "parser.y"
                              { 
        (yyval.arvore) = (yyvsp[0].arvore);
    }
#line 1659 "parser.tab.c"
    break;

  case 14: /* lista_opicional_parametros: lista_parametros  */
#line 203 "parser.y"
                       { 
        (yyval.arvore) = (yyvsp[0].arvore);
    }
#line 1667 "parser.tab.c"
    break;

  case 15: /* lista_parametros: parametro  */
#line 209 "parser.y"
              {
        (yyval.arvore) = (yyvsp[0].arvore); 
    }
#line 1675 "parser.tab.c"
    break;

  case 16: /* lista_parametros: parametro ',' lista_parametros  */
#line 212 "parser.y"
                                      {
        (yyval.arvore) = (yyvsp[-2].arvore);
        asd_add_child((yyval.arvore), (yyvsp[0].arvore)); 
    }
#line 1684 "parser.tab.c"
    break;

  case 17: /* parametro: TK_ID TK_ATRIB tipo  */
#line 223 "parser.y"
                        {
        (yyval.arvore) = new_node_from_lexval((yyvsp[-2].valor_lex)); 
        if ((yyval.arvore)) {
            (yyval.arvore)->data_type = (yyvsp[0].semantic_type); // <-- CORREÇÃO
        }
    }
#line 1695 "parser.tab.c"
    break;

  case 18: /* corpo_funcao: bloco_comandos  */
#line 233 "parser.y"
                   {
        (yyval.arvore) = (yyvsp[0].arvore); 
    }
#line 1703 "parser.tab.c"
    break;

  case 19: /* declaracao_variavel_s_ini: TK_VAR TK_ID TK_ATRIB tipo  */
#line 240 "parser.y"
                               {
       
        //pegar o escopo atual
        table_t* escopo_atual = scope_stack_peek();

        //verifica se simbolo esta declarado neste escopo 
        if (table_find(escopo_atual, (yyvsp[-2].valor_lex)->value) != NULL) {
            yyerror_semantic("Identificador ja declarado.", (yyvsp[-2].valor_lex)->line, ERR_DECLARED);
        }
        symbol_t* novo_simbolo = symbol_create_var((yyvsp[-2].valor_lex), (yyvsp[0].semantic_type));
        table_insert(escopo_atual, novo_simbolo);     
        (yyval.arvore) = NULL;
        
        //o ponteiro $2 agora esta salvo na tabela de simbolos
        //free($2->value);
        //free($2); 
    }
#line 1725 "parser.tab.c"
    break;

  case 20: /* tipo: TK_DECIMAL  */
#line 260 "parser.y"
               {(yyval.semantic_type) = SEMANTIC_TYPE_FLOAT; }
#line 1731 "parser.tab.c"
    break;

  case 21: /* tipo: TK_INTEIRO  */
#line 261 "parser.y"
                 {(yyval.semantic_type) = SEMANTIC_TYPE_INT; }
#line 1737 "parser.tab.c"
    break;

  case 22: /* declaracao_variavel_c_ini_opcional: TK_VAR TK_ID TK_ATRIB TK_INTEIRO inicializacao_inteiro_opcional  */
#line 269 "parser.y"
                                                                   {
        
        table_t* escopo_atual = scope_stack_peek();
        //verifica se simbolo esta declarado neste escopo 
        if (table_find(escopo_atual, (yyvsp[-3].valor_lex)->value) != NULL) {
            yyerror_semantic("Identificador ja declarado.", (yyvsp[-3].valor_lex)->line, ERR_DECLARED);
        }
        
        symbol_t* novo_simbolo = symbol_create_var((yyvsp[-3].valor_lex), SEMANTIC_TYPE_INT);
        table_insert(escopo_atual, novo_simbolo);
        
        if((yyvsp[0].arvore) == NULL){
            (yyval.arvore) = NULL;
        }
        else{
            if ((yyvsp[0].arvore)->data_type != SEMANTIC_TYPE_INT) {
                yyerror_semantic("Inicializacao incompativel. Esperava 'inteiro'.", (yyvsp[-3].valor_lex)->line, ERR_WRONG_TYPE);
            }
            (yyval.arvore) = asd_new("com"); 
            asd_tree_t* tk_id_no = asd_new((yyvsp[-3].valor_lex)->value);
            asd_add_child((yyval.arvore), tk_id_no);
            asd_add_child((yyval.arvore), (yyvsp[0].arvore));
        }
        //free($2->value);
        //free($2);
    }
#line 1768 "parser.tab.c"
    break;

  case 23: /* declaracao_variavel_c_ini_opcional: TK_VAR TK_ID TK_ATRIB TK_DECIMAL inicializacao_decimal_opcional  */
#line 295 "parser.y"
                                                                     {
       
        table_t* escopo_atual = scope_stack_peek();
        
        //verifica se simbolo esta declarado neste escopo 
        if (table_find(escopo_atual, (yyvsp[-3].valor_lex)->value) != NULL) {
            yyerror_semantic("Identificador ja declarado.", (yyvsp[-3].valor_lex)->line, ERR_DECLARED);
        }
       
        symbol_t* novo_simbolo = symbol_create_var((yyvsp[-3].valor_lex), SEMANTIC_TYPE_FLOAT);
        table_insert(escopo_atual, novo_simbolo);
        
        if((yyvsp[0].arvore) == NULL){
            (yyval.arvore) = NULL; 
        }
        else{
            if ((yyvsp[0].arvore)->data_type != SEMANTIC_TYPE_FLOAT) {
                yyerror_semantic("Inicializacao incompativel. Esperava 'decimal'.", (yyvsp[-3].valor_lex)->line, ERR_WRONG_TYPE);
            }
            (yyval.arvore) = asd_new("com"); 
            asd_tree_t* tk_id_no = asd_new((yyvsp[-3].valor_lex)->value);
            asd_add_child((yyval.arvore), tk_id_no);
            asd_add_child((yyval.arvore), (yyvsp[0].arvore));
        }
        //free($2->value);
        //free($2);
    }
#line 1800 "parser.tab.c"
    break;

  case 24: /* inicializacao_inteiro_opcional: %empty  */
#line 328 "parser.y"
           {(yyval.arvore) = NULL;}
#line 1806 "parser.tab.c"
    break;

  case 25: /* inicializacao_inteiro_opcional: TK_COM TK_LI_INTEIRO  */
#line 329 "parser.y"
                           {
        (yyval.arvore) = new_node_from_lexval((yyvsp[0].valor_lex)); 
        (yyval.arvore)->data_type = SEMANTIC_TYPE_INT;         
    }
#line 1815 "parser.tab.c"
    break;

  case 26: /* inicializacao_decimal_opcional: %empty  */
#line 337 "parser.y"
           {(yyval.arvore) = NULL;}
#line 1821 "parser.tab.c"
    break;

  case 27: /* inicializacao_decimal_opcional: TK_COM TK_LI_DECIMAL  */
#line 339 "parser.y"
                             { 
        (yyval.arvore) = new_node_from_lexval((yyvsp[0].valor_lex)); 
        (yyval.arvore)->data_type = SEMANTIC_TYPE_FLOAT; 

    }
#line 1831 "parser.tab.c"
    break;

  case 28: /* inicializacao_decimal_opcional: TK_COM TK_LI_INTEIRO  */
#line 344 "parser.y"
                            {// E também aceita literal inteiro (ex: var d := decimal com 5)
        (yyval.arvore) = new_node_from_lexval((yyvsp[0].valor_lex)); 
        (yyval.arvore)->data_type = SEMANTIC_TYPE_INT; 
    }
#line 1840 "parser.tab.c"
    break;

  case 29: /* literal: TK_LI_INTEIRO  */
#line 351 "parser.y"
                  {
        (yyval.arvore) = new_node_from_lexval((yyvsp[0].valor_lex)); 
        (yyval.arvore)->data_type = SEMANTIC_TYPE_INT; 
    }
#line 1849 "parser.tab.c"
    break;

  case 30: /* literal: TK_LI_DECIMAL  */
#line 355 "parser.y"
                    {
        (yyval.arvore) = new_node_from_lexval((yyvsp[0].valor_lex)); 
        (yyval.arvore)->data_type = SEMANTIC_TYPE_FLOAT; 
    }
#line 1858 "parser.tab.c"
    break;

  case 31: /* comando_simples: bloco_comandos  */
#line 368 "parser.y"
                   { (yyval.arvore) = (yyvsp[0].arvore); }
#line 1864 "parser.tab.c"
    break;

  case 32: /* comando_simples: declaracao_variavel_c_ini_opcional  */
#line 369 "parser.y"
                                         { if((yyvsp[0].arvore) == NULL ){(yyval.arvore) = NULL;} else{(yyval.arvore) = (yyvsp[0].arvore);} }
#line 1870 "parser.tab.c"
    break;

  case 33: /* comando_simples: comando_atribuicao  */
#line 370 "parser.y"
                         { (yyval.arvore) = (yyvsp[0].arvore); }
#line 1876 "parser.tab.c"
    break;

  case 34: /* comando_simples: chamada_funcao  */
#line 371 "parser.y"
                     { (yyval.arvore) = (yyvsp[0].arvore); }
#line 1882 "parser.tab.c"
    break;

  case 35: /* comando_simples: comando_retorno  */
#line 372 "parser.y"
                      { (yyval.arvore) = (yyvsp[0].arvore); }
#line 1888 "parser.tab.c"
    break;

  case 36: /* comando_simples: construcoes_fluxo_controle  */
#line 373 "parser.y"
                                 { (yyval.arvore) = (yyvsp[0].arvore); }
#line 1894 "parser.tab.c"
    break;

  case 37: /* bloco_comandos: '[' escopo_bloco_ini lista_comando_simples_opcionais escopo_bloco_fim ']'  */
#line 383 "parser.y"
                                                                           {
        (yyval.arvore) = (yyvsp[-2].arvore);
    }
#line 1902 "parser.tab.c"
    break;

  case 38: /* escopo_bloco_ini: %empty  */
#line 389 "parser.y"
           {
        table_t* tabela_bloco = table_create(); 
        scope_stack_push(tabela_bloco);
        (yyval.arvore) = NULL;   
    }
#line 1912 "parser.tab.c"
    break;

  case 39: /* escopo_bloco_fim: %empty  */
#line 397 "parser.y"
           {
        table_t* tabela_bloco = scope_stack_pop();
        table_free(tabela_bloco);
        (yyval.arvore) = NULL;
    }
#line 1922 "parser.tab.c"
    break;

  case 40: /* lista_comando_simples_opcionais: %empty  */
#line 405 "parser.y"
           {(yyval.arvore) = NULL;}
#line 1928 "parser.tab.c"
    break;

  case 41: /* lista_comando_simples_opcionais: lista_comando_simples  */
#line 406 "parser.y"
                            { (yyval.arvore) = (yyvsp[0].arvore); }
#line 1934 "parser.tab.c"
    break;

  case 42: /* lista_comando_simples: comando_simples  */
#line 410 "parser.y"
                   {
        if((yyvsp[0].arvore) == NULL ){(yyval.arvore) = NULL;} else{(yyval.arvore) = (yyvsp[0].arvore);} 
    }
#line 1942 "parser.tab.c"
    break;

  case 43: /* lista_comando_simples: comando_simples lista_comando_simples  */
#line 413 "parser.y"
                                             {
       
       if((yyvsp[-1].arvore) == NULL ){
            (yyval.arvore) = (yyvsp[0].arvore);
        } else{
            (yyval.arvore) = (yyvsp[-1].arvore);
            asd_add_child((yyvsp[-1].arvore), (yyvsp[0].arvore));    
        } 
    }
#line 1956 "parser.tab.c"
    break;

  case 44: /* comando_atribuicao: TK_ID TK_ATRIB expressao  */
#line 426 "parser.y"
                             {
        symbol_t* simbolo = stack_find_global((yyvsp[-2].valor_lex)->value);
        
        if (simbolo == NULL) {
            yyerror_semantic("Identificador nao declarado.", (yyvsp[-2].valor_lex)->line, ERR_UNDECLARED);
        }
        if (simbolo->nature == SYMBOL_FUNCAO) {
            yyerror_semantic("Funcao usada como variavel em atribuicao.", (yyvsp[-2].valor_lex)->line, ERR_FUNCTION);
        }

        // 4. (Passo 6) Verifique os tipos
        // (Será feito no Passo 6, mas a informação está aqui)
        // if (simbolo->data_type != $3->data_type) { ... }
        if (simbolo->data_type != (yyvsp[0].arvore)->data_type) {
            yyerror_semantic("Atribuicao de tipo incompativel.", (yyvsp[-2].valor_lex)->line, ERR_WRONG_TYPE);
        }

        (yyval.arvore) = asd_new(":="); 
        asd_tree_t* tk_id_no = asd_new((yyvsp[-2].valor_lex)->value);
        tk_id_no->data_type = simbolo->data_type;
        asd_add_child((yyval.arvore), tk_id_no); 
        asd_add_child((yyval.arvore), (yyvsp[0].arvore));      
        free((yyvsp[-2].valor_lex)->value);
        free((yyvsp[-2].valor_lex));
    }
#line 1986 "parser.tab.c"
    break;

  case 45: /* chamada_funcao: TK_ID '(' lista_argumentos_opcional ')'  */
#line 455 "parser.y"
                                            {
        symbol_t* simbolo = stack_find_global((yyvsp[-3].valor_lex)->value);   
        
        if (simbolo == NULL) {
            yyerror_semantic("Funcao nao declarada.", (yyvsp[-3].valor_lex)->line, ERR_UNDECLARED);
        }     

        if (simbolo->nature == SYMBOL_ID) {
            yyerror_semantic("Variavel usada como funcao.", (yyvsp[-3].valor_lex)->line, ERR_VARIABLE);
        }


        //conta argumentos e compara
        int provided_arg_count = count_params((yyvsp[-1].arvore));
        if (provided_arg_count < simbolo->num_args) {
            yyerror_semantic("Faltam argumentos na chamada da funcao.", (yyvsp[-3].valor_lex)->line, ERR_MISSING_ARGS);
        }    
        if (provided_arg_count > simbolo->num_args) {
            yyerror_semantic("Argumentos em excesso na chamada da funcao.", (yyvsp[-3].valor_lex)->line, ERR_EXCESS_ARGS);
        }
        //compara os tipos
        if (simbolo->num_args > 0 && provided_arg_count == simbolo->num_args) {
            check_argument_types(simbolo, (yyvsp[-1].arvore));
        }
        
        char label[256];
        sprintf(label, "call %s", (yyvsp[-3].valor_lex)->value);
        (yyval.arvore) = asd_new(label);
        
        (yyval.arvore)->line = (yyvsp[-3].valor_lex)->line;
        (yyval.arvore)->data_type = simbolo->data_type;

        if ((yyvsp[-1].arvore) != NULL) asd_add_child((yyval.arvore), (yyvsp[-1].arvore));
        free((yyvsp[-3].valor_lex)->value);
        free((yyvsp[-3].valor_lex));       
    }
#line 2027 "parser.tab.c"
    break;

  case 46: /* lista_argumentos_opcional: %empty  */
#line 495 "parser.y"
           {(yyval.arvore) = NULL;}
#line 2033 "parser.tab.c"
    break;

  case 48: /* lista_argumentos: expressao  */
#line 502 "parser.y"
             {
        (yyval.arvore) = (yyvsp[0].arvore); 
    }
#line 2041 "parser.tab.c"
    break;

  case 49: /* lista_argumentos: expressao ',' lista_argumentos  */
#line 505 "parser.y"
                                      {
        (yyval.arvore) = (yyvsp[-2].arvore);
        asd_add_child((yyval.arvore), (yyvsp[0].arvore));
    }
#line 2050 "parser.tab.c"
    break;

  case 50: /* comando_retorno: TK_RETORNA expressao TK_ATRIB tipo  */
#line 515 "parser.y"
                                      {
        if ((yyvsp[-2].arvore)->data_type != (yyvsp[0].semantic_type)) {
             yyerror_semantic("Tipo de retorno incompativel com a declaracao da funcao.", (yyvsp[-2].arvore)->line, ERR_WRONG_TYPE);
        }
        (yyval.arvore) = new_node_from_unary_op("retorna", (yyvsp[-2].arvore));  
        (yyval.arvore)->data_type = (yyvsp[-2].arvore)->data_type; 
    }
#line 2062 "parser.tab.c"
    break;

  case 51: /* construcoes_fluxo_controle: comando_condicional  */
#line 525 "parser.y"
                        { (yyval.arvore) = (yyvsp[0].arvore);}
#line 2068 "parser.tab.c"
    break;

  case 52: /* construcoes_fluxo_controle: comando_enquanto  */
#line 526 "parser.y"
                       { (yyval.arvore) = (yyvsp[0].arvore); }
#line 2074 "parser.tab.c"
    break;

  case 53: /* comando_condicional: TK_SE '(' expressao ')' bloco_comandos senao_opcional  */
#line 530 "parser.y"
                                                         {
        if ((yyvsp[-3].arvore)->data_type != SEMANTIC_TYPE_INT) {
            yyerror_semantic("Expressao de teste do 'se' deve ser do tipo inteiro.", (yyvsp[-3].arvore)->line, ERR_WRONG_TYPE);
        }
        (yyval.arvore) = new_node_from_binary_op("se", (yyvsp[-3].arvore), (yyvsp[-1].arvore));
        if((yyvsp[0].arvore) != NULL) asd_add_child((yyval.arvore), (yyvsp[0].arvore)); 
        (yyval.arvore)->data_type = SEMANTIC_TYPE_INT;
    }
#line 2087 "parser.tab.c"
    break;

  case 54: /* senao_opcional: %empty  */
#line 541 "parser.y"
           {(yyval.arvore) = NULL;}
#line 2093 "parser.tab.c"
    break;

  case 55: /* senao_opcional: TK_SENAO bloco_comandos  */
#line 542 "parser.y"
                              { (yyval.arvore) = (yyvsp[0].arvore);}
#line 2099 "parser.tab.c"
    break;

  case 56: /* comando_enquanto: TK_ENQUANTO '(' expressao ')' bloco_comandos  */
#line 546 "parser.y"
                                                 {
        if ((yyvsp[-2].arvore)->data_type != SEMANTIC_TYPE_INT) {
            yyerror_semantic("Expressao de teste do 'enquanto' deve ser do tipo inteiro.", (yyvsp[-2].arvore)->line, ERR_WRONG_TYPE);
        }
        (yyval.arvore) = new_node_from_binary_op("enquanto", (yyvsp[-2].arvore), (yyvsp[0].arvore));
        (yyval.arvore)->data_type = SEMANTIC_TYPE_INT; 
    }
#line 2111 "parser.tab.c"
    break;

  case 57: /* expressao: expr_nivel7  */
#line 557 "parser.y"
                { (yyval.arvore) = (yyvsp[0].arvore); }
#line 2117 "parser.tab.c"
    break;

  case 58: /* expr_nivel7: expr_nivel7 '|' expr_nivel6  */
#line 562 "parser.y"
                                {
        (yyval.arvore) = new_node_from_binary_op_rel_log("|", (yyvsp[-2].arvore), (yyvsp[0].arvore));
    }
#line 2125 "parser.tab.c"
    break;

  case 59: /* expr_nivel7: expr_nivel6  */
#line 565 "parser.y"
                   { (yyval.arvore) = (yyvsp[0].arvore); }
#line 2131 "parser.tab.c"
    break;

  case 60: /* expr_nivel6: expr_nivel6 '&' expr_nivel5  */
#line 570 "parser.y"
                                 { 
        (yyval.arvore) = new_node_from_binary_op_rel_log("&", (yyvsp[-2].arvore), (yyvsp[0].arvore));
    }
#line 2139 "parser.tab.c"
    break;

  case 61: /* expr_nivel6: expr_nivel5  */
#line 573 "parser.y"
                  { (yyval.arvore) = (yyvsp[0].arvore); }
#line 2145 "parser.tab.c"
    break;

  case 62: /* expr_nivel5: expr_nivel5 TK_OC_EQ expr_nivel4  */
#line 578 "parser.y"
                                     {
        (yyval.arvore) = new_node_from_binary_op_rel_log("==", (yyvsp[-2].arvore), (yyvsp[0].arvore));

    }
#line 2154 "parser.tab.c"
    break;

  case 63: /* expr_nivel5: expr_nivel5 TK_OC_NE expr_nivel4  */
#line 582 "parser.y"
                                       {
        (yyval.arvore) = new_node_from_binary_op_rel_log("!=", (yyvsp[-2].arvore), (yyvsp[0].arvore));
 
    }
#line 2163 "parser.tab.c"
    break;

  case 64: /* expr_nivel5: expr_nivel4  */
#line 586 "parser.y"
                  { (yyval.arvore) = (yyvsp[0].arvore); }
#line 2169 "parser.tab.c"
    break;

  case 65: /* expr_nivel4: expr_nivel4 '<' expr_nivel3  */
#line 591 "parser.y"
                                {
        (yyval.arvore) = new_node_from_binary_op_rel_log("<", (yyvsp[-2].arvore), (yyvsp[0].arvore));

    }
#line 2178 "parser.tab.c"
    break;

  case 66: /* expr_nivel4: expr_nivel4 '>' expr_nivel3  */
#line 595 "parser.y"
                                 {
        (yyval.arvore) = new_node_from_binary_op_rel_log(">", (yyvsp[-2].arvore), (yyvsp[0].arvore));

    }
#line 2187 "parser.tab.c"
    break;

  case 67: /* expr_nivel4: expr_nivel4 TK_OC_LE expr_nivel3  */
#line 599 "parser.y"
                                      {
        (yyval.arvore) = new_node_from_binary_op_rel_log("<=", (yyvsp[-2].arvore), (yyvsp[0].arvore));

    }
#line 2196 "parser.tab.c"
    break;

  case 68: /* expr_nivel4: expr_nivel4 TK_OC_GE expr_nivel3  */
#line 603 "parser.y"
                                      {
        (yyval.arvore) = new_node_from_binary_op_rel_log(">=", (yyvsp[-2].arvore), (yyvsp[0].arvore));

    }
#line 2205 "parser.tab.c"
    break;

  case 69: /* expr_nivel4: expr_nivel3  */
#line 607 "parser.y"
                  { (yyval.arvore) = (yyvsp[0].arvore); }
#line 2211 "parser.tab.c"
    break;

  case 70: /* expr_nivel3: expr_nivel3 '+' expr_nivel2  */
#line 612 "parser.y"
                               {
        (yyval.arvore) = new_node_from_binary_op_arit("+", (yyvsp[-2].arvore), (yyvsp[0].arvore));
    }
#line 2219 "parser.tab.c"
    break;

  case 71: /* expr_nivel3: expr_nivel3 '-' expr_nivel2  */
#line 615 "parser.y"
                                  {
        (yyval.arvore) = new_node_from_binary_op_arit("-", (yyvsp[-2].arvore), (yyvsp[0].arvore));

    }
#line 2228 "parser.tab.c"
    break;

  case 72: /* expr_nivel3: expr_nivel2  */
#line 619 "parser.y"
                  { (yyval.arvore) = (yyvsp[0].arvore); }
#line 2234 "parser.tab.c"
    break;

  case 73: /* expr_nivel2: expr_nivel2 '*' expr_nivel1  */
#line 624 "parser.y"
                                {
        (yyval.arvore) = new_node_from_binary_op_arit("*", (yyvsp[-2].arvore), (yyvsp[0].arvore));
    }
#line 2242 "parser.tab.c"
    break;

  case 74: /* expr_nivel2: expr_nivel2 '/' expr_nivel1  */
#line 627 "parser.y"
                                  {
        (yyval.arvore) = new_node_from_binary_op_arit("/", (yyvsp[-2].arvore), (yyvsp[0].arvore));
    }
#line 2250 "parser.tab.c"
    break;

  case 75: /* expr_nivel2: expr_nivel2 '%' expr_nivel1  */
#line 630 "parser.y"
                                  {
        if ((yyvsp[-2].arvore)->data_type != SEMANTIC_TYPE_INT || (yyvsp[0].arvore)->data_type != SEMANTIC_TYPE_INT) {
            yyerror_semantic("Operador de resto (%) aplicado a float.", (yyvsp[-2].arvore)->line, ERR_WRONG_TYPE);
        }
        (yyval.arvore) = new_node_from_binary_op_arit("%", (yyvsp[-2].arvore), (yyvsp[0].arvore));
    }
#line 2261 "parser.tab.c"
    break;

  case 76: /* expr_nivel2: expr_nivel1  */
#line 636 "parser.y"
                  { (yyval.arvore) = (yyvsp[0].arvore); }
#line 2267 "parser.tab.c"
    break;

  case 77: /* expr_nivel1: '+' expr_nivel1  */
#line 643 "parser.y"
                    {
        (yyval.arvore) = new_node_from_unary_op("+", (yyvsp[0].arvore));   
        (yyval.arvore)->data_type = (yyvsp[0].arvore)->data_type;
    }
#line 2276 "parser.tab.c"
    break;

  case 78: /* expr_nivel1: '-' expr_nivel1  */
#line 647 "parser.y"
                      {
        (yyval.arvore) = new_node_from_unary_op("-", (yyvsp[0].arvore)); 
        (yyval.arvore)->data_type = (yyvsp[0].arvore)->data_type;
    }
#line 2285 "parser.tab.c"
    break;

  case 79: /* expr_nivel1: '!' expr_nivel1  */
#line 651 "parser.y"
                      {
    if ((yyvsp[0].arvore)->data_type != SEMANTIC_TYPE_INT) {
             yyerror_semantic("Negacao logica (!) aplicada a um float.", (yyvsp[0].arvore)->line, ERR_WRONG_TYPE);
        }
        (yyval.arvore) = new_node_from_unary_op("!", (yyvsp[0].arvore));
        (yyval.arvore)->data_type = SEMANTIC_TYPE_INT; 
    }
#line 2297 "parser.tab.c"
    break;

  case 80: /* expr_nivel1: fator  */
#line 658 "parser.y"
            { (yyval.arvore) = (yyvsp[0].arvore); }
#line 2303 "parser.tab.c"
    break;

  case 81: /* fator: TK_ID  */
#line 664 "parser.y"
          {
        symbol_t* simbolo = stack_find_global((yyvsp[0].valor_lex)->value);
        if (simbolo == NULL) {
            yyerror_semantic("Identificador nao declarado.", (yyvsp[0].valor_lex)->line, ERR_UNDECLARED);
        }
        if (simbolo->nature == SYMBOL_FUNCAO) {
            yyerror_semantic("Funcao usada como variavel.", (yyvsp[0].valor_lex)->line, ERR_FUNCTION);
        }
        (yyval.arvore) = new_node_from_lexval((yyvsp[0].valor_lex)); 
        (yyval.arvore)->data_type = simbolo->data_type;
    }
#line 2319 "parser.tab.c"
    break;

  case 82: /* fator: literal  */
#line 675 "parser.y"
              { (yyval.arvore) = (yyvsp[0].arvore); }
#line 2325 "parser.tab.c"
    break;

  case 83: /* fator: chamada_funcao  */
#line 676 "parser.y"
                     { (yyval.arvore) = (yyvsp[0].arvore); }
#line 2331 "parser.tab.c"
    break;

  case 84: /* fator: '(' expressao ')'  */
#line 677 "parser.y"
                        {(yyval.arvore) = (yyvsp[-1].arvore); }
#line 2337 "parser.tab.c"
    break;


#line 2341 "parser.tab.c"

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
  YY_SYMBOL_PRINT ("-> $$ =", YY_CAST (yysymbol_kind_t, yyr1[yyn]), &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYSYMBOL_YYEMPTY : YYTRANSLATE (yychar);
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
      {
        yypcontext_t yyctx
          = {yyssp, yytoken};
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = yysyntax_error (&yymsg_alloc, &yymsg, &yyctx);
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == -1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = YY_CAST (char *,
                             YYSTACK_ALLOC (YY_CAST (YYSIZE_T, yymsg_alloc)));
            if (yymsg)
              {
                yysyntax_error_status
                  = yysyntax_error (&yymsg_alloc, &yymsg, &yyctx);
                yymsgp = yymsg;
              }
            else
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = YYENOMEM;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == YYENOMEM)
          YYNOMEM;
      }
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
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;
  ++yynerrs;

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

  /* Pop stack until we find a state that shifts the error token.  */
  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYSYMBOL_YYerror;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYSYMBOL_YYerror)
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
                  YY_ACCESSING_SYMBOL (yystate), yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", YY_ACCESSING_SYMBOL (yyn), yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturnlab;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturnlab;


/*-----------------------------------------------------------.
| yyexhaustedlab -- YYNOMEM (memory exhaustion) comes here.  |
`-----------------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  goto yyreturnlab;


/*----------------------------------------------------------.
| yyreturnlab -- parsing is finished, clean up and return.  |
`----------------------------------------------------------*/
yyreturnlab:
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
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
  return yyresult;
}

#line 679 "parser.y"


// yylineno eh uma variável global que o Flex (scanner.l) mantém com o número da linha atual
extern int yylineno;
 
// Função chamada pelo yyparse ao encontrar um erro sintático.
void yyerror (char const *mensagem) {
    printf("Linha %d: %s\n ", yylineno, mensagem);
}

void yyerror_semantic(const char *mensagem, int line, int error_code) {
    printf("Erro semantico (Linha %d): %s\n", line, mensagem);     
    exit(error_code); 
}

/*  =====================================================
    =================== Funcoes =========================
    =====================================================
*/ 
//new node from token/lex value
//lex values are e.g $1, $2, NULL
asd_tree_t* new_node_from_lexval(lexical_value_t *lexval) {
    if (lexval == NULL) return NULL;
    asd_tree_t *node = asd_new(lexval->value);    
    //adicionado E4
    node->line = lexval->line;
    free(lexval->value);
    free(lexval);
    return node;
}

asd_tree_t* new_node_from_binary_op(const char *label, asd_tree_t *child1, asd_tree_t *child2) {
    asd_tree_t *node = asd_new(label);
    asd_add_child(node, child1);
    asd_add_child(node, child2);
    return node;
}

asd_tree_t* new_node_from_unary_op(const char *label, asd_tree_t *child) {
    asd_tree_t *node = asd_new(label);
    asd_add_child(node, child);
    return node;
}


asd_tree_t* new_node_from_binary_op_arit(const char *label, asd_tree_t *child1, asd_tree_t *child2) {
    if (child1->data_type != child2->data_type) {
        yyerror_semantic("Tipos incompativeis em operacao aritmetica.", child1->line, ERR_WRONG_TYPE);
        //add e4
        return NULL;

    }

    asd_tree_t *node = asd_new(label);
    asd_add_child(node, child1);
    asd_add_child(node, child2);

    node->line = child1->line;  
    node->data_type = child1->data_type; 
    return node;
}


asd_tree_t* new_node_from_binary_op_rel_log(const char *label, asd_tree_t *child1, asd_tree_t *child2) {
    if (child1->data_type != child2->data_type) {
        yyerror_semantic("Tipos incompativeis em operacao relacional/logica.", child1->line, ERR_WRONG_TYPE); 
        //add e4
        return NULL;
    }
    asd_tree_t *node = asd_new(label);
    asd_add_child(node, child1); 
    asd_add_child(node, child2); 
    node->line = child1->line;  
    node->data_type = SEMANTIC_TYPE_INT; 
    return node;
}
