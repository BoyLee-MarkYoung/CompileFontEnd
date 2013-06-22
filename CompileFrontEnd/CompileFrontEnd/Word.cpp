//
//  Word.cpp
//  CompileFrontEnd
//
//  Created by Mark Young on 13-6-19.
//  Copyright (c) 2013年 Boy-Mark. All rights reserved.
//

#include "Word.h"

Word& Word::operator=(const Word &rhs)
{
    this->lexeme = rhs.lexeme;
    this->tag = rhs.tag;
    return *this;
}

bool Word::operator!=(const Word &rhs)
{
    return (this->lexeme != rhs.lexeme);
}

bool Word::operator==(const Word &rhs)
{
    return (this->lexeme == rhs.lexeme);
}


Word Word::eq = Word("==", Tag::EQ  ),
Word::ne = Word( "!=", Tag::NE ),
Word::le = Word( "<=", Tag::LE  ),
Word::ge = Word( ">=", Tag::GE ),
Word::andd = Word( "&&", Tag::AND ),
Word::orr = Word( "||", Tag::OR ),

Word::minus = Word( "minus", Tag::MINUS ),
Word::True = Word( "true",  Tag::TRUEE  ),
Word::False = Word( "false", Tag::FALSEE ),
Word::temp = Word( "t", Tag::TEMP),
Word::Null = Word("", Tag::Null);


