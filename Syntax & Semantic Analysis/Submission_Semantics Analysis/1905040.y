

%{
#include<cstdio>
#include<cstdlib>
#include<string>
#include<vector>
#include<iostream>
#include<fstream>
#include "1905040.h"

using namespace std;

// int line_count;
FILE *fp;
ofstream fout, eout, pout;
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
    table->enter_scope();
    if(param_list==nullptr){
        return;
    }
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
    SymbolInfo* temp2=table->LookUp(sname->getName());
    temp2->func_def_flag=1;
    if(param_list!=nullptr){
        for(int i=0;i<param_list->var_dec_list.size();i++){
            temp2->func_dec_list.push_back(param_list->var_dec_list[i]);
        }
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

%}


/* %error-verbose */

%union {
    SymbolInfo* symbol_info;
    string* symbol_info_str;
}

%token <symbol_info> IF ELSE FOR WHILE DO BREAK INT CHAR FLOAT DOUBLE VOID RETURN SWITCH CASE DEFAULT CONTINUE PRINTLN ID CONST_INT CONST_FLOAT CONST_CHAR CONST_STRING RELOP MULOP LOGICOP ADDOP LPAREN RPAREN LCURL RCURL LSQUARE RSQUARE COMMA SEMICOLON ASSIGNOP NOT INCOP DECOP
%type <symbol_info> start program unit var_declaration func_declaration func_definition type_specifier compound_statement parameter_list statements declaration_list statement expression expression_statement variable logic_expression rel_expression simple_expression term unary_expression factor argument_list arguments 
/* %start<rulemaker> start */
/* %destructor{/function}<rulemaker> */
%nonassoc LOWER_THAN_ELSE
%nonassoc ELSE
%%

start : program
	{
		string rule="start : program";
        
        fout<<rule<<" "<<endl;
        $$ = new SymbolInfo("start", "program");
        $$->message=rule;
        $$->add($1);
        $$->start=$1->start;
        $$->end=$1->end;
        $$->leaf=0;
        parse_tree_print($$);
	}
	;

program : program unit 
    {
        string rule="program : program unit";
        
        fout<<rule<<" "<<endl;
        $$ = new SymbolInfo("program", "program unit");
        $$->message=rule;
        $$->add($1);
        $$->add($2);
        $$->start=$1->start;
        $$->end=$2->end;
        $$->leaf=0;
    }
	| unit
    {
        string rule="program : unit";
        
        fout<<rule<<" "<<endl;
        $$ = new SymbolInfo("program", "unit");
        $$->message=rule;
        $$->add($1);
        $$->start=$1->start;
        $$->end=$1->end;
        $$->leaf=0;
    }
	;
	
unit : var_declaration
    {
        string rule="unit : var_declaration";
        
        fout<<rule<<" "<<endl;
        $$ = new SymbolInfo("unit", "var_declaration");
        $$->message=rule;
        $$->add($1);
        $$->start=$1->start;
        $$->end=$1->end;
        $$->leaf=0;
    }
     | func_declaration
     {
        string rule="unit : func_declaration";
        
        fout<<rule<<" "<<endl;
        $$ = new SymbolInfo("unit", "func_declaration");
        $$->message=rule;;
        $$->start=$1->start;
        $$->end=$1->end;
        $$->leaf=0;
        $$->add($1);
     }
     | func_definition
     {
        string rule="unit : func_definition";
        
        fout<<rule<<" "<<endl;
        $$ = new SymbolInfo("unit", "func_definition");
        $$->message=rule;
        $$->add($1);
        $$->start=$1->start;
        $$->end=$1->end;
        $$->leaf=0;
     }
     ;
     
func_declaration : type_specifier ID LPAREN parameter_list RPAREN SEMICOLON
    {
        string rule="func_declaration : type_specifier ID LPAREN parameter_list RPAREN SEMICOLON";
        
        fout<<rule<<" "<<endl;
        $$ = new SymbolInfo("func_declaration", "type_specifier ID LPAREN parameter_list RPAREN SEMICOLON");
        $$->message=rule;
        $$->add($1);
        $$->add($2);
        $$->add($3);
        $$->add($4);
        $$->add($5);
        $$->add($6);
        $$->start=$1->start;
        $$->end=$6->end;
        $$->leaf=0;
        SymbolInfo *temp = table->LookUp($2->getName());
        if(temp!=NULL)
        {
            //fout<<"Line# "<<line_count<<": Redeclaration of "<<$2->getName()<<endl;
            if(temp->optional=="FUNCTION")
            eout<<"Line# "<<line_count<<": Redeclaration of "<<$2->getName()<<endl;
            else
            eout<<"Line# "<<line_count<<": "<<$2->getName()<<"' redeclared as different kind of symbol "<<endl;
            error++;
        }
        else
        {
            SymbolInfo *ftemp=new SymbolInfo($2->getName(), $1->getType());
            ftemp->optional="FUNCTION";
            for(int i=0; i<$4->var_dec_list.size(); i++)
            {
                ftemp->func_dec_list.push_back($4->var_dec_list[i]);
            }
            table->opt_insert(ftemp->getName(), ftemp->getType(), ftemp->optional);
            //print_all();
        }
    }
		| type_specifier ID LPAREN RPAREN SEMICOLON
        {
        string rule="func_declaration : type_specifier ID LPAREN RPAREN SEMICOLON";
        
        fout<<rule<<" "<<endl;
        $$ = new SymbolInfo("func_declaration", "type_specifier ID LPAREN RPAREN SEMICOLON");
        $$->message=rule;
        $$->add($1);
        $$->add($2);
        $$->add($3);
        $$->add($4);
        $$->add($5);
        $$->start=$1->start;
        $$->end=$5->end;
        $$->leaf=0;
        SymbolInfo *temp = table->LookUp($2->getName());
        if(temp!=NULL)
        {
            //fout<<"Line# "<<line_count<<": Redeclaration of "<<$2->getName()<<endl;
            if(temp->optional=="FUNCTION")
            eout<<"Line# "<<line_count<<": Redeclaration of "<<$2->getName()<<endl;
            else
            eout<<"Line# "<<line_count<<" :'"<<$2->getName()<<"' redeclared as different kind of symbol "<<endl;
            error++;
        }
        else
        {
            SymbolInfo *ftemp=new SymbolInfo($2->getName(), $1->getType());
            ftemp->optional="FUNCTION";
            table->opt_insert(ftemp->getName(), ftemp->getType(), ftemp->optional);
            //print_all();
        }
        }
		;
		 
func_definition : type_specifier ID LPAREN parameter_list RPAREN {function_into_scope($2,$1,$4);} compound_statement
{
    string rule="func_definition : type_specifier ID LPAREN parameter_list RPAREN compound_statement";
    
        fout<<rule<<" "<<endl;
    $$ = new SymbolInfo("func_definition", "type_specifier ID LPAREN parameter_list RPAREN compound_statement");
        $$->message=rule;
        $$->add($1);
        $$->add($2);
        $$->add($3);
        $$->add($4);
        $$->add($5);
        //$$->add($6);
        $$->add($7);
        $$->start=$1->start;
        $$->end=$7->end;
        $$->leaf=0;
}
		| type_specifier ID LPAREN RPAREN {function_into_scope($2,$1,nullptr);} compound_statement
        {
        string rule="func_definition : type_specifier ID LPAREN RPAREN compound_statement";
        
        fout<<rule<<" "<<endl;
        $$ = new SymbolInfo("func_definition", "type_specifier ID LPAREN RPAREN compound_statement");
        $$->message=rule;
        $$->add($1);
        $$->add($2);
        $$->add($3);
        $$->add($4);
        //$$->add($5);
        $$->add($6);
        $$->start=$1->start;
        $$->end=$6->end;
        $$->leaf=0;
        }
 		;				


parameter_list  : parameter_list COMMA type_specifier ID
{
    string rule="parameter_list : parameter_list COMMA type_specifier ID";
    
        fout<<rule<<" "<<endl;
        $$ = new SymbolInfo("parameter_list", "parameter_list COMMA type_specifier ID");
        $$->message=rule;
        $$->add($1);
        $$->add($2);
        $$->add($3);
        $$->add($4);
        $$->start=$1->start;
        $$->end=$4->end;
        $$->leaf=0;
        $4->setType($3->getType());
        for(int i=0;i<$1->var_dec_list.size();i++)
        {
            $$->var_dec_list.push_back($1->var_dec_list[i]);
        }
        $4->setType($3->getType());
        $$->var_dec_list.push_back($4);
}
		| parameter_list COMMA type_specifier
        {
        string rule="parameter_list : parameter_list COMMA type_specifier";
        
        fout<<rule<<" "<<endl;
        $$ = new SymbolInfo("parameter_list", "parameter_list COMMA type_specifier");
        $$->message=rule;
        $$->add($1);
        $$->add($2);
        $$->add($3);
        $$->start=$1->start;
        $$->end=$3->end;
        $$->leaf=0;
        for(int i=0;i<$1->var_dec_list.size();i++)
        {
            $$->var_dec_list.push_back($1->var_dec_list[i]);
        }
        $$->var_dec_list.push_back($3);
        }
 		| type_specifier ID
        {
        string rule="parameter_list : type_specifier ID";
        
        fout<<rule<<" "<<endl;
        $$ = new SymbolInfo("parameter_list", "type_specifier ID");
        $$->message=rule;
        $$->add($1);
        $$->add($2);
        $$->start=$1->start;
        $$->end=$2->end;
        $$->leaf=0;
        $2->setType($1->getType());
        $$->var_dec_list.push_back($2);
        }
		| type_specifier
        {
        string rule="parameter_list : type_specifier";
        
        fout<<rule<<" "<<endl;
        $$ = new SymbolInfo("parameter_list", "type_specifier");
        $$->message=rule;
        $$->add($1);
        $$->start=$1->start;
        $$->end=$1->end;
        $$->leaf=0;
        $$->var_dec_list.push_back($1);
        }
 		;

 		
compound_statement : LCURL statements RCURL
{
        string rule="compound_statement : LCURL statements RCURL";
        
        fout<<rule<<" "<<endl;
        $$ = new SymbolInfo("compound_statement", "LCURL statements RCURL");
        $$->message=rule;
        $$->add($1);
        $$->add($2);
        $$->add($3);
        $$->start=$1->start;
        $$->end=$3->end;
        $$->leaf=0;
        print_all();
        table->exit_scope();
}
 		    | LCURL RCURL
            {
        string rule="compound_statement : LCURL RCURL";
        
        fout<<rule<<" "<<endl;
        $$ = new SymbolInfo("compound_statement", "LCURL RCURL");
        $$->message=rule;
        $$->add($1);
        $$->add($2);
        $$->start=$1->start;
        $$->end=$2->end;
        $$->leaf=0;
        print_all();
        table->exit_scope();
            }
 		    ;
 		    
var_declaration : type_specifier declaration_list SEMICOLON
{
    string rule="var_declaration : type_specifier declaration_list SEMICOLON";
    
        fout<<rule<<" "<<endl;
        $$ = new SymbolInfo("var_declaration", "type_specifier declaration_list SEMICOLON");
        $$->message=rule;
        $$->add($1);
        $$->add($2);
        $$->add($3);
        $$->start=$1->start;
        $$->end=$3->end;
        $$->leaf=0;
        if($1->getType()=="VOID"){
            error++;
            for(int i=0;i<$2->var_dec_list.size();i++){
                    eout<<"Line# "<<line_count<<": Variable or field '"<<$2->var_dec_list[i]->getName()<<"' declared void"<<endl;
            }
        }
        else{
            
            if ($2 == nullptr) cout << "wtf2" << endl;
           for(int i=0;i<$2->var_dec_list.size();i++){
            if(table->Scope_LookUp($2->var_dec_list[i]->getName())==nullptr){
                if($2->var_dec_list[i]->optional!="ARRAY")
                    table->insert($2->var_dec_list[i]->getName(),$1->getType());
                else{
                    table->opt_insert($2->var_dec_list[i]->getName(),$1->getType(),$2->var_dec_list[i]->optional);
                }
            }
            else{
                error++;
                SymbolInfo* s=new SymbolInfo();
                s=table->Scope_LookUp($2->var_dec_list[i]->getName());
                if($1->getType()!=s->getType()){
                    eout<<"Line# "<<line_count<<": Conflicting types for'"<<s->getName()<<"'"<<endl;
                }
                else {
                    if($1->optional!=s->optional){
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
 		 ;
 		 
type_specifier	: INT
{
    string rule="type_specifier : INT";
    
        fout<<rule<<" "<<endl;
        $$ = new SymbolInfo($1->getName(), "INT");
        $$->message=rule;
        $$->add($1);
        $$->start=$1->start;
        $$->end=$1->end;
        $$->leaf=0;
    //    $1->getName()<<endl;
}
 		| FLOAT
        {
    string rule="type_specifier : FLOAT";
    
        fout<<rule<<" "<<endl;
        $$ = new SymbolInfo($1->getName(), "FLOAT");
        $$->message=rule;
        $$->add($1);
    $$->start=$1->start;
        $$->end=$1->end;
        $$->leaf=0;
        //    $1->getName()<<endl;
}
 		| VOID
        {
    string rule="type_specifier : VOID";
    
        fout<<rule<<" "<<endl;
        $$ = new SymbolInfo($1->getName(), "VOID");
        $$->message=rule;
        $$->add($1);
        $$->start=$1->start;
        $$->end=$1->end;
        $$->leaf=0;
        //    $1->getName()<<endl;
}
 		;
 		
declaration_list : declaration_list COMMA ID
{
    string rule="declaration_list : declaration_list COMMA ID";
    
        fout<<rule<<" "<<endl;
        $$ = new SymbolInfo("declaration_list", "declaration_list COMMA ID");
        $$->message=rule;
        $$->add($1);
        $$->add($2);
        $$->add($3);
        $$->start=$1->start;
        $$->end=$3->end;
        $$->leaf=0;
        for(int i=0;i<$1->var_dec_list.size();i++){
            $$->var_dec_list.push_back($1->var_dec_list[i]);
        }
        $$->var_dec_list.push_back($3);
}
 		  | declaration_list COMMA ID LSQUARE CONST_INT RSQUARE
          {
    string rule="declaration_list : declaration_list COMMA ID LSQUARE CONST_INT RSQUARE";
    
        fout<<rule<<" "<<endl;
        $$ = new SymbolInfo("declaration_list", "declaration_list COMMA ID LSQUARE CONST_INT RSQUARE");
        $$->message=rule;
        $$->add($1);
        $$->add($2);
        $$->add($3);
        $$->add($4);
        $$->add($5);
        $$->add($6);
        $$->start=$1->start;
        $$->end=$6->end;
        $$->leaf=0;
        for(int i=0;i<$1->var_dec_list.size();i++){
            $$->var_dec_list.push_back($1->var_dec_list[i]);
        }
        $3->optional="ARRAY";
        $$->var_dec_list.push_back($3);
}
 		  | ID
          {
        string rule="declaration_list : ID";
        
        fout<<rule<<" "<<endl;
        $$ = new SymbolInfo("declaration_list", "ID");
        $$->message=rule;
        $$->add($1);
        $$->start=$1->start;
        $$->end=$1->end;
        $$->leaf=0;
        $$->var_dec_list.push_back($1);
          }
 		  | ID LSQUARE CONST_INT RSQUARE
          {
            string rule="declaration_list : ID LSQUARE CONST_INT RSQUARE";
            
        fout<<rule<<" "<<endl;
        $$ = new SymbolInfo("declaration_list", "ID LSQUARE CONST_INT RSQUARE");
        $$->message=rule;
        $$->add($1);
        $$->add($2);
        $$->add($3);
        $$->add($4);
        $$->start=$1->start;
        $$->end=$4->end;
        $$->leaf=0;
        $1->optional="ARRAY";
        $$->var_dec_list.push_back($1);
          }
 		  ;
 		  
statements : statement
{
        string rule="statements : statement";
        
        fout<<rule<<" "<<endl;
        $$ = new SymbolInfo("statements", "statement");
        $$->message=rule;
        $$->add($1);
        $$->start=$1->start;
        $$->end=$1->end;
        $$->leaf=0;
}
	   | statements statement
       {
        string rule="statements : statements statement";
        
        fout<<rule<<" "<<endl;
        $$ = new SymbolInfo("statements", "statements statement");
        $$->message=rule;
        $$->add($1);
        $$->add($2);
        $$->start=$1->start;
        $$->end=$2->end;
        $$->leaf=0;
       }
	   ;
	   
statement : var_declaration
{
        string rule="statement : var_declaration";
        
        fout<<rule<<" "<<endl;
        $$ = new SymbolInfo("statement", "var_declaration");
        $$->message=rule;
        $$->add($1);   
        $$->start=$1->start;
        $$->end=$1->end;
        $$->leaf=0;
}
	  | expression_statement
      {
        string rule="statement : expression_statement";
        
        fout<<rule<<" "<<endl;
        $$ = new SymbolInfo("statement", "expression_statement");
        $$->message=rule;
        $$->add($1);
        $$->start=$1->start;
        $$->end=$1->end;
        $$->leaf=0;
      }
	  | compound_statement
      {
        string rule="statement : compound_statement";
        
        fout<<rule<<" "<<endl;
        $$ = new SymbolInfo("statement","compound_statement");
        $$->message=rule;
        $$->add($1);
        $$->start=$1->start;
        $$->end=$1->end;
        $$->leaf=0;
      }
	  | FOR LPAREN expression_statement expression_statement expression RPAREN statement
      {
        string rule="statement: FOR LPAREN expression_statement expression_statement expression RPAREN statement";
        
        fout<<rule<<" "<<endl;
        $$ = new SymbolInfo("statement","FOR LPAREN expression_statement expression_statement expression RPAREN statement");
        $$->message=rule;
        $$->add($1);
        $$->add($2);
        $$->add($3);
        $$->add($4);
        $$->add($5);
        $$->add($6);
        $$->add($7);
        $$->start=$1->start;
        $$->end=$7->end;
        $$->leaf=0;
      }
	  | IF LPAREN expression RPAREN statement  %prec LOWER_THAN_ELSE
      {
        string rule="statement: IF LPAREN expression RPAREN statement";
        
        fout<<rule<<" "<<endl;
        $$ = new SymbolInfo("statement","IF LPAREN expression RPAREN statement");
        $$->message=rule;
        $$->add($1);
        $$->add($2);
        $$->add($3);
        $$->add($4);
        $$->add($5);
        $$->start=$1->start;
        $$->end=$5->end;
        $$->leaf=0;
      }
	  | IF LPAREN expression RPAREN statement ELSE statement
      {
        string rule="statement: IF LPAREN expression RPAREN statement ELSE statement";
        
        fout<<rule<<" "<<endl;
        $$ = new SymbolInfo("statement","IF LPAREN expression RPAREN statement ELSE statement");
        $$->message=rule;
        $$->add($1);
        $$->add($2);
        $$->add($3);
        $$->add($4);
        $$->add($5);
        $$->add($6);
        $$->add($7);
        $$->start=$1->start;
        $$->end=$7->end;
        $$->leaf=0;
      }
	  | WHILE LPAREN expression RPAREN statement
      {
        string rule="statement: WHILE LPAREN expression RPAREN statement";
        
        fout<<rule<<" "<<endl;
        $$ = new SymbolInfo("statement","WHILE LPAREN expression RPAREN statement");
        $$->message=rule;
        $$->add($1);
        $$->add($2);
        $$->add($3);
        $$->add($4);
        $$->add($5);
        $$->start=$1->start;
        $$->end=$5->end;
        $$->leaf=0;
      }
	  | PRINTLN LPAREN ID RPAREN SEMICOLON
      {
        string rule="statement: PRINTLN LPAREN ID RPAREN SEMICOLON";
        
        fout<<rule<<" "<<endl;
        $$ = new SymbolInfo("statement","PRINTLN LPAREN ID RPAREN SEMICOLON");
        $$->message=rule;
        $$->add($1);
        $$->add($2);
        $$->add($3);
        $$->add($4);
        $$->add($5);
        $$->start=$1->start;
        $$->end=$5->end;
        $$->leaf=0;
      }
	  | RETURN expression SEMICOLON
      {
        string rule="statement : RETURN expression SEMICOLON";
        
        fout<<rule<<" "<<endl;
        $$ = new SymbolInfo("statement","RETURN expression SEMICOLON");
        $$->message=rule;
        $$->add($1);
        $$->add($2);
        $$->add($3);
        $$->start=$1->start;
        $$->end=$3->end;
        $$->leaf=0;
      }
	  ;
	  
expression_statement 	: SEMICOLON
{
        string rule="expression_statement : SEMICOLON";
        
        fout<<rule<<" "<<endl;
        $$ = new SymbolInfo("expression_statement", "SEMICOLON");
        $$->message=rule;
        $$->add($1);
        $$->start=$1->start;
        $$->end=$1->end;
        $$->leaf=0;
}			
			| expression SEMICOLON
            {
        string rule="expression_statement : expression SEMICOLON";
        
        fout<<rule<<" "<<endl;
            $$ = new SymbolInfo("expression_statement", "expression SEMICOLON");
        $$->message=rule;
        $$->add($1);    
        $$->add($2);
        $$->start=$1->start;
        $$->end=$2->end;
        $$->leaf=0;
            } 
			;
	  
variable : ID 	
{
        string rule="variable : ID";
        
        fout<<rule<<" "<<endl;
        $$ = new SymbolInfo("variable", "ID");
        $$->message=rule;
        $$->add($1);
        $$->start=$1->start;
        $$->end=$1->end;
        $$->leaf=0;
        SymbolInfo *temp=table->LookUp($1->getName());
        if(temp==NULL)
        {
            eout<<"Line# "<<line_count<<": Undeclared variable '"<<$1->getName()<<"'"<<endl;
            error++;
        }
        else{
            $$->setType(temp->getType());
        }
        
}	
	 | ID LSQUARE expression RSQUARE
     {
        string rule="variable : ID LSQUARE expression RSQUARE";
        
        fout<<rule<<" "<<endl;
        $$ = new SymbolInfo("variable", "ID LSQUARE expression RSQUARE");
        $$->message=rule;
        $$->add($1);
        $$->add($2);
        $$->add($3);
        $$->add($4);
        $$->start=$1->start;
        $$->end=$4->end;
        $$->leaf=0;
            SymbolInfo *temp=table->LookUp($1->getName());
            if(temp==NULL)
            {
                eout<<"Line# "<<line_count<<": Undeclared variable "<<$1->getName()<<endl;
                error++;
            }
            else{
                if(temp->optional!="ARRAY"){
                    eout<<"Line# "<<line_count<<": '"<<$1->getName()<<"'"<<" is not an array"<<endl;
                    error++;
                }
                else if($3->getType()!="INT")
                {
                    eout<<"Line# "<<line_count<<": Array subscript is not an integer"<<endl;
                    error++;
                }
        
                else $$->setType(temp->getType());
            }
            
        } 
	 ;
	 
 expression : logic_expression
 {
        string rule="expression : logic_expression";
        
        fout<<rule<<" "<<endl;
        $$ = new SymbolInfo($1->getName(), "logic_expression");
        $$->message=rule;
        $$->add($1);
        $$->start=$1->start;
        $$->end=$1->end;
        $$->leaf=0;
        $$->setType($1->getType());
        cout<<"logic going to expr    "<<$1->getName()<<endl;
 }	
	   | variable ASSIGNOP logic_expression
       {
        string rule="expression : variable ASSIGNOP logic_expression";
        
        fout<<rule<<" "<<endl;
        $$ = new SymbolInfo("expression", "variable ASSIGNOP logic_expression");
        $$->message=rule;
        $$->add($1);
        $$->add($2);
        $$->add($3);
        $$->start=$1->start;
        $$->end=$3->end;
        $$->leaf=0;
        if($1->getType()=="VOID" || $3->getType()=="VOID"){
                eout<<"Line# "<<line_count<<": Void cannot be used in expression "<<endl;
                error++;
            }
        else if($1->getType()=="INT" && $3->getType()=="FLOAT"){
                eout<<"Line# "<<line_count<<": Warning: possible loss of data in assignment of FLOAT to INT"<<endl;
                error++;
            }
        else $$->setType($1->getType());
        }	
	   ;
			
logic_expression : rel_expression
{
        string rule="logic_expression : rel_expression";
        
        fout<<rule<<" "<<endl;
        $$ = new SymbolInfo($1->getName(), "rel_expression");
        $$->message=rule;
        $$->add($1);
        $$->start=$1->start;
        $$->end=$1->end;
        $$->leaf=0;
        $$->setType($1->getType());
        cout<<"relop going to logic    "<<$1->getName()<<endl;
} 	
		 | rel_expression LOGICOP rel_expression 
         {
        string rule="logic_expression : rel_expression LOGICOP rel_expression";
        
        fout<<rule<<" "<<endl;
        $$ = new SymbolInfo("logic_expression", "rel_expression LOGICOP rel_expression");
        $$->message=rule;
        $$->add($1);
        $$->add($2);
        $$->add($3);
        $$->start=$1->start;
        $$->end=$3->end;
        $$->leaf=0;
        if($1->getType()=="VOID"){
                eout<<"Line# "<<line_count<<": Void cannot be used in expression "<<endl;
                error++;
            }
        else $$->setType("INT");
         }	
		 ;
			
rel_expression	: simple_expression
{
        string rule="rel_expression : simple_expression";
        
        fout<<rule<<" "<<endl;
        $$ = new SymbolInfo($1->getName(), "simple_expression");
        $$->message=rule;
        $$->add($1);
        $$->start=$1->start;
        $$->end=$1->end;
        $$->leaf=0;
        $$->setType($1->getType());
        cout<<"simp_expr going to relop    "<<$1->getName()<<endl;
} 
		| simple_expression RELOP simple_expression
        {
        string rule="rel_expression	: simple_expression RELOP simple_expression";
        
        fout<<rule<<" "<<endl;
        $$ = new SymbolInfo("rel_expression", "simple_expression RELOP simple_expression");
        $$->message=rule;
        $$->add($1);
        $$->add($2);
        $$->add($3);
        $$->start=$1->start;
        $$->end=$3->end;
        $$->leaf=0;
        if($1->getType()=="VOID"){
                eout<<"Line# "<<line_count<<": Void cannot be used in expression "<<endl;
                error++;
            }
        else $$->setType("INT");
        }	
		;
				
simple_expression : term
{
        string rule="simple_expression : term";
        
        fout<<rule<<" "<<endl;
        $$ = new SymbolInfo($1->getName(), "term");
        $$->message=rule;
        $$->add($1);
        $$->start=$1->start;
        $$->end=$1->end;
        $$->leaf=0;
        $$->setType($1->getType());
        cout<<"term going to simp_expr    "<<$1->getName()<<endl;
} 
		  | simple_expression ADDOP term
          {
        string rule="simple_expression : simple_expression ADDOP term";
        
        fout<<rule<<" "<<endl;
        $$ = new SymbolInfo("simple_expression", "simple_expression ADDOP term");
        $$->message=rule;
        $$->add($1);
        $$->add($2);
        $$->add($3);
        $$->start=$1->start;
        $$->end=$3->end;
        $$->leaf=0;
        if($1->getType()=="VOID" ||$3->getType()=="VOID"){
                if($1->getType()=="VOID")
                eout<<"Line# "<<line_count<<": Void cannot be used in expression "<<endl;
                else
                eout<<"Line# "<<line_count<<": Void cannot be used in expression "<<endl;
                error++;
            }
        else if($1->getType()=="FLOAT" ||$3->getType()=="FLOAT"){
                $$->setType("FLOAT");
            }
        else{
                $$->setType("INT");
            }
          } 
		  ;
					
term :	unary_expression
{
        string rule="term : unary_expression";
        
        fout<<rule<<" "<<endl;
        $$ = new SymbolInfo($1->getName(), "unary_expression");
        $$->message=rule;
        $$->add($1);
        $$->start=$1->start;
        $$->end=$1->end;
        $$->leaf=0;
        $$->setType($1->getType());
        cout<<"uni going to term    "<<$1->getName()<<endl;
}
     |  term MULOP unary_expression
     {
        string rule="term : term MULOP unary_expression";
        
        fout<<rule<<" "<<endl;
        $$ = new SymbolInfo("term", "term MULOP unary_expression");
        $$->message=rule;
        $$->add($1);
        $$->add($2);
        $$->add($3);
        $$->start=$1->start;
        $$->end=$3->end;
        $$->leaf=0;
        cout<<"Here at mullop with "<<$3->getName()<<endl;
        //    $2->getName()<<"  Line number"<<line_count<<"    "<<$1->getName()<<endl;
        
            if($1->getType()=="VOID" ||$3->getType()=="VOID"){
                if($1->getType()=="VOID")
                eout<<"Line# "<<line_count<<": Void cannot be used in expression "<<endl;
                else 
                eout<<"Line# "<<line_count<<": Void cannot be used in expression "<<endl;
                error++;
            }
            else if($2->getName()== "%" && ($1->getType()=="FLOAT"||$3->getType()=="FLOAT")){
                eout<<"Line# "<<line_count<<": Operands of modulus must be integers "<<endl;
                error++;
            }
            else if(($2->getName()== "/" || $2->getName()== "%") && $3->getName()=="0"){
                eout<<"Line# "<<line_count<<": Warning: division by zero i=0f=1Const=0"<<endl;
                error++;
            }
            else if($1->getType()=="FLOAT" ||$3->getType()=="FLOAT"){
                $$->setType("FLOAT");
            }
            else{
                $$->setType("INT");
            }
        
     }
     ;

unary_expression : ADDOP unary_expression 
{
        string rule="unary_expression : ADDOP unary_expression";
        
        fout<<rule<<" "<<endl;
        $$ = new SymbolInfo("unary_expression", "ADDOP unary_expression");
        $$->message=rule;
        $$->add($1);
        $$->add($2);
        $$->start=$1->start;
        $$->end=$2->end;
        $$->leaf=0;
        if($2->getType()=="VOID"){
            eout<<"Line# "<<line_count<<": VOID cannot be used in expression "<<endl;
            error++;
        }
        else
        $$->setType($2->getType());
} 
		 | NOT unary_expression 
         {
        string rule="unary_expression : NOT unary_expression";
        
        fout<<rule<<" "<<endl;
        $$ = new SymbolInfo("unary_expression", "NOT unary_expression");
        $$->message=rule;
        $$->add($1);
        $$->add($2);
        $$->start=$1->start;
        $$->end=$2->end;
        $$->leaf=0;
        $$->setType("INT");
        if($2->getType()=="VOID"){
            eout<<"Line# "<<line_count<<": VOID cannot be used in expression "<<endl;
            error++;
        }
         }
		 | factor 
         {
        string rule="unary_expression : factor";
        
        fout<<rule<<" "<<endl;
        $$ = new SymbolInfo($1->getName(), "factor");
        $$->message=rule;
        $$->add($1);
        $$->start=$1->start;
        $$->end=$1->end;
        $$->leaf=0;
        $$->setType($1->getType());
        cout<<"factor going to uni    "<<$1->getName()<<endl;
         }
		 ;
	
factor	: variable 
{
        string rule="factor : variable";
        
        fout<<rule<<" "<<endl;
        $$ = new SymbolInfo($1->getName(), "variable");
        $$->message=rule;
        $$->add($1);
        $$->start=$1->start;
        $$->end=$1->end;
        $$->leaf=0;
        $$->setType($1->getType());
}
	| ID LPAREN argument_list RPAREN
    {
        string rule="factor : ID LPAREN argument_list RPAREN";
        
        fout<<rule<<" "<<endl;
        $$ = new SymbolInfo($1->getName(), "ID LPAREN argument_list RPAREN");
        $$->message=rule;
        $$->add($1);
        $$->add($2);
        $$->add($3);
        $$->add($4);
        $$->start=$1->start;
        $$->end=$4->end;
        $$->leaf=0;
        SymbolInfo *temp = table->LookUp($1->getName());
        if(temp==NULL){
            eout<<"Line# "<<line_count<<": Undeclared function '"<<$1->getName()<<"'"<<endl;
            error++;
        }
        else if(temp->optional!="FUNCTION"){
            eout<<"Line# "<<line_count<<": '"<<$1->getName()<<"' is not a function"<<endl;
            error++;
        }
        else{
            $$->setType(temp->getType());
            if(temp->func_dec_list.size()<$3->var_dec_list.size()){
                eout<<"Line# "<<line_count<<": Too many arguments to function '"<<$1->getName()<<"'"<<endl;
                //    temp->func_dec_list.size()<<" "<<$3->var_dec_list.size()<<endl;
                error++;
            }
            else if(temp->func_dec_list.size()>$3->var_dec_list.size()){
                eout<<"Line# "<<line_count<<": Too few arguments to function '"<<$1->getName()<<"'"<<endl;
                error++;
            }
            else{
                for(int i=0;i<temp->func_dec_list.size();i++){
                    if(temp->func_dec_list[i]->getType()!=$3->var_dec_list[i]->getType()){
                        eout<<"Line# "<<line_count<<": Type mismatch for argument "<<i+1<<" of '"<<$1->getName()<<"'"<<endl;
                        error++;
                    }
                }
            }
        }
    }
	| LPAREN expression RPAREN
    {
        string rule="factor	: LPAREN expression RPAREN";
        
        fout<<rule<<" "<<endl;
        $$ = new SymbolInfo($1->getName(), "LPAREN expression RPAREN");
        $$->message=rule;
        $$->add($1);
        $$->add($2);
        $$->add($3);
        $$->start=$1->start;
        $$->end=$3->end;
        $$->leaf=0;
        if($2->getName()=="0")
            $$->setName("0");
        $$->setType($2->getType());
    }
	| CONST_INT
    {
        string rule="factor : CONST_INT";
        
        fout<<rule<<" "<<endl;
        $$ = new SymbolInfo($1->getName(), "INT");
        $$->message=rule;
        $$->add($1);
        $$->start=$1->start;
        $$->end=$1->end;
        $$->leaf=0;
        if($1->getName()=="0")
            $$->setName("0");
        //    $$->getName()<<"  $$"<<endl;
        //    $1->getName()<<"  $1"<<endl;    
    } 
	| CONST_FLOAT
    {
        string rule="factor : CONST_FLOAT";
        
        fout<<rule<<" "<<endl;
        $$ = new SymbolInfo($1->getName(), "FLOAT");
        $$->message=rule;
        $$->add($1);
        $$->start=$1->start;
        $$->end=$1->end;
        $$->leaf=0;
        if($1->getName()=="0")
            $$->setName("0");
    }
	| variable INCOP
    {
        string rule="factor : variable INCOP";
        
        fout<<rule<<" "<<endl;
        $$ = new SymbolInfo($1->getName(), "variable INCOP");
        $$->message=rule;
        $$->add($1);
        $$->add($2);
        $$->start=$1->start;
        $$->end=$2->end;
        $$->leaf=0;
        $$->setType($1->getType());
    } 
	| variable DECOP
    {
        string rule="factor	: variable DECOP";
        
        fout<<rule<<" "<<endl;
        $$ = new SymbolInfo($1->getName(), "variable DECOP");
        $$->message=rule;
        $$->add($1);
        $$->add($2);
        $$->start=$1->start;
        $$->end=$2->end;
        $$->leaf=0;
        $$->setType($1->getType());
    }
	;
	
argument_list : arguments
{
        string rule="argument_list : arguments";
        
        fout<<rule<<" "<<endl;
        $$ = new SymbolInfo("argument_list", "arguments");
        $$->message=rule;
        $$->add($1);
        $$->start=$1->start;
        $$->end=$1->end;
        $$->leaf=0;
        for(int i=0;i<$1->var_dec_list.size();i++){
            $$->var_dec_list.push_back($1->var_dec_list[i]);
        }
}
			  |
              {
                string rule="argument_list : ";
                $$ = new SymbolInfo();
                $$->var_dec_list.clear();
              }
			  ;
	
arguments : arguments COMMA logic_expression
{
        string rule="arguments : arguments COMMA logic_expression";
        
        fout<<rule<<" "<<endl;
        $$ = new SymbolInfo("arguments", "arguments COMMA logic_expression");
        $$->message=rule;
        $$->add($1);
        $$->add($2);
        $$->add($3);
        $$->start=$1->start;
        $$->end=$3->end;
        $$->leaf=0;
        for(int i=0;i<$1->var_dec_list.size();i++){
            $$->var_dec_list.push_back($1->var_dec_list[i]);
        }
        $$->var_dec_list.push_back($3);
}
	      | logic_expression
          {
            string rule="arguments : logic_expression";
            
        fout<<rule<<" "<<endl;
            $$ = new SymbolInfo("arguments", "logic_expression");
            $$->message=rule;
        $$->add($1);
            $$->start=$1->start;
            $$->end=$1->end;
            $$->leaf=0;
            $$->var_dec_list.push_back($1);
          }
	      ;

%%
int main(int argc,char *argv[])
{
    
	globals a;
    fout.open("output.txt",ios::out | ios::trunc );
    eout.open("error_output.txt",ios::out | ios::trunc );
    pout.open("parser_output.txt",ios::out | ios::trunc );
    table=new SymbolTable(11);
    if((fp=fopen(argv[1],"r"))==NULL)
	{
		printf("Cannot Open Input File.\n");
		exit(1);
	}
	yyin=fp;
	yyparse();
	fout<<"Total Lines: "<<line_count<<endl;
    fout<<"Total Errors: "<<error<<endl;
    fclose(fp);
    fout.close();
	eout.close();
    pout.close();
	return 0;
}

