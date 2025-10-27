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
                if(!is_present(a[i][2])){
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



/*
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX 20

char production[MAX][MAX];
char firstSet[MAX][MAX];
char followSet[MAX][MAX];
char nonTerminals[MAX];
int n; // number of productions

int isPresent(char *set, char c) {
    for (int i = 0; set[i]; i++)
        if (set[i] == c) return 1;
    return 0;
}

void addToSet(char *set, char c) {
    if (!isPresent(set, c)) {
        int len = strlen(set);
        set[len] = c;
        set[len + 1] = '\0';
    }
}

void findFirst(char symbol, char *first);
void findFollow(char symbol, char *follow);

void findFirst(char symbol, char *first) {
    if (!isupper(symbol)) { // terminal
        addToSet(first, symbol);
        return;
    }

    for (int i = 0; i < n; i++) {
        if (production[i][0] == symbol) {
            int j = 2; // RHS starts at index 2 (e.g., A=XYZ)
            if (production[i][j] == '$') // epsilon
                addToSet(first, '$');

            while (production[i][j] != '\0') {
                char next = production[i][j];
                if (next == '$') {
                    addToSet(first, '$');
                    break;
                } else if (!isupper(next)) {
                    addToSet(first, next);
                    break;
                } else {
                    char temp[MAX] = "";
                    findFirst(next, temp);

                    int hasEps = 0;
                    for (int k = 0; temp[k]; k++) {
                        if (temp[k] == '$') hasEps = 1;
                        else addToSet(first, temp[k]);
                    }

                    if (!hasEps) break;
                    else j++;
                }
            }
        }
    }
}

void findFollow(char symbol, char *follow) {
    if (production[0][0] == symbol)
        addToSet(follow, '$'); // add $ for start symbol

    for (int i = 0; i < n; i++) {
        for (int j = 2; production[i][j] != '\0'; j++) {
            if (production[i][j] == symbol) {
                char next = production[i][j + 1];
                if (next != '\0') {
                    char temp[MAX] = "";
                    findFirst(next, temp);
                    int hasEps = 0;
                    for (int k = 0; temp[k]; k++) {
                        if (temp[k] == '$') hasEps = 1;
                        else addToSet(follow, temp[k]);
                    }
                    if (hasEps)
                        findFollow(production[i][0], follow);
                } else if (production[i][j + 1] == '\0' && symbol != production[i][0]) {
                    findFollow(production[i][0], follow);
                }
            }
        }
    }
}

int main() {
    printf("Enter number of productions: ");
    scanf("%d", &n);
    printf("Enter the productions (use $ for epsilon):\n");

    for (int i = 0; i < n; i++) {
        char input[MAX];
        scanf("%s", input);

        // Split multiple alternatives like A=aB|b into separate productions
        char lhs = input[0];
        char *rhs = strchr(input, '=') + 1;
        char *alt = strtok(rhs, "|");
        while (alt) {
            sprintf(production[i++], "%c=%s", lhs, alt);
            alt = strtok(NULL, "|");
            if (i >= n) break;
        }
        i--; // adjust since loop increments
    }

    printf("\n--- FIRST and FOLLOW sets ---\n");
    for (int i = 0; i < n; i++) {
        char nt = production[i][0];

        // Skip duplicate non-terminals
        int done = 0;
        for (int k = 0; k < i; k++)
            if (production[k][0] == nt)
                done = 1;
        if (done) continue;

        char first[MAX] = "";
        char follow[MAX] = "";
        findFirst(nt, first);
        findFollow(nt, follow);

        printf("FIRST(%c) = { ", nt);
        for (int j = 0; first[j]; j++)
            printf("%c ", first[j]);
        printf("}\n");

        printf("FOLLOW(%c) = { ", nt);
        for (int j = 0; follow[j]; j++)
            printf("%c ", follow[j]);
        printf("}\n\n");
    }

    return 0;
}



*/