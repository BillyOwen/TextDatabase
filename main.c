#include <stdio.h>
#include <stdlib.h>
#include "string32.h"
#include "member.h"


/*
Format:

FName:Greg,LName:Smith,ShoppingFrequency:7,ShoppingList:Watermelon|Milk|Pasta|Chicken\n
FName:,LName:,ShoppingFrequency:2,ShoppingList:\n



*/

int readDatabase(const char* databaseName, struct memberVector* members)
{
    FILE* fp;
    fp = fopen(databaseName, "r");

    char buffer[1024];
    
    while (fgets(buffer, 1024, fp))
    {
        struct Member member;
        if (convertTextToMember(buffer, 1024, &member)) return 1;
        memberVectorPush(members, member);
    }
    fclose(fp);
    return 0;
}

//Overwrites the database with the members vector
void updateDatabase(const char* databaseName, struct memberVector* members)
{
    FILE* fp;
    fp = fopen(databaseName, "w");

    for (int i = 0; i < members->length; ++i)
    {
        fprintf(fp, "ID:%d,FName:%s,LName:%s,ShoppingFrequency:%d,",members->value[i].ID,members->value[i].FName.value, members->value[i].LName.value, members->value[i].ShoppingFrequency);
        fprintf(fp, "ShoppingList:");
        for (int j = 0; j < members->value[i].ShoppingList.length; ++j)
        {
            if (j == members->value[i].ShoppingList.length - 1)
            {
                fprintf(fp, "%s\n",members->value[i].ShoppingList.value[j].value);
            }
            else
            {
                fprintf(fp, "%s|",members->value[i].ShoppingList.value[j].value);
            }   
        }
    }
    fclose(fp);
}


void printMembers(struct memberVector* members)
{
    for (int i = 0; i < members->length; ++i)
    {
        printf("%d\t%s\t%s\t%d\t",members->value[i].ID,members->value[i].FName.value,members->value[i].LName.value,members->value[i].ShoppingFrequency);
        for (int j = 0; j < members->value[i].ShoppingList.length; ++j)
        {
            printf("%s\t",members->value[i].ShoppingList.value[j].value);
        }
        printf("\n");
    }
    printf("\n");
}

void AddNewMember(struct memberVector* members, struct Member member)
{
    memberVectorPush(members, member);
}

int DeleteMember(struct memberVector* members, int id)
{
    for (int i = 0; i < members->length; ++i)
    {
        if (members->value[i].ID == id)
        {
            memberVectorRemove(members, i);
            return 0;
        }
    }
    return 1;
}

//Needs some thought
int UpdateMember(struct memberVector* members, int id, const char* field)
{

}
int main()
{

    struct memberVector members;
    memberVectorCreate(&members, 0);

    if (readDatabase("database.txt", &members)) return 1;

    printMembers(&members);

    DeleteMember(&members, 101);

    updateDatabase("database.txt", &members);
    memberVectorDelete(&members);


    return 0;
    
}