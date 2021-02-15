#include "lib/common.h"
#include "lib/utils.h"

//Question
//
//n! means n × (n - 1) × ... × 3 × 2 × 1
//For example, 10! = 10 × 9 × ... × 3 × 2 × 1 = 3628800,
//and the sum of the digits in the number 10! is 3 + 6 + 2 + 8 + 8 + 0 + 0 = 27.
//
//Find the sum of the digits in the number 100!


//
//adds a[] to b[] and stores the result in b
//assumes bLen > aLen
//assumes every element in a[] and b[] are 0 <= element <= 9
void sum(i32 a[],  i32 aLen, i32 b[], i32 bLen)
{
  i32 A = aLen - 1;
  i32 B = bLen - 1;
  i32 carry = 0;

  while (A >= 0)
  {
    i32 k = b[B] + a[A] + carry;
    b[B]  = k % 10;
    carry = k / 10;
    A--;
    B--;
  }

  while (carry)
  {
    i32 k = b[B] + carry;
    b[B]  = k % 10;
    carry =  k / 10;
    B--;
  }
}

//leftShift([3, 2, 4], 3, 2) => [3, 0, 0]
void leftShift(i32 arr[], i32 len, i32 shiftBy)
{
  shiftBy = MIN(shiftBy, len);

  for (i32 i = shiftBy, k = 0; i < len; i++, k++)
  {
    arr[k] = arr[i];
  }
  for (i32 j = len - shiftBy; j < len; j++)
  {
    arr[j] = 0;
  }
}

//
//factora: [0, 0, 3, 4, 4]
//factorb: 2 (0 <= factorb <= 9)
//
//result: [0, 0, 6, 8, 8] (this is stored in prod)
void mul1(i32 factora[], i32 factoraLen, i32 factorb, i32 prod[], i32 prodLen)
{
  memset(prod, 0, sizeof(i32) * prodLen);

  while(factorb-- > 0)
  {
    sum(factora, factoraLen, prod, prodLen);
  }
}

//
//Does multiplication old school way i.e.
//
//         4 4 4 4
//           * 2 2
//         --------
//         8 8 8 8
//     + 8 8 8 8 X
//     -----------
//       9 7 7 6 8
//       
//factora: [0, 0, 3, 4, 4]
//factorb: 2 (0 <= factorb <= MAX_i32)
//
//result: [0, 0, 6, 8, 8] (this is stored in prod)
void mul(i32 factora[], i32 factoraLen, i32 factorb, i32 prod[], i32 prodLen)
{
  memset(prod, 0, sizeof(i32) * prodLen);
  i32 prodTemp[prodLen];
  i32 iteration = 0;

  while (factorb > 0)
  {
    mul1(factora, factoraLen, factorb % 10, prodTemp, prodLen);
    leftShift(prodTemp, prodLen, iteration++);
    sum(prodTemp, prodLen, prod, prodLen);
    factorb /= 10;
  }
}

i32 main(i32 argc, char **argv)
{
  //factorial of 'K'
  i32 K = 100;

  //1. setup arrays/ function parameters
  
  //crude estimate
  i32 digits = (log(K) / log(10) + 1) * K;

  i32 factora_[digits]; memset(factora_, 0, sizeof(factora_));
  factora_[digits - 1] = 1;
  i32 *factora = factora_;

  i32 prod_[digits]; memset(prod_, 0, sizeof(prod_));
  i32 *prod = prod_;

  i32 *temp;

  //2. calculate factorial
  while(K > 0)
  {
    mul(factora, digits, K, prod, digits);

    //the overwritten product becomes the new multiplication factor 
    temp    = factora;
    factora = prod;
    prod    = temp;
    K--;
  }

  //3. digitSum
  i32 digitSum = 0;
  for (int i = 0; i < digits; i++)
  {
    digitSum += prod[i];
  }

  printf("%d\n", digitSum);

  return 0;
}
