#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "admin.route.h"
#include "user.route.h"

void SpecificDayIn7Days();
void SpecificWeekInMonth();
void printSingleProduct(UserPOS Product);
void CalculateDay(time_t *lastTime, time_t *lastLastTime, time_t *selectDate);
void CalculateMonth(char target[]);

void SelectPointOfSales(){
    int choice;
    fflush(stdin);
    purple();
    printf("\n\nHey Admin! What you want to do here");
    reset();
    printf("\n(1) See Some Specific Days In 7 Days");
    printf("\n(2) See Some Week In Month");
    // printf("\n(3) Back To Admin Dashboard");
    printf("\n(3) Exit");
    printf("\n\nYour choice\t:\t");
    yellow();
    if(scanf("%d",&choice) != 1) {
        system("clear");
        reset();
        printf("Please Enter Correct Type\n");
        SelectPointOfSales();
        return;
    }
    reset();

    switch (choice){
    case 1:
        SpecificDayIn7Days();
        break;

    case 2:
        SpecificWeekInMonth();
        break;

    case 3:
        printf("\n\t\t Bye Bye :)\n\n");
        exit(0);
        break;

    default:
        printf("Please Select A Correct Choice");
        SelectPointOfSales();
        break;
    }

}

void SpecificWeekInMonth(){

    FILE *fp;
    fp = fopen("database/UserPos.csv","r");    
    char line[1000];
    char *sp;

    int size = 0;

    UserPOS tempProduct[1000];


    while (fgets(line, 1000, fp) != NULL){

        sp = strtok(line, ",");
        strcpy(tempProduct[size].cartOwner, sp);
        // printf("%s\n",tempProduct[size].cartOwner);;

        sp = strtok(NULL, ",");
        strcpy(tempProduct[size].productName, sp);

        sp = strtok(NULL, ",");
        tempProduct[size].singlePriceProduct = atoi(sp);

        sp = strtok(NULL, ",");
        tempProduct[size].totalInCart = atoi(sp);

        
        sp = strtok(NULL, ",");
        tempProduct[size].totalCost = atoi(sp);
        
        sp = strtok(NULL, ",");
        int tempTime = atoi(sp);
        tempProduct[size].timeStamp = (time_t) tempTime;

        size++;

    }
   
    char target[50];

    CalculateMonth(target);
    int counter = 0;

    for (int i = 0; i < size; i++){

        char tempTime[50];
        strcpy(tempTime, ctime(&tempProduct[i].timeStamp));
        tempTime[7] = '\0';
        char result[50] = {tempTime[4], tempTime[5], tempTime[6],'\0'};

        // printf("THIS IS target %s\n",target);
        // printf("THIS IS Result %s\n",result);
        // printf("THIS IS compare %d\n\n\n",strcmp(tempTime, result));
        if(strcmp(target, result) == 0){
         
            printSingleProduct(tempProduct[i]);
            counter++;

        }
        // printSingleProduct(tempProduct[i]);

        // if(tempProduct[i].timeStamp > lastTime && tempProduct[i].timeStamp < lastLastTime){

            // printSingleProduct(tempProduct[i]);
            // counter++;
            
        // }

    }

    // SelectPointOfSales();
    return;
    
    // printf("There Are :\t %d Transection In %.10s To",counter, ctime(&lastTime));
    // printf("%.10s\n", ctime(&lastLastTime));

}

void CalculateMonth(char target[]){

    printf("------------- What Month Point Of Sales Do You Want -------------\n");
    printf("(1) %s\n","January");
    printf("(2) %s\n","February");
    printf("(3) %s\n","March");
    printf("(4) %s\n","April");
    printf("(5) %s\n","May");
    printf("(6) %s\n","June");
    printf("(7) %s\n","July");
    printf("(8) %s\n","August");
    printf("(9) %s\n","September");
    printf("(10) %s\n","October");
    printf("(11) %s\n","November");
    printf("(12) %s\n","December");
    int choice;
    printf("Your Input :\t");
    yellow();
    scanf("%d",&choice);
    reset();
    switch (choice){
    case 1:
        strcpy(target,"Jan");
        break;
    
    case 2:
        strcpy(target,"Feb");
        break;

    case 3:
        strcpy(target,"Mar");
        break;

    case 4:
        strcpy(target,"Apr");
        break;

    case 5:
        strcpy(target,"May");
        break;
    case 6:
        strcpy(target,"Jun");
        break;
    case 7:
        strcpy(target,"Jul");
        break;
    case 8:
        strcpy(target,"Aug");
        break;
    case 9:
        strcpy(target,"Sep");
        break;
    case 10:
        strcpy(target,"Oct");
        break;
    case 11:
        strcpy(target,"Nov");
        break;
    case 12:
        strcpy(target,"Dec");
        break;
    
    default:
        system("clear");
        printf("Please Enter A Correct Choice\n");
        CalculateMonth(target);
        return;
        break;
    }

}


void SpecificDayIn7Days(){

    FILE *fp;
    fp = fopen("database/UserPos.csv","r");    
    char line[1000];
    char *sp;

    int size = 0;

    UserPOS tempProduct[1000];


    while (fgets(line, 1000, fp) != NULL){

        sp = strtok(line, ",");
        strcpy(tempProduct[size].cartOwner, sp);
        // printf("%s\n",tempProduct[size].cartOwner);;

        sp = strtok(NULL, ",");
        strcpy(tempProduct[size].productName, sp);

        sp = strtok(NULL, ",");
        tempProduct[size].singlePriceProduct = atoi(sp);

        sp = strtok(NULL, ",");
        tempProduct[size].totalInCart = atoi(sp);

        
        sp = strtok(NULL, ",");
        tempProduct[size].totalCost = atoi(sp);
        
        sp = strtok(NULL, ",");
        int tempTime = atoi(sp);
        tempProduct[size].timeStamp = (time_t) tempTime;

        size++;

    }

    time_t selectDate;
    time_t lastTime = time(NULL);
    time_t lastLastTime = time(NULL);

    CalculateDay(&lastLastTime, &lastTime, &selectDate);    
    
    int counter = 0;
    // printf("Last Time :\t%s\n",ctime(&lastTime));
    // printf("Last last Time :\t%s\n",ctime(&lastLastTime));
    char last[50];
    strcpy(last, ctime(&selectDate));
    last[11] = '\0';


    for (int i = 0; i < size; i++){

        if(tempProduct[i].timeStamp > lastTime && tempProduct[i].timeStamp < lastLastTime){
            
            printSingleProduct(tempProduct[i]);
            counter++;

        }
        
    }
    
    printf("There Are :\t %d Transection In %.10s\n",counter, ctime(&selectDate));
    // SelectPointOfSales();
    return;
}

void CalculateDay(time_t *lastLastTime, time_t *lastTime, time_t *selectDate){

    int choice;
    int day = 24*60*60;
    time_t now = time(NULL);
    struct tm *now_tm;  
    int hour;
    int minute;
    int second;
    now_tm = localtime(&now);
    hour = now_tm->tm_hour;
    minute = now_tm->tm_min;
    second = now_tm->tm_sec;
    
    // time_t day1 = now - ((day) + (hour*60*60) + (minute*60) +  (second)); 
    // time_t day2 = now - ((day) + (hour*60*60) + (minute*60) +  (second)) + (almost24Hour*2); 
    // time_t day3 = now - ((day) + (hour*60*60) + (minute*60) +  (second)) + (almost24Hour*3); 
    // time_t day4 = now - ((day) + (hour*60*60) + (minute*60) +  (second)) + (almost24Hour*4); 
    // time_t day5 = now - ((day) + (hour*60*60) + (minute*60) +  (second)) + (almost24Hour*5); 
    // time_t day6 = now - ((day) + (hour*60*60) + (minute*60) +  (second)) + (almost24Hour*6); 
    // time_t day7 = now - ((day) + (hour*60*60) + (minute*60) +  (second)) + (almost24Hour*7); 
    // time_t day8 = now - ((day) + (hour*60*60) + (minute*60) +  (second)) + (almost24Hour*8); 
    time_t day1 = now; 
    time_t day2 = now - (day*1); 
    time_t day3 = now - (day*2); 
    time_t day4 = now - (day*3); 
    time_t day5 = now - (day*4); 
    time_t day6 = now - (day*5); 
    time_t day7 = now - (day*6); 
    // printf("%d\n",size);

    int almost24Hour = 86399;
    printf("------------- What Date Point Of Sales Do You Want -------------\n");
    printf("(1) %.10s\n",ctime(&day1));
    printf("(2) %.10s\n",ctime(&day2));
    printf("(3) %.10s\n",ctime(&day3));
    printf("(4) %.10s\n",ctime(&day4));
    printf("(5) %.10s\n",ctime(&day5));
    printf("(6) %.10s\n",ctime(&day6));
    printf("(7) %.10s\n",ctime(&day7));
    
    printf("Your Input :\t");    
    yellow();
    scanf("%d",&choice);
    reset();
    switch (choice){
    case 1:
        *lastLastTime =  now; 
        *lastTime = now - ((hour*60*60) + (minute*60) +  (second)); 
        // *lastTime =  now - ((day) + (hour*60*60) + (minute*60) +  (second));   
        *selectDate = day1; 
        break;
    case 2:
        *lastLastTime =  now - ((hour*60*60) + (minute*60) +  (second)) - 1; 
        *lastTime =  now - ((day) + (hour*60*60) + (minute*60) +  (second));   
        // *lastLastTime =  now - ((day) + (hour*60*60) + (minute*60) +  (second)) - 1;    
        // *lastTime =  now - ((day*2) + (hour*60*60) + (minute*60) +  (second)) ;   
        *selectDate = day2; 
        break;
    case 3:
        *lastLastTime =  now - ((day) + (hour*60*60) + (minute*60) +  (second)) - 1; 
        *lastTime =  now - ((day*2) + (hour*60*60) + (minute*60) +  (second));   
       
        *selectDate = day3; 
        break;
    case 4:
        *lastLastTime =  now - ((day*2) + (hour*60*60) + (minute*60) +  (second)) - 1; 
        *lastTime =  now - ((day*3) + (hour*60*60) + (minute*60) +  (second));   
        
        *selectDate = day4; 
        break;
    case 5:
        *lastLastTime =  now - ((day*3) + (hour*60*60) + (minute*60) +  (second)) - 1; 
        *lastTime =  now - ((day*4) + (hour*60*60) + (minute*60) +  (second));   
        
        *selectDate = day5; 
        break;
    case 6:
        *lastLastTime =  now - ((day*4) + (hour*60*60) + (minute*60) +  (second)) - 1; 
        *lastTime =  now - ((day*5) + (hour*60*60) + (minute*60) +  (second));   
        
          
        *selectDate = day6; 
        break;
    case 7:
        *lastLastTime =  now - ((day*5) + (hour*60*60) + (minute*60) +  (second)) - 1; 
        *lastTime =  now - ((day*6) + (hour*60*60) + (minute*60) +  (second));   
        
        // *lastLastTime =  now - ((day*6) + (hour*60*60) + (minute*60) +  (second)) - 1;    
        // *lastTime =  now - ((day*7) + (hour*60*60) + (minute*60) +  (second)) ;   
        *selectDate = day7; 
        break;
    
    default:
        system("clear");
        printf("Please Enter A Correct Choice\n");
        CalculateDay(lastLastTime, lastTime, selectDate);
        return;
        break;
    }
    
}


void printSingleProduct(UserPOS Product){

    printf("\tCart Owner                  :\t%s\n", Product.cartOwner);
    printf("\tProduct Name                :\t%s\n", Product.productName);
    printf("\tSingle Price Product        :\t%d\n", Product.singlePriceProduct);
    printf("\tTotal In Cart               :\t%d\n", Product.totalInCart);
    printf("\tTotal Cost                  :\t%d\n", Product.totalCost);
    printf("\tTime Stamps                 :\t%s\n", ctime(&Product.timeStamp));

}