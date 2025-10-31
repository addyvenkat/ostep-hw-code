/**
 * Try out some of the other interfaces to memory allocation. For ex-
 * ample, create a simple vector-like data structure and related rou-
 * tines that use realloc() to manage the vector. Use an array to
 * store the vectors elements; when a user adds an entry to the vec-
 * tor, use realloc() to allocate more space for it. How well does
 * such a vector perform? How does it compare to a linked list? Use
 * valgrind to help you find bugs.
 * 
 * Answer:
 * - No valgrind support on macos
 */


#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    int * data;
    size_t size; // Total number of elements currently
    size_t capacity; // Total allocated space
}vector;

void vector_init(vector* v, size_t initial_capacity)
{
    printf("Initializing a vector...\n");
    v->data = (int*) malloc(initial_capacity * sizeof(int));
    v->size = 0;
    v->capacity = initial_capacity;
    printf("Vector: v->size:%zu, v->capacity:%zu\n", v->size, v->capacity);
}

void vector_pushback(vector* v, int value)
{
    printf("Adding element at the end of vector...\n");
    if(v->size == v->capacity) {
        printf("Need to increase capacity...\n");
        // Double the capacity when full
        size_t new_capacity = (v->capacity == 0) ? 1 : v->capacity * 2;
        
        /** Realloc
         *  - either expands the existing heap memory block in-place
         *  - or creates a new heap memory with the new size and frees the old memory block
         */
        int * new_data = (int*) realloc(v->data, new_capacity * sizeof(int)); 
        
        v->data = new_data;
        v->capacity = new_capacity;
    }
    v->data[v->size++] = value;
    printf("Vector: v->size:%zu, v->capacity:%zu\n", v->size, v->capacity);
}

void vector_free(vector * v)
{
    printf("Freeing vector...\n");
    free(v->data);
    v->data = NULL;
    v->size = 0;
    v->capacity = 0;
    printf("Vector: v->size:%zu, v->capacity:%zu\n", v->size, v->capacity);
}

int vector_get(vector * v, size_t index)
{
    printf("Getting the Vector element...\n");
    if(index < v->size){
        return v->data[index];
    }
    fprintf(stderr, "Error: Index out of bounds.\n");
    return 0xFF;
}

void vector_popback(vector *v)
{
    printf("Removing the last element from the vector...");
    v->size--;
}

void vector_print(vector * v)
{
    printf("Printing the Vector: v->size:%zu, v->capacity:%zu\n", v->size, v->capacity);
    for(int i=0; i < v->size; i++)
    {
        printf("data[%d]=%d\n", i, v->data[i]);
    }
}

int main()
{
    // Initialize a vector
    vector array;
    vector_init(&array, 1);

    // Add elements -> resize will kick in
    vector_pushback(&array, 10);
    vector_pushback(&array, 20);
    vector_pushback(&array, 30);
    vector_pushback(&array, 40);
    vector_pushback(&array, 50);

    vector_print(&array);

    // Remove last element
    vector_popback(&array);

    vector_print(&array);

    int x = vector_get(&array, 3);
    printf("Value:%d\n", x);

    int y = vector_get(&array, 5); // Error here
    printf("Value:%d\n", y);
}
