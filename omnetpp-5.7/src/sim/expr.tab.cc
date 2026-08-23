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
#define yyparse         expryyparse
#define yylex           expryylex
#define yyerror         expryyerror
#define yydebug         expryydebug
#define yynerrs         expryynerrs
#define yylval          expryylval
#define yychar          expryychar

/* First part of user prologue.  */
#line 47 "expr.y"


#include <cstdio>
#include <cstdlib>
#include <limits>
#include "common/commonutil.h"
#include "expryydefs.h"

#define YYDEBUG 1           /* allow debugging */
#define YYDEBUGGING_ON 0    /* turn on/off debugging */

#if YYDEBUG != 0
#define YYERROR_VERBOSE     /* more detailed error messages */
#include <cstring>         /* YYVERBOSE needs it */
#endif

#define yyin expryyin
#define yyout expryyout
#define yyrestart expryyrestart
#define yy_scan_string expryy_scan_string
#define yy_delete_buffer expryy_delete_buffer
extern FILE *yyin;
extern FILE *yyout;
struct yy_buffer_state;
struct yy_buffer_state *yy_scan_string(const char *str);
void yy_delete_buffer(struct yy_buffer_state *);
void yyrestart(FILE *);
int yylex();
void yyerror (const char *s);

LineColumn xpos, xprevpos;


#include "common/stringutil.h"
#include "common/unitconversion.h"
#include "omnetpp/cdynamicexpression.h"
#include "omnetpp/cpar.h"
#include "omnetpp/cxmlelement.h"
#include "omnetpp/cexception.h"
#include "omnetpp/globals.h"
#include "omnetpp/cnedmathfunction.h"
#include "omnetpp/cnedfunction.h"
#include "omnetpp/nedsupport.h"

using namespace omnetpp;
using namespace omnetpp::common;
using namespace omnetpp::nedsupport;

static cDynamicExpression::Elem *e;

static char *expryyconcat(char *s1, char *s2, char *s3=nullptr)
{
    char *d = new char[strlen(s1)+strlen(s2)+strlen(s3?s3:"")+4];
    strcpy(d, s1);
    strcat(d, " ");
    strcat(d, s2);
    if (s3) {strcat(d, " "); strcat(d, s3);}
    delete [] s1; delete [] s2; delete [] s3;
    return d;
}

static void addFunction(const char *funcname, int argc)
{
    cNedMathFunction *f = cNedMathFunction::find(funcname, argc);
    if (f) {
        *e++ = f;
        return;
    }
    cNedFunction *nf = cNedFunction::find(funcname);
    if (nf) {
        if (argc < nf->getMinArgs() || (argc > nf->getMaxArgs() && !nf->hasVarArgs()))
            yyerror(opp_stringf("function '%s' does not accept %d arguments", nf->getSignature(), argc).c_str());
        (e++)->set(nf,argc);
        return;
    }
    yyerror(opp_stringf("function '%s()' (with %d args) not found (Define_NED_Function() or Define_NED_Math_Function() missing from C++ code?)", funcname, argc).c_str());
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


#line 170 "expr.tab.cc"

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

#include "expr.tab.hh"
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
  YYSYMBOL_XMLTYPE = 7,                    /* XMLTYPE  */
  YYSYMBOL_TRUE_ = 8,                      /* TRUE_  */
  YYSYMBOL_FALSE_ = 9,                     /* FALSE_  */
  YYSYMBOL_NAN_ = 10,                      /* NAN_  */
  YYSYMBOL_INF_ = 11,                      /* INF_  */
  YYSYMBOL_THIS_ = 12,                     /* THIS_  */
  YYSYMBOL_PARENT = 13,                    /* PARENT  */
  YYSYMBOL_ASK_ = 14,                      /* ASK_  */
  YYSYMBOL_DEFAULT_ = 15,                  /* DEFAULT_  */
  YYSYMBOL_CONST_ = 16,                    /* CONST_  */
  YYSYMBOL_SIZEOF_ = 17,                   /* SIZEOF_  */
  YYSYMBOL_INDEX_ = 18,                    /* INDEX_  */
  YYSYMBOL_EXISTS = 19,                    /* EXISTS  */
  YYSYMBOL_TYPENAME = 20,                  /* TYPENAME  */
  YYSYMBOL_XMLDOC_ = 21,                   /* XMLDOC_  */
  YYSYMBOL_NAME = 22,                      /* NAME  */
  YYSYMBOL_INTCONSTANT = 23,               /* INTCONSTANT  */
  YYSYMBOL_REALCONSTANT = 24,              /* REALCONSTANT  */
  YYSYMBOL_STRINGCONSTANT = 25,            /* STRINGCONSTANT  */
  YYSYMBOL_EQ_ = 26,                       /* EQ_  */
  YYSYMBOL_NE_ = 27,                       /* NE_  */
  YYSYMBOL_GE_ = 28,                       /* GE_  */
  YYSYMBOL_LE_ = 29,                       /* LE_  */
  YYSYMBOL_AND_ = 30,                      /* AND_  */
  YYSYMBOL_OR_ = 31,                       /* OR_  */
  YYSYMBOL_XOR_ = 32,                      /* XOR_  */
  YYSYMBOL_NOT_ = 33,                      /* NOT_  */
  YYSYMBOL_BINAND_ = 34,                   /* BINAND_  */
  YYSYMBOL_BINOR_ = 35,                    /* BINOR_  */
  YYSYMBOL_BINXOR_ = 36,                   /* BINXOR_  */
  YYSYMBOL_BINCOMPL_ = 37,                 /* BINCOMPL_  */
  YYSYMBOL_SHIFTLEFT_ = 38,                /* SHIFTLEFT_  */
  YYSYMBOL_SHIFTRIGHT_ = 39,               /* SHIFTRIGHT_  */
  YYSYMBOL_INVALID_CHAR = 40,              /* INVALID_CHAR  */
  YYSYMBOL_41_ = 41,                       /* '?'  */
  YYSYMBOL_42_ = 42,                       /* ':'  */
  YYSYMBOL_43_ = 43,                       /* '>'  */
  YYSYMBOL_44_ = 44,                       /* '<'  */
  YYSYMBOL_45_ = 45,                       /* '+'  */
  YYSYMBOL_46_ = 46,                       /* '-'  */
  YYSYMBOL_47_ = 47,                       /* '*'  */
  YYSYMBOL_48_ = 48,                       /* '/'  */
  YYSYMBOL_49_ = 49,                       /* '%'  */
  YYSYMBOL_50_ = 50,                       /* '^'  */
  YYSYMBOL_UMIN_ = 51,                     /* UMIN_  */
  YYSYMBOL_52_ = 52,                       /* '('  */
  YYSYMBOL_53_ = 53,                       /* ')'  */
  YYSYMBOL_54_ = 54,                       /* ','  */
  YYSYMBOL_55_ = 55,                       /* '.'  */
  YYSYMBOL_56_ = 56,                       /* '['  */
  YYSYMBOL_57_ = 57,                       /* ']'  */
  YYSYMBOL_YYACCEPT = 58,                  /* $accept  */
  YYSYMBOL_expression = 59,                /* expression  */
  YYSYMBOL_expr = 60,                      /* expr  */
  YYSYMBOL_simple_expr = 61,               /* simple_expr  */
  YYSYMBOL_funcname = 62,                  /* funcname  */
  YYSYMBOL_identifier = 63,                /* identifier  */
  YYSYMBOL_special_expr = 64,              /* special_expr  */
  YYSYMBOL_literal = 65,                   /* literal  */
  YYSYMBOL_stringliteral = 66,             /* stringliteral  */
  YYSYMBOL_boolliteral = 67,               /* boolliteral  */
  YYSYMBOL_numliteral = 68,                /* numliteral  */
  YYSYMBOL_quantity = 69                   /* quantity  */
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
#define YYFINAL  58
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   804

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  58
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  12
/* YYNRULES -- Number of rules.  */
#define YYNRULES  105
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  248

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
       2,     2,     2,     2,     2,     2,     2,    49,     2,     2,
      52,    53,    47,    45,    54,    46,    55,    48,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    42,     2,
      44,     2,    43,    41,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    56,     2,    57,    50,     2,     2,     2,     2,     2,
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
      35,    36,    37,    38,    39,    40,    51
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   142,   142,   143,   145,   147,   152,   153,   154,   157,
     159,   161,   163,   165,   167,   169,   178,   180,   182,   184,
     186,   188,   191,   193,   195,   198,   202,   204,   206,   209,
     212,   214,   216,   219,   221,   223,   226,   228,   230,   232,
     234,   236,   238,   240,   242,   244,   246,   251,   252,   253,
     257,   258,   260,   265,   267,   269,   271,   273,   275,   277,
     283,   285,   287,   289,   291,   293,   295,   297,   299,   303,
     305,   307,   309,   311,   313,   315,   317,   319,   321,   324,
     326,   328,   330,   332,   334,   336,   338,   343,   344,   345,
     349,   354,   356,   361,   363,   365,   367,   369,   385,   387,
     389,   391,   393,   395,   397,   399
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
  "INTTYPE", "STRINGTYPE", "BOOLTYPE", "XMLTYPE", "TRUE_", "FALSE_",
  "NAN_", "INF_", "THIS_", "PARENT", "ASK_", "DEFAULT_", "CONST_",
  "SIZEOF_", "INDEX_", "EXISTS", "TYPENAME", "XMLDOC_", "NAME",
  "INTCONSTANT", "REALCONSTANT", "STRINGCONSTANT", "EQ_", "NE_", "GE_",
  "LE_", "AND_", "OR_", "XOR_", "NOT_", "BINAND_", "BINOR_", "BINXOR_",
  "BINCOMPL_", "SHIFTLEFT_", "SHIFTRIGHT_", "INVALID_CHAR", "'?'", "':'",
  "'>'", "'<'", "'+'", "'-'", "'*'", "'/'", "'%'", "'^'", "UMIN_", "'('",
  "')'", "','", "'.'", "'['", "']'", "$accept", "expression", "expr",
  "simple_expr", "funcname", "identifier", "special_expr", "literal",
  "stringliteral", "boolliteral", "numliteral", "quantity", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-48)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-51)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     132,   -26,     9,    17,   -48,   -48,   -48,    48,    62,    45,
      59,   -48,    52,    58,    66,    70,    77,   -48,   -48,    38,
      99,   102,   -48,   220,   220,   220,   220,   133,   729,   -48,
      80,   -48,   -48,   -48,   -48,   -48,   -48,    -5,   220,   220,
     220,   -48,   -48,   116,   137,   220,   220,    12,   109,    69,
     149,   132,   -48,   -48,   -48,   -48,   -48,   508,   -48,   220,
     220,   220,   220,   220,   220,   220,   220,   220,   220,   220,
     220,   220,   220,   220,   220,   220,   220,   220,   220,   220,
      55,   150,   158,   165,   167,   536,   564,   592,   -48,   -42,
     620,   648,   -20,    30,    50,   -48,    34,    72,    56,   -48,
     141,   -48,   213,   213,   213,   213,   147,   147,   147,   -18,
     -18,   -18,   -38,   -38,   704,   213,   213,    49,    49,   151,
     151,   151,   151,   -48,   247,   -48,   -48,   -48,   -48,   -48,
     -48,   -48,   177,   132,   -48,   -48,   -48,   178,   -48,   180,
     -48,   182,   132,   -48,   183,   -48,   184,   -48,   185,   132,
     153,   220,   -48,   220,   -48,   152,    60,    64,   159,   154,
     105,   111,   161,   160,   193,   754,   276,   163,   -48,   198,
     132,   -48,   199,   132,   -48,   171,   -48,   212,   132,   -48,
     224,   132,   -48,   195,   -48,   -48,   220,   232,   202,   207,
     203,   208,   245,   215,   214,   216,   223,   248,   305,   -48,
     -48,   229,   -48,   234,   246,   -48,   115,   -48,   124,   256,
     -48,   220,   265,   291,   -48,   -48,   294,   -48,   296,   -48,
     334,   274,   275,   285,   289,   -48,   220,   -48,   -48,   -48,
     -48,   363,   -48,   220,   392,   -48,   220,   421,   -48,   220,
     450,   -48,   220,   479,   -48,   220,   676,   -48
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       0,     0,     0,     0,    52,    91,    92,    95,    96,     0,
       0,     3,     4,     0,     0,    60,     0,    68,    51,    53,
      93,    94,    90,     0,     0,     0,     0,     0,     2,     6,
       0,    47,    48,    49,    87,    88,    89,    97,     0,     0,
       0,   104,   105,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   102,   103,    25,    29,    15,     0,     1,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    54,    55,
       0,     0,     0,     0,     0,    61,     0,     0,     0,    56,
       0,     7,    16,    17,    19,    21,    22,    23,    24,    26,
      27,    28,    30,    31,     0,    18,    20,     9,    10,    11,
      12,    13,    14,    36,     0,   100,   101,    98,    99,    34,
      33,    35,     0,     0,     5,     8,    79,     0,    80,     0,
      65,     0,     0,    69,     0,    70,     0,    62,     0,     0,
       0,     0,    37,     0,    58,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    32,     0,     0,    66,     0,
       0,    67,     0,     0,    81,     0,    63,     0,     0,    64,
       0,     0,    73,     0,    57,    38,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    59,
      85,     0,    83,     0,     0,    77,     0,    75,     0,     0,
      39,     0,     0,     0,    82,    71,     0,    72,     0,    74,
       0,     0,     0,     0,     0,    40,     0,    86,    84,    78,
      76,     0,    41,     0,     0,    42,     0,     0,    43,     0,
       0,    44,     0,     0,    45,     0,     0,    46
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -48,   -47,   -23,   -48,   -48,   -48,   -48,   -48,   -48,   -48,
     -48,   -48
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
       0,    27,    28,    29,    30,    31,    32,    33,    34,    35,
      36,    37
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      54,    55,    56,    57,   100,    81,    82,    74,    75,    76,
      77,    78,    79,   132,   133,    85,    86,    87,    83,    84,
      69,    70,    90,    91,    92,    93,    38,    74,    75,    76,
      77,    78,    79,   136,    94,   137,   102,   103,   104,   105,
     106,   107,   108,   109,   110,   111,   112,   113,   114,   115,
     116,   117,   118,   119,   120,   121,   122,   124,     1,     2,
       3,    39,     4,     5,     6,     7,     8,     9,    10,    40,
      41,    13,    14,    15,    16,    17,    18,    19,    20,    21,
      22,    96,    97,   138,    42,   139,   155,   143,    23,   144,
     -50,    98,    24,    50,    51,   159,    76,    77,    78,    79,
      43,    25,   163,   140,    45,   141,   142,    26,   123,   147,
      46,   148,   149,   168,    44,   169,   170,   171,    47,   172,
     173,    52,    48,   189,    53,   145,   191,   146,   165,    49,
     166,   194,    80,    58,   196,     1,     2,     3,    88,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,   176,    89,
     177,   178,    95,   198,   179,    23,   180,   181,   215,    24,
     216,    99,   125,    59,    60,    61,    62,   217,    25,   218,
     126,    66,    67,    68,    26,    69,    70,   127,   220,   128,
      72,    73,    74,    75,    76,    77,    78,    79,   150,   154,
     156,    79,   157,   231,   158,   160,   161,   162,   164,   167,
     234,   175,   174,   237,   182,   184,   240,   183,   187,   243,
     188,   190,   246,     1,     2,     3,   192,     4,     5,     6,
       7,     8,     9,    10,   193,     0,    13,    14,    15,    16,
      17,    18,    19,    20,    21,    22,   195,    66,    67,    68,
     197,    69,    70,    23,   199,   200,   202,    24,    74,    75,
      76,    77,    78,    79,   201,   203,    25,   204,   205,   207,
     209,   206,    26,    59,    60,    61,    62,    63,    64,    65,
     208,    66,    67,    68,   212,    69,    70,   221,    71,   213,
      72,    73,    74,    75,    76,    77,    78,    79,     0,   214,
     152,   153,    59,    60,    61,    62,    63,    64,    65,   219,
      66,    67,    68,   222,    69,    70,   223,    71,   224,    72,
      73,    74,    75,    76,    77,    78,    79,   227,   228,   185,
     186,    59,    60,    61,    62,    63,    64,    65,   229,    66,
      67,    68,   230,    69,    70,     0,    71,     0,    72,    73,
      74,    75,    76,    77,    78,    79,     0,     0,   210,   211,
      59,    60,    61,    62,    63,    64,    65,     0,    66,    67,
      68,     0,    69,    70,     0,    71,     0,    72,    73,    74,
      75,    76,    77,    78,    79,     0,     0,   225,   226,    59,
      60,    61,    62,    63,    64,    65,     0,    66,    67,    68,
       0,    69,    70,     0,    71,     0,    72,    73,    74,    75,
      76,    77,    78,    79,     0,     0,   232,   233,    59,    60,
      61,    62,    63,    64,    65,     0,    66,    67,    68,     0,
      69,    70,     0,    71,     0,    72,    73,    74,    75,    76,
      77,    78,    79,     0,     0,   235,   236,    59,    60,    61,
      62,    63,    64,    65,     0,    66,    67,    68,     0,    69,
      70,     0,    71,     0,    72,    73,    74,    75,    76,    77,
      78,    79,     0,     0,   238,   239,    59,    60,    61,    62,
      63,    64,    65,     0,    66,    67,    68,     0,    69,    70,
       0,    71,     0,    72,    73,    74,    75,    76,    77,    78,
      79,     0,     0,   241,   242,    59,    60,    61,    62,    63,
      64,    65,     0,    66,    67,    68,     0,    69,    70,     0,
      71,     0,    72,    73,    74,    75,    76,    77,    78,    79,
       0,     0,   244,   245,    59,    60,    61,    62,    63,    64,
      65,     0,    66,    67,    68,     0,    69,    70,     0,    71,
       0,    72,    73,    74,    75,    76,    77,    78,    79,     0,
       0,   101,    59,    60,    61,    62,    63,    64,    65,     0,
      66,    67,    68,     0,    69,    70,     0,    71,     0,    72,
      73,    74,    75,    76,    77,    78,    79,     0,     0,   129,
      59,    60,    61,    62,    63,    64,    65,     0,    66,    67,
      68,     0,    69,    70,     0,    71,     0,    72,    73,    74,
      75,    76,    77,    78,    79,     0,     0,   130,    59,    60,
      61,    62,    63,    64,    65,     0,    66,    67,    68,     0,
      69,    70,     0,    71,     0,    72,    73,    74,    75,    76,
      77,    78,    79,     0,     0,   131,    59,    60,    61,    62,
      63,    64,    65,     0,    66,    67,    68,     0,    69,    70,
       0,    71,     0,    72,    73,    74,    75,    76,    77,    78,
      79,     0,     0,   134,    59,    60,    61,    62,    63,    64,
      65,     0,    66,    67,    68,     0,    69,    70,     0,    71,
       0,    72,    73,    74,    75,    76,    77,    78,    79,     0,
       0,   135,    59,    60,    61,    62,    63,    64,    65,     0,
      66,    67,    68,     0,    69,    70,     0,    71,     0,    72,
      73,    74,    75,    76,    77,    78,    79,     0,     0,   247,
      59,    60,    61,    62,    63,    64,    65,     0,    66,    67,
      68,     0,    69,    70,     0,    71,   151,    72,    73,    74,
      75,    76,    77,    78,    79,    59,    60,    61,    62,    63,
      64,    65,     0,    66,    67,    68,     0,    69,    70,     0,
      71,     0,    72,    73,    74,    75,    76,    77,    78,    79,
      59,    60,    61,    62,    63,    64,    65,     0,    66,    67,
      68,     0,    69,    70,     0,     0,     0,    72,    73,    74,
      75,    76,    77,    78,    79
};

static const yytype_int16 yycheck[] =
{
      23,    24,    25,    26,    51,    10,    11,    45,    46,    47,
      48,    49,    50,    55,    56,    38,    39,    40,    23,    24,
      38,    39,    45,    46,    12,    13,    52,    45,    46,    47,
      48,    49,    50,    53,    22,    55,    59,    60,    61,    62,
      63,    64,    65,    66,    67,    68,    69,    70,    71,    72,
      73,    74,    75,    76,    77,    78,    79,    80,     3,     4,
       5,    52,     7,     8,     9,    10,    11,    12,    13,    52,
      22,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    12,    13,    53,    22,    55,   133,    53,    33,    55,
      52,    22,    37,    55,    56,   142,    47,    48,    49,    50,
      55,    46,   149,    53,    52,    55,    56,    52,    53,    53,
      52,    55,    56,    53,    55,    55,    56,    53,    52,    55,
      56,    22,    52,   170,    22,    53,   173,    55,   151,    52,
     153,   178,    52,     0,   181,     3,     4,     5,    22,     7,
       8,     9,    10,    11,    12,    13,    14,    15,    16,    17,
      18,    19,    20,    21,    22,    23,    24,    25,    53,    22,
      55,    56,    53,   186,    53,    33,    55,    56,    53,    37,
      55,    22,    22,    26,    27,    28,    29,    53,    46,    55,
      22,    34,    35,    36,    52,    38,    39,    22,   211,    22,
      43,    44,    45,    46,    47,    48,    49,    50,    57,    22,
      22,    50,    22,   226,    22,    22,    22,    22,    55,    57,
     233,    57,    53,   236,    53,    22,   239,    57,    55,   242,
      22,    22,   245,     3,     4,     5,    55,     7,     8,     9,
      10,    11,    12,    13,    22,    -1,    16,    17,    18,    19,
      20,    21,    22,    23,    24,    25,    22,    34,    35,    36,
      55,    38,    39,    33,    22,    53,    53,    37,    45,    46,
      47,    48,    49,    50,    57,    57,    46,    22,    53,    53,
      22,    57,    52,    26,    27,    28,    29,    30,    31,    32,
      57,    34,    35,    36,    55,    38,    39,    22,    41,    55,
      43,    44,    45,    46,    47,    48,    49,    50,    -1,    53,
      53,    54,    26,    27,    28,    29,    30,    31,    32,    53,
      34,    35,    36,    22,    38,    39,    22,    41,    22,    43,
      44,    45,    46,    47,    48,    49,    50,    53,    53,    53,
      54,    26,    27,    28,    29,    30,    31,    32,    53,    34,
      35,    36,    53,    38,    39,    -1,    41,    -1,    43,    44,
      45,    46,    47,    48,    49,    50,    -1,    -1,    53,    54,
      26,    27,    28,    29,    30,    31,    32,    -1,    34,    35,
      36,    -1,    38,    39,    -1,    41,    -1,    43,    44,    45,
      46,    47,    48,    49,    50,    -1,    -1,    53,    54,    26,
      27,    28,    29,    30,    31,    32,    -1,    34,    35,    36,
      -1,    38,    39,    -1,    41,    -1,    43,    44,    45,    46,
      47,    48,    49,    50,    -1,    -1,    53,    54,    26,    27,
      28,    29,    30,    31,    32,    -1,    34,    35,    36,    -1,
      38,    39,    -1,    41,    -1,    43,    44,    45,    46,    47,
      48,    49,    50,    -1,    -1,    53,    54,    26,    27,    28,
      29,    30,    31,    32,    -1,    34,    35,    36,    -1,    38,
      39,    -1,    41,    -1,    43,    44,    45,    46,    47,    48,
      49,    50,    -1,    -1,    53,    54,    26,    27,    28,    29,
      30,    31,    32,    -1,    34,    35,    36,    -1,    38,    39,
      -1,    41,    -1,    43,    44,    45,    46,    47,    48,    49,
      50,    -1,    -1,    53,    54,    26,    27,    28,    29,    30,
      31,    32,    -1,    34,    35,    36,    -1,    38,    39,    -1,
      41,    -1,    43,    44,    45,    46,    47,    48,    49,    50,
      -1,    -1,    53,    54,    26,    27,    28,    29,    30,    31,
      32,    -1,    34,    35,    36,    -1,    38,    39,    -1,    41,
      -1,    43,    44,    45,    46,    47,    48,    49,    50,    -1,
      -1,    53,    26,    27,    28,    29,    30,    31,    32,    -1,
      34,    35,    36,    -1,    38,    39,    -1,    41,    -1,    43,
      44,    45,    46,    47,    48,    49,    50,    -1,    -1,    53,
      26,    27,    28,    29,    30,    31,    32,    -1,    34,    35,
      36,    -1,    38,    39,    -1,    41,    -1,    43,    44,    45,
      46,    47,    48,    49,    50,    -1,    -1,    53,    26,    27,
      28,    29,    30,    31,    32,    -1,    34,    35,    36,    -1,
      38,    39,    -1,    41,    -1,    43,    44,    45,    46,    47,
      48,    49,    50,    -1,    -1,    53,    26,    27,    28,    29,
      30,    31,    32,    -1,    34,    35,    36,    -1,    38,    39,
      -1,    41,    -1,    43,    44,    45,    46,    47,    48,    49,
      50,    -1,    -1,    53,    26,    27,    28,    29,    30,    31,
      32,    -1,    34,    35,    36,    -1,    38,    39,    -1,    41,
      -1,    43,    44,    45,    46,    47,    48,    49,    50,    -1,
      -1,    53,    26,    27,    28,    29,    30,    31,    32,    -1,
      34,    35,    36,    -1,    38,    39,    -1,    41,    -1,    43,
      44,    45,    46,    47,    48,    49,    50,    -1,    -1,    53,
      26,    27,    28,    29,    30,    31,    32,    -1,    34,    35,
      36,    -1,    38,    39,    -1,    41,    42,    43,    44,    45,
      46,    47,    48,    49,    50,    26,    27,    28,    29,    30,
      31,    32,    -1,    34,    35,    36,    -1,    38,    39,    -1,
      41,    -1,    43,    44,    45,    46,    47,    48,    49,    50,
      26,    27,    28,    29,    30,    31,    32,    -1,    34,    35,
      36,    -1,    38,    39,    -1,    -1,    -1,    43,    44,    45,
      46,    47,    48,    49,    50
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,     3,     4,     5,     7,     8,     9,    10,    11,    12,
      13,    14,    15,    16,    17,    18,    19,    20,    21,    22,
      23,    24,    25,    33,    37,    46,    52,    59,    60,    61,
      62,    63,    64,    65,    66,    67,    68,    69,    52,    52,
      52,    22,    22,    55,    55,    52,    52,    52,    52,    52,
      55,    56,    22,    22,    60,    60,    60,    60,     0,    26,
      27,    28,    29,    30,    31,    32,    34,    35,    36,    38,
      39,    41,    43,    44,    45,    46,    47,    48,    49,    50,
      52,    10,    11,    23,    24,    60,    60,    60,    22,    22,
      60,    60,    12,    13,    22,    53,    12,    13,    22,    22,
      59,    53,    60,    60,    60,    60,    60,    60,    60,    60,
      60,    60,    60,    60,    60,    60,    60,    60,    60,    60,
      60,    60,    60,    53,    60,    22,    22,    22,    22,    53,
      53,    53,    55,    56,    53,    53,    53,    55,    53,    55,
      53,    55,    56,    53,    55,    53,    55,    53,    55,    56,
      57,    42,    53,    54,    22,    59,    22,    22,    22,    59,
      22,    22,    22,    59,    55,    60,    60,    57,    53,    55,
      56,    53,    55,    56,    53,    57,    53,    55,    56,    53,
      55,    56,    53,    57,    22,    53,    54,    55,    22,    59,
      22,    59,    55,    22,    59,    22,    59,    55,    60,    22,
      53,    57,    53,    57,    22,    53,    57,    53,    57,    22,
      53,    54,    55,    55,    53,    53,    55,    53,    55,    53,
      60,    22,    22,    22,    22,    53,    54,    53,    53,    53,
      53,    60,    53,    54,    60,    53,    54,    60,    53,    54,
      60,    53,    54,    60,    53,    54,    60,    53
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    58,    59,    59,    59,    59,    60,    60,    60,    60,
      60,    60,    60,    60,    60,    60,    60,    60,    60,    60,
      60,    60,    60,    60,    60,    60,    60,    60,    60,    60,
      60,    60,    60,    60,    60,    60,    60,    60,    60,    60,
      60,    60,    60,    60,    60,    60,    60,    61,    61,    61,
      62,    62,    62,    63,    63,    63,    63,    63,    63,    63,
      64,    64,    64,    64,    64,    64,    64,    64,    64,    64,
      64,    64,    64,    64,    64,    64,    64,    64,    64,    64,
      64,    64,    64,    64,    64,    64,    64,    65,    65,    65,
      66,    67,    67,    68,    68,    68,    68,    68,    69,    69,
      69,    69,    69,    69,    69,    69
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     1,     1,     4,     1,     3,     4,     3,
       3,     3,     3,     3,     3,     2,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     2,     3,     3,     3,     2,
       3,     3,     5,     4,     4,     4,     3,     4,     6,     8,
      10,    12,    14,    16,    18,    20,    22,     1,     1,     1,
       1,     1,     1,     1,     3,     3,     3,     6,     5,     8,
       1,     3,     4,     6,     6,     4,     6,     6,     1,     4,
       4,     9,     9,     6,     9,     8,    11,     8,    11,     4,
       4,     6,     9,     8,    11,     8,    11,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     3,     3,
       3,     3,     2,     2,     2,     2
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
  case 3: /* expression: ASK_  */
#line 144 "expr.y"
                { yyerror("\"ask\" is not supported here"); }
#line 1489 "expr.tab.cc"
    break;

  case 4: /* expression: DEFAULT_  */
#line 146 "expr.y"
                { yyerror("\"default\" is not supported here"); }
#line 1495 "expr.tab.cc"
    break;

  case 5: /* expression: DEFAULT_ '(' expr ')'  */
#line 148 "expr.y"
                { yyerror("\"default()\" is not supported here"); }
#line 1501 "expr.tab.cc"
    break;

  case 8: /* expr: CONST_ '(' expr ')'  */
#line 155 "expr.y"
                { yyerror("const() is not supported here"); }
#line 1507 "expr.tab.cc"
    break;

  case 9: /* expr: expr '+' expr  */
#line 158 "expr.y"
                { *e++ = cDynamicExpression::ADD; }
#line 1513 "expr.tab.cc"
    break;

  case 10: /* expr: expr '-' expr  */
#line 160 "expr.y"
                { *e++ = cDynamicExpression::SUB; }
#line 1519 "expr.tab.cc"
    break;

  case 11: /* expr: expr '*' expr  */
#line 162 "expr.y"
                { *e++ = cDynamicExpression::MUL; }
#line 1525 "expr.tab.cc"
    break;

  case 12: /* expr: expr '/' expr  */
#line 164 "expr.y"
                { *e++ = cDynamicExpression::DIV; }
#line 1531 "expr.tab.cc"
    break;

  case 13: /* expr: expr '%' expr  */
#line 166 "expr.y"
                { *e++ = cDynamicExpression::MOD; }
#line 1537 "expr.tab.cc"
    break;

  case 14: /* expr: expr '^' expr  */
#line 168 "expr.y"
                { *e++ = cDynamicExpression::POW; }
#line 1543 "expr.tab.cc"
    break;

  case 15: /* expr: '-' expr  */
#line 171 "expr.y"
                {
                   cDynamicExpression::Elem& last = *(e-1);
                   if (last.isNumericConstant())
                       last.negate();
                   else
                       *e++ = cDynamicExpression::NEG;
                }
#line 1555 "expr.tab.cc"
    break;

  case 16: /* expr: expr EQ_ expr  */
#line 179 "expr.y"
                { *e++ = cDynamicExpression::EQ; }
#line 1561 "expr.tab.cc"
    break;

  case 17: /* expr: expr NE_ expr  */
#line 181 "expr.y"
                { *e++ = cDynamicExpression::NE; }
#line 1567 "expr.tab.cc"
    break;

  case 18: /* expr: expr '>' expr  */
#line 183 "expr.y"
                { *e++ = cDynamicExpression::GT; }
#line 1573 "expr.tab.cc"
    break;

  case 19: /* expr: expr GE_ expr  */
#line 185 "expr.y"
                { *e++ = cDynamicExpression::GE; }
#line 1579 "expr.tab.cc"
    break;

  case 20: /* expr: expr '<' expr  */
#line 187 "expr.y"
                { *e++ = cDynamicExpression::LT; }
#line 1585 "expr.tab.cc"
    break;

  case 21: /* expr: expr LE_ expr  */
#line 189 "expr.y"
                { *e++ = cDynamicExpression::LE; }
#line 1591 "expr.tab.cc"
    break;

  case 22: /* expr: expr AND_ expr  */
#line 192 "expr.y"
                { *e++ = cDynamicExpression::AND; }
#line 1597 "expr.tab.cc"
    break;

  case 23: /* expr: expr OR_ expr  */
#line 194 "expr.y"
                { *e++ = cDynamicExpression::OR; }
#line 1603 "expr.tab.cc"
    break;

  case 24: /* expr: expr XOR_ expr  */
#line 196 "expr.y"
                { *e++ = cDynamicExpression::XOR; }
#line 1609 "expr.tab.cc"
    break;

  case 25: /* expr: NOT_ expr  */
#line 200 "expr.y"
                { *e++ = cDynamicExpression::NOT; }
#line 1615 "expr.tab.cc"
    break;

  case 26: /* expr: expr BINAND_ expr  */
#line 203 "expr.y"
                { *e++ = cDynamicExpression::BIN_AND; }
#line 1621 "expr.tab.cc"
    break;

  case 27: /* expr: expr BINOR_ expr  */
#line 205 "expr.y"
                { *e++ = cDynamicExpression::BIN_OR; }
#line 1627 "expr.tab.cc"
    break;

  case 28: /* expr: expr BINXOR_ expr  */
#line 207 "expr.y"
                { *e++ = cDynamicExpression::BIN_XOR; }
#line 1633 "expr.tab.cc"
    break;

  case 29: /* expr: BINCOMPL_ expr  */
#line 211 "expr.y"
                { *e++ = cDynamicExpression::BIN_NOT; }
#line 1639 "expr.tab.cc"
    break;

  case 30: /* expr: expr SHIFTLEFT_ expr  */
#line 213 "expr.y"
                { *e++ = cDynamicExpression::LSHIFT; }
#line 1645 "expr.tab.cc"
    break;

  case 31: /* expr: expr SHIFTRIGHT_ expr  */
#line 215 "expr.y"
                { *e++ = cDynamicExpression::RSHIFT; }
#line 1651 "expr.tab.cc"
    break;

  case 32: /* expr: expr '?' expr ':' expr  */
#line 217 "expr.y"
                { *e++ = cDynamicExpression::IIF; }
#line 1657 "expr.tab.cc"
    break;

  case 33: /* expr: INTTYPE '(' expr ')'  */
#line 220 "expr.y"
                { addFunction("int",1); }
#line 1663 "expr.tab.cc"
    break;

  case 34: /* expr: DOUBLETYPE '(' expr ')'  */
#line 222 "expr.y"
                { addFunction("double",1); }
#line 1669 "expr.tab.cc"
    break;

  case 35: /* expr: STRINGTYPE '(' expr ')'  */
#line 224 "expr.y"
                { addFunction("string",1); }
#line 1675 "expr.tab.cc"
    break;

  case 36: /* expr: funcname '(' ')'  */
#line 227 "expr.y"
                { addFunction(yyvsp[-2],0); delete [] yyvsp[-2]; }
#line 1681 "expr.tab.cc"
    break;

  case 37: /* expr: funcname '(' expr ')'  */
#line 229 "expr.y"
                { addFunction(yyvsp[-3],1); delete [] yyvsp[-3]; }
#line 1687 "expr.tab.cc"
    break;

  case 38: /* expr: funcname '(' expr ',' expr ')'  */
#line 231 "expr.y"
                { addFunction(yyvsp[-5],2); delete [] yyvsp[-5]; }
#line 1693 "expr.tab.cc"
    break;

  case 39: /* expr: funcname '(' expr ',' expr ',' expr ')'  */
#line 233 "expr.y"
                { addFunction(yyvsp[-7],3); delete [] yyvsp[-7]; }
#line 1699 "expr.tab.cc"
    break;

  case 40: /* expr: funcname '(' expr ',' expr ',' expr ',' expr ')'  */
#line 235 "expr.y"
                { addFunction(yyvsp[-9],4); delete [] yyvsp[-9]; }
#line 1705 "expr.tab.cc"
    break;

  case 41: /* expr: funcname '(' expr ',' expr ',' expr ',' expr ',' expr ')'  */
#line 237 "expr.y"
                { addFunction(yyvsp[-11],5); delete [] yyvsp[-11]; }
#line 1711 "expr.tab.cc"
    break;

  case 42: /* expr: funcname '(' expr ',' expr ',' expr ',' expr ',' expr ',' expr ')'  */
#line 239 "expr.y"
                { addFunction(yyvsp[-13],6); delete [] yyvsp[-13]; }
#line 1717 "expr.tab.cc"
    break;

  case 43: /* expr: funcname '(' expr ',' expr ',' expr ',' expr ',' expr ',' expr ',' expr ')'  */
#line 241 "expr.y"
                { addFunction(yyvsp[-15],7); delete [] yyvsp[-15]; }
#line 1723 "expr.tab.cc"
    break;

  case 44: /* expr: funcname '(' expr ',' expr ',' expr ',' expr ',' expr ',' expr ',' expr ',' expr ')'  */
#line 243 "expr.y"
                { addFunction(yyvsp[-17],8); delete [] yyvsp[-17]; }
#line 1729 "expr.tab.cc"
    break;

  case 45: /* expr: funcname '(' expr ',' expr ',' expr ',' expr ',' expr ',' expr ',' expr ',' expr ',' expr ')'  */
#line 245 "expr.y"
                { addFunction(yyvsp[-19],9); delete [] yyvsp[-19]; }
#line 1735 "expr.tab.cc"
    break;

  case 46: /* expr: funcname '(' expr ',' expr ',' expr ',' expr ',' expr ',' expr ',' expr ',' expr ',' expr ',' expr ')'  */
#line 247 "expr.y"
                { addFunction(yyvsp[-21],10); delete [] yyvsp[-21]; }
#line 1741 "expr.tab.cc"
    break;

  case 51: /* funcname: XMLDOC_  */
#line 259 "expr.y"
                { yyval = common::opp_strdup("xmldoc"); }
#line 1747 "expr.tab.cc"
    break;

  case 52: /* funcname: XMLTYPE  */
#line 261 "expr.y"
                { yyval = common::opp_strdup("xml"); }
#line 1753 "expr.tab.cc"
    break;

  case 53: /* identifier: NAME  */
#line 266 "expr.y"
                { *e++ = new ParameterRef(yyvsp[0], true, false); delete [] yyvsp[0]; }
#line 1759 "expr.tab.cc"
    break;

  case 54: /* identifier: THIS_ '.' NAME  */
#line 268 "expr.y"
                { *e++ = new ParameterRef(yyvsp[0], false, true); delete [] yyvsp[0]; }
#line 1765 "expr.tab.cc"
    break;

  case 55: /* identifier: PARENT '.' NAME  */
#line 270 "expr.y"
                { *e++ = new ParameterRef(yyvsp[0], true, true); delete [] yyvsp[0]; }
#line 1771 "expr.tab.cc"
    break;

  case 56: /* identifier: NAME '.' NAME  */
#line 272 "expr.y"
                { *e++ = new SiblingModuleParameterRef(yyvsp[-2], yyvsp[0], true, false); delete [] yyvsp[-2]; delete [] yyvsp[0]; }
#line 1777 "expr.tab.cc"
    break;

  case 57: /* identifier: NAME '[' expression ']' '.' NAME  */
#line 274 "expr.y"
                { *e++ = new SiblingModuleParameterRef(yyvsp[-5], yyvsp[0], true, true); delete [] yyvsp[-5]; delete [] yyvsp[0]; }
#line 1783 "expr.tab.cc"
    break;

  case 58: /* identifier: PARENT '.' NAME '.' NAME  */
#line 276 "expr.y"
                { *e++ = new SiblingModuleParameterRef(yyvsp[-2], yyvsp[0], true, false); delete [] yyvsp[-2]; delete [] yyvsp[0]; }
#line 1789 "expr.tab.cc"
    break;

  case 59: /* identifier: PARENT '.' NAME '[' expression ']' '.' NAME  */
#line 278 "expr.y"
                { *e++ = new SiblingModuleParameterRef(yyvsp[-5], yyvsp[0], true, true); delete [] yyvsp[-5]; delete [] yyvsp[0]; }
#line 1795 "expr.tab.cc"
    break;

  case 60: /* special_expr: INDEX_  */
#line 284 "expr.y"
                { *e++ = new ModuleIndex(); }
#line 1801 "expr.tab.cc"
    break;

  case 61: /* special_expr: INDEX_ '(' ')'  */
#line 286 "expr.y"
                { *e++ = new ModuleIndex(); }
#line 1807 "expr.tab.cc"
    break;

  case 62: /* special_expr: EXISTS '(' NAME ')'  */
#line 288 "expr.y"
                { *e++ = new Exists(yyvsp[-1], true, false); delete [] yyvsp[-1]; }
#line 1813 "expr.tab.cc"
    break;

  case 63: /* special_expr: EXISTS '(' THIS_ '.' NAME ')'  */
#line 290 "expr.y"
                { *e++ = new Exists(yyvsp[-1], false, true); delete [] yyvsp[-1]; }
#line 1819 "expr.tab.cc"
    break;

  case 64: /* special_expr: EXISTS '(' PARENT '.' NAME ')'  */
#line 292 "expr.y"
                { *e++ = new Exists(yyvsp[-1], true, true); delete [] yyvsp[-1]; }
#line 1825 "expr.tab.cc"
    break;

  case 65: /* special_expr: SIZEOF_ '(' NAME ')'  */
#line 294 "expr.y"
                { *e++ = new Sizeof(yyvsp[-1], true, false); delete [] yyvsp[-1]; }
#line 1831 "expr.tab.cc"
    break;

  case 66: /* special_expr: SIZEOF_ '(' THIS_ '.' NAME ')'  */
#line 296 "expr.y"
                { *e++ = new Sizeof(yyvsp[-1], false, true); delete [] yyvsp[-1]; }
#line 1837 "expr.tab.cc"
    break;

  case 67: /* special_expr: SIZEOF_ '(' PARENT '.' NAME ')'  */
#line 298 "expr.y"
                { *e++ = new Sizeof(yyvsp[-1], true, true); delete [] yyvsp[-1]; }
#line 1843 "expr.tab.cc"
    break;

  case 68: /* special_expr: TYPENAME  */
#line 300 "expr.y"
                { *e++ = new Typename(); }
#line 1849 "expr.tab.cc"
    break;

  case 69: /* special_expr: EXISTS '(' THIS_ ')'  */
#line 304 "expr.y"
                { yyerror("exists(this) form not supported here"); }
#line 1855 "expr.tab.cc"
    break;

  case 70: /* special_expr: EXISTS '(' PARENT ')'  */
#line 306 "expr.y"
                { yyerror("exists(parent) form not supported here"); }
#line 1861 "expr.tab.cc"
    break;

  case 71: /* special_expr: EXISTS '(' THIS_ '.' NAME '[' expression ']' ')'  */
#line 308 "expr.y"
                { delete [] yyvsp[-4]; yyerror("exists(this.name[index]) form not supported here"); }
#line 1867 "expr.tab.cc"
    break;

  case 72: /* special_expr: EXISTS '(' PARENT '.' NAME '[' expression ']' ')'  */
#line 310 "expr.y"
                { delete [] yyvsp[-4]; yyerror("exists(parent.name[index]) form not supported here"); }
#line 1873 "expr.tab.cc"
    break;

  case 73: /* special_expr: EXISTS '(' NAME '.' NAME ')'  */
#line 312 "expr.y"
                { delete [] yyvsp[-3]; delete [] yyvsp[-1]; yyerror("exists(submodule.gate) form not supported here"); }
#line 1879 "expr.tab.cc"
    break;

  case 74: /* special_expr: EXISTS '(' NAME '[' expression ']' '.' NAME ')'  */
#line 314 "expr.y"
                { delete [] yyvsp[-6]; delete [] yyvsp[-1]; yyerror("exists(submodule[index].gate) form not supported here"); }
#line 1885 "expr.tab.cc"
    break;

  case 75: /* special_expr: EXISTS '(' PARENT '.' NAME '.' NAME ')'  */
#line 316 "expr.y"
                { delete [] yyvsp[-3]; delete [] yyvsp[-1]; yyerror("exists(parent.submodule.gate) form not supported here"); }
#line 1891 "expr.tab.cc"
    break;

  case 76: /* special_expr: EXISTS '(' PARENT '.' NAME '[' expression ']' '.' NAME ')'  */
#line 318 "expr.y"
                { delete [] yyvsp[-6]; delete [] yyvsp[-1]; yyerror("exists(parent.submodule[index].gate) form not supported here"); }
#line 1897 "expr.tab.cc"
    break;

  case 77: /* special_expr: EXISTS '(' THIS_ '.' NAME '.' NAME ')'  */
#line 320 "expr.y"
                { delete [] yyvsp[-3]; delete [] yyvsp[-1]; yyerror("exists(this.submodule.gate) form not supported here"); }
#line 1903 "expr.tab.cc"
    break;

  case 78: /* special_expr: EXISTS '(' THIS_ '.' NAME '[' expression ']' '.' NAME ')'  */
#line 322 "expr.y"
                { delete [] yyvsp[-6]; delete [] yyvsp[-1]; yyerror("exists(this.submodule[index].gate) form not supported here"); }
#line 1909 "expr.tab.cc"
    break;

  case 79: /* special_expr: SIZEOF_ '(' THIS_ ')'  */
#line 325 "expr.y"
                { yyerror("sizeof(this) form not supported here"); }
#line 1915 "expr.tab.cc"
    break;

  case 80: /* special_expr: SIZEOF_ '(' PARENT ')'  */
#line 327 "expr.y"
                { yyerror("sizeof(parent) form not supported here"); }
#line 1921 "expr.tab.cc"
    break;

  case 81: /* special_expr: SIZEOF_ '(' NAME '.' NAME ')'  */
#line 329 "expr.y"
                { delete [] yyvsp[-3]; delete [] yyvsp[-1]; yyerror("sizeof(submodule.gate) form not supported here"); }
#line 1927 "expr.tab.cc"
    break;

  case 82: /* special_expr: SIZEOF_ '(' NAME '[' expression ']' '.' NAME ')'  */
#line 331 "expr.y"
                { delete [] yyvsp[-6]; delete [] yyvsp[-1]; yyerror("sizeof(submodule[index].gate) form not supported here"); }
#line 1933 "expr.tab.cc"
    break;

  case 83: /* special_expr: SIZEOF_ '(' PARENT '.' NAME '.' NAME ')'  */
#line 333 "expr.y"
                { delete [] yyvsp[-3]; delete [] yyvsp[-1]; yyerror("sizeof(parent.submodule.gate) form not supported here"); }
#line 1939 "expr.tab.cc"
    break;

  case 84: /* special_expr: SIZEOF_ '(' PARENT '.' NAME '[' expression ']' '.' NAME ')'  */
#line 335 "expr.y"
                { delete [] yyvsp[-6]; delete [] yyvsp[-1]; yyerror("sizeof(parent.submodule[index].gate) form not supported here"); }
#line 1945 "expr.tab.cc"
    break;

  case 85: /* special_expr: SIZEOF_ '(' THIS_ '.' NAME '.' NAME ')'  */
#line 337 "expr.y"
                { delete [] yyvsp[-3]; delete [] yyvsp[-1]; yyerror("sizeof(this.submodule.gate) form not supported here"); }
#line 1951 "expr.tab.cc"
    break;

  case 86: /* special_expr: SIZEOF_ '(' THIS_ '.' NAME '[' expression ']' '.' NAME ')'  */
#line 339 "expr.y"
                { delete [] yyvsp[-6]; delete [] yyvsp[-1]; yyerror("sizeof(this.submodule[index].gate) form not supported here"); }
#line 1957 "expr.tab.cc"
    break;

  case 90: /* stringliteral: STRINGCONSTANT  */
#line 350 "expr.y"
                { *e++ = opp_parsequotedstr(yyvsp[0]).c_str(); delete [] yyvsp[0]; }
#line 1963 "expr.tab.cc"
    break;

  case 91: /* boolliteral: TRUE_  */
#line 355 "expr.y"
                { *e++ = true; }
#line 1969 "expr.tab.cc"
    break;

  case 92: /* boolliteral: FALSE_  */
#line 357 "expr.y"
                { *e++ = false; }
#line 1975 "expr.tab.cc"
    break;

  case 93: /* numliteral: INTCONSTANT  */
#line 362 "expr.y"
                { *e++ = (intpar_t)opp_atoll(yyvsp[0]); delete [] yyvsp[0]; }
#line 1981 "expr.tab.cc"
    break;

  case 94: /* numliteral: REALCONSTANT  */
#line 364 "expr.y"
                { *e++ = opp_atof(yyvsp[0]); delete [] yyvsp[0]; }
#line 1987 "expr.tab.cc"
    break;

  case 95: /* numliteral: NAN_  */
#line 366 "expr.y"
                { *e++ = std::nan(""); }
#line 1993 "expr.tab.cc"
    break;

  case 96: /* numliteral: INF_  */
#line 368 "expr.y"
                { *e++ = 1/0.0; }
#line 1999 "expr.tab.cc"
    break;

  case 97: /* numliteral: quantity  */
#line 370 "expr.y"
                {
                  std::string unit;
                  double d = parseQuantity(yyvsp[0], unit);
                  intpar_t l = (intpar_t)d; 
                  if (d == l)
                      *e++ = l;
                  else
                      *e++ = d;
                  if (!unit.empty())
                      (e-1)->setUnit(unit.c_str());
                  delete [] yyvsp[0];
                }
#line 2016 "expr.tab.cc"
    break;

  case 98: /* quantity: quantity INTCONSTANT NAME  */
#line 386 "expr.y"
                { yyval = expryyconcat(yyvsp[-2],yyvsp[-1],yyvsp[0]); }
#line 2022 "expr.tab.cc"
    break;

  case 99: /* quantity: quantity REALCONSTANT NAME  */
#line 388 "expr.y"
                { yyval = expryyconcat(yyvsp[-2],yyvsp[-1],yyvsp[0]); }
#line 2028 "expr.tab.cc"
    break;

  case 100: /* quantity: quantity NAN_ NAME  */
#line 390 "expr.y"
                { yyval = expryyconcat(yyvsp[-2],omnetpp::opp_strdup("nan"),yyvsp[0]); }
#line 2034 "expr.tab.cc"
    break;

  case 101: /* quantity: quantity INF_ NAME  */
#line 392 "expr.y"
                { yyval = expryyconcat(yyvsp[-2],omnetpp::opp_strdup("inf"),yyvsp[0]); }
#line 2040 "expr.tab.cc"
    break;

  case 102: /* quantity: INTCONSTANT NAME  */
#line 394 "expr.y"
                { yyval = expryyconcat(yyvsp[-1],yyvsp[0]); }
#line 2046 "expr.tab.cc"
    break;

  case 103: /* quantity: REALCONSTANT NAME  */
#line 396 "expr.y"
                { yyval = expryyconcat(yyvsp[-1],yyvsp[0]); }
#line 2052 "expr.tab.cc"
    break;

  case 104: /* quantity: NAN_ NAME  */
#line 398 "expr.y"
                { yyval = expryyconcat(omnetpp::opp_strdup("nan"),yyvsp[0]); }
#line 2058 "expr.tab.cc"
    break;

  case 105: /* quantity: INF_ NAME  */
#line 400 "expr.y"
                { yyval = expryyconcat(omnetpp::opp_strdup("inf"),yyvsp[0]); }
#line 2064 "expr.tab.cc"
    break;


#line 2068 "expr.tab.cc"

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

#line 403 "expr.y"


//----------------------------------------------------------------------

void doParseExpression(const char *nedtext, cDynamicExpression::Elem *&elems, int& nelems)
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
    struct yy_buffer_state *handle = yy_scan_string(nedtext);
    if (!handle)
        throw std::runtime_error("Parser is unable to allocate work memory");

    cDynamicExpression::Elem *v = new cDynamicExpression::Elem[100]; // overestimate for now; XXX danger of overrun
    e = v;

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
    elems = new cDynamicExpression::Elem[nelems];
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

