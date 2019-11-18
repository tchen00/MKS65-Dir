#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <time.h>
#include <errno.h>
#include <dirent.h>

void readable(float s){
  int i = 0;
  char * form[] = {"B", "KB", "MB", "GB"};
  while (s >= 1024){
    s /= 1024;
    i++;
  }
  printf("%f%s\t",s,form[i]);
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
/*
void dir_info(char *name){

}
*/
int main( int argc, char *argv[]){
  char* name = malloc(50);

  // if there is no command line argument
  if (argc <= 1){
      printf("Directory (. for current directory): ");
      fgets(name, 50, stdin);
      name[strlen(name)-1] = 0; // ending
  } else {
      // command line argument
      name = argv[1];
  }
  printf("Directory:  %s\n", name );

  struct stat *file = malloc(sizeof(struct stat));
  int size = 0;
  int rsize = 0;
  // TESTING printf("%d", size);
  DIR * d;
  d = opendir(name);
  struct dirent * entry;

  if (!d) {
    printf("Error! %s. Invalid directory. \n", strerror(errno));
    return 0;
  }

  entry = readdir(d);

  while (entry){
    // im baby so this will get the path NOT the file name
    char *fname = calloc(sizeof(char),100);
    strcat(fname,name);
    strcat(fname,"/");
    strcat(fname,entry->d_name);
    stat(fname,file);
    printf("File Name: %s\n",entry->d_name);
    if(entry->d_type==4){
      printf("File Type: Directory\n");
    }
    else if(entry->d_type==8){
      printf("File Type: Regular\n");
      rsize += file->st_size;
    }
    printf("File Size: %lld or ",file->st_size);
    readable((float)file->st_size);
    size += file->st_size;
    // TESTING printf("%d", size);
    entry = readdir(d);
    printf("\n-------------------------------\n");
  }

  printf("Total Directory (reg file) Size: %d bytes or ",rsize);
  readable(rsize);
  printf("\n");
  printf("Total File Size: %d bytes or ",size);
  readable(size);
  printf("\n");
  closedir(d);
  printf("----------------------------------------------------\n");
  return 0;
}
