//
//  Node.cpp
//  CompileFrontEnd
//
//  Created by Mark Young on 13-6-19.
//  Copyright (c) 2013年 Boy-Mark. All rights reserved.
//

#include "Node.h"


void Node::error(string s) {
    FILE *f = fopen("log.txt", "a+");
    //    ofstream fstrm(objFileName);
    //    fstrm.open(objFileName);
    
    
    //输出到文件
    fprintf(f, "near line %d: %s\n", lexline, s.c_str());

}

int Node::newlabel() {
     return ++labelMultiFile[objFileName];
}


void Node::emitlabel(int i) {
    FILE *f = fopen(objFileName.c_str(), "a+");
//    ofstream fstrm(objFileName);
//    fstrm.open(objFileName);

    
    //输出到文件
    fprintf(f, "L%d: ", i);
//    cout <<  "L"
//    << i
//    << ":";

}

void Node::emit(string s) {
        //输出到文件
    FILE *f = fopen(objFileName.c_str(), "a+");
    fstream fstrm(objFileName);
//    fstrm <<"\t" << s <<endl;
    fprintf(f, "\t%s\n", s.c_str());

//    cout <<"\t" << s <<endl;
}

bool Node::operator==(const Node& rhs)
{
    return this->lexline == rhs.lexline;
}

//int Node::labels = 0;
map<string, int> Node::labelMultiFile;
