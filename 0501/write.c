#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
  FILE* fp = fopen("./temp.txt","w");
  if(fp==NULL)
  {
    perror("wtite orror");
  }
  const char* msg = "my name is maze\n";
  int count = 5;
  while(count--)
  {
    fwrite(msg,strlen(msg),1,fp);
  }
  fclose(fp);
  return 0;
}


