#include "interfaces.h"
#include <string>
#include "StringReverser.h"
#include "FileCacheManager.h"
#include "MyTestClientHandler.h"
#include "MySerialServer.h"

namespace boot {
	class Main {
	public:
		int main(int argc, char* argv[]);
	};
	int Main::main(int argc, char* argv[]) {
		Solver< std::string, std::string>* sol =new StringReverser();
		FileCacheManager<std::string>* cm = new FileCacheManager<std::string>();
		MyTestClientHandler* handle = new MyTestClientHandler(sol, cm);
		
		server_side::Server* server = new MySerialServer();
		server->open(atoi(argv[1]), handle);
	}
}

