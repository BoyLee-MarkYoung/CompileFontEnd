#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <cstring>
#include <signal.h>
#include <unistd.h>
#include <sys/wait.h>
#include <pthread.h>

#define CON_COMPILE 100

using namespace std;

void handler(int num) {
  // 接受到SIGCHLD的信号
  int status;
  int pid = waitpid(-1, &status, WNOHANG);
  if (WIFEXITED(status)) {
    printf("The child %d exit with code %d\n", pid, WEXITSTATUS(status));
    exit(0);
  }
}

// 实现编译过程的线程函数
void* compile(void *) {
  int i, total = 5;
  for (i = 0; i < total; ++i)
    {
      printf("Compile...\n", total);
      sleep(1); // 测试用
    }
}

int main(int argc, const char * argv[]) {
  int c_pid, pid;
  pthread_t tid[CON_COMPILE];
  int d_count; // 动画用
  int err;
  int i;
  void *tret;

  if (argc == 1) exit(0);

  signal(SIGCHLD, handler);
  
  if ((pid = fork())) {
    //父进程
    c_pid = pid;
    printf("The child process is %d\n", c_pid);
    
    while (1) {
      for (d_count = 0; d_count < 10; ++d_count)
	{
	  printf("Draw...\n"); // 不能使用printf，使用write，否则缓冲区不刷出
	  sleep(1); // 测试用
	}
      printf("\n\n\n");
    }
  } else {
    //子进程
    for (i = 1; i < argc; ++i)
      {
	err = pthread_create(&tid[i], NULL, compile, NULL);
	sleep(3); // 测试用
	if (err != 0)
	  {
	    printf("thread create error: %s\n", strerror(err));
	    exit(-1);
	  }
      }
    for (i = 1; i < argc; ++i)
      {
	err = pthread_join(tid[i], &tret);
	if (err != 0)
	  {
	    printf("can not join with thread: %s\n", strerror(err));
	    exit(-1);
	  }
	printf("thread exit code %ld\n", (long)tret);
      }
    sleep(2);
    exit(0);
  }
}
