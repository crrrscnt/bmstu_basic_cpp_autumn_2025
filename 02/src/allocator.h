#ifndef ALLOCATOR_H
#define ALLOCATOR_H

#include <cstddef>

inline bool init_alloc = false;

struct Allocator{
    char *start = nullptr; // указатель на начало (выделенной) памяти
    char *end = nullptr; // указатель на конец (выделенной) памяти
    size_t offset = 0;
};

Allocator* init_allocator(size_t maxSize);
char* alloc(Allocator *alloc, size_t size);
void reset(Allocator *alloc);
void clear(Allocator *alloc);

#endif // ALLOCATOR_H