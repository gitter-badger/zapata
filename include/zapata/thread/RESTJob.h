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

#include <zapata/thread/Job.h>
#include <zapata/api/RESTPool.h>
#include <vector>
#include <sys/poll.h>
#include <sys/signalfd.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

using namespace std;
#if !defined __APPLE__
using namespace __gnu_cxx;
#endif

namespace zapata {

	typedef struct signalfd_siginfo thr_signal_t;

	class RESTJob: public Job {
		public:
			RESTJob(const RESTJob& _rhs);
			RESTJob(string _key_file_path);
			virtual ~RESTJob();

			virtual void assign(int _cs_fd);
			virtual void unassign(vector< size_t > _to_remove);
			zapata::JSONObj& configuration();

			RESTPool& pool();
			void pool(RESTPool* _pool);
			void log(zapata::HTTPReq&, zapata::HTTPRep&);

		private:
			vector< struct pollfd > __peers;
			RESTPool* __pool;
			JSONObj __configuration;
	};

}
