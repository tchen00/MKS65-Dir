#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <time.h>

char * readable(long s){
  int i = 0;
  char * form[] = {"B", "KB", "MB", "GB"};
  while (s >= 1024){
    s /= 1024;
    i++;
  }
  return form[i];
}

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

int main(){
  struct stat file;
  stat("stat.c", &file);
  float size = (float) file.st_size;
  char * loc = readable(size);
  while (size >= 1024){
    size /= 1024;
  }
  printf("File size (byte): %ld \n", file.st_size);
  printf("File size (human readable form): %f %s \n", size, loc);
  printf("Permissions (normal): %o\n", file.st_mode);

  char permi[10];
  permission(file.st_mode, permi);
  printf("Permissions (ls -l): %s\n",permi);
  printf("Time of Last Access: %s", ctime(&file.st_atime));

  return 0;
}
