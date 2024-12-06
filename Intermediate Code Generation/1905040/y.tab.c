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
#line 3 "parser.y"

// #include  <bits/stdc++.h>
#include<cstdio>
#include<cstdlib>
#include<string>
#include<vector>
#include<iostream>
#include<fstream>
#include<map>
#include "template.h"

using namespace std;

// int line_count;
FILE *fp;
ofstream fout, eout, pout,tout,finalout;
ifstream label_in;
int setoffset=0,temp_line_count=1,label_count=1,func_check=0;
map<int,string> umap;
extern int error;

// #define YYSTYPE SymbolInfo*

using namespace std;

// int yyparse(void);
int yylex(void);
extern FILE *yyin;
extern int line_count;
// extern int error=0;

SymbolTable *table;


void yyerror(char *s)
{
	fout<<"Line# "<<line_count<<": "<<s<<"\n"<<endl;
	eout<<"Line# "<<line_count<<": "<<s<<"\n"<<endl;
    error++;
}

void Print(ScopeTable* s){
        int count=1;
        fout<<"\tScopeTable# "<<s->order_no<<endl;
        for(int i=0;i<s->scope_num;i++){

            if(s->array[i]==NULL){

            }
            else{
                SymbolInfo* temp=s->array[i];
                fout<<"\t"<<count<<"--> ";
                while(temp!=NULL){

                    if(temp->optional=="")fout<<"<"<<temp->getName()<<", "<<temp->getType()<<"> ";
                    else fout<<"<"<<temp->getName()<<", "<<temp->optional<<", "<<temp->getType()<<"> ";
                    temp=temp->next;
                }

                fout<<endl;
            }

            count++;
        }
    }
void print_current(){
        Print(table->current);
    }
void print_all(){
        ScopeTable* temp=table->current;
        while(temp!=NULL){
            Print(temp);
            temp=temp->parent;
        }
}
void function_into_scope(SymbolInfo* sname,SymbolInfo* stype,SymbolInfo* param_list){

    SymbolInfo* temp=table->LookUp(sname->getName());
    
    if(temp!=nullptr){
        
        if(temp->func_def_flag==1){
            if(temp->optional=="FUNCTION")
            eout<<"Line# "<<line_count<<": Redefinition of function '"<<sname->getName()<<"'"<<endl;
            error++;
        }
        else{
            if(temp->optional!="FUNCTION"){
                eout<<"Line# "<<line_count<<": '"<<sname->getName()<<"' redeclared as different kind of symbol"<<endl;
                error++;
            }
            else if(stype->getType()!=temp->getType()){
                eout<<"Line# "<<line_count<<": Conflicting types for '"<<sname->getName()<<"'"<<endl;
                error++;
            }
            else if(temp->func_dec_list.size()!=param_list->var_dec_list.size()){
                eout<<"Line# "<<line_count<<": Conflicting types for '"<<sname->getName()<<"'"<<endl;
                error++;
            }
            for(int i=0;i<temp->func_dec_list.size();i++){
                if(temp->func_dec_list[i]->getType()!=param_list->var_dec_list[i]->getType()){
                    eout<<"Line# "<<line_count<<": Type mismatch in redeclaration of function "<<sname->getName()<<endl;
                    error++;
                }
            }
            temp->func_def_flag=1;
        }
    }
    
    table->opt_insert(sname->getName(),stype->getType(),"FUNCTION");
    if(func_check!=1)
        table->enter_scope();
    func_check=0;
    if(param_list==nullptr){
        cout<<sname->getName()<<","<<stype->getType()<<endl;
        if(sname->getName()=="main"){
            tout<<"MOV AX, @DATA\n\tMOV DS, AX\n\tPUSH BP\n\tMOV BP, SP"<<endl;
            temp_line_count=temp_line_count+4;
        }
        else{
            tout<<"PUSH BP\n\tMOV BP, SP"<<endl;
            temp_line_count=temp_line_count+2;
        }
        return;
    }
    else{
        for(int i=0;i<param_list->var_dec_list.size();i++){
        for(int j=0;j<=i;j++){
            if(param_list->var_dec_list[i]->getName()==param_list->var_dec_list[j]->getName() && i!=j){
                eout<<"Line# "<<line_count<<": Redefinition of parameter '"<<param_list->var_dec_list[i]->getName()<<"'"<<endl;
                error++;
                break;
            }
            
        }
        table->insert(param_list->var_dec_list[i]->getName(),param_list->var_dec_list[i]->getType());
    }
    }
    SymbolInfo* temp2=table->LookUp(sname->getName());
    temp2->func_def_flag=1;
    if(param_list!=nullptr){
        for(int i=0;i<param_list->var_dec_list.size();i++){
            temp2->func_dec_list.push_back(param_list->var_dec_list[i]);
        }
    }
        tout<<sname->getName()<<" PROC"<<endl;
        temp_line_count++;
        if(sname->getName()=="main"){
            tout<<"MOV AX, @DATA\nMOV DS, AX\nPUSH BP\nMOV BP, SP"<<endl;
            temp_line_count=temp_line_count+4;
        }
        else{
            tout<<"PUSH BP\n\tMOV BP, SP"<<endl;
            temp_line_count=temp_line_count+2;
        }
}
void rule_print(SymbolInfo* s){
    if(s->leaf==0)pout<<s->message<<" \t<Line: "<<s->start<<"-"<<s->end<<">"<<endl;
    else pout<<s->message<<"\t<Line: "<<s->start<<">"<<endl;
}
void parse_tree_print(SymbolInfo* s, int gap=0){
    for(int i=0;i<gap;i++){
        pout<<" ";
    }
    rule_print(s);
    if(s->leaf==0){
        for(int i=0;i<s->symbol_list.size();i++){
            parse_tree_print(s->symbol_list[i],gap+1);
        }
    }
}
void backpatch(vector<int> v,string s){
    for(int i=0;i<v.size();i++){
        umap[v[i]]=s;

    }
}
vector<int> merge(vector<int> a,vector<int> b){
    vector<int> temp;
    for(int i=0;i<a.size();i++){
        temp.push_back(a[i]);
    }
    for(int i=0;i<b.size();i++){
        temp.push_back(b[i]);
    }
    return temp;
}
void is_arith(SymbolInfo *s){
    if(s->arith_check==1){
        tout<<"POP AX"<<endl;
        temp_line_count++;
        tout<<"CMP AX,0"<<endl;
        temp_line_count++;
        tout<<"JNE "<<endl;
        s->truelist.push_back(temp_line_count);
        temp_line_count++;
        tout<<"JMP "<<endl;
        s->falselist.push_back(temp_line_count);
        temp_line_count++;
    }
}


#line 275 "y.tab.c"

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

/* Use api.header.include to #include this header
   instead of duplicating it here.  */
#ifndef YY_YY_Y_TAB_H_INCLUDED
# define YY_YY_Y_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
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
    IF = 258,                      /* IF  */
    ELSE = 259,                    /* ELSE  */
    FOR = 260,                     /* FOR  */
    WHILE = 261,                   /* WHILE  */
    DO = 262,                      /* DO  */
    BREAK = 263,                   /* BREAK  */
    INT = 264,                     /* INT  */
    CHAR = 265,                    /* CHAR  */
    FLOAT = 266,                   /* FLOAT  */
    DOUBLE = 267,                  /* DOUBLE  */
    VOID = 268,                    /* VOID  */
    RETURN = 269,                  /* RETURN  */
    SWITCH = 270,                  /* SWITCH  */
    CASE = 271,                    /* CASE  */
    DEFAULT = 272,                 /* DEFAULT  */
    CONTINUE = 273,                /* CONTINUE  */
    PRINTLN = 274,                 /* PRINTLN  */
    ID = 275,                      /* ID  */
    CONST_INT = 276,               /* CONST_INT  */
    CONST_FLOAT = 277,             /* CONST_FLOAT  */
    CONST_CHAR = 278,              /* CONST_CHAR  */
    CONST_STRING = 279,            /* CONST_STRING  */
    RELOP = 280,                   /* RELOP  */
    MULOP = 281,                   /* MULOP  */
    LOGICOP = 282,                 /* LOGICOP  */
    ADDOP = 283,                   /* ADDOP  */
    LPAREN = 284,                  /* LPAREN  */
    RPAREN = 285,                  /* RPAREN  */
    LCURL = 286,                   /* LCURL  */
    RCURL = 287,                   /* RCURL  */
    LSQUARE = 288,                 /* LSQUARE  */
    RSQUARE = 289,                 /* RSQUARE  */
    COMMA = 290,                   /* COMMA  */
    SEMICOLON = 291,               /* SEMICOLON  */
    ASSIGNOP = 292,                /* ASSIGNOP  */
    NOT = 293,                     /* NOT  */
    INCOP = 294,                   /* INCOP  */
    DECOP = 295,                   /* DECOP  */
    LOWER_THAN_ELSE = 296          /* LOWER_THAN_ELSE  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 210 "parser.y"

    SymbolInfo* symbol_info;
    string* symbol_info_str;

#line 371 "y.tab.c"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;


int yyparse (void);


#endif /* !YY_YY_Y_TAB_H_INCLUDED  */
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
  YYSYMBOL_LSQUARE = 33,                   /* LSQUARE  */
  YYSYMBOL_RSQUARE = 34,                   /* RSQUARE  */
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
  YYSYMBOL_48_1 = 48,                      /* $@1  */
  YYSYMBOL_49_2 = 49,                      /* $@2  */
  YYSYMBOL_parameter_list = 50,            /* parameter_list  */
  YYSYMBOL_compound_statement = 51,        /* compound_statement  */
  YYSYMBOL_52_3 = 52,                      /* $@3  */
  YYSYMBOL_var_declaration = 53,           /* var_declaration  */
  YYSYMBOL_type_specifier = 54,            /* type_specifier  */
  YYSYMBOL_declaration_list = 55,          /* declaration_list  */
  YYSYMBOL_statements = 56,                /* statements  */
  YYSYMBOL_statement = 57,                 /* statement  */
  YYSYMBOL_expression_statement = 58,      /* expression_statement  */
  YYSYMBOL_variable = 59,                  /* variable  */
  YYSYMBOL_expression = 60,                /* expression  */
  YYSYMBOL_logic_expression = 61,          /* logic_expression  */
  YYSYMBOL_62_4 = 62,                      /* $@4  */
  YYSYMBOL_rel_expression = 63,            /* rel_expression  */
  YYSYMBOL_simple_expression = 64,         /* simple_expression  */
  YYSYMBOL_term = 65,                      /* term  */
  YYSYMBOL_unary_expression = 66,          /* unary_expression  */
  YYSYMBOL_factor = 67,                    /* factor  */
  YYSYMBOL_argument_list = 68,             /* argument_list  */
  YYSYMBOL_arguments = 69,                 /* arguments  */
  YYSYMBOL_M = 70,                         /* M  */
  YYSYMBOL_N = 71                          /* N  */
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
#define YYFINAL  11
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   139

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  42
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  30
/* YYNRULES -- Number of rules.  */
#define YYNRULES  70
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  133

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
       0,   224,   224,   239,   252,   266,   278,   290,   304,   342,
     377,   377,   397,   397,   417,   439,   458,   473,   489,   489,
     507,   524,   611,   624,   637,   652,   670,   693,   706,   725,
     738,   756,   768,   780,   792,   821,   840,   866,   887,   918,
     934,   946,   961,   993,  1030,  1047,  1103,  1120,  1120,  1196,
    1213,  1275,  1291,  1335,  1352,  1418,  1447,  1475,  1493,  1512,
    1557,  1577,  1598,  1612,  1636,  1663,  1679,  1686,  1704,  1719,
    1728
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
  "LSQUARE", "RSQUARE", "COMMA", "SEMICOLON", "ASSIGNOP", "NOT", "INCOP",
  "DECOP", "LOWER_THAN_ELSE", "$accept", "start", "program", "unit",
  "func_declaration", "func_definition", "$@1", "$@2", "parameter_list",
  "compound_statement", "$@3", "var_declaration", "type_specifier",
  "declaration_list", "statements", "statement", "expression_statement",
  "variable", "expression", "logic_expression", "$@4", "rel_expression",
  "simple_expression", "term", "unary_expression", "factor",
  "argument_list", "arguments", "M", "N", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-78)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-48)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int8 yypact[] =
{
      44,   -78,   -78,   -78,    33,    44,   -78,   -78,   -78,   -78,
      36,   -78,   -78,    -5,    -4,     6,    37,    41,   -78,    26,
      -9,    48,    40,    45,   -78,    50,    53,    44,   -78,   -78,
      71,    61,   -78,   -78,    50,    76,    65,   -78,    66,   -78,
     -78,   -78,    72,    74,   -78,    85,    79,     9,   -78,   -78,
      85,    85,   -78,    85,   -78,   -78,    89,    78,   -78,   -78,
      27,    75,   -78,    88,   -15,    86,   -78,   -78,    85,    62,
      87,    81,    98,    85,    85,     4,   -78,    90,   -78,    91,
     -78,    66,    85,   -78,   -78,   -78,    92,    85,    85,    85,
      95,   -78,    85,   -78,    96,   -78,    97,    93,    99,   -78,
     -78,   -78,   -78,    94,    86,   -78,   -78,    62,   100,   101,
     -78,    85,   -78,    85,    66,   -78,   -78,   -78,   -78,   -78,
     117,    85,    66,   -78,   -78,   -78,   -78,   102,    66,   -78,
     -78,    66,   -78
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       0,    22,    23,    24,     0,     2,     4,     6,     7,     5,
       0,     1,     3,    27,     0,     0,     0,     0,    21,    12,
       0,    17,     0,    25,     9,     0,    10,     0,    16,    28,
       0,    18,    13,     8,     0,    15,     0,    20,     0,    11,
      14,    26,     0,     0,    69,     0,     0,    42,    61,    62,
       0,     0,    40,     0,    33,    31,     0,    69,    29,    32,
      58,     0,    44,    46,    49,    51,    53,    57,     0,     0,
       0,     0,     0,    66,     0,    58,    55,     0,    56,    27,
      19,     0,     0,    63,    64,    41,     0,     0,     0,     0,
       0,    69,     0,    39,     0,    68,     0,    65,     0,    60,
      30,    45,    69,    50,    52,    54,    69,     0,     0,     0,
      59,     0,    43,     0,     0,    69,    69,    38,    67,    48,
      35,     0,     0,    70,    70,    37,    69,     0,     0,    69,
      36,     0,    34
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -78,   -78,   -78,   124,   -78,   -78,   -78,   -78,   -78,   -18,
     -78,    22,     3,   -78,   -78,   -77,   -55,   -48,   -45,   -62,
     -78,    18,    47,    51,   -41,   -78,   -78,   -78,   -56,    11
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
       0,     4,     5,     6,     7,     8,    34,    25,    20,    54,
      38,    55,    56,    14,    57,    58,    59,    60,    61,    62,
      86,    63,    64,    65,    66,    67,    96,    97,    70,   126
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      71,    81,    75,    10,   100,    75,    77,    32,    10,    76,
      87,    95,    78,    88,    91,     1,    39,     2,    21,     3,
     101,    26,     9,    90,    15,    75,    27,     9,    16,    98,
      35,    17,    18,    11,    75,   107,    19,   120,    73,    75,
      75,    75,    74,    83,    84,   125,   113,   108,   105,   118,
     114,   130,   115,     1,   132,     2,    13,     3,    22,   121,
     122,    23,    24,    75,    82,    75,    83,    84,    28,    42,
     128,    43,    44,   131,    29,     1,   124,     2,    30,     3,
      45,    31,    47,    48,    49,    46,    47,    48,    49,    33,
      50,    51,    36,    37,    50,    51,    40,    31,    52,    41,
      53,    68,    52,    69,    53,    47,    48,    49,    72,    79,
      80,    85,    89,    50,    51,   -47,    92,    93,    94,   102,
      99,   123,    88,    53,    16,   106,   109,   110,   111,    12,
     116,   119,   129,   112,   103,   127,     0,   117,     0,   104
};

static const yytype_int16 yycheck[] =
{
      45,    57,    50,     0,    81,    53,    51,    25,     5,    50,
      25,    73,    53,    28,    69,     9,    34,    11,    15,    13,
      82,    30,     0,    68,    29,    73,    35,     5,    33,    74,
      27,    35,    36,     0,    82,    91,    30,   114,    29,    87,
      88,    89,    33,    39,    40,   122,   102,    92,    89,   111,
     106,   128,   107,     9,   131,    11,    20,    13,    21,   115,
     116,    20,    36,   111,    37,   113,    39,    40,    20,     3,
     126,     5,     6,   129,    34,     9,   121,    11,    33,    13,
      14,    31,    20,    21,    22,    19,    20,    21,    22,    36,
      28,    29,    21,    32,    28,    29,    20,    31,    36,    34,
      38,    29,    36,    29,    38,    20,    21,    22,    29,    20,
      32,    36,    26,    28,    29,    27,    29,    36,    20,    27,
      30,     4,    28,    38,    33,    30,    30,    30,    35,     5,
      30,   113,    30,    34,    87,   124,    -1,    36,    -1,    88
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,     9,    11,    13,    43,    44,    45,    46,    47,    53,
      54,     0,    45,    20,    55,    29,    33,    35,    36,    30,
      50,    54,    21,    20,    36,    49,    30,    35,    20,    34,
      33,    31,    51,    36,    48,    54,    21,    32,    52,    51,
      20,    34,     3,     5,     6,    14,    19,    20,    21,    22,
      28,    29,    36,    38,    51,    53,    54,    56,    57,    58,
      59,    60,    61,    63,    64,    65,    66,    67,    29,    29,
      70,    60,    29,    29,    33,    59,    66,    60,    66,    20,
      32,    70,    37,    39,    40,    36,    62,    25,    28,    26,
      60,    58,    29,    36,    20,    61,    68,    69,    60,    30,
      57,    61,    27,    64,    65,    66,    30,    70,    60,    30,
      30,    35,    34,    70,    70,    58,    30,    36,    61,    63,
      57,    70,    70,     4,    60,    57,    71,    71,    70,    30,
      57,    70,    57
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    42,    43,    44,    44,    45,    45,    45,    46,    46,
      48,    47,    49,    47,    50,    50,    50,    50,    52,    51,
      51,    53,    54,    54,    54,    55,    55,    55,    55,    56,
      56,    57,    57,    57,    57,    57,    57,    57,    57,    57,
      58,    58,    59,    59,    60,    60,    61,    62,    61,    63,
      63,    64,    64,    65,    65,    66,    66,    66,    67,    67,
      67,    67,    67,    67,    67,    68,    68,    69,    69,    70,
      71
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     2,     1,     1,     1,     1,     6,     5,
       0,     7,     0,     6,     4,     3,     2,     1,     0,     4,
       2,     3,     1,     1,     1,     3,     6,     1,     4,     1,
       3,     1,     1,     1,    11,     6,    10,     7,     5,     3,
       1,     2,     1,     4,     1,     3,     1,     0,     5,     1,
       3,     1,     3,     1,     3,     2,     2,     1,     1,     4,
       3,     1,     1,     2,     2,     1,     0,     3,     1,     0,
       0
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
#line 225 "parser.y"
        {
		string rule="start : program";
        
        fout<<rule<<" "<<endl;
        (yyval.symbol_info) = new SymbolInfo("start", "program");
        (yyval.symbol_info)->message=rule;
        (yyval.symbol_info)->add((yyvsp[0].symbol_info));
        (yyval.symbol_info)->start=(yyvsp[0].symbol_info)->start;
        (yyval.symbol_info)->end=(yyvsp[0].symbol_info)->end;
        (yyval.symbol_info)->leaf=0;
        parse_tree_print((yyval.symbol_info));
	}
#line 1523 "y.tab.c"
    break;

  case 3: /* program: program unit  */
#line 240 "parser.y"
    {
        string rule="program : program unit";
        
        fout<<rule<<" "<<endl;
        (yyval.symbol_info) = new SymbolInfo("program", "program unit");
        (yyval.symbol_info)->message=rule;
        (yyval.symbol_info)->add((yyvsp[-1].symbol_info));
        (yyval.symbol_info)->add((yyvsp[0].symbol_info));
        (yyval.symbol_info)->start=(yyvsp[-1].symbol_info)->start;
        (yyval.symbol_info)->end=(yyvsp[0].symbol_info)->end;
        (yyval.symbol_info)->leaf=0;
    }
#line 1540 "y.tab.c"
    break;

  case 4: /* program: unit  */
#line 253 "parser.y"
    {
        string rule="program : unit";
        
        fout<<rule<<" "<<endl;
        (yyval.symbol_info) = new SymbolInfo("program", "unit");
        (yyval.symbol_info)->message=rule;
        (yyval.symbol_info)->add((yyvsp[0].symbol_info));
        (yyval.symbol_info)->start=(yyvsp[0].symbol_info)->start;
        (yyval.symbol_info)->end=(yyvsp[0].symbol_info)->end;
        (yyval.symbol_info)->leaf=0;
    }
#line 1556 "y.tab.c"
    break;

  case 5: /* unit: var_declaration  */
#line 267 "parser.y"
    {
        string rule="unit : var_declaration";
        
        fout<<rule<<" "<<endl;
        (yyval.symbol_info) = new SymbolInfo("unit", "var_declaration");
        (yyval.symbol_info)->message=rule;
        (yyval.symbol_info)->add((yyvsp[0].symbol_info));
        (yyval.symbol_info)->start=(yyvsp[0].symbol_info)->start;
        (yyval.symbol_info)->end=(yyvsp[0].symbol_info)->end;
        (yyval.symbol_info)->leaf=0;
    }
#line 1572 "y.tab.c"
    break;

  case 6: /* unit: func_declaration  */
#line 279 "parser.y"
     {
        string rule="unit : func_declaration";
        
        fout<<rule<<" "<<endl;
        (yyval.symbol_info) = new SymbolInfo("unit", "func_declaration");
        (yyval.symbol_info)->message=rule;;
        (yyval.symbol_info)->start=(yyvsp[0].symbol_info)->start;
        (yyval.symbol_info)->end=(yyvsp[0].symbol_info)->end;
        (yyval.symbol_info)->leaf=0;
        (yyval.symbol_info)->add((yyvsp[0].symbol_info));
     }
#line 1588 "y.tab.c"
    break;

  case 7: /* unit: func_definition  */
#line 291 "parser.y"
     {
        string rule="unit : func_definition";
        
        fout<<rule<<" "<<endl;
        (yyval.symbol_info) = new SymbolInfo("unit", "func_definition");
        (yyval.symbol_info)->message=rule;
        (yyval.symbol_info)->add((yyvsp[0].symbol_info));
        (yyval.symbol_info)->start=(yyvsp[0].symbol_info)->start;
        (yyval.symbol_info)->end=(yyvsp[0].symbol_info)->end;
        (yyval.symbol_info)->leaf=0;
     }
#line 1604 "y.tab.c"
    break;

  case 8: /* func_declaration: type_specifier ID LPAREN parameter_list RPAREN SEMICOLON  */
#line 305 "parser.y"
    {
        string rule="func_declaration : type_specifier ID LPAREN parameter_list RPAREN SEMICOLON";
        
        fout<<rule<<" "<<endl;
        (yyval.symbol_info) = new SymbolInfo("func_declaration", "type_specifier ID LPAREN parameter_list RPAREN SEMICOLON");
        (yyval.symbol_info)->message=rule;
        (yyval.symbol_info)->add((yyvsp[-5].symbol_info));
        (yyval.symbol_info)->add((yyvsp[-4].symbol_info));
        (yyval.symbol_info)->add((yyvsp[-3].symbol_info));
        (yyval.symbol_info)->add((yyvsp[-2].symbol_info));
        (yyval.symbol_info)->add((yyvsp[-1].symbol_info));
        (yyval.symbol_info)->add((yyvsp[0].symbol_info));
        (yyval.symbol_info)->start=(yyvsp[-5].symbol_info)->start;
        (yyval.symbol_info)->end=(yyvsp[0].symbol_info)->end;
        (yyval.symbol_info)->leaf=0;
        SymbolInfo *temp = table->LookUp((yyvsp[-4].symbol_info)->getName());
        if(temp!=NULL)
        {
            //fout<<"Line# "<<line_count<<": Redeclaration of "<<$2->getName()<<endl;
            if(temp->optional=="FUNCTION")
            eout<<"Line# "<<line_count<<": Redeclaration of "<<(yyvsp[-4].symbol_info)->getName()<<endl;
            else
            eout<<"Line# "<<line_count<<": "<<(yyvsp[-4].symbol_info)->getName()<<"' redeclared as different kind of symbol "<<endl;
            error++;
        }
        else
        {
            SymbolInfo *ftemp=new SymbolInfo((yyvsp[-4].symbol_info)->getName(), (yyvsp[-5].symbol_info)->getType());
            ftemp->optional="FUNCTION";
            for(int i=0; i<(yyvsp[-2].symbol_info)->var_dec_list.size(); i++)
            {
                ftemp->func_dec_list.push_back((yyvsp[-2].symbol_info)->var_dec_list[i]);
            }
            table->opt_insert(ftemp->getName(), ftemp->getType(), ftemp->optional);
            //print_all();
        }
    }
#line 1646 "y.tab.c"
    break;

  case 9: /* func_declaration: type_specifier ID LPAREN RPAREN SEMICOLON  */
#line 343 "parser.y"
        {
        string rule="func_declaration : type_specifier ID LPAREN RPAREN SEMICOLON";
        
        fout<<rule<<" "<<endl;
        (yyval.symbol_info) = new SymbolInfo("func_declaration", "type_specifier ID LPAREN RPAREN SEMICOLON");
        (yyval.symbol_info)->message=rule;
        (yyval.symbol_info)->add((yyvsp[-4].symbol_info));
        (yyval.symbol_info)->add((yyvsp[-3].symbol_info));
        (yyval.symbol_info)->add((yyvsp[-2].symbol_info));
        (yyval.symbol_info)->add((yyvsp[-1].symbol_info));
        (yyval.symbol_info)->add((yyvsp[0].symbol_info));
        (yyval.symbol_info)->start=(yyvsp[-4].symbol_info)->start;
        (yyval.symbol_info)->end=(yyvsp[0].symbol_info)->end;
        (yyval.symbol_info)->leaf=0;
        SymbolInfo *temp = table->LookUp((yyvsp[-3].symbol_info)->getName());
        if(temp!=NULL)
        {
            //fout<<"Line# "<<line_count<<": Redeclaration of "<<$2->getName()<<endl;
            if(temp->optional=="FUNCTION")
            eout<<"Line# "<<line_count<<": Redeclaration of "<<(yyvsp[-3].symbol_info)->getName()<<endl;
            else
            eout<<"Line# "<<line_count<<" :'"<<(yyvsp[-3].symbol_info)->getName()<<"' redeclared as different kind of symbol "<<endl;
            error++;
        }
        else
        {
            SymbolInfo *ftemp=new SymbolInfo((yyvsp[-3].symbol_info)->getName(), (yyvsp[-4].symbol_info)->getType());
            ftemp->optional="FUNCTION";
            table->opt_insert(ftemp->getName(), ftemp->getType(), ftemp->optional);
            //print_all();
        }
        }
#line 1683 "y.tab.c"
    break;

  case 10: /* $@1: %empty  */
#line 377 "parser.y"
                                                                 {function_into_scope((yyvsp[-3].symbol_info),(yyvsp[-4].symbol_info),(yyvsp[-1].symbol_info));}
#line 1689 "y.tab.c"
    break;

  case 11: /* func_definition: type_specifier ID LPAREN parameter_list RPAREN $@1 compound_statement  */
#line 378 "parser.y"
{
    string rule="func_definition : type_specifier ID LPAREN parameter_list RPAREN compound_statement";
    
        fout<<rule<<" "<<endl;
    (yyval.symbol_info) = new SymbolInfo("func_definition", "type_specifier ID LPAREN parameter_list RPAREN compound_statement");
        (yyval.symbol_info)->message=rule;
        (yyval.symbol_info)->add((yyvsp[-6].symbol_info));
        (yyval.symbol_info)->add((yyvsp[-5].symbol_info));
        (yyval.symbol_info)->add((yyvsp[-4].symbol_info));
        (yyval.symbol_info)->add((yyvsp[-3].symbol_info));
        (yyval.symbol_info)->add((yyvsp[-2].symbol_info));
        //$$->add($6);
        (yyval.symbol_info)->add((yyvsp[0].symbol_info));
        (yyval.symbol_info)->start=(yyvsp[-6].symbol_info)->start;
        (yyval.symbol_info)->end=(yyvsp[0].symbol_info)->end;
        (yyval.symbol_info)->leaf=0;
        //tout<<$2->getName()<<" PROC"<<endl;

}
#line 1713 "y.tab.c"
    break;

  case 12: /* $@2: %empty  */
#line 397 "parser.y"
                                                  {function_into_scope((yyvsp[-2].symbol_info),(yyvsp[-3].symbol_info),new SymbolInfo());}
#line 1719 "y.tab.c"
    break;

  case 13: /* func_definition: type_specifier ID LPAREN RPAREN $@2 compound_statement  */
#line 398 "parser.y"
        {
        string rule="func_definition : type_specifier ID LPAREN RPAREN compound_statement";
        
        fout<<rule<<" "<<endl;
        (yyval.symbol_info) = new SymbolInfo("func_definition", "type_specifier ID LPAREN RPAREN compound_statement");
        (yyval.symbol_info)->message=rule;
        (yyval.symbol_info)->add((yyvsp[-5].symbol_info));
        (yyval.symbol_info)->add((yyvsp[-4].symbol_info));
        (yyval.symbol_info)->add((yyvsp[-3].symbol_info));
        (yyval.symbol_info)->add((yyvsp[-2].symbol_info));
        //$$->add($5);
        (yyval.symbol_info)->add((yyvsp[0].symbol_info));
        (yyval.symbol_info)->start=(yyvsp[-5].symbol_info)->start;
        (yyval.symbol_info)->end=(yyvsp[0].symbol_info)->end;
        (yyval.symbol_info)->leaf=0;
        }
#line 1740 "y.tab.c"
    break;

  case 14: /* parameter_list: parameter_list COMMA type_specifier ID  */
#line 418 "parser.y"
{
    string rule="parameter_list : parameter_list COMMA type_specifier ID";
    
        fout<<rule<<" "<<endl;
        (yyval.symbol_info) = new SymbolInfo("parameter_list", "parameter_list COMMA type_specifier ID");
        (yyval.symbol_info)->message=rule;
        (yyval.symbol_info)->add((yyvsp[-3].symbol_info));
        (yyval.symbol_info)->add((yyvsp[-2].symbol_info));
        (yyval.symbol_info)->add((yyvsp[-1].symbol_info));
        (yyval.symbol_info)->add((yyvsp[0].symbol_info));
        (yyval.symbol_info)->start=(yyvsp[-3].symbol_info)->start;
        (yyval.symbol_info)->end=(yyvsp[0].symbol_info)->end;
        (yyval.symbol_info)->leaf=0;
        (yyvsp[0].symbol_info)->setType((yyvsp[-1].symbol_info)->getType());
        for(int i=0;i<(yyvsp[-3].symbol_info)->var_dec_list.size();i++)
        {
            (yyval.symbol_info)->var_dec_list.push_back((yyvsp[-3].symbol_info)->var_dec_list[i]);
        }
        (yyvsp[0].symbol_info)->setType((yyvsp[-1].symbol_info)->getType());
        (yyval.symbol_info)->var_dec_list.push_back((yyvsp[0].symbol_info));
}
#line 1766 "y.tab.c"
    break;

  case 15: /* parameter_list: parameter_list COMMA type_specifier  */
#line 440 "parser.y"
        {
        string rule="parameter_list : parameter_list COMMA type_specifier";
        
        fout<<rule<<" "<<endl;
        (yyval.symbol_info) = new SymbolInfo("parameter_list", "parameter_list COMMA type_specifier");
        (yyval.symbol_info)->message=rule;
        (yyval.symbol_info)->add((yyvsp[-2].symbol_info));
        (yyval.symbol_info)->add((yyvsp[-1].symbol_info));
        (yyval.symbol_info)->add((yyvsp[0].symbol_info));
        (yyval.symbol_info)->start=(yyvsp[-2].symbol_info)->start;
        (yyval.symbol_info)->end=(yyvsp[0].symbol_info)->end;
        (yyval.symbol_info)->leaf=0;
        for(int i=0;i<(yyvsp[-2].symbol_info)->var_dec_list.size();i++)
        {
            (yyval.symbol_info)->var_dec_list.push_back((yyvsp[-2].symbol_info)->var_dec_list[i]);
        }
        (yyval.symbol_info)->var_dec_list.push_back((yyvsp[0].symbol_info));
        }
#line 1789 "y.tab.c"
    break;

  case 16: /* parameter_list: type_specifier ID  */
#line 459 "parser.y"
        {
        string rule="parameter_list : type_specifier ID";
        
        fout<<rule<<" "<<endl;
        (yyval.symbol_info) = new SymbolInfo("parameter_list", "type_specifier ID");
        (yyval.symbol_info)->message=rule;
        (yyval.symbol_info)->add((yyvsp[-1].symbol_info));
        (yyval.symbol_info)->add((yyvsp[0].symbol_info));
        (yyval.symbol_info)->start=(yyvsp[-1].symbol_info)->start;
        (yyval.symbol_info)->end=(yyvsp[0].symbol_info)->end;
        (yyval.symbol_info)->leaf=0;
        (yyvsp[0].symbol_info)->setType((yyvsp[-1].symbol_info)->getType());
        (yyval.symbol_info)->var_dec_list.push_back((yyvsp[0].symbol_info));
        }
#line 1808 "y.tab.c"
    break;

  case 17: /* parameter_list: type_specifier  */
#line 474 "parser.y"
        {
        string rule="parameter_list : type_specifier";
        
        fout<<rule<<" "<<endl;
        (yyval.symbol_info) = new SymbolInfo("parameter_list", "type_specifier");
        (yyval.symbol_info)->message=rule;
        (yyval.symbol_info)->add((yyvsp[0].symbol_info));
        (yyval.symbol_info)->start=(yyvsp[0].symbol_info)->start;
        (yyval.symbol_info)->end=(yyvsp[0].symbol_info)->end;
        (yyval.symbol_info)->leaf=0;
        (yyval.symbol_info)->var_dec_list.push_back((yyvsp[0].symbol_info));
        }
#line 1825 "y.tab.c"
    break;

  case 18: /* $@3: %empty  */
#line 489 "parser.y"
                           {table->enter_scope();}
#line 1831 "y.tab.c"
    break;

  case 19: /* compound_statement: LCURL $@3 statements RCURL  */
#line 490 "parser.y"
{
        string rule="compound_statement : LCURL statements RCURL";
        
        fout<<rule<<" "<<endl;
        (yyval.symbol_info) = new SymbolInfo("compound_statement", "LCURL statements RCURL");
        (yyval.symbol_info)->message=rule;
        (yyval.symbol_info)->add((yyvsp[-3].symbol_info));
        //$$->add($2);
        (yyval.symbol_info)->add((yyvsp[-1].symbol_info));
        (yyval.symbol_info)->add((yyvsp[0].symbol_info));
        (yyval.symbol_info)->start=(yyvsp[-3].symbol_info)->start;
        (yyval.symbol_info)->end=(yyvsp[0].symbol_info)->end;
        (yyval.symbol_info)->leaf=0;
        print_all();
        table->exit_scope();
        func_check=1;
}
#line 1853 "y.tab.c"
    break;

  case 20: /* compound_statement: LCURL RCURL  */
#line 508 "parser.y"
            {
        string rule="compound_statement : LCURL RCURL";
        
        fout<<rule<<" "<<endl;
        (yyval.symbol_info) = new SymbolInfo("compound_statement", "LCURL RCURL");
        (yyval.symbol_info)->message=rule;
        (yyval.symbol_info)->add((yyvsp[-1].symbol_info));
        (yyval.symbol_info)->add((yyvsp[0].symbol_info));
        (yyval.symbol_info)->start=(yyvsp[-1].symbol_info)->start;
        (yyval.symbol_info)->end=(yyvsp[0].symbol_info)->end;
        (yyval.symbol_info)->leaf=0;
        print_all();
        table->exit_scope();
            }
#line 1872 "y.tab.c"
    break;

  case 21: /* var_declaration: type_specifier declaration_list SEMICOLON  */
#line 525 "parser.y"
{
    string rule="var_declaration : type_specifier declaration_list SEMICOLON";
    
        fout<<rule<<" "<<endl;
        (yyval.symbol_info) = new SymbolInfo("var_declaration", "type_specifier declaration_list SEMICOLON");
        (yyval.symbol_info)->message=rule;
        (yyval.symbol_info)->add((yyvsp[-2].symbol_info));
        (yyval.symbol_info)->add((yyvsp[-1].symbol_info));
        (yyval.symbol_info)->add((yyvsp[0].symbol_info));
        (yyval.symbol_info)->start=(yyvsp[-2].symbol_info)->start;
        (yyval.symbol_info)->end=(yyvsp[0].symbol_info)->end;
        (yyval.symbol_info)->leaf=0;
        if(table->getScopeCount()==1){
            //$$->isGlobal=true;
            for(int i=0;i<(yyvsp[-1].symbol_info)->var_dec_list.size();i++){
                    (yyvsp[-1].symbol_info)->var_dec_list[i]->is_global=true;
                    if((yyvsp[-1].symbol_info)->var_dec_list[i]->optional!="ARRAY")
                    finalout<<(yyvsp[-1].symbol_info)->var_dec_list[i]->getName()<<" DW 1 DUP (0000H)"<<endl;
                    else{
                        finalout<<(yyvsp[-1].symbol_info)->var_dec_list[i]->getName()<<" DW "<<(yyvsp[-1].symbol_info)->var_dec_list[i]->array_size<<" DUP (0000H)"<<endl;
                    }
            }
        }
        else{
            setoffset=table->current->scope_offset;
            for(int i=0;i<(yyvsp[-1].symbol_info)->var_dec_list.size();i++){
                (yyvsp[-1].symbol_info)->var_dec_list[i]->is_global=false;
                   if((yyvsp[-1].symbol_info)->var_dec_list[i]->optional!="ARRAY"){
                          setoffset=setoffset+2;
                          table->current->scope_offset=setoffset;
                        (yyvsp[-1].symbol_info)->var_dec_list[i]->offset=setoffset;
                        tout<<"SUB SP, 2"<<endl;
                        temp_line_count++;
                   }
                    
                    else{
                        (yyvsp[-1].symbol_info)->var_dec_list[i]->offset=setoffset+2;
                        setoffset=setoffset+2*(yyvsp[-1].symbol_info)->var_dec_list[i]->array_size;
                        table->current->scope_offset=setoffset;
                        tout<<"SUB SP, "<<2*(yyvsp[-1].symbol_info)->var_dec_list[i]->array_size<<endl;
                        temp_line_count++;
                    }
            }
            
        }
        if((yyvsp[-2].symbol_info)->getType()=="VOID"){
            error++;
            for(int i=0;i<(yyvsp[-1].symbol_info)->var_dec_list.size();i++){
                    eout<<"Line# "<<line_count<<": Variable or field '"<<(yyvsp[-1].symbol_info)->var_dec_list[i]->getName()<<"' declared void"<<endl;
            }
        }
        else{
            
            if ((yyvsp[-1].symbol_info) == nullptr) cout << "wtf2" << endl;
           for(int i=0;i<(yyvsp[-1].symbol_info)->var_dec_list.size();i++){
            if(table->Scope_LookUp((yyvsp[-1].symbol_info)->var_dec_list[i]->getName())==nullptr){
                if((yyvsp[-1].symbol_info)->var_dec_list[i]->optional!="ARRAY"){
                    //table->insert($2->var_dec_list[i]->getName(),$1->getType());
                    table->sinsert((yyvsp[-1].symbol_info)->var_dec_list[i]);
                }   
                else{
                    //table->opt_insert($2->var_dec_list[i]->getName(),$1->getType(),$2->var_dec_list[i]->optional);
                    table->osinsert((yyvsp[-1].symbol_info)->var_dec_list[i]);
                }
            }
            else{
                error++;
                SymbolInfo* s=new SymbolInfo();
                s=table->Scope_LookUp((yyvsp[-1].symbol_info)->var_dec_list[i]->getName());
                if((yyvsp[-2].symbol_info)->getType()!=s->getType()){
                    eout<<"Line# "<<line_count<<": Conflicting types for'"<<s->getName()<<"'"<<endl;
                }
                else {
                    if((yyvsp[-2].symbol_info)->optional!=s->optional){
                        eout<<"Line# "<<line_count<<": '"<<s->getName()<<"' redeclared as different kind of symbol "<<endl;
                    }
                    else{
                        eout<<"Line# "<<line_count<<": Redefinition of parameter '"<<s->getName()<<"'"<<endl;
                    }
                }
            }
           } 
        }
}
#line 1961 "y.tab.c"
    break;

  case 22: /* type_specifier: INT  */
#line 612 "parser.y"
{
    string rule="type_specifier : INT";
    
        fout<<rule<<" "<<endl;
        (yyval.symbol_info) = new SymbolInfo((yyvsp[0].symbol_info)->getName(), "INT");
        (yyval.symbol_info)->message=rule;
        (yyval.symbol_info)->add((yyvsp[0].symbol_info));
        (yyval.symbol_info)->start=(yyvsp[0].symbol_info)->start;
        (yyval.symbol_info)->end=(yyvsp[0].symbol_info)->end;
        (yyval.symbol_info)->leaf=0;
    //    $1->getName()<<endl;
}
#line 1978 "y.tab.c"
    break;

  case 23: /* type_specifier: FLOAT  */
#line 625 "parser.y"
        {
    string rule="type_specifier : FLOAT";
    
        fout<<rule<<" "<<endl;
        (yyval.symbol_info) = new SymbolInfo((yyvsp[0].symbol_info)->getName(), "FLOAT");
        (yyval.symbol_info)->message=rule;
        (yyval.symbol_info)->add((yyvsp[0].symbol_info));
    (yyval.symbol_info)->start=(yyvsp[0].symbol_info)->start;
        (yyval.symbol_info)->end=(yyvsp[0].symbol_info)->end;
        (yyval.symbol_info)->leaf=0;
        //    $1->getName()<<endl;
}
#line 1995 "y.tab.c"
    break;

  case 24: /* type_specifier: VOID  */
#line 638 "parser.y"
        {
    string rule="type_specifier : VOID";
    
        fout<<rule<<" "<<endl;
        (yyval.symbol_info) = new SymbolInfo((yyvsp[0].symbol_info)->getName(), "VOID");
        (yyval.symbol_info)->message=rule;
        (yyval.symbol_info)->add((yyvsp[0].symbol_info));
        (yyval.symbol_info)->start=(yyvsp[0].symbol_info)->start;
        (yyval.symbol_info)->end=(yyvsp[0].symbol_info)->end;
        (yyval.symbol_info)->leaf=0;
        //    $1->getName()<<endl;
}
#line 2012 "y.tab.c"
    break;

  case 25: /* declaration_list: declaration_list COMMA ID  */
#line 653 "parser.y"
{
    string rule="declaration_list : declaration_list COMMA ID";
    
        fout<<rule<<" "<<endl;
        (yyval.symbol_info) = new SymbolInfo("declaration_list", "declaration_list COMMA ID");
        (yyval.symbol_info)->message=rule;
        (yyval.symbol_info)->add((yyvsp[-2].symbol_info));
        (yyval.symbol_info)->add((yyvsp[-1].symbol_info));
        (yyval.symbol_info)->add((yyvsp[0].symbol_info));
        (yyval.symbol_info)->start=(yyvsp[-2].symbol_info)->start;
        (yyval.symbol_info)->end=(yyvsp[0].symbol_info)->end;
        (yyval.symbol_info)->leaf=0;
        for(int i=0;i<(yyvsp[-2].symbol_info)->var_dec_list.size();i++){
            (yyval.symbol_info)->var_dec_list.push_back((yyvsp[-2].symbol_info)->var_dec_list[i]);
        }
        (yyval.symbol_info)->var_dec_list.push_back((yyvsp[0].symbol_info));
}
#line 2034 "y.tab.c"
    break;

  case 26: /* declaration_list: declaration_list COMMA ID LSQUARE CONST_INT RSQUARE  */
#line 671 "parser.y"
          {
    string rule="declaration_list : declaration_list COMMA ID LSQUARE CONST_INT RSQUARE";
    
        fout<<rule<<" "<<endl;
        (yyval.symbol_info) = new SymbolInfo("declaration_list", "declaration_list COMMA ID LSQUARE CONST_INT RSQUARE");
        (yyval.symbol_info)->message=rule;
        (yyval.symbol_info)->add((yyvsp[-5].symbol_info));
        (yyval.symbol_info)->add((yyvsp[-4].symbol_info));
        (yyval.symbol_info)->add((yyvsp[-3].symbol_info));
        (yyval.symbol_info)->add((yyvsp[-2].symbol_info));
        (yyval.symbol_info)->add((yyvsp[-1].symbol_info));
        (yyval.symbol_info)->add((yyvsp[0].symbol_info));
        (yyval.symbol_info)->start=(yyvsp[-5].symbol_info)->start;
        (yyval.symbol_info)->end=(yyvsp[0].symbol_info)->end;
        (yyval.symbol_info)->leaf=0;
        for(int i=0;i<(yyvsp[-5].symbol_info)->var_dec_list.size();i++){
            (yyval.symbol_info)->var_dec_list.push_back((yyvsp[-5].symbol_info)->var_dec_list[i]);
        }
        (yyvsp[-3].symbol_info)->optional="ARRAY";
        (yyvsp[-3].symbol_info)->array_size=stoi((yyvsp[-1].symbol_info)->getName());
        (yyval.symbol_info)->var_dec_list.push_back((yyvsp[-3].symbol_info));
}
#line 2061 "y.tab.c"
    break;

  case 27: /* declaration_list: ID  */
#line 694 "parser.y"
          {
        string rule="declaration_list : ID";
        
        fout<<rule<<" "<<endl;
        (yyval.symbol_info) = new SymbolInfo("declaration_list", "ID");
        (yyval.symbol_info)->message=rule;
        (yyval.symbol_info)->add((yyvsp[0].symbol_info));
        (yyval.symbol_info)->start=(yyvsp[0].symbol_info)->start;
        (yyval.symbol_info)->end=(yyvsp[0].symbol_info)->end;
        (yyval.symbol_info)->leaf=0;
        (yyval.symbol_info)->var_dec_list.push_back((yyvsp[0].symbol_info));
          }
#line 2078 "y.tab.c"
    break;

  case 28: /* declaration_list: ID LSQUARE CONST_INT RSQUARE  */
#line 707 "parser.y"
          {
            string rule="declaration_list : ID LSQUARE CONST_INT RSQUARE";
            
        fout<<rule<<" "<<endl;
        (yyval.symbol_info) = new SymbolInfo("declaration_list", "ID LSQUARE CONST_INT RSQUARE");
        (yyval.symbol_info)->message=rule;
        (yyval.symbol_info)->add((yyvsp[-3].symbol_info));
        (yyval.symbol_info)->add((yyvsp[-2].symbol_info));
        (yyval.symbol_info)->add((yyvsp[-1].symbol_info));
        (yyval.symbol_info)->add((yyvsp[0].symbol_info));
        (yyval.symbol_info)->start=(yyvsp[-3].symbol_info)->start;
        (yyval.symbol_info)->end=(yyvsp[0].symbol_info)->end;
        (yyval.symbol_info)->leaf=0;
        (yyvsp[-3].symbol_info)->optional="ARRAY";
        (yyval.symbol_info)->var_dec_list.push_back((yyvsp[-3].symbol_info));
          }
#line 2099 "y.tab.c"
    break;

  case 29: /* statements: statement  */
#line 726 "parser.y"
{
        string rule="statements : statement";
        
        fout<<rule<<" "<<endl;
        (yyval.symbol_info) = new SymbolInfo("statements", "statement");
        (yyval.symbol_info)->message=rule;
        (yyval.symbol_info)->add((yyvsp[0].symbol_info));
        (yyval.symbol_info)->start=(yyvsp[0].symbol_info)->start;
        (yyval.symbol_info)->end=(yyvsp[0].symbol_info)->end;
        (yyval.symbol_info)->leaf=0;
        (yyval.symbol_info)->nextlist=(yyvsp[0].symbol_info)->nextlist;
}
#line 2116 "y.tab.c"
    break;

  case 30: /* statements: statements M statement  */
#line 739 "parser.y"
       {
        string rule="statements : statements statement";
        
        fout<<rule<<" "<<endl;
        (yyval.symbol_info) = new SymbolInfo("statements", "statements statement");
        (yyval.symbol_info)->message=rule;
        (yyval.symbol_info)->add((yyvsp[-2].symbol_info));
        (yyval.symbol_info)->add((yyvsp[-1].symbol_info));
        (yyval.symbol_info)->add((yyvsp[0].symbol_info));
        (yyval.symbol_info)->start=(yyvsp[-2].symbol_info)->start;
        (yyval.symbol_info)->end=(yyvsp[0].symbol_info)->end;
        (yyval.symbol_info)->leaf=0;
        backpatch((yyvsp[-2].symbol_info)->nextlist,(yyvsp[-1].symbol_info)->label);
        (yyval.symbol_info)->nextlist=(yyvsp[0].symbol_info)->nextlist;
       }
#line 2136 "y.tab.c"
    break;

  case 31: /* statement: var_declaration  */
#line 757 "parser.y"
{
        string rule="statement : var_declaration";
        
        fout<<rule<<" "<<endl;
        (yyval.symbol_info) = new SymbolInfo("statement", "var_declaration");
        (yyval.symbol_info)->message=rule;
        (yyval.symbol_info)->add((yyvsp[0].symbol_info));   
        (yyval.symbol_info)->start=(yyvsp[0].symbol_info)->start;
        (yyval.symbol_info)->end=(yyvsp[0].symbol_info)->end;
        (yyval.symbol_info)->leaf=0;
}
#line 2152 "y.tab.c"
    break;

  case 32: /* statement: expression_statement  */
#line 769 "parser.y"
      {
        string rule="statement : expression_statement";
        
        fout<<rule<<" "<<endl;
        (yyval.symbol_info) = new SymbolInfo("statement", "expression_statement");
        (yyval.symbol_info)->message=rule;
        (yyval.symbol_info)->add((yyvsp[0].symbol_info));
        (yyval.symbol_info)->start=(yyvsp[0].symbol_info)->start;
        (yyval.symbol_info)->end=(yyvsp[0].symbol_info)->end;
        (yyval.symbol_info)->leaf=0;
      }
#line 2168 "y.tab.c"
    break;

  case 33: /* statement: compound_statement  */
#line 781 "parser.y"
      {
        string rule="statement : compound_statement";
        
        fout<<rule<<" "<<endl;
        (yyval.symbol_info) = new SymbolInfo("statement","compound_statement");
        (yyval.symbol_info)->message=rule;
        (yyval.symbol_info)->add((yyvsp[0].symbol_info));
        (yyval.symbol_info)->start=(yyvsp[0].symbol_info)->start;
        (yyval.symbol_info)->end=(yyvsp[0].symbol_info)->end;
        (yyval.symbol_info)->leaf=0;
      }
#line 2184 "y.tab.c"
    break;

  case 34: /* statement: FOR LPAREN expression_statement M expression_statement M expression N RPAREN M statement  */
#line 793 "parser.y"
      {
        string rule="statement: FOR LPAREN expression_statement expression_statement expression RPAREN statement";
        
        fout<<rule<<" "<<endl;
        (yyval.symbol_info) = new SymbolInfo("statement","FOR LPAREN expression_statement expression_statement expression RPAREN statement");
        (yyval.symbol_info)->message=rule;
        (yyval.symbol_info)->add((yyvsp[-10].symbol_info));
        (yyval.symbol_info)->add((yyvsp[-9].symbol_info));
        (yyval.symbol_info)->add((yyvsp[-8].symbol_info));
        (yyval.symbol_info)->add((yyvsp[-7].symbol_info));
        (yyval.symbol_info)->add((yyvsp[-6].symbol_info));
        (yyval.symbol_info)->add((yyvsp[-5].symbol_info));
        (yyval.symbol_info)->add((yyvsp[-4].symbol_info));
        (yyval.symbol_info)->add((yyvsp[-3].symbol_info));
        (yyval.symbol_info)->add((yyvsp[-2].symbol_info));
        (yyval.symbol_info)->add((yyvsp[-1].symbol_info));
        (yyval.symbol_info)->add((yyvsp[0].symbol_info));
        (yyval.symbol_info)->start=(yyvsp[-10].symbol_info)->start;
        (yyval.symbol_info)->end=(yyvsp[-4].symbol_info)->end;
        (yyval.symbol_info)->leaf=0;
        backpatch((yyvsp[-8].symbol_info)->nextlist,(yyvsp[-7].symbol_info)->label);
        backpatch((yyvsp[-6].symbol_info)->truelist,(yyvsp[-1].symbol_info)->label);
        backpatch((yyvsp[-4].symbol_info)->nextlist,(yyvsp[-7].symbol_info)->label);
        backpatch((yyvsp[0].symbol_info)->nextlist,(yyvsp[-5].symbol_info)->label);
        backpatch((yyvsp[-3].symbol_info)->nextlist,(yyvsp[-7].symbol_info)->label);
        (yyval.symbol_info)->nextlist=(yyvsp[-6].symbol_info)->falselist;
        tout<<"JMP "<<(yyvsp[-5].symbol_info)->label<<endl;
      }
#line 2217 "y.tab.c"
    break;

  case 35: /* statement: IF LPAREN expression RPAREN M statement  */
#line 822 "parser.y"
      {
        string rule="statement: IF LPAREN expression RPAREN statement";
        
        fout<<rule<<" "<<endl;
        (yyval.symbol_info) = new SymbolInfo("statement","IF LPAREN expression RPAREN statement");
        (yyval.symbol_info)->message=rule;
        (yyval.symbol_info)->add((yyvsp[-5].symbol_info));
        (yyval.symbol_info)->add((yyvsp[-4].symbol_info));
        (yyval.symbol_info)->add((yyvsp[-3].symbol_info));
        (yyval.symbol_info)->add((yyvsp[-2].symbol_info));
        (yyval.symbol_info)->add((yyvsp[-1].symbol_info));
        (yyval.symbol_info)->add((yyvsp[0].symbol_info));
        (yyval.symbol_info)->start=(yyvsp[-5].symbol_info)->start;
        (yyval.symbol_info)->end=(yyvsp[-1].symbol_info)->end;
        (yyval.symbol_info)->leaf=0;
        backpatch((yyvsp[-3].symbol_info)->truelist,(yyvsp[-1].symbol_info)->label);
        (yyval.symbol_info)->nextlist=merge((yyvsp[-3].symbol_info)->falselist,(yyvsp[0].symbol_info)->nextlist);
      }
#line 2240 "y.tab.c"
    break;

  case 36: /* statement: IF LPAREN expression RPAREN M statement ELSE N M statement  */
#line 841 "parser.y"
      {
        string rule="statement: IF LPAREN expression RPAREN statement ELSE statement";
        
        fout<<rule<<" "<<endl;
        (yyval.symbol_info) = new SymbolInfo("statement","IF LPAREN expression RPAREN statement ELSE statement");
        (yyval.symbol_info)->message=rule;
        (yyval.symbol_info)->add((yyvsp[-9].symbol_info));
        (yyval.symbol_info)->add((yyvsp[-8].symbol_info));
        (yyval.symbol_info)->add((yyvsp[-7].symbol_info));
        (yyval.symbol_info)->add((yyvsp[-6].symbol_info));
        (yyval.symbol_info)->add((yyvsp[-5].symbol_info));
        (yyval.symbol_info)->add((yyvsp[-4].symbol_info));
        (yyval.symbol_info)->add((yyvsp[-3].symbol_info));
        (yyval.symbol_info)->add((yyvsp[-2].symbol_info));
        (yyval.symbol_info)->add((yyvsp[-1].symbol_info));
        (yyval.symbol_info)->add((yyvsp[0].symbol_info));
        (yyval.symbol_info)->start=(yyvsp[-9].symbol_info)->start;
        (yyval.symbol_info)->end=(yyvsp[-3].symbol_info)->end;
        (yyval.symbol_info)->leaf=0;
        backpatch((yyvsp[-7].symbol_info)->truelist,(yyvsp[-5].symbol_info)->label);
        backpatch((yyvsp[-7].symbol_info)->falselist,(yyvsp[-1].symbol_info)->label);
        vector temp=merge((yyvsp[-4].symbol_info)->nextlist,(yyvsp[-3].symbol_info)->nextlist);
        (yyval.symbol_info)->nextlist=merge(temp,(yyvsp[0].symbol_info)->nextlist);

      }
#line 2270 "y.tab.c"
    break;

  case 37: /* statement: WHILE M LPAREN expression RPAREN M statement  */
#line 867 "parser.y"
      {
        string rule="statement: WHILE LPAREN expression RPAREN statement";
        
        fout<<rule<<" "<<endl;
        (yyval.symbol_info) = new SymbolInfo("statement","WHILE LPAREN expression RPAREN statement");
        (yyval.symbol_info)->message=rule;
        (yyval.symbol_info)->add((yyvsp[-6].symbol_info));
        (yyval.symbol_info)->add((yyvsp[-5].symbol_info));
        (yyval.symbol_info)->add((yyvsp[-4].symbol_info));
        (yyval.symbol_info)->add((yyvsp[-3].symbol_info));
        (yyval.symbol_info)->add((yyvsp[-2].symbol_info));
        (yyval.symbol_info)->add((yyvsp[-1].symbol_info));
        (yyval.symbol_info)->add((yyvsp[0].symbol_info));
        (yyval.symbol_info)->start=(yyvsp[-6].symbol_info)->start;
        (yyval.symbol_info)->end=(yyvsp[-2].symbol_info)->end;
        (yyval.symbol_info)->leaf=0;
        backpatch((yyvsp[-3].symbol_info)->truelist,(yyvsp[-1].symbol_info)->label);
        backpatch((yyvsp[0].symbol_info)->nextlist,(yyvsp[-5].symbol_info)->label);
        (yyval.symbol_info)->nextlist=(yyvsp[-3].symbol_info)->falselist;
      }
#line 2295 "y.tab.c"
    break;

  case 38: /* statement: PRINTLN LPAREN ID RPAREN SEMICOLON  */
#line 888 "parser.y"
      {
        string rule="statement: PRINTLN LPAREN ID RPAREN SEMICOLON";
        
        fout<<rule<<" "<<endl;
        (yyval.symbol_info) = new SymbolInfo("statement","PRINTLN LPAREN ID RPAREN SEMICOLON");
        (yyval.symbol_info)->message=rule;
        (yyval.symbol_info)->add((yyvsp[-4].symbol_info));
        (yyval.symbol_info)->add((yyvsp[-3].symbol_info));
        (yyval.symbol_info)->add((yyvsp[-2].symbol_info));
        (yyval.symbol_info)->add((yyvsp[-1].symbol_info));
        (yyval.symbol_info)->add((yyvsp[0].symbol_info));
        (yyval.symbol_info)->start=(yyvsp[-4].symbol_info)->start;
        (yyval.symbol_info)->end=(yyvsp[0].symbol_info)->end;
        (yyval.symbol_info)->leaf=0;
        
        SymbolInfo *temp=table->LookUp((yyvsp[-2].symbol_info)->getName());
        if(temp->is_global==true){
            cout<<"global Variable name is "<<temp->getName()<<endl;
            temp->ad=(yyvsp[-2].symbol_info)->getName();
        }
        else{
            cout<<"local Variable name is "<<temp->getName()<<endl;
            temp->ad="[BP-"+to_string(temp->offset)+"]";
        }
        tout<<"MOV AX,"<<temp->ad<<endl;
        temp_line_count++;
        tout<<"CALL print_output\nCALL new_line"<<endl;
        temp_line_count+=2;

      }
#line 2330 "y.tab.c"
    break;

  case 39: /* statement: RETURN expression SEMICOLON  */
#line 919 "parser.y"
      {
        string rule="statement : RETURN expression SEMICOLON";
        
        fout<<rule<<" "<<endl;
        (yyval.symbol_info) = new SymbolInfo("statement","RETURN expression SEMICOLON");
        (yyval.symbol_info)->message=rule;
        (yyval.symbol_info)->add((yyvsp[-2].symbol_info));
        (yyval.symbol_info)->add((yyvsp[-1].symbol_info));
        (yyval.symbol_info)->add((yyvsp[0].symbol_info));
        (yyval.symbol_info)->start=(yyvsp[-2].symbol_info)->start;
        (yyval.symbol_info)->end=(yyvsp[0].symbol_info)->end;
        (yyval.symbol_info)->leaf=0;
      }
#line 2348 "y.tab.c"
    break;

  case 40: /* expression_statement: SEMICOLON  */
#line 935 "parser.y"
{
        string rule="expression_statement : SEMICOLON";
        
        fout<<rule<<" "<<endl;
        (yyval.symbol_info) = new SymbolInfo("expression_statement", "SEMICOLON");
        (yyval.symbol_info)->message=rule;
        (yyval.symbol_info)->add((yyvsp[0].symbol_info));
        (yyval.symbol_info)->start=(yyvsp[0].symbol_info)->start;
        (yyval.symbol_info)->end=(yyvsp[0].symbol_info)->end;
        (yyval.symbol_info)->leaf=0;
}
#line 2364 "y.tab.c"
    break;

  case 41: /* expression_statement: expression SEMICOLON  */
#line 947 "parser.y"
            {
        string rule="expression_statement : expression SEMICOLON";
        
        fout<<rule<<" "<<endl;
            (yyval.symbol_info) = new SymbolInfo("expression_statement", "expression SEMICOLON");
        (yyval.symbol_info)->message=rule;
        (yyval.symbol_info)->add((yyvsp[-1].symbol_info));    
        (yyval.symbol_info)->add((yyvsp[0].symbol_info));
        (yyval.symbol_info)->start=(yyvsp[-1].symbol_info)->start;
        (yyval.symbol_info)->end=(yyvsp[0].symbol_info)->end;
        (yyval.symbol_info)->leaf=0;
            }
#line 2381 "y.tab.c"
    break;

  case 42: /* variable: ID  */
#line 962 "parser.y"
{
        string rule="variable : ID";
        
        fout<<rule<<" "<<endl;
        (yyval.symbol_info) = new SymbolInfo("variable", "ID");
        (yyval.symbol_info)->message=rule;
        (yyval.symbol_info)->add((yyvsp[0].symbol_info));
        (yyval.symbol_info)->start=(yyvsp[0].symbol_info)->start;
        (yyval.symbol_info)->end=(yyvsp[0].symbol_info)->end;
        (yyval.symbol_info)->leaf=0;
        SymbolInfo *temp=table->LookUp((yyvsp[0].symbol_info)->getName());
        if(temp==NULL)
        {
            eout<<"Line# "<<line_count<<": Undeclared variable '"<<(yyvsp[0].symbol_info)->getName()<<"'"<<endl;
            error++;
        }
        else{
            (yyval.symbol_info)->setType(temp->getType());
        }
        if(temp->is_global==true){
            (yyval.symbol_info)->is_global=true;
            (yyval.symbol_info)->ad=(yyvsp[0].symbol_info)->getName();
        }
        else{
            (yyval.symbol_info)->is_global=false;
            cout<<table->current->scope_offset<<endl;
            //$$->ad=$1->getName();
            (yyval.symbol_info)->ad="[BP-"+to_string(temp->offset)+"]";
        }
        
}
#line 2417 "y.tab.c"
    break;

  case 43: /* variable: ID LSQUARE expression RSQUARE  */
#line 994 "parser.y"
     {
        string rule="variable : ID LSQUARE expression RSQUARE";
        
        fout<<rule<<" "<<endl;
        (yyval.symbol_info) = new SymbolInfo("variable", "ID LSQUARE expression RSQUARE");
        (yyval.symbol_info)->message=rule;
        (yyval.symbol_info)->add((yyvsp[-3].symbol_info));
        (yyval.symbol_info)->add((yyvsp[-2].symbol_info));
        (yyval.symbol_info)->add((yyvsp[-1].symbol_info));
        (yyval.symbol_info)->add((yyvsp[0].symbol_info));
        (yyval.symbol_info)->start=(yyvsp[-3].symbol_info)->start;
        (yyval.symbol_info)->end=(yyvsp[0].symbol_info)->end;
        (yyval.symbol_info)->leaf=0;
            SymbolInfo *temp=table->LookUp((yyvsp[-3].symbol_info)->getName());
            if(temp==NULL)
            {
                eout<<"Line# "<<line_count<<": Undeclared variable "<<(yyvsp[-3].symbol_info)->getName()<<endl;
                error++;
            }
            else{
                if(temp->optional!="ARRAY"){
                    eout<<"Line# "<<line_count<<": '"<<(yyvsp[-3].symbol_info)->getName()<<"'"<<" is not an array"<<endl;
                    error++;
                }
                else if((yyvsp[-1].symbol_info)->getType()!="INT")
                {
                    eout<<"Line# "<<line_count<<": Array subscript is not an integer"<<endl;
                    error++;
                }
        
                else (yyval.symbol_info)->setType(temp->getType());
            }
            
        }
#line 2456 "y.tab.c"
    break;

  case 44: /* expression: logic_expression  */
#line 1031 "parser.y"
 {
        string rule="expression : logic_expression";
        
        fout<<rule<<" "<<endl;
        (yyval.symbol_info) = new SymbolInfo((yyvsp[0].symbol_info)->getName(), "logic_expression");
        (yyval.symbol_info)->message=rule;
        (yyval.symbol_info)->add((yyvsp[0].symbol_info));
        (yyval.symbol_info)->start=(yyvsp[0].symbol_info)->start;
        (yyval.symbol_info)->end=(yyvsp[0].symbol_info)->end;
        (yyval.symbol_info)->leaf=0;
        (yyval.symbol_info)->setType((yyvsp[0].symbol_info)->getType());
        (yyval.symbol_info)->arith_check=(yyvsp[0].symbol_info)->arith_check;
        (yyval.symbol_info)->truelist=(yyvsp[0].symbol_info)->truelist;
        (yyval.symbol_info)->falselist=(yyvsp[0].symbol_info)->falselist;
        (yyval.symbol_info)->nextlist=(yyvsp[0].symbol_info)->nextlist;
 }
#line 2477 "y.tab.c"
    break;

  case 45: /* expression: variable ASSIGNOP logic_expression  */
#line 1048 "parser.y"
       {
        string rule="expression : variable ASSIGNOP logic_expression";
        
        fout<<rule<<" "<<endl;
        (yyval.symbol_info) = new SymbolInfo("expression", "variable ASSIGNOP logic_expression");
        (yyval.symbol_info)->message=rule;
        (yyval.symbol_info)->add((yyvsp[-2].symbol_info));
        (yyval.symbol_info)->add((yyvsp[-1].symbol_info));
        (yyval.symbol_info)->add((yyvsp[0].symbol_info));
        (yyval.symbol_info)->start=(yyvsp[-2].symbol_info)->start;
        (yyval.symbol_info)->end=(yyvsp[0].symbol_info)->end;
        (yyval.symbol_info)->leaf=0;
        if((yyvsp[-2].symbol_info)->getType()=="VOID" || (yyvsp[0].symbol_info)->getType()=="VOID"){
                eout<<"Line# "<<line_count<<": Void cannot be used in expression "<<endl;
                error++;
            }
        else if((yyvsp[-2].symbol_info)->getType()=="INT" && (yyvsp[0].symbol_info)->getType()=="FLOAT"){
                eout<<"Line# "<<line_count<<": Warning: possible loss of data in assignment of FLOAT to INT"<<endl;
                error++;
            }
        else (yyval.symbol_info)->setType((yyvsp[-2].symbol_info)->getType());
        if((yyvsp[0].symbol_info)->arith_check==0){
            string l1,l2,l3;
            l1="L"+to_string(label_count);
            label_count++;
            l2="L"+to_string(label_count);
            label_count++;
            l3="L"+to_string(label_count);
            label_count++;
            tout<<l1<<":"<<endl;
            temp_line_count++;
            tout<<"MOV AX,1"<<endl;
            temp_line_count++;
            tout<<"JMP "<<l3<<endl;
            temp_line_count++;
            tout<<l2<<":"<<endl;
            temp_line_count++;
            tout<<"MOV AX,0"<<endl;
            temp_line_count++;
            tout<<l3<<":"<<endl;
            temp_line_count++;
            tout<<"PUSH AX"<<endl;
            temp_line_count++;
            backpatch((yyvsp[0].symbol_info)->truelist,l1);
            backpatch((yyvsp[0].symbol_info)->falselist,l2);
        }
        tout<<"POP AX"<<endl;
        temp_line_count++;
        tout<<"MOV "<<(yyvsp[-2].symbol_info)->ad<<",AX"<<endl;
        temp_line_count++;
        tout<<"PUSH AX"<<endl;
        temp_line_count++;
        }
#line 2535 "y.tab.c"
    break;

  case 46: /* logic_expression: rel_expression  */
#line 1104 "parser.y"
{
        string rule="logic_expression : rel_expression";
        
        fout<<rule<<" "<<endl;
        (yyval.symbol_info) = new SymbolInfo((yyvsp[0].symbol_info)->getName(), "rel_expression");
        (yyval.symbol_info)->message=rule;
        (yyval.symbol_info)->add((yyvsp[0].symbol_info));
        (yyval.symbol_info)->start=(yyvsp[0].symbol_info)->start;
        (yyval.symbol_info)->end=(yyvsp[0].symbol_info)->end;
        (yyval.symbol_info)->leaf=0;
        (yyval.symbol_info)->setType((yyvsp[0].symbol_info)->getType());
        (yyval.symbol_info)->truelist=(yyvsp[0].symbol_info)->truelist;
        (yyval.symbol_info)->falselist=(yyvsp[0].symbol_info)->falselist;
        (yyval.symbol_info)->arith_check=(yyvsp[0].symbol_info)->arith_check;
        (yyval.symbol_info)->nextlist=(yyvsp[0].symbol_info)->nextlist;
}
#line 2556 "y.tab.c"
    break;

  case 47: /* $@4: %empty  */
#line 1120 "parser.y"
                                  {is_arith((yyvsp[0].symbol_info));}
#line 2562 "y.tab.c"
    break;

  case 48: /* logic_expression: rel_expression $@4 LOGICOP M rel_expression  */
#line 1121 "parser.y"
         {
        string rule="logic_expression : rel_expression LOGICOP rel_expression";
        fout<<rule<<" "<<endl;
        (yyval.symbol_info) = new SymbolInfo("logic_expression", "rel_expression LOGICOP rel_expression");
        (yyval.symbol_info)->message=rule;
        (yyval.symbol_info)->add((yyvsp[-4].symbol_info));
        //$$->add($2);
        (yyval.symbol_info)->add((yyvsp[-2].symbol_info));
        (yyval.symbol_info)->add((yyvsp[-1].symbol_info));
        (yyval.symbol_info)->add((yyvsp[0].symbol_info));
        (yyval.symbol_info)->start=(yyvsp[-4].symbol_info)->start;
        (yyval.symbol_info)->end=(yyvsp[0].symbol_info)->end;
        (yyval.symbol_info)->leaf=0;
        if((yyvsp[-4].symbol_info)->getType()=="VOID"){
                eout<<"Line# "<<line_count<<": Void cannot be used in expression "<<endl;
                error++;
            }
        else (yyval.symbol_info)->setType("INT");
        if((yyvsp[0].symbol_info)->arith_check==1){
        tout<<"POP AX"<<endl;
        temp_line_count++;
        tout<<"CMP AX,0";
        temp_line_count++;
        tout<<"JNE "<<endl;
        cout<<"JNE er por print "<<endl;
        (yyvsp[0].symbol_info)->truelist.push_back(temp_line_count);
        temp_line_count++;
        tout<<"JMP "<<endl;
        cout<<"JMP er por print "<<endl;
        (yyvsp[0].symbol_info)->falselist.push_back(temp_line_count);
        temp_line_count++;
        cout<<"truelist falselist push kora shesh ekhn print"<<endl;
        for(int i=0;i<(yyvsp[0].symbol_info)->truelist.size();i++){
            cout<<(yyvsp[0].symbol_info)->truelist[i]<<" truelist e print kortesi"<<endl;
        }
        for(int i=0;i<(yyvsp[0].symbol_info)->falselist.size();i++){
            cout<<(yyvsp[0].symbol_info)->falselist[i]<<" falselist e print kortesi"<<endl;
        }
        
    }
        if((yyvsp[-2].symbol_info)->getName()=="||"){
            
            backpatch((yyvsp[-4].symbol_info)->falselist,(yyvsp[-1].symbol_info)->label);
            (yyval.symbol_info)->truelist=merge((yyvsp[-4].symbol_info)->truelist,(yyvsp[0].symbol_info)->truelist);
            (yyval.symbol_info)->falselist=(yyvsp[0].symbol_info)->falselist;
            cout<<"or rule e print kortesi,label"<<(yyvsp[-1].symbol_info)->label<<endl;
        
        }
        else if((yyvsp[-2].symbol_info)->getName()=="&&"){
            backpatch((yyvsp[-4].symbol_info)->truelist,(yyvsp[-1].symbol_info)->label);
            (yyval.symbol_info)->truelist=(yyvsp[0].symbol_info)->truelist;
            (yyval.symbol_info)->falselist=merge((yyvsp[-4].symbol_info)->falselist,(yyvsp[0].symbol_info)->falselist);
            cout<<"and rule e print kortesi"<<(yyvsp[-1].symbol_info)->label<<endl;
    
        }
    for(int i=0;i<(yyval.symbol_info)->truelist.size();i++){
        cout<<(yyval.symbol_info)->truelist[i]<<" Logicop rule e print kortesi"<<endl;
    }
    for(int i=0;i<(yyvsp[0].symbol_info)->truelist.size();i++){
            cout<<(yyvsp[0].symbol_info)->truelist[i]<<"\ truelist e print kortesi"<<endl;
        }
        for(int i=0;i<(yyvsp[0].symbol_info)->falselist.size();i++){
            cout<<(yyvsp[0].symbol_info)->falselist[i]<<"\ falselist e print kortesi"<<endl;
        }
        for(int i=0;i<(yyvsp[-4].symbol_info)->truelist.size();i++){
            cout<<(yyvsp[0].symbol_info)->truelist[i]<<"\ truelist e print kortesi"<<endl;
        }
        for(int i=0;i<(yyvsp[-4].symbol_info)->falselist.size();i++){
            cout<<(yyvsp[0].symbol_info)->falselist[i]<<"\ falselist e print kortesi"<<endl;
        }
         }
#line 2638 "y.tab.c"
    break;

  case 49: /* rel_expression: simple_expression  */
#line 1197 "parser.y"
{
        string rule="rel_expression : simple_expression";
        
        fout<<rule<<" "<<endl;
        (yyval.symbol_info) = new SymbolInfo((yyvsp[0].symbol_info)->getName(), "simple_expression");
        (yyval.symbol_info)->message=rule;
        (yyval.symbol_info)->add((yyvsp[0].symbol_info));
        (yyval.symbol_info)->start=(yyvsp[0].symbol_info)->start;
        (yyval.symbol_info)->end=(yyvsp[0].symbol_info)->end;
        (yyval.symbol_info)->leaf=0;
        (yyval.symbol_info)->setType((yyvsp[0].symbol_info)->getType());
        (yyval.symbol_info)->arith_check=(yyvsp[0].symbol_info)->arith_check;
        (yyval.symbol_info)->nextlist=(yyvsp[0].symbol_info)->nextlist;
        (yyval.symbol_info)->truelist=(yyvsp[0].symbol_info)->truelist;
        (yyval.symbol_info)->falselist=(yyvsp[0].symbol_info)->falselist;
}
#line 2659 "y.tab.c"
    break;

  case 50: /* rel_expression: simple_expression RELOP simple_expression  */
#line 1214 "parser.y"
        {
        string rule="rel_expression	: simple_expression RELOP simple_expression";
        
        fout<<rule<<" "<<endl;
        (yyval.symbol_info) = new SymbolInfo("rel_expression", "simple_expression RELOP simple_expression");
        (yyval.symbol_info)->message=rule;
        (yyval.symbol_info)->add((yyvsp[-2].symbol_info));
        (yyval.symbol_info)->add((yyvsp[-1].symbol_info));
        (yyval.symbol_info)->add((yyvsp[0].symbol_info));
        (yyval.symbol_info)->start=(yyvsp[-2].symbol_info)->start;
        (yyval.symbol_info)->end=(yyvsp[0].symbol_info)->end;
        (yyval.symbol_info)->leaf=0;
        if((yyvsp[-2].symbol_info)->getType()=="VOID"){
                eout<<"Line# "<<line_count<<": Void cannot be used in expression "<<endl;
                error++;
            }
        else (yyval.symbol_info)->setType("INT");
        tout<<"POP BX"<<endl;
        temp_line_count++;
        tout<<"POP AX"<<endl;
        temp_line_count++;
        tout<<"CMP AX,BX"<<endl;
        temp_line_count++;
        if((yyvsp[-1].symbol_info)->getName()==">"){
            tout<<"JG "<<endl;
            (yyval.symbol_info)->truelist.push_back(temp_line_count);
            temp_line_count++;
        }
        else if((yyvsp[-1].symbol_info)->getName()=="<"){
            tout<<"JL "<<endl;
            (yyval.symbol_info)->truelist.push_back(temp_line_count);
            temp_line_count++;
        }
        else if((yyvsp[-1].symbol_info)->getName()=="=="){
            tout<<"JE "<<endl;
            (yyval.symbol_info)->truelist.push_back(temp_line_count);
            temp_line_count++;
        }
        else if((yyvsp[-1].symbol_info)->getName()=="!="){
            tout<<"JNE "<<endl;
            (yyval.symbol_info)->truelist.push_back(temp_line_count);
            temp_line_count++;
        }
        else if((yyvsp[-1].symbol_info)->getName()==">="){
            tout<<"JGE "<<endl;
            (yyval.symbol_info)->truelist.push_back(temp_line_count);
            temp_line_count++;
        }
        else if((yyvsp[-1].symbol_info)->getName()=="<="){
            tout<<"JLE "<<endl;
            (yyval.symbol_info)->truelist.push_back(temp_line_count);
            temp_line_count++;
        }
        tout<<"JMP "<<endl;
        (yyval.symbol_info)->falselist.push_back(temp_line_count);
        temp_line_count++;	
        for(int i=0;i<(yyval.symbol_info)->truelist.size();i++){
        cout<<(yyval.symbol_info)->truelist[i]<<" Relop rule e print kortesi"<<endl;
        }
        }
#line 2724 "y.tab.c"
    break;

  case 51: /* simple_expression: term  */
#line 1276 "parser.y"
{
        string rule="simple_expression : term";
        
        fout<<rule<<" "<<endl;
        (yyval.symbol_info) = new SymbolInfo((yyvsp[0].symbol_info)->getName(), "term");
        (yyval.symbol_info)->message=rule;
        (yyval.symbol_info)->add((yyvsp[0].symbol_info));
        (yyval.symbol_info)->start=(yyvsp[0].symbol_info)->start;
        (yyval.symbol_info)->end=(yyvsp[0].symbol_info)->end;
        (yyval.symbol_info)->leaf=0;
        (yyval.symbol_info)->setType((yyvsp[0].symbol_info)->getType());
        (yyval.symbol_info)->arith_check=(yyvsp[0].symbol_info)->arith_check;
        (yyval.symbol_info)->truelist=(yyvsp[0].symbol_info)->truelist;
        (yyval.symbol_info)->falselist=(yyvsp[0].symbol_info)->falselist;
}
#line 2744 "y.tab.c"
    break;

  case 52: /* simple_expression: simple_expression ADDOP term  */
#line 1292 "parser.y"
          {
        string rule="simple_expression : simple_expression ADDOP term";
        
        fout<<rule<<" "<<endl;
        (yyval.symbol_info) = new SymbolInfo("simple_expression", "simple_expression ADDOP term");
        (yyval.symbol_info)->message=rule;
        (yyval.symbol_info)->add((yyvsp[-2].symbol_info));
        (yyval.symbol_info)->add((yyvsp[-1].symbol_info));
        (yyval.symbol_info)->add((yyvsp[0].symbol_info));
        (yyval.symbol_info)->start=(yyvsp[-2].symbol_info)->start;
        (yyval.symbol_info)->end=(yyvsp[0].symbol_info)->end;
        (yyval.symbol_info)->leaf=0;
        if((yyvsp[-2].symbol_info)->getType()=="VOID" ||(yyvsp[0].symbol_info)->getType()=="VOID"){
                if((yyvsp[-2].symbol_info)->getType()=="VOID")
                eout<<"Line# "<<line_count<<": Void cannot be used in expression "<<endl;
                else
                eout<<"Line# "<<line_count<<": Void cannot be used in expression "<<endl;
                error++;
            }
        else if((yyvsp[-2].symbol_info)->getType()=="FLOAT" ||(yyvsp[0].symbol_info)->getType()=="FLOAT"){
                (yyval.symbol_info)->setType("FLOAT");
            }
        else{
                (yyval.symbol_info)->setType("INT");
            }
            (yyval.symbol_info)->arith_check=1;
            tout<<"POP BX"<<endl;
            temp_line_count++;
            tout<<"POP AX"<<endl;
            temp_line_count++;
            if((yyvsp[-1].symbol_info)->getName()=="+"){
                tout<<"ADD AX,BX"<<endl;
                temp_line_count++;
            }
            else{
                tout<<"SUB AX,BX"<<endl;
                temp_line_count++;
            }
            tout<<"PUSH AX"<<endl;
            temp_line_count++;
          }
#line 2790 "y.tab.c"
    break;

  case 53: /* term: unary_expression  */
#line 1336 "parser.y"
{
        string rule="term : unary_expression";
        
        fout<<rule<<" "<<endl;
        (yyval.symbol_info) = new SymbolInfo((yyvsp[0].symbol_info)->getName(), "unary_expression");
        (yyval.symbol_info)->message=rule;
        (yyval.symbol_info)->add((yyvsp[0].symbol_info));
        (yyval.symbol_info)->start=(yyvsp[0].symbol_info)->start;
        (yyval.symbol_info)->end=(yyvsp[0].symbol_info)->end;
        (yyval.symbol_info)->leaf=0;
        (yyval.symbol_info)->setType((yyvsp[0].symbol_info)->getType());
        (yyval.symbol_info)->arith_check=(yyvsp[0].symbol_info)->arith_check;
        (yyval.symbol_info)->truelist=(yyvsp[0].symbol_info)->truelist;
        (yyval.symbol_info)->falselist=(yyvsp[0].symbol_info)->falselist;
    
}
#line 2811 "y.tab.c"
    break;

  case 54: /* term: term MULOP unary_expression  */
#line 1353 "parser.y"
     {
        string rule="term : term MULOP unary_expression";
        
        fout<<rule<<" "<<endl;
        (yyval.symbol_info) = new SymbolInfo("term", "term MULOP unary_expression");
        (yyval.symbol_info)->message=rule;
        (yyval.symbol_info)->add((yyvsp[-2].symbol_info));
        (yyval.symbol_info)->add((yyvsp[-1].symbol_info));
        (yyval.symbol_info)->add((yyvsp[0].symbol_info));
        (yyval.symbol_info)->start=(yyvsp[-2].symbol_info)->start;
        (yyval.symbol_info)->end=(yyvsp[0].symbol_info)->end;
        (yyval.symbol_info)->leaf=0;
        
        //    $2->getName()<<"  Line number"<<line_count<<"    "<<$1->getName()<<endl;
        
            if((yyvsp[-2].symbol_info)->getType()=="VOID" ||(yyvsp[0].symbol_info)->getType()=="VOID"){
                if((yyvsp[-2].symbol_info)->getType()=="VOID")
                eout<<"Line# "<<line_count<<": Void cannot be used in expression "<<endl;
                else 
                eout<<"Line# "<<line_count<<": Void cannot be used in expression "<<endl;
                error++;
            }
            else if((yyvsp[-1].symbol_info)->getName()== "%" && ((yyvsp[-2].symbol_info)->getType()=="FLOAT"||(yyvsp[0].symbol_info)->getType()=="FLOAT")){
                eout<<"Line# "<<line_count<<": Operands of modulus must be integers "<<endl;
                error++;
            }
            else if(((yyvsp[-1].symbol_info)->getName()== "/" || (yyvsp[-1].symbol_info)->getName()== "%") && (yyvsp[0].symbol_info)->getName()=="0"){
                eout<<"Line# "<<line_count<<": Warning: division by zero i=0f=1Const=0"<<endl;
                error++;
            }
            else if((yyvsp[-2].symbol_info)->getType()=="FLOAT" ||(yyvsp[0].symbol_info)->getType()=="FLOAT"){
                (yyval.symbol_info)->setType("FLOAT");
            }
            else{
                (yyval.symbol_info)->setType("INT");
            }
            (yyval.symbol_info)->arith_check=1;
            tout<<"POP BX"<<endl;
            temp_line_count++;
            tout<<"POP AX"<<endl;
            temp_line_count++;
            if((yyvsp[-1].symbol_info)->getName()=="/"){
                tout<<"CWD"<<endl;
                temp_line_count++;
                tout<<"DIV BX"<<endl;
                temp_line_count++;
            }
            else if((yyvsp[-1].symbol_info)->getName()=="*"){
                tout<<"MUL BX"<<endl;
                temp_line_count++;
            }
            else if((yyvsp[-1].symbol_info)->getName()=="%"){
                tout<<"CWD"<<endl;
                temp_line_count++;
                tout<<"DIV BX"<<endl;
                temp_line_count++;
                tout<<"MOV AX,DX"<<endl;
                temp_line_count++;
            }
            tout<<"PUSH AX"<<endl;
            temp_line_count++;
        
     }
#line 2879 "y.tab.c"
    break;

  case 55: /* unary_expression: ADDOP unary_expression  */
#line 1419 "parser.y"
{
        string rule="unary_expression : ADDOP unary_expression";
        
        fout<<rule<<" "<<endl;
        (yyval.symbol_info) = new SymbolInfo("unary_expression", "ADDOP unary_expression");
        (yyval.symbol_info)->message=rule;
        (yyval.symbol_info)->add((yyvsp[-1].symbol_info));
        (yyval.symbol_info)->add((yyvsp[0].symbol_info));
        (yyval.symbol_info)->start=(yyvsp[-1].symbol_info)->start;
        (yyval.symbol_info)->end=(yyvsp[0].symbol_info)->end;
        (yyval.symbol_info)->leaf=0;
        if((yyvsp[0].symbol_info)->getType()=="VOID"){
            eout<<"Line# "<<line_count<<": VOID cannot be used in expression "<<endl;
            error++;
        }
        else
        (yyval.symbol_info)->setType((yyvsp[0].symbol_info)->getType());
        (yyval.symbol_info)->arith_check=1;
        if((yyvsp[-1].symbol_info)->getName()=="-"){
            tout<<"POP AX"<<endl;
            temp_line_count++;
            tout<<"NEG AX"<<endl;
            temp_line_count++;
            tout<<"PUSH AX"<<endl;
            temp_line_count++;
        }

}
#line 2912 "y.tab.c"
    break;

  case 56: /* unary_expression: NOT unary_expression  */
#line 1448 "parser.y"
         {
        string rule="unary_expression : NOT unary_expression";
        
        fout<<rule<<" "<<endl;
        (yyval.symbol_info) = new SymbolInfo("unary_expression", "NOT unary_expression");
        (yyval.symbol_info)->message=rule;
        (yyval.symbol_info)->add((yyvsp[-1].symbol_info));
        (yyval.symbol_info)->add((yyvsp[0].symbol_info));
        (yyval.symbol_info)->start=(yyvsp[-1].symbol_info)->start;
        (yyval.symbol_info)->end=(yyvsp[0].symbol_info)->end;
        (yyval.symbol_info)->leaf=0;
        (yyval.symbol_info)->setType("INT");
        if((yyvsp[0].symbol_info)->getType()=="VOID"){
            eout<<"Line# "<<line_count<<": VOID cannot be used in expression "<<endl;
            error++;
        }

        // tout<<"POP AX"<<endl;
        // temp_line_count++;
        // tout<<"NOT AX"<<endl;
        // temp_line_count++;
        // tout<<"PUSH AX"<<endl;
        // temp_line_count++;
        (yyval.symbol_info)->truelist=(yyvsp[0].symbol_info)->falselist;
        (yyval.symbol_info)->falselist=(yyvsp[0].symbol_info)->truelist;

         }
#line 2944 "y.tab.c"
    break;

  case 57: /* unary_expression: factor  */
#line 1476 "parser.y"
         {
        string rule="unary_expression : factor";
        
        fout<<rule<<" "<<endl;
        (yyval.symbol_info) = new SymbolInfo((yyvsp[0].symbol_info)->getName(), "factor");
        (yyval.symbol_info)->message=rule;
        (yyval.symbol_info)->add((yyvsp[0].symbol_info));
        (yyval.symbol_info)->start=(yyvsp[0].symbol_info)->start;
        (yyval.symbol_info)->end=(yyvsp[0].symbol_info)->end;
        (yyval.symbol_info)->leaf=0;
        (yyval.symbol_info)->setType((yyvsp[0].symbol_info)->getType());
        (yyval.symbol_info)->arith_check=(yyvsp[0].symbol_info)->arith_check;
        (yyval.symbol_info)->truelist=(yyvsp[0].symbol_info)->truelist;
        (yyval.symbol_info)->falselist=(yyvsp[0].symbol_info)->falselist;
         }
#line 2964 "y.tab.c"
    break;

  case 58: /* factor: variable  */
#line 1494 "parser.y"
{
        string rule="factor : variable";
        
        fout<<rule<<" "<<endl;
        (yyval.symbol_info) = new SymbolInfo((yyvsp[0].symbol_info)->getName(), "variable");
        (yyval.symbol_info)->message=rule;
        (yyval.symbol_info)->add((yyvsp[0].symbol_info));
        (yyval.symbol_info)->start=(yyvsp[0].symbol_info)->start;
        (yyval.symbol_info)->end=(yyvsp[0].symbol_info)->end;
        (yyval.symbol_info)->leaf=0;
        (yyval.symbol_info)->setType((yyvsp[0].symbol_info)->getType());
        (yyval.symbol_info)->arith_check=1;
        tout<<"MOV AX,"<<(yyvsp[0].symbol_info)->ad<<endl;
        temp_line_count++;
        tout<<"PUSH AX"<<endl;
        temp_line_count++;
        //$$->arith_check=$1->arith_check;
}
#line 2987 "y.tab.c"
    break;

  case 59: /* factor: ID LPAREN argument_list RPAREN  */
#line 1513 "parser.y"
    {
        string rule="factor : ID LPAREN argument_list RPAREN";
        
        fout<<rule<<" "<<endl;
        (yyval.symbol_info) = new SymbolInfo((yyvsp[-3].symbol_info)->getName(), "ID LPAREN argument_list RPAREN");
        (yyval.symbol_info)->message=rule;
        (yyval.symbol_info)->add((yyvsp[-3].symbol_info));
        (yyval.symbol_info)->add((yyvsp[-2].symbol_info));
        (yyval.symbol_info)->add((yyvsp[-1].symbol_info));
        (yyval.symbol_info)->add((yyvsp[0].symbol_info));
        (yyval.symbol_info)->start=(yyvsp[-3].symbol_info)->start;
        (yyval.symbol_info)->end=(yyvsp[0].symbol_info)->end;
        (yyval.symbol_info)->leaf=0;
        (yyval.symbol_info)->arith_check=1;
        SymbolInfo *temp = table->LookUp((yyvsp[-3].symbol_info)->getName());
        if(temp==NULL){
            eout<<"Line# "<<line_count<<": Undeclared function '"<<(yyvsp[-3].symbol_info)->getName()<<"'"<<endl;
            error++;
        }
        else if(temp->optional!="FUNCTION"){
            eout<<"Line# "<<line_count<<": '"<<(yyvsp[-3].symbol_info)->getName()<<"' is not a function"<<endl;
            error++;
        }
        else{
            (yyval.symbol_info)->setType(temp->getType());
            if(temp->func_dec_list.size()<(yyvsp[-1].symbol_info)->var_dec_list.size()){
                eout<<"Line# "<<line_count<<": Too many arguments to function '"<<(yyvsp[-3].symbol_info)->getName()<<"'"<<endl;
                //    temp->func_dec_list.size()<<" "<<$3->var_dec_list.size()<<endl;
                error++;
            }
            else if(temp->func_dec_list.size()>(yyvsp[-1].symbol_info)->var_dec_list.size()){
                eout<<"Line# "<<line_count<<": Too few arguments to function '"<<(yyvsp[-3].symbol_info)->getName()<<"'"<<endl;
                error++;
            }
            else{
                for(int i=0;i<temp->func_dec_list.size();i++){
                    if(temp->func_dec_list[i]->getType()!=(yyvsp[-1].symbol_info)->var_dec_list[i]->getType()){
                        eout<<"Line# "<<line_count<<": Type mismatch for argument "<<i+1<<" of '"<<(yyvsp[-3].symbol_info)->getName()<<"'"<<endl;
                        error++;
                    }
                }
            }
        }
    }
#line 3036 "y.tab.c"
    break;

  case 60: /* factor: LPAREN expression RPAREN  */
#line 1558 "parser.y"
    {
        string rule="factor	: LPAREN expression RPAREN";
        
        fout<<rule<<" "<<endl;
        (yyval.symbol_info) = new SymbolInfo((yyvsp[-2].symbol_info)->getName(), "LPAREN expression RPAREN");
        (yyval.symbol_info)->message=rule;
        (yyval.symbol_info)->add((yyvsp[-2].symbol_info));
        (yyval.symbol_info)->add((yyvsp[-1].symbol_info));
        (yyval.symbol_info)->add((yyvsp[0].symbol_info));
        (yyval.symbol_info)->start=(yyvsp[-2].symbol_info)->start;
        (yyval.symbol_info)->end=(yyvsp[0].symbol_info)->end;
        (yyval.symbol_info)->leaf=0;
        if((yyvsp[-1].symbol_info)->getName()=="0")
            (yyval.symbol_info)->setName("0");
        (yyval.symbol_info)->setType((yyvsp[-1].symbol_info)->getType());
        (yyval.symbol_info)->arith_check=(yyvsp[-1].symbol_info)->arith_check;
        (yyval.symbol_info)->truelist=(yyvsp[-1].symbol_info)->truelist;
        (yyval.symbol_info)->falselist=(yyvsp[-1].symbol_info)->falselist;
    }
#line 3060 "y.tab.c"
    break;

  case 61: /* factor: CONST_INT  */
#line 1578 "parser.y"
    {
        string rule="factor : CONST_INT";
        
        fout<<rule<<" "<<endl;
        (yyval.symbol_info) = new SymbolInfo((yyvsp[0].symbol_info)->getName(), "INT");
        (yyval.symbol_info)->message=rule;
        (yyval.symbol_info)->add((yyvsp[0].symbol_info));
        (yyval.symbol_info)->start=(yyvsp[0].symbol_info)->start;
        (yyval.symbol_info)->end=(yyvsp[0].symbol_info)->end;
        (yyval.symbol_info)->leaf=0;
        if((yyvsp[0].symbol_info)->getName()=="0")
            (yyval.symbol_info)->setName("0");
        //    $$->getName()<<"  $$"<<endl;
        //    $1->getName()<<"  $1"<<endl; 
        (yyval.symbol_info)->arith_check=1;
        tout<<"MOV AX,"<<(yyvsp[0].symbol_info)->getName()<<endl;
        temp_line_count++;
        tout<<"PUSH AX"<<endl;
        temp_line_count++;
    }
#line 3085 "y.tab.c"
    break;

  case 62: /* factor: CONST_FLOAT  */
#line 1599 "parser.y"
    {
        string rule="factor : CONST_FLOAT";
        
        fout<<rule<<" "<<endl;
        (yyval.symbol_info) = new SymbolInfo((yyvsp[0].symbol_info)->getName(), "FLOAT");
        (yyval.symbol_info)->message=rule;
        (yyval.symbol_info)->add((yyvsp[0].symbol_info));
        (yyval.symbol_info)->start=(yyvsp[0].symbol_info)->start;
        (yyval.symbol_info)->end=(yyvsp[0].symbol_info)->end;
        (yyval.symbol_info)->leaf=0;
        if((yyvsp[0].symbol_info)->getName()=="0")
            (yyval.symbol_info)->setName("0");
    }
#line 3103 "y.tab.c"
    break;

  case 63: /* factor: variable INCOP  */
#line 1613 "parser.y"
    {
        string rule="factor : variable INCOP";
        
        fout<<rule<<" "<<endl;
        (yyval.symbol_info) = new SymbolInfo((yyvsp[-1].symbol_info)->getName(), "variable INCOP");
        (yyval.symbol_info)->message=rule;
        (yyval.symbol_info)->add((yyvsp[-1].symbol_info));
        (yyval.symbol_info)->add((yyvsp[0].symbol_info));
        (yyval.symbol_info)->start=(yyvsp[-1].symbol_info)->start;
        (yyval.symbol_info)->end=(yyvsp[0].symbol_info)->end;
        (yyval.symbol_info)->leaf=0;
        (yyval.symbol_info)->setType((yyvsp[-1].symbol_info)->getType());
        (yyval.symbol_info)->arith_check=1;
        //tout<<"POP AX"<<endl;
        tout<<"MOV AX,"<<(yyvsp[-1].symbol_info)->ad<<endl;
        temp_line_count++;
        tout<<"PUSH AX"<<endl;
        temp_line_count++;
        tout<<"INC AX"<<endl;
        temp_line_count++;
        tout<<"MOV "<<(yyvsp[-1].symbol_info)->ad<<",AX"<<endl;
        temp_line_count++;
    }
#line 3131 "y.tab.c"
    break;

  case 64: /* factor: variable DECOP  */
#line 1637 "parser.y"
    {
        string rule="factor	: variable DECOP";
        
        fout<<rule<<" "<<endl;
        (yyval.symbol_info) = new SymbolInfo((yyvsp[-1].symbol_info)->getName(), "variable DECOP");
        (yyval.symbol_info)->message=rule;
        (yyval.symbol_info)->add((yyvsp[-1].symbol_info));
        (yyval.symbol_info)->add((yyvsp[0].symbol_info));
        (yyval.symbol_info)->start=(yyvsp[-1].symbol_info)->start;
        (yyval.symbol_info)->end=(yyvsp[0].symbol_info)->end;
        (yyval.symbol_info)->leaf=0;
        (yyval.symbol_info)->setType((yyvsp[-1].symbol_info)->getType());
        (yyval.symbol_info)->arith_check=1;
        //tout<<"POP AX"<<endl;
        tout<<"MOV AX,"<<(yyvsp[-1].symbol_info)->ad<<endl;
        temp_line_count++;
        tout<<"PUSH AX"<<endl;
        temp_line_count++;
        tout<<"DEC AX"<<endl;
        temp_line_count++;
        tout<<"MOV "<<(yyvsp[-1].symbol_info)->ad<<",AX"<<endl;
        temp_line_count++;
        //tout<<"PUSH AX"<<endl;
    }
#line 3160 "y.tab.c"
    break;

  case 65: /* argument_list: arguments  */
#line 1664 "parser.y"
{
        string rule="argument_list : arguments";
        
        fout<<rule<<" "<<endl;
        (yyval.symbol_info) = new SymbolInfo("argument_list", "arguments");
        (yyval.symbol_info)->message=rule;
        (yyval.symbol_info)->add((yyvsp[0].symbol_info));
        (yyval.symbol_info)->start=(yyvsp[0].symbol_info)->start;
        (yyval.symbol_info)->end=(yyvsp[0].symbol_info)->end;
        (yyval.symbol_info)->leaf=0;
        for(int i=0;i<(yyvsp[0].symbol_info)->var_dec_list.size();i++){
            (yyval.symbol_info)->var_dec_list.push_back((yyvsp[0].symbol_info)->var_dec_list[i]);
        }
}
#line 3179 "y.tab.c"
    break;

  case 66: /* argument_list: %empty  */
#line 1679 "parser.y"
              {
                string rule="argument_list : ";
                (yyval.symbol_info) = new SymbolInfo();
                (yyval.symbol_info)->var_dec_list.clear();
              }
#line 3189 "y.tab.c"
    break;

  case 67: /* arguments: arguments COMMA logic_expression  */
#line 1687 "parser.y"
{
        string rule="arguments : arguments COMMA logic_expression";
        
        fout<<rule<<" "<<endl;
        (yyval.symbol_info) = new SymbolInfo("arguments", "arguments COMMA logic_expression");
        (yyval.symbol_info)->message=rule;
        (yyval.symbol_info)->add((yyvsp[-2].symbol_info));
        (yyval.symbol_info)->add((yyvsp[-1].symbol_info));
        (yyval.symbol_info)->add((yyvsp[0].symbol_info));
        (yyval.symbol_info)->start=(yyvsp[-2].symbol_info)->start;
        (yyval.symbol_info)->end=(yyvsp[0].symbol_info)->end;
        (yyval.symbol_info)->leaf=0;
        for(int i=0;i<(yyvsp[-2].symbol_info)->var_dec_list.size();i++){
            (yyval.symbol_info)->var_dec_list.push_back((yyvsp[-2].symbol_info)->var_dec_list[i]);
        }
        (yyval.symbol_info)->var_dec_list.push_back((yyvsp[0].symbol_info));
}
#line 3211 "y.tab.c"
    break;

  case 68: /* arguments: logic_expression  */
#line 1705 "parser.y"
          {
            string rule="arguments : logic_expression";
            
        fout<<rule<<" "<<endl;
            (yyval.symbol_info) = new SymbolInfo("arguments", "logic_expression");
            (yyval.symbol_info)->message=rule;
        (yyval.symbol_info)->add((yyvsp[0].symbol_info));
            (yyval.symbol_info)->start=(yyvsp[0].symbol_info)->start;
            (yyval.symbol_info)->end=(yyvsp[0].symbol_info)->end;
            (yyval.symbol_info)->leaf=0;
            (yyval.symbol_info)->var_dec_list.push_back((yyvsp[0].symbol_info));
          }
#line 3228 "y.tab.c"
    break;

  case 69: /* M: %empty  */
#line 1719 "parser.y"
{
    (yyval.symbol_info) = new SymbolInfo("M", "");
    string temp=to_string(label_count);
    (yyval.symbol_info)->label=temp;
    tout<<"L"<<temp<<":"<<endl;
    temp_line_count++;
    label_count++;
}
#line 3241 "y.tab.c"
    break;

  case 70: /* N: %empty  */
#line 1728 "parser.y"
{
    (yyval.symbol_info) = new SymbolInfo("N", "");
    (yyval.symbol_info)->nextlist.push_back(temp_line_count);
}
#line 3250 "y.tab.c"
    break;


#line 3254 "y.tab.c"

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

#line 1733 "parser.y"

int main(int argc,char *argv[])
{
    
	globals a;
    fout.open("output.txt",ios::out | ios::trunc );
    eout.open("error_output.txt",ios::out | ios::trunc );
    pout.open("parser_output.txt",ios::out | ios::trunc );
    tout.open("temp.txt",ios::out | ios::trunc );
    finalout.open("final_output.txt",ios::out | ios::trunc );
    ifstream label_in{"temp.txt"};
    string line;
    //label_in("label.txt");
    finalout<<".MODEL SMALL\n.STACK 1000H\n.Data\n\tCR EQU 0DH\n\tLF EQU 0AH\n\tnumber DB \"00000$\"\n .CODE"<<endl;
    table=new SymbolTable(11);
    if((fp=fopen(argv[1],"r"))==NULL)
	{
		printf("Cannot Open Input File.\n");
		exit(1);
	}
	yyin=fp;
	yyparse();
    int label_line_count=0;
    while(getline(label_in,line)){
        label_line_count++;
        if(umap.find(label_line_count)!=umap.end()){
            line=line+umap[label_line_count];

        }
        cout<<"Line count"<<label_line_count<<" "<<umap[label_line_count]<<endl;
        finalout<<line<<endl;
    }
    finalout<<"new_line proc\n\tpush ax\n\tpush dx\n\tmov ah,2\n\tmov dl,cr\n\tint 21h\n\tmov ah,2\n\tmov dl,lf\n\tint 21h"<<endl;
    finalout<<"\tpop dx\n\tpop ax\n\tret"<<endl;
    finalout<<"new_line endp"<<endl;
    finalout<<"print_output proc  ;print what is in ax"<<endl;
    finalout<<"\tpush ax"<<endl;
    finalout<<"\tpush bx"<<endl;
    finalout<<"\tpush cx"<<endl;
    finalout<<"\tpush dx"<<endl;
    finalout<<"\tpush si"<<endl;
    finalout<<"\tlea si,number"<<endl;
    finalout<<"\tmov bx,10"<<endl;
    finalout<<"\tadd si,4"<<endl;
    finalout<<"\tcmp ax,0"<<endl; 
    finalout<<"\tjnge negate"<<endl;
    finalout<<"\tprint:"<<endl;
    finalout<<"\txor dx,dx"<<endl; 
    finalout<<"\tdiv bx"<<endl;
    finalout<<"\tmov [si],dl"<<endl; 
    finalout<<"\tadd [si],'0'"<<endl;
    finalout<<"\tdec si"<<endl;
    finalout<<"\tcmp ax,0"<<endl;
    finalout<<"\tjne print"<<endl;
    finalout<<"\tinc si"<<endl;
    finalout<<"\tlea dx,si"<<endl;
    finalout<<"\tmov ah,9"<<endl;
    finalout<<"\tint 21h"<<endl;
    finalout<<"\tpop si"<<endl;
    finalout<<"\tpop dx"<<endl;
    finalout<<"\tpop cx"<<endl;
    finalout<<"\tpop bx"<<endl;
    finalout<<"\tpop ax"<<endl;
    finalout<<"\tret"<<endl;
    finalout<<"\tnegate:"<<endl;
    finalout<<"\tpush ax"<<endl;
    finalout<<"\tmov ah,2"<<endl;
    finalout<<"\tmov dl,'-'"<<endl;
    finalout<<"\tint 21h"<<endl;
    finalout<<"\tpop ax"<<endl;
    finalout<<"\tneg ax"<<endl;
    finalout<<"\tjmp print"<<endl;
finalout<<"print_output endp"<<endl;
finalout<<"END main"<<endl;
	fout<<"Total Lines: "<<line_count<<endl;
    fout<<"Total Errors: "<<error<<endl;
    fclose(fp);
    fout.close();
	eout.close();
    tout.close();
    finalout.close();
    pout.close();

    //pout.close();
	return 0;
}

