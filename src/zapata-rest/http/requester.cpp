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

#include <zapata/http/requester.h>

void zapata::send(zapata::HTTPReq& _in, zapata::HTTPRep& _out, bool _ssl) {
	string _address(_in->header("Host"));
	unsigned int _port = _ssl ? 443 : 80;
	size_t _idx = -1;

	if ((_idx = _address.find(":")) != string::npos) {
		string _ports(_address.substr(_idx + 1));
		zapata::fromstr(_ports, &_port);
		_address.assign(_address.substr(0, _idx));
	}

	if (_ssl) {
		zapata::sslsocketstream _s;
		_s.open(_address, _port);
		_in->stringify(cout);
		cout << endl << flush;
		_in->stringify(_s);
		_s << flush;

		zapata::fromhttpstream(_s, _out);
		_s.close();
	}
	else {
		zapata::socketstream _s;
		_s.open(_address, _port);
		_in->stringify(cout);
		cout << endl << flush;
		_in->stringify(_s);
		_s << flush;

		zapata::fromhttpstream(_s, _out);
		_s.close();
	}
}
