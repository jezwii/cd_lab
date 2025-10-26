#include<stdio.h>
#include<string.h>
#include<ctype.h>
#define MAX_TOKEN 100

char* keyword[] = {"int","if","for","else","while","float","return","printf"};
int num_keyword = 8;

int is_keyword(char str[]){
    for(int i = 0; i< num_keyword;i++){
        if(strcmp(str,keyword[i])==0){
            return 1;
        }
    }
    return 0;
}

int main(){
    FILE* fp = fopen("input.c","r");
    if(!fp){
        printf("cannot open file\n");
        return 1;
    }

    char token[MAX_TOKEN];
    char c;
    int index = 0;

    while((c=fgetc(fp)) != EOF){
            //ignoreing charecters
            if(c == ' ' || c == '\t' || c == '\n'){
                continue;
            }

            //identifiers and keyword

            if(isalpha(c)){
                index = 0 ;
                token[index++] = c;

                while(isalnum(c=fgetc(fp))){
                    token[index++] = c;
                }

                token[index] = '\0';
                fseek(fp,-1,SEEK_CUR);

                if(is_keyword(token) == 1){
                    printf("Keyword: %s\n",token);
                }
                else{
                    printf("Identifier: %s\n",token);
                }
            }
            else if(isdigit(c)){
                index = 0 ;
                token[index++] = c;

                while(isdigit(c=fgetc(fp))){
                    token[index++] = c;
                }
                token[index]  = '\0';
                fseek(fp,-1,SEEK_CUR);

                printf("Number: %s\n",token);
            }
            else{
                switch (c)
                {
                case '*':case '-': case '+':case '/':case '<':case '>':case '=':
                printf("Operators: %c\n",c);
                break;

                case '(': case ')' : case '{': case '}': case ',': case ';':
                printf("Delimiters: %c\n",c);
                break;

                default:
                    printf("Unknown: %c",c);
                    break;
                }
            }


    }

    fclose(fp);
    return 0;

}