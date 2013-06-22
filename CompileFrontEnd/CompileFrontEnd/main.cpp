//
//  main.cpp
//  CompileFrontEnd
//
//  Created by Mark Young on 13-6-19.
//  Copyright (c) 2013年 Boy-Mark. All rights reserved.
//

#include <iostream>
#include "Lexer.h"
#include "Parser.h"

using namespace std;

int main(int argc, const char * argv[])
{
    
    Lexer lex = Lexer();
    Parser parse(lex);
    parse.program();
//    std::cout << "Hello, World!\n";
    return 0;
}

