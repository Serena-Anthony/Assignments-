/*first name, last name, gender, date of bith, department and CGPA of fourth semester students*/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct student
{
    char fname[100];
    char lname[100];
    char gender;
    char birth[100];
    char dept[100];
    float cgpa;
    struct student* next;
 // cuz we creating linked list
};


