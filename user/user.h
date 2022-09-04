struct stat;    // 文件的结构体
struct rtcdate; // 时间的结构体

// system calls 系统调用函数（手册第11页包含部分介绍）
int fork(void);
int exit(int) __attribute__((noreturn));
int wait(int*);
int pipe(int*);
int write(int, const void*, int);
int read(int, void*, int);
int close(int);
int kill(int);
int exec(char*, char**);
int open(const char*, int);
int mknod(const char*, short, short);
int unlink(const char*);
int fstat(int fd, struct stat*);
int link(const char*, const char*);
int mkdir(const char*);
int chdir(const char*);
int dup(int);
int getpid(void);
char* sbrk(int);
int sleep(int);
int uptime(void);
int trace(int);

// ulib.c 一些函数库
int stat(const char*, struct stat*);     // 将有关打开文件的信息放入 *st
char* strcpy(char*, const char*);        // 将第二个字符串内容复制至第一个字符串，并返回第一个字符串
void *memmove(void*, const void*, int);  // 从str2复制n个字符到str1
char* strchr(const char*, char c);       // 在字符串中查找给定字符的第一个匹配之处
int strcmp(const char*, const char*);    // 比较两个字符串并根据比较结果返回整数
void fprintf(int, const char*, ...);     // 将字符输出到文件
void printf(const char*, ...);           // 将字符输出到标准输出设备，一般是屏幕
char* gets(char*, int max);              // 读取一行中的输入（最大为max个字符）
uint strlen(const char*);                // 返回一个字符串的长度
void* memset(void*, int, uint);          // 将字符串中前n个字符都设为某个数字
void* malloc(uint);                      // 分配n字节的内存
void free(void*);                        // 释放内存
int atoi(const char*);                   // 将字符串数字转换为整形数字
int memcmp(const void *, const void *, uint); // 比较字符串的，比较内存前N个字节
void *memcpy(void *, const void *, uint);  // 从源src所指的内存地址的起始位置开始拷贝n个字节到目标dest所指的内存地址的起始位置中,这里直接调用的memmove()
