/* 
หน้านี้มีฟังก์ชันของ USER อย่างเดียว
1. ฟังก์ชันตั้งแต่เริ่มโปรแกรม = FirstTouch
2. ฟังก์ชันให้ user เลือกหลังจาก login = UserSelection

 */


#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "user.route.h"

#define FILENAME_SIZE 1024
#define MAX_LINE 2048


void FirstTouch(int *loginOrNot, User *currentUser){
    int choice;
    system("cls");
    green();
    printf("----------------------------------------------\n");
    red();
    printf("            WELCOME TO SLEEP SHOP\n");
    green();
    printf("----------------------------------------------\n\n");
    reset();
    purple();
    printf("Please Select Your Prefered Operation\n\n");
    reset();
    printf("-> (1) Login\n");
    printf("-> (2) Register\n");
    printf("-> (3) Exit\n");
    printf("\n\nYour choice\t:\t");

    yellow();
    if(scanf("%d",&choice) != 1) {
        reset();
        system("cls");
        printf("Please Enter Correct Type\n");
        FirstTouch(loginOrNot, currentUser);
        return;
    } 


    if(choice > 3 || choice < 0) {
        system("cls");
        printf("Please Enter Correct Type\n");
        FirstTouch(loginOrNot, currentUser);
        return;
    }
    reset();
    // fgetc(stdin);

    switch (choice){
        case 1:
          Login(loginOrNot, currentUser);
          // printf("LOGIN %d\n",Login(loginOrNot));
          // printf("LOGIN OR NOT FROM CASE LOGIN %d\n",*loginOrNot);
          break;
        
        case 2:
          Register(loginOrNot, currentUser);
          // printf("LOGIN OR NOT FROM CASE REGISTER %d\n",*loginOrNot);
          break;

        case 3:
          printf("\n\t\t Bye Bye :)\n\n");
          exit(0);
          break;

        default:
          printf("Your input is invalid, please try again");
          break;
    }
    // printf("LOGIN OR NOT %d\n",*loginOrNot);
    return;
}

void UserSelection(User *currentUser){
    
    int choice;
    
    // while (choice != 1 || choice != 2){
    purple();
    printf("\n\nWhat You Want To Do Here?");
    reset();
    printf("\n(1) See Other Product");
    printf("\n(2) Add Product To Cart");
    printf("\n(3) Check Your Cart");
    printf("\n(4) Check bill");
    printf("\n(5) Exit");
    printf("\n\nYour choice\t:\t");
    fflush(stdin);
    yellow();
    scanf("%d",&choice);
    reset();
    
    switch (choice){
    case 1:
        PrintProductForUserSelection(currentUser);
        break;

    case 2:
        // printf("ADD PRODUCT RUNNING\n");
        AddProductToCart(currentUser);
        break;

    case 3:
        PrintUserCart(currentUser);
        break;

    case 4:
        // printf("CHECK BILL\n");
        CheckBill(currentUser);
        break;
    
    case 5:
        printf("\n\t\t Bye Bye :)\n\n");
        exit(0);
        break;

    default:
        printf("Please Select A Corrent Choice");
        UserSelection(currentUser);
        break;
    }
    // }

}


void white () {
  printf("\033[0;37m");
}
void black () {
  printf("\033[0;30m");
}
void red () {
  printf("\033[0;31m");
}
void green () {
  printf("\033[0;32m");
}

void yellow() {
  printf("\033[1;33m");
}
void blue() {
  printf("\033[1;34m");
}
void purple() {
  printf("\033[1;35m");
}
void cyan() {
  printf("\033[1;36m");
}


void reset () {
  printf("\033[0m");
}
