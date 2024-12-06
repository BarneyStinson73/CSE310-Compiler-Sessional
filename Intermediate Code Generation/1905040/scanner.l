
%{
#include<iostream>
#include<stdlib.h>
#include<string.h>
#include<fstream>
#include "template.h"
#include "y.tab.h"


using namespace std;


// extern YYSTYPE yylval.symbol_info;
extern SymbolTable *table;
extern ofstream fout;
void yyerror(char *);

int line_count=1;
int error=0;


%}



digit [0-9]
letter [A-Za-z]
delim [ \t\r\f\v]
newline \n
ws [delim]+
id (_|{letter})(_|{letter}|{digit})*
integer {digit}+
number {digit}*(\.{digit}+)?(E[+-]?{digit}+)?
ADDOP [+-] 
MULOP [*/%]

%%

{delim}+	{}
{newline} {line_count++;}

"if" {
    SymbolInfo *s= new  SymbolInfo(yytext, (char *)"IF");
	yylval.symbol_info = s;
	s->leaf = 1;
	s->start=s->end=line_count;
	s->message = "IF : if";
	fout<<"Line# "<<line_count<<": Token <IF> Lexeme "<<yytext<<" found"<<endl;
	return IF;
	}
"else" {
    SymbolInfo *s= new  SymbolInfo(yytext, (char *)"ELSE");
    yylval.symbol_info = s;
	s->leaf = 1;
	s->start=s->end=line_count;
	s->message = "ELSE : else";
	fout<<"Line# "<<line_count<<": Token <ELSE> Lexeme "<<yytext<<" found"<<endl;
	return ELSE;}
"for" {
    SymbolInfo *s= new  SymbolInfo(yytext, (char *)"FOR");
    yylval.symbol_info = s;
	s->leaf = 1;
	s->start=s->end=line_count;
	s->message = "FOR : for";
	fout<<"Line# "<<line_count<<": Token <FOR> Lexeme "<<yytext<<" found"<<endl;
	return FOR;}
"while" {
    SymbolInfo *s= new  SymbolInfo(yytext, (char *)"WHILE");
    yylval.symbol_info = s;
	s->leaf = 1;
	s->start=s->end=line_count;
	s->message = "WHILE : while";
	fout<<"Line# "<<line_count<<": Token <WHILE> Lexeme "<<yytext<<" found"<<endl;
	return WHILE;}
"int" {
    SymbolInfo *s= new  SymbolInfo(yytext, (char *)"INT");
    yylval.symbol_info = s;
	s->leaf = 1;
	s->start=s->end=line_count;
	s->message = "INT : int";
	fout<<"Line# "<<line_count<<": Token <INT> Lexeme "<<yytext<<" found"<<endl;
	return INT;}
"float" {
    SymbolInfo *s= new  SymbolInfo(yytext, (char *)"FLOAT");
    yylval.symbol_info = s;
	s->leaf = 1;
	s->start=s->end=line_count;
	s->message = "FLOAT : float";
	fout<<"Line# "<<line_count<<": Token <FLOAT> Lexeme "<<yytext<<" found"<<endl;
	return FLOAT;}
"double" {

    SymbolInfo *s= new  SymbolInfo(yytext, (char *)"DOUBLE");
    yylval.symbol_info = s;
	s->leaf = 1;
	s->start=s->end=line_count;
	s->message = "DOUBLE : double";
	fout<<"Line# "<<line_count<<": Token <DOUBLE> Lexeme "<<yytext<<" found"<<endl;
	return DOUBLE;}
"char" {
    SymbolInfo *s= new  SymbolInfo(yytext, (char *)"CHAR");
    yylval.symbol_info = s;
	s->leaf = 1;
	s->start=s->end=line_count;
	s->message = "CHAR : char";
	fout<<"Line# "<<line_count<<": Token <CHAR> Lexeme "<<yytext<<" found"<<endl;
	return CHAR;}
"return" {
    SymbolInfo *s= new  SymbolInfo(yytext, (char *)"RETURN");
    yylval.symbol_info = s;
	s->leaf = 1;
	s->start=s->end=line_count;
	s->message = "RETURN : return";
	fout<<"Line# "<<line_count<<": Token <RETURN> Lexeme "<<yytext<<" found"<<endl;
	return RETURN;}
"void" {
    SymbolInfo *s= new  SymbolInfo(yytext, (char *)"VOID");
    yylval.symbol_info = s;
	s->leaf = 1;
	s->start=s->end=line_count;
	s->message = "VOID : void";
	fout<<"Line# "<<line_count<<": Token <VOID> Lexeme "<<yytext<<" found"<<endl;
	return VOID;}
"println"	{
    SymbolInfo *s= new  SymbolInfo(yytext, (char *)"PRINTLN");
    yylval.symbol_info = s;
	s->leaf = 1;
	s->start=s->end=line_count;
	s->message = "PRINTLN : println";
	fout<<"Line# "<<line_count<<": Token <PRINTLN> Lexeme "<<yytext<<" found"<<endl;
	return PRINTLN;}

{ADDOP} { 
			SymbolInfo *s= new  SymbolInfo(yytext, (char *)"ADDOP");
			yylval.symbol_info = s;
			s->leaf = 1;
			s->start=s->end=line_count;
			s->message = "ADDOP : "+(string)yytext;
			fout<<"Line# "<<line_count<<": Token <ADDOP> Lexeme "<<yytext<<" found"<<endl;
			return ADDOP;
		}

{MULOP}	{
			SymbolInfo *s= new  SymbolInfo(yytext, (char *)"MULOP");
			yylval.symbol_info = s;
			s->leaf = 1;
			s->start=s->end=line_count;
			s->message = "MULOP : "+(string)yytext;
			fout<<"Line# "<<line_count<<": Token <MULOP> Lexeme "<<yytext<<" found"<<endl;
			return MULOP;
		}


"=" 	{

    SymbolInfo *s= new  SymbolInfo(yytext, (char *)"ASSIGNOP");
    yylval.symbol_info = s;
	s->leaf = 1;
	s->start=s->end=line_count;
	s->message = "ASSIGNOP : =";
	fout<<"Line# "<<line_count<<": Token <ASSIGNOP> Lexeme "<<yytext<<" found"<<endl;
	return ASSIGNOP;}

">" |
"<" |
">=" |
"<=" |
"==" |
"!=" {
		SymbolInfo *s= new  SymbolInfo(yytext, (char *)"RELOP");
		yylval.symbol_info = s;
		s->leaf = 1;
		s->start=s->end=line_count;
		s->message = "RELOP : "+(string)yytext;
		fout<<"Line# "<<line_count<<": Token <RELOP> Lexeme "<<yytext<<" found"<<endl;
		return RELOP;
	}

"&&"	|
"||"	{
			SymbolInfo *s= new  SymbolInfo(yytext, (char *)"LOGICOP");
			yylval.symbol_info = s;
			s->leaf = 1;
			s->start=s->end=line_count;
			s->message = "LOGICOP : "+(string)yytext;
			fout<<"Line# "<<line_count<<": Token <LOGICOP> Lexeme "<<yytext<<" found"<<endl;
			return LOGICOP;
		}
"!"		{	
            SymbolInfo *s= new  SymbolInfo(yytext, (char *)"NOT");
            yylval.symbol_info = s;
			s->leaf = 1;
			s->start=s->end=line_count;
			s->message = "NOT : !";
            fout<<"Line# "<<line_count<<": Token <NOT> Lexeme "<<yytext<<" found"<<endl;
            return NOT;
        }
";" 	{
   SymbolInfo *s= new  SymbolInfo(yytext, (char *)"SEMICOLON");
    yylval.symbol_info = s;  
	s->leaf = 1;
	s->start=s->end=line_count;
	s->message = "SEMICOLON : ;";
	fout<<"Line# "<<line_count<<": Token <SEMICOLON> Lexeme "<<yytext<<" found"<<endl;
	return SEMICOLON;
	}
"," 	{
    SymbolInfo *s= new  SymbolInfo(yytext, (char *)"COMMA");
    yylval.symbol_info = s;
	s->leaf = 1;
	s->start=s->end=line_count;
	s->message = "COMMA : ,";
	fout<<"Line# "<<line_count<<": Token <COMMA> Lexeme "<<yytext<<" found"<<endl;
	return COMMA;
	}
"(" 	{
    SymbolInfo *s= new  SymbolInfo(yytext, (char *)"LPAREN");
    yylval.symbol_info = s;
	s->leaf = 1;
	s->start=s->end=line_count;
	s->message = "LPAREN : (";
	fout<<"Line# "<<line_count<<": Token <LPAREN> Lexeme "<<yytext<<" found"<<endl;
	return LPAREN;
	}
")" 	{
    SymbolInfo *s= new  SymbolInfo(yytext, (char *)"RPAREN");
    yylval.symbol_info = s;
	s->leaf = 1;
	s->start=s->end=line_count;
	s->message = "RPAREN : )";
	fout<<"Line# "<<line_count<<": Token <RPAREN> Lexeme "<<yytext<<" found"<<endl;
	return RPAREN;
	}
"{" 	{
    SymbolInfo *s= new  SymbolInfo(yytext, (char *)"LCURL");
    yylval.symbol_info = s;
	s->leaf = 1;
	s->start=s->end=line_count;
	s->message = "LCURL : {";
	fout<<"Line# "<<line_count<<": Token <LCURL> Lexeme "<<yytext<<" found"<<endl;
	return LCURL;
	}
"}" 	{
    SymbolInfo *s= new  SymbolInfo(yytext, (char *)"RCURL");
    yylval.symbol_info = s;
	s->leaf = 1;
	s->start=s->end=line_count;
	s->message = "RCURL : }";
	fout<<"Line# "<<line_count<<": Token <RCURL> Lexeme "<<yytext<<" found"<<endl;
	return RCURL;
	}
"[" 	{
    SymbolInfo *s= new  SymbolInfo(yytext, (char *)"LSQUARE");
    yylval.symbol_info = s;
	s->leaf = 1;
	s->start=s->end=line_count;
	s->message = "LSQUARE : [";
	fout<<"Line# "<<line_count<<": Token <LSQUARE> Lexeme "<<yytext<<" found"<<endl;
	return LSQUARE;
	}
"]" 	{
	SymbolInfo *s= new  SymbolInfo(yytext, (char *)"RSQUARE");
    yylval.symbol_info = s;
	s->leaf = 1;
	s->start=s->end=line_count;
	s->message = "RSQUARE : ]";
	fout<<"Line# "<<line_count<<": Token <RSQUARE> Lexeme "<<yytext<<" found"<<endl;
	return RSQUARE;
	}
"++" 	{
	SymbolInfo *s= new  SymbolInfo(yytext, (char *)"INCOP");
    yylval.symbol_info = s;
	s->leaf = 1;
	s->start=s->end=line_count;
	s->message = "INCOP : ++";
	fout<<"Line# "<<line_count<<": Token <INCOP> Lexeme "<<yytext<<" found"<<endl;
	return INCOP;
	}
"--" 	{
	SymbolInfo *s= new  SymbolInfo(yytext, (char *)"DECOP");
    yylval.symbol_info = s;
	s->leaf = 1;
	s->start=s->end=line_count;
	s->message = "DECOP : --";
	fout<<"Line# "<<line_count<<": Token <DECOP> Lexeme "<<yytext<<" found"<<endl;
	return DECOP;
	}



{integer}	{
				SymbolInfo *s= new  SymbolInfo(yytext, (char *)"CONST_INT");
				yylval.symbol_info = s;
				s->leaf = 1;
				s->start=s->end=line_count;
				s->message = "CONST_INT : "+s->getName();
				fout<<"Line# "<<line_count<<": Token <CONST_INT> Lexeme "<<yytext<<" found"<<endl;
				return CONST_INT;
			}
{number} 	{	
				SymbolInfo *s= new  SymbolInfo(yytext, (char *)"CONST_FLOAT");
				yylval.symbol_info = s;
				s->leaf = 1;
				s->start=s->end=line_count;
				s->message = "CONST_FLOAT : "+s->getName();
				fout<<"Line# "<<line_count<<": Token <CONST_FLOAT> Lexeme "<<yytext<<" found"<<endl;
				return CONST_FLOAT; 
			}
{id} 		{	 			
			    SymbolInfo* s= new SymbolInfo(yytext, (char *)"ID");
				yylval.symbol_info = s;
				s->leaf = 1;
				s->start=s->end=line_count;
				s->message = "ID : "+s->getName();
				fout<<"Line# "<<line_count<<": Token <ID> Lexeme "<<yytext<<" found"<<endl;			
				return ID;
			}


%%

int yywrap(void)
{
	return 1;
}






