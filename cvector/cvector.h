#ifndef CVECTOR_H
#define CVECTOR_H

// All methods return a success status, and set the error variable if they fail.

// Macro so you can provide just the datatype without having to use sizeof()
#define Vec(obj) Vec_create(sizeof(obj))

// data is just an array, so you can cast it and use it as such.
typedef struct {
	void *data;
	size_t cap, size, obj_size, initial_size;
	const char *error;
	char popbuf[]; // intermediate buffer for popped items.
} Vec;

typedef void (*Vec_free_t)(void*);

// Create a Vec with a default size.
Vec *Vec_create_with_size(size_t obj_size, size_t initial_size);

// Takes the object size as a parameter
Vec *Vec_create(size_t obj_size);

// Takes the object and a custom free function, or NULL if one is not required.
void Vec_destroy(Vec *this, Vec_free_t free_func);

// Get an item from the desired index of a vector.
void *Vec_get(Vec *this, size_t index);

// Copy an item to the desired index of a vector.
int Vec_set(Vec *this, size_t index, void *new_obj);

// Insert an item at the desired index of a vector.
int Vec_insert(Vec *this, void *new_obj, size_t index);

// Remove an item from the desired index of a vector
int Vec_remove(Vec *this, size_t index);

// Push an item to the end of the vector.
int Vec_push(Vec *this, void *new_obj);

// Get the item at the top of the vector.
void *Vec_peek(Vec *this);

/* Pops the last item from the vector and removes it.
 * If you're going to use this, copy the result IMMEDIATELY.
 * This copies the popped item to an intermediate buffer,
 * which will be overwritten ever time an item is popped. */
void *Vec_pop(Vec *this);

// Return the error status of the vector as a string.
const char *Vec_error(Vec *this);

#endif
