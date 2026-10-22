#include<stdio.h>
#include<math.h>
int main(){
    int sensor;
    int hours;
    float h_ave=0;
    int high_s=0;

    printf("enter number of sensor : ");
    scanf("%d", &sensor);
    printf("\nenter number of hour : ");
    scanf("%d", &hours);
     int temperature[sensor][hours];

    //int function
     printf("\nenter temperature for each hour");
    for(int i = 0;i<sensor;i++){
        for(int j=0;j<hours;j++){
             printf("\n enter temperature for sensor(%d) and hour(%d) : ", i+1, j+1);
             scanf("%d", &temperature[i][j]);

        }
    }
    //analysis
     for(int i = 0;i<sensor;i++){
        printf("\n");
        int total_temp=0;
        float average;
        int max=temperature[i][0];int min=temperature[i][0];
        int critical=0;
        int warning=0;
        int peak=0;
        for(int j=0;j<hours;j++){
            total_temp = total_temp+temperature[i][j];
            if(temperature[i][j]>=max)max =temperature[i][j];
            if(temperature[i][j]<min)min =temperature[i][j];
            if(temperature[i][j]>=40)critical++;
            if(temperature[i][j]>34 && temperature[i][j]<40)warning++;
            if(temperature[i][j]>=35)peak++;
        }
        average = (float)total_temp/hours;
        printf("S%d:  ", i+1);
        printf("total  = %d  ",total_temp);
        printf("average = %.2f   ",average);
        printf(" min = %d   ",min);
        printf("max = %d   \n",max);
        printf("critical = %d   ",critical);
        printf("warning = %d   ",warning);
        printf("longest peak= %d   ",peak);
        if(h_ave>=average ||high_s==0){
           h_ave= h_ave+average;
           high_s++;
        }
    }
    printf("highest average: sensor %d (%.2f)",high_s,h_ave);

    return 0;
}