#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main()
{
  //FILE *fopen (const char* path ,const char* mode);
  char *file = "./tmp.txt";
  FILE *fp = fopen(file,"r");
  if(fp ==NULL)
  {
    return -1;
  }

  return 0;
}
