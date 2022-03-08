#include <stdio.h>
#include <stdlib.h>
#include "string32.h"
#include "member.h"


/*
Database Format:   (Can be changed without much difficulty)

FName:Greg,LName:Smith,ShoppingFrequency:7,ShoppingList:Watermelon|Milk|Pasta|Chicken\n

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
            fprintf(fp, "%s",members->value[i].ShoppingList.value[j].value);
            if (j != members->value[i].ShoppingList.length - 1)
            {
                fprintf(fp,"|");
            }
        }
        fprintf(fp,"\n");
    }
    fclose(fp);
}


int main()
{

    struct memberVector members;
    memberVectorCreate(&members, 0);

    if (readDatabase("database.txt", &members)) return 1;

    printMembers(&members);

    //UpdateMemberAddItemToShoppingList(&members, 103, "Lollies");
    //UpdateMemberRemoveItemFromShoppingList(&members, 103, "Lollies");
    //UpdateMemberClearShoppingList(&members, 102);
    //UpdateMemberFirstName(&members, 102, "Sandra");
    UpdateMemberShoppingFrequency(&members, 102, 3);

    updateDatabase("database.txt", &members);
    memberVectorDelete(&members);


    return 0;
    
}
