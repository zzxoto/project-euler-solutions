#ifndef COMMON_INCLUDE
#define COMMON_INCLUDE

#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

typedef long long int          i64;
typedef long long unsigned int u64;
typedef int                    i32;
typedef unsigned int           u32;

#define internal static

#define MIN(a, b) ((a) < (b)? (a): (b))
#define MAX(a, b) ((a) > (b)? (a): (b))

#endif
