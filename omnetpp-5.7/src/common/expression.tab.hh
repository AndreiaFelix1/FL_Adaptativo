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

#ifndef YY_EXPRESSIONYY_EXPRESSION_TAB_HH_INCLUDED
# define YY_EXPRESSIONYY_EXPRESSION_TAB_HH_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int expressionyydebug;
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
    TRUE_ = 262,                   /* TRUE_  */
    FALSE_ = 263,                  /* FALSE_  */
    NAME = 264,                    /* NAME  */
    INTCONSTANT = 265,             /* INTCONSTANT  */
    REALCONSTANT = 266,            /* REALCONSTANT  */
    STRINGCONSTANT = 267,          /* STRINGCONSTANT  */
    EQ_ = 268,                     /* EQ_  */
    NE_ = 269,                     /* NE_  */
    GE_ = 270,                     /* GE_  */
    LE_ = 271,                     /* LE_  */
    AND_ = 272,                    /* AND_  */
    OR_ = 273,                     /* OR_  */
    XOR_ = 274,                    /* XOR_  */
    NOT_ = 275,                    /* NOT_  */
    BINAND_ = 276,                 /* BINAND_  */
    BINOR_ = 277,                  /* BINOR_  */
    BINXOR_ = 278,                 /* BINXOR_  */
    BINCOMPL_ = 279,               /* BINCOMPL_  */
    SHIFTLEFT_ = 280,              /* SHIFTLEFT_  */
    SHIFTRIGHT_ = 281,             /* SHIFTRIGHT_  */
    INVALID_CHAR = 282,            /* INVALID_CHAR  */
    UMIN_ = 283                    /* UMIN_  */
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
#define TRUE_ 262
#define FALSE_ 263
#define NAME 264
#define INTCONSTANT 265
#define REALCONSTANT 266
#define STRINGCONSTANT 267
#define EQ_ 268
#define NE_ 269
#define GE_ 270
#define LE_ 271
#define AND_ 272
#define OR_ 273
#define XOR_ 274
#define NOT_ 275
#define BINAND_ 276
#define BINOR_ 277
#define BINXOR_ 278
#define BINCOMPL_ 279
#define SHIFTLEFT_ 280
#define SHIFTRIGHT_ 281
#define INVALID_CHAR 282
#define UMIN_ 283

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef int YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE expressionyylval;


int expressionyyparse (void);


#endif /* !YY_EXPRESSIONYY_EXPRESSION_TAB_HH_INCLUDED  */
