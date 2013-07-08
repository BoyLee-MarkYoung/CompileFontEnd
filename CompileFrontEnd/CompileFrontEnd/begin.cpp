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
#define BUF_SIZE 8192
#define GEEK_FILE_NAME "geek.txt"
#define COMPILING_FILE_NAME "compiling.txt"
#define COMPLETE_FILE_NAME "complete.txt"
#define LOG_FILE_NAME "log.txt"

int geek_fd;
int compiling_fd;
int complete_fd;
int log_fd;
char buf[BUF_SIZE];

void handler(int num);
void *compile(void *filename);

int main(int argc, const char * argv[])
{
    int c_pid;
    int pid;
    pthread_t tid[CON_COMPILE];
    int err;
    int i;
    void *tret;
    
    if (argc == 1) exit(0);
    
    log_fd = open(LOG_FILE_NAME, O_CREAT | O_APPEND | O_RDWR);
    
    signal(SIGCHLD, handler);
    
    if ((pid = fork())) {
        //父进程
        c_pid = pid;
        
        sprintf(buf, "The child process is %d\n", c_pid);
        write(log_fd, buf, strlen(buf));
        
        geek_fd = open(GEEK_FILE_NAME, O_RDONLY);
        compiling_fd = open(COMPILING_FILE_NAME, O_RDONLY);

        while (1)
        {
            puts("\33[2J");
            if (geek_fd != -1)
            {
                while (read(geek_fd, buf, 2) > 0)
                {
                    write(0, buf, 2);
                    usleep(USLEEP_TIME);
                }
                printf("\n\n\n");
                sleep(1);
                while (read(compiling_fd, buf, BUF_SIZE) > 0) {
                    write(0, buf, BUF_SIZE);
                }
                sleep(3);
            }
            else
                sleep(100);
            
            lseek(geek_fd, 0, SEEK_SET);
            lseek(compiling_fd, 0, SEEK_SET);
        }
    }
    else
    {
        //子进程
        for (i = 1; i < argc; ++i)
        {
            err = pthread_create(&tid[i], NULL, compile, (void *)argv[i]);
            if (err != 0)
            {
                sprintf(buf, "thread create error: %s\n", strerror(err));
                write(log_fd, buf, strlen(buf));
                exit(-1);
            }
        }
        for (i = 1; i < argc; ++i)
        {
            err = pthread_join(tid[i], &tret);
            if (err != 0)
            {
                sprintf(buf, "can not join with thread: %s\n", strerror(err));
                write(log_fd, buf, strlen(buf));
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
    close(geek_fd);
    close(compiling_fd);
    complete_fd = open(COMPLETE_FILE_NAME, O_RDONLY);
    
//    puts("\33[2J");
    int status;
    int pid = waitpid(-1, &status, WNOHANG);
    if (WIFEXITED(status)) {
        sprintf(buf, "The child %d exit with code %d\n", pid, WEXITSTATUS(status));
        write(log_fd, buf, strlen(buf));
        
        system("clear");
        while (read(complete_fd, buf, BUF_SIZE) > 0)
            write(0, buf, BUF_SIZE);
        close(complete_fd);
        close(log_fd);
        exit(0);
    }
}

void *compile(void *filename) {
    Lexer lex = Lexer((char *)filename);
    Parser parse(lex);
    parse.program();
    return NULL;
}
