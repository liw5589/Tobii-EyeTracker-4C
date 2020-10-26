#include <thread>
#include <iostream>
#include <stdio.h>
#include <string>
#include <fstream>
#include <interaction_lib/InteractionLib.h>
#include <interaction_lib/misc/InteractionLibPtr.h>
#include "Network.h"

using namespace std;

IL::UniqueInteractionLibPtr intlib(IL::CreateInteractionLib(IL::FieldOfUse::Interactive));

void start()
{
    while (1)
    {
        intlib->WaitAndUpdate();
    }
}
int main()
{
    try
    {
        WSASession Session;
        UDPSocket Socket;
        int count = 0;
        char last[100];
        char buffer[100];
        Socket.Bind(100);

        // create the interaction library

        // assume single screen with size 2560x1440 and use full screen (not window local) coordinates
        constexpr float width = 1920.0f;
        constexpr float height = 1080.0f;
        constexpr float offset = 0.0f;

        intlib->CoordinateTransformAddOrUpdateDisplayArea(width, height);
        intlib->CoordinateTransformSetOriginOffset(offset, offset);

        // subscribe to gaze point data; print data to stdout when called
        intlib->SubscribeGazePointData([](IL::GazePointData evt, void *context) {
            cout << endl;
            cout << "x: " << evt.x << ", y: " << evt.y << endl;
            cout << endl;

            ofstream myfile;
            myfile.open("C:\\project\\resource\\recognition.csv", ios::app);
            myfile << evt.x << "," << evt.y << ",\n";
            myfile.close();
        },
                                       nullptr);

        // setup and maintain device connection, wait for device data between events and
        // update interaction library to trigger all callbacks, stop after 200 cycles

        bool flag = false;
        
        

        thread t1([&]{
                    while(true){
                        this_thread::sleep_for( std::chrono::milliseconds(200));
                        if (flag){
                            intlib->WaitAndUpdate();
                        }
                    }
                });
        while (true)
        {
            sockaddr_in add = Socket.RecvFrom(buffer, sizeof(buffer));

            cout << count << endl;

            if (buffer[0] == 'S')
            {   
                char strPath[] = {"C:\\project\\resource\\recognition.csv"};
                int nResult = remove( strPath );
                flag = true;
            }
            else if (buffer[0] == 'E')
            {
                flag = false;
                cout << flag << endl;
            }

            memset(buffer, 0, sizeof(buffer));
        }

        return 0;
    }

    catch (std::system_error &e)
    {
        cout << e.what();
    }
}
