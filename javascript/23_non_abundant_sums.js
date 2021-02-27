//Question:
//
//A perfect number is a number for which the sum of its proper divisors is exactly equal to the number. 
//For example, the sum of the proper divisors of 28 would be 1 + 2 + 4 + 7 + 14 = 28, which means that 28 
//is a perfect number.
//
//A number n is called deficient if the sum of its proper divisors is less than n and it is called abundant 
//if this sum exceeds n.
//
//As 12 is the smallest abundant number, 1 + 2 + 3 + 4 + 6 = 16, the smallest number that can be written as 
//the sum of two abundant numbers is 24. By mathematical analysis, it can be shown that all integers greater 
//than 28123 can be written as the sum of two abundant numbers. However, this upper limit cannot be reduced 
//any further by analysis even though it is known that the greatest number that cannot be expressed as the sum 
//of two abundant numbers is less than this limit.
//
//Find the sum of all the positive integers which cannot be written as the sum of two abundant numbers.

function isAbundantNumber(n)
{
  if (n < 12) return false;

  //sum of proper divisors
  let sum = 0;

  const K = Math.floor(Math.sqrt(n));

  for (let factor = 1; factor <= K; factor++)
  {
    if (n % factor == 0 && factor != n)
    {
      sum += factor;

      const factorB = n / factor;
      if (factorB != factor && factorB != n)
      {
        sum += factorB;
      }
    }
  }

  return sum > n;
}

// fills array with N + 1 elements such that, 
// if k is abundantNumber, then arr[k] equals k otherwise, arr[k] equals -1
function listAbundantNumbers(N, arr)
{
  arr.length = N + 1;

  for (let n = 0; n <= N; n++)
  {
    if (isAbundantNumber(n))
    {
      arr[n] = n;
    }
    else
    {
      arr[n] = -1;
    }
  }
}

function soln()
{
  const N = 28123;
  const abundantNumbers = [];

  listAbundantNumbers(N, abundantNumbers);

  // sum of all the +ve integers, that cannot be written as sum of 2 abundant numbers
  let sum = 0;

  for (let n = 1; n  <= N; n++)
  {
    // false indicate cannot be written as sum of 2 abundant numbers
    let bool = false;

    for (let i = 0; i <= n; i++)
    {
      const a = abundantNumbers[i];
      if (a == -1)
      {
        continue;
      }
      const b = abundantNumbers[n - a];
      if (b == -1)
      {
        continue;
      }
      bool = true;
      break;
    }
    if (!bool)
    {
      sum += n;
    }
  }

  return sum;
}

console.log(soln());
