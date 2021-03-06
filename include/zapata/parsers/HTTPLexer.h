/*
The MIT License (MIT)

Copyright (c) 2014 Pedro (n@zgul) Figueiredo <pedro.figueiredo@gmail.com>

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

// Generated by Flexc++ V1.08.00 on Tue, 25 Nov 2014 18:01:35 +0000

#ifndef zapataHTTPLexer_H_INCLUDED_
#define zapataHTTPLexer_H_INCLUDED_

// $insert baseclass_h
#include "HTTPLexerbase.h"

// $insert namespace-open
namespace zapata
{

// $insert classHead
class HTTPLexer: public HTTPLexerBase
{
    public:
        explicit HTTPLexer(std::istream &in = std::cin,
                                std::ostream &out = std::cout);

        HTTPLexer(std::string const &infile, std::string const &outfile);
        
        // $insert lexFunctionDecl
        int lex();

    private:
        int lex__();
        int executeAction__(size_t ruleNr);

        void print();
        void preCode();     // re-implement this function for code that must 
                            // be exec'ed before the patternmatching starts

        void postCode(PostEnum__ type);    
                            // re-implement this function for code that must 
                            // be exec'ed after the rules's actions.
};

// $insert scannerConstructors
inline HTTPLexer::HTTPLexer(std::istream &in, std::ostream &out)
:
    HTTPLexerBase(in, out)
{}

inline HTTPLexer::HTTPLexer(std::string const &infile, std::string const &outfile)
:
    HTTPLexerBase(infile, outfile)
{}

// $insert inlineLexFunction
inline int HTTPLexer::lex()
{
    return lex__();
}

inline void HTTPLexer::preCode() 
{
    // optionally replace by your own code
}

inline void HTTPLexer::postCode(PostEnum__ type) 
{
    // optionally replace by your own code
}

inline void HTTPLexer::print() 
{
    print__();
}

// $insert namespace-close
}

#endif // HTTPLexer_H_INCLUDED_

