

%{
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

%}


/* %error-verbose */

%union {
    SymbolInfo* symbol_info;
    string* symbol_info_str;
}

%token <symbol_info> IF ELSE FOR WHILE DO BREAK INT CHAR FLOAT DOUBLE VOID RETURN SWITCH CASE DEFAULT CONTINUE PRINTLN ID CONST_INT CONST_FLOAT CONST_CHAR CONST_STRING RELOP MULOP LOGICOP ADDOP LPAREN RPAREN LCURL RCURL LSQUARE RSQUARE COMMA SEMICOLON ASSIGNOP NOT INCOP DECOP
%type <symbol_info> start program unit var_declaration func_declaration func_definition type_specifier compound_statement parameter_list statements declaration_list statement expression expression_statement variable logic_expression rel_expression simple_expression term unary_expression factor argument_list arguments
%type <symbol_info> M N
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
        //tout<<$2->getName()<<" PROC"<<endl;

}
		| type_specifier ID LPAREN RPAREN {function_into_scope($2,$1,new SymbolInfo());} compound_statement
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

 		
compound_statement : LCURL {table->enter_scope();} statements RCURL
{
        string rule="compound_statement : LCURL statements RCURL";
        
        fout<<rule<<" "<<endl;
        $$ = new SymbolInfo("compound_statement", "LCURL statements RCURL");
        $$->message=rule;
        $$->add($1);
        //$$->add($2);
        $$->add($3);
        $$->add($4);
        $$->start=$1->start;
        $$->end=$4->end;
        $$->leaf=0;
        print_all();
        table->exit_scope();
        func_check=1;
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
        if(table->getScopeCount()==1){
            //$$->isGlobal=true;
            for(int i=0;i<$2->var_dec_list.size();i++){
                    $2->var_dec_list[i]->is_global=true;
                    if($2->var_dec_list[i]->optional!="ARRAY")
                    finalout<<$2->var_dec_list[i]->getName()<<" DW 1 DUP (0000H)"<<endl;
                    else{
                        finalout<<$2->var_dec_list[i]->getName()<<" DW "<<$2->var_dec_list[i]->array_size<<" DUP (0000H)"<<endl;
                    }
            }
        }
        else{
            setoffset=table->current->scope_offset;
            for(int i=0;i<$2->var_dec_list.size();i++){
                $2->var_dec_list[i]->is_global=false;
                   if($2->var_dec_list[i]->optional!="ARRAY"){
                          setoffset=setoffset+2;
                          table->current->scope_offset=setoffset;
                        $2->var_dec_list[i]->offset=setoffset;
                        tout<<"SUB SP, 2"<<endl;
                        temp_line_count++;
                   }
                    
                    else{
                        $2->var_dec_list[i]->offset=setoffset+2;
                        setoffset=setoffset+2*$2->var_dec_list[i]->array_size;
                        table->current->scope_offset=setoffset;
                        tout<<"SUB SP, "<<2*$2->var_dec_list[i]->array_size<<endl;
                        temp_line_count++;
                    }
            }
            
        }
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
                if($2->var_dec_list[i]->optional!="ARRAY"){
                    //table->insert($2->var_dec_list[i]->getName(),$1->getType());
                    table->sinsert($2->var_dec_list[i]);
                }   
                else{
                    //table->opt_insert($2->var_dec_list[i]->getName(),$1->getType(),$2->var_dec_list[i]->optional);
                    table->osinsert($2->var_dec_list[i]);
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
        $3->array_size=stoi($5->getName());
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
        $$->nextlist=$1->nextlist;
}
	   | statements M statement
       {
        string rule="statements : statements statement";
        
        fout<<rule<<" "<<endl;
        $$ = new SymbolInfo("statements", "statements statement");
        $$->message=rule;
        $$->add($1);
        $$->add($2);
        $$->add($3);
        $$->start=$1->start;
        $$->end=$3->end;
        $$->leaf=0;
        backpatch($1->nextlist,$2->label);
        $$->nextlist=$3->nextlist;
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
	  | FOR LPAREN expression_statement M expression_statement M expression N RPAREN M statement
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
        $$->add($8);
        $$->add($9);
        $$->add($10);
        $$->add($11);
        $$->start=$1->start;
        $$->end=$7->end;
        $$->leaf=0;
        backpatch($3->nextlist,$4->label);
        backpatch($5->truelist,$10->label);
        backpatch($7->nextlist,$4->label);
        backpatch($11->nextlist,$6->label);
        backpatch($8->nextlist,$4->label);
        $$->nextlist=$5->falselist;
        tout<<"JMP "<<$6->label<<endl;
      }
	  | IF LPAREN expression RPAREN M statement  %prec LOWER_THAN_ELSE
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
        $$->add($6);
        $$->start=$1->start;
        $$->end=$5->end;
        $$->leaf=0;
        backpatch($3->truelist,$5->label);
        $$->nextlist=merge($3->falselist,$6->nextlist);
      }
	  | IF LPAREN expression RPAREN M statement ELSE N M statement
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
        $$->add($8);
        $$->add($9);
        $$->add($10);
        $$->start=$1->start;
        $$->end=$7->end;
        $$->leaf=0;
        backpatch($3->truelist,$5->label);
        backpatch($3->falselist,$9->label);
        vector temp=merge($6->nextlist,$7->nextlist);
        $$->nextlist=merge(temp,$10->nextlist);

      }
	  | WHILE M LPAREN expression RPAREN M statement
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
        $$->add($6);
        $$->add($7);
        $$->start=$1->start;
        $$->end=$5->end;
        $$->leaf=0;
        backpatch($4->truelist,$6->label);
        backpatch($7->nextlist,$2->label);
        $$->nextlist=$4->falselist;
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
        
        SymbolInfo *temp=table->LookUp($3->getName());
        if(temp->is_global==true){
            cout<<"global Variable name is "<<temp->getName()<<endl;
            temp->ad=$3->getName();
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
        if(temp->is_global==true){
            $$->is_global=true;
            $$->ad=$1->getName();
        }
        else{
            $$->is_global=false;
            cout<<table->current->scope_offset<<endl;
            //$$->ad=$1->getName();
            $$->ad="[BP-"+to_string(temp->offset)+"]";
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
        $$->arith_check=$1->arith_check;
        $$->truelist=$1->truelist;
        $$->falselist=$1->falselist;
        $$->nextlist=$1->nextlist;
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
        if($3->arith_check==0){
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
            backpatch($3->truelist,l1);
            backpatch($3->falselist,l2);
        }
        tout<<"POP AX"<<endl;
        temp_line_count++;
        tout<<"MOV "<<$1->ad<<",AX"<<endl;
        temp_line_count++;
        tout<<"PUSH AX"<<endl;
        temp_line_count++;
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
        $$->truelist=$1->truelist;
        $$->falselist=$1->falselist;
        $$->arith_check=$1->arith_check;
        $$->nextlist=$1->nextlist;
} 	
		 | rel_expression {is_arith($1);} LOGICOP M rel_expression 
         {
        string rule="logic_expression : rel_expression LOGICOP rel_expression";
        fout<<rule<<" "<<endl;
        $$ = new SymbolInfo("logic_expression", "rel_expression LOGICOP rel_expression");
        $$->message=rule;
        $$->add($1);
        //$$->add($2);
        $$->add($3);
        $$->add($4);
        $$->add($5);
        $$->start=$1->start;
        $$->end=$5->end;
        $$->leaf=0;
        if($1->getType()=="VOID"){
                eout<<"Line# "<<line_count<<": Void cannot be used in expression "<<endl;
                error++;
            }
        else $$->setType("INT");
        if($5->arith_check==1){
        tout<<"POP AX"<<endl;
        temp_line_count++;
        tout<<"CMP AX,0";
        temp_line_count++;
        tout<<"JNE "<<endl;
        cout<<"JNE er por print "<<endl;
        $5->truelist.push_back(temp_line_count);
        temp_line_count++;
        tout<<"JMP "<<endl;
        cout<<"JMP er por print "<<endl;
        $5->falselist.push_back(temp_line_count);
        temp_line_count++;
        cout<<"truelist falselist push kora shesh ekhn print"<<endl;
        for(int i=0;i<$5->truelist.size();i++){
            cout<<$5->truelist[i]<<" truelist e print kortesi"<<endl;
        }
        for(int i=0;i<$5->falselist.size();i++){
            cout<<$5->falselist[i]<<" falselist e print kortesi"<<endl;
        }
        
    }
        if($3->getName()=="||"){
            
            backpatch($1->falselist,$4->label);
            $$->truelist=merge($1->truelist,$5->truelist);
            $$->falselist=$5->falselist;
            cout<<"or rule e print kortesi,label"<<$4->label<<endl;
        
        }
        else if($3->getName()=="&&"){
            backpatch($1->truelist,$4->label);
            $$->truelist=$5->truelist;
            $$->falselist=merge($1->falselist,$5->falselist);
            cout<<"and rule e print kortesi"<<$4->label<<endl;
    
        }
    for(int i=0;i<$$->truelist.size();i++){
        cout<<$$->truelist[i]<<" Logicop rule e print kortesi"<<endl;
    }
    for(int i=0;i<$5->truelist.size();i++){
            cout<<$5->truelist[i]<<"\$5 truelist e print kortesi"<<endl;
        }
        for(int i=0;i<$5->falselist.size();i++){
            cout<<$5->falselist[i]<<"\$5 falselist e print kortesi"<<endl;
        }
        for(int i=0;i<$1->truelist.size();i++){
            cout<<$5->truelist[i]<<"\$1 truelist e print kortesi"<<endl;
        }
        for(int i=0;i<$1->falselist.size();i++){
            cout<<$5->falselist[i]<<"\$1 falselist e print kortesi"<<endl;
        }
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
        $$->arith_check=$1->arith_check;
        $$->nextlist=$1->nextlist;
        $$->truelist=$1->truelist;
        $$->falselist=$1->falselist;
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
        tout<<"POP BX"<<endl;
        temp_line_count++;
        tout<<"POP AX"<<endl;
        temp_line_count++;
        tout<<"CMP AX,BX"<<endl;
        temp_line_count++;
        if($2->getName()==">"){
            tout<<"JG "<<endl;
            $$->truelist.push_back(temp_line_count);
            temp_line_count++;
        }
        else if($2->getName()=="<"){
            tout<<"JL "<<endl;
            $$->truelist.push_back(temp_line_count);
            temp_line_count++;
        }
        else if($2->getName()=="=="){
            tout<<"JE "<<endl;
            $$->truelist.push_back(temp_line_count);
            temp_line_count++;
        }
        else if($2->getName()=="!="){
            tout<<"JNE "<<endl;
            $$->truelist.push_back(temp_line_count);
            temp_line_count++;
        }
        else if($2->getName()==">="){
            tout<<"JGE "<<endl;
            $$->truelist.push_back(temp_line_count);
            temp_line_count++;
        }
        else if($2->getName()=="<="){
            tout<<"JLE "<<endl;
            $$->truelist.push_back(temp_line_count);
            temp_line_count++;
        }
        tout<<"JMP "<<endl;
        $$->falselist.push_back(temp_line_count);
        temp_line_count++;	
        for(int i=0;i<$$->truelist.size();i++){
        cout<<$$->truelist[i]<<" Relop rule e print kortesi"<<endl;
        }
        };
				
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
        $$->arith_check=$1->arith_check;
        $$->truelist=$1->truelist;
        $$->falselist=$1->falselist;
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
            $$->arith_check=1;
            tout<<"POP BX"<<endl;
            temp_line_count++;
            tout<<"POP AX"<<endl;
            temp_line_count++;
            if($2->getName()=="+"){
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
        $$->arith_check=$1->arith_check;
        $$->truelist=$1->truelist;
        $$->falselist=$1->falselist;
    
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
            $$->arith_check=1;
            tout<<"POP BX"<<endl;
            temp_line_count++;
            tout<<"POP AX"<<endl;
            temp_line_count++;
            if($2->getName()=="/"){
                tout<<"CWD"<<endl;
                temp_line_count++;
                tout<<"DIV BX"<<endl;
                temp_line_count++;
            }
            else if($2->getName()=="*"){
                tout<<"MUL BX"<<endl;
                temp_line_count++;
            }
            else if($2->getName()=="%"){
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
        $$->arith_check=1;
        if($1->getName()=="-"){
            tout<<"POP AX"<<endl;
            temp_line_count++;
            tout<<"NEG AX"<<endl;
            temp_line_count++;
            tout<<"PUSH AX"<<endl;
            temp_line_count++;
        }

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

        // tout<<"POP AX"<<endl;
        // temp_line_count++;
        // tout<<"NOT AX"<<endl;
        // temp_line_count++;
        // tout<<"PUSH AX"<<endl;
        // temp_line_count++;
        $$->truelist=$2->falselist;
        $$->falselist=$2->truelist;

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
        $$->arith_check=$1->arith_check;
        $$->truelist=$1->truelist;
        $$->falselist=$1->falselist;
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
        $$->arith_check=1;
        tout<<"MOV AX,"<<$1->ad<<endl;
        temp_line_count++;
        tout<<"PUSH AX"<<endl;
        temp_line_count++;
        //$$->arith_check=$1->arith_check;
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
        $$->arith_check=1;
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
        $$->arith_check=$2->arith_check;
        $$->truelist=$2->truelist;
        $$->falselist=$2->falselist;
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
        $$->arith_check=1;
        tout<<"MOV AX,"<<$1->getName()<<endl;
        temp_line_count++;
        tout<<"PUSH AX"<<endl;
        temp_line_count++;
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
        $$->arith_check=1;
        //tout<<"POP AX"<<endl;
        tout<<"MOV AX,"<<$1->ad<<endl;
        temp_line_count++;
        tout<<"PUSH AX"<<endl;
        temp_line_count++;
        tout<<"INC AX"<<endl;
        temp_line_count++;
        tout<<"MOV "<<$1->ad<<",AX"<<endl;
        temp_line_count++;
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
        $$->arith_check=1;
        //tout<<"POP AX"<<endl;
        tout<<"MOV AX,"<<$1->ad<<endl;
        temp_line_count++;
        tout<<"PUSH AX"<<endl;
        temp_line_count++;
        tout<<"DEC AX"<<endl;
        temp_line_count++;
        tout<<"MOV "<<$1->ad<<",AX"<<endl;
        temp_line_count++;
        //tout<<"PUSH AX"<<endl;
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
M :
{
    $$ = new SymbolInfo("M", "");
    string temp=to_string(label_count);
    $$->label=temp;
    tout<<"L"<<temp<<":"<<endl;
    temp_line_count++;
    label_count++;
};
N :
{
    $$ = new SymbolInfo("N", "");
    $$->nextlist.push_back(temp_line_count);
};

%%
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

