#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/fs.h"

// 格式化路径path，ls.c中的fmtname()是包括./还有空格，这里需要在memset()函数中进行修改
char *fmtname(char *path){
  static char buf[DIRSIZ+1];
  char *p;

  // Find first character after last slash.
  for(p=path+strlen(path); p >= path && *p != '/'; p--)
    ;
  p++;

  if(strlen(p) >= DIRSIZ)
    return p;
  memmove(buf, p, strlen(p));
  memset(buf+strlen(p), 0, DIRSIZ-strlen(p)); 
  return buf;
}

void find(char *path, char *filename){
    char buf[512], *p; 
    int fd;            
    struct dirent de;  
    struct stat st;    

    if((fd = open(path, 0)) < 0){
        fprintf(2, "find: cannot open %s\n", path);
        return;
    }

    if(fstat(fd, &st) < 0){
        fprintf(2, "find: cannot stat %s\n", path);
        close(fd);
        return;
    }

    // 进行判断
    if( strcmp(filename, fmtname(path)) == 0){
        printf("%s\n", path);
    }

    switch(st.type){
        case T_DIR:
            if(strlen(path) + 1 + DIRSIZ + 1 > sizeof buf){
                fprintf(2, "find: path too long\n");
                break;
            }
            strcpy(buf, path);
            p = buf+strlen(buf);
            *p++ = '/';
            // 遍历目录下的每一个文件
            while(read(fd, &de, sizeof(de)) == sizeof(de)){
                if(de.inum == 0)
                    continue;
                // 不递归至.以及..（ls.c中会ls出.和..）
                if(strcmp(de.name, ".") == 0 || strcmp(de.name, "..") == 0)
                    continue;
                memmove(p, de.name, DIRSIZ); 
                p[DIRSIZ] = 0;               
                if(stat(buf, &st) < 0){
                    fprintf(2, "find: cannot stat %s\n", buf);
                    continue;
                }
                // 递归调用find()
                find(buf, filename);
            }
            break;
    }
    close(fd);
}

int main(int argc, char *argv[]){
    // 先判断参数
    if(argc != 3){
        fprintf(2, "Usage: find <directory> <file>\n");
        exit(1);
    }
    else{
        find(argv[1], argv[2]);
        exit(0);            
    }
}