//Question:
//
//2^15 = 32768 and the sum of its digits is 3 + 2 + 7 + 6 + 8 = 26.
//What is the sum of the digits of the number 2^1000?

//@param exp, integer >= 1
function soln(exp) 
{
  let digits = Math.floor(1 + exp * Math.log(2) / Math.log(10));

  const result  = [];
  for (let i = 0; i < digits; i++)
  {
    result.push(0);
  }
  result[result.length - 1] = 1;

  let carry = 0;

  for (let i = 0; i < exp; i++) 
  {
    //might exit sooner, but this is cleaner
    for (let j = digits - 1; j >= 0; j--)
    {
      result[j] = result[j] * 2 + carry;
      carry     = Math.floor(result[j] / 10);
      result[j] = result[j] % 10;
    }
  }

  return result.reduce((sum, a) => sum + a, 0);
}

console.log(soln(1000));
