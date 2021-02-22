#include "lib/common.h"
#include "lib/bst.h"
#include "lib/utils.h"
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>

#define IS_ALPHA(c)((c) >= 'A' && (c) <= 'Z')

//
//Question
//
//Using names.txt (right click and 'Save Link/Target As...'), a 46K text file containing over 
//five-thousand first names, begin by sorting it into alphabetical order. 
//Then working out the alphabetical value for each name, multiply this value by its 
//alphabetical position in the list to obtain a name score.
//
//For example, when the list is sorted into alphabetical order, COLIN, which is worth 
//3 + 15 + 12 + 9 + 14 = 53, is the 938th name in the list. So, COLIN would obtain a score of 938 � 53 = 49714.
//
//What is the total of all the name scores in the file?

i32 stringCompareFn(void *a, void *b)
{
  uchar *stra = (uchar *) a;
  uchar *strb = (uchar *) b;

  while (*stra != '\0' && *strb != '\0')
  {
    uchar ca = *stra++;
    uchar cb = *strb++;

    if (ca < cb)
    {
      return -1;
    }
    if (ca > cb)
    {
      return 1;
    }
  }

  if (*stra == '\0' && *strb == '\0')
  {
    return 0;
  }

  return *stra == '\0'? -1: 1;
}

u32 stringScore(char *s)
{
  i32 score = 0;
  while(*s != '\0')
  {
    score += *s - 'A' + 1;
    s++;
  }

  return score;
}

i32 main(i32 argc, char **argv)
{
  //1. open file and read content into "content" buffer
  i32 fd = open("data/22/names.txt", O_RDONLY);
  if (fd < 0)
  {
    u_merror("open");
    return 1;
  }

  struct stat fileStat;
  if (fstat(fd, &fileStat) < 0)
  {
    u_merror("fstat");
    return 1;
  }

  size_t contentSize = fileStat.st_size;
  char *content = (char *) malloc(contentSize);

  ssize_t readN = read(fd, content, contentSize);
  if (readN < 0)
  {
    u_merror("read");
    return 1;
  }

  if (readN < contentSize)
  {
    printf("Incomplete read\n");
    return 1;
  }

  //2. parse the file contents "ABC","DEF" to ABC\0DEF\0
  char *parsedContent = (char *) malloc(contentSize);
  size_t parsedContentSize;
  {
    //parse state -> 0, expect "
    //parse state -> 1, expect " or <char>
    //parse state -> 2, expect ,
    i32 parseState = 0;

    size_t contentAt = 0;
    size_t parsedContentAt = 0;

    while(contentAt < contentSize)
    {
      char c = content[contentAt++];

      if (c == 10 || c == 13) continue;

      if (parseState == 0)
      {
        if (c == '"')
        {
          parseState = 1;
        }
        else
        {
          //illegal
          assert(false);
        }
      }
      else if (parseState == 1)
      {
        if (c == '"')
        {
          parsedContent[parsedContentAt++] = '\0';
          parseState = 2;
        }
        else if (IS_ALPHA(c))
        {
          parsedContent[parsedContentAt++] = c;
        }
        else
        {
          //illegal
          assert(false);
        }
      }
      else
      {
        if (c == ',')
        {
          parseState = 0;
        }
        else
        {
          printf("%d\n", c);
          //illegal
          assert(false);
        }
      }
    }
    if (parseState != 2)
    {
      //illegal
      assert(false);
    }

    parsedContentSize = parsedContentAt;
  }

  //3. insert parsed contents to BST
  bst_BST *tree = bst_createBST(stringCompareFn);
  {
    size_t k = 0;
    for (size_t i = 0; i < parsedContentSize; i++)
    {
      if (parsedContent[i] == '\0')
      {
        bst_addNode(tree, parsedContent + k);
        k = i + 1;
      }
    }
  }

  //4. traverse and figure out sum
  bst_DFSTraversal *dfs = bst_createDFSTraversal(tree, bst_e_preorder);

  u64 i = 1;
  u64 totalScore = 0;

  for (;;)
  {
    char *nextStr = (char *) bst_DFSNext(dfs);
    if (nextStr == NULL)
    {
      break;
    }

    totalScore += i * stringScore(nextStr);
    i++;
  }

  printf("%lld\n", totalScore);

  free(tree);
  free(content);
  free(parsedContent);
  if (close(fd) < 0)
  {
    u_merror("close");
    exit(1);
  }

  return 0;
}
