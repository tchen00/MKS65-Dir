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
  printf("-----------------------------------------------------\n");
  DIR * d;
  d = opendir("dir");
  struct dirent *entry;

  struct stat *file = malloc(sizeof(struct stat));
  entry = readdir(d);
  int s, rs = 0;
  printf("---List of Files--- \n");

  while(entry){
    char *name = calloc(sizeof(char),100);
    strcat(name,dir);
    strcat(name,"/");
    strcat(name,entry->d_name);
    stat(name,file);

    printf("File Name: %s\n",entry->d_name);
    if(entry->d_type==4){
      printf("File Type: Directory\n");
    }
    else if(entry->d_type==8){
      printf("File Type: Regular\n");
      rs += file->st_size;
    }

    printf("File Size: %lld or ",file->st_size);
    readable((float)file->st_size);
    s += file->st_size;

    //updates entry with next file
    entry=readdir(d);
    printf("---------------\n");

  }



  return 0;

}
