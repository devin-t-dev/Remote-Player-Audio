/* @file Server.cpp
 * @brief File del Server
 *
 * In questo file c'è la classe Server. Si occupa di gestire la Socket e l'invio e il ricevimento dei dati.
 *
 */

#include "ServerUtil.cpp"
#include "Server.h"
#include <iostream>
#include <string>

//Used For Multithetering (-std=c++0x) -lphtreah
#include <thread>									//Libreria per il multithetering
#include <mutex>									//Blocco sezioni critiche
#include <condition_variable>						//Condizioni variabili

using namespace std;

Server::Server(int porta) {
	initServer(porta);
	kill=false; conn=false; thrActive=false;
	std::thread thr_server(&Server::ServerThread,this);
	thr_server.detach();
}

void Server::ServerThread() {
	conn=false;
	while (!Server::kill) {
		acceptClient();
		if (thrActive) conn=true; else closeServer();
	}
}
void Server::getData() {
	std::string rawData=ottieniData();
	if (conn&&rawData.length()>0&&thrActive)
	{
		currentApp=(int)(rawData[0]-'0');
		int n=1;
		for (n=1;n<1024&&rawData[n]!='\n'&&rawData[n]!='\0';n++) {}
		n=n-1;
		rawData = rawData.substr(1,n); //Make a string starting from 1st and ending at limit of message
		message=rawData;
		msgLen=n-2;
		conn=false;
	}
}

void Server::sendData(std::string message,std::string type) {
	if (thrActive) {
		std::string partialMessage;
		partialMessage=JSONEncode(message,type);
		mandaData(const_cast<char *>(partialMessage.c_str()),partialMessage.length());
	}
}

int Server::getApp() {int temp=currentApp; currentApp=-1; return temp;} //Reset currentApp for avoid to pass twoice the same comand
bool Server::isConn() {return conn;}
bool Server::getActived(){return thrActive;}
void Server::SetactiveThread(bool status) {thrActive=status;}

std::string Server::getMessage(){std::string temp=message; message="";return temp;}

Server::~Server () {
	killServer();
	std::cout<<"Quitting Server";
	kill=true;
}
