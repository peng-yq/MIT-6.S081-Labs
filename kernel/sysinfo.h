struct sysinfo {
  uint64 freemem;   // amount of free memory (bytes), 可用内存量（字节）
  uint64 nproc;     // number of process, 进程数量（NOT UNUSED）, proc结构体中(proc.h)有个变量为进程状态
};
