#include "Network.h"

using namespace std;
int main()
{
	try
	{
		WSASession Session;
		UDPSocket Socket;
		char buffer[100];
		Socket.Bind(100);

		while (1)
		{
			sockaddr_in add = Socket.RecvFrom(buffer, sizeof(buffer));
			cout << buffer << endl;
            if(buffer[0] == 'A'){
                cout << "HAHA" << endl;
            }
            memset( buffer, 0, sizeof(buffer) );
		}
	}
	catch (std::system_error& e)
	{
		cout << e.what();
	}
}