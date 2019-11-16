#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <time.h>
#include <errno.h>
#include <dirent.h>

char * readable(float s){
  int i = 0;
  char * form[] = {"B", "KB", "MB", "GB"};
  while (s >= 1024){
    s /= 1024;
    i++;
  }
  printf("%f%s\n",s,form[i]);
  return;
}

/*
void permission(mode_t mode, char * buffer){
  char perm[10] ="rwxrwxrwx";
  int i;
    for (i = 0; i < 9; i++){
      if(!(mode & (1 << (8-i)))){
        perm[i] = '-';
      }
    }
  strcat(buffer, perm);
}
*/

int main(){
  DIR * d;
  int size, rsize = 0;
  d = opendir("dir");
  struct direct * directory;

  if (errno){
    printf("errno #%d: %s", errno, strerror(errno));
  }

  struct stat *file = malloc(sizeof(struct stat));
  directory = readdir(d);


  return 0;

}
