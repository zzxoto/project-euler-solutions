#ifndef COMMON_INCLUDE
#define COMMON_INCLUDE

#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include <string.h>
#include <limits.h>

typedef long long int          i64;
typedef long long unsigned int u64;
typedef int                    i32;
typedef unsigned int           u32;
typedef double                 f64;
typedef float                  f32;
typedef unsigned char          uchar;

#define internal static
#define I32_MAX  INT_MAX
#define I32_MIN  INT_MIN

#define MIN(a, b) ((a) < (b)? (a): (b))
#define MAX(a, b) ((a) > (b)? (a): (b))

#endif
