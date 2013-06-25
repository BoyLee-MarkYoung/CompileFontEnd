//
//  begin.cpp
//  CompileFrontEnd
//
//  Created by Boy on 6/25/13.
//  Copyright (c) 2013 Boy-Mark. All rights reserved.
//

//#include <stdio.h>
//#include <stdlib.h>
//#include <string.h>
//#include <signal.h>
//#include <unistd.h>
//#include <sys/wait.h>
//#include <pthread.h>
//
//#define CON_COMPILE 100
//
//void handler(int num) {
//    // 接受到SIGCHLD的信号
//    int status;
//    int pid = waitpid(-1, &status, WNOHANG);
//    if (WIFEXITED(status)) {
//        printf("The child %d exit with code %d\n", pid, WEXITSTATUS(status));
//        exit(0);
//    }
//}
//
//void *compile(void *) {
//    int i, total;
//    srand((unsigned)time(NULL));
//    total = rand() % 10 + 1;
//    for (i = 0; i < total; ++i)
//    {
//        printf("Compile...\n");
//        sleep(1);
//    }
//    return NULL;
//}
//
//int main(int argc, const char * argv[]) {
//    int c_pid;
//    int pid;
//    pthread_t tid[CON_COMPILE];
//    int d_count; // 动画用
//    int err;
//    int i;
//    void *tret;
//    
//    if (argc == 1) exit(0);
//    
//    signal(SIGCHLD, handler);
//    
//    if ((pid = fork())) {
//        //父进程
//        c_pid = pid;
//        printf("The child process is %d\n", c_pid);
//        
//        while (1) {
//            for (d_count = 0; d_count < 10; ++d_count)
//            {
//                printf("Draw...\n"); // 不能使用printf，使用write，否则缓冲区不刷出
//                sleep(1);
//            }
//            printf("\n\n\n");
//        }
//    } else {
//        //子进程
//        for (i = 1; i < argc; ++i)
//        {
//            err = pthread_create(&tid[i], NULL, compile, NULL);
//            if (err != 0)
//            {
//                printf("thread create error: %s\n", strerror(err));
//                exit(-1);
//            }
//        }
//        for (i = 1; i < argc; ++i)
//        {
//            err = pthread_join(tid[i], &tret);
//            if (err != 0)
//            {
//                printf("can not join with thread: %s\n", strerror(err));
//                exit(-1);
//            }
//            printf("thread exit code %ld\n", (long)tret);
//        }
//        sleep(2);
//        exit(0);
//    }
//}
