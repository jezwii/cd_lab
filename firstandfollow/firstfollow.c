#include<stdio.h>
#include<string.h>
#include<ctype.h>

int m,n;
char a[10][10] , f[10];

void first(char c);
void follow(char c);

int is_present(char c){
    for(int i=0; i<m; i++){
        if(c == f[i]){
            return 1;
        }
    }
    return 0;
}


int main(){
    printf("Enter the no of production rules\n");
    scanf("%d",&n);

    printf("Enter the production rules: (use $ for epsilon)\n");
    for(int i=0; i<n; i++){
        scanf("%s",a[i]);
    }


    for(int k=0; k<n; k++){
        //finding the non terminal
        char nt = a[k][0];

        //finding the first

        m = 0 ;
        strcpy(f,""); //resetting the buffer
        first(nt);
        printf("First(%c) = { ",nt);
        for(int i = 0 ; i < m ; i++){
            printf("%c ",f[i]);
        }
        printf("}\n");

        //finding the follow

        m=0;
        strcpy(f,"");
        follow(nt);
        printf("Follow(%c) = { ",nt);
        for(int i=0 ;i<m ; i++){
            printf("%c ",f[i]);
        }
        printf("}\n");

    }

    return 0;
}

void first(char c){

    for(int i = 0 ; i < n ; i++){
        if(a[i][0] == c){
            if(!isupper(a[i][2])) // first is a terminal
            {
                if(!is_present(c)){
                    f[m++] = a[i][2];
                }
            }
            else{
                first(a[i][2]);
            }
        }
    }
}

void follow(char c){
    // check if c is a start symbol
    if(a[0][0] == c){
        if(!is_present('$')){
            f[m++] = '$';
        }
    }

    for(int i =0 ; i< n;i++){
        for(int j =2 ; j < strlen(a[i]) ; j++){
            if(a[i][j] == c){
                //check if follow exist
                if(a[i][j+1] != '\0'){

                    if(!isupper(a[i][j+1])){
                        if(!is_present(a[i][j+1])){
                            f[m++] = a[i][j+1];
                        }
                    }
                    else{
                        first(a[i][j+1]);
                    }
                }
                if(a[i][j+1] == '\0' && c != a[i][0]){
                    follow(a[i][0]);
                }
            }
        }
    }
}