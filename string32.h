//This exists so I don't have a bunch of double char pointers

struct String32
{
    char value[32];
};


//Vector Stuff
struct String32Vector
{
	struct String32* value;
	unsigned int size; //Actual size
	unsigned int length; //Used size
};

int string32VectorCreate(struct String32Vector* vector, unsigned int size)
{
    unsigned int Size = size;
    if (size == 0) Size = 10;
	vector->value = (struct String32*) malloc(Size * sizeof(struct String32));
	if (!vector->value) return 0;
	vector->size = Size;
	vector->length = size;
	return size;
}
//Free the vector
void string32VectorDelete(struct String32Vector* vector)
{
	vector->size = 0;
	vector->length = 0;
	free(vector->value);
}

//Add item to end
struct String32 string32VectorPush(struct String32Vector* vector, struct String32 value)
{
	if (vector->length >= vector->size)
	{
		vector->size <<= 1;
		vector->value = (struct String32*) realloc(vector->value, vector->size * sizeof(struct String32));
	}
	vector->value[vector->length] = value;
	vector->length++;
	return value;
}
//Insert an element at an index
struct String32 string32VectorInsert(struct String32Vector* vector, int index, struct String32 value)
{
	if (vector->length >= vector->size)
	{
		vector->size <<= 1;
		vector->value = (struct String32*) realloc(vector->value, vector->size * sizeof(struct String32));
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
struct String32 string32VectorPop(struct String32Vector* vector)
{
	struct String32 returnValue = vector->value[vector->length-1];
	if (vector->length < vector->size >> 1)
	{
		vector->size >>= 1;
		vector->value = (struct String32*) realloc(vector->value, vector->size * sizeof(struct String32));
	}
	vector->length--;
	return returnValue;
}
//Delete any element at location index
struct String32 string32VectorRemove(struct String32Vector* vector, unsigned int index)
{
	struct String32 returnValue = vector->value[index];

	if (vector->length < vector->size >> 1)
	{
		vector->size >>= 1;
		vector->value = (struct String32*) realloc(vector->value, vector->size * sizeof(struct String32));
	}
	vector->length--;

	for (int i = index; i < vector->length; ++i)
	{
		vector->value[i] = vector->value[i+1];
	}

	return returnValue;
}
