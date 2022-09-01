// Mutual exclusion lock.（互斥锁）
struct spinlock {
  uint locked;       // Is the lock held? （是否锁住）

  // For debugging:
  char *name;        // Name of lock. （锁的名字）
  struct cpu *cpu;   // The cpu holding the lock. （上锁的CPU）
};

