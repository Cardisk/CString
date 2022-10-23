//
// Created by Matteo Cardinaletti on 28/09/22.
//

#ifndef CSTRING_DARRAY_H
#define CSTRING_DARRAY_H

#include <stdlib.h>
#include <stdio.h>

/// Macros to handle the casting
#define INT(x) *((int*) x)
#define FLOAT(x)  *((float*) x)
#define DOUBLE(x) *((double*) x)
#define LONG(x) *((long*) x)
#define CHAR(x) *((char*) x)

/// Pseudo-generic type in c
typedef enum Type {
    INT,
    FLOAT,
    DOUBLE,
    LONG,
    CHAR
} Type;

/// Pseudo-generic Dynamic Array.
typedef struct DArray {
    Type type;
    void** arr;
    size_t size;
} DArray;

/// Custom sizeof function to make DArray struct more generic.
/// \param type A Type enum variable
/// \return sizeof() of the type associated
size_t sizeof_(Type type) {
    switch (type) {
        case INT:
            return sizeof(int*);
        case FLOAT:
            return sizeof(float*);
        case DOUBLE:
            return sizeof(double*);
        case LONG:
            return sizeof(long*);
        case CHAR:
            return sizeof(char*);
        default:
            return 0;
    }
}

/// Initializes the struct object.
/// \param array DArray* struct variable
/// \param type Init Type of the struct
void init_(DArray* array, Type type) {
    array->type = type;

    void** pointer = malloc(sizeof_(sizeof_(CHAR)));
    if (!pointer) {
        free(pointer);
        exit(EXIT_FAILURE);
    }

    array->arr = pointer;
    array->size = 0;
}

/// Destroys a struct object.
/// \param array DArray* struct variable
void free_(DArray* array) {
    free(array->arr);
    array->type = INT;
    array->arr = NULL;
    array->size = 0;
}

/// Destroys a struct object and all the pointers inside it.
/// \param array DArray* struct variable
void deep_free_(DArray* array) {
    for (int i = 0; i < array->size; ++i) {
        free(array->arr[i]);
    }
    free_(array);
}

/// Resets the struct object to its initial state.
/// \param array DArray* struct variable
void reset_(DArray* array) {
    Type type = array->type;
    free_(array);
    init_(array, type);
}

/// Adds an element to the struct object passed.
/// \param array DArray* struct variable
/// \param value TYPE value that has to be added to the array
void add_(DArray* array, void* value) {
    array->size += 1;

    void** pointer = realloc(array->arr, array->size * sizeof_(array->type));
    if (!pointer) {
        free(pointer);
        exit(EXIT_FAILURE);
    }

    pointer[array->size - 1] = value;
    array->arr = pointer;
}

/// Deletes an element contained into the struct object passed at the relative index.
/// \param array DArray* struct variable
/// \param index Index that has to be removed
void delete_(DArray *array, int index) {
    DArray temp;

    for (int i = index; i < array->size; ++i) {
        array->arr[i] = array->arr[i + 1];
    }

    init_(&temp, array->type);
    for (int i = 0; i < array->size; ++i) {
        add_(&temp, array->arr[i]);
    }

    void** pointer = realloc(temp.arr, temp.size * sizeof_(array->type));
    if (!pointer) {
        free(pointer);
        exit(EXIT_FAILURE);
    }

    free(array->arr);
    array->arr = pointer;
    array->size -= 1;
}

/// Returns the pointer to the variable stored at the given index.
/// \param array DArray struct variable
/// \param index Index of the array
/// \return A pointer that has to be casted on the type of the DArray
void* get_(DArray array, int index) {
    if (index < 0 || index >= array.size) exit(EXIT_FAILURE);
    return ((void*) (array.arr[index]));
}

int* int_array_(DArray array) {
    int* pointer = malloc(array.size * sizeof(int));
    if (!pointer) {
        free(pointer);
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < array.size; ++i) {
        pointer[i] = INT(get_(array, i));
    }

    return pointer;
}

float* float_array_(DArray array) {
    float* pointer = malloc(array.size * sizeof(float));
    if (!pointer) {
        free(pointer);
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < array.size; ++i) {
        pointer[i] = FLOAT(get_(array, i));
    }

    return pointer;
}

double* double_array_(DArray array) {
    double* pointer = malloc(array.size * sizeof(double));
    if (!pointer) {
        free(pointer);
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < array.size; ++i) {
        pointer[i] = DOUBLE(get_(array, i));
    }

    return pointer;
}

long* long_array_(DArray array) {
    long* pointer = malloc(array.size * sizeof(long));
    if (!pointer) {
        free(pointer);
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < array.size; ++i) {
        pointer[i] = LONG(get_(array, i));
    }

    return pointer;
}

char* char_array_(DArray array) {
    char* pointer = malloc((array.size + 1) * sizeof(char));
    if (!pointer) {
        free(pointer);
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < array.size; ++i) {
        pointer[i] = CHAR(get_(array, i));
    }
    pointer[array.size] = '\0';

    return pointer;
}

void* to_array_(DArray array) {
    switch (array.type) {
        case INT:
            return (void*) int_array_(array);
        case FLOAT:
            return (void*) float_array_(array);
        case DOUBLE:
            return (void*) double_array_(array);
        case LONG:
            return (void*) long_array_(array);
        case CHAR:
            return (void*) char_array_(array);
        default:
            break;
    }
}

#endif // CSTRING_DARRAY_H
