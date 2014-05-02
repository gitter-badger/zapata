#define DEBUG 1

#include <signal.h>
#include <unistd.h>
#include <iostream>
#include <fstream>
#include <string>

#include <zapata/core.h>
#include <zapata/json.h>
#include <zapata/http.h>
#include <zapata/net.h>

using namespace std;
using namespace __gnu_cxx;

void sigsev(int sig) {
}

void stop(int sig) {
}

#define CYCLES 3
#define OBJECTS 100
//#define TEST_JSON
//#define TEST_HTTP
#define TEST_SOCK

int main(int argc, char* argv[]) {
	locale loc("");
	cout.imbue(loc);
	time_t ti = time(NULL);
	double vm;
	double resident;

	zapata::process_mem_usage(vm, resident);
	cout << "Initial\n\tVM: " << vm << "kB\tRESIDENT: " << resident << "kB" << endl << flush;

#ifdef TEST_SOCK
		zapata::serversocketstream ss;
		ss.bind(9090);

		zapata::socketstream cs;
		ss.accept(&cs);
#endif


	for (int k = 0; k != CYCLES; k++) {
#ifdef TEST_JSON
		{
			zapata::JSONObj obj;
			ifstream f;
			f.open("/home/pf/some.json");
			zapata::fromfile(f, obj);
			f.close();
		}
		{
			zapata::JSONArr obj;
			ifstream f;
			f.open("/home/pf/someother.json");
			zapata::fromfile(f, obj);
			f.close();
		}
#endif
#ifdef TEST_HTTP
		{
			zapata::HTTPReq obj;
			ifstream f;
			f.open("/home/pf/some.http");
			zapata::fromfile(f, obj);
			f.close();
			cout << obj << endl;
		}
		{
			zapata::HTTPRep obj;
			ifstream f;
			f.open("/home/pf/someresp.http");
			zapata::fromfile(f, obj);
			f.close();
			cout << obj << endl;
		}
#endif
#ifdef TEST_SOCK
		zapata::HTTPReq obj;
		zapata::fromstream(cs, obj);
		cout << obj << endl;

		{
			zapata::HTTPRep obj2;
			ifstream f;
			f.open("/home/pf/someresp.http");
			zapata::fromfile(f, obj2);
			f.close();

			cs << obj2 << flush;
		}


#endif

		zapata::process_mem_usage(vm, resident);
		cout << "\t\t\t\t\t\t\tAfter Cycle Nr. " << k << "\n\tVM: " << vm << "kB\tRESIDENT: " << resident << "kB" << endl << flush;
	}


	zapata::process_mem_usage(vm, resident);
	cout << "Final\n\tVM: " << vm << "kB\tRESIDENT: " << resident << "kB" << endl << flush;

	//zapata::__memory->print(cout);

	time_t tf = time(NULL);
	cout << "Took " << (tf - ti) << "s" << endl << flush;

	return 0;
}
