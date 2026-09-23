#include "cyber_cafe.h"
char isStrongPassword(char password[]){
    if(strlen(password)<8)
    return 0;
    int hasUpper=0,hasLower=0,hasDigit=0,hasSpecial=0;
    for(int i=0;password[i]!='\0';i++){
        if(isupper(password[i]))
        hasUpper=1;
        else if(islower(password[i]))
        hasLower=1;
        else if(isdigit(password[i]))
        hasDigit=1;
        else if(ispunct(password[i]))
        hasSpecial=1;
    }
        return (hasUpper && hasLower && hasDigit && hasSpecial);
}
int validInt(int *n){
    if(scanf("%d",n)!=1){
        int c;
        while((c=getchar())!='\n'&& c!=EOF);
        return 0;
    }
    int c;
    while((c=getchar())!='\n'&& c!=EOF);
    return 1;
}
float validFloat(float *n){
    if(scanf("%f",n)!=1){
        int c;
        while((c=getchar())!='\n'&& c!=EOF);
        return 0;
    }
    int c;
    while((c=getchar())!='\n'&& c!=EOF);
    return 1;
}
void UserRegister(){
    User u;
    FILE *fp=fopen("user.txt","a");
    if(fp==NULL){
        printf("Error! Cannot open user database\n");
        return;
    }
    printf("\n------USER REGISTRATION-------\n");
    printf("Enter new user name:");
    scanf(" %29[^\n]",u.user_name);
    if(strchr(u.user_name, ',') != NULL){
        printf("Invalid username! Username cannot contain commas.\n");
        fclose(fp);
        return;
    }
    while(1){
        printf("Enter new password:");
        scanf(" %29s",u.password);
        if(isStrongPassword(u.password))
        break;
        else{
            printf("\nWeak Password!Ensure your password must -\n");
            printf("1.Be at least 8 characters long\n");
            printf("2.Contain at least one upper case character(A-Z)\n");
            printf("3.Contain at least one lower case character(a-z)\n");
            printf("4.Contain at least one digit(0-9)\n");
            printf("5.Contain at least one special character(!,@,#,$,%%,etc.)\n");
        }
    }
    fprintf(fp,"%s,%s\n",u.user_name,u.password);
    fclose(fp);
    printf("\n***Registration Completed Successfully***\n");
}

int UserLogin(){
    User input_user,verify_user;
    FILE *fp=fopen("user.txt","r");
    if(fp==NULL){
        printf("No Registered User Found!\nPlease register first!\n");
        return 0;
    }
    printf("\n   ------USER LOGIN------\n");
    printf("Enter user name:");
    scanf(" %29[^\n]",input_user.user_name);
    printf("Enter password:");
    scanf(" %29s",input_user.password);
    if(strcmp(input_user.user_name,"Admin")==0 &&
            strcmp(input_user.password,"Admin007$")==0){
                fclose(fp);
                printf("\n***Admin Login Successful.***\n");
                return 2;
        }
    while((fscanf(fp," %29[^,\r\n],%29s",verify_user.user_name,verify_user.password))
            ==2){

        if(strcmp(input_user.user_name,verify_user.user_name)==0 &&
            strcmp(input_user.password,verify_user.password)==0){
                 fclose(fp);
                printf("\n***User Login Successful***.\n***Welcome %s***\n",input_user.user_name);
                return 1;
            }
    }
    fclose(fp);
    printf("\n---Invalid username or password! Login failed.---\n");
    return 0;
}
void displayPCstatus(){
    int PCstatus[Max_PC+1]={0};
    FILE *fp=fopen("session.txt","r");
    if(fp!=NULL){
        computer temp;
        while(fscanf(fp," %49[^\n]\n%d %f %d",temp.customer_name,&temp.computer_number,
            &temp.duration,&temp.computer_type)==4){
                 if(temp.computer_number>=1 && temp.computer_number<=Max_PC){
                   PCstatus[temp.computer_number]=1;
            }
        }
     fclose(fp);
    }
     int count=0;
     printf("\n===========================================\n");
     printf("               PC STATUS BOARD             \n");
     printf("\n===========================================\n");
        for(int i=1;i<=Max_PC;i++){
            if(PCstatus[i]==1){
                printf("[ PC %02d :UNAVAILABLE ]",i);
                count++;
            }
            else{
                printf("[ PC %02d :AVAILABLE ]",i);
            }
            if(i%2==0){
                printf("\n");
            }
        }
        printf("\n----------------------------------------------\n");
        printf("Total Unavailable:%d/%d | Total available:%d\n",count,Max_PC,Max_PC-count);
        printf("==============================================\n");
}
int isPCavailable(int PC_No){
    FILE *fp=fopen("session.txt","r");
    if(fp==NULL){
       return 0;
    }
    computer temp;
    while(fscanf(fp," %49[^\n]\n%d %f %d",temp.customer_name,&temp.computer_number,
            &temp.duration,&temp.computer_type)==4){
                 if(temp.computer_number==PC_No){
                    fclose(fp);
                    return 1;
             }
        }
        fclose(fp);
        return 0;
}
void Bill(int n,float duration){
    float amount=0.0;
    if(n==1){
        amount+=100*duration;
        printf("Total Amount :%.2f/-\n",amount);
    }
    else if(n==2){
        amount+=200*duration;
        printf("Total Amount :%.2f/-\n",amount);
    }
    else{
        printf("Invalid choice!Must choose  1 or 2!");
    }
}
void addsession(){
    computer temp;
    FILE *fp=fopen("session.txt","a");
    if(fp==NULL){
        printf("Error opening session file!\n");
        return;
    }
        printf("\n  ------ADD NEW SESSION------\n");
        printf("Enter name:");
        scanf(" %49[^\n]",temp.customer_name);
        printf("Enter computer number(%d - %d):", Min_PC , Max_PC);
        if(!validInt(&temp.computer_number)){
            printf("Invalid Input! PC no must be a number!\n");
            fclose(fp);
            return;
        }
        if(temp.computer_number<Min_PC || temp.computer_number>Max_PC){
            printf("\nInvalid Number! We Have Only (%d - %d) PC Available!\n",Min_PC,Max_PC);
            fclose(fp);
            return;
        }
        if(isPCavailable(temp.computer_number)){
            printf("\nERROR! PC No.%d is not available.Please choose another PC\n",temp.computer_number);
            fclose(fp);
            return;
        }
        printf("Enter duration(hrs):");
        if(!validFloat(&temp.duration) || temp.duration <= 0){
            printf("Invalid Input! Duration must be a positive number!\n");
            fclose(fp);
            return;
        }
        printf("Enter  computer type(1:Basic,2:Gaming):");
        if(!validInt(&temp.computer_type) || (temp.computer_type != 1 && temp.computer_type != 2)){
            printf("Invalid Input! Must choose 1 or 2!\n");
            fclose(fp);
            return;
        }
    fprintf(fp,"%s\n%d %.2f %d\n",temp.customer_name,temp.computer_number,
            temp.duration,temp.computer_type);
            Bill(temp.computer_type,temp.duration);
            fclose(fp);
            printf("\n***Added new session successfully***\n");
}
void ViewSession(){
    computer temp;
    FILE *fp=fopen("session.txt","r");
    if(fp==NULL){
        printf("Error! No session found!\n");
        return;
    }
    char type[10];
    int count = 0;
     printf("\n------VIEW SESSION------\n");
    printf("\n===================================\n");
    while(fscanf(fp," %49[^\n]\n%d %f %d",temp.customer_name,&temp.computer_number,
            &temp.duration,&temp.computer_type)==4){
                count++;
                if(temp.computer_type==1) strcpy(type,"Basic");
                else strcpy(type,"Gaming");
                printf("Customer Name:%s\n",temp.customer_name);
                printf("PC NO        :%d\n",temp.computer_number);
                printf("Duration(hr) :%.2f hr\n",temp.duration);
                printf("Computer type:%s\n",type);
                Bill(temp.computer_type,temp.duration);
                printf("\n");
            }
    if(count == 0){
        printf("No active sessions found.\n\n");
    }
    printf("\n====================================\n");
    fclose(fp);
}
void searchSession(){
    computer temp;
    int found=0,PC_no;
    FILE *fp=fopen("session.txt","r");
    if(fp==NULL){
        printf("Error! No session record found!\n");
        return;
    }
    printf("Enter PC No. (%d-%d):",Min_PC,Max_PC);
    if(!validInt(&PC_no)){
        printf("Invalid Input! Must be a number!\n");
        fclose(fp);
        return;
    }
    if(PC_no<Min_PC || PC_no>Max_PC){
            printf("\nInvalid Number! We Have Only (%d - %d) PC Available!\n",Min_PC,Max_PC);
            fclose(fp);
            return;
        }
        char type[10];
    while(fscanf(fp," %49[^\n]\n%d %f %d",temp.customer_name,&temp.computer_number,
            &temp.duration,&temp.computer_type)==4){
                if(temp.computer_type==1) strcpy(type,"Basic");
                else strcpy(type,"Gaming");
                 if(temp.computer_number==PC_no){
                 printf("\n------SEARCH SESSION------\n");
                printf("Customer Name:%s\n",temp.customer_name);
                printf("PC NO        :%d\n",temp.computer_number);
                printf("Duration(hr) :%.2f hr\n",temp.duration);
                printf("Computer type:%s\n",type);
                Bill(temp.computer_type,temp.duration);
                found=1;
                break;
            }
        }
    if(!found){
        printf("\n------No session found for this PC------\n");
    }
    fclose(fp);
}
void deleteSession(){
    computer temp;
    FILE *fp=fopen("session.txt","r");
    FILE *newFp=fopen("newSession.txt","w");
    if(fp==NULL || newFp==NULL){
        printf("Error! No session record found to delete!\n");
         if(fp) fclose(fp);
         if(newFp) fclose(newFp);
        return;
    }
    int delete_PC,found=0;
     printf("\n------DELETE SESSION------\n");
    printf("Enter PC No. to delete (%d-%d):",Min_PC,Max_PC);
    if(!validInt(&delete_PC))
    {
        printf("Invalid Input! Must be a number!\n");
        fclose(fp);
        fclose(newFp);
        remove("newSession.txt");
        return;
    }
    if(delete_PC<Min_PC || delete_PC>Max_PC){
            printf("\nInvalid Number! We Have Only (%d - %d) PC Available!\n",Min_PC,Max_PC);
            fclose(fp);
            fclose(newFp);
            remove("newSession.txt");
            return;
        }
    while(fscanf(fp," %49[^\n]\n%d %f %d",temp.customer_name,&temp.computer_number,
            &temp.duration,&temp.computer_type)==4){
                 if(temp.computer_number==delete_PC){
                   found=1;
                }
                else{
                    fprintf(newFp,"%s\n%d %.2f %d\n",temp.customer_name,temp.computer_number,
            temp.duration,temp.computer_type);
                }
        }
        fclose(fp);
        fclose(newFp);
        remove("session.txt");
        rename("newSession.txt","session.txt");
    if(found){
        printf("\n------Successfully deleted session for PC NO.%d------\n",delete_PC);
    }
    else{
        printf("\nPC NO.%d not found\n",delete_PC);
    }
}
void updateSession(){
    computer temp;
    FILE *fp=fopen("session.txt","r");
    FILE *newFp=fopen("newSession.txt","w");
    if(fp==NULL || newFp==NULL){
        printf("Error! No session record found to update!\n");
        if(fp) fclose(fp);
        if(newFp) fclose(newFp);
        return;
    }
    int target_PC,found=0;
    printf("Enter PC No. to update (%d-%d):",Min_PC,Max_PC);
    if(!validInt(&target_PC)){
        printf("Invalid Input! Must be a number!\n");
        fclose(fp);
        fclose(newFp);
        remove("newSession.txt");
        return;
    }
    if(target_PC<Min_PC || target_PC>Max_PC){
            printf("\nInvalid Number! We Have Only (%d - %d) PC Available!\n",Min_PC,Max_PC);
            fclose(fp);
            fclose(newFp);
            remove("newSession.txt");
            return;
        }
     printf("\n------UPDATE SESSION------\n");
    char type[10];
    while(fscanf(fp," %49[^\n]\n%d %f %d",temp.customer_name,&temp.computer_number,
            &temp.duration,&temp.computer_type)==4){
                 if(temp.computer_number==target_PC){
                   found=1;
                   if(temp.computer_type==1) strcpy(type,"Basic");
                else strcpy(type,"Gaming");
                printf("---Current Details For PC No.%d---\n",target_PC);
                printf("Customer Name:%s\n",temp.customer_name);
                printf("PC NO        :%d\n",temp.computer_number);
                printf("Duration(hr) :%.2f hr\n",temp.duration);
                printf("Computer type:%s\n",type);
                Bill(temp.computer_type,temp.duration);
                printf("\n--------------------------------------\n");
                printf("Enter new customer name:");
                scanf(" %49[^\n]",temp.customer_name);
                printf("Enter new computer number(%d - %d):", Min_PC, Max_PC);
                if(!validInt(&temp.computer_number)){
                    printf("Invalid Input! PC no must be a number!\n");
                    fclose(fp);
                    fclose(newFp);
                    remove("newSession.txt");
                    return;
                }
                if(temp.computer_number<Min_PC || temp.computer_number>Max_PC){
                    printf("\nInvalid Number! We Have Only (%d - %d) PC Available!\n",Min_PC,Max_PC);
                    fclose(fp);
                    fclose(newFp);
                    remove("newSession.txt");
                    return;
                }
                if(temp.computer_number != target_PC && isPCavailable(temp.computer_number)){
                    printf("\nERROR! PC No.%d is already in use.\n",temp.computer_number);
                    fclose(fp);
                    fclose(newFp);
                    remove("newSession.txt");
                    return;
                }
                printf("Enter new duration(hrs):");
                if(!validFloat(&temp.duration) || temp.duration <= 0){
                    printf("Invalid Input! Duration must be a positive number!\n");
                    fclose(fp);
                    fclose(newFp);
                    remove("newSession.txt");
                    return;
                }
                printf("Enter new computer type(1:Basic,2:Gaming):");
                if(!validInt(&temp.computer_type) || (temp.computer_type != 1 && temp.computer_type != 2)){
                    printf("Invalid Input! Must choose 1 or 2!\n");
                    fclose(fp);
                    fclose(newFp);
                    remove("newSession.txt");
                    return;
                }
                fprintf(newFp,"%s\n%d %.2f %d\n",temp.customer_name,temp.computer_number,
                    temp.duration,temp.computer_type);
                Bill(temp.computer_type,temp.duration);
                }

                else{
                    fprintf(newFp,"%s\n%d %.2f %d\n",temp.customer_name,temp.computer_number,
            temp.duration,temp.computer_type);
                }
        }
        fclose(fp);
        fclose(newFp);
        remove("session.txt");
        rename("newSession.txt","session.txt");
    if(found){
        printf("\n------Successfully updated session for PC NO.%d------\n",target_PC);
    }
    else{
        printf("\nPC NO.%d not found\n",target_PC);
    }
}
void revenueReport(){
    computer temp;
    FILE *fp=fopen("session.txt","r");
    if(fp==NULL){
        printf("Error!No Report Found!\n");
        return;
    }
    int totalSession=0;
    float totalRevenue=0.0;
    while(fscanf(fp," %49[^\n]\n%d %f %d",temp.customer_name,&temp.computer_number,
            &temp.duration,&temp.computer_type)==4){
                float bill=0.0;
                if(temp.computer_type==1){
                    bill=100*temp.duration;
                }
                else{
                    bill=200*temp.duration;
                }
                totalRevenue+=bill;
                totalSession++;
            }
            fclose(fp);
            printf("\n==================================\n");
            printf("          REVENUE REPORT          \n");
            printf("\n==================================\n");
            printf("Total sessions:%d\n",totalSession);
            printf("Total revenue :%.2f/-\n",totalRevenue);
            printf("\n=================================\n");
}


