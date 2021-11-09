#include "StdAfx.h"
//#include "CSocketSession.h"
#include "CServer.h"
int main(int argc, char* argv[]){

    cout << "hello" << endl;
    

    char buff[256];
    int nSelect = 0;
    string ipAddress = "192.168.0.42";
    int port = SERVER_PORT;

    cout << "1.Server " << endl;
    cout << "2.Clinet " << endl;
    cout << "3.Quit " << endl;
    cin >> nSelect;


switch (nSelect-1)
    {     
    case ServerMode: {
        cout << "start server " << endl;
        CServer s;
        
        s.start(ipAddress.c_str(), port);

        while (s.RecvData(buff, sizeof(buff)) != 0) {
            if (strncmp(buff, "exit", 4) == 0)
                break;

            cout << "cli_MSG" << buff << endl;
            cin >> buff;

            s.SendData(buff);

        }
        //delete s;
        break;
    }
    case ClientMode: {

/*
        cout << "start clinet " << endl;
        CClient c;
        c.Connect(ipAddress.c_str(), port);
        while (1) {
            cin.ignore();
            cout << "input : ";
            cin.get(buff, sizeof(buff));

            c.SendData(buff);
            c.RecvData(buff, sizeof(buff));

            cout << "S_MSG+" << buff << endl;

            if (strncmp(buff, "exit", 4) == 0) {
                exit(0);
            }

        }
        */
    }
        break;
        
    

    case Quit: {
        cout << "Exit " << endl;
        exit(0);
        break;
    }

    default: {
        cout << "Err Exit" << endl;
        break;
    }
    
    }
    return 0;
}