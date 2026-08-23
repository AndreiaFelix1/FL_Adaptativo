/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison interface for Yacc-like parsers in C

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

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

#ifndef YY_EXPRYY_EXPR_TAB_HH_INCLUDED
# define YY_EXPRYY_EXPR_TAB_HH_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int expryydebug;
#endif

/* Token kinds.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    YYEMPTY = -2,
    YYEOF = 0,                     /* "end of file"  */
    YYerror = 256,                 /* error  */
    YYUNDEF = 257,                 /* "invalid token"  */
    DOUBLETYPE = 258,              /* DOUBLETYPE  */
    INTTYPE = 259,                 /* INTTYPE  */
    STRINGTYPE = 260,              /* STRINGTYPE  */
    BOOLTYPE = 261,                /* BOOLTYPE  */
    XMLTYPE = 262,                 /* XMLTYPE  */
    TRUE_ = 263,                   /* TRUE_  */
    FALSE_ = 264,                  /* FALSE_  */
    NAN_ = 265,                    /* NAN_  */
    INF_ = 266,                    /* INF_  */
    THIS_ = 267,                   /* THIS_  */
    PARENT = 268,                  /* PARENT  */
    ASK_ = 269,                    /* ASK_  */
    DEFAULT_ = 270,                /* DEFAULT_  */
    CONST_ = 271,                  /* CONST_  */
    SIZEOF_ = 272,                 /* SIZEOF_  */
    INDEX_ = 273,                  /* INDEX_  */
    EXISTS = 274,                  /* EXISTS  */
    TYPENAME = 275,                /* TYPENAME  */
    XMLDOC_ = 276,                 /* XMLDOC_  */
    NAME = 277,                    /* NAME  */
    INTCONSTANT = 278,             /* INTCONSTANT  */
    REALCONSTANT = 279,            /* REALCONSTANT  */
    STRINGCONSTANT = 280,          /* STRINGCONSTANT  */
    EQ_ = 281,                     /* EQ_  */
    NE_ = 282,                     /* NE_  */
    GE_ = 283,                     /* GE_  */
    LE_ = 284,                     /* LE_  */
    AND_ = 285,                    /* AND_  */
    OR_ = 286,                     /* OR_  */
    XOR_ = 287,                    /* XOR_  */
    NOT_ = 288,                    /* NOT_  */
    BINAND_ = 289,                 /* BINAND_  */
    BINOR_ = 290,                  /* BINOR_  */
    BINXOR_ = 291,                 /* BINXOR_  */
    BINCOMPL_ = 292,               /* BINCOMPL_  */
    SHIFTLEFT_ = 293,              /* SHIFTLEFT_  */
    SHIFTRIGHT_ = 294,             /* SHIFTRIGHT_  */
    INVALID_CHAR = 295,            /* INVALID_CHAR  */
    UMIN_ = 296                    /* UMIN_  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif
/* Token kinds.  */
#define YYEMPTY -2
#define YYEOF 0
#define YYerror 256
#define YYUNDEF 257
#define DOUBLETYPE 258
#define INTTYPE 259
#define STRINGTYPE 260
#define BOOLTYPE 261
#define XMLTYPE 262
#define TRUE_ 263
#define FALSE_ 264
#define NAN_ 265
#define INF_ 266
#define THIS_ 267
#define PARENT 268
#define ASK_ 269
#define DEFAULT_ 270
#define CONST_ 271
#define SIZEOF_ 272
#define INDEX_ 273
#define EXISTS 274
#define TYPENAME 275
#define XMLDOC_ 276
#define NAME 277
#define INTCONSTANT 278
#define REALCONSTANT 279
#define STRINGCONSTANT 280
#define EQ_ 281
#define NE_ 282
#define GE_ 283
#define LE_ 284
#define AND_ 285
#define OR_ 286
#define XOR_ 287
#define NOT_ 288
#define BINAND_ 289
#define BINOR_ 290
#define BINXOR_ 291
#define BINCOMPL_ 292
#define SHIFTLEFT_ 293
#define SHIFTRIGHT_ 294
#define INVALID_CHAR 295
#define UMIN_ 296

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef int YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE expryylval;


int expryyparse (void);


#endif /* !YY_EXPRYY_EXPR_TAB_HH_INCLUDED  */
