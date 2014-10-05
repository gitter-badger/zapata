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

#include <http/HTTPObj.h>

#include <iostream>
#include <exceptions/CastException.h>
#include <exceptions/NoHeaderNameException.h>

zapata::HTTPRepRef::HTTPRepRef() : __name(NULL), __status(zapata::HTTP100) {
}

zapata::HTTPRepRef::~HTTPRepRef() {
}

string& zapata::HTTPRepRef::body() {
	return this->__body;
}

void zapata::HTTPRepRef::body(string _body) {
	this->__body.assign(_body);
}

zapata::HTTPStatus zapata::HTTPRepRef::status() {
	return this->__status;
}

void zapata::HTTPRepRef::status(zapata::HTTPStatus _in) {
	this->__status = _in;
}

void zapata::HTTPRepRef::unset(string _in) {
}

void zapata::HTTPRepRef::unset(long long _in) {
}

void zapata::HTTPRepRef::put(int _in) {
	if (this->__name == NULL) {
		this->__name = new string();
		zapata::tostr(*this->__name, _in);
		this->__name->insert(0, "_");
	}
	else {
		string* _s = new string();
		zapata::tostr(*_s, _in);
		this->insert(string(this->__name->data()), _s);
		delete this->__name;
		this->__name = NULL;
	}
}

void zapata::HTTPRepRef::put(long _in) {
	if (this->__name == NULL) {
		this->__name = new string();
		zapata::tostr(*this->__name, _in);
		this->__name->insert(0, "_");
	}
	else {
		string* _s = new string();
		zapata::tostr(*_s, _in);
		this->insert(string(this->__name->data()), _s);
		delete this->__name;
		this->__name = NULL;
	}
}

void zapata::HTTPRepRef::put(long long _in) {
	if (this->__name == NULL) {
		this->__name = new string();
		zapata::tostr(*this->__name, _in);
		this->__name->insert(0, "_");
	}
	else {
		string* _s = new string();
		zapata::tostr(*_s, _in);
		this->insert(string(this->__name->data()), _s);
		delete this->__name;
		this->__name = NULL;
	}
}

void zapata::HTTPRepRef::put(double _in) {
	if (this->__name == NULL) {
		this->__name = new string();
		zapata::tostr(*this->__name, _in);
		size_t dot = this->__name->find(".");
		if (dot != string::npos) {
			this->__name->erase(dot, 1);
			this->__name->insert(dot, "_");
		}
		this->__name->insert(0, "_");
	}
	else {
		string* _s = new string();
		zapata::tostr(*_s, _in);
		this->insert(string(this->__name->data()), _s);
		delete this->__name;
		this->__name = NULL;
	}
}

void zapata::HTTPRepRef::put(bool _in) {
	if (this->__name == NULL) {
		this->__name = new string();
		zapata::tostr(*this->__name, _in);
		this->__name->insert(0, "_");
	}
	else {
		string* _s = new string();
		zapata::tostr(*_s, _in);
		this->insert(string(this->__name->data()), _s);
		delete this->__name;
		this->__name = NULL;
	}
}

void zapata::HTTPRepRef::put(string _in) {
	if (this->__name == NULL) {
		this->__name = new string(_in);
	}
	else {
		string* _s = new string(_in);
		this->insert(string(this->__name->data()), _s);
		delete this->__name;
		this->__name = NULL;
	}
}

string& zapata::HTTPRepRef::get(size_t _idx) {
	if(_idx < this->size()) {
		return *this->at(_idx);
	}
	return zapata::nil_header;
}

string& zapata::HTTPRepRef::get(const char* _idx) {
	HTTPRepRef::iterator i;
	if ((i = this->find(_idx)) != this->end()) {
		return *((*i)->second);
	}
	return zapata::nil_header;
}

string& zapata::HTTPRepRef::header(const char* _idx) {
	return this->get(_idx);
}

void zapata::HTTPRepRef::stringify(ostream& _out, short _flags, string _tabs) {
	string _ret;
	this->stringify(_ret, _flags, _tabs);
	_out << _ret << flush;
}

void zapata::HTTPRepRef::stringify(string& _out, short _flags, string _tabs) {
	_out.insert(_out.length(), "HTTP/1.1 "),
	_out.insert(_out.length(),  zapata::status_names[this->__status]);
	_out.insert(_out.length(), CRLF);
	for (HTTPRepRef::iterator i = this->begin(); i != this->end(); i++) {
		_out.insert(_out.length(), (*i)->first);
		_out.insert(_out.length(), ": ");
		_out.insert(_out.length(), *(*i)->second);
		_out.insert(_out.length(), CRLF);
	}
	_out.insert(_out.length(), CRLF);
	_out.insert(_out.length(), this->__body);
}