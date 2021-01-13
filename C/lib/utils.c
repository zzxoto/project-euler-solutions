#include "common.h"
#include "utils.h"

void u_printList_i32(i32 *list, i32 len)
{
  printf("[");
  for (i32 i = 0; i < len; i++)
  {
    if (i == len - 1)
    {
      printf("%d", list[i]);
    }
    else
    {
      printf("%d, ", list[i]);
    }
  }
  printf("]\n");
}
