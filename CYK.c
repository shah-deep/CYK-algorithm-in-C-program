#include <stdio.h>
#include <string.h>
#include <stdbool.h>

bool checkNTR(char ch){
    char big[] = {'S','A','B','C','D','E','F','G','H'};
    for(int i=0; i<strlen(big); i++){
        if(ch==big[i])
            return true;
    }
    return false;
}

bool checkTR(char ch){
    char small[] = {'a','b','c','d','e'};
    for(int i=0; i<strlen(small); i++){
        if(ch==small[i])
            return true;
    }
    return false;
}

bool checkPR(char ch[]){
        if(strlen(ch)==1){
            if(checkTR(ch[0])){
                return true;
            }
        } else if(strlen(ch)==2){
            if(checkNTR(ch[0]) && checkNTR(ch[1])){
               return true;
            }
        }
    return false;
}

bool checkEle(char El[], char ch){
    for(int i=0; i<strlen(El); i++){
        if(ch==El[i]){
            return true;
        }
    }
    return false;
}

int main(){

    printf("DEMO Input for Production : S->AB, S->e, A->a, B->b :\n\n");
    printf("No. of production rules = 4\n\nEnter generating symbols:\n\nSymbol  Count\nS 2\nA 1\nB 1\n\nEnter Production rules :\n\nNon- Terminal   -->   Production\nS --> AB\nS --> e\nA --> a\nB --> b\n\n\n");


    int n_pr=0, n_pr2=0, pr_cnt=0;

    printf("Allowed Symbols: 'S','A','B','C','D','E','F','G','H' \n");
    printf("Allowed terminals: 'a','b','c','d' and 'e':epsilon/lambda\n");
    printf("\n\nNo. of production rules = ");
    scanf("%d",&n_pr);
    char ntr[n_pr], pr[n_pr][3];
    int ntr_cnt[n_pr];

    printf("\nEnter generating symbols:\n\nSymbol  Count\n");
    fflush(stdin);
    int i1=0;
    while(n_pr2<n_pr){
        scanf("%c %d",&ntr[i1],&ntr_cnt[i1]);
        fflush(stdin);

        if(!checkNTR(ntr[i1])){
          printf("Invalid Input. Please choose from 'Allowed Symbols' and try again.\n\nExiting...\n");
          return -1;
        }
        n_pr2 += ntr_cnt[i1];
        i1++;
    }

    if(n_pr != n_pr2){
        printf("Invalid Input for 'No. of production rules'. Please try again.\n\nExiting...\n");
        return -1;
    }

    printf("\n\nEnter Production rules : \n");
    printf("\nNon- Terminal   -->   Production\n");
    fflush(stdin);
    for(int i=0; i<i1; i++){
        for(int j=0; j<ntr_cnt[i]; j++) {
            printf("%c --> ",ntr[i]);
            pr_cnt += (i+j);
            fflush(stdin);
            pr[pr_cnt][1]=pr[pr_cnt][2]='\0';
            gets(pr[pr_cnt]);
            fflush(stdin);
            if(!checkPR(pr[pr_cnt])){
               printf("Invalid Input. Please write correct CNF and try again.\n\nExiting...\n");
               return -1;
            }
        }
    }

     pr_cnt = 0;
     for(int i=0; i<i1; i++){
        for(int j=0; j<ntr_cnt[i]; j++) {
            pr_cnt += (i+j);
            printf("\n%c --> %s",ntr[i],pr[pr_cnt]);
        }
    }

    fflush(stdin);
    int n=0;
    printf("\n\nInput String: ");
    char s1[10];
    gets(s1);
    fflush(stdin);
    n = strlen(s1);
    char st[n];
    strcpy(st,s1);
    char tb[n][n][10]; // Table

    if(n==0){
        printf("Empty String!\n");
        return -1;
    }


    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            for(int k=0; k<10; k++)
                tb[i][j][k]='\0';
        }
    }

    for(int i=0;i<n;i++){
        pr_cnt = 0;
        int  k2 = 0;
         for(int i2=0; i2<i1; i2++){
            for(int j2=0; j2<ntr_cnt[i2]; j2++) {
                pr_cnt += (i2+j2);
                if(checkTR(pr[pr_cnt][0]) && pr[pr_cnt][0]==st[i]){
                    tb[i][i][k2]=ntr[i2];
                    k2+=1;
                }
            }
        }
    }

    for(int l=1; l<=(n-1); l++){
        for(int i=0, j=0; i<=(n-l-1); i++){
            j = i+l;

          for(int k=i; k<=(j-1); k++){
              pr_cnt = 0;
              int k2 = 0;

              for(int i2=0; i2<i1; i2++){
                 for(int j2=0; j2<ntr_cnt[i2]; j2++) {

                    pr_cnt += (i2+j2);
                    if(checkNTR(pr[pr_cnt][0])){
                        if(checkEle(tb[i][k],pr[pr_cnt][0]) && checkEle(tb[k+1][j],pr[pr_cnt][1])){
                            tb[i][j][k2]=ntr[i2];
                            k2+=1;
                        }
                    }
                }
             }
           }
        }
    }


printf("\n\n\nTable:\n\n");

    for(int i=0; i<n; i++){
            printf("|");
        for(int j=0; j<n; j++){
            printf("%s |",tb[i][j]);
        }
        printf("\n");
    }

    if(checkEle(tb[0][n-1],'S')){
        printf("\n\nThis String is Accepted!\n\n");
    } else{
        printf("\n\nThis String is Rejected!\n\n");
    }

    return 0;
}
