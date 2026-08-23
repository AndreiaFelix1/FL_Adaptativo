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


/* Substitute the variable and function names.  */
#define yyparse         expressionyyparse
#define yylex           expressionyylex
#define yyerror         expressionyyerror
#define yydebug         expressionyydebug
#define yynerrs         expressionyynerrs
#define yylval          expressionyylval
#define yychar          expressionyychar

/* First part of user prologue.  */
#line 46 "expression.y"


#include <cstdio>
#include <cstdlib>
#include "commonutil.h"
#include "expressionyydefs.h"

#define YYDEBUG 1           /* allow debugging */
#define YYDEBUGGING_ON 0    /* turn on/off debugging */

#if YYDEBUG != 0
#define YYERROR_VERBOSE     /* more detailed error messages */
#include <cstring>         /* YYVERBOSE needs it */
#endif

#include "expression.h"
#include "exception.h"
#include "stringutil.h"
#include "unitconversion.h"

using namespace omnetpp;
using namespace omnetpp::common;

#define yyin expressionyyin
#define yyout expressionyyout
#define yyrestart expressionyyrestart
#define yy_scan_string expressionyy_scan_string
#define yy_delete_buffer expressionyy_delete_buffer
extern FILE *yyin;
extern FILE *yyout;
struct yy_buffer_state;
struct yy_buffer_state *yy_scan_string(const char *str);
void yy_delete_buffer(struct yy_buffer_state *);
void yyrestart(FILE *);
int yylex();
void yyerror (const char *s);

LineColumn xpos, xprevpos;

static Expression::Elem *e;
static Expression::Resolver *resolver;

static char *join(const char *s1, const char *s2, const char *s3=nullptr)
{
    char *d = new char[strlen(s1) + strlen(s2) + strlen(s3?s3:"") + 4];
    strcpy(d, s1);
    strcat(d, " ");
    strcat(d, s2);
    if (s3) {strcat(d, " "); strcat(d, s3);}
    return d;
}

static char *concat(const char *s1, const char *s2, const char *s3=nullptr, const char *s4=nullptr)
{
    char *d = new char[strlen(s1) + strlen(s2) + strlen(s3?s3:"") + strlen(s4?s4:"") + 1];
    strcpy(d, s1);
    strcat(d, s2);
    if (s3) strcat(d, s3);
    if (s4) strcat(d, s4);
    return d;
}

static void addFunction(const char *funcname, int numargs)
{
    try {
        if (!resolver)
            throw opp_runtime_error("Cannot resolve function '%s': No resolver provided", funcname);
        Expression::Functor *f = resolver->resolveFunction(funcname, numargs);
        if (!f)
            throw opp_runtime_error("Cannot resolve function name '%s'", funcname);
        if (f->getNumArgs() != numargs)
            throw opp_runtime_error("Function %s() takes %d argument(s) and not %d", funcname, f->getNumArgs(), numargs);
        *e++ = f;
    }
    catch (std::exception& e) {
        yyerror(e.what());
    }
}

static void addVariableRef(const char *varname)
{
    try {
        if (!resolver)
            throw opp_runtime_error("Cannot resolve variable '%s': No resolver provided", varname);
        Expression::Functor *f = resolver->resolveVariable(varname);
        if (!f)
            throw opp_runtime_error("Cannot resolve variable '%s'", varname);
        if (f->getNumArgs() != 0)
            throw opp_runtime_error("Internal error: functor representing a variable cannot expect arguments: %s", varname);
        *e++ = f;
    }
    catch (std::exception& e) {
        yyerror(e.what());
    }
}

static double parseQuantity(const char *text, std::string& unit)
{
    try {
        // evaluate quantities like "5s 230ms"
        return UnitConversion::parseQuantity(text, unit);
    }
    catch (std::exception& e) {
        yyerror(e.what());
        return 0;
    }
}


#line 188 "expression.tab.cc"

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

#include "expression.tab.hh"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_DOUBLETYPE = 3,                 /* DOUBLETYPE  */
  YYSYMBOL_INTTYPE = 4,                    /* INTTYPE  */
  YYSYMBOL_STRINGTYPE = 5,                 /* STRINGTYPE  */
  YYSYMBOL_BOOLTYPE = 6,                   /* BOOLTYPE  */
  YYSYMBOL_TRUE_ = 7,                      /* TRUE_  */
  YYSYMBOL_FALSE_ = 8,                     /* FALSE_  */
  YYSYMBOL_NAME = 9,                       /* NAME  */
  YYSYMBOL_INTCONSTANT = 10,               /* INTCONSTANT  */
  YYSYMBOL_REALCONSTANT = 11,              /* REALCONSTANT  */
  YYSYMBOL_STRINGCONSTANT = 12,            /* STRINGCONSTANT  */
  YYSYMBOL_EQ_ = 13,                       /* EQ_  */
  YYSYMBOL_NE_ = 14,                       /* NE_  */
  YYSYMBOL_GE_ = 15,                       /* GE_  */
  YYSYMBOL_LE_ = 16,                       /* LE_  */
  YYSYMBOL_AND_ = 17,                      /* AND_  */
  YYSYMBOL_OR_ = 18,                       /* OR_  */
  YYSYMBOL_XOR_ = 19,                      /* XOR_  */
  YYSYMBOL_NOT_ = 20,                      /* NOT_  */
  YYSYMBOL_BINAND_ = 21,                   /* BINAND_  */
  YYSYMBOL_BINOR_ = 22,                    /* BINOR_  */
  YYSYMBOL_BINXOR_ = 23,                   /* BINXOR_  */
  YYSYMBOL_BINCOMPL_ = 24,                 /* BINCOMPL_  */
  YYSYMBOL_SHIFTLEFT_ = 25,                /* SHIFTLEFT_  */
  YYSYMBOL_SHIFTRIGHT_ = 26,               /* SHIFTRIGHT_  */
  YYSYMBOL_INVALID_CHAR = 27,              /* INVALID_CHAR  */
  YYSYMBOL_28_ = 28,                       /* '?'  */
  YYSYMBOL_29_ = 29,                       /* ':'  */
  YYSYMBOL_30_ = 30,                       /* '>'  */
  YYSYMBOL_31_ = 31,                       /* '<'  */
  YYSYMBOL_32_ = 32,                       /* '+'  */
  YYSYMBOL_33_ = 33,                       /* '-'  */
  YYSYMBOL_34_ = 34,                       /* '*'  */
  YYSYMBOL_35_ = 35,                       /* '/'  */
  YYSYMBOL_36_ = 36,                       /* '%'  */
  YYSYMBOL_37_ = 37,                       /* '^'  */
  YYSYMBOL_UMIN_ = 38,                     /* UMIN_  */
  YYSYMBOL_39_ = 39,                       /* '('  */
  YYSYMBOL_40_ = 40,                       /* ')'  */
  YYSYMBOL_41_ = 41,                       /* '='  */
  YYSYMBOL_42_ = 42,                       /* ','  */
  YYSYMBOL_43_ = 43,                       /* '.'  */
  YYSYMBOL_44_ = 44,                       /* '['  */
  YYSYMBOL_45_ = 45,                       /* ']'  */
  YYSYMBOL_YYACCEPT = 46,                  /* $accept  */
  YYSYMBOL_expression = 47,                /* expression  */
  YYSYMBOL_expr = 48,                      /* expr  */
  YYSYMBOL_simple_expr = 49,               /* simple_expr  */
  YYSYMBOL_variable = 50,                  /* variable  */
  YYSYMBOL_variable2 = 51,                 /* variable2  */
  YYSYMBOL_segment = 52,                   /* segment  */
  YYSYMBOL_literal = 53,                   /* literal  */
  YYSYMBOL_stringliteral = 54,             /* stringliteral  */
  YYSYMBOL_boolliteral = 55,               /* boolliteral  */
  YYSYMBOL_numliteral = 56,                /* numliteral  */
  YYSYMBOL_quantity = 57                   /* quantity  */
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
#define YYFINAL  30
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   390

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  46
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  12
/* YYNRULES -- Number of rules.  */
#define YYNRULES  54
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  99

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   283


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
       2,     2,     2,     2,     2,     2,     2,    36,     2,     2,
      39,    40,    34,    32,    42,    33,    43,    35,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    29,     2,
      31,    41,    30,    28,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    44,     2,    45,    37,     2,     2,     2,     2,     2,
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
      25,    26,    27,    38
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   159,   159,   163,   164,   166,   168,   170,   172,   174,
     176,   179,   183,   185,   187,   189,   191,   193,   195,   198,
     200,   202,   205,   209,   211,   213,   216,   219,   221,   223,
     226,   228,   230,   232,   234,   239,   240,   244,   249,   251,
     255,   256,   261,   262,   263,   267,   272,   274,   279,   281,
     283,   294,   296,   298,   300
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
  "\"end of file\"", "error", "\"invalid token\"", "DOUBLETYPE",
  "INTTYPE", "STRINGTYPE", "BOOLTYPE", "TRUE_", "FALSE_", "NAME",
  "INTCONSTANT", "REALCONSTANT", "STRINGCONSTANT", "EQ_", "NE_", "GE_",
  "LE_", "AND_", "OR_", "XOR_", "NOT_", "BINAND_", "BINOR_", "BINXOR_",
  "BINCOMPL_", "SHIFTLEFT_", "SHIFTRIGHT_", "INVALID_CHAR", "'?'", "':'",
  "'>'", "'<'", "'+'", "'-'", "'*'", "'/'", "'%'", "'^'", "UMIN_", "'('",
  "')'", "'='", "','", "'.'", "'['", "']'", "$accept", "expression",
  "expr", "simple_expr", "variable", "variable2", "segment", "literal",
  "stringliteral", "boolliteral", "numliteral", "quantity", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-29)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
      57,   -29,   -29,    13,    11,    12,   -29,    57,    57,    57,
      57,    22,   261,   -29,   -29,    10,   -29,   -29,   -29,   -29,
     -29,     1,    39,    44,   -29,   -29,    14,    14,    14,   174,
     -29,    57,    57,    57,    57,    57,    57,    57,    57,    57,
      57,    57,    57,    57,    57,    57,    57,    57,    57,    57,
      57,    57,    57,    47,    49,    51,   -29,    84,    16,   -29,
     336,   336,   336,   336,   319,   319,   319,   349,   349,   349,
     -28,   -28,   203,   336,   336,   -18,   -18,   -27,   -27,   -27,
     -27,   261,    18,   -29,   -29,   -29,   -29,    57,   -29,    57,
     114,   290,   -29,    57,   144,   -29,    57,   232,   -29
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       0,    46,    47,    40,    48,    49,    45,     0,     0,     0,
       0,     0,     2,     3,    35,    37,    39,    36,    42,    43,
      44,    50,     0,     0,    53,    54,    22,    26,    11,     0,
       1,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    30,     0,     0,     4,
      13,    14,    16,    18,    19,    20,    21,    23,    24,    25,
      27,    28,     0,    15,    17,     5,     6,     7,     8,     9,
      10,    12,    40,    38,    51,    52,    31,     0,    41,     0,
       0,    29,    32,     0,     0,    33,     0,     0,    34
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -29,   -29,    -7,   -29,   -29,   -29,    17,   -29,   -29,   -29,
     -29,   -29
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
       0,    11,    12,    13,    14,    15,    16,    17,    18,    19,
      20,    21
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int8 yytable[] =
{
      26,    27,    28,    29,    46,    47,    48,    49,    50,    51,
      51,    54,    55,    52,    52,    57,    48,    49,    50,    51,
      24,    25,    30,    52,    60,    61,    62,    63,    64,    65,
      66,    67,    68,    69,    70,    71,    72,    73,    74,    75,
      76,    77,    78,    79,    80,    81,     1,     2,     3,     4,
       5,     6,    22,    53,    58,    52,    82,    23,    84,     7,
      85,    88,    23,     8,     1,     2,     3,     4,     5,     6,
      83,     0,     9,     0,     0,     0,     0,     7,    10,    56,
      90,     8,    91,     0,     0,     0,    94,     0,     0,    97,
       9,     0,     0,     0,     0,     0,    10,    31,    32,    33,
      34,    35,    36,    37,     0,    38,    39,    40,     0,    41,
      42,     0,    43,     0,    44,    45,    46,    47,    48,    49,
      50,    51,     0,     0,    86,    52,    87,    31,    32,    33,
      34,    35,    36,    37,     0,    38,    39,    40,     0,    41,
      42,     0,    43,     0,    44,    45,    46,    47,    48,    49,
      50,    51,     0,     0,    92,    52,    93,    31,    32,    33,
      34,    35,    36,    37,     0,    38,    39,    40,     0,    41,
      42,     0,    43,     0,    44,    45,    46,    47,    48,    49,
      50,    51,     0,     0,    95,    52,    96,    31,    32,    33,
      34,    35,    36,    37,     0,    38,    39,    40,     0,    41,
      42,     0,    43,     0,    44,    45,    46,    47,    48,    49,
      50,    51,     0,     0,    59,    52,    31,    32,    33,    34,
      35,    36,    37,     0,    38,    39,    40,     0,    41,    42,
       0,    43,    89,    44,    45,    46,    47,    48,    49,    50,
      51,     0,     0,     0,    52,    31,    32,    33,    34,    35,
      36,    37,     0,    38,    39,    40,     0,    41,    42,     0,
      43,     0,    44,    45,    46,    47,    48,    49,    50,    51,
       0,     0,    98,    52,    31,    32,    33,    34,    35,    36,
      37,     0,    38,    39,    40,     0,    41,    42,     0,    43,
       0,    44,    45,    46,    47,    48,    49,    50,    51,     0,
       0,     0,    52,    31,    32,    33,    34,    35,    36,    37,
       0,    38,    39,    40,     0,    41,    42,     0,     0,     0,
      44,    45,    46,    47,    48,    49,    50,    51,     0,     0,
       0,    52,    31,    32,    33,    34,     0,     0,     0,     0,
      38,    39,    40,     0,    41,    42,     0,     0,     0,    44,
      45,    46,    47,    48,    49,    50,    51,    38,    39,    40,
      52,    41,    42,     0,     0,     0,     0,     0,    46,    47,
      48,    49,    50,    51,    41,    42,     0,    52,     0,     0,
       0,    46,    47,    48,    49,    50,    51,     0,     0,     0,
      52
};

static const yytype_int8 yycheck[] =
{
       7,     8,     9,    10,    32,    33,    34,    35,    36,    37,
      37,    10,    11,    41,    41,    22,    34,    35,    36,    37,
       9,     9,     0,    41,    31,    32,    33,    34,    35,    36,
      37,    38,    39,    40,    41,    42,    43,    44,    45,    46,
      47,    48,    49,    50,    51,    52,     7,     8,     9,    10,
      11,    12,    39,    43,    10,    41,     9,    44,     9,    20,
       9,    45,    44,    24,     7,     8,     9,    10,    11,    12,
      53,    -1,    33,    -1,    -1,    -1,    -1,    20,    39,    40,
      87,    24,    89,    -1,    -1,    -1,    93,    -1,    -1,    96,
      33,    -1,    -1,    -1,    -1,    -1,    39,    13,    14,    15,
      16,    17,    18,    19,    -1,    21,    22,    23,    -1,    25,
      26,    -1,    28,    -1,    30,    31,    32,    33,    34,    35,
      36,    37,    -1,    -1,    40,    41,    42,    13,    14,    15,
      16,    17,    18,    19,    -1,    21,    22,    23,    -1,    25,
      26,    -1,    28,    -1,    30,    31,    32,    33,    34,    35,
      36,    37,    -1,    -1,    40,    41,    42,    13,    14,    15,
      16,    17,    18,    19,    -1,    21,    22,    23,    -1,    25,
      26,    -1,    28,    -1,    30,    31,    32,    33,    34,    35,
      36,    37,    -1,    -1,    40,    41,    42,    13,    14,    15,
      16,    17,    18,    19,    -1,    21,    22,    23,    -1,    25,
      26,    -1,    28,    -1,    30,    31,    32,    33,    34,    35,
      36,    37,    -1,    -1,    40,    41,    13,    14,    15,    16,
      17,    18,    19,    -1,    21,    22,    23,    -1,    25,    26,
      -1,    28,    29,    30,    31,    32,    33,    34,    35,    36,
      37,    -1,    -1,    -1,    41,    13,    14,    15,    16,    17,
      18,    19,    -1,    21,    22,    23,    -1,    25,    26,    -1,
      28,    -1,    30,    31,    32,    33,    34,    35,    36,    37,
      -1,    -1,    40,    41,    13,    14,    15,    16,    17,    18,
      19,    -1,    21,    22,    23,    -1,    25,    26,    -1,    28,
      -1,    30,    31,    32,    33,    34,    35,    36,    37,    -1,
      -1,    -1,    41,    13,    14,    15,    16,    17,    18,    19,
      -1,    21,    22,    23,    -1,    25,    26,    -1,    -1,    -1,
      30,    31,    32,    33,    34,    35,    36,    37,    -1,    -1,
      -1,    41,    13,    14,    15,    16,    -1,    -1,    -1,    -1,
      21,    22,    23,    -1,    25,    26,    -1,    -1,    -1,    30,
      31,    32,    33,    34,    35,    36,    37,    21,    22,    23,
      41,    25,    26,    -1,    -1,    -1,    -1,    -1,    32,    33,
      34,    35,    36,    37,    25,    26,    -1,    41,    -1,    -1,
      -1,    32,    33,    34,    35,    36,    37,    -1,    -1,    -1,
      41
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,     7,     8,     9,    10,    11,    12,    20,    24,    33,
      39,    47,    48,    49,    50,    51,    52,    53,    54,    55,
      56,    57,    39,    44,     9,     9,    48,    48,    48,    48,
       0,    13,    14,    15,    16,    17,    18,    19,    21,    22,
      23,    25,    26,    28,    30,    31,    32,    33,    34,    35,
      36,    37,    41,    43,    10,    11,    40,    48,    10,    40,
      48,    48,    48,    48,    48,    48,    48,    48,    48,    48,
      48,    48,    48,    48,    48,    48,    48,    48,    48,    48,
      48,    48,     9,    52,     9,     9,    40,    42,    45,    29,
      48,    48,    40,    42,    48,    40,    42,    48,    40
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    46,    47,    48,    48,    48,    48,    48,    48,    48,
      48,    48,    48,    48,    48,    48,    48,    48,    48,    48,
      48,    48,    48,    48,    48,    48,    48,    48,    48,    48,
      48,    48,    48,    48,    48,    49,    49,    50,    51,    51,
      52,    52,    53,    53,    53,    54,    55,    55,    56,    56,
      56,    57,    57,    57,    57
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     1,     3,     3,     3,     3,     3,     3,
       3,     2,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     2,     3,     3,     3,     2,     3,     3,     5,
       3,     4,     6,     8,    10,     1,     1,     1,     3,     1,
       1,     4,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     3,     3,     2,     2
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
  case 5: /* expr: expr '+' expr  */
#line 167 "expression.y"
                { *e++ = Expression::ADD; }
#line 1350 "expression.tab.cc"
    break;

  case 6: /* expr: expr '-' expr  */
#line 169 "expression.y"
                { *e++ = Expression::SUB; }
#line 1356 "expression.tab.cc"
    break;

  case 7: /* expr: expr '*' expr  */
#line 171 "expression.y"
                { *e++ = Expression::MUL; }
#line 1362 "expression.tab.cc"
    break;

  case 8: /* expr: expr '/' expr  */
#line 173 "expression.y"
                { *e++ = Expression::DIV; }
#line 1368 "expression.tab.cc"
    break;

  case 9: /* expr: expr '%' expr  */
#line 175 "expression.y"
                { *e++ = Expression::MOD; }
#line 1374 "expression.tab.cc"
    break;

  case 10: /* expr: expr '^' expr  */
#line 177 "expression.y"
                { *e++ = Expression::POW; }
#line 1380 "expression.tab.cc"
    break;

  case 11: /* expr: '-' expr  */
#line 181 "expression.y"
                { *e++ = Expression::NEG; }
#line 1386 "expression.tab.cc"
    break;

  case 12: /* expr: expr '=' expr  */
#line 184 "expression.y"
                { *e++ = Expression::EQ; }
#line 1392 "expression.tab.cc"
    break;

  case 13: /* expr: expr EQ_ expr  */
#line 186 "expression.y"
                { *e++ = Expression::EQ; }
#line 1398 "expression.tab.cc"
    break;

  case 14: /* expr: expr NE_ expr  */
#line 188 "expression.y"
                { *e++ = Expression::NE; }
#line 1404 "expression.tab.cc"
    break;

  case 15: /* expr: expr '>' expr  */
#line 190 "expression.y"
                { *e++ = Expression::GT; }
#line 1410 "expression.tab.cc"
    break;

  case 16: /* expr: expr GE_ expr  */
#line 192 "expression.y"
                { *e++ = Expression::GE; }
#line 1416 "expression.tab.cc"
    break;

  case 17: /* expr: expr '<' expr  */
#line 194 "expression.y"
                { *e++ = Expression::LT; }
#line 1422 "expression.tab.cc"
    break;

  case 18: /* expr: expr LE_ expr  */
#line 196 "expression.y"
                { *e++ = Expression::LE; }
#line 1428 "expression.tab.cc"
    break;

  case 19: /* expr: expr AND_ expr  */
#line 199 "expression.y"
                { *e++ = Expression::AND; }
#line 1434 "expression.tab.cc"
    break;

  case 20: /* expr: expr OR_ expr  */
#line 201 "expression.y"
                { *e++ = Expression::OR; }
#line 1440 "expression.tab.cc"
    break;

  case 21: /* expr: expr XOR_ expr  */
#line 203 "expression.y"
                { *e++ = Expression::XOR; }
#line 1446 "expression.tab.cc"
    break;

  case 22: /* expr: NOT_ expr  */
#line 207 "expression.y"
                { *e++ = Expression::NOT; }
#line 1452 "expression.tab.cc"
    break;

  case 23: /* expr: expr BINAND_ expr  */
#line 210 "expression.y"
                { *e++ = Expression::BIN_AND; }
#line 1458 "expression.tab.cc"
    break;

  case 24: /* expr: expr BINOR_ expr  */
#line 212 "expression.y"
                { *e++ = Expression::BIN_OR; }
#line 1464 "expression.tab.cc"
    break;

  case 25: /* expr: expr BINXOR_ expr  */
#line 214 "expression.y"
                { *e++ = Expression::BIN_XOR; }
#line 1470 "expression.tab.cc"
    break;

  case 26: /* expr: BINCOMPL_ expr  */
#line 218 "expression.y"
                { *e++ = Expression::BIN_NOT; }
#line 1476 "expression.tab.cc"
    break;

  case 27: /* expr: expr SHIFTLEFT_ expr  */
#line 220 "expression.y"
                { *e++ = Expression::LSHIFT; }
#line 1482 "expression.tab.cc"
    break;

  case 28: /* expr: expr SHIFTRIGHT_ expr  */
#line 222 "expression.y"
                { *e++ = Expression::RSHIFT; }
#line 1488 "expression.tab.cc"
    break;

  case 29: /* expr: expr '?' expr ':' expr  */
#line 224 "expression.y"
                { *e++ = Expression::IIF; }
#line 1494 "expression.tab.cc"
    break;

  case 30: /* expr: NAME '(' ')'  */
#line 227 "expression.y"
                { addFunction(yyvsp[-2],0); delete [] yyvsp[-2]; }
#line 1500 "expression.tab.cc"
    break;

  case 31: /* expr: NAME '(' expr ')'  */
#line 229 "expression.y"
                { addFunction(yyvsp[-3],1); delete [] yyvsp[-3]; }
#line 1506 "expression.tab.cc"
    break;

  case 32: /* expr: NAME '(' expr ',' expr ')'  */
#line 231 "expression.y"
                { addFunction(yyvsp[-5],2); delete [] yyvsp[-5]; }
#line 1512 "expression.tab.cc"
    break;

  case 33: /* expr: NAME '(' expr ',' expr ',' expr ')'  */
#line 233 "expression.y"
                { addFunction(yyvsp[-7],3); delete [] yyvsp[-7]; }
#line 1518 "expression.tab.cc"
    break;

  case 34: /* expr: NAME '(' expr ',' expr ',' expr ',' expr ')'  */
#line 235 "expression.y"
                { addFunction(yyvsp[-9],4); delete [] yyvsp[-9]; }
#line 1524 "expression.tab.cc"
    break;

  case 37: /* variable: variable2  */
#line 245 "expression.y"
                { addVariableRef(yyvsp[0]); delete [] yyvsp[0]; }
#line 1530 "expression.tab.cc"
    break;

  case 38: /* variable2: variable2 '.' segment  */
#line 250 "expression.y"
                { yyval = concat(yyvsp[-2], ".", yyvsp[0]); delete [] yyvsp[-2]; delete [] yyvsp[0]; }
#line 1536 "expression.tab.cc"
    break;

  case 41: /* segment: NAME '[' INTCONSTANT ']'  */
#line 257 "expression.y"
                { yyval = concat(yyvsp[-3], "[", yyvsp[-1], "]"); delete [] yyvsp[-3]; delete [] yyvsp[-1]; }
#line 1542 "expression.tab.cc"
    break;

  case 45: /* stringliteral: STRINGCONSTANT  */
#line 268 "expression.y"
                { *e++ = opp_parsequotedstr(yyvsp[0]).c_str(); delete [] yyvsp[0]; }
#line 1548 "expression.tab.cc"
    break;

  case 46: /* boolliteral: TRUE_  */
#line 273 "expression.y"
                { *e++ = true; }
#line 1554 "expression.tab.cc"
    break;

  case 47: /* boolliteral: FALSE_  */
#line 275 "expression.y"
                { *e++ = false; }
#line 1560 "expression.tab.cc"
    break;

  case 48: /* numliteral: INTCONSTANT  */
#line 280 "expression.y"
                { *e++ = opp_atol(yyvsp[0]); delete [] yyvsp[0]; }
#line 1566 "expression.tab.cc"
    break;

  case 49: /* numliteral: REALCONSTANT  */
#line 282 "expression.y"
                { *e++ = opp_atof(yyvsp[0]); delete [] yyvsp[0]; }
#line 1572 "expression.tab.cc"
    break;

  case 50: /* numliteral: quantity  */
#line 284 "expression.y"
                {
                  std::string unit;
                  *e++ = parseQuantity(yyvsp[0], unit);
                  if (!unit.empty())
                      (e-1)->setUnit(unit.c_str());
                  delete [] yyvsp[0];
                }
#line 1584 "expression.tab.cc"
    break;

  case 51: /* quantity: quantity INTCONSTANT NAME  */
#line 295 "expression.y"
                { yyval = join(yyvsp[-2], yyvsp[-1], yyvsp[0]); delete [] yyvsp[-2]; delete [] yyvsp[-1]; delete [] yyvsp[0]; }
#line 1590 "expression.tab.cc"
    break;

  case 52: /* quantity: quantity REALCONSTANT NAME  */
#line 297 "expression.y"
                { yyval = join(yyvsp[-2], yyvsp[-1], yyvsp[0]); delete [] yyvsp[-2]; delete [] yyvsp[-1]; delete [] yyvsp[0]; }
#line 1596 "expression.tab.cc"
    break;

  case 53: /* quantity: INTCONSTANT NAME  */
#line 299 "expression.y"
                { yyval = join(yyvsp[-1], yyvsp[0]); delete [] yyvsp[-1]; delete [] yyvsp[0]; }
#line 1602 "expression.tab.cc"
    break;

  case 54: /* quantity: REALCONSTANT NAME  */
#line 301 "expression.y"
                { yyval = join(yyvsp[-1], yyvsp[0]); delete [] yyvsp[-1]; delete [] yyvsp[0]; }
#line 1608 "expression.tab.cc"
    break;


#line 1612 "expression.tab.cc"

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

#line 304 "expression.y"


//----------------------------------------------------------------------

void doParseExpression(const char *text, Expression::Resolver *res, Expression::Elem *&elems, int& nelems)
{
    NONREENTRANT_PARSER();

    elems = nullptr;
    nelems = 0;

    // reset the lexer
    xpos.co = 0;
    xpos.li = 1;
    xprevpos = xpos;

    yyin = nullptr;
    yyout = stderr; // not used anyway

    // alloc buffer
    struct yy_buffer_state *handle = yy_scan_string(text);
    if (!handle)
        throw std::runtime_error("Parser is unable to allocate work memory");

    Expression::Elem *v = new Expression::Elem[100]; // overestimate for now; XXX danger of overrun
    e = v;
    resolver = res;

    // parse
    try
    {
        yyparse();
    }
    catch (std::exception& e)
    {
        yy_delete_buffer(handle);
        delete [] v;
        throw;
    }
    yy_delete_buffer(handle);

    // copy v[] and return
    nelems = e - v;
    elems = new Expression::Elem[nelems];
    for (int i=0; i<nelems; i++)
        elems[i] = v[i];
    delete [] v;
}

void yyerror(const char *s)
{
    // chop newline
    char buf[250];
    strcpy(buf, s);
    if (buf[strlen(buf)-1] == '\n')
        buf[strlen(buf)-1] = '\0';

    throw std::runtime_error(buf);
}
