
/*
Database Format:   (Can be changed without much difficulty)

FName:Greg,LName:Smith,ShoppingFrequency:7,ShoppingList:Watermelon|Milk|Pasta|Chicken\n

*/


struct Member {
    int ID;
    struct String32 FName;
    struct String32 LName;
    int ShoppingFrequency;
    struct String32Vector ShoppingList;
};


void createMember(struct Member* member, int ID, struct String32 FName, struct String32 LName, int ShoppingFrequency, struct String32Vector ShoppingList)
{
    member->ID = ID;
    member->FName = FName;
    member->LName = LName;
    member->ShoppingFrequency = ShoppingFrequency;
    member->ShoppingList = ShoppingList;
}


int convertTextToMember(char* string, unsigned int stringLength, struct Member* member)
{
    
    unsigned int startPointer = 0;
    unsigned int i;

    //ID
    if (stringLength < startPointer + 2)
    {
        printf("ID Error 1");
        return 1;
    }
    if (!(string[startPointer+0] == 'I' && string[startPointer+1] == 'D' && string[startPointer+2] == ':'))
    {
        printf("ID Error 2");
        return 1;
    }
    startPointer += 3;

    struct String32 convert;
    for (i = 0; i < 32 - 1; ++i)
    {
        if (string[startPointer + i] == ',')
            break;
        convert.value[i] = string[startPointer + i];
    }
    convert.value[i] = '\0';
    int ID = atoi(convert.value);

    startPointer += i + 1;


    //FName:
    if (stringLength < startPointer + 5)
    {
        printf("FNAME Error 1");
        return 1;
    }
    struct String32 FName;
    if (!(string[startPointer+0] == 'F' && string[startPointer+1] == 'N' && string[startPointer+2] == 'a' && string[startPointer+3] == 'm' && string[startPointer+4] == 'e' && string[startPointer+5] == ':'))
    {
        printf("FNAME Error 2");
        return 1;
    }
    startPointer += 6;
    
    for (i = 0; i < 32 - 1; ++i)
    {
        if (string[startPointer + i] == ',')
            break;
        FName.value[i] = string[startPointer + i];
    }
    FName.value[i] = '\0';
    startPointer += i + 1;

    
    //LName
    if (stringLength < startPointer + 5)
    {
        printf("LNAME Error 1");
        return 1;
    }
    struct String32 LName;
    if (!(string[startPointer] == 'L' && string[startPointer+1] == 'N' && string[startPointer+2] == 'a' && string[startPointer+3] == 'm' && string[startPointer+4] == 'e' && string[startPointer+5] == ':'))
    {
        printf("LNAME Error 2");
        return 1;
    }

    startPointer += 6;
    for (i = 0; i < 32 - 1; ++i)
    {
        if (string[startPointer + i] == ',')
            break;
        LName.value[i] = string[startPointer + i];
    }
    LName.value[i] = '\0';
    startPointer += i + 1;

    
    //ShoppingFrequency
    if (stringLength < startPointer + 17)
    {
        printf("ShoppingFrequency Error 1");
        return 1;
    }
    if (!(string[startPointer] == 'S' && string[startPointer+1] == 'h' && string[startPointer+2] == 'o' && string[startPointer+3] == 'p' && string[startPointer+4] == 'p' && string[startPointer+5] == 'i' && string[startPointer+6] == 'n' && string[startPointer+7] == 'g' && string[startPointer+8] == 'F' && string[startPointer+9] == 'r' && string[startPointer+10] == 'e' && string[startPointer+11] == 'q' && string[startPointer+12] == 'u' && string[startPointer+13] == 'e' && string[startPointer+14] == 'n' && string[startPointer+15] == 'c' && string[startPointer+16] == 'y' && string[startPointer+17] == ':'))
    {
        printf("ShoppingFrequency Error 2");
        return 1;
    }

    startPointer += 18;
    for (i = 0; i < 32 - 1; ++i)
    {
        if (string[startPointer + i] == ',')
            break;
        convert.value[i] = string[startPointer + i];
    }
    convert.value[i] = '\0';
    int ShoppingFrequency = atoi(convert.value);

    startPointer += i + 1;
    
    //ShoppingList
    if (stringLength < startPointer + 12)
    {
        printf("ShoppingList Error 1");
        return 1;
    }
    struct String32Vector ShoppingList;
    string32VectorCreate(&ShoppingList, 0);

    if (!(string[startPointer] == 'S' && string[startPointer+1] == 'h' && string[startPointer+2] == 'o' && string[startPointer+3] == 'p' && string[startPointer+4] == 'p' && string[startPointer+5] == 'i' && string[startPointer+6] == 'n' && string[startPointer+7] == 'g' && string[startPointer+8] == 'L' && string[startPointer+9] == 'i' && string[startPointer+10] == 's' && string[startPointer+11] == 't' && string[startPointer+12] == ':'))
    {
        printf("ShoppingList Error 2");
        return 1;
    }

    startPointer += 13;
    
    while (string[startPointer] != EOF && string[startPointer] != '\n')
    {
        struct String32 item;
        unsigned int len = 0;
        while (string[startPointer] != '|')
        {
            
            if (string[startPointer] == EOF || string[startPointer] == '\n')
            {
                item.value[len] = '\0';
                string32VectorPush(&ShoppingList, item);
                goto endList;
            }
            item.value[len] = string[startPointer];
            len++;
            startPointer++;
        }
        
        item.value[len] = '\0';
        string32VectorPush(&ShoppingList, item);
        startPointer++;
    }
    endList:
    createMember(member, ID, FName, LName, ShoppingFrequency, ShoppingList);
    return 0;
}



//Vector Stuff
struct memberVector
{
	struct Member* value;
	unsigned int size; //Actual size
	unsigned int length; //Used size
};

int memberVectorCreate(struct memberVector* vector, unsigned int size)
{
    unsigned int Size = size;
	if (size == 0) Size = 10;
	vector->value = (struct Member*) malloc(Size * sizeof(struct Member));
	if (!vector->value) return 0;
	vector->size = Size;
	vector->length = size;
	return size;
}
//Free the vector
void memberVectorDelete(struct memberVector* vector)
{
	vector->size = 0;
	vector->length = 0;
	free(vector->value);
}

//Add item to end
struct Member memberVectorPush(struct memberVector* vector, struct Member value)
{
	if (vector->length >= vector->size)
	{
		vector->size <<= 1;
		vector->value = (struct Member*) realloc(vector->value, vector->size * sizeof(struct Member));
	}
	vector->value[vector->length] = value;
	vector->length++;
	return value;
}
//Insert an element at an index
struct Member memberVectorInsert(struct memberVector* vector, int index, struct Member value)
{
	if (vector->length >= vector->size)
	{
		vector->size <<= 1;
		vector->value = (struct Member*) realloc(vector->value, vector->size * sizeof(struct Member));
	}
	for (int i = vector->length; i > index; --i)
	{
		vector->value[i] = vector->value[i-1];
	}
	vector->value[index] = value;
	vector->length++;
	return value;
}

//Pop off last element  (DO NOT POP EMTPTY VECTOR)
struct Member memberVectorPop(struct memberVector* vector)
{
	struct Member returnValue = vector->value[vector->length-1];
	if (vector->length < vector->size >> 1)
	{
		vector->size >>= 1;
		vector->value = (struct Member*) realloc(vector->value, vector->size * sizeof(struct Member));
	}
	vector->length--;
	return returnValue;
}
//Delete any element at location index
struct Member memberVectorRemove(struct memberVector* vector, unsigned int index)
{
	struct Member returnValue = vector->value[index];

	if (vector->length < vector->size >> 1)
	{
		vector->size >>= 1;
		vector->value = (struct Member*) realloc(vector->value, vector->size * sizeof(struct Member));
	}
	vector->length--;

	for (int i = index; i < vector->length; ++i)
	{
		vector->value[i] = vector->value[i+1];
	}

	return returnValue;
}



//Database operations

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


//Also add a way to add which handles IDs
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

//Returns 0 on success, 1 if member not found
int UpdateMemberFirstName(struct memberVector* members, int id, const char string[])
{
    for (int i = 0; i < members->length; ++i)
    {
        if (members->value[i].ID == id)
        {
            string32Create(&members->value[i].FName, string);
            return 0;
        }
    }
    return 1;
}

//Returns 0 on success, 1 if member not found
int UpdateMemberLastName(struct memberVector* members, int id, const char string[])
{
    for (int i = 0; i < members->length; ++i)
    {
        if (members->value[i].ID == id)
        {
            string32Create(&members->value[i].LName, string);
            return 0;
        }
    }
    return 1;
}

//Returns 0 on success, 1 if member not found
int UpdateMemberShoppingFrequency(struct memberVector* members, int id, int shoppingFrequency)
{
    for (int i = 0; i < members->length; ++i)
    {
        if (members->value[i].ID == id)
        {
            members->value[i].ShoppingFrequency = shoppingFrequency;
            return 0;
        }
    }
    return 1;
}

//Returns 0 on success, 1 if member not found
int UpdateMemberClearShoppingList(struct memberVector* members, int id)
{
    for (int i = 0; i < members->length; ++i)
    {
        if (members->value[i].ID == id)
        {
            int length = members->value[i].ShoppingList.length;
            for (int j = 0; j < length; ++j)
            {
                string32VectorPop(&members->value[i].ShoppingList);
            }
            return 0;
        }
    }
    return 1;
}

//Returns 0 on success, 1 if item already on list and 2 if member not found
int UpdateMemberAddItemToShoppingList(struct memberVector* members, int id, const char item[])
{
    for (int i = 0; i < members->length; ++i)
    {
        if (members->value[i].ID == id)
        {
            //Check if it is there
            for (int j = 0; j < members->value[i].ShoppingList.length; ++j)
            {
                if (compareStrings(members->value[i].ShoppingList.value[j].value, item))
                {
                    return 1;
                }
            }
            //Add it
            struct String32 newItem;
            string32Create(&newItem, item);
            string32VectorPush(&(members->value[i].ShoppingList), newItem);
            return 0;
        }
    }
    return 2;
}
//Returns 0 on success, 1 if member found but not item and 2 if member not found
int UpdateMemberRemoveItemFromShoppingList(struct memberVector* members, int id, const char item[])
{
    for (int i = 0; i < members->length; ++i)
    {
        if (members->value[i].ID == id)
        {
            for (int j = 0; j < members->value[i].ShoppingList.length; ++j)
            {
                if (compareStrings(item, members->value[i].ShoppingList.value[j].value))
                {
                    string32VectorRemove(&members->value[i].ShoppingList, j);
                    return 0;
                }
            }
            return 1;
        }
    }
    return 2;
}



