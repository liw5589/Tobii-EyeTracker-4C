#include "Network.h"

using namespace std;
int main()
{
	try
	{
		WSASession Session;
		UDPSocket Socket;
		string data = "S";
		char buffer[100];

		Socket.SendTo("127.0.0.1", 100, data.c_str(), data.size());
	}
	catch (exception &ex)
	{
		cout << ex.what();
	}
	return 0;
}