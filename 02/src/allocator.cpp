#include "allocator.h"
#include <iostream>

Allocator* init_allocator(size_t maxSize)
{
    if (maxSize == 0) return nullptr;
    Allocator* alloc = new(std::nothrow) Allocator();
    if (!alloc) {
        delete alloc;
        return nullptr;
    }
    alloc->start = new(std::nothrow) char[maxSize];
    if (!alloc->start) {
        delete alloc;
        return nullptr;
    }
    alloc->end = alloc->start + maxSize;
    alloc->offset = static_cast<size_t>(0);
    return alloc;
};

char* alloc(Allocator *alloc, size_t size)
{
    if (!alloc || !alloc->start || size == 0) {
        return nullptr;
    }
    if ((alloc->start + alloc->offset + size) > alloc->end)
    {
        return nullptr;
    }
    char* res = alloc->start +  static_cast<int>(alloc->offset);
    alloc->offset += size;
    return res;
};

void reset(Allocator *alloc)
{
    if (!alloc  || !alloc->start) return;
    alloc->offset =  static_cast<size_t>(0);
};

void clear(Allocator *alloc)
{
    if (!alloc) return;
    if (alloc->start) {
        delete[] alloc->start;
    }
    alloc->start = nullptr;
    alloc->end = nullptr;
    alloc->offset =  0;
    delete alloc;
};