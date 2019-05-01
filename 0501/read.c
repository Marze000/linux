#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
  FILE* fd = fopen("./temp.txt","r");
  if(fd ==NULL)
  {
    perror("read error");
    return -1;
  }
  
  char buf[1024];
  const char* msg = "my name is ma ze";
  while(1)
  {
    ssize_t s = fread(buf,1,strlen(msg),fd);
    printf("%d\n",s);
    if(s>0)
    {
      buf[s]= 0;
      printf("%s\n",buf);
    }
     
    if(feof(fd))
    {
      break;
    }
  }

  fclose(fd);
  return 0;
}
