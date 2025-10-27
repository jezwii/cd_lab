%{
    #include<stdio.h>
    int yylex(void);
    int yyerror(const char* c); 
%}

%token FOR ID NUM ASSIGN RELOP INCDEC

%%
stmnt:
    FOR '(' assign_exp ';' condn ';' assign_exp ')' '{' '}'  {printf("Valid for syntax");}
    ;
assign_exp:
    ID INCDEC
    |ID ASSIGN ID
    |ID ASSIGN NUM
    ;

condn:
    ID RELOP ID
    |ID RELOP NUM
    ;
%%

int yyerror(const char *c){
    fprintf(stderr,"Error: %s",c);
    return 0;
}

int main(){
    printf("Enter an expression: ");
    yyparse();
    return 0;
}




