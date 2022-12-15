
#include <stdio.h>
#include "admin.route.h"
#include <string.h>
#include <stdlib.h>
// #include "headerFile/userAuth.h"
#include "user.route.h"

void PrintCurrentUserStruct(User *currentUser){
  blue();
  printf("\n----------------------  Current User  ----------------------\n\n");
  reset();
  printf("UserName  \t:\t\033[0;33m%s \033[0m\n",currentUser->userName);
  printf("Email     \t:\t\033[0;33m%s \033[0m\n",currentUser->email);
  printf("Phone     \t:\t\033[0;33m%s \033[0m\n",currentUser->phone);
  printf("Role      \t:\t\033[0;33m%s \033[0m\n",currentUser->role);
}

int main(void){
  
  // time_t t = time(NULL);
  // printf("\n Current date and time is : %s", ctime(&t));

  int loginOrNot = 0;
  // 0 = NotLogin 1 = AdminLogin 2 = UserLogin
  
  char keepGoingOrNot = 'y';
  
  User *currentUser;
  currentUser = calloc(1, sizeof(User));

  while (loginOrNot == 0){
    FirstTouch(&loginOrNot, currentUser);
    // printf("LOGIN OR NOT FROM WHILE %d\n",loginOrNot);
    if(loginOrNot == 0){
      // system("cls");
      red();
      printf("========= Your UserName Or Password Is Wrong =========\n");
      reset();
    }
  }
  // printf("LOGIN OR NOT %d\n",loginOrNot);
  if(loginOrNot == 2){
    PrintCurrentUserStruct(currentUser);
    AdminSelection(currentUser);
    // printf("Admin Login\n");
  }

  else if(loginOrNot == 1){
    PrintCurrentUserStruct(currentUser);
    UserSelection(currentUser);
    // printf("User Login\n");
  }
  return 0;
}


/* 
int main(void){
  
  int loginOrNot = 0;
  // 0 = NotLogin 1 = UserLogin 2 = AdminLogin
  char keepGoingOrNot = 'y';
  while(keepGoingOrNot == 'y'){
    printf("THIS IS LOGINORNOT %d\n",loginOrNot);
    if(loginOrNot == 0){
      int choice;
      system("cls");
      printf("\t============WELCOME TO SLEEP SHOP============");
      printf("\n\nPlease select your prefered operation");
      printf("\n(1) Login");
      printf("\n(2) Register");
      printf("\n(3) PrintDb User");
      printf("\n(4) Number User");
      printf("\n(5) Edit User");
      printf("\n(6) Remove User");
      printf("\n(7) Add Product");
      printf("\n(8) Print Product");
      printf("\n(9) Edit Product");
      printf("\n(10) Remove Product");
      printf("\n(11) Exist");
      printf("\n\nYour choice\t:\t");
      scanf("%d",&choice);
      fgetc(stdin);

      switch (choice){
        case 1:
          loginOrNot = Login();
          break;
        
        case 2:
          loginOrNot = Register();
          break;

        case 3:
          PrintUserData();
          break;
        
        case 4:
           
            printf("Number Of User %d\n",NumberOfUser());
            break;

        case 5:
            EditUser();
            break;
      
        case 6:
            RemoveUser();
            break;

        case 7:
          AddProduct();
          break;
        
        case 8:
          PrintProduct();
          break;
        
        case 9:
          EditProductInDB();
          break;
       
        case 10:
          RemoveProduct();
          break;

        case 11:
          printf("\n\t\t Bye Bye :)\n\n");
          exit(0);
          break;

        default:
          printf("Your input is invalid, please try again");
          break;
      }
    }

    printf("\nDo you want to perform another operation?[y/n]:\t");
    scanf("%s",&keepGoingOrNot);
  }
  return 0;
}

 */