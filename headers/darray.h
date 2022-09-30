//
// Created by Matteo Cardinaletti on 28/09/22.
//

#ifndef DARRAY_DARRAY_GENERICS_H
#define DARRAY_DARRAY_GENERICS_H

#ifndef TYPE
#define TYPE int
#endif

#include <stdlib.h>
#include <stdio.h>

/// Pseudo-generic Dynamic Array.
/// You have to specify the constant TYPE right before including the header file containing this struct.
typedef struct DArray {
    TYPE* arr;
    size_t size;
} DArray;

/// Initializes the struct object.
void init_(DArray* array) {
    TYPE* pointer = (TYPE*) malloc(sizeof(TYPE));
    if (!pointer) {
        printf("Memory allocation failed.");
        free(pointer);
        exit(EXIT_FAILURE);
    }

    array->arr = pointer;
    array->size = 0;
}

/// Destroys a struct object.
void free_(DArray* array) {
    free(array->arr);
    array->arr = NULL;
    array->size = 0;
}

/// Resets the struct object to its initial state.
void reset_(DArray* array) {
    free_(array);
    init_(array);
}

/// Adds an element to the struct object passed.
void add_(DArray* array, TYPE value) {
    array->size += 1;

    TYPE* pointer = realloc(array->arr, array->size * sizeof(TYPE));
    if (!pointer) {
        printf("Memory allocation failed.");
        free(pointer);
        exit(EXIT_FAILURE);
    }

    pointer[array->size - 1] = value;
    array->arr = pointer;
}

/// Deletes an element contained into the struct object passed at the relative index.
void delete_(DArray *array, int index) {
    DArray temp;

    for (int i = index; i < array->size - 1; ++i) {
        array->arr[i] = array->arr[i + 1];
    }

    init_(&temp);
    for (int i = 0; i < array->size; ++i) {
        add_(&temp, array->arr[i]);
    }

    TYPE* pointer = (TYPE *) realloc(temp.arr, temp.size * sizeof(TYPE));
    if (!pointer) {
        printf("Memory allocation failed.");
        free(pointer);
        exit(EXIT_FAILURE);
    }

    free(array->arr);
    array->arr = pointer;
    array->size -= 1;
}

#endif // DARRAY_DARRAY_GENERICS_H
