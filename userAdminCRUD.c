/* 
1. ฟังก์ชัน PRINT USER ทั้งหมดที่มี = PrintUserData
2. ฟังก์ชั่นปริ้นจำนวนลูกค้าทั้งหมดที่มี = NumberOfUser
3. ฟังก์ชัน EDIT USER = EditUser
4. ฟังก์ชันลบ USER = RemoveUser
 */


#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "user.route.h"
#include <stdbool.h>
#define FILENAME_SIZE 1024
#define MAX_LINE 2048


User makeUser(char *userName, char *email, char *password, char *phone, char *role){
  User user;
  
  strcpy(user.userName,userName);
  strcpy(user.email,email);
  strcpy(user.password,password);
  strcpy(user.phone,phone);
  strcpy(user.role,role);
  return user;

}

void PrintUserData(){

    FILE *fp;
    User users[1000];

    fp = fopen("database/User.csv", "r"); 
    if(fp == NULL){
        printf("Error Opening File.\n");
        return;
    }
    char line[1000];
    
    char *sp;
    int i = 1;
    // TODO: print table header 
    while (fgets(line, 1000, fp) != NULL){
        // printf("\n%s",line);

        // printf("----------- User Line : %d -------------\n\n",i);

        sp = strtok(line, ",");
        strcpy(users[i].userName, sp);

        sp = strtok(NULL, ",");
        strcpy(users[i].password, sp);

        sp = strtok(NULL, ",");
        strcpy(users[i].email, sp);

        sp = strtok(NULL, ",");
        strcpy(users[i].phone, sp);
        
        sp = strtok(NULL, ",");
        strcpy(users[i].role, sp);

        printf("-----------  Number Of User : \033[0;32m%d\033[0m  --------------\n\n",i);
        reset();
        printf("UserName        :\t\033[0;33m%s\n",users[i].userName);
        reset();
        printf("Password        :\t\033[0;33m%s\n",users[i].password);
        reset();
        printf("Email           :\t\033[0;33m%s\n",users[i].email);
        reset();
        printf("Phone           :\t\033[0;33m%s\n",users[i].phone);
        reset();
        printf("Role            :\t\033[0;33m%s\n",users[i].role);
        reset();
        printf("\n-----------------------------------------------\n\n");

        // printf("%s %s %s %s %s",users[i].userName, users[i].password, users[i].email, users[i].phone, users[i].role);

        i++;
    }   
    // scanf("");

    fclose(fp);

}

int NumberOfUser(){
    FILE *fp;

    if (fp == NULL){
        printf("Error opening file.\n");
        return 0;
    }
    fp = fopen("database/User.csv", "r"); 
   
    char line[1000];

    char *sp;
    int i = 0;
    while (fgets(line, 1000, fp) != NULL){
        // printf("\n%s",line);
        i++;
    }   
    
    fclose(fp);

    // printf("%d\n",i);

    return i;
}


void EditUser(){
    FILE *fp;
    FILE *fpTemp;

    fp = fopen("database/User.csv","r");
    fpTemp = fopen("database/TempUser.csv","w");

    if(fp == NULL || fpTemp == NULL){
        printf("Error Opening File.\n");
        return;
    }
    
    User users[1000];
    User updateUser;
    User tempUser;
    char line[1000];    
    int found = 0;
    char targetUser[100];
    PrintUserData();

    char *sp;
    printf("Enter Name That You Want To Update\t:\t");
    fflush(stdin);
    yellow();
    fgets(targetUser, 50, stdin);
    reset();

    targetUser[strlen(targetUser)-1] = 0;
    bool keepReading = true;

    char buffer[MAX_LINE];

    while (fgets(line, 1000, fp) != NULL){
      
        sp = strtok(line, ",");
        strcpy(updateUser.userName, sp);

        sp = strtok(NULL, ",");
        strcpy(updateUser.password, sp);

        sp = strtok(NULL, ",");
        strcpy(updateUser.email, sp);

        sp = strtok(NULL, ",");
        strcpy(updateUser.phone, sp);
        
        sp = strtok(NULL, ",");
        strcpy(updateUser.role, sp);

        // printf("UserName %s\n",updateUser.userName);
        // printf("Password %s\n",updateUser.password);
        // printf("Email %s\n",updateUser.email);
        // printf("Phone %s\n",updateUser.phone);
        // printf("Role %s\n",updateUser.role);
        
        if(strcmp(targetUser, updateUser.userName) == 0){

            found = 1;

            printf("Current Value For Username Is \033[0;34m%s\033[0m \nPlease Enter New Value:\t", updateUser.userName);
            fflush(stdin);
            yellow();
            fgets(updateUser.userName, 50, stdin); 
            reset();
            updateUser.userName[strlen(updateUser.userName)-1] = 0;
            // scanf("%s", &updateUser.userName);

            printf("\nCurrent Value For Email Is \033[0;34m%s\033[0m \nPlease Enter New Value:\t", updateUser.email );
            yellow();
            scanf("%s", &updateUser.email);
            reset();

            printf("\nCurrent Value For Phone Is \033[0;34m%s\033[0m \nPlease Enter New Value:\t", updateUser.phone );
            yellow();
            scanf("%s", &updateUser.phone);
            reset();

            fprintf(fpTemp,
                "%s,%s,%s,%s,%s",
                updateUser.userName,
                updateUser.password,
                updateUser.email,
                updateUser.phone,
                updateUser.role
            );
        }

        else {
            fprintf(fpTemp,
                "%s,%s,%s,%s,%s",
                updateUser.userName,
                updateUser.password,
                updateUser.email,
                updateUser.phone,
                updateUser.role
            );
        }
    }
    
    fclose(fp);
    fclose(fpTemp);

    if(found == 1){
        fp = fopen("database/User.csv","w");
        fpTemp = fopen("database/TempUser.csv","r");

        while (fgets(line, 1000, fpTemp) != NULL){
            sp = strtok(line, ",");
            strcpy(tempUser.userName, sp);

            sp = strtok(NULL, ",");
            strcpy(tempUser.password, sp);

            sp = strtok(NULL, ",");
            strcpy(tempUser.email, sp);

            sp = strtok(NULL, ",");
            strcpy(tempUser.phone, sp);
            
            sp = strtok(NULL, ",");
            strcpy(tempUser.role, sp);
        
            fprintf(fp,
            "%s,%s,%s,%s,%s",
            tempUser.userName,
            tempUser.password,
            tempUser.email,
            tempUser.phone,
            tempUser.role
            );
        }
        fclose(fp);
        fclose(fpTemp);
        green();
        printf("Update User SuccessFully\n");
        reset();
    
    }
    else {
        printf("DATA NOT FOUND\n");
    }
}



void RemoveUser(){

    FILE *fp, *fpTemp;

    PrintUserData();

    int targetLine;
    fflush(stdin);
    printf("Enter Number Of User That You Want To Remove :\t");

    yellow();
    if(scanf("%d",&targetLine) != 1) {
        reset();
        system("clear");
        printf("Please Enter Correct Type\n");
        RemoveUser();
    }

    reset();
    
    fp = fopen("database/User.csv","r");
    fpTemp = fopen("database/TempUser.csv","w");

    if(fp == NULL || fpTemp == NULL){
        printf("FILE FORMAT ERROR\n");
        return;
    }

    char *sp;
    char line[1000];
    User updateUser;
    User tempUser;
    

    int i = 1;
    int found = 0;

    while (fgets(line, 1000, fp) != NULL){
        
        if(i == targetLine){

        }

        else {
            sp = strtok(line, ",");
            strcpy(tempUser.userName, sp);

            sp = strtok(NULL, ",");
            strcpy(tempUser.password, sp);

            sp = strtok(NULL, ",");
            strcpy(tempUser.email, sp);

            sp = strtok(NULL, ",");
            strcpy(tempUser.phone, sp);
            
            sp = strtok(NULL, ",");
            strcpy(tempUser.role, sp);

            found = 1;
            fprintf(fpTemp,
            "%s,%s,%s,%s,%s",
            tempUser.userName,
            tempUser.password,
            tempUser.email,
            tempUser.phone,
            tempUser.role
            );
        }

        i++;

    }

    fclose(fp);
    fclose(fpTemp);


    if(found == 1){
        fp = fopen("database/User.csv","w");
        fpTemp = fopen("database/TempUser.csv","r");

        while (fgets(line, 1000, fpTemp) != NULL){
           
            sscanf(line, "%s", &tempUser.userName);

            sp = strtok(line, ",");
            strcpy(tempUser.userName, sp);

            sp = strtok(NULL, ",");
            strcpy(tempUser.password, sp);

            sp = strtok(NULL, ",");
            strcpy(tempUser.email, sp);

            sp = strtok(NULL, ",");
            strcpy(tempUser.phone, sp);
            
            sp = strtok(NULL, ",");
            strcpy(tempUser.role, sp);
        
            fprintf(fp,
            "%s,%s,%s,%s,%s",
            tempUser.userName,
            tempUser.password,
            tempUser.email,
            tempUser.phone,
            tempUser.role
            );
        }
        fclose(fp);
        fclose(fpTemp);
        green();
        printf("Remove User Successfully\n");
        reset();
    }
    else {
        printf("\n----------------------------------------------\n");
        red();
        printf("                  DATA NOT FOUND     ");
        reset();
        printf("----------------------------------------------\n\n");
    }

    return;

}   


/* 

void RemoveUser(){
    
    FILE *fp, *fpTemp;

    char fileName[FILENAME_SIZE] = "database/User.csv";
    char tempFileName[FILENAME_SIZE];
    char buffer[MAX_LINE];
    int deleteLine = 0;
    PrintUserData();
    strcpy(tempFileName, "temp____");
    strcat(tempFileName, fileName);

    printf("Delete Line: ");
    fflush(stdin);
    scanf("%d",&deleteLine);

    fp = fopen(fileName, "r");
    fpTemp = fopen(tempFileName, "w");

    if(fp == NULL || fpTemp == NULL){
        printf("FILE FORMAT ERROR\n");
        return;
    }

    bool keepReading = true;
    int currentLine = 1;
    do{
        fgets(buffer, MAX_LINE, fp);
        if(feof(fp)) keepReading = false;
        else if(currentLine != deleteLine){
            fputs(buffer, fpTemp);
        }
        currentLine++;

    } while (keepReading);
    
    fclose(fp);
    fclose(fpTemp);

    remove(fileName);
    rename(tempFileName, fileName);
    return;

}   

 */