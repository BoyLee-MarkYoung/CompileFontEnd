//
//  begin.cpp
//  CompileFrontEnd
//
//  Created by Boy on 6/27/13.
//  Copyright (c) 2013 Boy-Mark. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <pthread.h>

#include "Lexer.h"
#include "Parser.h"

#define CON_COMPILE 100
#define USLEEP_TIME 100
#define BUF_SIZE 10
#define FILE_NAME "test.txt"

void handler(int num);
void *compile(void *filename);

int main(int argc, const char * argv[]) {
    int c_pid;
    int pid;
    pthread_t tid[CON_COMPILE];
    int err;
    int i;
    void *tret;
    char buf[BUF_SIZE];
    
    if (argc == 1) exit(0);
    
    signal(SIGCHLD, handler);
    
    if ((pid = fork())) {
        //父进程
        c_pid = pid;
        printf("The child process is %d\n", c_pid);
        int fd = open(FILE_NAME, O_RDONLY);
        while (1) {
            system("clear");
            if (fd != -1)
            {
                while (read(fd, buf, 2) > 0)
                {
                    write(0, buf, 2);
                    usleep(USLEEP_TIME);
                }
                printf("\n\n\n");
                sleep(3);
            }
            else
            {
                printf("Loading...");
                sleep(100);
            }
            
            lseek(fd, 0, SEEK_SET);
        }
    } else {
        //子进程
        for (i = 1; i < argc; ++i)
        {
            sleep(1); // 可以看效果
            err = pthread_create(&tid[i], NULL, compile, (void *)argv[i]);
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
//            printf("thread exit code %ld\n", (long)tret);
        }
        sleep(2);
        exit(0);
    }
}

void handler(int num) {
    // 接受到SIGCHLD的信号
    int status;
    int pid = waitpid(-1, &status, WNOHANG);
    if (WIFEXITED(status)) {
//        printf("The child %d exit with code %d\n", pid, WEXITSTATUS(status));
        exit(0);
    }
}

void *compile(void *filename) {
    Lexer lex = Lexer((char *)filename);
    Parser parse(lex);
    parse.program();
    return NULL;
}
