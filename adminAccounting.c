#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "admin.route.h"
#include "user.route.h"

void SeeAllProfit();
void CalculateWeekAccounting(time_t *lastTime, time_t *lastLastTime, time_t *selectDate);
void DeleteDuplicate(ProductPOS product[], int *size);
void ProfitByProductName();
void ProfitTimeRange();
void SortProduct(ProductPOS product[], int size);
void CalculateMonthAccounting(char target[], char fullTarget[]);

void SelectAccounting(){

    int choice;
    fflush(stdin);
    purple();
    printf("\n\nHey Admin! What You Want To Do Here?");
    reset();
    printf("\n(1) See All Profit");
    printf("\n(2) Profit Specific Product");
    printf("\n(3) Profit Time Range");
    printf("\n(4) Exit");
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
        // SpecificDayIn7Days();
        SeeAllProfit();
        break;

    case 2:
        ProfitByProductName();
        break;

    case 3:
        ProfitTimeRange();
        break;

    case 4:
        printf("\n\t\t Bye Bye :)\n\n");
        exit(0);
        break;

    default:
        printf("Please Select A Corrent Choice");
        // SelectAccounting();
        break;
    }

}

void SeeAllProfit(){
    FILE *fp;
    fp = fopen("database/UserPos.csv","r");    
    char line[1000];
    char *sp;

    ProductPOS tempProduct[1000];
    int size = 0;

    while (fgets(line, 1000, fp) != NULL){

        sp = strtok(line, ",");
        strcpy(tempProduct[size].ownerName, sp);
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

    fclose(fp);
    
    FILE *fpProduct;
    fpProduct = fopen("database/Product.csv","r");
    Product productData;

    int sumProfit = 0;
    int sumCost = 0;
    int moneyReceive = 0;

    while (fgets(line, 1000, fpProduct) != NULL){

        // printf("\n%s\n",line);
        sp = strtok(line, ",");
        strcpy(productData.productName, sp);
        
        sp = strtok(NULL, ",");
        productData.productPrice = atoi(sp);

        sp = strtok(NULL, ",");
        productData.productQuantity = atoi(sp);
        
        sp = strtok(NULL, ",");
        productData.productCost = atoi(sp);
      
        // sp = strtok(NULL, ",");
        // productData.productProfit = atoi(sp);

        sp = strtok(NULL, ",");
        productData.minimumQuantity = atoi(sp);

        for (int i = 0; i < size; i++){
            if(strcmp(tempProduct[i].productName, productData.productName) == 0){
                // printf("PRODUCT TOTAL IN CART %d\n",tempProduct[i].totalInCart);
                tempProduct[i].productPrice = productData.productPrice;
                tempProduct[i].productProfit = productData.productPrice - productData.productCost;
                tempProduct[i].productCost = productData.productCost;
                // tempProduct[i].sumProfit = tempProduct[i].totalInCart * productData.productProfit;
                // tempProduct[i].productQuantity = productData.productQuantity;
                // sumProfit += tempProduct[i].sumProfit;
                // sumCost += tempProduct[i].productCost;
                moneyReceive += tempProduct[i].productPrice * tempProduct[i].totalInCart;
                sumProfit += tempProduct[i].productProfit * tempProduct[i].totalInCart;
                sumCost += tempProduct[i].productCost * tempProduct[i].totalInCart;
            }
        }
    }
    printf("\n--------------------------------------------\n");
    printf("\033[0;33mMoney Receieve\033[0m Of All Time  :\t\033[0;33m%d\n", moneyReceive);
    reset();
    printf("\033[0;31mProduct Cost\033[0m Of All Time    :\t\033[0;31m%d\n", sumCost);
    reset();
    printf("\033[0;32mProduct Profit\033[0m Of All Time  :\t\033[0;32m%d\n", sumProfit);
    reset();
    printf("--------------------------------------------\n");

    // SelectAccounting();
    return;
}


void ProfitByProductName(){

    FILE *fp;
    fp = fopen("database/UserPos.csv","r");    
    char line[1000];
    char *sp;

    ProductPOS tempProduct[1000];
    int size = 0;

    while (fgets(line, 1000, fp) != NULL){

        sp = strtok(line, ",");
        strcpy(tempProduct[size].ownerName, sp);
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

    fclose(fp);
    
    FILE *fpProduct;
    fpProduct = fopen("database/Product.csv","r");
    Product productData;

    while (fgets(line, 1000, fpProduct) != NULL){

        // printf("\n%s\n",line);
        sp = strtok(line, ",");
        strcpy(productData.productName, sp);
        
        sp = strtok(NULL, ",");
        productData.productPrice = atoi(sp);

        sp = strtok(NULL, ",");
        productData.productQuantity = atoi(sp);
        
        sp = strtok(NULL, ",");
        productData.productCost = atoi(sp);
      
        // sp = strtok(NULL, ",");
        // productData.productProfit = atoi(sp);

        sp = strtok(NULL, ",");
        productData.minimumQuantity = atoi(sp);

        for (int i = 0; i < size; i++){
            if(strcmp(tempProduct[i].productName, productData.productName) == 0){
                tempProduct[i].productPrice = productData.productPrice;
                tempProduct[i].productCost = productData.productCost;
                tempProduct[i].productProfit = productData.productPrice - productData.productCost;
                tempProduct[i].sumProfit = tempProduct[i].totalInCart * productData.productProfit;
                tempProduct[i].productQuantity = productData.productQuantity;
                // tempProduct[i].singlePriceProduct = productData.productPrice;
            }
        }
    }
  

    DeleteDuplicate(tempProduct, &size);

    SortProduct(tempProduct, size);
    int counter = 1;

    for (int i = 0; i < size; i++){
        if(strcmp(tempProduct[i].productName, "None") != 0){
            printf("------------------------------\n");
            printf("Rank \033[0;35m%d\n",counter);
            reset();
            printf("Product Name    :\t\033[0;34m%s\n",tempProduct[i].productName);
            reset();
            printf("\033[0;33mMoney Receieve\033[0m  :\t\033[0;33m%d\n",tempProduct[i].productPrice * tempProduct[i].totalInCart);
            reset();
            printf("\033[0;31mProduct Cost\033[0m    :\t\033[0;31m%d\n",tempProduct[i].productCost * tempProduct[i].totalInCart);
            reset();
            printf("\033[0;32mProduct Profit\033[0m  :\t\033[0;32m%d\n",tempProduct[i].productProfit * tempProduct[i].totalInCart);
            reset();
            printf("------------------------------\n\n");
            
            
            counter++;
        }
    }
    
    // SelectAccounting();
    return;

}




void DeleteDuplicate(ProductPOS product[], int *size){
    
    for (int i = 0; i < *size; i++) {
        for (int j = 0; j < *size; j++) {
            if(i == j || product[i].productQuantity == 0 || strcmp(product[i].productName, "None") == 0) continue;

            else if(strcmp(product[i].productName, product[j].productName) == 0){
                
                strcpy(product[j].productName, "None");
                product[i].totalInCart += product[j].totalInCart;
                product[i].sumProfit += product[j].sumProfit;
                // product[i].productCost += product[j].productCost;
                product[j].productQuantity = 0;

            }
        }
    }
}


void ProfitTimeRange(){

    FILE *fp;
    fp = fopen("database/UserPos.csv","r");
    char line[1000];
    char *sp;

    ProductPOS tempProduct[1000];
    int size = 0;

    
    while (fgets(line, 1000, fp) != NULL){

        sp = strtok(line, ",");
        strcpy(tempProduct[size].ownerName, sp);
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

    fclose(fp);


    FILE *fpProduct;
    fpProduct = fopen("database/Product.csv","r");
    Product productData;

    while (fgets(line, 1000, fpProduct) != NULL){

        // printf("\n%s\n",line);
        sp = strtok(line, ",");
        strcpy(productData.productName, sp);
        
        sp = strtok(NULL, ",");
        productData.productPrice = atoi(sp);

        sp = strtok(NULL, ",");
        productData.productQuantity = atoi(sp);
        
        sp = strtok(NULL, ",");
        productData.productCost = atoi(sp);
      
        // sp = strtok(NULL, ",");
        // productData.productProfit = atoi(sp);

        sp = strtok(NULL, ",");
        productData.minimumQuantity = atoi(sp);

        for (int i = 0; i < size; i++){
            if(strcmp(tempProduct[i].productName, productData.productName) == 0){
                tempProduct[i].productPrice = productData.productPrice;
                tempProduct[i].productCost = productData.productCost;
                tempProduct[i].productProfit = productData.productPrice - productData.productCost;
                tempProduct[i].sumProfit = tempProduct[i].totalInCart * productData.productProfit;
                tempProduct[i].productQuantity = productData.productQuantity;
                tempProduct[i].singlePriceProduct = productData.productPrice;
            }
        }
    }

    // DeleteDuplicate(tempProduct, &size);

    

    char target[50];
    char fullTarget[50];
    CalculateMonthAccounting(target, fullTarget);

    int sumCost = 0;
    int sumProfit = 0;
    int moneyReceive = 0;

    for (int i = 0; i < size; i++){

        char tempTime[50];
        strcpy(tempTime, ctime(&tempProduct[i].timeStamp));
        tempTime[7] = '\0';
        char result[50] = {tempTime[4],tempTime[5],tempTime[6],'\0'};

        if(strcmp(target,result) == 0 && strcmp(tempProduct[i].productName, "None") != 0){
            
            moneyReceive += tempProduct[i].productPrice * tempProduct[i].totalInCart;
            sumProfit += tempProduct[i].productProfit * tempProduct[i].totalInCart;
            sumCost += tempProduct[i].productCost * tempProduct[i].totalInCart;

            // printf("Product Name    :\t%s\n",tempProduct[i].productName);
            // printf("Money Receive   :\t%d\n",tempProduct[i].productPrice * tempProduct[i].totalInCart);
            // printf("Product Cost    :\t%d\n",tempProduct[i].productCost * tempProduct[i].totalInCart);
            // printf("Product ProFit  :\t%d\n",tempProduct[i].productProfit * tempProduct[i].totalInCart);
            // printf("\n\n");
        }
    }
    printf("\n--------------------------------------------\n");
    printf("Accounting In \033[0;34m%s \n",fullTarget);
    reset();
    printf("\033[0;33mMoney Receieve\033[0m Of All Time  :\t\033[0;33m%d\n", moneyReceive);
    reset();
    printf("\033[0;31mProduct Cost\033[0m Of All Time    :\t\033[0;31m%d\n", sumCost);
    reset();
    printf("\033[0;32mProduct Profit\033[0m Of All Time  :\t\033[0;32m%d\n", sumProfit);
    reset();
    printf("--------------------------------------------\n");


    // SelectAccounting();
    return;
}


void CalculateMonthAccounting(char target[], char fullTarget[]){
    purple();
    printf("What Month Do You Want To See Accounting\n");
    reset();
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
    fflush(stdin);
    printf("\nYour Input :\t");

    int choice;
    yellow();
    scanf("%d",&choice);
    reset();

    switch (choice){
    case 1:
        strcpy(target,"Jan");
        strcpy(fullTarget,"January");
        break;
    
    case 2:
        strcpy(target,"Feb");
        strcpy(fullTarget,"February");
        break;

    case 3:
        strcpy(target,"Mar");
        strcpy(fullTarget,"March");
        break;

    case 4:
        strcpy(target,"Apr");
        strcpy(fullTarget,"April");
        break;

    case 5:
        strcpy(target,"May");
        strcpy(fullTarget,"May");
        break;
    case 6:
        strcpy(target,"Jun");
        strcpy(fullTarget,"June");
        break;
    case 7:
        strcpy(target,"Jul");
        strcpy(fullTarget,"July");
        break;
    case 8:
        strcpy(target,"Aug");
        strcpy(fullTarget,"August");
        break;
    case 9:
        strcpy(target,"Sep");
        strcpy(fullTarget,"September");
        break;
    case 10:
        strcpy(target,"Oct");
        strcpy(fullTarget,"October");
        break;
    case 11:
        strcpy(target,"Nov");
        strcpy(fullTarget,"November");
        break;
    case 12:
        strcpy(target,"Dec");
        strcpy(fullTarget,"December");
        break;
    
    default:
        system("clear");
        printf("Please Enter A Correct Choice\n");
        CalculateMonthAccounting(target, fullTarget);
        return;
        break;
    }
}


void CalculateWeekAccounting(time_t *lastTime, time_t *lastLastTime, time_t *selectDate){

    int miltime = 24*60*60;
    time_t now = time(NULL);
    time_t week1 = now - (miltime); 
    time_t week2 = now - (miltime*7); 
    time_t week3 = now - (miltime*14); 
    time_t week4 = now - (miltime*21); 
    time_t week5 = now - (miltime*28); 
    time_t week6 = now - (miltime*35); 
    // printf("%d\n",size);


    printf("------------- What Week Point Of Sales Do You Want -------------\n");
    printf("(1) %.10s To ",ctime(&week1));
    printf("%.10s\n",ctime(&week2));

    printf("(2) %.10s To ",ctime(&week2));
    printf("%.10s\n",ctime(&week3));

    printf("(3) %.10s To ",ctime(&week3));
    printf("%.10s\n",ctime(&week4));

    printf("(4) %.10s To ",ctime(&week4));
    printf("%.10s\n",ctime(&week5));

    printf("(4) %.10s To ",ctime(&week5));
    printf("%.10s\n",ctime(&week6));

    int choice;
    yellow();
    scanf("%d",&choice);
    reset();
    
    switch (choice){
    case 1:
        *lastTime = week1;    
        *lastLastTime = week2;   
        break;
    
    case 2:
        *lastTime = week2;    
        *lastLastTime = week3;   
        break;

    case 3:
        *lastTime = week3;    
        *lastLastTime = week4;   
        break;

    case 4:
        *lastTime = week4;    
        *lastLastTime = week5;   
        break;

    case 5:
        *lastTime = week5;    
        *lastLastTime = week6;   
        break;
    
    default:
        system("clear");
        printf("Please Enter A Correct Choice\n");
        CalculateWeekAccounting(lastTime, lastLastTime, selectDate);
        return;
        break;
}}


void SortProduct(ProductPOS product[], int size){



    for (int i = 0; i < size-1; i++){
        for (int j = 0; j < size-1-i; j++){
            // int temp = product[j].productProfit * product[j].totalInCart;
            if(product[j].productProfit * product[j].totalInCart < product[j+1].productProfit * product[j+1].totalInCart){
                ProductPOS temp = product[j];
                product[j] = product[j+1];
                product[j+1] = temp;
            }
        }
        
    }
    

}