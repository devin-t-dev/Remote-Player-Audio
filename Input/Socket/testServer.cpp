#include <iostream>
#include "Server.h"

//Used For Multithetering (-std=c++0x)
#include <thread>									//Libreria per il multithetering
#include <mutex>									//Blocco sezioni critiche
#include <condition_variable>						//Condizioni variabili
#include <queue>									//Code

using namespace std;
bool exited=false;
int main ()
{
	Server *ComandiServer = new Server(7777);
	//std::thread thr_server(ComandiServer->ServerThread,ComandiServer);
	//thr_server.detach();
	while(!exited){
		if (ComandiServer->isConn())
		{
			ComandiServer->getData();
			cout<<"\n MESSAGGIO RICEVUTO: "<<ComandiServer->getMessage()<<endl;
		}
	}
}
