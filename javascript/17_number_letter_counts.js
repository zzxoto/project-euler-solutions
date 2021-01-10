//Question:
//
//If the numbers 1 to 5 are written out in words: one, two, three, four, five, then there are 3 + 3 + 5 + 4 + 4 = 19 letters used in total.
//If all the numbers from 1 to 1000 (one thousand) inclusive were written out in words, how many letters would be used?
//
//NOTE: Do not count spaces or hyphens. For example, 342 (three hundred and forty-two) contains 23 letters and 115 (one hundred and fifteen) contains 20 letters.
//The use of 'and' when writing out numbers is in compliance with British usage.

const list_1_19 = [
 '',  /*zero gets no length*/
 'one',
 'two',
 'three',
 'four',
 'five',
 'six',
 'seven',
 'eight',
 'nine',
 'ten',
 'eleven',
 'twelve',
 'thirteen',
 'fourteen',
 'fifteen',
 'sixteen',
 'seventeen',
 'eighteen',
 'nineteen'
];

//@param number, 0 <= number < 10,0000
function numberToString(number, bag)
{
  const b = str => bag.push(str);

  const fl = Math.floor;

  //if 1000 <= number <= 9999, numberToString_(number, 3, []);
  //if 100 <= number <= 999,   numberToString_(number, 2, []);
  //if 10 <= number <= 99,     numberToString_(number, 1, []);
  //if 1 <= number <= 9,       numberToString_(number, 0, []);
  //
  //passing 0 would just leave bag with an empty string
  function numberToString_(number, position, bag)
  {
    if (position < 0)
    {
      return;
    }

    let digit = number;
    for (let i = position; i > 0; i--)
    {
      digit = fl(digit / 10);
    }

    switch(position)
    {
      case 0:
      case 1:
      {
        if (number <= 19)
        {
          b(list_1_19[number]);
          return; /*exit from recursion*/
        }
        switch(digit)
        {
          case 2:
          {
            b('twenty');
            break;
          }
          case 3:
          {
            b('thirty');
            break;
          }
          case 4:
          {
            b('forty');
            break;
          }
          case 5:
          {
            b('fifty');
            break;
          }
          case 6:
          {
            b('sixty');
            break;
          }
          case 7:
          {
            b('seventy');
            break;
          }
          case 8:
          {
            b('eighty');
            break;
          }
          case 9:
          {
            b('ninety');
            break;
          }
        }
        break;
      }
      case 2:
      {
        if (digit > 0)
        {
          b(list_1_19[digit]);
          b('hundred');
        }
        if (number % 100 != 0)
        {
          b('and');
        }
        break;
      }
      case 3:
      {
        if (digit > 0)
        {
          b(list_1_19[digit]);
          b('thousand');
        }
        break;
      }
    }

    numberToString_(number - ((10 ** position) * digit), position - 1, bag);
  }

  if (number < 0 || number >= 10000)
  {
    throw new Error('Too big an argument');
  }

  if (number == 0)
  {
    b('zero');
  }

  const position = number < 10
    ? 0
    : number < 100
    ? 1
    : number < 1000
    ? 2
    : 3;

  numberToString_(number, position, bag);
}

function soln(r1, r2)
{
  const bag = [];
  let result   = 0;

  while (r1 <= r2)
  {
    numberToString(r1, bag);
    result = bag.reduce((len, word) => len += word.length, result);
    bag.length = 0;
    r1++;
  }

  return result;
}

console.log(soln(1, 1000));
