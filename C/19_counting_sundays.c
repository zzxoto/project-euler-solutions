#include "lib/common.h"

//Question
//
//You are given the following information, but you may prefer to do some research for yourself.
//
// 1 Jan 1900 was a Monday.
// Thirty days has September,
// April, June and November.
// All the rest have thirty-one,
// Saving February alone,
// Which has twenty-eight, rain or shine.
// And on leap years, twenty-nine.
// A leap year occurs on any year evenly divisible by 4, but not on a century unless it is divisible by 400.
//
//How many Sundays fell on the first of the month during the twentieth century (1 Jan 1901 to 31 Dec 2000)?
//

#define SUN 0
#define MON 1
#define IS_LEAP_YEAR(y) ((y) % 4 == 0 && ((y) % 100 != 0 || (y) % 400 == 0))
#define HAS_30_DAYS(m) ((m) == 4 || (m) == 6 || (m) == 9 || (m) == 11)
#define HAS_31_DAYS(m) ((m) != 2 && !HAS_30_DAYS(m))

i32 getWeekDay(i32 year, i32 month, i32 day)
{
  assert(year >= 1900);
  assert(month >= 1 && month <= 12);
  assert(day >= 1 && day <= 31);
  if (HAS_30_DAYS(month))
  {
    assert(day <= 30);
  }
  if (month == 2)
  {
    if (IS_LEAP_YEAR(year))
    {
      assert(day <= 29);
    }
    else
    {
      assert(day <= 28);
    }
  }

  i32 days = 0;

  for (i32 i = 1900; i < year; i++)
  {
    if (IS_LEAP_YEAR(i)) 
    {
      days += 366;
    }
    else
    {
      days += 365;
    }
  }
  
  for (i32 i = 1; i < month; i++)
  {
    if (i == 4 || i == 6 || i == 9 || i == 11)
    {
      days += 30;
    }
    else if (i == 2)
    {
      if (IS_LEAP_YEAR(year))
      {
        days += 29;
      }
      else
      {
        days += 28;
      }
    }
    else
    {
      days += 31;
    }
  }

  days += day - 1;

  return (MON + days) % 7;
}

i32 main(i32 argc, char **argv)
{
  i32 total = 0;

  for (i32 y = 1901; y <= 2000; y++)
  {
    for (i32 m = 1; m <= 12; m++)
    {
      i32 weekDay = getWeekDay(y, m, 1);
      if (weekDay == SUN)
      {
        total++;
      }
    }
  }

  printf("%d\n", total);
  return 0;
}
