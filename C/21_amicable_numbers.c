#include "lib/common.h"

//Question
//
// Let d(n) be defined as the sum of proper divisors of n (numbers less than n which divide evenly i32o n).
// If d(a) = b and d(b) = a, where a != b, then a and b are an amicable pair and each of a and b are called amicable numbers.
// 
// For example, the proper divisors of 220 are 1, 2, 4, 5, 10, 11, 20, 22, 44, 55 and 110; 
// therefore d(220) = 284. The proper divisors of 284 are 1, 2, 4, 71 and 142; so d(284) = 220.
//
// Evaluate the sum of all the amicable numbers under 10000.
//

//returns sum of proper divisors of n
i32 d(i32 n)
{
  if (n <= 1) return 0;
  
  i32 k = floor(sqrt(n));

  i32 factorSum = 1;
  for (i32 factor = 2; factor <= k; factor++)
  {
    if (n % factor == 0)
    {
      i32 factor2 = n / factor;
      factorSum += factor;

      if (factor2 != factor)
      {
        factorSum += factor2;
      }
    }
  }

  return factorSum;
}

i32 main(i32 argc, char **argv)
{
  i32 amicableSum = 0;

  for (i32 a = 1; a <= 10000; a++)
  {
    i32 b = d(a);
    if (a == b) continue;

    i32 a_ = d(b);
    if (a_ == a)
    {
      amicableSum += a;
    }
  }

  printf("%d\n", amicableSum);

  return 0;
}
