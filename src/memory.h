/*
 * # memory.h
 * ## Created:
 * November 6, A.D. 2019
 * ## Author:
 * Andrew Thomas Porter [<caritasdedeus@gmail.com>](mailto:caritasdedeus@gmail.com)
 *
 * Copyright &copy; 2019 Christi Crucifixi, LLC. All rights reserved.
 */

#include <stdint.h>
#include "error.h"

#ifndef MEMORY_H_
#define MEMORY_H_

enum cache {
	L1 = 0,
	L2 = 1,
	L3 = 3,
	L_EXT = 0
	// `L_EXT` is the start of cache level extensions for CPUs or platforms offering more than four cache levels
	// and begins at zero for compatibility purposes. Access of `L_EXT + (level - 1)` greater than or equal to `caches`
	// is undefined behavior.
};

struct block {
	struct block *prev;
	struct block *next;
	uintptr_t size;
	uintptr_t data[];
};

struct heap {
	// size of memory in bytes
	size_t size;
	// address of the last block for static section
	struct block *global_next;
	// address of the last block for dynamic section
	struct block *local_next;
	// location of the heap's memory
	uintptr_t memory;
};

enum cardinality {
	LEFT,
	RIGHT,
	UP,
	DOWN
};

enum m_type {
	LOCAL,
	GLOBAL
};

/*
 * # `void m_heap_create(size_t minbytes, size_t maxbytes);`
 * Initializes memory.c's internal heap (the process heap).
 *
 * ## `size_t minbytes`
 * The minimum size of the heap in bytes for the duration of the program.
 */
void m_heap_create(size_t minbytes);

/*
 * # `void m_heap_destroy();`
 * Frees the heap memory and then frees the heap object.
 */
void m_heap_destroy();

/*
 * # `void m_heap_resize(size_t minbytes);`
 * Resizes the heap with as many pages as are necessary to meet the minimum bytes requirement.
 * If the heap is greater than `minbytes` bytes, an attempt will be made to shrink the heap. Any memory outside this range
 * that is accessed after a call to this function is undefined behavior.
 *
 * If the heap is less than `minbytes` bytes, an attempt will be made to expand the heap.
 *
 *
 */
void m_heap_resize(size_t minbytes);

/*
 * # `size_t m_get_heap_size();`
 * Gets the actual size of the heap in bytes.
 *
 * ## `return size_t`
 * A value representing the size of the heap in bytes
 */
size_t m_get_heap_size();

/*
 * # `void *m_create(size_t minbytes, enum side side);`
 * Gets the next available memory block on the heap.
 *
 * ## `return void *`
 * A pointer to a block of allocated memory, or NULL if we failed to find available memory
 */
void *m_create(size_t minbytes, enum m_type type);

/*
 * Resizes the given block of memory to minbytes.
 */
void *m_resize(void *ptr, size_t minbytes);

/*
 * Frees the given block of memory.
 */
void m_free(void *ptr);

void *m_copy(void *src, size_t srcoff, size_t srclen, enum cardinality srcdir, void *dst, size_t dstoff, size_t dstlen, enum cardinality dstdir);

void *m_set(void *memory, size_t offset, size_t length, uintptr_t value, enum cardinality dir);

size_t m_get_cache_size(enum cache cache);

size_t m_get_page_size();

size_t m_get_cache_sector_size();

size_t m_get_word_size();

size_t m_get_caches();

size_t m_get_cache_sectors(enum cache cache);

#endif /* MEMORY_H_ */
