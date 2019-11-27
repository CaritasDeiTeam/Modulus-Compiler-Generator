/*
 ============================================================================
 Name        : Modulus.c
 Author      : Andrew Thomas Porter (AMDG)
 Version     : 1.2.1
 Copyright   : See LICENSE.txt
 Description : Modulus language compiler
 ============================================================================
 */
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

// make other libraries use our memory manager (overwrites free as well)
#define MEMORY_MALLOC_OVERWRITE true
// enable debug message printing
#define R_DEBUG true
// set memory unit to use dynamic allocations instead of a single static allocation
#define DYNAMIC_HEAP true
#include "memory.h"
#include "debug.h"
#include "compiler.h"


int main(int argc, char *argv[]) {
	r_debug_info(__func__, "Running...\n");
	m_sysheap_create(64, 128);
	return 0;
}
