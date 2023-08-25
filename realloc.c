#include"shell.h"

/**
**_memset - fills memory with a constant byte
*@dest: the pointer to the memory area
*@ch: the byte to fill *dest with
*@n: the amount of bytes to be filled
*Return: (dest) a pointer to the memory area dest
*/
char*_memset(char *dest, char ch, unsigned int n)
{
	unsignedint i;

	for(i = 0; i < n; i++)
		dest[i]= ch;
	returndest;
}

/**
* free_string_array - frees an array of strings
* @arr: array of strings to free
*/
voidfree_string_array(char **arr)
{
	char**temp = arr;

	if(!arr)
		return;

	while(*arr)
		free(*arr++);

	free(temp);
}

/**
* custom_realloc - reallocates a block of memory
* @ptr: pointer to previous allocated block
* @old_size: byte size of previous block
* @new_size: byte size of new block
*
* Return: pointer to the reallocated block or NULL on failure.
*/
void*custom_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
	char*new_ptr;

	if(!ptr)
		returnmalloc(new_size);

	if(!new_size)
	{
		free(ptr);
		returnNULL;
	}

	if(new_size == old_size)
		returnptr;

	new_ptr= malloc(new_size);
	if(!new_ptr)
		returnNULL;

	old_size= old_size < new_size ? old_size : new_size;
	while(old_size--)
		new_ptr[old_size]= ((char *)ptr)[old_size];

	free(ptr);
	returnnew_ptr;
}
