//
//  Lexer.h
//  CompileFrontEnd
//
//  Created by Mark Young on 13-6-19.
//  Copyright (c) 2013年 Boy-Mark. All rights reserved.
//

#ifndef __CompileFrontEnd__Lexer__
#define __CompileFrontEnd__Lexer__

#include <iostream>
#include "Word.h"
#include "Type.h"
#include <map>
#include "Num.h"
#include "Real.h"

#define MAX_FILE_NAME_LENGTH 256

using namespace std;


/*
 词法分析器
 
 */
class Lexer {
private:
    //源代码输入流文件
    FILE *fp;
    
    //源代码输入流文件名
    char fn[MAX_FILE_NAME_LENGTH];
    
    //目标文件文件名
    string objFileName;
public:
    
    //多线程编译多个文件时，用static map记录到达源文件的行数
    static map<string, int> lineMultiFile;
    
    //当前读入字符
    char peek;
    
    //预留关键字符号表
    map<string, Word*> words;
    
    //保留关键字接口
    void reserve( Word* w) { words.insert(make_pair(w->lexeme, w)); }
    
    //constructor...
    Lexer();
    Lexer(const char *filename);
    
    //读入下一个自符
    void readch();
    
    //读入并判断时候等于目标字符 c
    bool readch(char c);
    
    //扫描字符流，产出符号单元接口
    Token* scan();
    
    Lexer& operator=(const Lexer& rhs);
    
    //目标文件名get函数
    string getObjFileName();
    
    //目标文件名set函数
    void setObjFileName();
};
#endif /* defined(__CompileFrontEnd__Lexer__) */
