#define _POSIX_C_SOURCE 200809L
#include <dirent.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <limits.h>
#ifndef PATH_MAX
#define PATH_MAX 4096
#endif
static int marker(const char *s) {
  const char *prefixes[]={"SLUS_","SLES_","SCES_","SCUS_","SLPM_","SLPS_",NULL};
  if (!strcmp(s,"SYSTEM.CNF")) return 1;
  for(int i=0;prefixes[i];i++) if(!strncmp(s,prefixes[i],strlen(prefixes[i]))) return 1;
  return 0;
}
static void scan(const char *path,int depth) {
  DIR *d=opendir(path);
  if(!d){printf("unavailable %s: %s\n",path,strerror(errno));return;}
  printf("readable %s\n",path);
  struct dirent *e;
  while((e=readdir(d))){
    if(!strcmp(e->d_name,".")||!strcmp(e->d_name,".."))continue;
    char p[PATH_MAX];
    int n=snprintf(p,sizeof p,"%s/%s",path,e->d_name);
    if(n<0||(size_t)n>=sizeof p)continue;
    struct stat st;
    if(lstat(p,&st))continue;
    printf("%s %s\n",marker(e->d_name)?"PS2 marker":"entry",p);
    if(depth>0&&S_ISDIR(st.st_mode))scan(p,depth-1);
  }
  closedir(d);
}
int main(int argc,char **argv){
  if(argc>1){for(int i=1;i<argc;i++)scan(argv[i],2);}
  else {scan("/mnt/disc",1);scan("/mnt",0);}
  return 0;
}
