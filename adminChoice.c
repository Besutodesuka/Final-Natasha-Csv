/* 
1. หน้าให้แอดมินเลือกว่าจะทำเกี่ยวกับ user หรือ product = AdminSelection
2. ปริ้นสิ่งที่ ADMIN สามารถทำกับ USER ได้ = CommandUser
3. ปริ้นสิ่งที่ ADMIN ทำกับ PRODUCT ได้ = CommandProduct
 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "admin.route.h"
#include "user.route.h"

void AdminSelection(User *currentUser){
    
    int choice;
    // while (choice != 4){
    // system("cls");
    fflush(stdin);
    purple();
    printf("\n\nHey Admin! What you want to do here");
    reset();
    printf("\n-> (1) See All Command User");
    printf("\n-> (2) See All Command Product");
    printf("\n-> (3) Accounting System");
    printf("\n-> (4) Point Of Sales");
    // printf("\n-> (5) Go To User Selection");
    printf("\n-> (5) Exit");
    printf("\n\nYour choice\t:\t");
    yellow();
    if(scanf("%d",&choice) != 1) {
        system("cls");
        printf("Please Enter Correct Type\n");
        AdminSelection(currentUser);
        return;
    }
    reset();
    // scanf("%d",&choice);

    switch (choice){
    case 1:
        CommandUser(currentUser);
        break;
    
    case 2:
        CommandProduct(currentUser);
        break;
    
    case 3:
        SelectAccounting();
        AdminSelection(currentUser);
        break;

    case 4:
        SelectPointOfSales();
        AdminSelection(currentUser);
        break;

    case 5:
        printf("\n\t\t Bye Bye :)\n\n");
        exit(0);
        break;
        // UserSelection(currentUser);
        // break;       

    default:
        printf("Please Select A Corrent Choice");
        AdminSelection(currentUser);
        break;
    }
    // }
    

}

void CommandUser(User *currentUser){

    int choice;
    // while (choice != 5){
    purple();
    printf("\n\nHey Admin! What you want to do for user?");
    reset();
    printf("\n(1) Number User");
    printf("\n(2) PrintDb User");
    printf("\n(3) Edit User");
    printf("\n(4) Remove User");
    printf("\n(5) Back To Admin Dashboard");
    printf("\n(6) Exit");
    printf("\n\nYour choice\t:\t");
    fflush(stdin);
    scanf("%d",&choice);

    switch (choice){
    case 1:

        printf("Number Of User %d\n",NumberOfUser());
        AdminSelection(currentUser);
        return;
        break;

    case 2:
        PrintUserData();
        AdminSelection(currentUser);
        return;
        break;

    case 3:
        EditUser();
        AdminSelection(currentUser);
        return;
        break;

    case 4:
        RemoveUser();
        AdminSelection(currentUser);
        return;
        break;

    case 5:
        AdminSelection(currentUser);
        break;

    case 6:
        printf("\n\t\t Bye Bye :)\n\n");
        exit(0);
        break;

    default:
        printf("Please Select A Corrent Choice");
        CommandUser(currentUser);
        break;
    }
// }
    
}

void CommandProduct(User *currentUser){
    
    int choice;
    purple();
    printf("\n\nHey Admin! What you want to do for user?");
    reset();
    printf("\n(1) Print Product");
    printf("\n(2) Add Product");
    printf("\n(3) Edit Product");
    printf("\n(4) Remove Product");
    printf("\n(5) Back To Admin Dashboard");
    printf("\n(6) Exit");
    printf("\n\nYour choice\t:\t");
    fflush(stdin);
    scanf("%d",&choice);

    switch (choice){
    case 1:
        PrintProduct();
        AdminSelection(currentUser);
        return;
        break;

    case 2:
        AddProduct();
        AdminSelection(currentUser);
        return;
        break;

    case 3:
        EditProductInDB();
        AdminSelection(currentUser);
        return;
        break;

    case 4:
        RemoveProduct();
        AdminSelection(currentUser);
        return;
        break;
    case 5:
        AdminSelection(currentUser);
        break;

    case 6:
        printf("\n\t\t Bye Bye :)\n\n");
        exit(0);
        break;

    default:
        printf("Please Select A Corrent Choice");
        CommandProduct(currentUser);
        break;
    }
}