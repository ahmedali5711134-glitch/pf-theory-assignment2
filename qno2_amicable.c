#include<stdio.h>
int main(){
    int n,a,b,i,suma,sumb,count=0;
    printf("enter your number : ");
    scanf("%d", &n);
    for(a=2;a<n;a++){
        suma=0;
        for(i=1;i<=a/2;i++){
            if(a%i==0){
                suma +=i;
            }
            
        }
        b=suma;
        if(b<a && b<n){
            sumb=0;
            for(i=1;i<=b/2;i++){
                if(b%i==0)sumb+=i;
                
            }
            if(sumb==a){printf("(%d,%d)\n",a,b);
            count++;}
        }
    }
     if(count==0)printf("no amicible number\n");
        else("total emicible number are:%d", count);








    return 0;
}