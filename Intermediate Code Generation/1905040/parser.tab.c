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
#line 11 "parser.y"



using namespace std;

// int line_count;
FILE *fp;
ofstream fout,eout,pout;
int error;

// #define YYSTYPE SymbolInfo*

using namespace std;

int yyparse(void);
int yylex(void);
extern FILE *yyin;
extern int line_count;
// extern int error=0;

SymbolTable *table;


void yyerror(char *s)
{
	fout<<"Error at line "<<line_count<<": "<<s<<"\n"<<endl;
	eout<<"Error at line "<<line_count<<": "<<s<<"\n"<<endl;
    error++;
}


#line 103 "parser.tab.c"

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
  YYSYMBOL_IF = 3,                         /* IF  */
  YYSYMBOL_ELSE = 4,                       /* ELSE  */
  YYSYMBOL_FOR = 5,                        /* FOR  */
  YYSYMBOL_WHILE = 6,                      /* WHILE  */
  YYSYMBOL_DO = 7,                         /* DO  */
  YYSYMBOL_BREAK = 8,                      /* BREAK  */
  YYSYMBOL_INT = 9,                        /* INT  */
  YYSYMBOL_CHAR = 10,                      /* CHAR  */
  YYSYMBOL_FLOAT = 11,                     /* FLOAT  */
  YYSYMBOL_DOUBLE = 12,                    /* DOUBLE  */
  YYSYMBOL_VOID = 13,                      /* VOID  */
  YYSYMBOL_RETURN = 14,                    /* RETURN  */
  YYSYMBOL_SWITCH = 15,                    /* SWITCH  */
  YYSYMBOL_CASE = 16,                      /* CASE  */
  YYSYMBOL_DEFAULT = 17,                   /* DEFAULT  */
  YYSYMBOL_CONTINUE = 18,                  /* CONTINUE  */
  YYSYMBOL_PRINTLN = 19,                   /* PRINTLN  */
  YYSYMBOL_ID = 20,                        /* ID  */
  YYSYMBOL_CONST_INT = 21,                 /* CONST_INT  */
  YYSYMBOL_CONST_FLOAT = 22,               /* CONST_FLOAT  */
  YYSYMBOL_CONST_CHAR = 23,                /* CONST_CHAR  */
  YYSYMBOL_CONST_STRING = 24,              /* CONST_STRING  */
  YYSYMBOL_RELOP = 25,                     /* RELOP  */
  YYSYMBOL_MULOP = 26,                     /* MULOP  */
  YYSYMBOL_LOGICOP = 27,                   /* LOGICOP  */
  YYSYMBOL_ADDOP = 28,                     /* ADDOP  */
  YYSYMBOL_LPAREN = 29,                    /* LPAREN  */
  YYSYMBOL_RPAREN = 30,                    /* RPAREN  */
  YYSYMBOL_LCURL = 31,                     /* LCURL  */
  YYSYMBOL_RCURL = 32,                     /* RCURL  */
  YYSYMBOL_LTHIRD = 33,                    /* LTHIRD  */
  YYSYMBOL_RTHIRD = 34,                    /* RTHIRD  */
  YYSYMBOL_COMMA = 35,                     /* COMMA  */
  YYSYMBOL_SEMICOLON = 36,                 /* SEMICOLON  */
  YYSYMBOL_ASSIGNOP = 37,                  /* ASSIGNOP  */
  YYSYMBOL_NOT = 38,                       /* NOT  */
  YYSYMBOL_INCOP = 39,                     /* INCOP  */
  YYSYMBOL_DECOP = 40,                     /* DECOP  */
  YYSYMBOL_LOWER_THAN_ELSE = 41,           /* LOWER_THAN_ELSE  */
  YYSYMBOL_YYACCEPT = 42,                  /* $accept  */
  YYSYMBOL_start = 43,                     /* start  */
  YYSYMBOL_program = 44,                   /* program  */
  YYSYMBOL_unit = 45,                      /* unit  */
  YYSYMBOL_func_declaration = 46,          /* func_declaration  */
  YYSYMBOL_func_definition = 47,           /* func_definition  */
  YYSYMBOL_parameter_list = 48,            /* parameter_list  */
  YYSYMBOL_compound_statement = 49,        /* compound_statement  */
  YYSYMBOL_var_declaration = 50,           /* var_declaration  */
  YYSYMBOL_type_specifier = 51,            /* type_specifier  */
  YYSYMBOL_declaration_list = 52,          /* declaration_list  */
  YYSYMBOL_statements = 53,                /* statements  */
  YYSYMBOL_statement = 54,                 /* statement  */
  YYSYMBOL_expression_statement = 55,      /* expression_statement  */
  YYSYMBOL_variable = 56,                  /* variable  */
  YYSYMBOL_expression = 57,                /* expression  */
  YYSYMBOL_logic_expression = 58,          /* logic_expression  */
  YYSYMBOL_rel_expression = 59,            /* rel_expression  */
  YYSYMBOL_simple_expression = 60,         /* simple_expression  */
  YYSYMBOL_term = 61,                      /* term  */
  YYSYMBOL_unary_expression = 62,          /* unary_expression  */
  YYSYMBOL_factor = 63,                    /* factor  */
  YYSYMBOL_argument_list = 64,             /* argument_list  */
  YYSYMBOL_arguments = 65                  /* arguments  */
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
typedef yytype_int8 yy_state_t;

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

#if !defined yyoverflow

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
#endif /* !defined yyoverflow */

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
#define YYFINAL  11
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   176

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  42
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  24
/* YYNRULES -- Number of rules.  */
#define YYNRULES  64
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  118

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   296


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
      35,    36,    37,    38,    39,    40,    41
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,    58,    58,    66,    73,    82,    89,    96,   105,   117,
     129,   140,   153,   162,   170,   177,   186,   194,   203,   213,
     220,   227,   236,   244,   255,   261,   272,   278,   287,   293,
     299,   305,   317,   327,   339,   349,   359,   369,   375,   384,
     390,   401,   407,   417,   423,   433,   439,   449,   455,   465,
     471,   481,   488,   495,   503,   509,   518,   526,   532,   538,
     545,   554,   561,   567,   575
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if YYDEBUG || 0
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "\"invalid token\"", "IF", "ELSE", "FOR",
  "WHILE", "DO", "BREAK", "INT", "CHAR", "FLOAT", "DOUBLE", "VOID",
  "RETURN", "SWITCH", "CASE", "DEFAULT", "CONTINUE", "PRINTLN", "ID",
  "CONST_INT", "CONST_FLOAT", "CONST_CHAR", "CONST_STRING", "RELOP",
  "MULOP", "LOGICOP", "ADDOP", "LPAREN", "RPAREN", "LCURL", "RCURL",
  "LTHIRD", "RTHIRD", "COMMA", "SEMICOLON", "ASSIGNOP", "NOT", "INCOP",
  "DECOP", "LOWER_THAN_ELSE", "$accept", "start", "program", "unit",
  "func_declaration", "func_definition", "parameter_list",
  "compound_statement", "var_declaration", "type_specifier",
  "declaration_list", "statements", "statement", "expression_statement",
  "variable", "expression", "logic_expression", "rel_expression",
  "simple_expression", "term", "unary_expression", "factor",
  "argument_list", "arguments", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-67)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
      43,   -67,   -67,   -67,    26,    43,   -67,   -67,   -67,   -67,
      12,   -67,   -67,    10,   -23,     6,     8,    15,   -67,   -15,
      -8,    22,    19,    36,    70,   -67,   -67,     2,    43,   -67,
     -67,    53,    48,    49,    51,    65,    59,    33,   -67,   -67,
      65,    65,   -67,   -67,    65,   -67,   -67,    62,   104,   -67,
     -67,    82,    60,   -67,    68,    -5,    71,   -67,   -67,   -67,
     -67,    80,    77,    65,    29,    65,    69,    84,    65,    65,
      24,   -67,    86,   -67,    79,   -67,   -67,    65,   -67,   -67,
     -67,    65,    65,    65,    65,   -67,   -67,    90,    29,    97,
     -67,    98,   -67,    99,    95,   100,   -67,   -67,   -67,   103,
      71,   -67,   138,    65,   138,    78,   -67,    65,   -67,   133,
     108,   -67,   -67,   -67,   138,   138,   -67,   -67
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       0,    19,    20,    21,     0,     2,     4,     6,     7,     5,
       0,     1,     3,    24,     0,     0,     0,     0,    18,     0,
       0,    15,     0,    22,     0,     9,    11,     0,     0,    14,
      25,     0,     0,     0,     0,     0,     0,    39,    57,    58,
       0,     0,    17,    37,     0,    30,    28,     0,     0,    26,
      29,    54,     0,    41,    43,    45,    47,    49,    53,     8,
      10,    13,     0,     0,     0,     0,     0,     0,    62,     0,
      54,    51,     0,    52,    24,    16,    27,     0,    59,    60,
      38,     0,     0,     0,     0,    12,    23,     0,     0,     0,
      36,     0,    64,     0,    61,     0,    56,    42,    44,    46,
      48,    50,     0,     0,     0,     0,    55,     0,    40,    32,
       0,    34,    35,    63,     0,     0,    33,    31
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
     -67,   -67,   -67,   134,   -67,   -67,   -67,    -9,    55,     9,
     -67,   -67,   -43,   -63,   -37,   -35,   -66,    64,    66,    63,
     -36,   -67,   -67,   -67
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
       0,     4,     5,     6,     7,     8,    20,    45,    46,    47,
      14,    48,    49,    50,    51,    52,    53,    54,    55,    56,
      57,    58,    93,    94
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int8 yytable[] =
{
      66,    88,    92,    70,    71,    76,    72,    70,    73,    10,
      26,    97,    17,    18,    10,     1,    24,     2,    60,     3,
      82,    25,    27,    83,    21,   103,    11,    28,    87,    22,
      89,    70,    13,    24,    95,    23,    19,    61,    59,    15,
      70,   113,    29,    16,    70,    70,    70,    70,   101,    37,
      38,    39,     1,    30,     2,     9,     3,    40,    41,   109,
       9,   111,    68,    78,    79,    43,    69,    44,   110,    31,
      70,   116,   117,    32,    62,    33,    34,    63,    64,     1,
      65,     2,    74,     3,    35,    37,    38,    39,    67,    36,
      37,    38,    39,    40,    41,    81,    80,    84,    40,    41,
      85,    24,    42,    44,    91,    90,    43,    32,    44,    33,
      34,    86,    16,     1,   112,     2,    96,     3,    35,    77,
     102,    78,    79,    36,    37,    38,    39,   104,   105,   106,
     107,    83,    40,    41,   108,    24,    75,   114,   115,    12,
      43,    32,    44,    33,    34,    98,   100,     1,    99,     2,
       0,     3,    35,     0,     0,     0,     0,    36,    37,    38,
      39,     0,     0,     0,     0,     0,    40,    41,     0,    24,
       0,     0,     0,     0,    43,     0,    44
};

static const yytype_int8 yycheck[] =
{
      35,    64,    68,    40,    40,    48,    41,    44,    44,     0,
      19,    77,    35,    36,     5,     9,    31,    11,    27,    13,
      25,    36,    30,    28,    15,    88,     0,    35,    63,    21,
      65,    68,    20,    31,    69,    20,    30,    28,    36,    29,
      77,   107,    20,    33,    81,    82,    83,    84,    84,    20,
      21,    22,     9,    34,    11,     0,    13,    28,    29,   102,
       5,   104,    29,    39,    40,    36,    33,    38,   103,    33,
     107,   114,   115,     3,    21,     5,     6,    29,    29,     9,
      29,    11,    20,    13,    14,    20,    21,    22,    29,    19,
      20,    21,    22,    28,    29,    27,    36,    26,    28,    29,
      20,    31,    32,    38,    20,    36,    36,     3,    38,     5,
       6,    34,    33,     9,    36,    11,    30,    13,    14,    37,
      30,    39,    40,    19,    20,    21,    22,    30,    30,    30,
      35,    28,    28,    29,    34,    31,    32,     4,    30,     5,
      36,     3,    38,     5,     6,    81,    83,     9,    82,    11,
      -1,    13,    14,    -1,    -1,    -1,    -1,    19,    20,    21,
      22,    -1,    -1,    -1,    -1,    -1,    28,    29,    -1,    31,
      -1,    -1,    -1,    -1,    36,    -1,    38
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,     9,    11,    13,    43,    44,    45,    46,    47,    50,
      51,     0,    45,    20,    52,    29,    33,    35,    36,    30,
      48,    51,    21,    20,    31,    36,    49,    30,    35,    20,
      34,    33,     3,     5,     6,    14,    19,    20,    21,    22,
      28,    29,    32,    36,    38,    49,    50,    51,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    36,
      49,    51,    21,    29,    29,    29,    57,    29,    29,    33,
      56,    62,    57,    62,    20,    32,    54,    37,    39,    40,
      36,    27,    25,    28,    26,    20,    34,    57,    55,    57,
      36,    20,    58,    64,    65,    57,    30,    58,    59,    60,
      61,    62,    30,    55,    30,    30,    30,    35,    34,    54,
      57,    54,    36,    58,     4,    30,    54,    54
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    42,    43,    44,    44,    45,    45,    45,    46,    46,
      47,    47,    48,    48,    48,    48,    49,    49,    50,    51,
      51,    51,    52,    52,    52,    52,    53,    53,    54,    54,
      54,    54,    54,    54,    54,    54,    54,    55,    55,    56,
      56,    57,    57,    58,    58,    59,    59,    60,    60,    61,
      61,    62,    62,    62,    63,    63,    63,    63,    63,    63,
      63,    64,    64,    65,    65
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     2,     1,     1,     1,     1,     6,     5,
       6,     5,     4,     3,     2,     1,     3,     2,     3,     1,
       1,     1,     3,     6,     1,     4,     1,     2,     1,     1,
       1,     7,     5,     7,     5,     5,     3,     1,     2,     1,
       4,     1,     3,     1,     3,     1,     3,     1,     3,     1,
       3,     2,     2,     1,     1,     4,     3,     1,     1,     2,
       2,     1,     0,     3,     1
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
  case 2: /* start: program  */
#line 59 "parser.y"
        {
		string rule="start : program";
        (yyval.symbol_info) = new SymbolInfo("start", "program");
        (yyval.symbol_info)->add((yyvsp[0].symbol_info));
	}
#line 1249 "parser.tab.c"
    break;

  case 3: /* program: program unit  */
#line 67 "parser.y"
    {
        string rule="program : program unit";
        (yyval.symbol_info) = new SymbolInfo("program", "program unit");
        (yyval.symbol_info)->add((yyvsp[-1].symbol_info));
        (yyval.symbol_info)->add((yyvsp[0].symbol_info));
    }
#line 1260 "parser.tab.c"
    break;

  case 4: /* program: unit  */
#line 74 "parser.y"
    {
        string rule="program : unit";
        
        (yyval.symbol_info) = new SymbolInfo("program", "unit");
        (yyval.symbol_info)->add((yyvsp[0].symbol_info));
    }
#line 1271 "parser.tab.c"
    break;

  case 5: /* unit: var_declaration  */
#line 83 "parser.y"
    {
        string rule="unit : var_declaration";
        
        (yyval.symbol_info) = new SymbolInfo("unit", "var_declaration");
        (yyval.symbol_info)->add((yyvsp[0].symbol_info));
    }
#line 1282 "parser.tab.c"
    break;

  case 6: /* unit: func_declaration  */
#line 90 "parser.y"
     {
        string rule="unit : func_declaration";
        
        (yyval.symbol_info) = new SymbolInfo("unit", "func_declaration");
        (yyval.symbol_info)->add((yyvsp[0].symbol_info));
     }
#line 1293 "parser.tab.c"
    break;

  case 7: /* unit: func_definition  */
#line 97 "parser.y"
     {
        string rule="unit : func_definition";
        
        (yyval.symbol_info) = new SymbolInfo("unit", "func_definition");
        (yyval.symbol_info)->add((yyvsp[0].symbol_info));
     }
#line 1304 "parser.tab.c"
    break;

  case 8: /* func_declaration: type_specifier ID LPAREN parameter_list RPAREN SEMICOLON  */
#line 106 "parser.y"
    {
        string rule="func_declaration : type_specifier ID LPAREN parameter_list RPAREN SEMICOLON";
        
        (yyval.symbol_info) = new SymbolInfo("func_declaration", "type_specifier ID LPAREN parameter_list RPAREN SEMICOLON");
        (yyval.symbol_info)->add((yyvsp[-5].symbol_info));
        (yyval.symbol_info)->add((yyvsp[-4].symbol_info));
        (yyval.symbol_info)->add((yyvsp[-3].symbol_info));
        (yyval.symbol_info)->add((yyvsp[-2].symbol_info));
        (yyval.symbol_info)->add((yyvsp[-1].symbol_info));
        (yyval.symbol_info)->add((yyvsp[0].symbol_info));
        }
#line 1320 "parser.tab.c"
    break;

  case 9: /* func_declaration: type_specifier ID LPAREN RPAREN SEMICOLON  */
#line 118 "parser.y"
        {
        string rule="func_declaration : type_specifier ID LPAREN RPAREN SEMICOLON";
        (yyval.symbol_info) = new SymbolInfo("func_declaration", "type_specifier ID LPAREN RPAREN SEMICOLON");
        (yyval.symbol_info)->add((yyvsp[-4].symbol_info));
        (yyval.symbol_info)->add((yyvsp[-3].symbol_info));
        (yyval.symbol_info)->add((yyvsp[-2].symbol_info));
        (yyval.symbol_info)->add((yyvsp[-1].symbol_info));
        (yyval.symbol_info)->add((yyvsp[0].symbol_info));
        }
#line 1334 "parser.tab.c"
    break;

  case 10: /* func_definition: type_specifier ID LPAREN parameter_list RPAREN compound_statement  */
#line 130 "parser.y"
{
    string rule="func_definition : type_specifier ID LPAREN parameter_list RPAREN compound_statement";
    (yyval.symbol_info) = new SymbolInfo("func_definition", "type_specifier ID LPAREN parameter_list RPAREN compound_statement");
        (yyval.symbol_info)->add((yyvsp[-5].symbol_info));
        (yyval.symbol_info)->add((yyvsp[-4].symbol_info));
        (yyval.symbol_info)->add((yyvsp[-3].symbol_info));
        (yyval.symbol_info)->add((yyvsp[-2].symbol_info));
        (yyval.symbol_info)->add((yyvsp[-1].symbol_info));
        (yyval.symbol_info)->add((yyvsp[0].symbol_info));
}
#line 1349 "parser.tab.c"
    break;

  case 11: /* func_definition: type_specifier ID LPAREN RPAREN compound_statement  */
#line 141 "parser.y"
        {
        string rule="func_definition : type_specifier ID LPAREN parameter_list RPAREN compound_statement";
        (yyval.symbol_info) = new SymbolInfo("func_definition", "type_specifier ID LPAREN RPAREN compound_statement");
        (yyval.symbol_info)->add((yyvsp[-4].symbol_info));
        (yyval.symbol_info)->add((yyvsp[-3].symbol_info));
        (yyval.symbol_info)->add((yyvsp[-2].symbol_info));
        (yyval.symbol_info)->add((yyvsp[-1].symbol_info));
        (yyval.symbol_info)->add((yyvsp[0].symbol_info));
        }
#line 1363 "parser.tab.c"
    break;

  case 12: /* parameter_list: parameter_list COMMA type_specifier ID  */
#line 154 "parser.y"
{
    string rule="parameter_list  : parameter_list COMMA type_specifier ID";
        (yyval.symbol_info) = new SymbolInfo("parameter_list", "parameter_list COMMA type_specifier ID");
        (yyval.symbol_info)->add((yyvsp[-3].symbol_info));
        (yyval.symbol_info)->add((yyvsp[-2].symbol_info));
        (yyval.symbol_info)->add((yyvsp[-1].symbol_info));
        (yyval.symbol_info)->add((yyvsp[0].symbol_info));
}
#line 1376 "parser.tab.c"
    break;

  case 13: /* parameter_list: parameter_list COMMA type_specifier  */
#line 163 "parser.y"
        {
        string rule="parameter_list  : parameter_list COMMA type_specifier";
        (yyval.symbol_info) = new SymbolInfo("parameter_list", "parameter_list COMMA type_specifier");
        (yyval.symbol_info)->add((yyvsp[-2].symbol_info));
        (yyval.symbol_info)->add((yyvsp[-1].symbol_info));
        (yyval.symbol_info)->add((yyvsp[0].symbol_info)); 
        }
#line 1388 "parser.tab.c"
    break;

  case 14: /* parameter_list: type_specifier ID  */
#line 171 "parser.y"
        {
        string rule="parameter_list  : type_specifier ID";
        (yyval.symbol_info) = new SymbolInfo("parameter_list", "type_specifier ID");
        (yyval.symbol_info)->add((yyvsp[-1].symbol_info));
        (yyval.symbol_info)->add((yyvsp[0].symbol_info));
        }
#line 1399 "parser.tab.c"
    break;

  case 15: /* parameter_list: type_specifier  */
#line 178 "parser.y"
        {
        string rule="parameter_list  : type_specifier";
        (yyval.symbol_info) = new SymbolInfo("parameter_list", "type_specifier");
        (yyval.symbol_info)->add((yyvsp[0].symbol_info));
        }
#line 1409 "parser.tab.c"
    break;

  case 16: /* compound_statement: LCURL statements RCURL  */
#line 187 "parser.y"
{
        string rule="compound_statement : LCURL statements RCURL";
        (yyval.symbol_info) = new SymbolInfo("compound_statement", "LCURL statements RCURL");
        (yyval.symbol_info)->add((yyvsp[-2].symbol_info));
        (yyval.symbol_info)->add((yyvsp[-1].symbol_info));
        (yyval.symbol_info)->add((yyvsp[0].symbol_info));
}
#line 1421 "parser.tab.c"
    break;

  case 17: /* compound_statement: LCURL RCURL  */
#line 195 "parser.y"
            {
        string rule="compound_statement : LCURL RCURL";
        (yyval.symbol_info) = new SymbolInfo("compound_statement", "LCURL RCURL");
        (yyval.symbol_info)->add((yyvsp[-1].symbol_info));
        (yyval.symbol_info)->add((yyvsp[0].symbol_info));
            }
#line 1432 "parser.tab.c"
    break;

  case 18: /* var_declaration: type_specifier declaration_list SEMICOLON  */
#line 204 "parser.y"
{
    string rule="var_declaration : type_specifier declaration_list SEMICOLON";
        (yyval.symbol_info) = new SymbolInfo("var_declaration", "type_specifier declaration_list SEMICOLON");
        (yyval.symbol_info)->add((yyvsp[-2].symbol_info));
        (yyval.symbol_info)->add((yyvsp[-1].symbol_info));
        (yyval.symbol_info)->add((yyvsp[0].symbol_info));
}
#line 1444 "parser.tab.c"
    break;

  case 19: /* type_specifier: INT  */
#line 214 "parser.y"
{
    string rule="type_specifier	: INT";
        (yyval.symbol_info) = new SymbolInfo("type_specifier", "INT");
        (yyval.symbol_info)->add((yyvsp[0].symbol_info));
    
}
#line 1455 "parser.tab.c"
    break;

  case 20: /* type_specifier: FLOAT  */
#line 221 "parser.y"
        {
    string rule="type_specifier	: FLOAT";
        (yyval.symbol_info) = new SymbolInfo("type_specifier", "FLOAT");
        (yyval.symbol_info)->add((yyvsp[0].symbol_info));
    
}
#line 1466 "parser.tab.c"
    break;

  case 21: /* type_specifier: VOID  */
#line 228 "parser.y"
        {
    string rule="type_specifier	: VOID";
        (yyval.symbol_info) = new SymbolInfo("type_specifier", "VOID");
        (yyval.symbol_info)->add((yyvsp[0].symbol_info));
    
}
#line 1477 "parser.tab.c"
    break;

  case 22: /* declaration_list: declaration_list COMMA ID  */
#line 237 "parser.y"
{
    string rule="declaration_list : declaration_list COMMA ID";
        (yyval.symbol_info) = new SymbolInfo("declaration_list", "declaration_list COMMA ID");
        (yyval.symbol_info)->add((yyvsp[-2].symbol_info));
        (yyval.symbol_info)->add((yyvsp[-1].symbol_info));
        (yyval.symbol_info)->add((yyvsp[0].symbol_info));
}
#line 1489 "parser.tab.c"
    break;

  case 23: /* declaration_list: declaration_list COMMA ID LTHIRD CONST_INT RTHIRD  */
#line 245 "parser.y"
          {
    string rule="declaration_list : declaration_list COMMA ID LTHIRD CONST_INT RTHIRD";
        (yyval.symbol_info) = new SymbolInfo("declaration_list", "declaration_list COMMA ID LTHIRD CONST_INT RTHIRD");
        (yyval.symbol_info)->add((yyvsp[-5].symbol_info));
        (yyval.symbol_info)->add((yyvsp[-4].symbol_info));
        (yyval.symbol_info)->add((yyvsp[-3].symbol_info));
        (yyval.symbol_info)->add((yyvsp[-2].symbol_info));
        (yyval.symbol_info)->add((yyvsp[-1].symbol_info));
        (yyval.symbol_info)->add((yyvsp[0].symbol_info));
}
#line 1504 "parser.tab.c"
    break;

  case 24: /* declaration_list: ID  */
#line 256 "parser.y"
          {
        string rule="declaration_list : ID";
        (yyval.symbol_info) = new SymbolInfo("declaration_list", "ID");
        (yyval.symbol_info)->add((yyvsp[0].symbol_info));
          }
#line 1514 "parser.tab.c"
    break;

  case 25: /* declaration_list: ID LTHIRD CONST_INT RTHIRD  */
#line 262 "parser.y"
          {
            string rule="declaration_list : ID LTHIRD CONST_INT RTHIRD";
        (yyval.symbol_info) = new SymbolInfo("declaration_list", "ID LTHIRD CONST_INT RTHIRD");
        (yyval.symbol_info)->add((yyvsp[-3].symbol_info));
        (yyval.symbol_info)->add((yyvsp[-2].symbol_info));
        (yyval.symbol_info)->add((yyvsp[-1].symbol_info));
        (yyval.symbol_info)->add((yyvsp[0].symbol_info));
          }
#line 1527 "parser.tab.c"
    break;

  case 26: /* statements: statement  */
#line 273 "parser.y"
{
        string rule="statements : statement";
        (yyval.symbol_info) = new SymbolInfo("statements", "statement");
        (yyval.symbol_info)->add((yyvsp[0].symbol_info));
}
#line 1537 "parser.tab.c"
    break;

  case 27: /* statements: statements statement  */
#line 279 "parser.y"
       {
        string rule="statements : statements statement";
        (yyval.symbol_info) = new SymbolInfo("statements", "statements statement");
        (yyval.symbol_info)->add((yyvsp[-1].symbol_info));
        (yyval.symbol_info)->add((yyvsp[0].symbol_info));
       }
#line 1548 "parser.tab.c"
    break;

  case 28: /* statement: var_declaration  */
#line 288 "parser.y"
{
        string rule="statement : var_declaration";
        (yyval.symbol_info) = new SymbolInfo("statement", "var_declaration");
        (yyval.symbol_info)->add((yyvsp[0].symbol_info));   
}
#line 1558 "parser.tab.c"
    break;

  case 29: /* statement: expression_statement  */
#line 294 "parser.y"
      {
        string rule="statement : expression_statement";
        (yyval.symbol_info) = new SymbolInfo("statement", "expression_statement");
        (yyval.symbol_info)->add((yyvsp[0].symbol_info));
      }
#line 1568 "parser.tab.c"
    break;

  case 30: /* statement: compound_statement  */
#line 300 "parser.y"
      {
        string rule="statement : compound_statement";
        (yyval.symbol_info) = new SymbolInfo("statement","compound_statement");
        (yyval.symbol_info)->add((yyvsp[0].symbol_info));
      }
#line 1578 "parser.tab.c"
    break;

  case 31: /* statement: FOR LPAREN expression_statement expression_statement expression RPAREN statement  */
#line 306 "parser.y"
      {
        string rule="statement: FOR LPAREN expression_statement expression_statement expression RPAREN statement";
        (yyval.symbol_info) = new SymbolInfo("statement","FOR LPAREN expression_statement expression_statement expression RPAREN statement");
        (yyval.symbol_info)->add((yyvsp[-6].symbol_info));
        (yyval.symbol_info)->add((yyvsp[-5].symbol_info));
        (yyval.symbol_info)->add((yyvsp[-4].symbol_info));
        (yyval.symbol_info)->add((yyvsp[-3].symbol_info));
        (yyval.symbol_info)->add((yyvsp[-2].symbol_info));
        (yyval.symbol_info)->add((yyvsp[-1].symbol_info));
        (yyval.symbol_info)->add((yyvsp[0].symbol_info));
      }
#line 1594 "parser.tab.c"
    break;

  case 32: /* statement: IF LPAREN expression RPAREN statement  */
#line 318 "parser.y"
      {
        string rule="statement: IF LPAREN expression RPAREN statement";
        (yyval.symbol_info) = new SymbolInfo("statement","IF LPAREN expression RPAREN statement");
        (yyval.symbol_info)->add((yyvsp[-4].symbol_info));
        (yyval.symbol_info)->add((yyvsp[-3].symbol_info));
        (yyval.symbol_info)->add((yyvsp[-2].symbol_info));
        (yyval.symbol_info)->add((yyvsp[-1].symbol_info));
        (yyval.symbol_info)->add((yyvsp[0].symbol_info));
      }
#line 1608 "parser.tab.c"
    break;

  case 33: /* statement: IF LPAREN expression RPAREN statement ELSE statement  */
#line 328 "parser.y"
      {
        string rule="statement: IF LPAREN expression RPAREN statement ELSE statement";
        (yyval.symbol_info) = new SymbolInfo("statement","IF LPAREN expression RPAREN statement ELSE statement");
        (yyval.symbol_info)->add((yyvsp[-6].symbol_info));
        (yyval.symbol_info)->add((yyvsp[-5].symbol_info));
        (yyval.symbol_info)->add((yyvsp[-4].symbol_info));
        (yyval.symbol_info)->add((yyvsp[-3].symbol_info));
        (yyval.symbol_info)->add((yyvsp[-2].symbol_info));
        (yyval.symbol_info)->add((yyvsp[-1].symbol_info));
        (yyval.symbol_info)->add((yyvsp[0].symbol_info));
      }
#line 1624 "parser.tab.c"
    break;

  case 34: /* statement: WHILE LPAREN expression RPAREN statement  */
#line 340 "parser.y"
      {
        string rule="statement: WHILE LPAREN expression RPAREN statement";
        (yyval.symbol_info) = new SymbolInfo("statement","WHILE LPAREN expression RPAREN statement");
        (yyval.symbol_info)->add((yyvsp[-4].symbol_info));
        (yyval.symbol_info)->add((yyvsp[-3].symbol_info));
        (yyval.symbol_info)->add((yyvsp[-2].symbol_info));
        (yyval.symbol_info)->add((yyvsp[-1].symbol_info));
        (yyval.symbol_info)->add((yyvsp[0].symbol_info));
      }
#line 1638 "parser.tab.c"
    break;

  case 35: /* statement: PRINTLN LPAREN ID RPAREN SEMICOLON  */
#line 350 "parser.y"
      {
        string rule="statement: PRINTLN LPAREN ID RPAREN SEMICOLON";
        (yyval.symbol_info) = new SymbolInfo("statement","PRINTLN LPAREN ID RPAREN SEMICOLON");
        (yyval.symbol_info)->add((yyvsp[-4].symbol_info));
        (yyval.symbol_info)->add((yyvsp[-3].symbol_info));
        (yyval.symbol_info)->add((yyvsp[-2].symbol_info));
        (yyval.symbol_info)->add((yyvsp[-1].symbol_info));
        (yyval.symbol_info)->add((yyvsp[0].symbol_info));
      }
#line 1652 "parser.tab.c"
    break;

  case 36: /* statement: RETURN expression SEMICOLON  */
#line 360 "parser.y"
      {
        string rule="statement: RETURN expression SEMICOLON";
        (yyval.symbol_info) = new SymbolInfo("statement","RETURN expression SEMICOLON");
        (yyval.symbol_info)->add((yyvsp[-2].symbol_info));
        (yyval.symbol_info)->add((yyvsp[-1].symbol_info));
        (yyval.symbol_info)->add((yyvsp[0].symbol_info));
      }
#line 1664 "parser.tab.c"
    break;

  case 37: /* expression_statement: SEMICOLON  */
#line 370 "parser.y"
{
        string rule="expression_statement 	: SEMICOLON";
        (yyval.symbol_info) = new SymbolInfo("expression_statement", "SEMICOLON");
        (yyval.symbol_info)->add((yyvsp[0].symbol_info));
}
#line 1674 "parser.tab.c"
    break;

  case 38: /* expression_statement: expression SEMICOLON  */
#line 376 "parser.y"
            {
        string rule="expression_statement 	: expression SEMICOLON";
            (yyval.symbol_info) = new SymbolInfo("expression_statement", "expression SEMICOLON");
        (yyval.symbol_info)->add((yyvsp[-1].symbol_info));    
        (yyval.symbol_info)->add((yyvsp[0].symbol_info));        
            }
#line 1685 "parser.tab.c"
    break;

  case 39: /* variable: ID  */
#line 385 "parser.y"
{
        string rule="variable : ID";
        (yyval.symbol_info) = new SymbolInfo("variable", "ID");
        (yyval.symbol_info)->add((yyvsp[0].symbol_info));
}
#line 1695 "parser.tab.c"
    break;

  case 40: /* variable: ID LTHIRD expression RTHIRD  */
#line 391 "parser.y"
     {
        string rule="variable : ID LTHIRD expression RTHIRD";
        (yyval.symbol_info) = new SymbolInfo("variable", "ID LTHIRD expression RTHIRD");
        (yyval.symbol_info)->add((yyvsp[-3].symbol_info));
        (yyval.symbol_info)->add((yyvsp[-2].symbol_info));
        (yyval.symbol_info)->add((yyvsp[-1].symbol_info));
        (yyval.symbol_info)->add((yyvsp[0].symbol_info));
     }
#line 1708 "parser.tab.c"
    break;

  case 41: /* expression: logic_expression  */
#line 402 "parser.y"
 {
        string rule="expression : logic_expression";
        (yyval.symbol_info) = new SymbolInfo("expression", "logic_expression");
        (yyval.symbol_info)->add((yyvsp[0].symbol_info));
 }
#line 1718 "parser.tab.c"
    break;

  case 42: /* expression: variable ASSIGNOP logic_expression  */
#line 408 "parser.y"
       {
        string rule="expression : variable ASSIGNOP logic_expression";
        (yyval.symbol_info) = new SymbolInfo("expression", "variable ASSIGNOP logic_expression");
        (yyval.symbol_info)->add((yyvsp[-2].symbol_info));
        (yyval.symbol_info)->add((yyvsp[-1].symbol_info));
        (yyval.symbol_info)->add((yyvsp[0].symbol_info));
       }
#line 1730 "parser.tab.c"
    break;

  case 43: /* logic_expression: rel_expression  */
#line 418 "parser.y"
{
        string rule="logic_expression : rel_expression";
        (yyval.symbol_info) = new SymbolInfo("logic_expression", "rel_expression");
        (yyval.symbol_info)->add((yyvsp[0].symbol_info));
}
#line 1740 "parser.tab.c"
    break;

  case 44: /* logic_expression: rel_expression LOGICOP rel_expression  */
#line 424 "parser.y"
         {
        string rule="logic_expression : rel_expression LOGICOP rel_expression";
        (yyval.symbol_info) = new SymbolInfo("logic_expression", "rel_expression LOGICOP rel_expression");
        (yyval.symbol_info)->add((yyvsp[-2].symbol_info));
        (yyval.symbol_info)->add((yyvsp[-1].symbol_info));
        (yyval.symbol_info)->add((yyvsp[0].symbol_info));
         }
#line 1752 "parser.tab.c"
    break;

  case 45: /* rel_expression: simple_expression  */
#line 434 "parser.y"
{
        string rule="rel_expression	: simple_expression";
        (yyval.symbol_info) = new SymbolInfo("rel_expression", "simple_expression");
        (yyval.symbol_info)->add((yyvsp[0].symbol_info));
}
#line 1762 "parser.tab.c"
    break;

  case 46: /* rel_expression: simple_expression RELOP simple_expression  */
#line 440 "parser.y"
        {
        string rule="rel_expression	: simple_expression RELOP simple_expression";
        (yyval.symbol_info) = new SymbolInfo("rel_expression", "simple_expression RELOP simple_expression");
        (yyval.symbol_info)->add((yyvsp[-2].symbol_info));
        (yyval.symbol_info)->add((yyvsp[-1].symbol_info));
        (yyval.symbol_info)->add((yyvsp[0].symbol_info));
        }
#line 1774 "parser.tab.c"
    break;

  case 47: /* simple_expression: term  */
#line 450 "parser.y"
{
        string rule="simple_expression : term";
        (yyval.symbol_info) = new SymbolInfo("simple_expression", "term");
        (yyval.symbol_info)->add((yyvsp[0].symbol_info));
}
#line 1784 "parser.tab.c"
    break;

  case 48: /* simple_expression: simple_expression ADDOP term  */
#line 456 "parser.y"
          {
        string rule="simple_expression : simple_expression ADDOP term";
        (yyval.symbol_info) = new SymbolInfo("simple_expression", "simple_expression ADDOP term");
        (yyval.symbol_info)->add((yyvsp[-2].symbol_info));
        (yyval.symbol_info)->add((yyvsp[-1].symbol_info));
        (yyval.symbol_info)->add((yyvsp[0].symbol_info));
          }
#line 1796 "parser.tab.c"
    break;

  case 49: /* term: unary_expression  */
#line 466 "parser.y"
{
        string rule="term :	unary_expression";
        (yyval.symbol_info) = new SymbolInfo("term", "unary_expression");
        (yyval.symbol_info)->add((yyvsp[0].symbol_info));
}
#line 1806 "parser.tab.c"
    break;

  case 50: /* term: term MULOP unary_expression  */
#line 472 "parser.y"
     {
        string rule="term :	term MULOP unary_expression";
        (yyval.symbol_info) = new SymbolInfo("term", "term MULOP unary_expression");
        (yyval.symbol_info)->add((yyvsp[-2].symbol_info));
        (yyval.symbol_info)->add((yyvsp[-1].symbol_info));
        (yyval.symbol_info)->add((yyvsp[0].symbol_info));
     }
#line 1818 "parser.tab.c"
    break;

  case 51: /* unary_expression: ADDOP unary_expression  */
#line 482 "parser.y"
{
        string rule="unary_expression : ADDOP unary_expression";
        (yyval.symbol_info) = new SymbolInfo("unary_expression", "ADDOP unary_expression");
        (yyval.symbol_info)->add((yyvsp[-1].symbol_info));
        (yyval.symbol_info)->add((yyvsp[0].symbol_info));
}
#line 1829 "parser.tab.c"
    break;

  case 52: /* unary_expression: NOT unary_expression  */
#line 489 "parser.y"
         {
        string rule="unary_expression : NOT unary_expression";
        (yyval.symbol_info) = new SymbolInfo("unary_expression", "NOT unary_expression");
        (yyval.symbol_info)->add((yyvsp[-1].symbol_info));
        (yyval.symbol_info)->add((yyvsp[0].symbol_info));
         }
#line 1840 "parser.tab.c"
    break;

  case 53: /* unary_expression: factor  */
#line 496 "parser.y"
         {
        string rule="unary_expression : factor";
        (yyval.symbol_info) = new SymbolInfo("unary_expression", "factor");
        (yyval.symbol_info)->add((yyvsp[0].symbol_info));
         }
#line 1850 "parser.tab.c"
    break;

  case 54: /* factor: variable  */
#line 504 "parser.y"
{
        string rule="factor	: variable";
        (yyval.symbol_info) = new SymbolInfo("factor", "variable");
        (yyval.symbol_info)->add((yyvsp[0].symbol_info));
}
#line 1860 "parser.tab.c"
    break;

  case 55: /* factor: ID LPAREN argument_list RPAREN  */
#line 510 "parser.y"
    {
        string rule="factor	: ID LPAREN argument_list RPAREN";
        (yyval.symbol_info) = new SymbolInfo("factor", "ID LPAREN argument_list RPAREN");
        (yyval.symbol_info)->add((yyvsp[-3].symbol_info));
        (yyval.symbol_info)->add((yyvsp[-2].symbol_info));
        (yyval.symbol_info)->add((yyvsp[-1].symbol_info));
        (yyval.symbol_info)->add((yyvsp[0].symbol_info));
    }
#line 1873 "parser.tab.c"
    break;

  case 56: /* factor: LPAREN expression RPAREN  */
#line 519 "parser.y"
    {
        string rule="factor	: LPAREN expression RPAREN";
        (yyval.symbol_info) = new SymbolInfo("factor", "LPAREN expression RPAREN");
        (yyval.symbol_info)->add((yyvsp[-2].symbol_info));
        (yyval.symbol_info)->add((yyvsp[-1].symbol_info));
        (yyval.symbol_info)->add((yyvsp[0].symbol_info));
    }
#line 1885 "parser.tab.c"
    break;

  case 57: /* factor: CONST_INT  */
#line 527 "parser.y"
    {
        string rule="factor	: CONST_INT";
        (yyval.symbol_info) = new SymbolInfo("factor", "CONST_INT");
        (yyval.symbol_info)->add((yyvsp[0].symbol_info));
    }
#line 1895 "parser.tab.c"
    break;

  case 58: /* factor: CONST_FLOAT  */
#line 533 "parser.y"
    {
        string rule="factor	: CONST_FLOAT";
        (yyval.symbol_info) = new SymbolInfo("factor", "CONST_FLOAT");
        (yyval.symbol_info)->add((yyvsp[0].symbol_info));
    }
#line 1905 "parser.tab.c"
    break;

  case 59: /* factor: variable INCOP  */
#line 539 "parser.y"
    {
        string rule="factor	: variable INCOP";
        (yyval.symbol_info) = new SymbolInfo("factor", "variable INCOP");
        (yyval.symbol_info)->add((yyvsp[-1].symbol_info));
        (yyval.symbol_info)->add((yyvsp[0].symbol_info));
    }
#line 1916 "parser.tab.c"
    break;

  case 60: /* factor: variable DECOP  */
#line 546 "parser.y"
    {
        string rule="factor	: variable DECOP";
        (yyval.symbol_info) = new SymbolInfo("factor", "variable DECOP");
        (yyval.symbol_info)->add((yyvsp[-1].symbol_info));
        (yyval.symbol_info)->add((yyvsp[0].symbol_info));
    }
#line 1927 "parser.tab.c"
    break;

  case 61: /* argument_list: arguments  */
#line 555 "parser.y"
{
        string rule="argument_list : arguments";
        (yyval.symbol_info) = new SymbolInfo("argument_list", "arguments");
        (yyval.symbol_info)->add((yyvsp[0].symbol_info));
}
#line 1937 "parser.tab.c"
    break;

  case 62: /* argument_list: %empty  */
#line 561 "parser.y"
              {
                string rule="argument_list : ";
                (yyval.symbol_info) = new SymbolInfo();
              }
#line 1946 "parser.tab.c"
    break;

  case 63: /* arguments: arguments COMMA logic_expression  */
#line 568 "parser.y"
{
        string rule="arguments : arguments COMMA logic_expression";
        (yyval.symbol_info) = new SymbolInfo("arguments", "arguments COMMA logic_expression");
        (yyval.symbol_info)->add((yyvsp[-2].symbol_info));
        (yyval.symbol_info)->add((yyvsp[-1].symbol_info));
        (yyval.symbol_info)->add((yyvsp[0].symbol_info));
}
#line 1958 "parser.tab.c"
    break;

  case 64: /* arguments: logic_expression  */
#line 576 "parser.y"
          {
            string rule="arguments : logic_expression";
            (yyval.symbol_info) = new SymbolInfo("arguments", "logic_expression");
            (yyval.symbol_info)->add((yyvsp[0].symbol_info));
          }
#line 1968 "parser.tab.c"
    break;


#line 1972 "parser.tab.c"

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
      yyerror (YY_("syntax error"));
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

  return yyresult;
}

#line 584 "parser.y"

int main(int argc,char *argv[])
{
    
	fout.open("output.txt",ios::out | ios::trunc );
    /* eout.OpenFile("error_output.txt");
    pout.OpenFile("parser_output.txt"); */
    table=new SymbolTable(bucket);
    if((fp=fopen(argv[1],"r"))==NULL)
	{
		printf("Cannot Open Input File.\n");
		exit(1);
	}
	yyin=fp;
	yyparse();
	
    fclose(fp);
    fout.close();
	
	return 0;
}

