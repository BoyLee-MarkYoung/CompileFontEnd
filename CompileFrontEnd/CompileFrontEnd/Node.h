//
//  Node.h
//  CompileFrontEnd
//
//  Created by Mark Young on 13-6-19.
//  Copyright (c) 2013年 Boy-Mark. All rights reserved.
//

#ifndef __CompileFrontEnd__Node__
#define __CompileFrontEnd__Node__

#include <iostream>
#include <String.h>
#include "Lexer.h"
#include <fstream>

using namespace std;

/*
 语法树节点类
 */
class Node {
public:
    
    //节点对应语法范畴在文件中出现的行数，用于报错
    int lexline;
    
    //目标文件文件名
    string objFileName;

    //用于多文件同时编译时，static map记录各自的label，以文件名为key
    static map<string, int> labelMultiFile;
    
    //报错函数，输出行数和 错误 s 内容
    void error(string s);
    
    //获得新的 label 数
    int newlabel();
    
    //输出 label
    void emitlabel(int i);
    
    //输出语句
    void emit(string s);
    
    //默认结构体只用于构造各个子类的 自定义 Null
    Node() {
        lexline = 1;
    }
    
    /*
     构建时填入对应输出文件文件名
     并填入语法范畴所在行数
    */
    Node(string fn) {
        
        objFileName = fn;
        if (!labelMultiFile[fn])
            labelMultiFile.insert(make_pair(fn, 1));
        lexline = Lexer::lineMultiFile[objFileName];
    }
    
    bool operator==(const Node& rhs);

};
#endif /* defined(__CompileFrontEnd__Node__) */
