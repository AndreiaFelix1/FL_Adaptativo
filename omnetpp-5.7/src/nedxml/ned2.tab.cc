/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Skeleton implementation for Bison GLR parsers in C

   Copyright (C) 2002-2015, 2018-2021 Free Software Foundation, Inc.

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

/* C GLR parser skeleton written by Paul Hilfinger.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

/* Identify Bison output, and Bison version.  */
#define YYBISON 30802

/* Bison version string.  */
#define YYBISON_VERSION "3.8.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "glr.c"

/* Pure parsers.  */
#define YYPURE 0




/* Substitute the variable and function names.  */
#define yyparse ned2yyparse
#define yylex   ned2yylex
#define yyerror ned2yyerror
#define yydebug ned2yydebug
#define yylval  ned2yylval
#define yychar  ned2yychar
#define yynerrs ned2yynerrs
#define yylloc  ned2yylloc

/* First part of user prologue.  */
#line 81 "ned2.y"


#include <cstdio>
#include <cstdlib>
#include <stack>
#include "common/commonutil.h"
#include "common/stringutil.h"
#include "yydefs.h"
#include "errorstore.h"
#include "sourcedocument.h"
#include "exception.h"
#include "nedelements.h"

#define YYDEBUG 1           /* allow debugging */
#define YYDEBUGGING_ON 0    /* turn on/off debugging */

#if YYDEBUG != 0
#define YYERROR_VERBOSE     /* more detailed error messages */
#include <cstring>         /* YYVERBOSE needs it */
#endif

/* increase GLR stack -- with the default 200 some NED files have reportedly caused a "memory exhausted" error */
#define YYINITDEPTH 500

#define yylloc ned2yylloc
#define yyin ned2yyin
#define yyout ned2yyout
#define yyrestart ned2yyrestart
#define yy_scan_string ned2yy_scan_string
#define yy_delete_buffer ned2yy_delete_buffer
extern FILE *yyin;
extern FILE *yyout;
struct yy_buffer_state;
struct yy_buffer_state *yy_scan_string(const char *str);
void yy_delete_buffer(struct yy_buffer_state *);
void yyrestart(FILE *);
int yylex();
void yyerror (omnetpp::nedxml::ParseContext *np, const char *s);

#include "nedutil.h"
#include "nedyyutil.h"

using namespace omnetpp;

using namespace omnetpp::common;
using namespace omnetpp::nedxml;
using namespace omnetpp::nedxml::nedyyutil;

static struct NedParserState
{
    bool inTypes;
    bool inConnGroup;
    std::stack<ASTNode *> propertyscope; // top(): where to insert properties as we parse them
    std::stack<ASTNode *> blockscope;    // top(): where to insert parameters, gates, etc
    std::stack<ASTNode *> typescope;     // top(): as blockscope, but ignore submodules and connection channels

    /* tmp flags, used with param, gate and conn */
    int paramType;
    int gateType;
    bool isVolatile;
    bool isDefault;
    YYLTYPE exprPos;
    int subgate;
    std::vector<ASTNode *> propvals; // temporarily collects property values

    /* tmp flags, used with msg fields */
    bool isAbstract;
    bool isReadonly;

    /* NED-II: modules, channels */
    NedFileElement *nedfile;
    CommentElement *comment;
    PackageElement *package;
    ImportElement *import;
    PropertyDeclElement *propertydecl;
    ExtendsElement *extends;
    InterfaceNameElement *interfacename;
    ASTNode *component;  // compound/simple module, module interface, channel or channel interface
    ParametersElement *parameters;
    ParamElement *param;
    PropertyElement *property;
    PropertyKeyElement *propkey;
    TypesElement *types;
    GatesElement *gates;
    GateElement *gate;
    SubmodulesElement *submods;
    SubmoduleElement *submod;
    ConnectionsElement *conns;
    ConnectionGroupElement *conngroup;
    ConnectionElement *conn;
    LoopElement *loop;
    ConditionElement *condition;
} ps;


static void resetParserState()
{
    static NedParserState cleanps;
    ps = cleanps;
}

static NedParserState globalps;  // for error recovery

static void restoreGlobalParserState()  // for error recovery
{
    ps = globalps;
}

static void assertNonEmpty(std::stack<ASTNode *>& somescope)
{
    // for error recovery: STL stack::top() crashes if stack is empty
    if (somescope.empty())
    {
        INTERNAL_ERROR0(nullptr, "error during parsing: scope stack empty");
        somescope.push(nullptr);
    }
}


#line 186 "ned2.tab.cc"

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

#include "ned2.tab.hh"

/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_IMPORT = 3,                     /* IMPORT  */
  YYSYMBOL_PACKAGE = 4,                    /* PACKAGE  */
  YYSYMBOL_PROPERTY = 5,                   /* PROPERTY  */
  YYSYMBOL_MODULE = 6,                     /* MODULE  */
  YYSYMBOL_SIMPLE = 7,                     /* SIMPLE  */
  YYSYMBOL_NETWORK = 8,                    /* NETWORK  */
  YYSYMBOL_CHANNEL = 9,                    /* CHANNEL  */
  YYSYMBOL_MODULEINTERFACE = 10,           /* MODULEINTERFACE  */
  YYSYMBOL_CHANNELINTERFACE = 11,          /* CHANNELINTERFACE  */
  YYSYMBOL_EXTENDS = 12,                   /* EXTENDS  */
  YYSYMBOL_LIKE = 13,                      /* LIKE  */
  YYSYMBOL_TYPES = 14,                     /* TYPES  */
  YYSYMBOL_PARAMETERS = 15,                /* PARAMETERS  */
  YYSYMBOL_GATES = 16,                     /* GATES  */
  YYSYMBOL_SUBMODULES = 17,                /* SUBMODULES  */
  YYSYMBOL_CONNECTIONS = 18,               /* CONNECTIONS  */
  YYSYMBOL_ALLOWUNCONNECTED = 19,          /* ALLOWUNCONNECTED  */
  YYSYMBOL_DOUBLETYPE = 20,                /* DOUBLETYPE  */
  YYSYMBOL_INTTYPE = 21,                   /* INTTYPE  */
  YYSYMBOL_STRINGTYPE = 22,                /* STRINGTYPE  */
  YYSYMBOL_BOOLTYPE = 23,                  /* BOOLTYPE  */
  YYSYMBOL_XMLTYPE = 24,                   /* XMLTYPE  */
  YYSYMBOL_VOLATILE = 25,                  /* VOLATILE  */
  YYSYMBOL_INPUT_ = 26,                    /* INPUT_  */
  YYSYMBOL_OUTPUT_ = 27,                   /* OUTPUT_  */
  YYSYMBOL_INOUT_ = 28,                    /* INOUT_  */
  YYSYMBOL_IF = 29,                        /* IF  */
  YYSYMBOL_FOR = 30,                       /* FOR  */
  YYSYMBOL_RIGHTARROW = 31,                /* RIGHTARROW  */
  YYSYMBOL_LEFTARROW = 32,                 /* LEFTARROW  */
  YYSYMBOL_DBLARROW = 33,                  /* DBLARROW  */
  YYSYMBOL_TO = 34,                        /* TO  */
  YYSYMBOL_TRUE_ = 35,                     /* TRUE_  */
  YYSYMBOL_FALSE_ = 36,                    /* FALSE_  */
  YYSYMBOL_NAN_ = 37,                      /* NAN_  */
  YYSYMBOL_INF_ = 38,                      /* INF_  */
  YYSYMBOL_THIS_ = 39,                     /* THIS_  */
  YYSYMBOL_PARENT = 40,                    /* PARENT  */
  YYSYMBOL_DEFAULT = 41,                   /* DEFAULT  */
  YYSYMBOL_ASK = 42,                       /* ASK  */
  YYSYMBOL_CONST_ = 43,                    /* CONST_  */
  YYSYMBOL_SIZEOF = 44,                    /* SIZEOF  */
  YYSYMBOL_INDEX_ = 45,                    /* INDEX_  */
  YYSYMBOL_EXISTS = 46,                    /* EXISTS  */
  YYSYMBOL_TYPENAME = 47,                  /* TYPENAME  */
  YYSYMBOL_XMLDOC = 48,                    /* XMLDOC  */
  YYSYMBOL_NAME = 49,                      /* NAME  */
  YYSYMBOL_PROPNAME = 50,                  /* PROPNAME  */
  YYSYMBOL_INTCONSTANT = 51,               /* INTCONSTANT  */
  YYSYMBOL_REALCONSTANT = 52,              /* REALCONSTANT  */
  YYSYMBOL_STRINGCONSTANT = 53,            /* STRINGCONSTANT  */
  YYSYMBOL_CHARCONSTANT = 54,              /* CHARCONSTANT  */
  YYSYMBOL_PLUSPLUS = 55,                  /* PLUSPLUS  */
  YYSYMBOL_DOUBLEASTERISK = 56,            /* DOUBLEASTERISK  */
  YYSYMBOL_EQ = 57,                        /* EQ  */
  YYSYMBOL_NE = 58,                        /* NE  */
  YYSYMBOL_GE = 59,                        /* GE  */
  YYSYMBOL_LE = 60,                        /* LE  */
  YYSYMBOL_AND = 61,                       /* AND  */
  YYSYMBOL_OR = 62,                        /* OR  */
  YYSYMBOL_XOR = 63,                       /* XOR  */
  YYSYMBOL_NOT = 64,                       /* NOT  */
  YYSYMBOL_BIN_AND = 65,                   /* BIN_AND  */
  YYSYMBOL_BIN_OR = 66,                    /* BIN_OR  */
  YYSYMBOL_BIN_XOR = 67,                   /* BIN_XOR  */
  YYSYMBOL_BIN_COMPL = 68,                 /* BIN_COMPL  */
  YYSYMBOL_SHIFT_LEFT = 69,                /* SHIFT_LEFT  */
  YYSYMBOL_SHIFT_RIGHT = 70,               /* SHIFT_RIGHT  */
  YYSYMBOL_EXPRESSION_SELECTOR = 71,       /* EXPRESSION_SELECTOR  */
  YYSYMBOL_CHAR = 72,                      /* CHAR  */
  YYSYMBOL_INVALID_CHAR = 73,              /* INVALID_CHAR  */
  YYSYMBOL_74_ = 74,                       /* '?'  */
  YYSYMBOL_75_ = 75,                       /* ':'  */
  YYSYMBOL_76_ = 76,                       /* '>'  */
  YYSYMBOL_77_ = 77,                       /* '<'  */
  YYSYMBOL_78_ = 78,                       /* '+'  */
  YYSYMBOL_79_ = 79,                       /* '-'  */
  YYSYMBOL_80_ = 80,                       /* '*'  */
  YYSYMBOL_81_ = 81,                       /* '/'  */
  YYSYMBOL_82_ = 82,                       /* '%'  */
  YYSYMBOL_83_ = 83,                       /* '^'  */
  YYSYMBOL_UMIN = 84,                      /* UMIN  */
  YYSYMBOL_85_ = 85,                       /* ';'  */
  YYSYMBOL_86_ = 86,                       /* '}'  */
  YYSYMBOL_87_ = 87,                       /* '.'  */
  YYSYMBOL_88_ = 88,                       /* '('  */
  YYSYMBOL_89_ = 89,                       /* ')'  */
  YYSYMBOL_90_ = 90,                       /* '@'  */
  YYSYMBOL_91_ = 91,                       /* '['  */
  YYSYMBOL_92_ = 92,                       /* ']'  */
  YYSYMBOL_93_ = 93,                       /* '{'  */
  YYSYMBOL_94_ = 94,                       /* ','  */
  YYSYMBOL_95_ = 95,                       /* '='  */
  YYSYMBOL_96_ = 96,                       /* '$'  */
  YYSYMBOL_YYACCEPT = 97,                  /* $accept  */
  YYSYMBOL_startsymbol = 98,               /* startsymbol  */
  YYSYMBOL_nedfile = 99,                   /* nedfile  */
  YYSYMBOL_definitions = 100,              /* definitions  */
  YYSYMBOL_definition = 101,               /* definition  */
  YYSYMBOL_packagedeclaration = 102,       /* packagedeclaration  */
  YYSYMBOL_dottedname = 103,               /* dottedname  */
  YYSYMBOL_import = 104,                   /* import  */
  YYSYMBOL_importspec = 105,               /* importspec  */
  YYSYMBOL_importname = 106,               /* importname  */
  YYSYMBOL_propertydecl = 107,             /* propertydecl  */
  YYSYMBOL_propertydecl_header = 108,      /* propertydecl_header  */
  YYSYMBOL_opt_propertydecl_keys = 109,    /* opt_propertydecl_keys  */
  YYSYMBOL_propertydecl_keys = 110,        /* propertydecl_keys  */
  YYSYMBOL_propertydecl_key = 111,         /* propertydecl_key  */
  YYSYMBOL_fileproperty = 112,             /* fileproperty  */
  YYSYMBOL_channeldefinition = 113,        /* channeldefinition  */
  YYSYMBOL_114_1 = 114,                    /* $@1  */
  YYSYMBOL_channelheader = 115,            /* channelheader  */
  YYSYMBOL_116_2 = 116,                    /* $@2  */
  YYSYMBOL_opt_inheritance = 117,          /* opt_inheritance  */
  YYSYMBOL_extendsname = 118,              /* extendsname  */
  YYSYMBOL_likenames = 119,                /* likenames  */
  YYSYMBOL_likename = 120,                 /* likename  */
  YYSYMBOL_channelinterfacedefinition = 121, /* channelinterfacedefinition  */
  YYSYMBOL_122_3 = 122,                    /* $@3  */
  YYSYMBOL_channelinterfaceheader = 123,   /* channelinterfaceheader  */
  YYSYMBOL_124_4 = 124,                    /* $@4  */
  YYSYMBOL_opt_interfaceinheritance = 125, /* opt_interfaceinheritance  */
  YYSYMBOL_extendsnames = 126,             /* extendsnames  */
  YYSYMBOL_simplemoduledefinition = 127,   /* simplemoduledefinition  */
  YYSYMBOL_128_5 = 128,                    /* $@5  */
  YYSYMBOL_simplemoduleheader = 129,       /* simplemoduleheader  */
  YYSYMBOL_130_6 = 130,                    /* $@6  */
  YYSYMBOL_compoundmoduledefinition = 131, /* compoundmoduledefinition  */
  YYSYMBOL_132_7 = 132,                    /* $@7  */
  YYSYMBOL_compoundmoduleheader = 133,     /* compoundmoduleheader  */
  YYSYMBOL_134_8 = 134,                    /* $@8  */
  YYSYMBOL_networkdefinition = 135,        /* networkdefinition  */
  YYSYMBOL_136_9 = 136,                    /* $@9  */
  YYSYMBOL_networkheader = 137,            /* networkheader  */
  YYSYMBOL_138_10 = 138,                   /* $@10  */
  YYSYMBOL_moduleinterfacedefinition = 139, /* moduleinterfacedefinition  */
  YYSYMBOL_140_11 = 140,                   /* $@11  */
  YYSYMBOL_moduleinterfaceheader = 141,    /* moduleinterfaceheader  */
  YYSYMBOL_142_12 = 142,                   /* $@12  */
  YYSYMBOL_opt_paramblock = 143,           /* opt_paramblock  */
  YYSYMBOL_144_13 = 144,                   /* $@13  */
  YYSYMBOL_opt_params = 145,               /* opt_params  */
  YYSYMBOL_params = 146,                   /* params  */
  YYSYMBOL_paramsitem = 147,               /* paramsitem  */
  YYSYMBOL_param = 148,                    /* param  */
  YYSYMBOL_param_typenamevalue = 149,      /* param_typenamevalue  */
  YYSYMBOL_param_typename = 150,           /* param_typename  */
  YYSYMBOL_pattern_value = 151,            /* pattern_value  */
  YYSYMBOL_paramtype = 152,                /* paramtype  */
  YYSYMBOL_opt_volatile = 153,             /* opt_volatile  */
  YYSYMBOL_paramvalue = 154,               /* paramvalue  */
  YYSYMBOL_opt_inline_properties = 155,    /* opt_inline_properties  */
  YYSYMBOL_inline_properties = 156,        /* inline_properties  */
  YYSYMBOL_pattern = 157,                  /* pattern  */
  YYSYMBOL_pattern2 = 158,                 /* pattern2  */
  YYSYMBOL_pattern_elem = 159,             /* pattern_elem  */
  YYSYMBOL_pattern_name = 160,             /* pattern_name  */
  YYSYMBOL_pattern_index = 161,            /* pattern_index  */
  YYSYMBOL_property = 162,                 /* property  */
  YYSYMBOL_property_namevalue = 163,       /* property_namevalue  */
  YYSYMBOL_property_name = 164,            /* property_name  */
  YYSYMBOL_opt_property_keys = 165,        /* opt_property_keys  */
  YYSYMBOL_property_keys = 166,            /* property_keys  */
  YYSYMBOL_property_key = 167,             /* property_key  */
  YYSYMBOL_property_values = 168,          /* property_values  */
  YYSYMBOL_property_value = 169,           /* property_value  */
  YYSYMBOL_property_literal = 170,         /* property_literal  */
  YYSYMBOL_opt_gateblock = 171,            /* opt_gateblock  */
  YYSYMBOL_gateblock = 172,                /* gateblock  */
  YYSYMBOL_173_14 = 173,                   /* $@14  */
  YYSYMBOL_opt_gates = 174,                /* opt_gates  */
  YYSYMBOL_gates = 175,                    /* gates  */
  YYSYMBOL_gate = 176,                     /* gate  */
  YYSYMBOL_177_15 = 177,                   /* $@15  */
  YYSYMBOL_gate_typenamesize = 178,        /* gate_typenamesize  */
  YYSYMBOL_gatetype = 179,                 /* gatetype  */
  YYSYMBOL_opt_typeblock = 180,            /* opt_typeblock  */
  YYSYMBOL_typeblock = 181,                /* typeblock  */
  YYSYMBOL_182_16 = 182,                   /* $@16  */
  YYSYMBOL_opt_localtypes = 183,           /* opt_localtypes  */
  YYSYMBOL_localtypes = 184,               /* localtypes  */
  YYSYMBOL_localtype = 185,                /* localtype  */
  YYSYMBOL_opt_submodblock = 186,          /* opt_submodblock  */
  YYSYMBOL_submodblock = 187,              /* submodblock  */
  YYSYMBOL_188_17 = 188,                   /* $@17  */
  YYSYMBOL_opt_submodules = 189,           /* opt_submodules  */
  YYSYMBOL_submodules = 190,               /* submodules  */
  YYSYMBOL_submodule = 191,                /* submodule  */
  YYSYMBOL_192_18 = 192,                   /* $@18  */
  YYSYMBOL_submoduleheader = 193,          /* submoduleheader  */
  YYSYMBOL_submodulename = 194,            /* submodulename  */
  YYSYMBOL_likeexpr = 195,                 /* likeexpr  */
  YYSYMBOL_opt_condition = 196,            /* opt_condition  */
  YYSYMBOL_opt_connblock = 197,            /* opt_connblock  */
  YYSYMBOL_connblock = 198,                /* connblock  */
  YYSYMBOL_199_19 = 199,                   /* $@19  */
  YYSYMBOL_200_20 = 200,                   /* $@20  */
  YYSYMBOL_opt_connections = 201,          /* opt_connections  */
  YYSYMBOL_connections = 202,              /* connections  */
  YYSYMBOL_connectionsitem = 203,          /* connectionsitem  */
  YYSYMBOL_connectiongroup = 204,          /* connectiongroup  */
  YYSYMBOL_205_21 = 205,                   /* $@21  */
  YYSYMBOL_opt_loops_and_conditions = 206, /* opt_loops_and_conditions  */
  YYSYMBOL_loops_and_conditions = 207,     /* loops_and_conditions  */
  YYSYMBOL_loop_or_condition = 208,        /* loop_or_condition  */
  YYSYMBOL_loop = 209,                     /* loop  */
  YYSYMBOL_connection = 210,               /* connection  */
  YYSYMBOL_leftgatespec = 211,             /* leftgatespec  */
  YYSYMBOL_leftmod = 212,                  /* leftmod  */
  YYSYMBOL_leftgate = 213,                 /* leftgate  */
  YYSYMBOL_parentleftgate = 214,           /* parentleftgate  */
  YYSYMBOL_rightgatespec = 215,            /* rightgatespec  */
  YYSYMBOL_rightmod = 216,                 /* rightmod  */
  YYSYMBOL_rightgate = 217,                /* rightgate  */
  YYSYMBOL_parentrightgate = 218,          /* parentrightgate  */
  YYSYMBOL_opt_subgate = 219,              /* opt_subgate  */
  YYSYMBOL_channelspec = 220,              /* channelspec  */
  YYSYMBOL_221_22 = 221,                   /* $@22  */
  YYSYMBOL_channelspec_header = 222,       /* channelspec_header  */
  YYSYMBOL_opt_channelname = 223,          /* opt_channelname  */
  YYSYMBOL_condition = 224,                /* condition  */
  YYSYMBOL_vector = 225,                   /* vector  */
  YYSYMBOL_expression = 226,               /* expression  */
  YYSYMBOL_expr = 227,                     /* expr  */
  YYSYMBOL_simple_expr = 228,              /* simple_expr  */
  YYSYMBOL_funcname = 229,                 /* funcname  */
  YYSYMBOL_identifier = 230,               /* identifier  */
  YYSYMBOL_operator = 231,                 /* operator  */
  YYSYMBOL_literal = 232,                  /* literal  */
  YYSYMBOL_stringliteral = 233,            /* stringliteral  */
  YYSYMBOL_boolliteral = 234,              /* boolliteral  */
  YYSYMBOL_numliteral = 235,               /* numliteral  */
  YYSYMBOL_quantity = 236,                 /* quantity  */
  YYSYMBOL_realconstant_ext = 237,         /* realconstant_ext  */
  YYSYMBOL_opt_semicolon = 238             /* opt_semicolon  */
};
typedef enum yysymbol_kind_t yysymbol_kind_t;


/* Default (constant) value used for initialization for null
   right-hand sides.  Unlike the standard yacc.c template, here we set
   the default value of $$ to a zeroed-out value.  Since the default
   value is undefined, this behavior is technically correct.  */
static YYSTYPE yyval_default;
static YYLTYPE yyloc_default
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL
  = { 1, 1, 1, 1 }
# endif
;



#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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


#ifndef YYFREE
# define YYFREE free
#endif
#ifndef YYMALLOC
# define YYMALLOC malloc
#endif
#ifndef YYREALLOC
# define YYREALLOC realloc
#endif

#ifdef __cplusplus
  typedef bool yybool;
# define yytrue true
# define yyfalse false
#else
  /* When we move to stdbool, get rid of the various casts to yybool.  */
  typedef signed char yybool;
# define yytrue 1
# define yyfalse 0
#endif

#ifndef YYSETJMP
# include <setjmp.h>
# define YYJMP_BUF jmp_buf
# define YYSETJMP(Env) setjmp (Env)
/* Pacify Clang and ICC.  */
# define YYLONGJMP(Env, Val)                    \
 do {                                           \
   longjmp (Env, Val);                          \
   YY_ASSERT (0);                               \
 } while (yyfalse)
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

/* The _Noreturn keyword of C11.  */
#ifndef _Noreturn
# if (defined __cplusplus \
      && ((201103 <= __cplusplus && !(__GNUC__ == 4 && __GNUC_MINOR__ == 7)) \
          || (defined _MSC_VER && 1900 <= _MSC_VER)))
#  define _Noreturn [[noreturn]]
# elif ((!defined __cplusplus || defined __clang__) \
        && (201112 <= (defined __STDC_VERSION__ ? __STDC_VERSION__ : 0) \
            || (!defined __STRICT_ANSI__ \
                && (4 < __GNUC__ + (7 <= __GNUC_MINOR__) \
                    || (defined __apple_build_version__ \
                        ? 6000000 <= __apple_build_version__ \
                        : 3 < __clang_major__ + (5 <= __clang_minor__))))))
   /* _Noreturn works as-is.  */
# elif (2 < __GNUC__ + (8 <= __GNUC_MINOR__) || defined __clang__ \
        || 0x5110 <= __SUNPRO_C)
#  define _Noreturn __attribute__ ((__noreturn__))
# elif 1200 <= (defined _MSC_VER ? _MSC_VER : 0)
#  define _Noreturn __declspec (noreturn)
# else
#  define _Noreturn
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

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  92
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   1436

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  97
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  142
/* YYNRULES -- Number of rules.  */
#define YYNRULES  349
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  605
/* YYMAXRHS -- Maximum number of symbols on right-hand side of rule.  */
#define YYMAXRHS 22
/* YYMAXLEFT -- Maximum number of symbols to the left of a handle
   accessed by $0, $-1, etc., in any rule.  */
#define YYMAXLEFT 0

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   329

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
       2,     2,     2,     2,     2,     2,    96,    82,     2,     2,
      88,    89,    80,    78,    94,    79,    87,    81,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    75,    85,
      77,    95,    76,    74,    90,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    91,     2,    92,    83,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    93,     2,    86,     2,     2,     2,     2,
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
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    73,    84
};

#if YYDEBUG
/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   207,   207,   209,   216,   217,   221,   222,   226,   227,
     228,   229,   230,   231,   232,   233,   234,   235,   236,   238,
     240,   242,   244,   246,   248,   250,   252,   254,   256,   258,
     260,   265,   275,   276,   283,   293,   294,   298,   299,   300,
     301,   302,   303,   310,   315,   323,   328,   337,   338,   342,
     343,   347,   359,   371,   370,   394,   393,   403,   404,   405,
     406,   410,   419,   420,   424,   437,   436,   460,   459,   469,
     470,   474,   475,   483,   482,   507,   506,   520,   519,   547,
     546,   560,   559,   587,   586,   603,   602,   627,   626,   639,
     648,   647,   657,   658,   662,   663,   667,   668,   672,   673,
     680,   686,   704,   711,   719,   741,   743,   745,   747,   749,
     754,   757,   761,   763,   765,   769,   777,   778,   782,   783,
     787,   788,   792,   793,   797,   798,   799,   800,   804,   805,
     806,   807,   808,   809,   810,   811,   815,   816,   817,   818,
     825,   833,   834,   838,   844,   854,   858,   859,   863,   872,
     884,   886,   891,   896,   904,   905,   906,   907,   914,   915,
     920,   919,   932,   933,   937,   941,   952,   951,   963,   968,
     974,   981,   985,   990,   999,  1001,  1003,  1011,  1012,  1017,
    1016,  1033,  1034,  1038,  1039,  1043,  1044,  1045,  1046,  1047,
    1048,  1049,  1050,  1057,  1058,  1063,  1062,  1075,  1076,  1080,
    1081,  1085,  1091,  1090,  1110,  1115,  1125,  1130,  1139,  1141,
    1143,  1148,  1151,  1158,  1159,  1164,  1163,  1175,  1174,  1187,
    1188,  1192,  1193,  1197,  1198,  1211,  1210,  1232,  1235,  1239,
    1244,  1252,  1253,  1257,  1272,  1277,  1282,  1288,  1294,  1298,
    1305,  1306,  1310,  1316,  1324,  1329,  1335,  1344,  1351,  1359,
    1370,  1371,  1375,  1379,  1387,  1392,  1398,  1407,  1412,  1418,
    1427,  1438,  1442,  1444,  1443,  1458,  1459,  1463,  1472,  1473,
    1481,  1494,  1500,  1510,  1511,  1513,  1516,  1518,  1520,  1522,
    1524,  1526,  1528,  1539,  1541,  1543,  1545,  1547,  1549,  1552,
    1554,  1556,  1559,  1563,  1565,  1567,  1570,  1573,  1575,  1577,
    1580,  1582,  1584,  1587,  1589,  1591,  1593,  1595,  1597,  1599,
    1601,  1603,  1605,  1607,  1613,  1614,  1615,  1619,  1620,  1621,
    1625,  1627,  1629,  1631,  1633,  1635,  1637,  1642,  1644,  1646,
    1648,  1650,  1655,  1656,  1657,  1661,  1666,  1668,  1673,  1675,
    1677,  1682,  1683,  1684,  1685,  1689,  1690,  1691,  1695,  1696
};
#endif

#define YYPACT_NINF (-473)
#define YYTABLE_NINF (-318)

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
      44,   187,    14,    -3,    41,    55,    57,    69,    70,    77,
     634,  -473,    81,   107,  -473,   184,  -473,  -473,  -473,  -473,
     142,  -473,  -473,     7,  -473,    15,  -473,    17,  -473,    18,
    -473,    19,  -473,    20,    90,    78,  -473,  -473,  -473,   214,
     196,  -473,   245,   183,   180,  -473,   189,  -473,   199,  -473,
     206,  -473,   220,  -473,   227,  -473,   191,   230,   274,  -473,
    -473,  -473,  -473,  -473,   223,   246,   286,   319,   321,   322,
    -473,  -473,   282,   368,  -473,  -473,   634,   634,   634,   634,
    1272,  -473,   330,  -473,  -473,  -473,  -473,  -473,  -473,   252,
     381,   343,  -473,  -473,    23,   353,   349,  -473,   365,  -473,
     366,  -473,   370,  -473,   377,  -473,   379,  -473,   380,  -473,
    -473,    23,  -473,   187,  -473,  -473,  -473,  -473,   404,   363,
    -473,   168,  -473,   168,  -473,   168,  -473,   168,  -473,   450,
    -473,   450,   634,   634,   634,   418,   420,   634,   258,   382,
     258,   421,   634,  -473,  -473,  -473,  -473,  1047,   634,   634,
     634,   634,   634,   634,   634,   634,   634,   634,   634,   634,
     634,   634,   634,   634,   634,   634,   634,   634,   634,   437,
     430,   438,  -473,   447,  -473,  -473,   409,   414,  -473,    33,
    -473,  -473,  -473,   231,  -473,   231,  -473,   222,  -473,   193,
    -473,   193,  -473,   222,   411,   417,  -473,   412,  -473,   -12,
     196,  -473,   416,    14,    14,  -473,  -473,  -473,  -473,    14,
    -473,  -473,  1080,  1113,  1146,  -473,   114,  1179,   171,   415,
    -473,   425,  -473,   991,  -473,   298,   298,   298,   298,  1353,
     452,  1326,   256,   323,   367,   413,   413,  1245,   298,   298,
     302,   302,   441,   441,   441,   441,  -473,   649,  -473,  -473,
     428,   349,    23,  -473,  -473,  -473,   461,  -473,   224,  -473,
    -473,   128,   453,  -473,   201,  -473,  -473,  -473,   349,  -473,
     525,   408,   440,  -473,   148,  -473,   458,   464,   522,   522,
     522,   522,  -473,    23,    23,    23,  -473,   465,   538,   465,
     459,  -473,  -473,   476,  -473,  -473,  -473,   526,   634,  -473,
    -473,  -473,   487,   634,  -473,   634,  -473,   492,  -473,  -473,
     529,   528,   546,   495,  -473,  -473,   169,  -473,  -473,  -473,
    -473,  -473,   534,   520,   116,  -473,  -473,    40,   128,  -473,
    -473,   510,   500,  -473,   573,   573,   504,  -473,  -473,    33,
     412,    14,    14,    14,  -473,  1019,   542,  1272,   687,  -473,
     201,  -473,  -473,   549,  -473,  -473,   520,  -473,   505,  -473,
     512,  -473,  1299,  -473,   506,   514,   511,   513,   518,  -473,
    -473,   531,   590,  -473,   590,  -473,   459,  -473,  -473,   537,
    -473,  -473,   634,  -473,  -473,   349,   634,  -473,  -473,  -473,
    -473,   233,  -473,   541,   610,  -473,   610,   580,   725,   545,
     543,  -473,  -473,  -473,   540,  -473,   233,  -473,  -473,   584,
      24,  -473,     5,   548,  -473,   550,  -473,  -473,   634,  -473,
    -473,   307,  -473,  -473,   349,   544,   588,   591,   592,   594,
     595,   596,  -473,  -473,  -473,   553,  -473,   554,  -473,   555,
    -473,   556,  -473,   558,  -473,   559,  -473,    24,  -473,   608,
     564,  -473,  -473,  -473,   763,  -473,   567,   575,   376,  -473,
    -473,   570,  -473,   608,  -473,    43,   589,  -473,     8,  -473,
     634,  -473,  -473,  -473,   634,  -473,  -473,  -473,  -473,    26,
       8,   634,   614,   181,  -473,     8,  -473,  -473,   572,   581,
    -473,  -473,    52,   410,   579,  -473,  -473,   801,   222,   574,
     -23,   654,  -473,  -473,   593,   619,     6,  -473,  -473,  -473,
      52,   599,   627,   640,   641,   642,  -473,   634,   522,   604,
    -473,   617,  -473,  -473,    14,   634,  -473,  -473,  -473,   155,
    -473,  -473,   209,  -473,   607,  -473,   664,   603,    26,  -473,
     665,  -473,   666,   605,  -473,   839,   618,   634,  -473,   -23,
     669,    10,  -473,    80,  -473,   651,   656,  -473,   465,   704,
     656,   656,   172,  -473,   634,   635,   632,  -473,   634,   635,
    -473,  -473,   605,  -473,   270,  -473,   231,    14,  -473,  -473,
    -473,  -473,   877,  -473,  -473,   648,  -473,  -473,   174,   647,
     465,  -473,   634,  -473,  -473,  -473,  -473,   915,  -473,   634,
     953,  -473,   634,  1212,  -473
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int16 yydefact[] =
{
       5,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    18,     0,     0,     3,     4,     7,     8,     9,    10,
     117,    11,    12,     0,    13,     0,    14,     0,    15,     0,
      16,     0,    17,     0,     0,   141,    40,    42,    41,     0,
      36,    33,     0,     0,     0,    79,     0,    75,     0,    83,
       0,    55,     0,    87,     0,    67,     0,     0,     0,   319,
     336,   337,   347,   346,     0,     0,     0,     0,   327,     0,
     331,   318,   320,   338,   345,   335,     0,     0,     0,     0,
       2,   273,     0,   314,   315,   316,   332,   333,   334,   340,
     339,   143,     1,     6,    48,     0,   116,   119,     0,    53,
       0,    65,     0,    73,     0,    77,     0,    81,     0,    85,
      52,   153,    34,     0,    37,    39,    38,    31,     0,    45,
      24,    57,    22,    57,    26,    57,    30,    57,    28,    70,
      20,    70,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   343,   292,   296,   282,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   344,     0,   157,   156,     0,    47,    50,    51,
      43,   118,    29,   111,    19,   111,    21,   111,    23,    93,
      25,    93,    27,   111,     0,   145,   147,   149,   151,   152,
      35,    32,     0,     0,     0,    80,    76,    84,    56,     0,
      88,    68,     0,     0,     0,   321,   322,     0,   320,     0,
     328,     0,   323,     0,   274,   283,   284,   286,   288,   289,
     290,   291,   293,   294,   295,   297,   298,     0,   285,   287,
     276,   277,   278,   279,   280,   281,   303,     0,   341,   342,
       0,   117,     0,   155,   154,   130,     0,   110,   128,   127,
     132,     0,     0,    89,    92,    95,    96,    98,   117,    99,
       0,     0,     0,   123,   124,    97,     0,     0,   159,   159,
     159,   159,   142,   153,   153,   153,    46,    61,    58,    64,
      59,    63,    72,    69,   301,   300,   302,     0,     0,   275,
     330,   329,     0,     0,   304,     0,   144,     0,    49,    90,
       0,     0,   136,     0,    54,    94,     0,   105,   106,   107,
     108,   109,     0,     0,     0,   133,   135,     0,     0,   140,
      66,     0,     0,   158,   178,   178,     0,   146,   150,   152,
     148,     0,     0,     0,   325,     0,     0,   299,     0,    44,
      93,   129,   138,   139,   131,   100,     0,   102,   114,   115,
       0,   112,   272,   121,   128,   120,     0,     0,     0,   160,
      74,     0,   194,   177,   194,    86,    60,    62,    71,     0,
     324,   305,     0,    91,   137,   117,     0,   104,   126,   125,
     134,   163,   179,     0,   214,   193,   214,     0,     0,     0,
       0,   174,   175,   176,   171,   161,   162,   165,   166,     0,
     182,   195,     0,     0,   213,     0,   326,   306,     0,   101,
     113,     0,   173,   164,   117,   168,     0,     0,     0,     0,
       0,     0,   192,   185,   186,     0,   187,     0,   188,     0,
     189,     0,   190,     0,   191,     0,   180,   181,   184,   198,
       0,   217,    78,    82,     0,   172,     0,     0,     0,   170,
     183,   206,   196,   197,   200,     0,     0,   215,   220,   307,
       0,   271,   167,   169,     0,   207,   199,   201,   202,     0,
     220,     0,     0,   261,   218,   219,   222,   223,     0,   227,
     230,   231,   228,     0,     0,   241,   232,     0,   111,     0,
     212,     0,   216,   270,     0,     0,   247,   242,   221,   225,
       0,     0,   268,   268,   268,     0,   308,     0,   159,     0,
     208,     0,   204,   211,     0,     0,   260,   249,   248,   228,
     229,   224,   261,   234,     0,   251,     0,   262,   265,   236,
       0,   238,     0,   261,   240,     0,     0,     0,   209,   212,
       0,   228,   269,   257,   253,     0,     0,   263,   266,     0,
       0,     0,   244,   309,     0,   349,     0,   205,     0,   349,
     259,   258,   261,   250,   261,   235,   111,     0,   237,   239,
     246,   245,     0,   348,   203,     0,   233,   226,   254,     0,
     267,   310,     0,   210,   256,   255,   264,     0,   311,     0,
       0,   312,     0,     0,   313
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -473,  -473,  -473,  -473,   719,  -473,    -1,  -473,  -473,   622,
    -348,  -473,  -473,  -473,   484,  -473,  -345,  -473,  -331,  -473,
     308,  -183,   396,   397,  -326,  -473,  -280,  -473,   609,  -473,
    -277,  -473,  -273,  -473,  -241,  -473,  -228,  -473,  -227,  -473,
    -212,  -473,  -203,  -473,  -199,  -473,  -182,  -473,   391,  -473,
     478,  -473,  -473,  -473,  -473,  -473,  -473,   395,  -224,  -473,
    -473,  -473,   431,  -473,    -5,  -473,     2,  -473,  -473,  -473,
     475,   474,   488,  -107,  -267,  -473,  -473,  -473,  -473,   354,
    -473,  -473,  -473,   427,  -473,  -473,  -473,  -473,   324,   399,
    -473,  -473,  -473,  -473,   311,  -473,  -473,  -473,   237,   228,
     383,  -473,  -473,  -473,   300,   249,  -462,  -473,  -473,   297,
    -473,   283,  -473,  -473,  -473,  -473,  -473,  -473,  -468,  -473,
    -473,  -473,  -458,  -165,  -473,  -473,  -473,  -472,  -389,  -313,
     -10,  -473,  -473,   251,  -473,  -473,  -473,  -473,  -473,  -473,
     707,   229
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
       0,    13,    14,    15,    16,    17,   287,    18,    39,    40,
      19,    20,   176,   177,   178,    21,    22,   183,    23,   127,
     205,   288,   290,   291,    24,   185,    25,   131,   210,   293,
      26,   187,    27,   123,    28,   189,    29,   121,    30,   191,
      31,   125,    32,   193,    33,   129,   262,   350,   263,   264,
     265,   266,   267,   268,   269,   322,   270,   360,    95,    96,
     271,   272,   273,   274,   313,   275,   276,    35,   194,   195,
     196,   197,   198,   179,   332,   333,   391,   405,   406,   407,
     424,   408,   409,   372,   373,   410,   446,   447,   448,   394,
     395,   449,   462,   463,   464,   498,   465,   466,   501,   522,
     413,   414,   480,   468,   484,   485,   486,   487,   529,   488,
     489,   490,   491,   492,   493,   494,   544,   495,   533,   534,
     573,   535,   553,   536,   576,   537,   538,   496,   554,   456,
     362,    81,    82,    83,    84,    85,    86,    87,    88,    89,
      90,   584
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      80,    42,    34,   277,   199,   278,   481,   279,    98,   280,
     361,   281,   334,   335,   336,   422,   100,    34,   102,   104,
     106,   108,    97,   508,   450,   506,   292,   307,   523,     3,
     426,   427,   428,   429,   430,   431,   459,   481,   482,   481,
     482,   253,    44,   361,   316,   539,   541,     1,     2,     3,
       4,     5,     6,     7,     8,     9,    46,   483,    48,   483,
     254,   527,   433,    41,   118,   434,   144,   145,   146,   147,
      50,    52,   475,   400,   311,    41,   174,   523,    54,   435,
     451,   481,   482,   285,   436,   562,   253,    43,   575,   508,
      45,   312,   578,   579,   507,   175,   569,   474,   181,   433,
      99,  -228,   434,   499,    47,   254,    49,    92,   101,   432,
     103,   105,   107,   109,   588,    10,   435,   528,    51,    53,
     366,   436,   212,   213,   214,   255,    55,   217,   477,    11,
     437,    91,   223,   438,    12,   570,   478,   439,   225,   226,
     227,   228,   229,   230,   231,   232,   233,   234,   235,   236,
     237,   238,   239,   240,   241,   242,   243,   244,   245,   247,
     378,   399,   311,   363,   571,   364,   111,   437,   503,   440,
     438,   474,   259,   581,   439,   110,   199,   339,   339,   312,
     203,   204,   441,   442,   481,   482,   521,     1,     2,     3,
       4,     5,     6,     7,     8,     9,   260,   325,   443,   595,
     457,   297,   255,   289,   483,   298,   440,   444,   256,   261,
     255,   445,   550,  -111,  -111,  -111,  -111,  -111,   257,   441,
     442,  -111,  -111,  -111,  -111,  -111,   257,   580,   326,   594,
      94,   255,    12,   119,   566,   443,    36,   256,   -93,   327,
     255,   328,   258,    37,   444,   114,   256,   257,   445,   259,
     258,   546,   115,    97,   355,   586,   257,   259,   141,   401,
     402,   403,   142,   474,   356,   474,   120,    38,  -243,    11,
      97,   258,   474,   260,    12,   122,   116,   505,   259,   132,
     258,   260,   404,    12,   552,   124,   261,   259,   345,    62,
      63,    12,   126,   347,   261,   348,  -252,    64,    65,   112,
     474,   113,   260,   170,    74,   505,   128,   218,   -93,  -103,
     135,   260,    12,   130,  -103,   261,   518,   -93,   133,  -103,
     310,    12,   367,   368,   261,   158,   159,    56,    57,    58,
     117,    59,   118,   136,   163,   164,   165,   166,   167,   168,
     289,   289,    60,    61,    62,    63,    64,    65,   540,   542,
      66,    67,    68,    69,    70,    71,    72,  -252,    73,    74,
      75,   474,   134,   155,   156,   157,   505,   158,   159,   141,
    -317,    76,   398,   142,   137,    77,   163,   164,   165,   166,
     167,   168,   165,   166,   167,   168,    78,    97,   155,   219,
     157,   221,   158,   159,   589,    79,    56,    57,    58,   455,
      59,   163,   164,   165,   166,   167,   168,   138,   454,   139,
     140,    60,    61,    62,    63,    64,    65,   143,   169,    66,
      67,    68,    69,    70,    71,    72,    97,    73,    74,    75,
     172,   206,   155,   207,   173,   208,   158,   159,   180,    12,
      76,   512,   513,   514,    77,   163,   164,   165,   166,   167,
     168,   182,   184,   201,   202,    78,   186,    56,    57,    58,
     497,    59,   209,   188,    79,   190,   192,   215,   473,   216,
     222,   220,    60,    61,    62,    63,    64,    65,   500,   248,
      66,    67,    68,    69,    70,    71,    72,   249,    73,    74,
      75,   163,   164,   165,   166,   167,   168,   250,   251,   252,
     282,    76,   283,   323,   300,    77,   284,   545,   286,   148,
     149,   150,   151,   152,   301,   154,    78,   155,   156,   157,
     306,   158,   159,   549,   168,    79,   246,   324,   161,   162,
     163,   164,   165,   166,   167,   168,   309,   558,   331,   314,
      56,    57,    58,   329,    59,   317,   318,   319,   320,   321,
     330,   341,   118,   342,   582,    60,    61,    62,    63,    64,
      65,   358,   359,    66,    67,    68,    69,    70,    71,    72,
     343,    73,    74,    75,   346,   344,   590,   349,   351,   352,
     353,   354,   597,   357,    76,   369,   370,   371,    77,   600,
     375,   380,   603,   386,    56,    57,    58,   387,    59,    78,
     384,  -122,   310,   388,   390,   389,   392,   393,    79,    60,
      61,    62,    63,    64,    65,   519,   411,    66,    67,    68,
      69,    70,    71,    72,   397,    73,    74,    75,   412,   416,
     419,   421,   420,   425,   452,   458,   453,    45,    76,   467,
      47,    49,    77,    51,    53,    55,    99,   101,   103,   105,
     520,   107,   109,    78,    56,    57,    58,   461,    59,   471,
     472,   474,    79,   504,   479,   509,   515,   524,   526,    60,
      61,    62,    63,    64,    65,   510,   532,    66,    67,    68,
      69,    70,    71,    72,   531,    73,    74,    75,   525,   532,
     532,   543,   547,   548,   555,   556,   557,   560,    76,   561,
     572,   505,    77,   568,   565,   574,   148,   149,   150,   151,
     152,   153,   154,    78,   155,   156,   157,   577,   158,   159,
     583,   585,    79,   160,   593,   161,   162,   163,   164,   165,
     166,   167,   168,   596,    93,   200,   308,   376,   304,   377,
     211,   383,   315,   305,   148,   149,   150,   151,   152,   153,
     154,   385,   155,   156,   157,   365,   158,   159,   337,   340,
     423,   160,   374,   161,   162,   163,   164,   165,   166,   167,
     168,   460,   338,   396,   476,   559,   381,   567,   551,   415,
     502,   382,   148,   149,   150,   151,   152,   153,   154,   511,
     155,   156,   157,   530,   158,   159,   171,     0,   587,   160,
       0,   161,   162,   163,   164,   165,   166,   167,   168,     0,
       0,     0,     0,     0,   417,     0,     0,     0,     0,   418,
     148,   149,   150,   151,   152,   153,   154,     0,   155,   156,
     157,     0,   158,   159,     0,     0,     0,   160,     0,   161,
     162,   163,   164,   165,   166,   167,   168,     0,     0,     0,
       0,     0,   469,     0,     0,     0,     0,   470,   148,   149,
     150,   151,   152,   153,   154,     0,   155,   156,   157,     0,
     158,   159,     0,     0,     0,   160,     0,   161,   162,   163,
     164,   165,   166,   167,   168,     0,     0,     0,     0,     0,
     516,     0,     0,     0,     0,   517,   148,   149,   150,   151,
     152,   153,   154,     0,   155,   156,   157,     0,   158,   159,
       0,     0,     0,   160,     0,   161,   162,   163,   164,   165,
     166,   167,   168,     0,     0,     0,     0,     0,   563,     0,
       0,     0,     0,   564,   148,   149,   150,   151,   152,   153,
     154,     0,   155,   156,   157,     0,   158,   159,     0,     0,
       0,   160,     0,   161,   162,   163,   164,   165,   166,   167,
     168,     0,     0,     0,     0,     0,   591,     0,     0,     0,
       0,   592,   148,   149,   150,   151,   152,   153,   154,     0,
     155,   156,   157,     0,   158,   159,     0,     0,     0,   160,
       0,   161,   162,   163,   164,   165,   166,   167,   168,     0,
       0,     0,     0,     0,   598,     0,     0,     0,     0,   599,
     148,   149,   150,   151,   152,   153,   154,     0,   155,   156,
     157,     0,   158,   159,     0,     0,     0,   160,     0,   161,
     162,   163,   164,   165,   166,   167,   168,     0,     0,     0,
       0,     0,   601,     0,     0,     0,     0,   602,   148,   149,
     150,   151,   152,   153,   154,     0,   155,   156,   157,     0,
     158,   159,     0,     0,     0,   160,     0,   161,   162,   163,
     164,   165,   166,   167,   168,     0,   148,   149,   150,   151,
     152,   153,   154,   302,   155,   156,   157,     0,   158,   159,
       0,     0,     0,   160,     0,   161,   162,   163,   164,   165,
     166,   167,   168,     0,   148,   149,   150,   151,   152,   153,
     154,   379,   155,   156,   157,     0,   158,   159,     0,     0,
       0,   160,     0,   161,   162,   163,   164,   165,   166,   167,
     168,     0,     0,     0,     0,     0,   224,   148,   149,   150,
     151,   152,   153,   154,     0,   155,   156,   157,     0,   158,
     159,     0,     0,     0,   160,     0,   161,   162,   163,   164,
     165,   166,   167,   168,     0,     0,     0,     0,     0,   294,
     148,   149,   150,   151,   152,   153,   154,     0,   155,   156,
     157,     0,   158,   159,     0,     0,     0,   160,     0,   161,
     162,   163,   164,   165,   166,   167,   168,     0,     0,     0,
       0,     0,   295,   148,   149,   150,   151,   152,   153,   154,
       0,   155,   156,   157,     0,   158,   159,     0,     0,     0,
     160,     0,   161,   162,   163,   164,   165,   166,   167,   168,
       0,     0,     0,     0,     0,   296,   148,   149,   150,   151,
     152,   153,   154,     0,   155,   156,   157,     0,   158,   159,
       0,     0,     0,   160,     0,   161,   162,   163,   164,   165,
     166,   167,   168,     0,     0,     0,     0,     0,   299,   148,
     149,   150,   151,   152,   153,   154,     0,   155,   156,   157,
       0,   158,   159,     0,     0,     0,   160,     0,   161,   162,
     163,   164,   165,   166,   167,   168,     0,     0,     0,     0,
       0,   604,   148,   149,   150,   151,   152,   153,   154,     0,
     155,   156,   157,     0,   158,   159,     0,     0,     0,   160,
     303,   161,   162,   163,   164,   165,   166,   167,   168,   148,
     149,   150,   151,   152,   153,   154,     0,   155,   156,   157,
       0,   158,   159,     0,     0,     0,   160,     0,   161,   162,
     163,   164,   165,   166,   167,   168,   148,   149,   150,   151,
     152,   153,   154,     0,   155,   156,   157,     0,   158,   159,
       0,     0,     0,   160,     0,   161,   162,   163,   164,   165,
     166,   167,   168,   148,   149,   150,   151,   152,     0,     0,
       0,   155,   156,   157,     0,   158,   159,     0,     0,     0,
       0,     0,   161,   162,   163,   164,   165,   166,   167,   168,
     148,   149,   150,   151,     0,     0,     0,     0,   155,   156,
     157,     0,   158,   159,     0,     0,     0,     0,     0,   161,
     162,   163,   164,   165,   166,   167,   168
};

static const yytype_int16 yycheck[] =
{
      10,     2,     0,   185,   111,   187,    29,   189,     1,   191,
     323,   193,   279,   280,   281,   404,     1,    15,     1,     1,
       1,     1,    20,   485,    19,   483,   209,   251,   500,     5,
       6,     7,     8,     9,    10,    11,   425,    29,    30,    29,
      30,    53,     1,   356,   268,   513,   514,     3,     4,     5,
       6,     7,     8,     9,    10,    11,     1,    49,     1,    49,
      72,    55,   410,    49,    87,   410,    76,    77,    78,    79,
       1,     1,   461,   386,    34,    49,    53,   549,     1,   410,
      75,    29,    30,    95,   410,   543,    53,    90,   556,   551,
      49,    51,   560,   561,   483,    72,    86,    91,    96,   447,
      93,    93,   447,    77,    49,    72,    49,     0,    93,    85,
      93,    93,    93,    93,   572,    71,   447,   506,    49,    49,
      80,   447,   132,   133,   134,     9,    49,   137,    85,    85,
     410,    50,   142,   410,    90,    55,    93,   410,   148,   149,
     150,   151,   152,   153,   154,   155,   156,   157,   158,   159,
     160,   161,   162,   163,   164,   165,   166,   167,   168,   169,
     343,   385,    34,    47,   553,    49,    88,   447,   481,   410,
     447,    91,    56,   562,   447,    85,   283,   284,   285,    51,
      12,    13,   410,   410,    29,    30,   499,     3,     4,     5,
       6,     7,     8,     9,    10,    11,    80,    49,   410,   588,
     424,    87,     9,   204,    49,    91,   447,   410,    15,    93,
       9,   410,   525,    20,    21,    22,    23,    24,    25,   447,
     447,    20,    21,    22,    23,    24,    25,    55,    80,    55,
      88,     9,    90,    50,   547,   447,    49,    15,    16,    91,
       9,    93,    49,    56,   447,    49,    15,    25,   447,    56,
      49,   518,    56,   251,    85,   568,    25,    56,    87,    26,
      27,    28,    91,    91,    95,    91,    86,    80,    87,    85,
     268,    49,    91,    80,    90,    86,    80,    96,    56,    88,
      49,    80,    49,    90,    75,    86,    93,    56,   298,    37,
      38,    90,    86,   303,    93,   305,    87,    39,    40,    85,
      91,    87,    80,    51,    52,    96,    86,    49,    86,    85,
      87,    80,    90,    86,    90,    93,   498,    86,    88,    95,
      96,    90,   327,   328,    93,    69,    70,    20,    21,    22,
      85,    24,    87,    87,    78,    79,    80,    81,    82,    83,
     341,   342,    35,    36,    37,    38,    39,    40,   513,   514,
      43,    44,    45,    46,    47,    48,    49,    87,    51,    52,
      53,    91,    88,    65,    66,    67,    96,    69,    70,    87,
      88,    64,   382,    91,    88,    68,    78,    79,    80,    81,
      82,    83,    80,    81,    82,    83,    79,   385,    65,   138,
      67,   140,    69,    70,   576,    88,    20,    21,    22,    92,
      24,    78,    79,    80,    81,    82,    83,    88,   418,    88,
      88,    35,    36,    37,    38,    39,    40,    49,    88,    43,
      44,    45,    46,    47,    48,    49,   424,    51,    52,    53,
      49,   123,    65,   125,    91,   127,    69,    70,    85,    90,
      64,    31,    32,    33,    68,    78,    79,    80,    81,    82,
      83,    86,    86,    49,    91,    79,    86,    20,    21,    22,
     470,    24,    12,    86,    88,    86,    86,    49,    92,    49,
      49,    89,    35,    36,    37,    38,    39,    40,   479,    49,
      43,    44,    45,    46,    47,    48,    49,    49,    51,    52,
      53,    78,    79,    80,    81,    82,    83,    50,    89,    85,
      89,    64,    85,    95,    89,    68,    94,   517,    92,    57,
      58,    59,    60,    61,    89,    63,    79,    65,    66,    67,
      92,    69,    70,   524,    83,    88,    89,    87,    76,    77,
      78,    79,    80,    81,    82,    83,    75,   538,    16,    86,
      20,    21,    22,    85,    24,    20,    21,    22,    23,    24,
      86,    13,    87,    94,   564,    35,    36,    37,    38,    39,
      40,    41,    42,    43,    44,    45,    46,    47,    48,    49,
      94,    51,    52,    53,    87,    49,   577,    85,    49,    51,
      34,    86,   592,    49,    64,    75,    86,    14,    68,   599,
      86,    49,   602,    88,    20,    21,    22,    85,    24,    79,
      51,    87,    96,    92,    86,    92,    75,    17,    88,    35,
      36,    37,    38,    39,    40,    41,    75,    43,    44,    45,
      46,    47,    48,    49,    87,    51,    52,    53,    18,    49,
      85,    91,    89,    49,    86,    91,    86,    49,    64,    75,
      49,    49,    68,    49,    49,    49,    93,    93,    93,    93,
      76,    93,    93,    79,    20,    21,    22,    49,    24,    92,
      85,    91,    88,    49,    75,    93,    87,    13,    49,    35,
      36,    37,    38,    39,    40,    94,    49,    43,    44,    45,
      46,    47,    48,    49,    85,    51,    52,    53,    95,    49,
      49,    49,    88,    76,    87,    31,    93,    32,    64,    33,
      49,    96,    68,    34,    86,    49,    57,    58,    59,    60,
      61,    62,    63,    79,    65,    66,    67,    13,    69,    70,
      85,    89,    88,    74,    76,    76,    77,    78,    79,    80,
      81,    82,    83,    86,    15,   113,   252,   341,    89,   342,
     131,   350,   264,    94,    57,    58,    59,    60,    61,    62,
      63,   356,    65,    66,    67,   324,    69,    70,   283,   285,
     406,    74,   335,    76,    77,    78,    79,    80,    81,    82,
      83,   447,   284,   374,   463,   538,    89,   549,   529,   396,
     480,    94,    57,    58,    59,    60,    61,    62,    63,   492,
      65,    66,    67,   510,    69,    70,    89,    -1,   569,    74,
      -1,    76,    77,    78,    79,    80,    81,    82,    83,    -1,
      -1,    -1,    -1,    -1,    89,    -1,    -1,    -1,    -1,    94,
      57,    58,    59,    60,    61,    62,    63,    -1,    65,    66,
      67,    -1,    69,    70,    -1,    -1,    -1,    74,    -1,    76,
      77,    78,    79,    80,    81,    82,    83,    -1,    -1,    -1,
      -1,    -1,    89,    -1,    -1,    -1,    -1,    94,    57,    58,
      59,    60,    61,    62,    63,    -1,    65,    66,    67,    -1,
      69,    70,    -1,    -1,    -1,    74,    -1,    76,    77,    78,
      79,    80,    81,    82,    83,    -1,    -1,    -1,    -1,    -1,
      89,    -1,    -1,    -1,    -1,    94,    57,    58,    59,    60,
      61,    62,    63,    -1,    65,    66,    67,    -1,    69,    70,
      -1,    -1,    -1,    74,    -1,    76,    77,    78,    79,    80,
      81,    82,    83,    -1,    -1,    -1,    -1,    -1,    89,    -1,
      -1,    -1,    -1,    94,    57,    58,    59,    60,    61,    62,
      63,    -1,    65,    66,    67,    -1,    69,    70,    -1,    -1,
      -1,    74,    -1,    76,    77,    78,    79,    80,    81,    82,
      83,    -1,    -1,    -1,    -1,    -1,    89,    -1,    -1,    -1,
      -1,    94,    57,    58,    59,    60,    61,    62,    63,    -1,
      65,    66,    67,    -1,    69,    70,    -1,    -1,    -1,    74,
      -1,    76,    77,    78,    79,    80,    81,    82,    83,    -1,
      -1,    -1,    -1,    -1,    89,    -1,    -1,    -1,    -1,    94,
      57,    58,    59,    60,    61,    62,    63,    -1,    65,    66,
      67,    -1,    69,    70,    -1,    -1,    -1,    74,    -1,    76,
      77,    78,    79,    80,    81,    82,    83,    -1,    -1,    -1,
      -1,    -1,    89,    -1,    -1,    -1,    -1,    94,    57,    58,
      59,    60,    61,    62,    63,    -1,    65,    66,    67,    -1,
      69,    70,    -1,    -1,    -1,    74,    -1,    76,    77,    78,
      79,    80,    81,    82,    83,    -1,    57,    58,    59,    60,
      61,    62,    63,    92,    65,    66,    67,    -1,    69,    70,
      -1,    -1,    -1,    74,    -1,    76,    77,    78,    79,    80,
      81,    82,    83,    -1,    57,    58,    59,    60,    61,    62,
      63,    92,    65,    66,    67,    -1,    69,    70,    -1,    -1,
      -1,    74,    -1,    76,    77,    78,    79,    80,    81,    82,
      83,    -1,    -1,    -1,    -1,    -1,    89,    57,    58,    59,
      60,    61,    62,    63,    -1,    65,    66,    67,    -1,    69,
      70,    -1,    -1,    -1,    74,    -1,    76,    77,    78,    79,
      80,    81,    82,    83,    -1,    -1,    -1,    -1,    -1,    89,
      57,    58,    59,    60,    61,    62,    63,    -1,    65,    66,
      67,    -1,    69,    70,    -1,    -1,    -1,    74,    -1,    76,
      77,    78,    79,    80,    81,    82,    83,    -1,    -1,    -1,
      -1,    -1,    89,    57,    58,    59,    60,    61,    62,    63,
      -1,    65,    66,    67,    -1,    69,    70,    -1,    -1,    -1,
      74,    -1,    76,    77,    78,    79,    80,    81,    82,    83,
      -1,    -1,    -1,    -1,    -1,    89,    57,    58,    59,    60,
      61,    62,    63,    -1,    65,    66,    67,    -1,    69,    70,
      -1,    -1,    -1,    74,    -1,    76,    77,    78,    79,    80,
      81,    82,    83,    -1,    -1,    -1,    -1,    -1,    89,    57,
      58,    59,    60,    61,    62,    63,    -1,    65,    66,    67,
      -1,    69,    70,    -1,    -1,    -1,    74,    -1,    76,    77,
      78,    79,    80,    81,    82,    83,    -1,    -1,    -1,    -1,
      -1,    89,    57,    58,    59,    60,    61,    62,    63,    -1,
      65,    66,    67,    -1,    69,    70,    -1,    -1,    -1,    74,
      75,    76,    77,    78,    79,    80,    81,    82,    83,    57,
      58,    59,    60,    61,    62,    63,    -1,    65,    66,    67,
      -1,    69,    70,    -1,    -1,    -1,    74,    -1,    76,    77,
      78,    79,    80,    81,    82,    83,    57,    58,    59,    60,
      61,    62,    63,    -1,    65,    66,    67,    -1,    69,    70,
      -1,    -1,    -1,    74,    -1,    76,    77,    78,    79,    80,
      81,    82,    83,    57,    58,    59,    60,    61,    -1,    -1,
      -1,    65,    66,    67,    -1,    69,    70,    -1,    -1,    -1,
      -1,    -1,    76,    77,    78,    79,    80,    81,    82,    83,
      57,    58,    59,    60,    -1,    -1,    -1,    -1,    65,    66,
      67,    -1,    69,    70,    -1,    -1,    -1,    -1,    -1,    76,
      77,    78,    79,    80,    81,    82,    83
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     3,     4,     5,     6,     7,     8,     9,    10,    11,
      71,    85,    90,    98,    99,   100,   101,   102,   104,   107,
     108,   112,   113,   115,   121,   123,   127,   129,   131,   133,
     135,   137,   139,   141,   163,   164,    49,    56,    80,   105,
     106,    49,   103,    90,     1,    49,     1,    49,     1,    49,
       1,    49,     1,    49,     1,    49,    20,    21,    22,    24,
      35,    36,    37,    38,    39,    40,    43,    44,    45,    46,
      47,    48,    49,    51,    52,    53,    64,    68,    79,    88,
     227,   228,   229,   230,   231,   232,   233,   234,   235,   236,
     237,    50,     0,   101,    88,   155,   156,   163,     1,    93,
       1,    93,     1,    93,     1,    93,     1,    93,     1,    93,
      85,    88,    85,    87,    49,    56,    80,    85,    87,    50,
      86,   134,    86,   130,    86,   138,    86,   116,    86,   142,
      86,   124,    88,    88,    88,    87,    87,    88,    88,    88,
      88,    87,    91,    49,   227,   227,   227,   227,    57,    58,
      59,    60,    61,    62,    63,    65,    66,    67,    69,    70,
      74,    76,    77,    78,    79,    80,    81,    82,    83,    88,
      51,   237,    49,    91,    53,    72,   109,   110,   111,   170,
      85,   163,    86,   114,    86,   122,    86,   128,    86,   132,
      86,   136,    86,   140,   165,   166,   167,   168,   169,   170,
     106,    49,    91,    12,    13,   117,   117,   117,   117,    12,
     125,   125,   227,   227,   227,    49,    49,   227,    49,   230,
      89,   230,    49,   227,    89,   227,   227,   227,   227,   227,
     227,   227,   227,   227,   227,   227,   227,   227,   227,   227,
     227,   227,   227,   227,   227,   227,    89,   227,    49,    49,
      50,    89,    85,    53,    72,     9,    15,    25,    49,    56,
      80,    93,   143,   145,   146,   147,   148,   149,   150,   151,
     153,   157,   158,   159,   160,   162,   163,   143,   143,   143,
     143,   143,    89,    85,    94,    95,    92,   103,   118,   103,
     119,   120,   118,   126,    89,    89,    89,    87,    91,    89,
      89,    89,    92,    75,    89,    94,    92,   155,   111,    75,
      96,    34,    51,   161,    86,   147,   155,    20,    21,    22,
      23,    24,   152,    95,    87,    49,    80,    91,    93,    85,
      86,    16,   171,   172,   171,   171,   171,   167,   169,   170,
     168,    13,    94,    94,    49,   227,    87,   227,   227,    85,
     144,    49,    51,    34,    86,    85,    95,    49,    41,    42,
     154,   226,   227,    47,    49,   159,    80,   161,   161,    75,
      86,    14,   180,   181,   180,    86,   119,   120,   118,    92,
      49,    89,    94,   145,    51,   154,    88,    85,    92,    92,
      86,   173,    75,    17,   186,   187,   186,    87,   227,   155,
     226,    26,    27,    28,    49,   174,   175,   176,   178,   179,
     182,    75,    18,   197,   198,   197,    49,    89,    94,    85,
      89,    91,   225,   176,   177,    49,     6,     7,     8,     9,
      10,    11,    85,   107,   113,   115,   121,   123,   127,   129,
     131,   133,   135,   137,   139,   141,   183,   184,   185,   188,
      19,    75,    86,    86,   227,    92,   226,   155,    91,   225,
     185,    49,   189,   190,   191,   193,   194,    75,   200,    89,
      94,    92,    85,    92,    91,   225,   191,    85,    93,    75,
     199,    29,    30,    49,   201,   202,   203,   204,   206,   207,
     208,   209,   210,   211,   212,   214,   224,   227,   192,    77,
     103,   195,   201,   226,    49,    96,   219,   225,   203,    93,
      94,   206,    31,    32,    33,    87,    89,    94,   143,    41,
      76,   226,   196,   224,    13,    95,    49,    55,   225,   205,
     208,    85,    49,   215,   216,   218,   220,   222,   223,   215,
     220,   215,   220,    49,   213,   227,   171,    88,    76,   103,
     226,   202,    75,   219,   225,    87,    31,    93,   103,   195,
      32,    33,   219,    89,    94,    86,   226,   196,    34,    86,
      55,   225,    49,   217,    49,   215,   221,    13,   215,   215,
      55,   225,   227,    85,   238,    89,   226,   238,   219,   143,
     103,    89,    94,    76,    55,   225,    86,   227,    89,    94,
     227,    89,    94,   227,    89
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_uint8 yyr1[] =
{
       0,    97,    98,    98,    99,    99,   100,   100,   101,   101,
     101,   101,   101,   101,   101,   101,   101,   101,   101,   101,
     101,   101,   101,   101,   101,   101,   101,   101,   101,   101,
     101,   102,   103,   103,   104,   105,   105,   106,   106,   106,
     106,   106,   106,   107,   107,   108,   108,   109,   109,   110,
     110,   111,   112,   114,   113,   116,   115,   117,   117,   117,
     117,   118,   119,   119,   120,   122,   121,   124,   123,   125,
     125,   126,   126,   128,   127,   130,   129,   132,   131,   134,
     133,   136,   135,   138,   137,   140,   139,   142,   141,   143,
     144,   143,   145,   145,   146,   146,   147,   147,   148,   148,
     149,   149,   150,   150,   151,   152,   152,   152,   152,   152,
     153,   153,   154,   154,   154,   154,   155,   155,   156,   156,
     157,   157,   158,   158,   159,   159,   159,   159,   160,   160,
     160,   160,   160,   160,   160,   160,   161,   161,   161,   161,
     162,   163,   163,   164,   164,   165,   166,   166,   167,   167,
     168,   168,   169,   169,   170,   170,   170,   170,   171,   171,
     173,   172,   174,   174,   175,   175,   177,   176,   178,   178,
     178,   178,   178,   178,   179,   179,   179,   180,   180,   182,
     181,   183,   183,   184,   184,   185,   185,   185,   185,   185,
     185,   185,   185,   186,   186,   188,   187,   189,   189,   190,
     190,   191,   192,   191,   193,   193,   194,   194,   195,   195,
     195,   196,   196,   197,   197,   199,   198,   200,   198,   201,
     201,   202,   202,   203,   203,   205,   204,   206,   206,   207,
     207,   208,   208,   209,   210,   210,   210,   210,   210,   210,
     211,   211,   212,   212,   213,   213,   213,   214,   214,   214,
     215,   215,   216,   216,   217,   217,   217,   218,   218,   218,
     219,   219,   220,   221,   220,   222,   222,   222,   223,   223,
     224,   225,   226,   227,   227,   227,   227,   227,   227,   227,
     227,   227,   227,   227,   227,   227,   227,   227,   227,   227,
     227,   227,   227,   227,   227,   227,   227,   227,   227,   227,
     227,   227,   227,   227,   227,   227,   227,   227,   227,   227,
     227,   227,   227,   227,   228,   228,   228,   229,   229,   229,
     230,   230,   230,   230,   230,   230,   230,   231,   231,   231,
     231,   231,   232,   232,   232,   233,   234,   234,   235,   235,
     235,   236,   236,   236,   236,   237,   237,   237,   238,   238
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     2,     1,     1,     0,     2,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     1,     3,     3,     1,     2,     2,     2,
       1,     1,     1,     3,     6,     3,     5,     1,     0,     3,
       1,     1,     2,     0,     5,     0,     4,     0,     2,     2,
       4,     1,     3,     1,     1,     0,     5,     0,     4,     2,
       0,     3,     1,     0,     6,     0,     4,     0,     9,     0,
       4,     0,     9,     0,     4,     0,     6,     0,     4,     1,
       0,     4,     1,     0,     2,     1,     1,     1,     1,     1,
       3,     6,     3,     1,     4,     1,     1,     1,     1,     1,
       1,     0,     1,     4,     1,     1,     1,     0,     2,     1,
       3,     3,     3,     1,     1,     4,     4,     1,     1,     3,
       1,     3,     1,     2,     4,     2,     1,     3,     2,     2,
       2,     1,     4,     2,     5,     1,     3,     1,     3,     1,
       3,     1,     1,     0,     2,     2,     1,     1,     1,     0,
       0,     4,     1,     0,     2,     1,     0,     4,     2,     4,
       3,     1,     3,     2,     1,     1,     1,     1,     0,     0,
       4,     1,     0,     2,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     0,     0,     4,     1,     0,     2,
       1,     2,     0,     7,     4,     6,     1,     2,     2,     3,
       6,     1,     0,     1,     0,     0,     5,     0,     4,     1,
       0,     2,     1,     1,     3,     0,     6,     1,     0,     3,
       1,     1,     1,     6,     3,     5,     3,     5,     3,     5,
       3,     1,     2,     1,     2,     3,     3,     2,     3,     3,
       3,     1,     1,     2,     2,     3,     3,     2,     3,     3,
       2,     0,     1,     0,     5,     1,     2,     4,     0,     2,
       2,     3,     1,     1,     3,     4,     3,     3,     3,     3,
       3,     3,     2,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     2,     3,     3,     3,     2,     3,     3,     5,
       4,     4,     4,     3,     4,     6,     8,    10,    12,    14,
      16,    18,    20,    22,     1,     1,     1,     1,     1,     1,
       1,     3,     3,     3,     6,     5,     8,     1,     3,     4,
       4,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     3,     3,     2,     2,     1,     1,     1,     1,     0
};


/* YYDPREC[RULE-NUM] -- Dynamic precedence of rule #RULE-NUM (0 if none).  */
static const yytype_int8 yydprec[] =
{
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0
};

/* YYMERGER[RULE-NUM] -- Index of merging function for rule #RULE-NUM.  */
static const yytype_int8 yymerger[] =
{
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0
};

/* YYIMMEDIATE[RULE-NUM] -- True iff rule #RULE-NUM is not to be deferred, as
   in the case of predicates.  */
static const yybool yyimmediate[] =
{
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0
};

/* YYCONFLP[YYPACT[STATE-NUM]] -- Pointer into YYCONFL of start of
   list of conflicting reductions corresponding to action entry for
   state STATE-NUM in yytable.  0 means no conflicts.  The list in
   yyconfl is terminated by a rule number of 0.  */
static const yytype_int8 yyconflp[] =
{
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     3,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      11,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    13,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     5,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     7,
       9,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     1,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0
};

/* YYCONFL[I] -- lists of conflicting rule numbers, each terminated by
   0, pointed into by YYCONFLP.  */
static const short yyconfl[] =
{
       0,   272,     0,   261,     0,   268,     0,   268,     0,   268,
       0,   261,     0,   261,     0
};


/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)                                \
    do                                                                  \
      if (N)                                                            \
        {                                                               \
          (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;        \
          (Current).first_column = YYRHSLOC (Rhs, 1).first_column;      \
          (Current).last_line    = YYRHSLOC (Rhs, N).last_line;         \
          (Current).last_column  = YYRHSLOC (Rhs, N).last_column;       \
        }                                                               \
      else                                                              \
        {                                                               \
          (Current).first_line   = (Current).last_line   =              \
            YYRHSLOC (Rhs, 0).last_line;                                \
          (Current).first_column = (Current).last_column =              \
            YYRHSLOC (Rhs, 0).last_column;                              \
        }                                                               \
    while (0)
#endif

# define YYRHSLOC(Rhs, K) ((Rhs)[K].yystate.yyloc)


YYSTYPE yylval;
YYLTYPE yylloc;

int yynerrs;
int yychar;

enum { YYENOMEM = -2 };

typedef enum { yyok, yyaccept, yyabort, yyerr, yynomem } YYRESULTTAG;

#define YYCHK(YYE)                              \
  do {                                          \
    YYRESULTTAG yychk_flag = YYE;               \
    if (yychk_flag != yyok)                     \
      return yychk_flag;                        \
  } while (0)

/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   SIZE_MAX < YYMAXDEPTH * sizeof (GLRStackItem)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif

/* Minimum number of free items on the stack allowed after an
   allocation.  This is to allow allocation and initialization
   to be completed by functions that call yyexpandGLRStack before the
   stack is expanded, thus insuring that all necessary pointers get
   properly redirected to new data.  */
#define YYHEADROOM 2

#ifndef YYSTACKEXPANDABLE
#  define YYSTACKEXPANDABLE 1
#endif

#if YYSTACKEXPANDABLE
# define YY_RESERVE_GLRSTACK(Yystack)                   \
  do {                                                  \
    if (Yystack->yyspaceLeft < YYHEADROOM)              \
      yyexpandGLRStack (Yystack);                       \
  } while (0)
#else
# define YY_RESERVE_GLRSTACK(Yystack)                   \
  do {                                                  \
    if (Yystack->yyspaceLeft < YYHEADROOM)              \
      yyMemoryExhausted (Yystack);                      \
  } while (0)
#endif

/** State numbers. */
typedef int yy_state_t;

/** Rule numbers. */
typedef int yyRuleNum;

/** Item references. */
typedef short yyItemNum;

typedef struct yyGLRState yyGLRState;
typedef struct yyGLRStateSet yyGLRStateSet;
typedef struct yySemanticOption yySemanticOption;
typedef union yyGLRStackItem yyGLRStackItem;
typedef struct yyGLRStack yyGLRStack;

struct yyGLRState
{
  /** Type tag: always true.  */
  yybool yyisState;
  /** Type tag for yysemantics.  If true, yyval applies, otherwise
   *  yyfirstVal applies.  */
  yybool yyresolved;
  /** Number of corresponding LALR(1) machine state.  */
  yy_state_t yylrState;
  /** Preceding state in this stack */
  yyGLRState* yypred;
  /** Source position of the last token produced by my symbol */
  YYPTRDIFF_T yyposn;
  union {
    /** First in a chain of alternative reductions producing the
     *  nonterminal corresponding to this state, threaded through
     *  yynext.  */
    yySemanticOption* yyfirstVal;
    /** Semantic value for this state.  */
    YYSTYPE yyval;
  } yysemantics;
  /** Source location for this state.  */
  YYLTYPE yyloc;
};

struct yyGLRStateSet
{
  yyGLRState** yystates;
  /** During nondeterministic operation, yylookaheadNeeds tracks which
   *  stacks have actually needed the current lookahead.  During deterministic
   *  operation, yylookaheadNeeds[0] is not maintained since it would merely
   *  duplicate yychar != YYEMPTY.  */
  yybool* yylookaheadNeeds;
  YYPTRDIFF_T yysize;
  YYPTRDIFF_T yycapacity;
};

struct yySemanticOption
{
  /** Type tag: always false.  */
  yybool yyisState;
  /** Rule number for this reduction */
  yyRuleNum yyrule;
  /** The last RHS state in the list of states to be reduced.  */
  yyGLRState* yystate;
  /** The lookahead for this reduction.  */
  int yyrawchar;
  YYSTYPE yyval;
  YYLTYPE yyloc;
  /** Next sibling in chain of options.  To facilitate merging,
   *  options are chained in decreasing order by address.  */
  yySemanticOption* yynext;
};

/** Type of the items in the GLR stack.  The yyisState field
 *  indicates which item of the union is valid.  */
union yyGLRStackItem {
  yyGLRState yystate;
  yySemanticOption yyoption;
};

struct yyGLRStack {
  int yyerrState;
  /* To compute the location of the error token.  */
  yyGLRStackItem yyerror_range[3];

  YYJMP_BUF yyexception_buffer;
  yyGLRStackItem* yyitems;
  yyGLRStackItem* yynextFree;
  YYPTRDIFF_T yyspaceLeft;
  yyGLRState* yysplitPoint;
  yyGLRState* yylastDeleted;
  yyGLRStateSet yytops;
};

#if YYSTACKEXPANDABLE
static void yyexpandGLRStack (yyGLRStack* yystackp);
#endif

_Noreturn static void
yyFail (yyGLRStack* yystackp, omnetpp::nedxml::ParseContext *np, const char* yymsg)
{
  if (yymsg != YY_NULLPTR)
    yyerror (np, yymsg);
  YYLONGJMP (yystackp->yyexception_buffer, 1);
}

_Noreturn static void
yyMemoryExhausted (yyGLRStack* yystackp)
{
  YYLONGJMP (yystackp->yyexception_buffer, 2);
}

/** Accessing symbol of state YYSTATE.  */
static inline yysymbol_kind_t
yy_accessing_symbol (yy_state_t yystate)
{
  return YY_CAST (yysymbol_kind_t, yystos[yystate]);
}

#if YYDEBUG || 0
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "\"invalid token\"", "IMPORT", "PACKAGE",
  "PROPERTY", "MODULE", "SIMPLE", "NETWORK", "CHANNEL", "MODULEINTERFACE",
  "CHANNELINTERFACE", "EXTENDS", "LIKE", "TYPES", "PARAMETERS", "GATES",
  "SUBMODULES", "CONNECTIONS", "ALLOWUNCONNECTED", "DOUBLETYPE", "INTTYPE",
  "STRINGTYPE", "BOOLTYPE", "XMLTYPE", "VOLATILE", "INPUT_", "OUTPUT_",
  "INOUT_", "IF", "FOR", "RIGHTARROW", "LEFTARROW", "DBLARROW", "TO",
  "TRUE_", "FALSE_", "NAN_", "INF_", "THIS_", "PARENT", "DEFAULT", "ASK",
  "CONST_", "SIZEOF", "INDEX_", "EXISTS", "TYPENAME", "XMLDOC", "NAME",
  "PROPNAME", "INTCONSTANT", "REALCONSTANT", "STRINGCONSTANT",
  "CHARCONSTANT", "PLUSPLUS", "DOUBLEASTERISK", "EQ", "NE", "GE", "LE",
  "AND", "OR", "XOR", "NOT", "BIN_AND", "BIN_OR", "BIN_XOR", "BIN_COMPL",
  "SHIFT_LEFT", "SHIFT_RIGHT", "EXPRESSION_SELECTOR", "CHAR",
  "INVALID_CHAR", "'?'", "':'", "'>'", "'<'", "'+'", "'-'", "'*'", "'/'",
  "'%'", "'^'", "UMIN", "';'", "'}'", "'.'", "'('", "')'", "'@'", "'['",
  "']'", "'{'", "','", "'='", "'$'", "$accept", "startsymbol", "nedfile",
  "definitions", "definition", "packagedeclaration", "dottedname",
  "import", "importspec", "importname", "propertydecl",
  "propertydecl_header", "opt_propertydecl_keys", "propertydecl_keys",
  "propertydecl_key", "fileproperty", "channeldefinition", "$@1",
  "channelheader", "$@2", "opt_inheritance", "extendsname", "likenames",
  "likename", "channelinterfacedefinition", "$@3",
  "channelinterfaceheader", "$@4", "opt_interfaceinheritance",
  "extendsnames", "simplemoduledefinition", "$@5", "simplemoduleheader",
  "$@6", "compoundmoduledefinition", "$@7", "compoundmoduleheader", "$@8",
  "networkdefinition", "$@9", "networkheader", "$@10",
  "moduleinterfacedefinition", "$@11", "moduleinterfaceheader", "$@12",
  "opt_paramblock", "$@13", "opt_params", "params", "paramsitem", "param",
  "param_typenamevalue", "param_typename", "pattern_value", "paramtype",
  "opt_volatile", "paramvalue", "opt_inline_properties",
  "inline_properties", "pattern", "pattern2", "pattern_elem",
  "pattern_name", "pattern_index", "property", "property_namevalue",
  "property_name", "opt_property_keys", "property_keys", "property_key",
  "property_values", "property_value", "property_literal", "opt_gateblock",
  "gateblock", "$@14", "opt_gates", "gates", "gate", "$@15",
  "gate_typenamesize", "gatetype", "opt_typeblock", "typeblock", "$@16",
  "opt_localtypes", "localtypes", "localtype", "opt_submodblock",
  "submodblock", "$@17", "opt_submodules", "submodules", "submodule",
  "$@18", "submoduleheader", "submodulename", "likeexpr", "opt_condition",
  "opt_connblock", "connblock", "$@19", "$@20", "opt_connections",
  "connections", "connectionsitem", "connectiongroup", "$@21",
  "opt_loops_and_conditions", "loops_and_conditions", "loop_or_condition",
  "loop", "connection", "leftgatespec", "leftmod", "leftgate",
  "parentleftgate", "rightgatespec", "rightmod", "rightgate",
  "parentrightgate", "opt_subgate", "channelspec", "$@22",
  "channelspec_header", "opt_channelname", "condition", "vector",
  "expression", "expr", "simple_expr", "funcname", "identifier",
  "operator", "literal", "stringliteral", "boolliteral", "numliteral",
  "quantity", "realconstant_ext", "opt_semicolon", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

/** Left-hand-side symbol for rule #YYRULE.  */
static inline yysymbol_kind_t
yylhsNonterm (yyRuleNum yyrule)
{
  return YY_CAST (yysymbol_kind_t, yyr1[yyrule]);
}

#if YYDEBUG

# ifndef YYFPRINTF
#  define YYFPRINTF fprintf
# endif

# define YY_FPRINTF                             \
  YY_IGNORE_USELESS_CAST_BEGIN YY_FPRINTF_

# define YY_FPRINTF_(Args)                      \
  do {                                          \
    YYFPRINTF Args;                             \
    YY_IGNORE_USELESS_CAST_END                  \
  } while (0)

# define YY_DPRINTF                             \
  YY_IGNORE_USELESS_CAST_BEGIN YY_DPRINTF_

# define YY_DPRINTF_(Args)                      \
  do {                                          \
    if (yydebug)                                \
      YYFPRINTF Args;                           \
    YY_IGNORE_USELESS_CAST_END                  \
  } while (0)


/* YYLOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

# ifndef YYLOCATION_PRINT

#  if defined YY_LOCATION_PRINT

   /* Temporary convenience wrapper in case some people defined the
      undocumented and private YY_LOCATION_PRINT macros.  */
#   define YYLOCATION_PRINT(File, Loc)  YY_LOCATION_PRINT(File, *(Loc))

#  elif defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL

/* Print *YYLOCP on YYO.  Private, do not rely on its existence. */

YY_ATTRIBUTE_UNUSED
static int
yy_location_print_ (FILE *yyo, YYLTYPE const * const yylocp)
{
  int res = 0;
  int end_col = 0 != yylocp->last_column ? yylocp->last_column - 1 : 0;
  if (0 <= yylocp->first_line)
    {
      res += YYFPRINTF (yyo, "%d", yylocp->first_line);
      if (0 <= yylocp->first_column)
        res += YYFPRINTF (yyo, ".%d", yylocp->first_column);
    }
  if (0 <= yylocp->last_line)
    {
      if (yylocp->first_line < yylocp->last_line)
        {
          res += YYFPRINTF (yyo, "-%d", yylocp->last_line);
          if (0 <= end_col)
            res += YYFPRINTF (yyo, ".%d", end_col);
        }
      else if (0 <= end_col && yylocp->first_column < end_col)
        res += YYFPRINTF (yyo, "-%d", end_col);
    }
  return res;
}

#   define YYLOCATION_PRINT  yy_location_print_

    /* Temporary convenience wrapper in case some people defined the
       undocumented and private YY_LOCATION_PRINT macros.  */
#   define YY_LOCATION_PRINT(File, Loc)  YYLOCATION_PRINT(File, &(Loc))

#  else

#   define YYLOCATION_PRINT(File, Loc) ((void) 0)
    /* Temporary convenience wrapper in case some people defined the
       undocumented and private YY_LOCATION_PRINT macros.  */
#   define YY_LOCATION_PRINT  YYLOCATION_PRINT

#  endif
# endif /* !defined YYLOCATION_PRINT */



/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp, omnetpp::nedxml::ParseContext *np)
{
  FILE *yyoutput = yyo;
  YY_USE (yyoutput);
  YY_USE (yylocationp);
  YY_USE (np);
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
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp, omnetpp::nedxml::ParseContext *np)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  YYLOCATION_PRINT (yyo, yylocationp);
  YYFPRINTF (yyo, ": ");
  yy_symbol_value_print (yyo, yykind, yyvaluep, yylocationp, np);
  YYFPRINTF (yyo, ")");
}

# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                  \
  do {                                                                  \
    if (yydebug)                                                        \
      {                                                                 \
        YY_FPRINTF ((stderr, "%s ", Title));                            \
        yy_symbol_print (stderr, Kind, Value, Location, np);        \
        YY_FPRINTF ((stderr, "\n"));                                    \
      }                                                                 \
  } while (0)

static inline void
yy_reduce_print (yybool yynormal, yyGLRStackItem* yyvsp, YYPTRDIFF_T yyk,
                 yyRuleNum yyrule, omnetpp::nedxml::ParseContext *np);

# define YY_REDUCE_PRINT(Args)          \
  do {                                  \
    if (yydebug)                        \
      yy_reduce_print Args;             \
  } while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;

static void yypstack (yyGLRStack* yystackp, YYPTRDIFF_T yyk)
  YY_ATTRIBUTE_UNUSED;
static void yypdumpstack (yyGLRStack* yystackp)
  YY_ATTRIBUTE_UNUSED;

#else /* !YYDEBUG */

# define YY_DPRINTF(Args) do {} while (yyfalse)
# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)
# define YY_REDUCE_PRINT(Args)

#endif /* !YYDEBUG */



/** Fill in YYVSP[YYLOW1 .. YYLOW0-1] from the chain of states starting
 *  at YYVSP[YYLOW0].yystate.yypred.  Leaves YYVSP[YYLOW1].yystate.yypred
 *  containing the pointer to the next state in the chain.  */
static void yyfillin (yyGLRStackItem *, int, int) YY_ATTRIBUTE_UNUSED;
static void
yyfillin (yyGLRStackItem *yyvsp, int yylow0, int yylow1)
{
  int i;
  yyGLRState *s = yyvsp[yylow0].yystate.yypred;
  for (i = yylow0-1; i >= yylow1; i -= 1)
    {
#if YYDEBUG
      yyvsp[i].yystate.yylrState = s->yylrState;
#endif
      yyvsp[i].yystate.yyresolved = s->yyresolved;
      if (s->yyresolved)
        yyvsp[i].yystate.yysemantics.yyval = s->yysemantics.yyval;
      else
        /* The effect of using yyval or yyloc (in an immediate rule) is
         * undefined.  */
        yyvsp[i].yystate.yysemantics.yyfirstVal = YY_NULLPTR;
      yyvsp[i].yystate.yyloc = s->yyloc;
      s = yyvsp[i].yystate.yypred = s->yypred;
    }
}


/** If yychar is empty, fetch the next token.  */
static inline yysymbol_kind_t
yygetToken (int *yycharp, omnetpp::nedxml::ParseContext *np)
{
  yysymbol_kind_t yytoken;
  YY_USE (np);
  if (*yycharp == YYEMPTY)
    {
      YY_DPRINTF ((stderr, "Reading a token\n"));
      *yycharp = yylex ();
    }
  if (*yycharp <= YYEOF)
    {
      *yycharp = YYEOF;
      yytoken = YYSYMBOL_YYEOF;
      YY_DPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yytoken = YYTRANSLATE (*yycharp);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }
  return yytoken;
}

/* Do nothing if YYNORMAL or if *YYLOW <= YYLOW1.  Otherwise, fill in
 * YYVSP[YYLOW1 .. *YYLOW-1] as in yyfillin and set *YYLOW = YYLOW1.
 * For convenience, always return YYLOW1.  */
static inline int yyfill (yyGLRStackItem *, int *, int, yybool)
     YY_ATTRIBUTE_UNUSED;
static inline int
yyfill (yyGLRStackItem *yyvsp, int *yylow, int yylow1, yybool yynormal)
{
  if (!yynormal && yylow1 < *yylow)
    {
      yyfillin (yyvsp, *yylow, yylow1);
      *yylow = yylow1;
    }
  return yylow1;
}

/** Perform user action for rule number YYN, with RHS length YYRHSLEN,
 *  and top stack item YYVSP.  YYLVALP points to place to put semantic
 *  value ($$), and yylocp points to place for location information
 *  (@$).  Returns yyok for normal return, yyaccept for YYACCEPT,
 *  yyerr for YYERROR, yyabort for YYABORT, yynomem for YYNOMEM.  */
static YYRESULTTAG
yyuserAction (yyRuleNum yyrule, int yyrhslen, yyGLRStackItem* yyvsp,
              yyGLRStack* yystackp, YYPTRDIFF_T yyk,
              YYSTYPE* yyvalp, YYLTYPE *yylocp, omnetpp::nedxml::ParseContext *np)
{
  const yybool yynormal YY_ATTRIBUTE_UNUSED = yystackp->yysplitPoint == YY_NULLPTR;
  int yylow = 1;
  YY_USE (yyvalp);
  YY_USE (yylocp);
  YY_USE (np);
  YY_USE (yyk);
  YY_USE (yyrhslen);
# undef yyerrok
# define yyerrok (yystackp->yyerrState = 0)
# undef YYACCEPT
# define YYACCEPT return yyaccept
# undef YYABORT
# define YYABORT return yyabort
# undef YYNOMEM
# define YYNOMEM return yynomem
# undef YYERROR
# define YYERROR return yyerrok, yyerr
# undef YYRECOVERING
# define YYRECOVERING() (yystackp->yyerrState != 0)
# undef yyclearin
# define yyclearin (yychar = YYEMPTY)
# undef YYFILL
# define YYFILL(N) yyfill (yyvsp, &yylow, (N), yynormal)
# undef YYBACKUP
# define YYBACKUP(Token, Value)                                              \
  return yyerror (np, YY_("syntax error: cannot back up")),     \
         yyerrok, yyerr

  if (yyrhslen == 0)
    *yyvalp = yyval_default;
  else
    *yyvalp = yyvsp[YYFILL (1-yyrhslen)].yystate.yysemantics.yyval;
  /* Default location. */
  YYLLOC_DEFAULT ((*yylocp), (yyvsp - yyrhslen), yyrhslen);
  yystackp->yyerror_range[1].yystate.yyloc = *yylocp;
  /* If yyk == -1, we are running a deferred action on a temporary
     stack.  In that case, YY_REDUCE_PRINT must not play with YYFILL,
     so pretend the stack is "normal". */
  YY_REDUCE_PRINT ((yynormal || yyk == -1, yyvsp, yyk, yyrule, np));
  switch (yyrule)
    {
  case 2: /* startsymbol: EXPRESSION_SELECTOR expr  */
#line 208 "ned2.y"
                { ps.nedfile->appendChild(YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yyval); }
#line 2292 "ned2.tab.cc"
    break;

  case 19: /* definition: channelinterfaceheader error '}'  */
#line 239 "ned2.y"
                { storePos(np,  ps.component, (*yylocp)); restoreGlobalParserState(); }
#line 2298 "ned2.tab.cc"
    break;

  case 20: /* definition: CHANNELINTERFACE error '}'  */
#line 241 "ned2.y"
                { restoreGlobalParserState(); }
#line 2304 "ned2.tab.cc"
    break;

  case 21: /* definition: simplemoduleheader error '}'  */
#line 243 "ned2.y"
                { storePos(np,  ps.component, (*yylocp)); restoreGlobalParserState(); }
#line 2310 "ned2.tab.cc"
    break;

  case 22: /* definition: SIMPLE error '}'  */
#line 245 "ned2.y"
                { restoreGlobalParserState(); }
#line 2316 "ned2.tab.cc"
    break;

  case 23: /* definition: compoundmoduleheader error '}'  */
#line 247 "ned2.y"
                { storePos(np,  ps.component, (*yylocp)); restoreGlobalParserState(); }
#line 2322 "ned2.tab.cc"
    break;

  case 24: /* definition: MODULE error '}'  */
#line 249 "ned2.y"
                { restoreGlobalParserState(); }
#line 2328 "ned2.tab.cc"
    break;

  case 25: /* definition: networkheader error '}'  */
#line 251 "ned2.y"
                { storePos(np,  ps.component, (*yylocp)); restoreGlobalParserState(); }
#line 2334 "ned2.tab.cc"
    break;

  case 26: /* definition: NETWORK error '}'  */
#line 253 "ned2.y"
                { restoreGlobalParserState(); }
#line 2340 "ned2.tab.cc"
    break;

  case 27: /* definition: moduleinterfaceheader error '}'  */
#line 255 "ned2.y"
                { storePos(np,  ps.component, (*yylocp)); restoreGlobalParserState(); }
#line 2346 "ned2.tab.cc"
    break;

  case 28: /* definition: MODULEINTERFACE error '}'  */
#line 257 "ned2.y"
                { restoreGlobalParserState(); }
#line 2352 "ned2.tab.cc"
    break;

  case 29: /* definition: channelheader error '}'  */
#line 259 "ned2.y"
                { storePos(np,  ps.component, (*yylocp)); restoreGlobalParserState(); }
#line 2358 "ned2.tab.cc"
    break;

  case 30: /* definition: CHANNEL error '}'  */
#line 261 "ned2.y"
                { restoreGlobalParserState(); }
#line 2364 "ned2.tab.cc"
    break;

  case 31: /* packagedeclaration: PACKAGE dottedname ';'  */
#line 266 "ned2.y"
                {
                  ps.package = (PackageElement *)createNedElementWithTag(np, NED_PACKAGE, ps.nedfile);
                  ps.package->setName(removeSpaces(np, (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yyloc)).c_str());
                  storePos(np,  ps.package,(*yylocp));
                  storeBannerAndRightComments(np, ps.package,(*yylocp));
                }
#line 2375 "ned2.tab.cc"
    break;

  case 34: /* import: IMPORT importspec ';'  */
#line 284 "ned2.y"
                {
                  ps.import = (ImportElement *)createNedElementWithTag(np, NED_IMPORT, ps.nedfile);
                  ps.import->setImportSpec(removeSpaces(np, (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yyloc)).c_str());
                  storePos(np,  ps.import,(*yylocp));
                  storeBannerAndRightComments(np, ps.import,(*yylocp));
                }
#line 2386 "ned2.tab.cc"
    break;

  case 43: /* propertydecl: propertydecl_header opt_inline_properties ';'  */
#line 311 "ned2.y"
                {
                    storePos(np,  ps.propertydecl, (*yylocp));
                    storeBannerAndRightComments(np, ps.propertydecl,(*yylocp));
                }
#line 2395 "ned2.tab.cc"
    break;

  case 44: /* propertydecl: propertydecl_header '(' opt_propertydecl_keys ')' opt_inline_properties ';'  */
#line 316 "ned2.y"
                {
                    storePos(np,  ps.propertydecl, (*yylocp));
                    storeBannerAndRightComments(np, ps.propertydecl,(*yylocp));
                }
#line 2404 "ned2.tab.cc"
    break;

  case 45: /* propertydecl_header: PROPERTY '@' PROPNAME  */
#line 324 "ned2.y"
                {
                  ps.propertydecl = (PropertyDeclElement *)createNedElementWithTag(np, NED_PROPERTY_DECL, ps.nedfile);
                  ps.propertydecl->setName(toString(np, (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yyloc)));
                }
#line 2413 "ned2.tab.cc"
    break;

  case 46: /* propertydecl_header: PROPERTY '@' PROPNAME '[' ']'  */
#line 329 "ned2.y"
                {
                  ps.propertydecl = (PropertyDeclElement *)createNedElementWithTag(np, NED_PROPERTY_DECL, ps.nedfile);
                  ps.propertydecl->setName(toString(np, (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-2)].yystate.yyloc)));
                  ps.propertydecl->setIsArray(true);
                }
#line 2423 "ned2.tab.cc"
    break;

  case 51: /* propertydecl_key: property_literal  */
#line 348 "ned2.y"
                {
                  ps.propkey = (PropertyKeyElement *)createNedElementWithTag(np, NED_PROPERTY_KEY, ps.propertydecl);
                  ps.propkey->setName(opp_trim(toString(np, (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yyloc))).c_str());
                  storePos(np,  ps.propkey, (*yylocp));
                }
#line 2433 "ned2.tab.cc"
    break;

  case 52: /* fileproperty: property_namevalue ';'  */
#line 360 "ned2.y"
                {
                  storePos(np,  ps.property, (*yylocp));
                  storeBannerAndRightComments(np, ps.property,(*yylocp));
                }
#line 2442 "ned2.tab.cc"
    break;

  case 53: /* $@1: %empty  */
#line 371 "ned2.y"
                {
                  ps.typescope.push(ps.component);
                  ps.blockscope.push(ps.component);
                  ps.parameters = (ParametersElement *)createNedElementWithTag(np, NED_PARAMETERS, ps.component);
                  ps.parameters->setIsImplicit(true);
                  ps.propertyscope.push(ps.parameters);
                }
#line 2454 "ned2.tab.cc"
    break;

  case 54: /* channeldefinition: channelheader '{' $@1 opt_paramblock '}'  */
#line 380 "ned2.y"
                {
                  ps.propertyscope.pop();
                  ps.blockscope.pop();
                  ps.component = ps.typescope.top();
                  ps.typescope.pop();
                  if (np->getStoreSourceFlag())
                      storeComponentSourceCode(np, ps.component, (*yylocp));
                  storePos(np,  ps.component, (*yylocp));
                  storeTrailingComment(np, ps.component,(*yylocp));
                }
#line 2469 "ned2.tab.cc"
    break;

  case 55: /* $@2: %empty  */
#line 394 "ned2.y"
                {
                  ps.component = (ChannelElement *)createNedElementWithTag(np, NED_CHANNEL, ps.inTypes ? (ASTNode *)ps.types : (ASTNode *)ps.nedfile);
                  ((ChannelElement *)ps.component)->setName(toString(np, (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yyloc)));
                }
#line 2478 "ned2.tab.cc"
    break;

  case 56: /* channelheader: CHANNEL NAME $@2 opt_inheritance  */
#line 399 "ned2.y"
                { storeBannerAndRightComments(np, ps.component,(*yylocp)); }
#line 2484 "ned2.tab.cc"
    break;

  case 61: /* extendsname: dottedname  */
#line 411 "ned2.y"
                {
                  ps.extends = (ExtendsElement *)createNedElementWithTag(np, NED_EXTENDS, ps.component);
                  ps.extends->setName(removeSpaces(np, (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yyloc)).c_str());
                  storePos(np,  ps.extends, (*yylocp));
                }
#line 2494 "ned2.tab.cc"
    break;

  case 64: /* likename: dottedname  */
#line 425 "ned2.y"
                {
                  ps.interfacename = (InterfaceNameElement *)createNedElementWithTag(np, NED_INTERFACE_NAME, ps.component);
                  ps.interfacename->setName(removeSpaces(np, (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yyloc)).c_str());
                  storePos(np, ps.interfacename, (*yylocp));
                }
#line 2504 "ned2.tab.cc"
    break;

  case 65: /* $@3: %empty  */
#line 437 "ned2.y"
                {
                  ps.typescope.push(ps.component);
                  ps.blockscope.push(ps.component);
                  ps.parameters = (ParametersElement *)createNedElementWithTag(np, NED_PARAMETERS, ps.component);
                  ps.parameters->setIsImplicit(true);
                  ps.propertyscope.push(ps.parameters);
                }
#line 2516 "ned2.tab.cc"
    break;

  case 66: /* channelinterfacedefinition: channelinterfaceheader '{' $@3 opt_paramblock '}'  */
#line 446 "ned2.y"
                {
                  ps.propertyscope.pop();
                  ps.blockscope.pop();
                  ps.component = ps.typescope.top();
                  ps.typescope.pop();
                  if (np->getStoreSourceFlag())
                      storeComponentSourceCode(np, ps.component, (*yylocp));
                  storePos(np, ps.component, (*yylocp));
                  storeTrailingComment(np, ps.component,(*yylocp));
                }
#line 2531 "ned2.tab.cc"
    break;

  case 67: /* $@4: %empty  */
#line 460 "ned2.y"
                {
                  ps.component = (ChannelInterfaceElement *)createNedElementWithTag(np, NED_CHANNEL_INTERFACE, ps.inTypes ? (ASTNode *)ps.types : (ASTNode *)ps.nedfile);
                  ((ChannelInterfaceElement *)ps.component)->setName(toString(np, (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yyloc)));
                }
#line 2540 "ned2.tab.cc"
    break;

  case 68: /* channelinterfaceheader: CHANNELINTERFACE NAME $@4 opt_interfaceinheritance  */
#line 465 "ned2.y"
                { storeBannerAndRightComments(np, ps.component,(*yylocp)); }
#line 2546 "ned2.tab.cc"
    break;

  case 73: /* $@5: %empty  */
#line 483 "ned2.y"
                {
                  ps.typescope.push(ps.component);
                  ps.blockscope.push(ps.component);
                  ps.parameters = (ParametersElement *)createNedElementWithTag(np, NED_PARAMETERS, ps.component);
                  ps.parameters->setIsImplicit(true);
                  ps.propertyscope.push(ps.parameters);
                }
#line 2558 "ned2.tab.cc"
    break;

  case 74: /* simplemoduledefinition: simplemoduleheader '{' $@5 opt_paramblock opt_gateblock '}'  */
#line 493 "ned2.y"
                {
                  ps.propertyscope.pop();
                  ps.blockscope.pop();
                  ps.component = ps.typescope.top();
                  ps.typescope.pop();
                  if (np->getStoreSourceFlag())
                      storeComponentSourceCode(np, ps.component, (*yylocp));
                  storePos(np, ps.component, (*yylocp));
                  storeTrailingComment(np, ps.component,(*yylocp));
                }
#line 2573 "ned2.tab.cc"
    break;

  case 75: /* $@6: %empty  */
#line 507 "ned2.y"
                {
                  ps.component = (SimpleModuleElement *)createNedElementWithTag(np, NED_SIMPLE_MODULE, ps.inTypes ? (ASTNode *)ps.types : (ASTNode *)ps.nedfile );
                  ((SimpleModuleElement *)ps.component)->setName(toString(np, (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yyloc)));
                }
#line 2582 "ned2.tab.cc"
    break;

  case 76: /* simplemoduleheader: SIMPLE NAME $@6 opt_inheritance  */
#line 512 "ned2.y"
                { storeBannerAndRightComments(np, ps.component,(*yylocp)); }
#line 2588 "ned2.tab.cc"
    break;

  case 77: /* $@7: %empty  */
#line 520 "ned2.y"
                {
                  ps.typescope.push(ps.component);
                  ps.blockscope.push(ps.component);
                  ps.parameters = (ParametersElement *)createNedElementWithTag(np, NED_PARAMETERS, ps.component);
                  ps.parameters->setIsImplicit(true);
                  ps.propertyscope.push(ps.parameters);
                }
#line 2600 "ned2.tab.cc"
    break;

  case 78: /* compoundmoduledefinition: compoundmoduleheader '{' $@7 opt_paramblock opt_gateblock opt_typeblock opt_submodblock opt_connblock '}'  */
#line 533 "ned2.y"
                {
                  ps.propertyscope.pop();
                  ps.blockscope.pop();
                  ps.component = ps.typescope.top();
                  ps.typescope.pop();
                  if (np->getStoreSourceFlag())
                      storeComponentSourceCode(np, ps.component, (*yylocp));
                  storePos(np, ps.component, (*yylocp));
                  storeTrailingComment(np, ps.component,(*yylocp));
                }
#line 2615 "ned2.tab.cc"
    break;

  case 79: /* $@8: %empty  */
#line 547 "ned2.y"
                {
                  ps.component = (CompoundModuleElement *)createNedElementWithTag(np, NED_COMPOUND_MODULE, ps.inTypes ? (ASTNode *)ps.types : (ASTNode *)ps.nedfile );
                  ((CompoundModuleElement *)ps.component)->setName(toString(np, (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yyloc)));
                }
#line 2624 "ned2.tab.cc"
    break;

  case 80: /* compoundmoduleheader: MODULE NAME $@8 opt_inheritance  */
#line 552 "ned2.y"
                { storeBannerAndRightComments(np, ps.component,(*yylocp)); }
#line 2630 "ned2.tab.cc"
    break;

  case 81: /* $@9: %empty  */
#line 560 "ned2.y"
                {
                  ps.typescope.push(ps.component);
                  ps.blockscope.push(ps.component);
                  ps.parameters = (ParametersElement *)ps.component->getFirstChildWithTag(NED_PARAMETERS); // networkheader already created it for @isNetwork
                  ps.parameters->setIsImplicit(true);
                  ps.propertyscope.push(ps.parameters);
                }
#line 2642 "ned2.tab.cc"
    break;

  case 82: /* networkdefinition: networkheader '{' $@9 opt_paramblock opt_gateblock opt_typeblock opt_submodblock opt_connblock '}'  */
#line 573 "ned2.y"
                {
                  ps.propertyscope.pop();
                  ps.blockscope.pop();
                  ps.component = ps.typescope.top();
                  ps.typescope.pop();
                  if (np->getStoreSourceFlag())
                      storeComponentSourceCode(np, ps.component, (*yylocp));
                  storePos(np, ps.component, (*yylocp));
                  storeTrailingComment(np, ps.component,(*yylocp));
                }
#line 2657 "ned2.tab.cc"
    break;

  case 83: /* $@10: %empty  */
#line 587 "ned2.y"
                {
                  ps.component = (CompoundModuleElement *)createNedElementWithTag(np, NED_COMPOUND_MODULE, ps.inTypes ? (ASTNode *)ps.types : (ASTNode *)ps.nedfile );
                  ((CompoundModuleElement *)ps.component)->setName(toString(np, (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yyloc)));
                }
#line 2666 "ned2.tab.cc"
    break;

  case 84: /* networkheader: NETWORK NAME $@10 opt_inheritance  */
#line 592 "ned2.y"
                {
                  setIsNetworkProperty(np, ps.component);
                  storeBannerAndRightComments(np, ps.component,(*yylocp));
                }
#line 2675 "ned2.tab.cc"
    break;

  case 85: /* $@11: %empty  */
#line 603 "ned2.y"
                {
                  ps.typescope.push(ps.component);
                  ps.blockscope.push(ps.component);
                  ps.parameters = (ParametersElement *)createNedElementWithTag(np, NED_PARAMETERS, ps.component);
                  ps.parameters->setIsImplicit(true);
                  ps.propertyscope.push(ps.parameters);
                }
#line 2687 "ned2.tab.cc"
    break;

  case 86: /* moduleinterfacedefinition: moduleinterfaceheader '{' $@11 opt_paramblock opt_gateblock '}'  */
#line 613 "ned2.y"
                {
                  ps.propertyscope.pop();
                  ps.blockscope.pop();
                  ps.component = ps.typescope.top();
                  ps.typescope.pop();
                  if (np->getStoreSourceFlag())
                      storeComponentSourceCode(np, ps.component, (*yylocp));
                  storePos(np, ps.component, (*yylocp));
                  storeTrailingComment(np, ps.component,(*yylocp));
                }
#line 2702 "ned2.tab.cc"
    break;

  case 87: /* $@12: %empty  */
#line 627 "ned2.y"
                {
                  ps.component = (ModuleInterfaceElement *)createNedElementWithTag(np, NED_MODULE_INTERFACE, ps.inTypes ? (ASTNode *)ps.types : (ASTNode *)ps.nedfile);
                  ((ModuleInterfaceElement *)ps.component)->setName(toString(np, (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yyloc)));
                }
#line 2711 "ned2.tab.cc"
    break;

  case 88: /* moduleinterfaceheader: MODULEINTERFACE NAME $@12 opt_interfaceinheritance  */
#line 632 "ned2.y"
                { storeBannerAndRightComments(np, ps.component,(*yylocp)); }
#line 2717 "ned2.tab.cc"
    break;

  case 89: /* opt_paramblock: opt_params  */
#line 640 "ned2.y"
                {
                  storePos(np, ps.parameters, (*yylocp));
                  if (!ps.parameters->getFirstChild()) { // delete "parameters" element if empty
                      ps.parameters->getParent()->removeChild(ps.parameters);
                      delete ps.parameters;
                  }
                }
#line 2729 "ned2.tab.cc"
    break;

  case 90: /* $@13: %empty  */
#line 648 "ned2.y"
                {
                  ps.parameters->setIsImplicit(false);
                  storeBannerAndRightComments(np, ps.parameters,(YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yyloc),(YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yyloc));
                }
#line 2738 "ned2.tab.cc"
    break;

  case 91: /* opt_paramblock: PARAMETERS ':' $@13 opt_params  */
#line 653 "ned2.y"
                { storePos(np, ps.parameters, (*yylocp)); }
#line 2744 "ned2.tab.cc"
    break;

  case 100: /* param_typenamevalue: param_typename opt_inline_properties ';'  */
#line 681 "ned2.y"
                {
                  ps.propertyscope.pop();
                  storePos(np, ps.param, (*yylocp));
                  storeBannerAndRightComments(np, ps.param,(*yylocp));
                }
#line 2754 "ned2.tab.cc"
    break;

  case 101: /* param_typenamevalue: param_typename opt_inline_properties '=' paramvalue opt_inline_properties ';'  */
#line 687 "ned2.y"
                {
                  ps.propertyscope.pop();
                  if (!isEmpty(ps.exprPos))  // note: $4 cannot be checked, as it's always nullptr when expression parsing is off
                      addExpression(np, ps.param, "value",ps.exprPos,YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-2)].yystate.yysemantics.yyval);
                  else {
                      // Note: "=default" is currently not accepted in NED files, because
                      // it would be complicated to support in the Inifile Editor.
                      if (ps.isDefault)
                          np->getErrors()->addError(ps.param,"applying the default value (\"=default\" syntax) is not supported in NED files");
                  }
                  ps.param->setIsDefault(ps.isDefault);
                  storePos(np, ps.param, (*yylocp));
                  storeBannerAndRightComments(np, ps.param,(*yylocp));
                }
#line 2773 "ned2.tab.cc"
    break;

  case 102: /* param_typename: opt_volatile paramtype NAME  */
#line 705 "ned2.y"
                {
                  ps.param = addParameter(np, ps.parameters, (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yyloc));
                  ps.param->setType(ps.paramType);
                  ps.param->setIsVolatile(ps.isVolatile);
                  ps.propertyscope.push(ps.param);
                }
#line 2784 "ned2.tab.cc"
    break;

  case 103: /* param_typename: NAME  */
#line 712 "ned2.y"
                {
                  ps.param = addParameter(np, ps.parameters, (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yyloc));
                  ps.propertyscope.push(ps.param);
                }
#line 2793 "ned2.tab.cc"
    break;

  case 104: /* pattern_value: pattern '=' paramvalue ';'  */
#line 720 "ned2.y"
                {
                  ps.param = addParameter(np, ps.parameters, (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-3)].yystate.yyloc));
                  ps.param->setIsPattern(true);
                  const char *patt = ps.param->getName();
                  if (strchr(patt,' ') || strchr(patt,'\t') || strchr(patt,'\n'))
                      np->getErrors()->addError(ps.param,"parameter name patterns may not contain whitespace");
                  if (!isEmpty(ps.exprPos))  // note: $3 cannot be checked, as it's always nullptr when expression parsing is off
                      addExpression(np, ps.param, "value",ps.exprPos,YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yysemantics.yyval);
                  else {
                      // Note: "=default" is currently not accepted in NED files, because
                      // it would be complicated to support in the Inifile Editor.
                      if (ps.isDefault)
                          np->getErrors()->addError(ps.param,"applying the default value (\"=default\" syntax) is not supported in NED files");
                  }
                  ps.param->setIsDefault(ps.isDefault);
                  storePos(np, ps.param, (*yylocp));
                  storeBannerAndRightComments(np, ps.param,(*yylocp));
                }
#line 2816 "ned2.tab.cc"
    break;

  case 105: /* paramtype: DOUBLETYPE  */
#line 742 "ned2.y"
                { ps.paramType = PARTYPE_DOUBLE; }
#line 2822 "ned2.tab.cc"
    break;

  case 106: /* paramtype: INTTYPE  */
#line 744 "ned2.y"
                { ps.paramType = PARTYPE_INT; }
#line 2828 "ned2.tab.cc"
    break;

  case 107: /* paramtype: STRINGTYPE  */
#line 746 "ned2.y"
                { ps.paramType = PARTYPE_STRING; }
#line 2834 "ned2.tab.cc"
    break;

  case 108: /* paramtype: BOOLTYPE  */
#line 748 "ned2.y"
                { ps.paramType = PARTYPE_BOOL; }
#line 2840 "ned2.tab.cc"
    break;

  case 109: /* paramtype: XMLTYPE  */
#line 750 "ned2.y"
                { ps.paramType = PARTYPE_XML; }
#line 2846 "ned2.tab.cc"
    break;

  case 110: /* opt_volatile: VOLATILE  */
#line 755 "ned2.y"
                { ps.isVolatile = true; }
#line 2852 "ned2.tab.cc"
    break;

  case 111: /* opt_volatile: %empty  */
#line 757 "ned2.y"
                { ps.isVolatile = false; }
#line 2858 "ned2.tab.cc"
    break;

  case 112: /* paramvalue: expression  */
#line 762 "ned2.y"
                { (*yyvalp) = YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yyval; ps.exprPos = (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yyloc); ps.isDefault = false; }
#line 2864 "ned2.tab.cc"
    break;

  case 113: /* paramvalue: DEFAULT '(' expression ')'  */
#line 764 "ned2.y"
                { (*yyvalp) = YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yysemantics.yyval; ps.exprPos = (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yyloc); ps.isDefault = true; }
#line 2870 "ned2.tab.cc"
    break;

  case 114: /* paramvalue: DEFAULT  */
#line 766 "ned2.y"
                {
                  (*yyvalp) = nullptr; ps.exprPos = makeEmptyYYLoc(); ps.isDefault = true;
                }
#line 2878 "ned2.tab.cc"
    break;

  case 115: /* paramvalue: ASK  */
#line 770 "ned2.y"
                {
                  np->getErrors()->addError(ps.parameters,"interactive prompting (\"=ask\" syntax) is not supported in NED files");
                  (*yyvalp) = nullptr; ps.exprPos = makeEmptyYYLoc(); ps.isDefault = false;
                }
#line 2887 "ned2.tab.cc"
    break;

  case 140: /* property: property_namevalue ';'  */
#line 826 "ned2.y"
                {
                  storePos(np, ps.property, (*yylocp));
                  storeBannerAndRightComments(np, ps.property,(*yylocp));
                }
#line 2896 "ned2.tab.cc"
    break;

  case 143: /* property_name: '@' PROPNAME  */
#line 839 "ned2.y"
                {
                  assertNonEmpty(ps.propertyscope);
                  ps.property = addProperty(np, ps.propertyscope.top(), toString(np, (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yyloc)));
                  ps.propvals.clear(); // just to be safe
                }
#line 2906 "ned2.tab.cc"
    break;

  case 144: /* property_name: '@' PROPNAME '[' PROPNAME ']'  */
#line 845 "ned2.y"
                {
                  assertNonEmpty(ps.propertyscope);
                  ps.property = addProperty(np, ps.propertyscope.top(), toString(np, (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-3)].yystate.yyloc)));
                  ps.property->setIndex(toString(np, (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yyloc)));
                  ps.propvals.clear(); // just to be safe
                }
#line 2917 "ned2.tab.cc"
    break;

  case 148: /* property_key: property_literal '=' property_values  */
#line 864 "ned2.y"
                {
                  ps.propkey = (PropertyKeyElement *)createNedElementWithTag(np, NED_PROPERTY_KEY, ps.property);
                  ps.propkey->setName(opp_trim(toString(np, (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-2)].yystate.yyloc))).c_str());
                  for (int i=0; i<(int)ps.propvals.size(); i++)
                      ps.propkey->appendChild(ps.propvals[i]);
                  ps.propvals.clear();
                  storePos(np, ps.propkey, (*yylocp));
                }
#line 2930 "ned2.tab.cc"
    break;

  case 149: /* property_key: property_values  */
#line 873 "ned2.y"
                {
                  ps.propkey = (PropertyKeyElement *)createNedElementWithTag(np, NED_PROPERTY_KEY, ps.property);
                  ps.propkey->appendChild(YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yyval);
                  for (int i=0; i<(int)ps.propvals.size(); i++)
                      ps.propkey->appendChild(ps.propvals[i]);
                  ps.propvals.clear();
                  storePos(np, ps.propkey, (*yylocp));
                }
#line 2943 "ned2.tab.cc"
    break;

  case 150: /* property_values: property_values ',' property_value  */
#line 885 "ned2.y"
                { ps.propvals.push_back(YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yyval); }
#line 2949 "ned2.tab.cc"
    break;

  case 151: /* property_values: property_value  */
#line 887 "ned2.y"
                { ps.propvals.push_back(YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yyval); }
#line 2955 "ned2.tab.cc"
    break;

  case 152: /* property_value: property_literal  */
#line 892 "ned2.y"
                {
                  (*yyvalp) = createPropertyValue(np, (*yylocp));
                }
#line 2963 "ned2.tab.cc"
    break;

  case 153: /* property_value: %empty  */
#line 896 "ned2.y"
                {
                  LiteralElement *node = (LiteralElement *)createNedElementWithTag(np, NED_LITERAL);
                  node->setType(LIT_SPEC); // and leave both value and text at ""
                  (*yyvalp) = node;
                }
#line 2973 "ned2.tab.cc"
    break;

  case 160: /* $@14: %empty  */
#line 920 "ned2.y"
                {
                  assertNonEmpty(ps.blockscope);
                  ps.gates = (GatesElement *)createNedElementWithTag(np, NED_GATES, ps.blockscope.top());
                  storeBannerAndRightComments(np, ps.gates,(YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yyloc),(YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yyloc));
                }
#line 2983 "ned2.tab.cc"
    break;

  case 161: /* gateblock: GATES ':' $@14 opt_gates  */
#line 926 "ned2.y"
                {
                  storePos(np, ps.gates, (*yylocp));
                }
#line 2991 "ned2.tab.cc"
    break;

  case 164: /* gates: gates gate  */
#line 938 "ned2.y"
                {
                  storeBannerAndRightComments(np, ps.gate,(YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yyloc));
                }
#line 2999 "ned2.tab.cc"
    break;

  case 165: /* gates: gate  */
#line 942 "ned2.y"
                {
                  storeBannerAndRightComments(np, ps.gate,(YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yyloc));
                }
#line 3007 "ned2.tab.cc"
    break;

  case 166: /* $@15: %empty  */
#line 952 "ned2.y"
                {
                  ps.propertyscope.push(ps.gate);
                }
#line 3015 "ned2.tab.cc"
    break;

  case 167: /* gate: gate_typenamesize $@15 opt_inline_properties ';'  */
#line 956 "ned2.y"
                {
                  ps.propertyscope.pop();
                  storePos(np, ps.gate, (*yylocp));
                }
#line 3024 "ned2.tab.cc"
    break;

  case 168: /* gate_typenamesize: gatetype NAME  */
#line 964 "ned2.y"
                {
                  ps.gate = addGate(np, ps.gates, (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yyloc));
                  ps.gate->setType(ps.gateType);
                }
#line 3033 "ned2.tab.cc"
    break;

  case 169: /* gate_typenamesize: gatetype NAME '[' ']'  */
#line 969 "ned2.y"
                {
                  ps.gate = addGate(np, ps.gates, (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-2)].yystate.yyloc));
                  ps.gate->setType(ps.gateType);
                  ps.gate->setIsVector(true);
                }
#line 3043 "ned2.tab.cc"
    break;

  case 170: /* gate_typenamesize: gatetype NAME vector  */
#line 975 "ned2.y"
                {
                  ps.gate = addGate(np, ps.gates, (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yyloc));
                  ps.gate->setType(ps.gateType);
                  ps.gate->setIsVector(true);
                  addExpression(np, ps.gate, "vector-size",ps.exprPos,YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yyval);
                }
#line 3054 "ned2.tab.cc"
    break;

  case 171: /* gate_typenamesize: NAME  */
#line 982 "ned2.y"
                {
                  ps.gate = addGate(np, ps.gates, (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yyloc));
                }
#line 3062 "ned2.tab.cc"
    break;

  case 172: /* gate_typenamesize: NAME '[' ']'  */
#line 986 "ned2.y"
                {
                  ps.gate = addGate(np, ps.gates, (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-2)].yystate.yyloc));
                  ps.gate->setIsVector(true);
                }
#line 3071 "ned2.tab.cc"
    break;

  case 173: /* gate_typenamesize: NAME vector  */
#line 991 "ned2.y"
                {
                  ps.gate = addGate(np, ps.gates, (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yyloc));
                  ps.gate->setIsVector(true);
                  addExpression(np, ps.gate, "vector-size",ps.exprPos,YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yyval);
                }
#line 3081 "ned2.tab.cc"
    break;

  case 174: /* gatetype: INPUT_  */
#line 1000 "ned2.y"
                { ps.gateType = GATETYPE_INPUT; }
#line 3087 "ned2.tab.cc"
    break;

  case 175: /* gatetype: OUTPUT_  */
#line 1002 "ned2.y"
                { ps.gateType = GATETYPE_OUTPUT; }
#line 3093 "ned2.tab.cc"
    break;

  case 176: /* gatetype: INOUT_  */
#line 1004 "ned2.y"
                { ps.gateType = GATETYPE_INOUT; }
#line 3099 "ned2.tab.cc"
    break;

  case 179: /* $@16: %empty  */
#line 1017 "ned2.y"
                {
                  assertNonEmpty(ps.blockscope);
                  ps.types = (TypesElement *)createNedElementWithTag(np, NED_TYPES, ps.blockscope.top());
                  storeBannerAndRightComments(np, ps.types,(YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yyloc),(YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yyloc));
                  if (ps.inTypes)
                     np->getErrors()->addError(ps.types,"more than one level of type nesting is not allowed");
                  ps.inTypes = true;
                }
#line 3112 "ned2.tab.cc"
    break;

  case 180: /* typeblock: TYPES ':' $@16 opt_localtypes  */
#line 1026 "ned2.y"
                {
                  ps.inTypes = false;
                  storePos(np, ps.types, (*yylocp));
                }
#line 3121 "ned2.tab.cc"
    break;

  case 195: /* $@17: %empty  */
#line 1063 "ned2.y"
                {
                  assertNonEmpty(ps.blockscope);
                  ps.submods = (SubmodulesElement *)createNedElementWithTag(np, NED_SUBMODULES, ps.blockscope.top());
                  storeBannerAndRightComments(np, ps.submods,(YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yyloc),(YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yyloc));
                }
#line 3131 "ned2.tab.cc"
    break;

  case 196: /* submodblock: SUBMODULES ':' $@17 opt_submodules  */
#line 1069 "ned2.y"
                {
                  storePos(np, ps.submods, (*yylocp));
                }
#line 3139 "ned2.tab.cc"
    break;

  case 201: /* submodule: submoduleheader ';'  */
#line 1086 "ned2.y"
                {
                  storeBannerAndRightComments(np, ps.submod,(YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yyloc),(YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yyloc));
                  storePos(np, ps.submod, (*yylocp));
                }
#line 3148 "ned2.tab.cc"
    break;

  case 202: /* $@18: %empty  */
#line 1091 "ned2.y"
                {
                  ps.blockscope.push(ps.submod);
                  ps.parameters = (ParametersElement *)createNedElementWithTag(np, NED_PARAMETERS, ps.submod);
                  ps.parameters->setIsImplicit(true);
                  ps.propertyscope.push(ps.parameters);
                  storeBannerAndRightComments(np, ps.submod,(YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yyloc),(YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yyloc));
                }
#line 3160 "ned2.tab.cc"
    break;

  case 203: /* submodule: submoduleheader '{' $@18 opt_paramblock opt_gateblock '}' opt_semicolon  */
#line 1101 "ned2.y"
                {
                  ps.blockscope.pop();
                  ps.propertyscope.pop();
                  storePos(np, ps.submod, (*yylocp));
                  storeTrailingComment(np, ps.submod,(*yylocp));
                }
#line 3171 "ned2.tab.cc"
    break;

  case 204: /* submoduleheader: submodulename ':' dottedname opt_condition  */
#line 1111 "ned2.y"
                {
                  ps.submod->setType(removeSpaces(np, (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yyloc)).c_str());
                  if (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yyval) ps.submod->appendChild(YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yyval);
                }
#line 3180 "ned2.tab.cc"
    break;

  case 205: /* submoduleheader: submodulename ':' likeexpr LIKE dottedname opt_condition  */
#line 1116 "ned2.y"
                {
                  addOptionalExpression(np, ps.submod, "like-expr", ps.exprPos, YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-3)].yystate.yysemantics.yyval);
                  ps.submod->setLikeType(removeSpaces(np, (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yyloc)).c_str());
                  ps.submod->setIsDefault(ps.isDefault);
                  if (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yyval) ps.submod->appendChild(YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yyval);
                }
#line 3191 "ned2.tab.cc"
    break;

  case 206: /* submodulename: NAME  */
#line 1126 "ned2.y"
                {
                  ps.submod = (SubmoduleElement *)createNedElementWithTag(np, NED_SUBMODULE, ps.submods);
                  ps.submod->setName(toString(np, (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yyloc)));
                }
#line 3200 "ned2.tab.cc"
    break;

  case 207: /* submodulename: NAME vector  */
#line 1131 "ned2.y"
                {
                  ps.submod = (SubmoduleElement *)createNedElementWithTag(np, NED_SUBMODULE, ps.submods);
                  ps.submod->setName(toString(np, (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yyloc)));
                  addExpression(np, ps.submod, "vector-size",ps.exprPos,YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yyval);
                }
#line 3210 "ned2.tab.cc"
    break;

  case 208: /* likeexpr: '<' '>'  */
#line 1140 "ned2.y"
                { (*yyvalp) = nullptr; ps.exprPos = makeEmptyYYLoc(); ps.isDefault = false; }
#line 3216 "ned2.tab.cc"
    break;

  case 209: /* likeexpr: '<' expression '>'  */
#line 1142 "ned2.y"
                { (*yyvalp) = YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yysemantics.yyval; ps.exprPos = (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yyloc); ps.isDefault = false; }
#line 3222 "ned2.tab.cc"
    break;

  case 210: /* likeexpr: '<' DEFAULT '(' expression ')' '>'  */
#line 1144 "ned2.y"
                { (*yyvalp) = YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-2)].yystate.yysemantics.yyval; ps.exprPos = (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-2)].yystate.yyloc); ps.isDefault = true; }
#line 3228 "ned2.tab.cc"
    break;

  case 211: /* opt_condition: condition  */
#line 1149 "ned2.y"
                { (*yyvalp) = YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yyval; }
#line 3234 "ned2.tab.cc"
    break;

  case 212: /* opt_condition: %empty  */
#line 1151 "ned2.y"
                { (*yyvalp) = nullptr; }
#line 3240 "ned2.tab.cc"
    break;

  case 215: /* $@19: %empty  */
#line 1164 "ned2.y"
                {
                  assertNonEmpty(ps.blockscope);
                  ps.conns = (ConnectionsElement *)createNedElementWithTag(np, NED_CONNECTIONS, ps.blockscope.top());
                  ps.conns->setAllowUnconnected(true);
                  storeBannerAndRightComments(np, ps.conns,(YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-2)].yystate.yyloc),(YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yyloc));
                }
#line 3251 "ned2.tab.cc"
    break;

  case 216: /* connblock: CONNECTIONS ALLOWUNCONNECTED ':' $@19 opt_connections  */
#line 1171 "ned2.y"
                {
                  storePos(np, ps.conns, (*yylocp));
                }
#line 3259 "ned2.tab.cc"
    break;

  case 217: /* $@20: %empty  */
#line 1175 "ned2.y"
                {
                  assertNonEmpty(ps.blockscope);
                  ps.conns = (ConnectionsElement *)createNedElementWithTag(np, NED_CONNECTIONS, ps.blockscope.top());
                  storeBannerAndRightComments(np, ps.conns,(YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yyloc),(YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yyloc));
                }
#line 3269 "ned2.tab.cc"
    break;

  case 218: /* connblock: CONNECTIONS ':' $@20 opt_connections  */
#line 1181 "ned2.y"
                {
                  storePos(np, ps.conns, (*yylocp));
                }
#line 3277 "ned2.tab.cc"
    break;

  case 224: /* connectionsitem: connection opt_loops_and_conditions ';'  */
#line 1199 "ned2.y"
                {
                  if (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yysemantics.yyval) {
                      transferChildren(YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yysemantics.yyval, ps.conn);
                      delete YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yysemantics.yyval;
                  }
                  storePos(np, ps.conn, (*yylocp));
                  storeBannerAndRightComments(np, ps.conn,(*yylocp));
                }
#line 3290 "ned2.tab.cc"
    break;

  case 225: /* $@21: %empty  */
#line 1211 "ned2.y"
                {
                  if (ps.inConnGroup)
                      np->getErrors()->addError(ps.conngroup,"nested connection groups are not allowed");
                  ps.conngroup = (ConnectionGroupElement *)createNedElementWithTag(np, NED_CONNECTION_GROUP, ps.conns);
                  if (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yysemantics.yyval) {
                      // for's and if's were collected in a temporary UnknownElement, put them under conngroup now
                      transferChildren(YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yysemantics.yyval, ps.conngroup);
                      delete YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yysemantics.yyval;
                  }
                  ps.inConnGroup = true;
                  storeBannerAndRightComments(np, ps.conngroup,(YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yyloc));
                }
#line 3307 "ned2.tab.cc"
    break;

  case 226: /* connectiongroup: opt_loops_and_conditions '{' $@21 connections '}' opt_semicolon  */
#line 1224 "ned2.y"
                {
                  ps.inConnGroup = false;
                  storePos(np, ps.conngroup,(*yylocp));
                  storeTrailingComment(np, ps.conngroup,(*yylocp));
                }
#line 3317 "ned2.tab.cc"
    break;

  case 227: /* opt_loops_and_conditions: loops_and_conditions  */
#line 1233 "ned2.y"
                { (*yyvalp) = YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yyval; }
#line 3323 "ned2.tab.cc"
    break;

  case 228: /* opt_loops_and_conditions: %empty  */
#line 1235 "ned2.y"
                { (*yyvalp) = nullptr; }
#line 3329 "ned2.tab.cc"
    break;

  case 229: /* loops_and_conditions: loops_and_conditions ',' loop_or_condition  */
#line 1240 "ned2.y"
                {
                  YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-2)].yystate.yysemantics.yyval->appendChild(YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yyval);
                  (*yyvalp) = YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-2)].yystate.yysemantics.yyval;
                }
#line 3338 "ned2.tab.cc"
    break;

  case 230: /* loops_and_conditions: loop_or_condition  */
#line 1245 "ned2.y"
                {
                  (*yyvalp) = new UnknownElement();
                  (*yyvalp)->appendChild(YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yyval);
                }
#line 3347 "ned2.tab.cc"
    break;

  case 233: /* loop: FOR NAME '=' expression TO expression  */
#line 1258 "ned2.y"
                {
                  ps.loop = (LoopElement *)createNedElementWithTag(np, NED_LOOP);
                  ps.loop->setParamName( toString(np, (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-4)].yystate.yyloc)) );
                  addExpression(np, ps.loop, "from-value",(YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-2)].yystate.yyloc),YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-2)].yystate.yysemantics.yyval);
                  addExpression(np, ps.loop, "to-value",(YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yyloc),YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yyval);
                  storePos(np, ps.loop, (*yylocp));
                  (*yyvalp) = ps.loop;
                }
#line 3360 "ned2.tab.cc"
    break;

  case 234: /* connection: leftgatespec RIGHTARROW rightgatespec  */
#line 1273 "ned2.y"
                {
                  ps.conn->setIsBidirectional(false);
                  ps.conn->setIsForwardArrow(true);
                }
#line 3369 "ned2.tab.cc"
    break;

  case 235: /* connection: leftgatespec RIGHTARROW channelspec RIGHTARROW rightgatespec  */
#line 1278 "ned2.y"
                {
                  ps.conn->setIsBidirectional(false);
                  ps.conn->setIsForwardArrow(true);
                }
#line 3378 "ned2.tab.cc"
    break;

  case 236: /* connection: leftgatespec LEFTARROW rightgatespec  */
#line 1283 "ned2.y"
                {
                  swapConnection(ps.conn);
                  ps.conn->setIsBidirectional(false);
                  ps.conn->setIsForwardArrow(false);
                }
#line 3388 "ned2.tab.cc"
    break;

  case 237: /* connection: leftgatespec LEFTARROW channelspec LEFTARROW rightgatespec  */
#line 1289 "ned2.y"
                {
                  swapConnection(ps.conn);
                  ps.conn->setIsBidirectional(false);
                  ps.conn->setIsForwardArrow(false);
                }
#line 3398 "ned2.tab.cc"
    break;

  case 238: /* connection: leftgatespec DBLARROW rightgatespec  */
#line 1295 "ned2.y"
                {
                  ps.conn->setIsBidirectional(true);
                }
#line 3406 "ned2.tab.cc"
    break;

  case 239: /* connection: leftgatespec DBLARROW channelspec DBLARROW rightgatespec  */
#line 1299 "ned2.y"
                {
                  ps.conn->setIsBidirectional(true);
                }
#line 3414 "ned2.tab.cc"
    break;

  case 242: /* leftmod: NAME vector  */
#line 1311 "ned2.y"
                {
                  ps.conn = (ConnectionElement *)createNedElementWithTag(np, NED_CONNECTION, ps.inConnGroup ? (ASTNode*)ps.conngroup : (ASTNode*)ps.conns );
                  ps.conn->setSrcModule( toString(np, (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yyloc)) );
                  addExpression(np, ps.conn, "src-module-index",ps.exprPos,YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yyval);
                }
#line 3424 "ned2.tab.cc"
    break;

  case 243: /* leftmod: NAME  */
#line 1317 "ned2.y"
                {
                  ps.conn = (ConnectionElement *)createNedElementWithTag(np, NED_CONNECTION, ps.inConnGroup ? (ASTNode*)ps.conngroup : (ASTNode*)ps.conns );
                  ps.conn->setSrcModule( toString(np, (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yyloc)) );
                }
#line 3433 "ned2.tab.cc"
    break;

  case 244: /* leftgate: NAME opt_subgate  */
#line 1325 "ned2.y"
                {
                  ps.conn->setSrcGate( toString(np,  (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yyloc)) );
                  ps.conn->setSrcGateSubg(ps.subgate);
                }
#line 3442 "ned2.tab.cc"
    break;

  case 245: /* leftgate: NAME opt_subgate vector  */
#line 1330 "ned2.y"
                {
                  ps.conn->setSrcGate( toString(np,  (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-2)].yystate.yyloc)) );
                  ps.conn->setSrcGateSubg(ps.subgate);
                  addExpression(np, ps.conn, "src-gate-index",ps.exprPos,YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yyval);
                }
#line 3452 "ned2.tab.cc"
    break;

  case 246: /* leftgate: NAME opt_subgate PLUSPLUS  */
#line 1336 "ned2.y"
                {
                  ps.conn->setSrcGate( toString(np,  (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-2)].yystate.yyloc)) );
                  ps.conn->setSrcGateSubg(ps.subgate);
                  ps.conn->setSrcGatePlusplus(true);
                }
#line 3462 "ned2.tab.cc"
    break;

  case 247: /* parentleftgate: NAME opt_subgate  */
#line 1345 "ned2.y"
                {
                  ps.conn = (ConnectionElement *)createNedElementWithTag(np, NED_CONNECTION, ps.inConnGroup ? (ASTNode*)ps.conngroup : (ASTNode*)ps.conns );
                  ps.conn->setSrcModule("");
                  ps.conn->setSrcGate(toString(np, (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yyloc)));
                  ps.conn->setSrcGateSubg(ps.subgate);
                }
#line 3473 "ned2.tab.cc"
    break;

  case 248: /* parentleftgate: NAME opt_subgate vector  */
#line 1352 "ned2.y"
                {
                  ps.conn = (ConnectionElement *)createNedElementWithTag(np, NED_CONNECTION, ps.inConnGroup ? (ASTNode*)ps.conngroup : (ASTNode*)ps.conns );
                  ps.conn->setSrcModule("");
                  ps.conn->setSrcGate(toString(np, (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-2)].yystate.yyloc)));
                  ps.conn->setSrcGateSubg(ps.subgate);
                  addExpression(np, ps.conn, "src-gate-index",ps.exprPos,YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yyval);
                }
#line 3485 "ned2.tab.cc"
    break;

  case 249: /* parentleftgate: NAME opt_subgate PLUSPLUS  */
#line 1360 "ned2.y"
                {
                  ps.conn = (ConnectionElement *)createNedElementWithTag(np, NED_CONNECTION, ps.inConnGroup ? (ASTNode*)ps.conngroup : (ASTNode*)ps.conns );
                  ps.conn->setSrcModule("");
                  ps.conn->setSrcGate(toString(np, (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-2)].yystate.yyloc)));
                  ps.conn->setSrcGateSubg(ps.subgate);
                  ps.conn->setSrcGatePlusplus(true);
                }
#line 3497 "ned2.tab.cc"
    break;

  case 252: /* rightmod: NAME  */
#line 1376 "ned2.y"
                {
                  ps.conn->setDestModule( toString(np, (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yyloc)) );
                }
#line 3505 "ned2.tab.cc"
    break;

  case 253: /* rightmod: NAME vector  */
#line 1380 "ned2.y"
                {
                  ps.conn->setDestModule( toString(np, (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yyloc)) );
                  addExpression(np, ps.conn, "dest-module-index",ps.exprPos,YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yyval);
                }
#line 3514 "ned2.tab.cc"
    break;

  case 254: /* rightgate: NAME opt_subgate  */
#line 1388 "ned2.y"
                {
                  ps.conn->setDestGate( toString(np,  (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yyloc)) );
                  ps.conn->setDestGateSubg(ps.subgate);
                }
#line 3523 "ned2.tab.cc"
    break;

  case 255: /* rightgate: NAME opt_subgate vector  */
#line 1393 "ned2.y"
                {
                  ps.conn->setDestGate( toString(np,  (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-2)].yystate.yyloc)) );
                  ps.conn->setDestGateSubg(ps.subgate);
                  addExpression(np, ps.conn, "dest-gate-index",ps.exprPos,YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yyval);
                }
#line 3533 "ned2.tab.cc"
    break;

  case 256: /* rightgate: NAME opt_subgate PLUSPLUS  */
#line 1399 "ned2.y"
                {
                  ps.conn->setDestGate( toString(np,  (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-2)].yystate.yyloc)) );
                  ps.conn->setDestGateSubg(ps.subgate);
                  ps.conn->setDestGatePlusplus(true);
                }
#line 3543 "ned2.tab.cc"
    break;

  case 257: /* parentrightgate: NAME opt_subgate  */
#line 1408 "ned2.y"
                {
                  ps.conn->setDestGate( toString(np,  (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yyloc)) );
                  ps.conn->setDestGateSubg(ps.subgate);
                }
#line 3552 "ned2.tab.cc"
    break;

  case 258: /* parentrightgate: NAME opt_subgate vector  */
#line 1413 "ned2.y"
                {
                  ps.conn->setDestGate( toString(np,  (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-2)].yystate.yyloc)) );
                  ps.conn->setDestGateSubg(ps.subgate);
                  addExpression(np, ps.conn, "dest-gate-index",ps.exprPos,YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yyval);
                }
#line 3562 "ned2.tab.cc"
    break;

  case 259: /* parentrightgate: NAME opt_subgate PLUSPLUS  */
#line 1419 "ned2.y"
                {
                  ps.conn->setDestGate( toString(np,  (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-2)].yystate.yyloc)) );
                  ps.conn->setDestGateSubg(ps.subgate);
                  ps.conn->setDestGatePlusplus(true);
                }
#line 3572 "ned2.tab.cc"
    break;

  case 260: /* opt_subgate: '$' NAME  */
#line 1428 "ned2.y"
                {
                  const char *s = toString(np, (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yyloc));
                  if (!strcmp(s,"i"))
                      ps.subgate = SUBGATE_I;
                  else if (!strcmp(s,"o"))
                      ps.subgate = SUBGATE_O;
                  else
                       np->getErrors()->addError(currentLocation(np), "invalid subgate spec '%s', must be 'i' or 'o'", toString(np, (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yyloc)));
                }
#line 3586 "ned2.tab.cc"
    break;

  case 261: /* opt_subgate: %empty  */
#line 1438 "ned2.y"
                { ps.subgate = SUBGATE_NONE; }
#line 3592 "ned2.tab.cc"
    break;

  case 263: /* $@22: %empty  */
#line 1444 "ned2.y"
                {
                  ps.parameters = (ParametersElement *)createNedElementWithTag(np, NED_PARAMETERS, ps.conn);
                  ps.parameters->setIsImplicit(true);
                  ps.propertyscope.push(ps.parameters);
                }
#line 3602 "ned2.tab.cc"
    break;

  case 264: /* channelspec: channelspec_header '{' $@22 opt_paramblock '}'  */
#line 1451 "ned2.y"
                {
                  ps.propertyscope.pop();
                }
#line 3610 "ned2.tab.cc"
    break;

  case 266: /* channelspec_header: opt_channelname dottedname  */
#line 1460 "ned2.y"
                {
                  ps.conn->setType(removeSpaces(np, (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yyloc)).c_str());
                }
#line 3618 "ned2.tab.cc"
    break;

  case 267: /* channelspec_header: opt_channelname likeexpr LIKE dottedname  */
#line 1464 "ned2.y"
                {
                  addOptionalExpression(np, ps.conn, "like-expr", ps.exprPos, YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-2)].yystate.yysemantics.yyval);
                  ps.conn->setLikeType(removeSpaces(np, (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yyloc)).c_str());
                  ps.conn->setIsDefault(ps.isDefault);
                }
#line 3628 "ned2.tab.cc"
    break;

  case 269: /* opt_channelname: NAME ':'  */
#line 1474 "ned2.y"
                { ps.conn->setName(toString(np, (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yyloc))); }
#line 3634 "ned2.tab.cc"
    break;

  case 270: /* condition: IF expression  */
#line 1482 "ned2.y"
                {
                  ps.condition = (ConditionElement *)createNedElementWithTag(np, NED_CONDITION);
                  addExpression(np, ps.condition, "condition",(YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yyloc),YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yyval);
                  storePos(np, ps.condition, (*yylocp));
                  (*yyvalp) = ps.condition;
                }
#line 3645 "ned2.tab.cc"
    break;

  case 271: /* vector: '[' expression ']'  */
#line 1495 "ned2.y"
                { (*yyvalp) = YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yysemantics.yyval; ps.exprPos = (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yyloc); }
#line 3651 "ned2.tab.cc"
    break;

  case 272: /* expression: expr  */
#line 1501 "ned2.y"
                {
                  if (np->getParseExpressionsFlag()) (*yyvalp) = createExpression(np, YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yyval);
                }
#line 3659 "ned2.tab.cc"
    break;

  case 274: /* expr: '(' expr ')'  */
#line 1512 "ned2.y"
                { (*yyvalp) = YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yysemantics.yyval; }
#line 3665 "ned2.tab.cc"
    break;

  case 275: /* expr: CONST_ '(' expr ')'  */
#line 1514 "ned2.y"
                { if (np->getParseExpressionsFlag()) (*yyvalp) = createFunction(np, "const", YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yysemantics.yyval); }
#line 3671 "ned2.tab.cc"
    break;

  case 276: /* expr: expr '+' expr  */
#line 1517 "ned2.y"
                { if (np->getParseExpressionsFlag()) (*yyvalp) = createOperator(np, "+", YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-2)].yystate.yysemantics.yyval, YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yyval); }
#line 3677 "ned2.tab.cc"
    break;

  case 277: /* expr: expr '-' expr  */
#line 1519 "ned2.y"
                { if (np->getParseExpressionsFlag()) (*yyvalp) = createOperator(np, "-", YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-2)].yystate.yysemantics.yyval, YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yyval); }
#line 3683 "ned2.tab.cc"
    break;

  case 278: /* expr: expr '*' expr  */
#line 1521 "ned2.y"
                { if (np->getParseExpressionsFlag()) (*yyvalp) = createOperator(np, "*", YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-2)].yystate.yysemantics.yyval, YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yyval); }
#line 3689 "ned2.tab.cc"
    break;

  case 279: /* expr: expr '/' expr  */
#line 1523 "ned2.y"
                { if (np->getParseExpressionsFlag()) (*yyvalp) = createOperator(np, "/", YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-2)].yystate.yysemantics.yyval, YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yyval); }
#line 3695 "ned2.tab.cc"
    break;

  case 280: /* expr: expr '%' expr  */
#line 1525 "ned2.y"
                { if (np->getParseExpressionsFlag()) (*yyvalp) = createOperator(np, "%", YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-2)].yystate.yysemantics.yyval, YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yyval); }
#line 3701 "ned2.tab.cc"
    break;

  case 281: /* expr: expr '^' expr  */
#line 1527 "ned2.y"
                { if (np->getParseExpressionsFlag()) (*yyvalp) = createOperator(np, "^", YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-2)].yystate.yysemantics.yyval, YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yyval); }
#line 3707 "ned2.tab.cc"
    break;

  case 282: /* expr: '-' expr  */
#line 1530 "ned2.y"
                { 
                  if (np->getParseExpressionsFlag()) {
                      if (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yyval->getTagCode() == NED_LITERAL)
                          (*yyvalp) = prependMinusSign(np, YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yyval); 
                      else
                          (*yyvalp) = createOperator(np, "-", YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yyval);
                  }
                }
#line 3720 "ned2.tab.cc"
    break;

  case 283: /* expr: expr EQ expr  */
#line 1540 "ned2.y"
                { if (np->getParseExpressionsFlag()) (*yyvalp) = createOperator(np, "==", YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-2)].yystate.yysemantics.yyval, YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yyval); }
#line 3726 "ned2.tab.cc"
    break;

  case 284: /* expr: expr NE expr  */
#line 1542 "ned2.y"
                { if (np->getParseExpressionsFlag()) (*yyvalp) = createOperator(np, "!=", YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-2)].yystate.yysemantics.yyval, YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yyval); }
#line 3732 "ned2.tab.cc"
    break;

  case 285: /* expr: expr '>' expr  */
#line 1544 "ned2.y"
                { if (np->getParseExpressionsFlag()) (*yyvalp) = createOperator(np, ">", YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-2)].yystate.yysemantics.yyval, YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yyval); }
#line 3738 "ned2.tab.cc"
    break;

  case 286: /* expr: expr GE expr  */
#line 1546 "ned2.y"
                { if (np->getParseExpressionsFlag()) (*yyvalp) = createOperator(np, ">=", YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-2)].yystate.yysemantics.yyval, YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yyval); }
#line 3744 "ned2.tab.cc"
    break;

  case 287: /* expr: expr '<' expr  */
#line 1548 "ned2.y"
                { if (np->getParseExpressionsFlag()) (*yyvalp) = createOperator(np, "<", YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-2)].yystate.yysemantics.yyval, YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yyval); }
#line 3750 "ned2.tab.cc"
    break;

  case 288: /* expr: expr LE expr  */
#line 1550 "ned2.y"
                { if (np->getParseExpressionsFlag()) (*yyvalp) = createOperator(np, "<=", YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-2)].yystate.yysemantics.yyval, YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yyval); }
#line 3756 "ned2.tab.cc"
    break;

  case 289: /* expr: expr AND expr  */
#line 1553 "ned2.y"
                { if (np->getParseExpressionsFlag()) (*yyvalp) = createOperator(np, "&&", YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-2)].yystate.yysemantics.yyval, YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yyval); }
#line 3762 "ned2.tab.cc"
    break;

  case 290: /* expr: expr OR expr  */
#line 1555 "ned2.y"
                { if (np->getParseExpressionsFlag()) (*yyvalp) = createOperator(np, "||", YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-2)].yystate.yysemantics.yyval, YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yyval); }
#line 3768 "ned2.tab.cc"
    break;

  case 291: /* expr: expr XOR expr  */
#line 1557 "ned2.y"
                { if (np->getParseExpressionsFlag()) (*yyvalp) = createOperator(np, "##", YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-2)].yystate.yysemantics.yyval, YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yyval); }
#line 3774 "ned2.tab.cc"
    break;

  case 292: /* expr: NOT expr  */
#line 1561 "ned2.y"
                { if (np->getParseExpressionsFlag()) (*yyvalp) = createOperator(np, "!", YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yyval); }
#line 3780 "ned2.tab.cc"
    break;

  case 293: /* expr: expr BIN_AND expr  */
#line 1564 "ned2.y"
                { if (np->getParseExpressionsFlag()) (*yyvalp) = createOperator(np, "&", YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-2)].yystate.yysemantics.yyval, YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yyval); }
#line 3786 "ned2.tab.cc"
    break;

  case 294: /* expr: expr BIN_OR expr  */
#line 1566 "ned2.y"
                { if (np->getParseExpressionsFlag()) (*yyvalp) = createOperator(np, "|", YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-2)].yystate.yysemantics.yyval, YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yyval); }
#line 3792 "ned2.tab.cc"
    break;

  case 295: /* expr: expr BIN_XOR expr  */
#line 1568 "ned2.y"
                { if (np->getParseExpressionsFlag()) (*yyvalp) = createOperator(np, "#", YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-2)].yystate.yysemantics.yyval, YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yyval); }
#line 3798 "ned2.tab.cc"
    break;

  case 296: /* expr: BIN_COMPL expr  */
#line 1572 "ned2.y"
                { if (np->getParseExpressionsFlag()) (*yyvalp) = createOperator(np, "~", YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yyval); }
#line 3804 "ned2.tab.cc"
    break;

  case 297: /* expr: expr SHIFT_LEFT expr  */
#line 1574 "ned2.y"
                { if (np->getParseExpressionsFlag()) (*yyvalp) = createOperator(np, "<<", YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-2)].yystate.yysemantics.yyval, YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yyval); }
#line 3810 "ned2.tab.cc"
    break;

  case 298: /* expr: expr SHIFT_RIGHT expr  */
#line 1576 "ned2.y"
                { if (np->getParseExpressionsFlag()) (*yyvalp) = createOperator(np, ">>", YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-2)].yystate.yysemantics.yyval, YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yyval); }
#line 3816 "ned2.tab.cc"
    break;

  case 299: /* expr: expr '?' expr ':' expr  */
#line 1578 "ned2.y"
                { if (np->getParseExpressionsFlag()) (*yyvalp) = createOperator(np, "?:", YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-4)].yystate.yysemantics.yyval, YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-2)].yystate.yysemantics.yyval, YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yyval); }
#line 3822 "ned2.tab.cc"
    break;

  case 300: /* expr: INTTYPE '(' expr ')'  */
#line 1581 "ned2.y"
                { if (np->getParseExpressionsFlag()) (*yyvalp) = createFunction(np, toString(np, (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-3)].yystate.yyloc)), YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yysemantics.yyval); }
#line 3828 "ned2.tab.cc"
    break;

  case 301: /* expr: DOUBLETYPE '(' expr ')'  */
#line 1583 "ned2.y"
                { if (np->getParseExpressionsFlag()) (*yyvalp) = createFunction(np, toString(np, (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-3)].yystate.yyloc)), YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yysemantics.yyval); }
#line 3834 "ned2.tab.cc"
    break;

  case 302: /* expr: STRINGTYPE '(' expr ')'  */
#line 1585 "ned2.y"
                { if (np->getParseExpressionsFlag()) (*yyvalp) = createFunction(np, toString(np, (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-3)].yystate.yyloc)), YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yysemantics.yyval); }
#line 3840 "ned2.tab.cc"
    break;

  case 303: /* expr: funcname '(' ')'  */
#line 1588 "ned2.y"
                { if (np->getParseExpressionsFlag()) (*yyvalp) = createFunction(np, toString(np, (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-2)].yystate.yyloc))); }
#line 3846 "ned2.tab.cc"
    break;

  case 304: /* expr: funcname '(' expr ')'  */
#line 1590 "ned2.y"
                { if (np->getParseExpressionsFlag()) (*yyvalp) = createFunction(np, toString(np, (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-3)].yystate.yyloc)), YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yysemantics.yyval); }
#line 3852 "ned2.tab.cc"
    break;

  case 305: /* expr: funcname '(' expr ',' expr ')'  */
#line 1592 "ned2.y"
                { if (np->getParseExpressionsFlag()) (*yyvalp) = createFunction(np, toString(np, (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-5)].yystate.yyloc)), YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-3)].yystate.yysemantics.yyval, YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yysemantics.yyval); }
#line 3858 "ned2.tab.cc"
    break;

  case 306: /* expr: funcname '(' expr ',' expr ',' expr ')'  */
#line 1594 "ned2.y"
                { if (np->getParseExpressionsFlag()) (*yyvalp) = createFunction(np, toString(np, (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-7)].yystate.yyloc)), YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-5)].yystate.yysemantics.yyval, YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-3)].yystate.yysemantics.yyval, YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yysemantics.yyval); }
#line 3864 "ned2.tab.cc"
    break;

  case 307: /* expr: funcname '(' expr ',' expr ',' expr ',' expr ')'  */
#line 1596 "ned2.y"
                { if (np->getParseExpressionsFlag()) (*yyvalp) = createFunction(np, toString(np, (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-9)].yystate.yyloc)), YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-7)].yystate.yysemantics.yyval, YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-5)].yystate.yysemantics.yyval, YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-3)].yystate.yysemantics.yyval, YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yysemantics.yyval); }
#line 3870 "ned2.tab.cc"
    break;

  case 308: /* expr: funcname '(' expr ',' expr ',' expr ',' expr ',' expr ')'  */
#line 1598 "ned2.y"
                { if (np->getParseExpressionsFlag()) (*yyvalp) = createFunction(np, toString(np, (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-11)].yystate.yyloc)), YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-9)].yystate.yysemantics.yyval, YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-7)].yystate.yysemantics.yyval, YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-5)].yystate.yysemantics.yyval, YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-3)].yystate.yysemantics.yyval, YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yysemantics.yyval); }
#line 3876 "ned2.tab.cc"
    break;

  case 309: /* expr: funcname '(' expr ',' expr ',' expr ',' expr ',' expr ',' expr ')'  */
#line 1600 "ned2.y"
                { if (np->getParseExpressionsFlag()) (*yyvalp) = createFunction(np, toString(np, (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-13)].yystate.yyloc)), YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-11)].yystate.yysemantics.yyval, YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-9)].yystate.yysemantics.yyval, YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-7)].yystate.yysemantics.yyval, YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-5)].yystate.yysemantics.yyval, YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-3)].yystate.yysemantics.yyval, YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yysemantics.yyval); }
#line 3882 "ned2.tab.cc"
    break;

  case 310: /* expr: funcname '(' expr ',' expr ',' expr ',' expr ',' expr ',' expr ',' expr ')'  */
#line 1602 "ned2.y"
                { if (np->getParseExpressionsFlag()) (*yyvalp) = createFunction(np, toString(np, (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-15)].yystate.yyloc)), YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-13)].yystate.yysemantics.yyval, YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-11)].yystate.yysemantics.yyval, YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-9)].yystate.yysemantics.yyval, YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-7)].yystate.yysemantics.yyval, YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-5)].yystate.yysemantics.yyval, YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-3)].yystate.yysemantics.yyval, YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yysemantics.yyval); }
#line 3888 "ned2.tab.cc"
    break;

  case 311: /* expr: funcname '(' expr ',' expr ',' expr ',' expr ',' expr ',' expr ',' expr ',' expr ')'  */
#line 1604 "ned2.y"
                { if (np->getParseExpressionsFlag()) (*yyvalp) = createFunction(np, toString(np, (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-17)].yystate.yyloc)), YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-15)].yystate.yysemantics.yyval, YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-13)].yystate.yysemantics.yyval, YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-11)].yystate.yysemantics.yyval, YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-9)].yystate.yysemantics.yyval, YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-7)].yystate.yysemantics.yyval, YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-5)].yystate.yysemantics.yyval, YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-3)].yystate.yysemantics.yyval, YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yysemantics.yyval); }
#line 3894 "ned2.tab.cc"
    break;

  case 312: /* expr: funcname '(' expr ',' expr ',' expr ',' expr ',' expr ',' expr ',' expr ',' expr ',' expr ')'  */
#line 1606 "ned2.y"
                { if (np->getParseExpressionsFlag()) (*yyvalp) = createFunction(np, toString(np, (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-19)].yystate.yyloc)), YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-17)].yystate.yysemantics.yyval, YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-15)].yystate.yysemantics.yyval, YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-13)].yystate.yysemantics.yyval, YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-11)].yystate.yysemantics.yyval, YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-9)].yystate.yysemantics.yyval, YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-7)].yystate.yysemantics.yyval, YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-5)].yystate.yysemantics.yyval, YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-3)].yystate.yysemantics.yyval, YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yysemantics.yyval); }
#line 3900 "ned2.tab.cc"
    break;

  case 313: /* expr: funcname '(' expr ',' expr ',' expr ',' expr ',' expr ',' expr ',' expr ',' expr ',' expr ',' expr ')'  */
#line 1608 "ned2.y"
                { if (np->getParseExpressionsFlag()) (*yyvalp) = createFunction(np, toString(np, (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-21)].yystate.yyloc)), YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-19)].yystate.yysemantics.yyval, YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-17)].yystate.yysemantics.yyval, YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-15)].yystate.yysemantics.yyval, YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-13)].yystate.yysemantics.yyval, YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-11)].yystate.yysemantics.yyval, YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-9)].yystate.yysemantics.yyval, YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-7)].yystate.yysemantics.yyval, YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-5)].yystate.yysemantics.yyval, YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-3)].yystate.yysemantics.yyval, YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yysemantics.yyval); }
#line 3906 "ned2.tab.cc"
    break;

  case 320: /* identifier: NAME  */
#line 1626 "ned2.y"
                { if (np->getParseExpressionsFlag()) (*yyvalp) = createIdent(np, (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yyloc)); }
#line 3912 "ned2.tab.cc"
    break;

  case 321: /* identifier: THIS_ '.' NAME  */
#line 1628 "ned2.y"
                { if (np->getParseExpressionsFlag()) (*yyvalp) = createIdent(np, (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yyloc), (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-2)].yystate.yyloc)); }
#line 3918 "ned2.tab.cc"
    break;

  case 322: /* identifier: PARENT '.' NAME  */
#line 1630 "ned2.y"
                { if (np->getParseExpressionsFlag()) (*yyvalp) = createIdent(np, (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yyloc), (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-2)].yystate.yyloc)); }
#line 3924 "ned2.tab.cc"
    break;

  case 323: /* identifier: NAME '.' NAME  */
#line 1632 "ned2.y"
                { if (np->getParseExpressionsFlag()) (*yyvalp) = createIdent(np, (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yyloc), (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-2)].yystate.yyloc)); }
#line 3930 "ned2.tab.cc"
    break;

  case 324: /* identifier: NAME '[' expr ']' '.' NAME  */
#line 1634 "ned2.y"
                { if (np->getParseExpressionsFlag()) (*yyvalp) = createIdent(np, (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yyloc), (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-5)].yystate.yyloc), YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-3)].yystate.yysemantics.yyval); }
#line 3936 "ned2.tab.cc"
    break;

  case 325: /* identifier: PARENT '.' NAME '.' NAME  */
#line 1636 "ned2.y"
                { if (np->getParseExpressionsFlag()) (*yyvalp) = createIdent(np, (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yyloc), (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-2)].yystate.yyloc)); }
#line 3942 "ned2.tab.cc"
    break;

  case 326: /* identifier: PARENT '.' NAME '[' expr ']' '.' NAME  */
#line 1638 "ned2.y"
                { if (np->getParseExpressionsFlag()) (*yyvalp) = createIdent(np, (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yyloc), (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-5)].yystate.yyloc), YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-3)].yystate.yysemantics.yyval); }
#line 3948 "ned2.tab.cc"
    break;

  case 327: /* operator: INDEX_  */
#line 1643 "ned2.y"
                { if (np->getParseExpressionsFlag()) (*yyvalp) = createFunction(np, "index"); }
#line 3954 "ned2.tab.cc"
    break;

  case 328: /* operator: INDEX_ '(' ')'  */
#line 1645 "ned2.y"
                { if (np->getParseExpressionsFlag()) (*yyvalp) = createFunction(np, "index"); }
#line 3960 "ned2.tab.cc"
    break;

  case 329: /* operator: EXISTS '(' identifier ')'  */
#line 1647 "ned2.y"
                { if (np->getParseExpressionsFlag()) (*yyvalp) = createFunction(np, "exists", YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yysemantics.yyval); }
#line 3966 "ned2.tab.cc"
    break;

  case 330: /* operator: SIZEOF '(' identifier ')'  */
#line 1649 "ned2.y"
                { if (np->getParseExpressionsFlag()) (*yyvalp) = createFunction(np, "sizeof", YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yysemantics.yyval); }
#line 3972 "ned2.tab.cc"
    break;

  case 331: /* operator: TYPENAME  */
#line 1651 "ned2.y"
                { if (np->getParseExpressionsFlag()) (*yyvalp) = createFunction(np, "typename"); }
#line 3978 "ned2.tab.cc"
    break;

  case 335: /* stringliteral: STRINGCONSTANT  */
#line 1662 "ned2.y"
                { if (np->getParseExpressionsFlag()) (*yyvalp) = createStringLiteral(np, (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yyloc)); }
#line 3984 "ned2.tab.cc"
    break;

  case 336: /* boolliteral: TRUE_  */
#line 1667 "ned2.y"
                { if (np->getParseExpressionsFlag()) (*yyvalp) = createLiteral(np, LIT_BOOL, (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yyloc), (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yyloc)); }
#line 3990 "ned2.tab.cc"
    break;

  case 337: /* boolliteral: FALSE_  */
#line 1669 "ned2.y"
                { if (np->getParseExpressionsFlag()) (*yyvalp) = createLiteral(np, LIT_BOOL, (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yyloc), (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yyloc)); }
#line 3996 "ned2.tab.cc"
    break;

  case 338: /* numliteral: INTCONSTANT  */
#line 1674 "ned2.y"
                { if (np->getParseExpressionsFlag()) (*yyvalp) = createLiteral(np, LIT_INT, (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yyloc), (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yyloc)); }
#line 4002 "ned2.tab.cc"
    break;

  case 339: /* numliteral: realconstant_ext  */
#line 1676 "ned2.y"
                { if (np->getParseExpressionsFlag()) (*yyvalp) = createLiteral(np, LIT_DOUBLE, (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yyloc), (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yyloc)); }
#line 4008 "ned2.tab.cc"
    break;

  case 340: /* numliteral: quantity  */
#line 1678 "ned2.y"
                { if (np->getParseExpressionsFlag()) (*yyvalp) = createQuantityLiteral(np, (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yyloc)); }
#line 4014 "ned2.tab.cc"
    break;


#line 4018 "ned2.tab.cc"

      default: break;
    }
  YY_SYMBOL_PRINT ("-> $$ =", yylhsNonterm (yyrule), yyvalp, yylocp);

  return yyok;
# undef yyerrok
# undef YYABORT
# undef YYACCEPT
# undef YYNOMEM
# undef YYERROR
# undef YYBACKUP
# undef yyclearin
# undef YYRECOVERING
}


static void
yyuserMerge (int yyn, YYSTYPE* yy0, YYSTYPE* yy1)
{
  YY_USE (yy0);
  YY_USE (yy1);

  switch (yyn)
    {

      default: break;
    }
}

                              /* Bison grammar-table manipulation.  */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg,
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep, YYLTYPE *yylocationp, omnetpp::nedxml::ParseContext *np)
{
  YY_USE (yyvaluep);
  YY_USE (yylocationp);
  YY_USE (np);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}

/** Number of symbols composing the right hand side of rule #RULE.  */
static inline int
yyrhsLength (yyRuleNum yyrule)
{
  return yyr2[yyrule];
}

static void
yydestroyGLRState (char const *yymsg, yyGLRState *yys, omnetpp::nedxml::ParseContext *np)
{
  if (yys->yyresolved)
    yydestruct (yymsg, yy_accessing_symbol (yys->yylrState),
                &yys->yysemantics.yyval, &yys->yyloc, np);
  else
    {
#if YYDEBUG
      if (yydebug)
        {
          if (yys->yysemantics.yyfirstVal)
            YY_FPRINTF ((stderr, "%s unresolved", yymsg));
          else
            YY_FPRINTF ((stderr, "%s incomplete", yymsg));
          YY_SYMBOL_PRINT ("", yy_accessing_symbol (yys->yylrState), YY_NULLPTR, &yys->yyloc);
        }
#endif

      if (yys->yysemantics.yyfirstVal)
        {
          yySemanticOption *yyoption = yys->yysemantics.yyfirstVal;
          yyGLRState *yyrh;
          int yyn;
          for (yyrh = yyoption->yystate, yyn = yyrhsLength (yyoption->yyrule);
               yyn > 0;
               yyrh = yyrh->yypred, yyn -= 1)
            yydestroyGLRState (yymsg, yyrh, np);
        }
    }
}

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

/** True iff LR state YYSTATE has only a default reduction (regardless
 *  of token).  */
static inline yybool
yyisDefaultedState (yy_state_t yystate)
{
  return yypact_value_is_default (yypact[yystate]);
}

/** The default reduction for YYSTATE, assuming it has one.  */
static inline yyRuleNum
yydefaultAction (yy_state_t yystate)
{
  return yydefact[yystate];
}

#define yytable_value_is_error(Yyn) \
  0

/** The action to take in YYSTATE on seeing YYTOKEN.
 *  Result R means
 *    R < 0:  Reduce on rule -R.
 *    R = 0:  Error.
 *    R > 0:  Shift to state R.
 *  Set *YYCONFLICTS to a pointer into yyconfl to a 0-terminated list
 *  of conflicting reductions.
 */
static inline int
yygetLRActions (yy_state_t yystate, yysymbol_kind_t yytoken, const short** yyconflicts)
{
  int yyindex = yypact[yystate] + yytoken;
  if (yytoken == YYSYMBOL_YYerror)
    {
      // This is the error token.
      *yyconflicts = yyconfl;
      return 0;
    }
  else if (yyisDefaultedState (yystate)
           || yyindex < 0 || YYLAST < yyindex || yycheck[yyindex] != yytoken)
    {
      *yyconflicts = yyconfl;
      return -yydefact[yystate];
    }
  else if (! yytable_value_is_error (yytable[yyindex]))
    {
      *yyconflicts = yyconfl + yyconflp[yyindex];
      return yytable[yyindex];
    }
  else
    {
      *yyconflicts = yyconfl + yyconflp[yyindex];
      return 0;
    }
}

/** Compute post-reduction state.
 * \param yystate   the current state
 * \param yysym     the nonterminal to push on the stack
 */
static inline yy_state_t
yyLRgotoState (yy_state_t yystate, yysymbol_kind_t yysym)
{
  int yyr = yypgoto[yysym - YYNTOKENS] + yystate;
  if (0 <= yyr && yyr <= YYLAST && yycheck[yyr] == yystate)
    return yytable[yyr];
  else
    return yydefgoto[yysym - YYNTOKENS];
}

static inline yybool
yyisShiftAction (int yyaction)
{
  return 0 < yyaction;
}

static inline yybool
yyisErrorAction (int yyaction)
{
  return yyaction == 0;
}

                                /* GLRStates */

/** Return a fresh GLRStackItem in YYSTACKP.  The item is an LR state
 *  if YYISSTATE, and otherwise a semantic option.  Callers should call
 *  YY_RESERVE_GLRSTACK afterwards to make sure there is sufficient
 *  headroom.  */

static inline yyGLRStackItem*
yynewGLRStackItem (yyGLRStack* yystackp, yybool yyisState)
{
  yyGLRStackItem* yynewItem = yystackp->yynextFree;
  yystackp->yyspaceLeft -= 1;
  yystackp->yynextFree += 1;
  yynewItem->yystate.yyisState = yyisState;
  return yynewItem;
}

/** Add a new semantic action that will execute the action for rule
 *  YYRULE on the semantic values in YYRHS to the list of
 *  alternative actions for YYSTATE.  Assumes that YYRHS comes from
 *  stack #YYK of *YYSTACKP. */
static void
yyaddDeferredAction (yyGLRStack* yystackp, YYPTRDIFF_T yyk, yyGLRState* yystate,
                     yyGLRState* yyrhs, yyRuleNum yyrule)
{
  yySemanticOption* yynewOption =
    &yynewGLRStackItem (yystackp, yyfalse)->yyoption;
  YY_ASSERT (!yynewOption->yyisState);
  yynewOption->yystate = yyrhs;
  yynewOption->yyrule = yyrule;
  if (yystackp->yytops.yylookaheadNeeds[yyk])
    {
      yynewOption->yyrawchar = yychar;
      yynewOption->yyval = yylval;
      yynewOption->yyloc = yylloc;
    }
  else
    yynewOption->yyrawchar = YYEMPTY;
  yynewOption->yynext = yystate->yysemantics.yyfirstVal;
  yystate->yysemantics.yyfirstVal = yynewOption;

  YY_RESERVE_GLRSTACK (yystackp);
}

                                /* GLRStacks */

/** Initialize YYSET to a singleton set containing an empty stack.  */
static yybool
yyinitStateSet (yyGLRStateSet* yyset)
{
  yyset->yysize = 1;
  yyset->yycapacity = 16;
  yyset->yystates
    = YY_CAST (yyGLRState**,
               YYMALLOC (YY_CAST (YYSIZE_T, yyset->yycapacity)
                         * sizeof yyset->yystates[0]));
  if (! yyset->yystates)
    return yyfalse;
  yyset->yystates[0] = YY_NULLPTR;
  yyset->yylookaheadNeeds
    = YY_CAST (yybool*,
               YYMALLOC (YY_CAST (YYSIZE_T, yyset->yycapacity)
                         * sizeof yyset->yylookaheadNeeds[0]));
  if (! yyset->yylookaheadNeeds)
    {
      YYFREE (yyset->yystates);
      return yyfalse;
    }
  memset (yyset->yylookaheadNeeds,
          0,
          YY_CAST (YYSIZE_T, yyset->yycapacity) * sizeof yyset->yylookaheadNeeds[0]);
  return yytrue;
}

static void yyfreeStateSet (yyGLRStateSet* yyset)
{
  YYFREE (yyset->yystates);
  YYFREE (yyset->yylookaheadNeeds);
}

/** Initialize *YYSTACKP to a single empty stack, with total maximum
 *  capacity for all stacks of YYSIZE.  */
static yybool
yyinitGLRStack (yyGLRStack* yystackp, YYPTRDIFF_T yysize)
{
  yystackp->yyerrState = 0;
  yynerrs = 0;
  yystackp->yyspaceLeft = yysize;
  yystackp->yyitems
    = YY_CAST (yyGLRStackItem*,
               YYMALLOC (YY_CAST (YYSIZE_T, yysize)
                         * sizeof yystackp->yynextFree[0]));
  if (!yystackp->yyitems)
    return yyfalse;
  yystackp->yynextFree = yystackp->yyitems;
  yystackp->yysplitPoint = YY_NULLPTR;
  yystackp->yylastDeleted = YY_NULLPTR;
  return yyinitStateSet (&yystackp->yytops);
}


#if YYSTACKEXPANDABLE
# define YYRELOC(YYFROMITEMS, YYTOITEMS, YYX, YYTYPE)                   \
  &((YYTOITEMS)                                                         \
    - ((YYFROMITEMS) - YY_REINTERPRET_CAST (yyGLRStackItem*, (YYX))))->YYTYPE

/** If *YYSTACKP is expandable, extend it.  WARNING: Pointers into the
    stack from outside should be considered invalid after this call.
    We always expand when there are 1 or fewer items left AFTER an
    allocation, so that we can avoid having external pointers exist
    across an allocation.  */
static void
yyexpandGLRStack (yyGLRStack* yystackp)
{
  yyGLRStackItem* yynewItems;
  yyGLRStackItem* yyp0, *yyp1;
  YYPTRDIFF_T yynewSize;
  YYPTRDIFF_T yyn;
  YYPTRDIFF_T yysize = yystackp->yynextFree - yystackp->yyitems;
  if (YYMAXDEPTH - YYHEADROOM < yysize)
    yyMemoryExhausted (yystackp);
  yynewSize = 2*yysize;
  if (YYMAXDEPTH < yynewSize)
    yynewSize = YYMAXDEPTH;
  yynewItems
    = YY_CAST (yyGLRStackItem*,
               YYMALLOC (YY_CAST (YYSIZE_T, yynewSize)
                         * sizeof yynewItems[0]));
  if (! yynewItems)
    yyMemoryExhausted (yystackp);
  for (yyp0 = yystackp->yyitems, yyp1 = yynewItems, yyn = yysize;
       0 < yyn;
       yyn -= 1, yyp0 += 1, yyp1 += 1)
    {
      *yyp1 = *yyp0;
      if (*YY_REINTERPRET_CAST (yybool *, yyp0))
        {
          yyGLRState* yys0 = &yyp0->yystate;
          yyGLRState* yys1 = &yyp1->yystate;
          if (yys0->yypred != YY_NULLPTR)
            yys1->yypred =
              YYRELOC (yyp0, yyp1, yys0->yypred, yystate);
          if (! yys0->yyresolved && yys0->yysemantics.yyfirstVal != YY_NULLPTR)
            yys1->yysemantics.yyfirstVal =
              YYRELOC (yyp0, yyp1, yys0->yysemantics.yyfirstVal, yyoption);
        }
      else
        {
          yySemanticOption* yyv0 = &yyp0->yyoption;
          yySemanticOption* yyv1 = &yyp1->yyoption;
          if (yyv0->yystate != YY_NULLPTR)
            yyv1->yystate = YYRELOC (yyp0, yyp1, yyv0->yystate, yystate);
          if (yyv0->yynext != YY_NULLPTR)
            yyv1->yynext = YYRELOC (yyp0, yyp1, yyv0->yynext, yyoption);
        }
    }
  if (yystackp->yysplitPoint != YY_NULLPTR)
    yystackp->yysplitPoint = YYRELOC (yystackp->yyitems, yynewItems,
                                      yystackp->yysplitPoint, yystate);

  for (yyn = 0; yyn < yystackp->yytops.yysize; yyn += 1)
    if (yystackp->yytops.yystates[yyn] != YY_NULLPTR)
      yystackp->yytops.yystates[yyn] =
        YYRELOC (yystackp->yyitems, yynewItems,
                 yystackp->yytops.yystates[yyn], yystate);
  YYFREE (yystackp->yyitems);
  yystackp->yyitems = yynewItems;
  yystackp->yynextFree = yynewItems + yysize;
  yystackp->yyspaceLeft = yynewSize - yysize;
}
#endif

static void
yyfreeGLRStack (yyGLRStack* yystackp)
{
  YYFREE (yystackp->yyitems);
  yyfreeStateSet (&yystackp->yytops);
}

/** Assuming that YYS is a GLRState somewhere on *YYSTACKP, update the
 *  splitpoint of *YYSTACKP, if needed, so that it is at least as deep as
 *  YYS.  */
static inline void
yyupdateSplit (yyGLRStack* yystackp, yyGLRState* yys)
{
  if (yystackp->yysplitPoint != YY_NULLPTR && yystackp->yysplitPoint > yys)
    yystackp->yysplitPoint = yys;
}

/** Invalidate stack #YYK in *YYSTACKP.  */
static inline void
yymarkStackDeleted (yyGLRStack* yystackp, YYPTRDIFF_T yyk)
{
  if (yystackp->yytops.yystates[yyk] != YY_NULLPTR)
    yystackp->yylastDeleted = yystackp->yytops.yystates[yyk];
  yystackp->yytops.yystates[yyk] = YY_NULLPTR;
}

/** Undelete the last stack in *YYSTACKP that was marked as deleted.  Can
    only be done once after a deletion, and only when all other stacks have
    been deleted.  */
static void
yyundeleteLastStack (yyGLRStack* yystackp)
{
  if (yystackp->yylastDeleted == YY_NULLPTR || yystackp->yytops.yysize != 0)
    return;
  yystackp->yytops.yystates[0] = yystackp->yylastDeleted;
  yystackp->yytops.yysize = 1;
  YY_DPRINTF ((stderr, "Restoring last deleted stack as stack #0.\n"));
  yystackp->yylastDeleted = YY_NULLPTR;
}

static inline void
yyremoveDeletes (yyGLRStack* yystackp)
{
  YYPTRDIFF_T yyi, yyj;
  yyi = yyj = 0;
  while (yyj < yystackp->yytops.yysize)
    {
      if (yystackp->yytops.yystates[yyi] == YY_NULLPTR)
        {
          if (yyi == yyj)
            YY_DPRINTF ((stderr, "Removing dead stacks.\n"));
          yystackp->yytops.yysize -= 1;
        }
      else
        {
          yystackp->yytops.yystates[yyj] = yystackp->yytops.yystates[yyi];
          /* In the current implementation, it's unnecessary to copy
             yystackp->yytops.yylookaheadNeeds[yyi] since, after
             yyremoveDeletes returns, the parser immediately either enters
             deterministic operation or shifts a token.  However, it doesn't
             hurt, and the code might evolve to need it.  */
          yystackp->yytops.yylookaheadNeeds[yyj] =
            yystackp->yytops.yylookaheadNeeds[yyi];
          if (yyj != yyi)
            YY_DPRINTF ((stderr, "Rename stack %ld -> %ld.\n",
                        YY_CAST (long, yyi), YY_CAST (long, yyj)));
          yyj += 1;
        }
      yyi += 1;
    }
}

/** Shift to a new state on stack #YYK of *YYSTACKP, corresponding to LR
 * state YYLRSTATE, at input position YYPOSN, with (resolved) semantic
 * value *YYVALP and source location *YYLOCP.  */
static inline void
yyglrShift (yyGLRStack* yystackp, YYPTRDIFF_T yyk, yy_state_t yylrState,
            YYPTRDIFF_T yyposn,
            YYSTYPE* yyvalp, YYLTYPE* yylocp)
{
  yyGLRState* yynewState = &yynewGLRStackItem (yystackp, yytrue)->yystate;

  yynewState->yylrState = yylrState;
  yynewState->yyposn = yyposn;
  yynewState->yyresolved = yytrue;
  yynewState->yypred = yystackp->yytops.yystates[yyk];
  yynewState->yysemantics.yyval = *yyvalp;
  yynewState->yyloc = *yylocp;
  yystackp->yytops.yystates[yyk] = yynewState;

  YY_RESERVE_GLRSTACK (yystackp);
}

/** Shift stack #YYK of *YYSTACKP, to a new state corresponding to LR
 *  state YYLRSTATE, at input position YYPOSN, with the (unresolved)
 *  semantic value of YYRHS under the action for YYRULE.  */
static inline void
yyglrShiftDefer (yyGLRStack* yystackp, YYPTRDIFF_T yyk, yy_state_t yylrState,
                 YYPTRDIFF_T yyposn, yyGLRState* yyrhs, yyRuleNum yyrule)
{
  yyGLRState* yynewState = &yynewGLRStackItem (yystackp, yytrue)->yystate;
  YY_ASSERT (yynewState->yyisState);

  yynewState->yylrState = yylrState;
  yynewState->yyposn = yyposn;
  yynewState->yyresolved = yyfalse;
  yynewState->yypred = yystackp->yytops.yystates[yyk];
  yynewState->yysemantics.yyfirstVal = YY_NULLPTR;
  yystackp->yytops.yystates[yyk] = yynewState;

  /* Invokes YY_RESERVE_GLRSTACK.  */
  yyaddDeferredAction (yystackp, yyk, yynewState, yyrhs, yyrule);
}

#if YYDEBUG

/*----------------------------------------------------------------------.
| Report that stack #YYK of *YYSTACKP is going to be reduced by YYRULE. |
`----------------------------------------------------------------------*/

static inline void
yy_reduce_print (yybool yynormal, yyGLRStackItem* yyvsp, YYPTRDIFF_T yyk,
                 yyRuleNum yyrule, omnetpp::nedxml::ParseContext *np)
{
  int yynrhs = yyrhsLength (yyrule);
  int yylow = 1;
  int yyi;
  YY_FPRINTF ((stderr, "Reducing stack %ld by rule %d (line %d):\n",
               YY_CAST (long, yyk), yyrule - 1, yyrline[yyrule]));
  if (! yynormal)
    yyfillin (yyvsp, 1, -yynrhs);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YY_FPRINTF ((stderr, "   $%d = ", yyi + 1));
      yy_symbol_print (stderr,
                       yy_accessing_symbol (yyvsp[yyi - yynrhs + 1].yystate.yylrState),
                       &yyvsp[yyi - yynrhs + 1].yystate.yysemantics.yyval,
                       &(YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL ((yyi + 1) - (yynrhs))].yystate.yyloc)                       , np);
      if (!yyvsp[yyi - yynrhs + 1].yystate.yyresolved)
        YY_FPRINTF ((stderr, " (unresolved)"));
      YY_FPRINTF ((stderr, "\n"));
    }
}
#endif

/** Pop the symbols consumed by reduction #YYRULE from the top of stack
 *  #YYK of *YYSTACKP, and perform the appropriate semantic action on their
 *  semantic values.  Assumes that all ambiguities in semantic values
 *  have been previously resolved.  Set *YYVALP to the resulting value,
 *  and *YYLOCP to the computed location (if any).  Return value is as
 *  for userAction.  */
static inline YYRESULTTAG
yydoAction (yyGLRStack* yystackp, YYPTRDIFF_T yyk, yyRuleNum yyrule,
            YYSTYPE* yyvalp, YYLTYPE *yylocp, omnetpp::nedxml::ParseContext *np)
{
  int yynrhs = yyrhsLength (yyrule);

  if (yystackp->yysplitPoint == YY_NULLPTR)
    {
      /* Standard special case: single stack.  */
      yyGLRStackItem* yyrhs
        = YY_REINTERPRET_CAST (yyGLRStackItem*, yystackp->yytops.yystates[yyk]);
      YY_ASSERT (yyk == 0);
      yystackp->yynextFree -= yynrhs;
      yystackp->yyspaceLeft += yynrhs;
      yystackp->yytops.yystates[0] = & yystackp->yynextFree[-1].yystate;
      return yyuserAction (yyrule, yynrhs, yyrhs, yystackp, yyk,
                           yyvalp, yylocp, np);
    }
  else
    {
      yyGLRStackItem yyrhsVals[YYMAXRHS + YYMAXLEFT + 1];
      yyGLRState* yys = yyrhsVals[YYMAXRHS + YYMAXLEFT].yystate.yypred
        = yystackp->yytops.yystates[yyk];
      int yyi;
      if (yynrhs == 0)
        /* Set default location.  */
        yyrhsVals[YYMAXRHS + YYMAXLEFT - 1].yystate.yyloc = yys->yyloc;
      for (yyi = 0; yyi < yynrhs; yyi += 1)
        {
          yys = yys->yypred;
          YY_ASSERT (yys);
        }
      yyupdateSplit (yystackp, yys);
      yystackp->yytops.yystates[yyk] = yys;
      return yyuserAction (yyrule, yynrhs, yyrhsVals + YYMAXRHS + YYMAXLEFT - 1,
                           yystackp, yyk, yyvalp, yylocp, np);
    }
}

/** Pop items off stack #YYK of *YYSTACKP according to grammar rule YYRULE,
 *  and push back on the resulting nonterminal symbol.  Perform the
 *  semantic action associated with YYRULE and store its value with the
 *  newly pushed state, if YYFORCEEVAL or if *YYSTACKP is currently
 *  unambiguous.  Otherwise, store the deferred semantic action with
 *  the new state.  If the new state would have an identical input
 *  position, LR state, and predecessor to an existing state on the stack,
 *  it is identified with that existing state, eliminating stack #YYK from
 *  *YYSTACKP.  In this case, the semantic value is
 *  added to the options for the existing state's semantic value.
 */
static inline YYRESULTTAG
yyglrReduce (yyGLRStack* yystackp, YYPTRDIFF_T yyk, yyRuleNum yyrule,
             yybool yyforceEval, omnetpp::nedxml::ParseContext *np)
{
  YYPTRDIFF_T yyposn = yystackp->yytops.yystates[yyk]->yyposn;

  if (yyforceEval || yystackp->yysplitPoint == YY_NULLPTR)
    {
      YYSTYPE yyval;
      YYLTYPE yyloc;

      YYRESULTTAG yyflag = yydoAction (yystackp, yyk, yyrule, &yyval, &yyloc, np);
      if (yyflag == yyerr && yystackp->yysplitPoint != YY_NULLPTR)
        YY_DPRINTF ((stderr,
                     "Parse on stack %ld rejected by rule %d (line %d).\n",
                     YY_CAST (long, yyk), yyrule - 1, yyrline[yyrule]));
      if (yyflag != yyok)
        return yyflag;
      yyglrShift (yystackp, yyk,
                  yyLRgotoState (yystackp->yytops.yystates[yyk]->yylrState,
                                 yylhsNonterm (yyrule)),
                  yyposn, &yyval, &yyloc);
    }
  else
    {
      YYPTRDIFF_T yyi;
      int yyn;
      yyGLRState* yys, *yys0 = yystackp->yytops.yystates[yyk];
      yy_state_t yynewLRState;

      for (yys = yystackp->yytops.yystates[yyk], yyn = yyrhsLength (yyrule);
           0 < yyn; yyn -= 1)
        {
          yys = yys->yypred;
          YY_ASSERT (yys);
        }
      yyupdateSplit (yystackp, yys);
      yynewLRState = yyLRgotoState (yys->yylrState, yylhsNonterm (yyrule));
      YY_DPRINTF ((stderr,
                   "Reduced stack %ld by rule %d (line %d); action deferred.  "
                   "Now in state %d.\n",
                   YY_CAST (long, yyk), yyrule - 1, yyrline[yyrule],
                   yynewLRState));
      for (yyi = 0; yyi < yystackp->yytops.yysize; yyi += 1)
        if (yyi != yyk && yystackp->yytops.yystates[yyi] != YY_NULLPTR)
          {
            yyGLRState *yysplit = yystackp->yysplitPoint;
            yyGLRState *yyp = yystackp->yytops.yystates[yyi];
            while (yyp != yys && yyp != yysplit && yyp->yyposn >= yyposn)
              {
                if (yyp->yylrState == yynewLRState && yyp->yypred == yys)
                  {
                    yyaddDeferredAction (yystackp, yyk, yyp, yys0, yyrule);
                    yymarkStackDeleted (yystackp, yyk);
                    YY_DPRINTF ((stderr, "Merging stack %ld into stack %ld.\n",
                                 YY_CAST (long, yyk), YY_CAST (long, yyi)));
                    return yyok;
                  }
                yyp = yyp->yypred;
              }
          }
      yystackp->yytops.yystates[yyk] = yys;
      yyglrShiftDefer (yystackp, yyk, yynewLRState, yyposn, yys0, yyrule);
    }
  return yyok;
}

static YYPTRDIFF_T
yysplitStack (yyGLRStack* yystackp, YYPTRDIFF_T yyk)
{
  if (yystackp->yysplitPoint == YY_NULLPTR)
    {
      YY_ASSERT (yyk == 0);
      yystackp->yysplitPoint = yystackp->yytops.yystates[yyk];
    }
  if (yystackp->yytops.yycapacity <= yystackp->yytops.yysize)
    {
      YYPTRDIFF_T state_size = YYSIZEOF (yystackp->yytops.yystates[0]);
      YYPTRDIFF_T half_max_capacity = YYSIZE_MAXIMUM / 2 / state_size;
      if (half_max_capacity < yystackp->yytops.yycapacity)
        yyMemoryExhausted (yystackp);
      yystackp->yytops.yycapacity *= 2;

      {
        yyGLRState** yynewStates
          = YY_CAST (yyGLRState**,
                     YYREALLOC (yystackp->yytops.yystates,
                                (YY_CAST (YYSIZE_T, yystackp->yytops.yycapacity)
                                 * sizeof yynewStates[0])));
        if (yynewStates == YY_NULLPTR)
          yyMemoryExhausted (yystackp);
        yystackp->yytops.yystates = yynewStates;
      }

      {
        yybool* yynewLookaheadNeeds
          = YY_CAST (yybool*,
                     YYREALLOC (yystackp->yytops.yylookaheadNeeds,
                                (YY_CAST (YYSIZE_T, yystackp->yytops.yycapacity)
                                 * sizeof yynewLookaheadNeeds[0])));
        if (yynewLookaheadNeeds == YY_NULLPTR)
          yyMemoryExhausted (yystackp);
        yystackp->yytops.yylookaheadNeeds = yynewLookaheadNeeds;
      }
    }
  yystackp->yytops.yystates[yystackp->yytops.yysize]
    = yystackp->yytops.yystates[yyk];
  yystackp->yytops.yylookaheadNeeds[yystackp->yytops.yysize]
    = yystackp->yytops.yylookaheadNeeds[yyk];
  yystackp->yytops.yysize += 1;
  return yystackp->yytops.yysize - 1;
}

/** True iff YYY0 and YYY1 represent identical options at the top level.
 *  That is, they represent the same rule applied to RHS symbols
 *  that produce the same terminal symbols.  */
static yybool
yyidenticalOptions (yySemanticOption* yyy0, yySemanticOption* yyy1)
{
  if (yyy0->yyrule == yyy1->yyrule)
    {
      yyGLRState *yys0, *yys1;
      int yyn;
      for (yys0 = yyy0->yystate, yys1 = yyy1->yystate,
           yyn = yyrhsLength (yyy0->yyrule);
           yyn > 0;
           yys0 = yys0->yypred, yys1 = yys1->yypred, yyn -= 1)
        if (yys0->yyposn != yys1->yyposn)
          return yyfalse;
      return yytrue;
    }
  else
    return yyfalse;
}

/** Assuming identicalOptions (YYY0,YYY1), destructively merge the
 *  alternative semantic values for the RHS-symbols of YYY1 and YYY0.  */
static void
yymergeOptionSets (yySemanticOption* yyy0, yySemanticOption* yyy1)
{
  yyGLRState *yys0, *yys1;
  int yyn;
  for (yys0 = yyy0->yystate, yys1 = yyy1->yystate,
       yyn = yyrhsLength (yyy0->yyrule);
       0 < yyn;
       yys0 = yys0->yypred, yys1 = yys1->yypred, yyn -= 1)
    {
      if (yys0 == yys1)
        break;
      else if (yys0->yyresolved)
        {
          yys1->yyresolved = yytrue;
          yys1->yysemantics.yyval = yys0->yysemantics.yyval;
        }
      else if (yys1->yyresolved)
        {
          yys0->yyresolved = yytrue;
          yys0->yysemantics.yyval = yys1->yysemantics.yyval;
        }
      else
        {
          yySemanticOption** yyz0p = &yys0->yysemantics.yyfirstVal;
          yySemanticOption* yyz1 = yys1->yysemantics.yyfirstVal;
          while (yytrue)
            {
              if (yyz1 == *yyz0p || yyz1 == YY_NULLPTR)
                break;
              else if (*yyz0p == YY_NULLPTR)
                {
                  *yyz0p = yyz1;
                  break;
                }
              else if (*yyz0p < yyz1)
                {
                  yySemanticOption* yyz = *yyz0p;
                  *yyz0p = yyz1;
                  yyz1 = yyz1->yynext;
                  (*yyz0p)->yynext = yyz;
                }
              yyz0p = &(*yyz0p)->yynext;
            }
          yys1->yysemantics.yyfirstVal = yys0->yysemantics.yyfirstVal;
        }
    }
}

/** Y0 and Y1 represent two possible actions to take in a given
 *  parsing state; return 0 if no combination is possible,
 *  1 if user-mergeable, 2 if Y0 is preferred, 3 if Y1 is preferred.  */
static int
yypreference (yySemanticOption* y0, yySemanticOption* y1)
{
  yyRuleNum r0 = y0->yyrule, r1 = y1->yyrule;
  int p0 = yydprec[r0], p1 = yydprec[r1];

  if (p0 == p1)
    {
      if (yymerger[r0] == 0 || yymerger[r0] != yymerger[r1])
        return 0;
      else
        return 1;
    }
  if (p0 == 0 || p1 == 0)
    return 0;
  if (p0 < p1)
    return 3;
  if (p1 < p0)
    return 2;
  return 0;
}

static YYRESULTTAG
yyresolveValue (yyGLRState* yys, yyGLRStack* yystackp, omnetpp::nedxml::ParseContext *np);


/** Resolve the previous YYN states starting at and including state YYS
 *  on *YYSTACKP. If result != yyok, some states may have been left
 *  unresolved possibly with empty semantic option chains.  Regardless
 *  of whether result = yyok, each state has been left with consistent
 *  data so that yydestroyGLRState can be invoked if necessary.  */
static YYRESULTTAG
yyresolveStates (yyGLRState* yys, int yyn,
                 yyGLRStack* yystackp, omnetpp::nedxml::ParseContext *np)
{
  if (0 < yyn)
    {
      YY_ASSERT (yys->yypred);
      YYCHK (yyresolveStates (yys->yypred, yyn-1, yystackp, np));
      if (! yys->yyresolved)
        YYCHK (yyresolveValue (yys, yystackp, np));
    }
  return yyok;
}

/** Resolve the states for the RHS of YYOPT on *YYSTACKP, perform its
 *  user action, and return the semantic value and location in *YYVALP
 *  and *YYLOCP.  Regardless of whether result = yyok, all RHS states
 *  have been destroyed (assuming the user action destroys all RHS
 *  semantic values if invoked).  */
static YYRESULTTAG
yyresolveAction (yySemanticOption* yyopt, yyGLRStack* yystackp,
                 YYSTYPE* yyvalp, YYLTYPE *yylocp, omnetpp::nedxml::ParseContext *np)
{
  yyGLRStackItem yyrhsVals[YYMAXRHS + YYMAXLEFT + 1];
  int yynrhs = yyrhsLength (yyopt->yyrule);
  YYRESULTTAG yyflag =
    yyresolveStates (yyopt->yystate, yynrhs, yystackp, np);
  if (yyflag != yyok)
    {
      yyGLRState *yys;
      for (yys = yyopt->yystate; yynrhs > 0; yys = yys->yypred, yynrhs -= 1)
        yydestroyGLRState ("Cleanup: popping", yys, np);
      return yyflag;
    }

  yyrhsVals[YYMAXRHS + YYMAXLEFT].yystate.yypred = yyopt->yystate;
  if (yynrhs == 0)
    /* Set default location.  */
    yyrhsVals[YYMAXRHS + YYMAXLEFT - 1].yystate.yyloc = yyopt->yystate->yyloc;
  {
    int yychar_current = yychar;
    YYSTYPE yylval_current = yylval;
    YYLTYPE yylloc_current = yylloc;
    yychar = yyopt->yyrawchar;
    yylval = yyopt->yyval;
    yylloc = yyopt->yyloc;
    yyflag = yyuserAction (yyopt->yyrule, yynrhs,
                           yyrhsVals + YYMAXRHS + YYMAXLEFT - 1,
                           yystackp, -1, yyvalp, yylocp, np);
    yychar = yychar_current;
    yylval = yylval_current;
    yylloc = yylloc_current;
  }
  return yyflag;
}

#if YYDEBUG
static void
yyreportTree (yySemanticOption* yyx, int yyindent)
{
  int yynrhs = yyrhsLength (yyx->yyrule);
  int yyi;
  yyGLRState* yys;
  yyGLRState* yystates[1 + YYMAXRHS];
  yyGLRState yyleftmost_state;

  for (yyi = yynrhs, yys = yyx->yystate; 0 < yyi; yyi -= 1, yys = yys->yypred)
    yystates[yyi] = yys;
  if (yys == YY_NULLPTR)
    {
      yyleftmost_state.yyposn = 0;
      yystates[0] = &yyleftmost_state;
    }
  else
    yystates[0] = yys;

  if (yyx->yystate->yyposn < yys->yyposn + 1)
    YY_FPRINTF ((stderr, "%*s%s -> <Rule %d, empty>\n",
                 yyindent, "", yysymbol_name (yylhsNonterm (yyx->yyrule)),
                 yyx->yyrule - 1));
  else
    YY_FPRINTF ((stderr, "%*s%s -> <Rule %d, tokens %ld .. %ld>\n",
                 yyindent, "", yysymbol_name (yylhsNonterm (yyx->yyrule)),
                 yyx->yyrule - 1, YY_CAST (long, yys->yyposn + 1),
                 YY_CAST (long, yyx->yystate->yyposn)));
  for (yyi = 1; yyi <= yynrhs; yyi += 1)
    {
      if (yystates[yyi]->yyresolved)
        {
          if (yystates[yyi-1]->yyposn+1 > yystates[yyi]->yyposn)
            YY_FPRINTF ((stderr, "%*s%s <empty>\n", yyindent+2, "",
                         yysymbol_name (yy_accessing_symbol (yystates[yyi]->yylrState))));
          else
            YY_FPRINTF ((stderr, "%*s%s <tokens %ld .. %ld>\n", yyindent+2, "",
                         yysymbol_name (yy_accessing_symbol (yystates[yyi]->yylrState)),
                         YY_CAST (long, yystates[yyi-1]->yyposn + 1),
                         YY_CAST (long, yystates[yyi]->yyposn)));
        }
      else
        yyreportTree (yystates[yyi]->yysemantics.yyfirstVal, yyindent+2);
    }
}
#endif

static YYRESULTTAG
yyreportAmbiguity (yySemanticOption* yyx0,
                   yySemanticOption* yyx1, omnetpp::nedxml::ParseContext *np)
{
  YY_USE (yyx0);
  YY_USE (yyx1);

#if YYDEBUG
  YY_FPRINTF ((stderr, "Ambiguity detected.\n"));
  YY_FPRINTF ((stderr, "Option 1,\n"));
  yyreportTree (yyx0, 2);
  YY_FPRINTF ((stderr, "\nOption 2,\n"));
  yyreportTree (yyx1, 2);
  YY_FPRINTF ((stderr, "\n"));
#endif

  yyerror (np, YY_("syntax is ambiguous"));
  return yyabort;
}

/** Resolve the locations for each of the YYN1 states in *YYSTACKP,
 *  ending at YYS1.  Has no effect on previously resolved states.
 *  The first semantic option of a state is always chosen.  */
static void
yyresolveLocations (yyGLRState *yys1, int yyn1,
                    yyGLRStack *yystackp, omnetpp::nedxml::ParseContext *np)
{
  if (0 < yyn1)
    {
      yyresolveLocations (yys1->yypred, yyn1 - 1, yystackp, np);
      if (!yys1->yyresolved)
        {
          yyGLRStackItem yyrhsloc[1 + YYMAXRHS];
          int yynrhs;
          yySemanticOption *yyoption = yys1->yysemantics.yyfirstVal;
          YY_ASSERT (yyoption);
          yynrhs = yyrhsLength (yyoption->yyrule);
          if (0 < yynrhs)
            {
              yyGLRState *yys;
              int yyn;
              yyresolveLocations (yyoption->yystate, yynrhs,
                                  yystackp, np);
              for (yys = yyoption->yystate, yyn = yynrhs;
                   yyn > 0;
                   yys = yys->yypred, yyn -= 1)
                yyrhsloc[yyn].yystate.yyloc = yys->yyloc;
            }
          else
            {
              /* Both yyresolveAction and yyresolveLocations traverse the GSS
                 in reverse rightmost order.  It is only necessary to invoke
                 yyresolveLocations on a subforest for which yyresolveAction
                 would have been invoked next had an ambiguity not been
                 detected.  Thus the location of the previous state (but not
                 necessarily the previous state itself) is guaranteed to be
                 resolved already.  */
              yyGLRState *yyprevious = yyoption->yystate;
              yyrhsloc[0].yystate.yyloc = yyprevious->yyloc;
            }
          YYLLOC_DEFAULT ((yys1->yyloc), yyrhsloc, yynrhs);
        }
    }
}

/** Resolve the ambiguity represented in state YYS in *YYSTACKP,
 *  perform the indicated actions, and set the semantic value of YYS.
 *  If result != yyok, the chain of semantic options in YYS has been
 *  cleared instead or it has been left unmodified except that
 *  redundant options may have been removed.  Regardless of whether
 *  result = yyok, YYS has been left with consistent data so that
 *  yydestroyGLRState can be invoked if necessary.  */
static YYRESULTTAG
yyresolveValue (yyGLRState* yys, yyGLRStack* yystackp, omnetpp::nedxml::ParseContext *np)
{
  yySemanticOption* yyoptionList = yys->yysemantics.yyfirstVal;
  yySemanticOption* yybest = yyoptionList;
  yySemanticOption** yypp;
  yybool yymerge = yyfalse;
  YYSTYPE yyval;
  YYRESULTTAG yyflag;
  YYLTYPE *yylocp = &yys->yyloc;

  for (yypp = &yyoptionList->yynext; *yypp != YY_NULLPTR; )
    {
      yySemanticOption* yyp = *yypp;

      if (yyidenticalOptions (yybest, yyp))
        {
          yymergeOptionSets (yybest, yyp);
          *yypp = yyp->yynext;
        }
      else
        {
          switch (yypreference (yybest, yyp))
            {
            case 0:
              yyresolveLocations (yys, 1, yystackp, np);
              return yyreportAmbiguity (yybest, yyp, np);
              break;
            case 1:
              yymerge = yytrue;
              break;
            case 2:
              break;
            case 3:
              yybest = yyp;
              yymerge = yyfalse;
              break;
            default:
              /* This cannot happen so it is not worth a YY_ASSERT (yyfalse),
                 but some compilers complain if the default case is
                 omitted.  */
              break;
            }
          yypp = &yyp->yynext;
        }
    }

  if (yymerge)
    {
      yySemanticOption* yyp;
      int yyprec = yydprec[yybest->yyrule];
      yyflag = yyresolveAction (yybest, yystackp, &yyval, yylocp, np);
      if (yyflag == yyok)
        for (yyp = yybest->yynext; yyp != YY_NULLPTR; yyp = yyp->yynext)
          {
            if (yyprec == yydprec[yyp->yyrule])
              {
                YYSTYPE yyval_other;
                YYLTYPE yydummy;
                yyflag = yyresolveAction (yyp, yystackp, &yyval_other, &yydummy, np);
                if (yyflag != yyok)
                  {
                    yydestruct ("Cleanup: discarding incompletely merged value for",
                                yy_accessing_symbol (yys->yylrState),
                                &yyval, yylocp, np);
                    break;
                  }
                yyuserMerge (yymerger[yyp->yyrule], &yyval, &yyval_other);
              }
          }
    }
  else
    yyflag = yyresolveAction (yybest, yystackp, &yyval, yylocp, np);

  if (yyflag == yyok)
    {
      yys->yyresolved = yytrue;
      yys->yysemantics.yyval = yyval;
    }
  else
    yys->yysemantics.yyfirstVal = YY_NULLPTR;
  return yyflag;
}

static YYRESULTTAG
yyresolveStack (yyGLRStack* yystackp, omnetpp::nedxml::ParseContext *np)
{
  if (yystackp->yysplitPoint != YY_NULLPTR)
    {
      yyGLRState* yys;
      int yyn;

      for (yyn = 0, yys = yystackp->yytops.yystates[0];
           yys != yystackp->yysplitPoint;
           yys = yys->yypred, yyn += 1)
        continue;
      YYCHK (yyresolveStates (yystackp->yytops.yystates[0], yyn, yystackp
                             , np));
    }
  return yyok;
}

/** Called when returning to deterministic operation to clean up the extra
 * stacks. */
static void
yycompressStack (yyGLRStack* yystackp)
{
  /* yyr is the state after the split point.  */
  yyGLRState *yyr;

  if (yystackp->yytops.yysize != 1 || yystackp->yysplitPoint == YY_NULLPTR)
    return;

  {
    yyGLRState *yyp, *yyq;
    for (yyp = yystackp->yytops.yystates[0], yyq = yyp->yypred, yyr = YY_NULLPTR;
         yyp != yystackp->yysplitPoint;
         yyr = yyp, yyp = yyq, yyq = yyp->yypred)
      yyp->yypred = yyr;
  }

  yystackp->yyspaceLeft += yystackp->yynextFree - yystackp->yyitems;
  yystackp->yynextFree = YY_REINTERPRET_CAST (yyGLRStackItem*, yystackp->yysplitPoint) + 1;
  yystackp->yyspaceLeft -= yystackp->yynextFree - yystackp->yyitems;
  yystackp->yysplitPoint = YY_NULLPTR;
  yystackp->yylastDeleted = YY_NULLPTR;

  while (yyr != YY_NULLPTR)
    {
      yystackp->yynextFree->yystate = *yyr;
      yyr = yyr->yypred;
      yystackp->yynextFree->yystate.yypred = &yystackp->yynextFree[-1].yystate;
      yystackp->yytops.yystates[0] = &yystackp->yynextFree->yystate;
      yystackp->yynextFree += 1;
      yystackp->yyspaceLeft -= 1;
    }
}

static YYRESULTTAG
yyprocessOneStack (yyGLRStack* yystackp, YYPTRDIFF_T yyk,
                   YYPTRDIFF_T yyposn, omnetpp::nedxml::ParseContext *np)
{
  while (yystackp->yytops.yystates[yyk] != YY_NULLPTR)
    {
      yy_state_t yystate = yystackp->yytops.yystates[yyk]->yylrState;
      YY_DPRINTF ((stderr, "Stack %ld Entering state %d\n",
                   YY_CAST (long, yyk), yystate));

      YY_ASSERT (yystate != YYFINAL);

      if (yyisDefaultedState (yystate))
        {
          YYRESULTTAG yyflag;
          yyRuleNum yyrule = yydefaultAction (yystate);
          if (yyrule == 0)
            {
              YY_DPRINTF ((stderr, "Stack %ld dies.\n", YY_CAST (long, yyk)));
              yymarkStackDeleted (yystackp, yyk);
              return yyok;
            }
          yyflag = yyglrReduce (yystackp, yyk, yyrule, yyimmediate[yyrule], np);
          if (yyflag == yyerr)
            {
              YY_DPRINTF ((stderr,
                           "Stack %ld dies "
                           "(predicate failure or explicit user error).\n",
                           YY_CAST (long, yyk)));
              yymarkStackDeleted (yystackp, yyk);
              return yyok;
            }
          if (yyflag != yyok)
            return yyflag;
        }
      else
        {
          yysymbol_kind_t yytoken = yygetToken (&yychar, np);
          const short* yyconflicts;
          const int yyaction = yygetLRActions (yystate, yytoken, &yyconflicts);
          yystackp->yytops.yylookaheadNeeds[yyk] = yytrue;

          for (/* nothing */; *yyconflicts; yyconflicts += 1)
            {
              YYRESULTTAG yyflag;
              YYPTRDIFF_T yynewStack = yysplitStack (yystackp, yyk);
              YY_DPRINTF ((stderr, "Splitting off stack %ld from %ld.\n",
                           YY_CAST (long, yynewStack), YY_CAST (long, yyk)));
              yyflag = yyglrReduce (yystackp, yynewStack,
                                    *yyconflicts,
                                    yyimmediate[*yyconflicts], np);
              if (yyflag == yyok)
                YYCHK (yyprocessOneStack (yystackp, yynewStack,
                                          yyposn, np));
              else if (yyflag == yyerr)
                {
                  YY_DPRINTF ((stderr, "Stack %ld dies.\n", YY_CAST (long, yynewStack)));
                  yymarkStackDeleted (yystackp, yynewStack);
                }
              else
                return yyflag;
            }

          if (yyisShiftAction (yyaction))
            break;
          else if (yyisErrorAction (yyaction))
            {
              YY_DPRINTF ((stderr, "Stack %ld dies.\n", YY_CAST (long, yyk)));
              yymarkStackDeleted (yystackp, yyk);
              break;
            }
          else
            {
              YYRESULTTAG yyflag = yyglrReduce (yystackp, yyk, -yyaction,
                                                yyimmediate[-yyaction], np);
              if (yyflag == yyerr)
                {
                  YY_DPRINTF ((stderr,
                               "Stack %ld dies "
                               "(predicate failure or explicit user error).\n",
                               YY_CAST (long, yyk)));
                  yymarkStackDeleted (yystackp, yyk);
                  break;
                }
              else if (yyflag != yyok)
                return yyflag;
            }
        }
    }
  return yyok;
}






static void
yyreportSyntaxError (yyGLRStack* yystackp, omnetpp::nedxml::ParseContext *np)
{
  if (yystackp->yyerrState != 0)
    return;
  yyerror (np, YY_("syntax error"));
  yynerrs += 1;
}

/* Recover from a syntax error on *YYSTACKP, assuming that *YYSTACKP->YYTOKENP,
   yylval, and yylloc are the syntactic category, semantic value, and location
   of the lookahead.  */
static void
yyrecoverSyntaxError (yyGLRStack* yystackp, omnetpp::nedxml::ParseContext *np)
{
  if (yystackp->yyerrState == 3)
    /* We just shifted the error token and (perhaps) took some
       reductions.  Skip tokens until we can proceed.  */
    while (yytrue)
      {
        yysymbol_kind_t yytoken;
        int yyj;
        if (yychar == YYEOF)
          yyFail (yystackp, np, YY_NULLPTR);
        if (yychar != YYEMPTY)
          {
            /* We throw away the lookahead, but the error range
               of the shifted error token must take it into account.  */
            yyGLRState *yys = yystackp->yytops.yystates[0];
            yyGLRStackItem yyerror_range[3];
            yyerror_range[1].yystate.yyloc = yys->yyloc;
            yyerror_range[2].yystate.yyloc = yylloc;
            YYLLOC_DEFAULT ((yys->yyloc), yyerror_range, 2);
            yytoken = YYTRANSLATE (yychar);
            yydestruct ("Error: discarding",
                        yytoken, &yylval, &yylloc, np);
            yychar = YYEMPTY;
          }
        yytoken = yygetToken (&yychar, np);
        yyj = yypact[yystackp->yytops.yystates[0]->yylrState];
        if (yypact_value_is_default (yyj))
          return;
        yyj += yytoken;
        if (yyj < 0 || YYLAST < yyj || yycheck[yyj] != yytoken)
          {
            if (yydefact[yystackp->yytops.yystates[0]->yylrState] != 0)
              return;
          }
        else if (! yytable_value_is_error (yytable[yyj]))
          return;
      }

  /* Reduce to one stack.  */
  {
    YYPTRDIFF_T yyk;
    for (yyk = 0; yyk < yystackp->yytops.yysize; yyk += 1)
      if (yystackp->yytops.yystates[yyk] != YY_NULLPTR)
        break;
    if (yyk >= yystackp->yytops.yysize)
      yyFail (yystackp, np, YY_NULLPTR);
    for (yyk += 1; yyk < yystackp->yytops.yysize; yyk += 1)
      yymarkStackDeleted (yystackp, yyk);
    yyremoveDeletes (yystackp);
    yycompressStack (yystackp);
  }

  /* Pop stack until we find a state that shifts the error token.  */
  yystackp->yyerrState = 3;
  while (yystackp->yytops.yystates[0] != YY_NULLPTR)
    {
      yyGLRState *yys = yystackp->yytops.yystates[0];
      int yyj = yypact[yys->yylrState];
      if (! yypact_value_is_default (yyj))
        {
          yyj += YYSYMBOL_YYerror;
          if (0 <= yyj && yyj <= YYLAST && yycheck[yyj] == YYSYMBOL_YYerror
              && yyisShiftAction (yytable[yyj]))
            {
              /* Shift the error token.  */
              int yyaction = yytable[yyj];
              /* First adjust its location.*/
              YYLTYPE yyerrloc;
              yystackp->yyerror_range[2].yystate.yyloc = yylloc;
              YYLLOC_DEFAULT (yyerrloc, (yystackp->yyerror_range), 2);
              YY_SYMBOL_PRINT ("Shifting", yy_accessing_symbol (yyaction),
                               &yylval, &yyerrloc);
              yyglrShift (yystackp, 0, yyaction,
                          yys->yyposn, &yylval, &yyerrloc);
              yys = yystackp->yytops.yystates[0];
              break;
            }
        }
      yystackp->yyerror_range[1].yystate.yyloc = yys->yyloc;
      if (yys->yypred != YY_NULLPTR)
        yydestroyGLRState ("Error: popping", yys, np);
      yystackp->yytops.yystates[0] = yys->yypred;
      yystackp->yynextFree -= 1;
      yystackp->yyspaceLeft += 1;
    }
  if (yystackp->yytops.yystates[0] == YY_NULLPTR)
    yyFail (yystackp, np, YY_NULLPTR);
}

#define YYCHK1(YYE)                             \
  do {                                          \
    switch (YYE) {                              \
    case yyok:     break;                       \
    case yyabort:  goto yyabortlab;             \
    case yyaccept: goto yyacceptlab;            \
    case yyerr:    goto yyuser_error;           \
    case yynomem:  goto yyexhaustedlab;         \
    default:       goto yybuglab;               \
    }                                           \
  } while (0)

/*----------.
| yyparse.  |
`----------*/

int
yyparse (omnetpp::nedxml::ParseContext *np)
{
  int yyresult;
  yyGLRStack yystack;
  yyGLRStack* const yystackp = &yystack;
  YYPTRDIFF_T yyposn;

  YY_DPRINTF ((stderr, "Starting parse\n"));

  yychar = YYEMPTY;
  yylval = yyval_default;
  yylloc = yyloc_default;

  if (! yyinitGLRStack (yystackp, YYINITDEPTH))
    goto yyexhaustedlab;
  switch (YYSETJMP (yystack.yyexception_buffer))
    {
    case 0: break;
    case 1: goto yyabortlab;
    case 2: goto yyexhaustedlab;
    default: goto yybuglab;
    }
  yyglrShift (&yystack, 0, 0, 0, &yylval, &yylloc);
  yyposn = 0;

  while (yytrue)
    {
      /* For efficiency, we have two loops, the first of which is
         specialized to deterministic operation (single stack, no
         potential ambiguity).  */
      /* Standard mode. */
      while (yytrue)
        {
          yy_state_t yystate = yystack.yytops.yystates[0]->yylrState;
          YY_DPRINTF ((stderr, "Entering state %d\n", yystate));
          if (yystate == YYFINAL)
            goto yyacceptlab;
          if (yyisDefaultedState (yystate))
            {
              yyRuleNum yyrule = yydefaultAction (yystate);
              if (yyrule == 0)
                {
                  yystack.yyerror_range[1].yystate.yyloc = yylloc;
                  yyreportSyntaxError (&yystack, np);
                  goto yyuser_error;
                }
              YYCHK1 (yyglrReduce (&yystack, 0, yyrule, yytrue, np));
            }
          else
            {
              yysymbol_kind_t yytoken = yygetToken (&yychar, np);
              const short* yyconflicts;
              int yyaction = yygetLRActions (yystate, yytoken, &yyconflicts);
              if (*yyconflicts)
                /* Enter nondeterministic mode.  */
                break;
              if (yyisShiftAction (yyaction))
                {
                  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);
                  yychar = YYEMPTY;
                  yyposn += 1;
                  yyglrShift (&yystack, 0, yyaction, yyposn, &yylval, &yylloc);
                  if (0 < yystack.yyerrState)
                    yystack.yyerrState -= 1;
                }
              else if (yyisErrorAction (yyaction))
                {
                  yystack.yyerror_range[1].yystate.yyloc = yylloc;
                  /* Issue an error message unless the scanner already
                     did. */
                  if (yychar != YYerror)
                    yyreportSyntaxError (&yystack, np);
                  goto yyuser_error;
                }
              else
                YYCHK1 (yyglrReduce (&yystack, 0, -yyaction, yytrue, np));
            }
        }

      /* Nondeterministic mode. */
      while (yytrue)
        {
          yysymbol_kind_t yytoken_to_shift;
          YYPTRDIFF_T yys;

          for (yys = 0; yys < yystack.yytops.yysize; yys += 1)
            yystackp->yytops.yylookaheadNeeds[yys] = yychar != YYEMPTY;

          /* yyprocessOneStack returns one of three things:

              - An error flag.  If the caller is yyprocessOneStack, it
                immediately returns as well.  When the caller is finally
                yyparse, it jumps to an error label via YYCHK1.

              - yyok, but yyprocessOneStack has invoked yymarkStackDeleted
                (&yystack, yys), which sets the top state of yys to NULL.  Thus,
                yyparse's following invocation of yyremoveDeletes will remove
                the stack.

              - yyok, when ready to shift a token.

             Except in the first case, yyparse will invoke yyremoveDeletes and
             then shift the next token onto all remaining stacks.  This
             synchronization of the shift (that is, after all preceding
             reductions on all stacks) helps prevent double destructor calls
             on yylval in the event of memory exhaustion.  */

          for (yys = 0; yys < yystack.yytops.yysize; yys += 1)
            YYCHK1 (yyprocessOneStack (&yystack, yys, yyposn, np));
          yyremoveDeletes (&yystack);
          if (yystack.yytops.yysize == 0)
            {
              yyundeleteLastStack (&yystack);
              if (yystack.yytops.yysize == 0)
                yyFail (&yystack, np, YY_("syntax error"));
              YYCHK1 (yyresolveStack (&yystack, np));
              YY_DPRINTF ((stderr, "Returning to deterministic operation.\n"));
              yystack.yyerror_range[1].yystate.yyloc = yylloc;
              yyreportSyntaxError (&yystack, np);
              goto yyuser_error;
            }

          /* If any yyglrShift call fails, it will fail after shifting.  Thus,
             a copy of yylval will already be on stack 0 in the event of a
             failure in the following loop.  Thus, yychar is set to YYEMPTY
             before the loop to make sure the user destructor for yylval isn't
             called twice.  */
          yytoken_to_shift = YYTRANSLATE (yychar);
          yychar = YYEMPTY;
          yyposn += 1;
          for (yys = 0; yys < yystack.yytops.yysize; yys += 1)
            {
              yy_state_t yystate = yystack.yytops.yystates[yys]->yylrState;
              const short* yyconflicts;
              int yyaction = yygetLRActions (yystate, yytoken_to_shift,
                              &yyconflicts);
              /* Note that yyconflicts were handled by yyprocessOneStack.  */
              YY_DPRINTF ((stderr, "On stack %ld, ", YY_CAST (long, yys)));
              YY_SYMBOL_PRINT ("shifting", yytoken_to_shift, &yylval, &yylloc);
              yyglrShift (&yystack, yys, yyaction, yyposn,
                          &yylval, &yylloc);
              YY_DPRINTF ((stderr, "Stack %ld now in state %d\n",
                           YY_CAST (long, yys),
                           yystack.yytops.yystates[yys]->yylrState));
            }

          if (yystack.yytops.yysize == 1)
            {
              YYCHK1 (yyresolveStack (&yystack, np));
              YY_DPRINTF ((stderr, "Returning to deterministic operation.\n"));
              yycompressStack (&yystack);
              break;
            }
        }
      continue;
    yyuser_error:
      yyrecoverSyntaxError (&yystack, np);
      yyposn = yystack.yytops.yystates[0]->yyposn;
    }

 yyacceptlab:
  yyresult = 0;
  goto yyreturnlab;

 yybuglab:
  YY_ASSERT (yyfalse);
  goto yyabortlab;

 yyabortlab:
  yyresult = 1;
  goto yyreturnlab;

 yyexhaustedlab:
  yyerror (np, YY_("memory exhausted"));
  yyresult = 2;
  goto yyreturnlab;

 yyreturnlab:
  if (yychar != YYEMPTY)
    yydestruct ("Cleanup: discarding lookahead",
                YYTRANSLATE (yychar), &yylval, &yylloc, np);

  /* If the stack is well-formed, pop the stack until it is empty,
     destroying its entries as we go.  But free the stack regardless
     of whether it is well-formed.  */
  if (yystack.yyitems)
    {
      yyGLRState** yystates = yystack.yytops.yystates;
      if (yystates)
        {
          YYPTRDIFF_T yysize = yystack.yytops.yysize;
          YYPTRDIFF_T yyk;
          for (yyk = 0; yyk < yysize; yyk += 1)
            if (yystates[yyk])
              {
                while (yystates[yyk])
                  {
                    yyGLRState *yys = yystates[yyk];
                    yystack.yyerror_range[1].yystate.yyloc = yys->yyloc;
                    if (yys->yypred != YY_NULLPTR)
                      yydestroyGLRState ("Cleanup: popping", yys, np);
                    yystates[yyk] = yys->yypred;
                    yystack.yynextFree -= 1;
                    yystack.yyspaceLeft += 1;
                  }
                break;
              }
        }
      yyfreeGLRStack (&yystack);
    }

  return yyresult;
}

/* DEBUGGING ONLY */
#if YYDEBUG
/* Print *YYS and its predecessors. */
static void
yy_yypstack (yyGLRState* yys)
{
  if (yys->yypred)
    {
      yy_yypstack (yys->yypred);
      YY_FPRINTF ((stderr, " -> "));
    }
  YY_FPRINTF ((stderr, "%d@%ld", yys->yylrState, YY_CAST (long, yys->yyposn)));
}

/* Print YYS (possibly NULL) and its predecessors. */
static void
yypstates (yyGLRState* yys)
{
  if (yys == YY_NULLPTR)
    YY_FPRINTF ((stderr, "<null>"));
  else
    yy_yypstack (yys);
  YY_FPRINTF ((stderr, "\n"));
}

/* Print the stack #YYK.  */
static void
yypstack (yyGLRStack* yystackp, YYPTRDIFF_T yyk)
{
  yypstates (yystackp->yytops.yystates[yyk]);
}

/* Print all the stacks.  */
static void
yypdumpstack (yyGLRStack* yystackp)
{
#define YYINDEX(YYX)                                                    \
  YY_CAST (long,                                                        \
           ((YYX)                                                       \
            ? YY_REINTERPRET_CAST (yyGLRStackItem*, (YYX)) - yystackp->yyitems \
            : -1))

  yyGLRStackItem* yyp;
  for (yyp = yystackp->yyitems; yyp < yystackp->yynextFree; yyp += 1)
    {
      YY_FPRINTF ((stderr, "%3ld. ",
                   YY_CAST (long, yyp - yystackp->yyitems)));
      if (*YY_REINTERPRET_CAST (yybool *, yyp))
        {
          YY_ASSERT (yyp->yystate.yyisState);
          YY_ASSERT (yyp->yyoption.yyisState);
          YY_FPRINTF ((stderr, "Res: %d, LR State: %d, posn: %ld, pred: %ld",
                       yyp->yystate.yyresolved, yyp->yystate.yylrState,
                       YY_CAST (long, yyp->yystate.yyposn),
                       YYINDEX (yyp->yystate.yypred)));
          if (! yyp->yystate.yyresolved)
            YY_FPRINTF ((stderr, ", firstVal: %ld",
                         YYINDEX (yyp->yystate.yysemantics.yyfirstVal)));
        }
      else
        {
          YY_ASSERT (!yyp->yystate.yyisState);
          YY_ASSERT (!yyp->yyoption.yyisState);
          YY_FPRINTF ((stderr, "Option. rule: %d, state: %ld, next: %ld",
                       yyp->yyoption.yyrule - 1,
                       YYINDEX (yyp->yyoption.yystate),
                       YYINDEX (yyp->yyoption.yynext)));
        }
      YY_FPRINTF ((stderr, "\n"));
    }

  YY_FPRINTF ((stderr, "Tops:"));
  {
    YYPTRDIFF_T yyi;
    for (yyi = 0; yyi < yystackp->yytops.yysize; yyi += 1)
      YY_FPRINTF ((stderr, "%ld: %ld; ", YY_CAST (long, yyi),
                   YYINDEX (yystackp->yytops.yystates[yyi])));
    YY_FPRINTF ((stderr, "\n"));
  }
#undef YYINDEX
}
#endif

#undef yylval
#undef yychar
#undef yynerrs
#undef yylloc

/* Substitute the variable and function names.  */
#define yyparse ned2yyparse
#define yylex   ned2yylex
#define yyerror ned2yyerror
#define yylval  ned2yylval
#define yychar  ned2yychar
#define yydebug ned2yydebug
#define yynerrs ned2yynerrs
#define yylloc  ned2yylloc


#line 1699 "ned2.y"


//----------------------------------------------------------------------
// general bison/flex stuff:
//
int ned2yylex_destroy();  // from lex.XXX.cc file

ASTNode *doParseNed(ParseContext *np, const char *nedtext)
{
#if YYDEBUG != 0      /* #if added --VA */
    yydebug = YYDEBUGGING_ON;
#endif

    ned2yylex_destroy();

    DETECT_PARSER_REENTRY();

    // reset the lexer
    pos.co = 0;
    pos.li = 1;
    prevpos = pos;

    yyin = nullptr;
    yyout = stderr; // not used anyway

    // alloc buffer
    struct yy_buffer_state *handle = yy_scan_string(nedtext);
    if (!handle)
        {np->getErrors()->addError("", "unable to allocate work memory"); return nullptr;}

    // create parser state and NedFileElement
    resetParserState();
    ps.nedfile = new NedFileElement();

    // store file name with slashes always, even on Windows -- neddoc relies on that
    ps.nedfile->setFilename(slashifyFilename(np->getFileName()).c_str());
    ps.nedfile->setVersion("2");

    // storing the start and end position of the whole file for the NedFileElement
    // NOTE: we cannot use storePos() because it strips off the leading spaces
    // and comments from the element.
    YYLTYPE pos = np->getSource()->getFullTextPos();
    SourceRegion region;
    region.startLine = pos.first_line;
    region.startColumn = pos.first_column;
    region.endLine = pos.last_line;
    region.endColumn = pos.last_column;
    ps.nedfile->setSourceRegion(region);

    // store file comment
    storeFileComment(np, ps.nedfile);

    ps.propertyscope.push(ps.nedfile);

    globalps = ps; // remember this for error recovery

    if (np->getStoreSourceFlag())
        storeSourceCode(np, ps.nedfile, np->getSource()->getFullTextPos());

    // parse
    try
    {
        yyparse(np);
    }
    catch (NedException& e)
    {
        yyerror(np, (std::string("error during parsing: ")+e.what()).c_str());
        yy_delete_buffer(handle);
        return nullptr;
    }

    if (np->getErrors()->empty())
    {
        // more sanity checks
        if (ps.propertyscope.size()!=1 || ps.propertyscope.top()!=ps.nedfile)
            INTERNAL_ERROR0(nullptr, "error during parsing: imbalanced propertyscope");
        if (!ps.blockscope.empty() || !ps.typescope.empty())
            INTERNAL_ERROR0(nullptr, "error during parsing: imbalanced blockscope or typescope");
    }
    yy_delete_buffer(handle);

    return ps.nedfile;
}

void yyerror(ParseContext *np, const char *s)
{
    // chop newline
    char buf[250];
    strcpy(buf, s);
    if (buf[strlen(buf)-1] == '\n')
        buf[strlen(buf)-1] = '\0';

    np->error(buf, pos.li);
}
