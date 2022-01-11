#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>

typedef struct dynarray
{
    size_t number_of_elements;
    size_t size_of_elements;
    size_t capacity;
    uint8_t *data; //non usiamo void* perche' non sappiamo quale dato sia, si usa uint8 per far in modo che sia piu' leggero
    uint8_t *tmp_data;
} dynarray_t;

int dynarray_init(dynarray_t *array, const size_t size_of_elements)
{
    array->number_of_elements = 0;
    array->size_of_elements = size_of_elements;
    array->capacity = 0;
    array->data = NULL;
    array->tmp_data = malloc(size_of_elements);
    if (!array->tmp_data)
    {
        return -1;
    }
    return 0;
}

#define dynarray_init_type(array, type) dynarray_init(array, sizeof(type))

void dynarray_clear(dynarray_t *array)
{
    array->number_of_elements = 0;
    free(array->data);
    array->data = NULL;
    free(array->tmp_data);
    array->tmp_data = NULL;
}

int dynarray_append(dynarray_t *array, const void *value)
{
    const size_t new_size = array->number_of_elements + 1;
    // check if capacity is enought for add new element (if is enought realloc not needed)
    uint8_t *new_ptr;
    if (array->capacity <= new_size * array->size_of_elements)
    {
        new_ptr = realloc(array->data, new_size * array->size_of_elements);
        array->capacity = new_size * array->size_of_elements;


        if (!new_ptr)
        {
            return -1;
        }
        else
        {
            array->data = new_ptr;
        }
    }
   
    size_t offset = array->number_of_elements * array->size_of_elements;
    memcpy(array->data + offset, value, array->size_of_elements);
    array->number_of_elements = new_size;

    return 0;
}

size_t dynarray_len(const dynarray_t *array)
{
    return array->number_of_elements;
}

int dynarray_get(const dynarray_t *array, const size_t index, void *value)
{
    if (index >= array->number_of_elements)
    {
        return -1;
    }
    const size_t offset = index * array->size_of_elements;
    memcpy(value, array->data + offset, array->size_of_elements);
    return 0;
}

int dynarray_remove(dynarray_t *array, const size_t index)
{
    if (index >= array->number_of_elements)
    {
        return -1;
    }

    const size_t offset = index * array->size_of_elements;

    if (index < array->number_of_elements - 1)
    {
        memcpy(array->tmp_data, array->data + offset, array->size_of_elements); //make copy of the original data
        memmove(array->data + offset, array->data + offset + array->size_of_elements, (array->number_of_elements - index) * array->size_of_elements);
    }

    const size_t new_size = array->number_of_elements - 1;
    uint8_t *new_ptr = realloc(array->data, new_size * array->size_of_elements);
    if (!new_ptr)
    {
        if (index < array->number_of_elements - 1)
        {
            memmove(array->data + offset + array->size_of_elements, array->data + offset, (array->number_of_elements - index) * array->size_of_elements);
            memcpy(array->data + offset, array->tmp_data, array->size_of_elements); //restore original data
        }
        return -1;
    }
    array->data = new_ptr;
}

int main()
{

    dynarray_t array;

    dynarray_init_type(&array, int);
    int a = 100;
    int b = 200;
    int c = 300;

    dynarray_append(&array, &a);
    dynarray_append(&array, &b);
    dynarray_append(&array, &c);
    dynarray_append(&array, &c);
    dynarray_append(&array, &c);

    printf("number  of elements = %llu\n", dynarray_len(&array));
    for (size_t i = 0; i < dynarray_len(&array); i++)
    {
        int value;
        if (!dynarray_get(&array, i, &value))
        {
            printf("[%llu] %d\n", i, value);
        }
    }

    dynarray_clear(&array);

    return 0;
}