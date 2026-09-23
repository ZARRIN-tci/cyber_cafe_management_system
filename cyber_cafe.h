#ifndef CYBER_CAFE_H
#define CYBER_CAFE_H
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#define Min_PC 1
#define Max_PC 20
typedef struct{
    char customer_name[50];
    int computer_number;
    float duration;
    int computer_type;
}computer;

typedef struct{
    char user_name[30];
    char password[30];
}User;

char isStrongPassword(char password[]);
int validInt(int *n);
float validFloat(float *n);
void UserRegister();
int UserLogin();
void displayPCstatus();
int isPCavailable(int PC_No);
void Bill(int n, float duration);
void addsession();
void ViewSession();
void searchSession();
void deleteSession();
void updateSession();
void revenueReport();

#endif
