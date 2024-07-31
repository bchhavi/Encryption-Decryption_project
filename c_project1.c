#include<stdio.h>
#include<stdlib.h>
#include <string.h>
#include<windows.h>


int length(char temp[]){
    for(int i = 0; ; i++){
        if(temp[i] == '\0')
        return i;
    }
}

//encrypting the data by changing the ASCII values
char* encrypt(char key[]){
    int len = length(key);
    for(int i = 0; i < len; i++){
        key[i] = key[i] + 100;
    }
    return key;
}

//decrypting the data
char* decrypt(char key[]){
    int len = length(key);
    for(int i = 0; i < len; i++){
        key[i] = key[i] - 100;
    }
    return key;
}

//create file using some existing data
FILE* create_File(FILE* fp){
    char names[][20] = {"Ayush Gautam",
                        "Ayush Soni",
                        "Ashwani Kumar",
                        "Chaavi Kumari",
                        "Biswamohan Jena",
                        "Deepak Kishore",
                        "Jaya Lalitha",
                        "Himanshu MME",
                        "Hirakjyoti Deka"
                        };
    char email_ids[][40] = {"ayushgautam@gmail.com",
                            "ayushsoni@outlook.com",
                            "ahwanijha@hotmail.com",
                            "chaavi12345@hotmail.com",
                            "biswamohanjenna@outlook.com",
                            "deepak123@gamil.com",
                            "lalitha987@outlook.com",
                            "himanshumme@gmail.com",
                            "hiracivil123@gmail.com"};
    char passwords[][20] = {"password1",
                            "password2",
                            "password3",
                            "password4",
                            "password5",
                            "password6",
                            "password7",
                            "password8",
                            "password9",
                            };
    char enc_keys[][20] = {"ayushKey",
                           "soniKey",
                           "ashwaniKey",
                           "chaaviKey",
                           "biswaKey",
                           "deepakKey",
                           "lalithaKey",
                           "himanshuKey",
                           "hiraKey"
                           };
    for(int i = 0; i < 9; i++){
        fputs("\n", fp);
        fputs("Name: ", fp);
        fputs(names[i], fp);
        fputs("\n", fp);
        fputs("Email ID: ", fp);
        fputs(encrypt(email_ids[i]), fp);
        fputs("\n", fp);
        fputs("Password: ", fp);
        fputs(encrypt(passwords[i]), fp);
        fputs("\n", fp);
        fputs("Encryption Key: ", fp);
        fputs(encrypt(enc_keys[i]), fp);
        fputs("\n", fp);
    }
    return fp;
}

//compare the two strings
int strcomp(char* x, char* y, int lenx, int leny){
    for(int i = 0; i < lenx && i < leny; i++){
        if((int)x[i] > (int)y[i])
        return -1;
        if((int)x[i] < (int)y[i])
        return 1;
    }
    if(lenx == leny)
    return 0;
    else if(lenx > leny)
    return -1;
    else
    return 1;
}

//tranverses the file for the given name and print the data
void traverse_file(FILE* fp, char name[], char sname[]){
    char data[100];
    int flag = 1;
    for(; !feof(fp); ){
        fgets(data, 100, fp);
        if(strstr(data, name) != NULL && strstr(data, sname) != NULL){
            flag = 0;
            char temp[3][100]; //array to store the data
            for(int j = 0; j < 3; j++){
                fgets(data, 100, fp);
                char* pos1 = strstr(data, ":");  //memory location of :
                char* pos2 = strstr(data, "\n"); // memory location of \n
                int index1 = pos1 - data + 1;
                int index2 = pos2 - data ;
                strncpy(temp[j], data + index1 + 1, index2);  //cuts the data from the required indexes and paste it into temp
                decrypt(temp[j]);
            }
            char key[20];
            int count  = 0;
      A:    printf("Enter the encryption key: ");
            scanf("%s", key);
            
            //check the required encryption key and then display the data
          if(strcomp(key, temp[2], length(key), length(temp[2]) - 1) == 0){
                printf("------------------------------\n");
                printf("Decrypted data: \n");
                printf("------------------------------\n");
                Sleep(1000);
                printf("Email: %s\n", temp[0]);
                Sleep(10);
                printf("Password: %s\n", temp[1]);
                Sleep(10);
                printf("Encryption key: %s\n", temp[2]);
                Sleep(10);
                printf("------------------------------\n");
                printf("------------------------------\n");
                Sleep(1000);
            }
            else{
                Sleep(100);
                count++;
                if(count <= 3){
                    printf("WRONG KEY!!!!\nTry Again.\n");
                    goto A;
                }
                else
                printf("Maximum attempts reached. Try again later.\n");
            }
        }
    }
    if(flag)
    printf("Required query not found!!\n");
}

//apppends the new data in the file
FILE* append(FILE* fp, char name[], char sname[], char email[], char password[], char key[]){
    fputs("\n", fp);
    fputs("Name: ", fp);
    fputs(name, fp);
    fputc(' ', fp);
    fputs(sname, fp);
    fputs("\n", fp);
    fputs("Email ID: ", fp);
    fputs(encrypt(email), fp);
    fputs("\n", fp);
    fputs("Password: ", fp);
    fputs(encrypt(password), fp);
    fputs("\n", fp);
    fputs("Encryption Key: ", fp);
    fputs(encrypt(key), fp);
    fputs("\n", fp);

    return fp;
}

//will display all the content of the file
void display(FILE* fp){
    char data[100];
    fgets(data, 100, fp);
    for(;!feof(fp);fgets(data, 100, fp)){
        printf("%s", data);
        Sleep(1);
    }
    printf("\n");
}

int main(){
    FILE* fp;
    char loc[] = {"C:\\project.txt"};  //contains the file location
    fp = fopen(loc, "r");
    if(fp == NULL)  //if file not present then make it using the given data through create_FIle function
    {
        fp = fopen(loc, "w");
        fp = create_File(fp);
        fclose(fp);
    }
    int choice;
    A:
    //choice of operations that the user can take
    printf("Enter the index of the operation you want to perform:\n1 -> For extracting saved data.");
    printf("\n2 -> For appending new data.\n3 -> For viewing all the encrypted data.\n4 -> To exit.\n");
    printf("Your choice: ");
    scanf("%d", &choice);
    if(choice == 1){
        fp = fopen(loc, "r");
        char name[50];
        char sname[50];
        printf("Write name: ");
        scanf("%s %s", name, sname);
        traverse_file(fp , name, sname);
        fclose(fp);
        goto A;
    }
    if(choice == 2){
        fp = fopen(loc, "a");
        char name[20];
        char sname[20];
        char email[40];
        char pass[20];
        char key[20];
        printf("Write name: ");
        scanf("%s %s", name, sname);
        printf("Write email: ");
        scanf("%s", email);
        printf("Write password: ");
        scanf("%s", pass);
        printf("Write key: ");
        scanf("%s", key);
        fp = append(fp, name, sname, email, pass, key);
        fclose(fp);
        goto A;
    }
    if(choice == 3){
        fp = fopen(loc, "r");
        display(fp);
        fclose(fp);
        goto A;
    }
    if(choice == 4)
    fclose(fp);
    else{
        printf("Enter a valid choice.\n");
        goto A;
    }

    return 0;
}