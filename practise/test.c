//first and follow

#include<stdio.h>
#include<string.h>
#include<ctype.h>

int n,m;
char a[10][10],f[10];

void first(char c);
void follow(char c);

int is_present(char c){
    for(int i=0;i<m;i++){
        if(f[i] == c){
            return 1;
        }
    }
    return 0;
}

int main(){
    printf("enter no of productions\n");
    scanf("%d",&n);

    printf("enter the production rules (use $ for epsilon)\n");
    for(int i=0 ; i<n ; i++){
        scanf("%s",a[i]);
    }

    //finding non terminal
    for(int k =0 ; k < n ; k++){
        char nt = a[k][0];

        //first
        m=0 ;
        strcpy(f,"");
        first(nt);
        printf("First(%c) : { ",nt);
        for(int i =0 ; i< m ; i++){
            printf("%c ",f[i]);
        }
        printf("}\n");

        //follow
        m=0;
        strcpy(f,"");
        follow(nt);
        printf("Follow(%c) : { ",nt);
        for(int i= 0 ; i< m ; i++){
            printf("%c ",f[i]);
        }
        printf("}\n");
    }
    return 0 ;
}

void first(char c){
    for(int k = 0 ; k < n;k++){
        if(a[k][0] == c){
            if(!isupper(a[k][2])){
                if(!is_present(a[k][2])){
                    f[m++] = a[k][2];
                }
            }
            else{
                first(a[k][2]);
            }
        }
    }
}

