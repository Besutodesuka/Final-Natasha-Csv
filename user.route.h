#ifndef _USERROUTE_H
#define _USERROUTE_H

#include <time.h>

typedef struct {
  char userName[50];
  char email[50];
  char password[50];
  char phone[50];
  char role[10];
} User;

typedef struct {
  char cartOwner[50];
  char productName[50];
  int totalInCart;
  int singlePriceProduct;
  int totalCost;
  time_t timeStamp;
} UserCart;

typedef struct {
  char cartOwner[50];
  char productName[50];
  int totalInCart;
  int singlePriceProduct;
  int totalCost;
  time_t timeStamp;
} UserPOS;




typedef struct {

  char productName[50];
  int totalToCut;

} CutStock;



void FirstTouch(int *loginOrNot, User *currentUser);

// ============= ADMIN CHOICE =============

void AdminSelection(User *currentUser);

// ============= END ADMIN CHOICE =============


// ============ Authentication ============

void Register(int *loginOrNot, User *currentUser);
void Login(int *loginOrNot, User *currentUser);

// ========== END Authentication ==========



// ============== USER CART ===============

void PrintProductForUser(User *currentUser);
void PrintProductForUserSelection(User *currentUser);
void AddProductToCart(User *currentUser);
void PrintUserCart(User *currentUser);

// ============ END USER CART =============

// ============== USER CART ===============

void CheckBill(User *currentUser);
// ============ END USER CART =============





void UserSelection(User *currentUser);




void white ();
void black ();
void red ();
void green ();
void yellow();
void blue();
void purple();
void cyan();
void reset ();


#endif 