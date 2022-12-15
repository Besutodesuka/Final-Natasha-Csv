/* 
ไฟล์ที่เกี่ยวกับให้พวกตะกร้าสินค้าของ user ทุกอย่างที่ user ต้องเกี่ยวข้องกับสินค้าจะรวมไว้ที่นี้
1. Print Product ทั้งหมดที่มีให้ user ดู = PrintProductForUser
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "user.route.h"
#include "admin.route.h"

void AddSaveProductCart(UserCart *userCart, User *currentUser, Product *targetProduct);
void PrintUserCartSpecific(char *target, UserCart itemsInCart[], int *itemsCount, int *sumPrice);
void CheckBillSelection(User *currentUser);
void EditItemInCart(User *currentUser);
void RemoveItemInCart(User *currentUser);
void PayBill(User *currentUser);
void SaveUserPos(User *currentUser);
void UpdateUserCart(User *currentUser);
void UpdateStock(User *currentUser);
void SumCutStock(CutStock product[], int size);
void CheckIfProductExistInCart(User *currentUser, UserCart *userCart);
void SaveProductToCart(UserCart *userCart);

void CheckBillSelection(User *currentUser){
    
    int choice;
    purple();
    printf("What you want to do here");
    reset();
    printf("\n(1) Pay Bill");
    printf("\n(2) Edit Item In Cart");
    printf("\n(3) Remove Item In Cart");
    printf("\n(4) Exit");
    printf("\n\nYour choice\t:\t");
    fflush(stdin);
    
    yellow();
    if(scanf("%d",&choice) != 1) {
        reset();
        system("clear");
        printf("Please Enter Correct Type\n");
        CheckBillSelection(currentUser);
        return;
    }

    reset();
    
    switch (choice){
    case 1:
        PayBill(currentUser);
        break;

    case 2:
        EditItemInCart(currentUser);
        break;

    case 3:
        RemoveItemInCart(currentUser);
        break;

    // case 4:
    //     // CheckBill(currentUser);
    //     break;
    
    case 4:
        printf("\n\t\t Bye Bye :)\n\n");
        exit(0);
        break;

    default:
        printf("Please Select A Corrent Choice");
        CheckBillSelection(currentUser);
        break;
    }
}


void PrintProductForUserSelection(User *currentUser){

    Product product;
    FILE *fp;

    fp = fopen("database/Product.csv","r");
    printf("\n----------------  Product Information  ----------------\n");

    int i = 1;
    char line[1000];
    char *sp;

    while (fgets(line, 1000, fp) != NULL){
        // printf("\n%s\n",line);
        printf("\n----------- Product Key : \033[0;32m%d\033[0m -------------\n\n",i);

        sp = strtok(line, ",");
        strcpy(product.productName, sp);
        printf("\tProduct Name                  :\t%s\n", product.productName);
        
        sp = strtok(NULL, ",");
        product.productPrice = atoi(sp);
        printf("\tProduct Price                 :\t%d\n", product.productPrice);

        sp = strtok(NULL, ",");
        product.productQuantity = atoi(sp);
        printf("\tProduct Quantity              :\t%d\n", product.productQuantity);

        printf("\n\n");
        i++;
    }

    fclose(fp); 
    UserSelection(currentUser);
    return;   
}

void PrintProductForUser(User *currentUser){

    Product product;
    FILE *fp;

    fp = fopen("database/Product.csv","r");
    printf("\n----------------  Product Information  ----------------\n");
    int i = 1;
    char line[1000];
    char *sp;

    while (fgets(line, 1000, fp) != NULL){
        // printf("\n%s\n",line);
        printf("\n----------- Product Key : \033[0;32m%d\033[0m -------------\n\n",i);

        sp = strtok(line, ",");
        strcpy(product.productName, sp);
        printf("\tProduct Name                  :\t%s\n", product.productName);
        
        sp = strtok(NULL, ",");
        product.productPrice = atoi(sp);
        printf("\tProduct Price                 :\t%d\n", product.productPrice);

        sp = strtok(NULL, ",");
        product.productQuantity = atoi(sp);
        printf("\tProduct Quantity              :\t%d\n", product.productQuantity);

        printf("\n\n");
        i++;
    }

    fclose(fp); 
    // UserSelection(currentUser);
    return;   
}


void FindProductByProductKey(int *productKey, Product *targetProduct){

    FILE *fp;
    Product product;
    fp = fopen("database/Product.csv","r");

    char line[1000];
    int i = 1;
    char *sp;

    while (fgets(line, 1000, fp) != NULL){
        
        if(i == *productKey){
            
            // Product Name
            sp = strtok(line, ",");
            strcpy(targetProduct->productName, sp);
            
            // Product Price
            sp = strtok(NULL, ",");
            targetProduct->productPrice = atoi(sp);
            
            // Product Quantity
            sp = strtok(NULL, ",");
            targetProduct->productQuantity = atoi(sp);
            *productKey = 0;
            break;   
        }

        i++;
    }   
    return;
}


void AddProductToCart(User *currentUser){

    
    // FILE *fpOpenProduct;
    Product *targetProduct;
    targetProduct = calloc(1, sizeof(Product));

    UserCart *userCart;
    userCart = calloc(1, sizeof(UserCart));

    char continueOrNot = 'y';
    int productKey = 0;

    while (continueOrNot == 'y'){

        printf("Add Product To Your Cart\n");
        PrintProductForUser(currentUser);
        
        printf("Enter Product Key To Add Product To Cart :\t");
        // scanf("%d",&productKey);
        fflush(stdin);
        yellow();
        if(scanf("%d",&productKey) != 1) {
            reset();
            system("clear");
            printf("Please Enter Correct Type\n");
            AddProductToCart(currentUser);
            return;
        }

        reset();

        FindProductByProductKey(&productKey, targetProduct);
        // printf("TARGET PRODUCT %s\n",targetProduct->productName);
        
        if(productKey == 0){
            
            AddSaveProductCart(userCart, currentUser, targetProduct);
            printf("Do You Want To Continue This Process? [y/n]:\t");
            yellow();
            if(scanf("%s",&continueOrNot) != 1) {
                reset();
                system("clear");
                printf("Please Enter Correct Type\n");
                AddProductToCart(currentUser);
                return;
            }
            reset();
        }

        else {
            printf("Do You Want To Continue This Process Or Not [y/n]:\t");
            yellow();
            if(scanf("%s",&continueOrNot) != 1) {
                reset();
                system("clear");
                printf("Please Enter Correct Type\n");
                AddProductToCart(currentUser);
                return;
            }
            reset();

        }

    }

    UserSelection(currentUser);
    return;
}


void AddSaveProductCart(UserCart *userCart, User *currentUser, Product *targetProduct){
    
    FILE *fp;
    strcpy(userCart->cartOwner, currentUser->userName);
    strcpy(userCart->productName, targetProduct->productName);
    userCart->singlePriceProduct = targetProduct->productPrice;
    userCart->timeStamp = time(NULL);
    
    int quantity = 0;
    
    while (quantity == 0){

        printf("We Only have %d Item In Stock\n",targetProduct->productQuantity);
        printf("Please Enter How Many Do You Want To Add In Cart\t:\t");
        yellow();
        if(scanf("%d",&quantity) != 1) {
            reset();
            system("clear");
            printf("Please Enter Correct Type\n");
            AddSaveProductCart(userCart, currentUser, targetProduct);
            return;
        }

        reset();
        if(quantity > targetProduct->productQuantity){
            printf("We Only have %d Item In Stock\n",targetProduct->productQuantity);
            printf("Please Enter Number Of Your Item Again\n");
            AddSaveProductCart(userCart, currentUser, targetProduct);
            return;
        }

    }
    
    int totalCost;
    totalCost = userCart->singlePriceProduct * quantity;
    userCart->totalCost = totalCost;
    userCart->totalInCart = quantity;

    printf("\n---------- Product Detail ----------\n");
    printf("\tCartOwner             :\t%s\n",userCart->cartOwner);
    printf("\tProductName           :\t%s\n",userCart->productName);
    printf("\tSinglePriceProduct    :\t%d\n",userCart->singlePriceProduct);
    printf("\tTimeStamps            :\t%s",ctime(&userCart->timeStamp));
    printf("\tToTalInCart           :\t%d\n",userCart->totalInCart);
    printf("\tToTalCost             :\t%d\n",userCart->totalCost);
    printf("\nConfirm To Add This Product? [y/n]:\t");
    
    char saveProductToCart;
    fflush(stdin);
    yellow();
    scanf("%s",&saveProductToCart);
    reset();
    bool found = false;

    if(saveProductToCart == 'y'){

        CheckIfProductExistInCart(currentUser, userCart);

    }
}

void CheckIfProductExistInCart(User *currentUser, UserCart *userCart){

    FILE *fp, *fpTemp;

    fp = fopen("database/UserCart.csv","r");
    
    if(fp == NULL){
        printf("Error Opening UserCart.csv\n");
        return;
    }

    UserCart tempUserCart[1000];
    int size = 0;
    char line[1000];
    char *sp;
    int i = 0;

    while (fgets(line, 1000, fp) != NULL){
        sp = strtok(line, ",");
        strcpy(tempUserCart[i].cartOwner, sp);

        sp = strtok(NULL, ",");
        strcpy(tempUserCart[i].productName, sp);

        sp = strtok(NULL, ",");
        tempUserCart[i].singlePriceProduct = atoi(sp);

        sp = strtok(NULL, ",");
        tempUserCart[i].totalInCart = atoi(sp);

        sp = strtok(NULL, ",");
        tempUserCart[i].totalCost = atoi(sp);

        sp = strtok(NULL, ",");
        int tempTime = atoi(sp);
        tempUserCart[i].timeStamp = (time_t) tempTime;

        // if(strcmp(tempUserCart[i].cartOwner, userCart->cartOwner) == 0 && strcmp(tempUserCart[i].productName, userCart->cartOwner) == 0){
        //     tempUserCart[i].totalInCart += userCart->totalInCart;
        //     tempUserCart[i].totalCost += userCart->totalCost;
        // }

        // fprintf(fpTemp,
        //     "%s,%s,%d,%d,%d,%d\n",
        //     tempUserCart[i].cartOwner,
        //     tempUserCart[i].productName,
        //     tempUserCart[i].singlePriceProduct,
        //     // strtok(ctime(&userCart.timeStamp),"\n"),
        //     tempUserCart[i].totalInCart,
        //     tempUserCart[i].totalCost,
        //     tempUserCart[i].timeStamp
        // );


        i++;
    }

    fclose(fp);
    // fclose(fpTemp);
    bool found = false;
    for (int j = 0; j < i; j++){
        if(strcmp(tempUserCart[j].cartOwner, userCart->cartOwner) == 0 && strcmp(tempUserCart[j].productName, userCart->productName) == 0){
            tempUserCart[j].totalInCart += userCart->totalInCart;
            tempUserCart[j].totalCost += userCart->totalCost;
            found = true;
            break;
        }
    }
    
    if(found){
        fpTemp = fopen("database/UserCart.csv","w");
        if(fpTemp == NULL){
            printf("Error Opening UserCart.csv\n");
            return;
        }

        for (int j = 0; j < i; j++){
            fprintf(fpTemp,
                "%s,%s,%d,%d,%d,%d\n",
                tempUserCart[j].cartOwner,
                tempUserCart[j].productName,
                tempUserCart[j].singlePriceProduct,
                // strtok(ctime(&userCart.timeStamp),"\n"),
                tempUserCart[j].totalInCart,
                tempUserCart[j].totalCost,
                tempUserCart[j].timeStamp
            );
        }
        
        fclose(fpTemp);
    }
    else {
        SaveProductToCart(userCart);
    }
   
    

}

void SaveProductToCart(UserCart *userCart){
    FILE *fp;

    fp = fopen("database/UserCart.csv","a+");

    if(fp == NULL){
        printf("Error Opening UserCart.csv\n");
        return;
    }

    // printf("Time in string %s",ctime(&userCart->timeStamp));
    // printf("Time in millisecond %d",userCart->timeStamp);
    fprintf(fp,
        "%s,%s,%d,%d,%d,%d\n",
        userCart->cartOwner,
        userCart->productName,
        userCart->singlePriceProduct,
        // strtok(ctime(&userCart->timeStamp),"\n"),
        userCart->totalInCart,
        userCart->totalCost,
        userCart->timeStamp
    );
    
    if(fwrite != 0){
        printf("\nSuccessfully saved");
    }
    else{
        printf("\nError saving");
    } 

    fclose(fp);

}


void PrintUserCart(User *currentUser){

    FILE *fp;
    UserCart userCart;

    fp = fopen("database/UserCart.csv","r");
    printf("\n------------------   USER CART  ------------------\n");

    char line[1000];
    char *sp;
    int i = 1;


    while (fgets(line, 1000, fp) != NULL){

        sp = strtok(line, ",");
        strcpy(userCart.cartOwner, sp);
        if(strcmp(userCart.cartOwner, currentUser->userName) == 0){
            
            printf("\n--------------- Item In Cart  :  \033[0;32m%d\033[0m ----------------\n\n",i);
            
            printf("\tCart Owner                  :\t%s\n", userCart.cartOwner);

            sp = strtok(NULL, ",");
            strcpy(userCart.productName, sp);
            printf("\tProduct Name                :\t%s\n", userCart.productName);
        
            sp = strtok(NULL, ",");
            userCart.singlePriceProduct = atoi(sp);
            printf("\tSingle Price Product        :\t%d\n", userCart.singlePriceProduct);
            

            sp = strtok(NULL, ",");
            userCart.totalInCart = atoi(sp);
            printf("\tTotal In Cart               :\t%d\n", userCart.totalInCart);

            sp = strtok(NULL, ",");
            userCart.totalCost = atoi(sp);
            printf("\tTotal Cost                  :\t%d\n", userCart.totalCost);
        
            sp = strtok(NULL, ",");
            int tempTime = atoi(sp);

            userCart.timeStamp = (time_t) tempTime;
            printf("\tTime Stamps                 :\t%s\n", strtok(ctime(&userCart.timeStamp),"\n"));
            // strptime(sp, "%s", &userCart.timeStamp);
        
            printf("\n\n"); 
        
            i++;
        
        }
      

    }

    fclose(fp);
    UserSelection(currentUser);
    return;

}


void CheckBill(User *currentUser){

    UserCart userCart[1000];
    char target[100];
    int itemsCount = 0;
    int sumPrice = 0;
    strcpy(target, currentUser->userName);

    PrintUserCartSpecific(target, userCart, &itemsCount, &sumPrice);

    CheckBillSelection(currentUser);


}


void PrintUserCartSpecific(char *target, UserCart itemsInCart[], int *itemsCount, int *sumPrice){
    FILE *fp;
    // UserCart userCart;

    fp = fopen("database/UserCart.csv","r");
    // printf("\n =========   USER CART  ========== \n");

    char line[1000];
    char *sp;
    int i = 1;


    while (fgets(line, 1000, fp) != NULL){

        sp = strtok(line, ",");
        
        if(strcmp(sp, target) == 0){

            printf("\n--------------- Number of Items In Your Cart  :  \033[0;32m%d\033[0m ----------------\n\n",*itemsCount+1);

            strcpy(itemsInCart[*itemsCount].cartOwner, sp);
            printf("\tCart Owner                  :\t%s\n", itemsInCart[*itemsCount].cartOwner);

            sp = strtok(NULL, ",");
            strcpy(itemsInCart[*itemsCount].productName, sp);
            printf("\tProduct Name                :\t%s\n", itemsInCart[*itemsCount].productName);
        
            sp = strtok(NULL, ",");
            itemsInCart[*itemsCount].singlePriceProduct = atoi(sp);
            printf("\tSingle Price Product        :\t%d\n", itemsInCart[*itemsCount].singlePriceProduct);
            

            sp = strtok(NULL, ",");
            itemsInCart[*itemsCount].totalInCart = atoi(sp);
            printf("\tTotal In Cart               :\t%d\n", itemsInCart[*itemsCount].totalInCart);

            sp = strtok(NULL, ",");
            itemsInCart[*itemsCount].totalCost = atoi(sp);
            printf("\tTotal Cost                  :\t%d\n", itemsInCart[*itemsCount].totalCost);
            *sumPrice = *sumPrice + itemsInCart[*itemsCount].totalCost;

            sp = strtok(NULL, ",");
            int tempTime = atoi(sp);

            itemsInCart[*itemsCount].timeStamp = (time_t) tempTime;
            printf("\tTime Stamps                 :\t%s\n", strtok(ctime(&itemsInCart[*itemsCount].timeStamp),"\n"));
            // strptime(sp, "%s", &userCart.timeStamp);
            *itemsCount = *itemsCount + 1;
            printf("\n\n");
        }
      
        i++;

    }

    printf("Total Price In Your Cart :\t%d\n",*sumPrice);

    fclose(fp);
    

}




void PayBill(User *currentUser){

    printf("----------------- Items In Your Cart -----------------\n");

    UserCart userCart[1000];
    char target[100];
    int itemsCount = 0;
    int sumPrice = 0;
    strcpy(target, currentUser->userName);
    PrintUserCartSpecific(target, userCart, &itemsCount, &sumPrice);

    char choice;
    printf("Do You Want To Confirmation Of Payment? [y/n] :\t");

    fflush(stdin);   
    yellow();
    if(scanf("%c",&choice) != 1) {
        reset();
        system("clear");
        printf("Please Enter Correct Type\n");
        PayBill(currentUser);
        return;
    } 

    reset();
    
    if(choice == 'y'){

        SaveUserPos(currentUser);
        UpdateStock(currentUser);
        UpdateUserCart(currentUser);

    }

    else if(choice == 'n'){
        UserSelection(currentUser);
        return;
    }

    else {
        system("clear");
        printf("Please Enter Correct Type \n");
        PayBill(currentUser);
        return;
    }
    UserSelection(currentUser);
    return;
}


void SaveUserPos(User *currentUser){

    FILE *fp, *fpTemp, *fpTemp2, *fpTemp3;
    fp = fopen("database/UserCart.csv","r");
    fpTemp = fopen("database/UserPOS.csv","a+");        
    fpTemp2 = fopen("database/tempUserCart.csv","w");        
    fpTemp3 = fopen("database/TempUserPOS.csv","w");        
    char *sp;
    char line[1000];
    UserPOS createPOS;
    int i = 0;
    int found = 0;

    while (fgets(line, 1000, fp) != NULL){

        sp = strtok(line, ",");
        strcpy(createPOS.cartOwner, sp);
        // printf("%s\n",currentUser->userName);
        sp = strtok(NULL, ",");
        strcpy(createPOS.productName, sp);
        
        sp = strtok(NULL, ",");
        createPOS.singlePriceProduct = atoi(sp);

        sp = strtok(NULL, ",");
        createPOS.totalInCart = atoi(sp);

        sp = strtok(NULL, ",");
        createPOS.totalCost = atoi(sp);

        if(strcmp(createPOS.cartOwner, currentUser->userName) == 0){

            // printf("%s\n",createPOS.cartOwner);
            sp = strtok(NULL, ",");
            createPOS.timeStamp = time(NULL);

            fprintf(fpTemp,
                "%s,%s,%d,%d,%d,%d\n",
                createPOS.cartOwner,
                createPOS.productName,
                createPOS.singlePriceProduct,
                createPOS.totalInCart,
                createPOS.totalCost,
                createPOS.timeStamp
            );

            fprintf(fpTemp3,
                "%s,%s,%d,%d,%d,%d\n",
                createPOS.cartOwner,
                createPOS.productName,
                createPOS.singlePriceProduct,
                createPOS.totalInCart,
                createPOS.totalCost,
                createPOS.timeStamp
            );

            if(fwrite != 0){
                // printf("\nSuccessfully save\n");
            }
            else{
                printf("\nError saving\n");
            } 
            
        }

        else {
            
            sp = strtok(NULL, ",");
            int tempTime = atoi(sp);
            createPOS.timeStamp = (time_t) tempTime;

            fprintf(fpTemp2,
                "%s,%s,%d,%d,%d,%d\n",
                createPOS.cartOwner,
                createPOS.productName,
                createPOS.singlePriceProduct,
                createPOS.totalInCart,
                createPOS.totalCost,
                createPOS.timeStamp 
            );

            if(fwrite != 0){
                // printf("\nSuccessfully save\n");
            }
            else{
                printf("\nError saving\n");
            } 

        }

    }

    fclose(fp);
    fclose(fpTemp);
    fclose(fpTemp2);
    fclose(fpTemp3);
    // rename("database/tempUserCart.csv","database/UserCart.csv");

}


void UpdateStock(User *currentUser){

    FILE *fp, *fpTemp, *fpTemp2;
    // fp = fopen("database/UserCart.csv","w");
    fp = fopen("database/TempUserPOS.csv","r");
    char line[1000];
    char *sp;

    CutStock product[100];
    int size = 0;

    while (fgets(line, 1000, fp) != NULL){

        //Cart Owner
        sp = strtok(line, ",");

        sp = strtok(NULL, ",");
        strcpy(product[size].productName, sp);

        sp = strtok(NULL, ",");
        sp = strtok(NULL, ",");
        product[size].totalToCut = atoi(sp);

        size++;

    }

    // for (int i = 0; i < size; i++){
    //     printf("Product Name :\t%s\n",product[i].productName);
    // }

    
    fpTemp = fopen("database/Product.csv","r");
    fpTemp2 = fopen("database/TempProduct.csv","w");
    char *sp1;
    int found = 0;
    bool exist = false;

    Product updateProduct;
    
    SumCutStock(product, size);

    while (fgets(line, 1000, fpTemp) != NULL){
        exist = false;
        sp1 = strtok(line, ",");
        strcpy(updateProduct.productName, sp1);

        sp1 = strtok(NULL, ",");
        updateProduct.productPrice = atoi(sp1);

        sp1 = strtok(NULL, ",");
        updateProduct.productQuantity = atoi(sp1);
       
        sp1 = strtok(NULL, ",");
        updateProduct.productCost = atoi(sp1);

        // sp1 = strtok(NULL, ",");
        // updateProduct.productProfit = atoi(sp1);

        sp1 = strtok(NULL, ",");
        updateProduct.minimumQuantity = atoi(sp1);

        for (int i = 0; i < size; i++){
            // printf("UPDATE PRODUCTNAME %s AND PRODUCT NAME %s RESULT = %d\n",updateProduct.productName, product[i].productName,strcmp(updateProduct.productName, product[i].productName));
            if(product[i].totalToCut == 0) continue;
            else if(strcmp(updateProduct.productName, product[i].productName) == 0){
                // printf("FOUND SAVING");
                found = 1;
                exist = true;
                fprintf(fpTemp2,
                    "%s,%d,%d,%d,%d\n",
                    updateProduct.productName,
                    updateProduct.productPrice,
                    updateProduct.productQuantity - product[i].totalToCut,
                    updateProduct.productCost,
                    // updateProduct.productProfit,
                    updateProduct.minimumQuantity
                );

                if(fwrite != 0){
                    // printf("\nSuccessfully saved");
                }
                else{
                    printf("\nError saving");
                } 
                break;
            }

        }

        if(exist == false){
            fprintf(fpTemp2,
            "%s,%d,%d,%d,%d\n",
            updateProduct.productName,
            updateProduct.productPrice,
            updateProduct.productQuantity,
            updateProduct.productCost,
            // updateProduct.productProfit,
            updateProduct.minimumQuantity
        );}

        if(fwrite != 0){
            // printf("\nSuccessfully saved");
        }
        else{
            printf("\nError saving");
        } 
        

    }
    fclose(fp);
    fclose(fpTemp);
    fclose(fpTemp2);
    
    if(found == 1){

        fpTemp = fopen("database/Product.csv","w");
        fpTemp2 = fopen("database/TempProduct.csv","r");
        Product tempProduct;

        while (fgets(line, 1000, fpTemp2) != NULL){

            // sscanf(line, "%s", &tempProduct.productName);

            sp = strtok(line, ",");
            strcpy(tempProduct.productName, sp);
            
            sp = strtok(NULL, ",");
            tempProduct.productPrice = atoi(sp);

            sp = strtok(NULL, ",");
            tempProduct.productQuantity = atoi(sp);

            sp = strtok(NULL, ",");
            tempProduct.productCost = atoi(sp);

            // sp = strtok(NULL, ",");
            // tempProduct.productProfit = atoi(sp);

            sp = strtok(NULL, ",");
            tempProduct.minimumQuantity = atoi(sp);

         
            fprintf(fpTemp,
            "%s,%d,%d,%d,%d\n",
                tempProduct.productName,
                tempProduct.productPrice,
                tempProduct.productQuantity,
                tempProduct.productCost,
                // tempProduct.productProfit,
                tempProduct.minimumQuantity
            );
        }

        fclose(fpTemp);     
        fclose(fpTemp2);

    }
    else {
        printf("DATA NOT FOUND\n");
    }


}

void SumCutStock(CutStock product[], int size){
    
    for (int i = 0; i < size; i++){
        for (int j = 0; j < size; j++){
            if(i == j || product[j].totalToCut == 0) continue;
            else if(strcmp(product[i].productName, product[j].productName) == 0){
                // printf("TRUE\n");
                strcpy(product[j].productName, "chitsanupong");
                product[i].totalToCut += product[j].totalToCut;
                product[j].totalToCut = 0;
            }
        }
    }

    // for (int i = 0; i < size; i++){
    //     printf("%s %d\n",product[i].productName, product[i].totalToCut);
    // }

}


void UpdateUserCart(User *currentUser){

    FILE *fp, *fpTemp;
    fp = fopen("database/UserCart.csv","w");
    fpTemp = fopen("database/tempUserCart.csv","r");
    char line[1000];
    char *sp;
    UserCart tempUserCart;

    while (fgets(line, 1000, fpTemp) != NULL){

        sp = strtok(line, ",");
        strcpy(tempUserCart.cartOwner, sp);

        sp = strtok(NULL, ",");
        strcpy(tempUserCart.productName, sp);

        sp = strtok(NULL, ",");
        tempUserCart.singlePriceProduct = atoi(sp);

        sp = strtok(NULL, ",");
        tempUserCart.totalInCart = atoi(sp);

        sp = strtok(NULL, ",");
        tempUserCart.totalCost = atoi(sp);

        sp = strtok(NULL, ",");
        int tempTime = atoi(sp);


        tempUserCart.timeStamp = (time_t) tempTime;
        
        fprintf(fp,
            "%s,%s,%d,%d,%d,%d\n",
            tempUserCart.cartOwner,
            tempUserCart.productName,
            tempUserCart.singlePriceProduct,
            // strtok(ctime(&userCart.timeStamp),"\n"),
            tempUserCart.totalInCart,
            tempUserCart.totalCost,
            tempUserCart.timeStamp
        );

    }
    
    fclose(fp);
    fclose(fpTemp);


}


void EditItemInCart(User *currentUser){
    
    UserCart userCart[1000];
    char target[100];
    int itemsCount = 0;
    int sumPrice = 0;
    strcpy(target, currentUser->userName);
    PrintUserCartSpecific(target, userCart, &itemsCount, &sumPrice);
    
    
    UserCart tempCart;
    FILE *fp, *fpTemp;

    char line[1000];

    int targetLine;
    fflush(stdin);
    printf("Enter Number Of Item That You Want To Edit :\t");
    yellow();
    if(scanf("%d",&targetLine) != 1) {
        reset();
        system("clear");
        printf("Please Enter Correct Type\n");
        EditItemInCart(currentUser);
    }
    reset();

    fp = fopen("database/UserCart.csv","r");
    fpTemp = fopen("database/tempUserCart.csv","w");
    char *sp;
    UserCart updateCart;
    int i = 0;
    int found = 0;

    while (fgets(line, 1000, fp) != NULL){
        

        sp = strtok(line, ",");
        strcpy(updateCart.cartOwner, sp);
        if(strcmp(updateCart.cartOwner, currentUser->userName) == 0) i++;

        sp = strtok(NULL, ",");
        strcpy(updateCart.productName, sp);

        sp = strtok(NULL, ",");
        updateCart.singlePriceProduct = atoi(sp);

        sp = strtok(NULL, ",");
        updateCart.totalInCart = atoi(sp);

        sp = strtok(NULL, ",");
        updateCart.totalCost = atoi(sp);

        sp = strtok(NULL, ",");
        int tempTime = atoi(sp);
        updateCart.timeStamp = (time_t) tempTime;

        if(targetLine == i && strcmp(updateCart.cartOwner, currentUser->userName) == 0){

            found = 1;

            printf("Current Total In Cart Is %d: Please Enter New Value :\t", updateCart.totalInCart);
            yellow();
            scanf("%d", &updateCart.totalInCart);
            reset();

            updateCart.totalCost = updateCart.singlePriceProduct * updateCart.totalInCart;

            fprintf(fpTemp,
                "%s,%s,%d,%d,%d,%d\n",
                updateCart.cartOwner,
                updateCart.productName,
                updateCart.singlePriceProduct,
                // strtok(ctime(&userCart.timeStamp),"\n"),
                updateCart.totalInCart,
                updateCart.totalCost,
                updateCart.timeStamp
            );

            if(fwrite != 0){
                // printf("\nSuccessfully saved");
            }
            else{
                printf("\nError saving");
            } 

        }     
        else {
            fprintf(fpTemp,
                "%s,%s,%d,%d,%d,%d\n",
                updateCart.cartOwner,
                updateCart.productName,
                updateCart.singlePriceProduct,
                // strtok(ctime(&userCart.timeStamp),"\n"),
                updateCart.totalInCart,
                updateCart.totalCost,
                updateCart.timeStamp
            );

            if(fwrite != 0){
                // printf("\nSuccessfully saved");
            }
            else{
                printf("\nError saving");
            } 
        }   

    }
        
    fclose(fp);
    fclose(fpTemp);

    if(found == 1){
        
        fp = fopen("database/UserCart.csv", "w");
        fpTemp = fopen("database/tempUserCart.csv", "r");

        while (fgets(line, 1000, fpTemp) != NULL){

            sp = strtok(line, ",");

            strcpy(tempCart.cartOwner, sp);
            // printf("\tCart Owner                  :\t%s\n", tempCart.cartOwner);

            sp = strtok(NULL, ",");
            strcpy(tempCart.productName, sp);
            // printf("\tProduct Name                :\t%s\n", tempCart.productName);
        
            sp = strtok(NULL, ",");
            tempCart.singlePriceProduct = atoi(sp);
            // printf("\tSingle Price Product        :\t%d\n", tempCart.singlePriceProduct);
            

            sp = strtok(NULL, ",");
            tempCart.totalInCart = atoi(sp);
            // printf("\tTotal In Cart               :\t%d\n", tempCart.totalInCart);

            sp = strtok(NULL, ",");
            tempCart.totalCost = atoi(sp);
            // printf("\tTotal Cost                  :\t%d\n", tempCart.totalCost);

            sp = strtok(NULL, ",");
            int tempTime = atoi(sp);

            tempCart.timeStamp = (time_t) tempTime;
            // printf("\tTime Stamps                 :\t%s\n", strtok(ctime(&tempCart.timeStamp),"\n"));
            // strptime(sp, "%s", &userCart.timeStamp);

            fprintf(fp,
                "%s,%s,%d,%d,%d,%d\n",
                tempCart.cartOwner,
                tempCart.productName,
                tempCart.singlePriceProduct,
                // strtok(ctime(&userCart.timeStamp),"\n"),
                tempCart.totalInCart,
                tempCart.totalCost,
                tempCart.timeStamp
            );

        }

        fclose(fp);
        fclose(fpTemp);
        printf("Successfully saved\n");
        UserSelection(currentUser);
        return;
    }

    else {
        printf("DATA NOT FOUND\n");
        
    }

    UserSelection(currentUser);
    return;


}


void RemoveItemInCart(User *currentUser){

    FILE *fp, *fpTemp;

    UserCart userCart[1000];
    char target[100];
    int itemsCount = 0;
    int sumPrice = 0;
    strcpy(target, currentUser->userName);
    PrintUserCartSpecific(target, userCart, &itemsCount, &sumPrice);
    
    int targetLine;
    fflush(stdin);
    printf("Enter Number Of Item That You Want To Remove :\t"); 
    yellow();
    if(scanf("%d",&targetLine) != 1) {
        reset();
        system("clear");
        printf("Please Enter Correct Type\n");
        RemoveItemInCart(currentUser);
    }

    reset();
    fp = fopen("database/UserCart.csv","r");
    fpTemp = fopen("database/tempUserCart.csv","w");
    char *sp;
    char line[1000];
    UserCart tempCart;
    int i = 0;
    int found = 0;


    while (fgets(line, 1000, fp) != NULL){

        sp = strtok(line, ",");
        strcpy(tempCart.cartOwner, sp);
        if(strcmp(tempCart.cartOwner, currentUser->userName) == 0) i++;

        sp = strtok(NULL, ",");
        strcpy(tempCart.productName, sp);

        sp = strtok(NULL, ",");
        tempCart.singlePriceProduct = atoi(sp);

        sp = strtok(NULL, ",");
        tempCart.totalInCart = atoi(sp);

        sp = strtok(NULL, ",");
        tempCart.totalCost = atoi(sp);

        sp = strtok(NULL, ",");
        int tempTime = atoi(sp);
        tempCart.timeStamp = (time_t) tempTime;

        if(targetLine == i && strcmp(tempCart.cartOwner, currentUser->userName) == 0){

            found = 1;

        }     
        else {
            fprintf(fpTemp,
                "%s,%s,%d,%d,%d,%d\n",
                tempCart.cartOwner,
                tempCart.productName,
                tempCart.singlePriceProduct,
                // strtok(ctime(&userCart.timeStamp),"\n"),
                tempCart.totalInCart,
                tempCart.totalCost,
                tempCart.timeStamp
            );

            if(fwrite != 0){
                // printf("\nSuccessfully saved");
            }
            else{
                printf("\nError saving");
            } 
        }   

    }
    
    fclose(fp);
    fclose(fpTemp);

    if(found == 1){
        fp = fopen("database/UserCart.csv", "w");
        fpTemp = fopen("database/tempUserCart.csv", "r");

        while (fgets(line, 1000, fpTemp) != NULL){
            sp = strtok(line, ",");

            strcpy(tempCart.cartOwner, sp);
            // printf("\tCart Owner                  :\t%s\n", tempCart.cartOwner);

            sp = strtok(NULL, ",");
            strcpy(tempCart.productName, sp);
            // printf("\tProduct Name                :\t%s\n", tempCart.productName);
        
            sp = strtok(NULL, ",");
            tempCart.singlePriceProduct = atoi(sp);
            // printf("\tSingle Price Product        :\t%d\n", tempCart.singlePriceProduct);
            

            sp = strtok(NULL, ",");
            tempCart.totalInCart = atoi(sp);
            // printf("\tTotal In Cart               :\t%d\n", tempCart.totalInCart);

            sp = strtok(NULL, ",");
            tempCart.totalCost = atoi(sp);
            // printf("\tTotal Cost                  :\t%d\n", tempCart.totalCost);

            sp = strtok(NULL, ",");
            int tempTime = atoi(sp);

            tempCart.timeStamp = (time_t) tempTime;
            // printf("\tTime Stamps                 :\t%s\n", strtok(ctime(&tempCart.timeStamp),"\n"));
            // strptime(sp, "%s", &userCart.timeStamp);

            fprintf(fp,
                "%s,%s,%d,%d,%d,%d\n",
                tempCart.cartOwner,
                tempCart.productName,
                tempCart.singlePriceProduct,
                // strtok(ctime(&userCart.timeStamp),"\n"),
                tempCart.totalInCart,
                tempCart.totalCost,
                tempCart.timeStamp
            );
        }
        

        fclose(fp);
        fclose(fpTemp);
        printf("Successfully saved\n");
        UserSelection(currentUser);
        return;
    }

    else {
        printf("DATA NOT FOUND\n");
    }
    UserSelection(currentUser);
    return;

}


