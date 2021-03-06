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

#pragma once

#include <zapata/json/JSONObj.h>
#include <zapata/parsers/JSONLexer.h>

namespace zapata {

	class JSONTokenizerLexer: public JSONLexer {
		public:
			JSONTokenizerLexer(std::istream &_in = std::cin, std::ostream &_out = std::cout);
			virtual ~JSONTokenizerLexer();

			void switchRoots(JSONPtr& _root);

			void result(zapata::JSONType _in);
			void finish(zapata::JSONType _in);

			void init(zapata::JSONType _in_type, const string _in_str);
			void init(zapata::JSONType _in_type);
			void init(bool _in);
			void init(long long _in);
			void init(double _in);
			void init(string _in);
			void init();

			void add();

			JSONElementT* __root;
			JSONType __root_type;
			JSONElementT* __parent;
	};

}
