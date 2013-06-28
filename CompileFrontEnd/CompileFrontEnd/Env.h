//
//  Env.h
//  CompileFrontEnd
//
//  Created by Mark Young on 13-6-19.
//  Copyright (c) 2013年 Boy-Mark. All rights reserved.
//

#ifndef __CompileFrontEnd__Env__
#define __CompileFrontEnd__Env__

#include <iostream>
#include "Token.h"
#include "Id.h"
#include <map>
#include "Word.h"
//#include "Word.h"


using namespace std;

/*
    用于 map first 参数的比较函数 operator() 重载
    Key 类型为 Token
    含子类 Word、Num、Float
    两个字、两个实数、两个整数是否相等
*/
struct classcomp {
    bool operator() (Token* lhs, Token* rhs) const
    {
        bool isWordSame = true;
        bool isNumSame = true;
        bool isFloatSame = true;
    
        //动态转换，如果lhs、rhs确实只想一个 Word对象，则返回指针，否则返回 NULL
        Word *lhw = dynamic_cast<Word*>(lhs);
        Word *rhw = dynamic_cast<Word*>(rhs);
        if ( lhw && rhw)
        {
            isWordSame = (lhw->lexeme < rhw->lexeme);
        }
        Num *ln = dynamic_cast<Num *>(lhs);
        Num *rn = dynamic_cast<Num *>(rhs);
        if ( ln && rn ) {
            isNumSame = (ln->value < rn->value);
        }
        Real *lr = dynamic_cast<Real *>(lhs);
        Real *rr = dynamic_cast<Real *>(rhs);
        if ( lr && rr ) {
            isFloatSame = (lr->value < rr->value);
        }
        return (lhs->tag <= rhs->tag) && isWordSame && isNumSame && isFloatSame;
    }
};


/*
 符号表类
 存储标识符
 用向前链表的方式处理当前所在 block 和上层 block 的关系
 */
class Env {
    
private:
    // 符号表
    map<Token*, Id, classcomp> table;
    
protected:
    Env * prev;
    
public:
    Env(Env *n) { prev = n; }
    
    
    Env()
    :prev(NULL)
    {
        //cout << "default Env constructing";
    }
    
    //添加符号入符号表
    void put(Token *w, Id i);

    //根据字获取标识符
    Id get(Token *w);

    static Env Null;
    
    Env& operator=(const Env& rhs);
    bool operator==(const Env& rhs);
    bool operator!=(const Env& rhs);
};
#endif /* defined(__CompileFrontEnd__Env__) */
