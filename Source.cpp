#include <iostream>
#include "sha1.h"
#include "chat.h"
#include <string.h>

using namespace std;

int main()
{
	setlocale(LC_ALL, "rus");

	Chat ch = Chat();

	// Registration
	ch.reg((char*)"user1", (char*)"pass1", sizeof("pass1"));
	ch.reg((char*)"user2", (char*)"pass2", sizeof("pass2"));
	ch.reg((char*)"user3", (char*)"pass3", sizeof("pass3"));
	ch.reg((char*)"user4", (char*)"pass4", sizeof("pass4"));
	ch.reg((char*)"user5", (char*)"pass5", sizeof("pass5"));

	// Removal
	ch.del_reg((char*)"user2");
	ch.del_reg((char*)"user4");

	// Checking
	cout << "Login user1" << " Password pass1" << " Status : " << ch.login((char*)"user1", (char*)"pass1", sizeof("pass1")) << endl;

	cout << "Login user2" << " Password pass2" << " Status : " << ch.login((char*)"user2", (char*)"pass2", sizeof("pass2")) << endl;

	cout << "Login user3" << " Password pass3" << " Status : " << ch.login((char*)"user3", (char*)"pass3", sizeof("pass3")) << endl;

	cout << "Login user4" << " Password pass4" << " Status : " << ch.login((char*)"user4", (char*)"pass4", sizeof("pass4")) << endl;

	cout << "Login user5" << " Password pass5" << " Status : " << ch.login((char*)"user5", (char*)"pass5", sizeof("pass5")) << endl;

	return 0;
}