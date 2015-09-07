///@file dataManagerHub.cpp
///File d'implementazione relativo alla classe dataManager.
//Static
#include "dataManagerHub.h"
#include "../Input/Socket/Server.h"
#include "../Process/Riproduttore.h"
#include "util.h"
//Dynamic
#include <iostream>								//Libreria Input / Output
#include <string>									//Libreria per gestire le stringhe
#include <cstring> 								//strcpy !check
//Multitheathering
//Used For Multithetering (-std=c++0x) -lphtreah
#include <thread>									//Libreria per il multithetering
#include <mutex>									//Blocco sezioni critiche !check or implement in the right way
#include <condition_variable>						//Condizioni variabili !check

std::mutex lockAction;
int action=-1; int app=-1;
const std::string dirUpload="WebManager/uploadedFiles/";
std::string dirSongs;
Server comandiServer(7777);
Riproduttore*	Audio;
Riproduttore*   disabledPlayer; bool disabledPlayerLocked=false;//Contains only the song that we had uploaded
dataManager::dataManager(std::string dir) { //Gestirà tutti i thread!
	Audio=NULL;
	disabledPlayer=NULL;
	menuActive=false;					  //Set as actived the menu console line interface
	streamActive=false;
	comandiServer.SetactiveThread(true); //Imposta come attivo il Server
	dirSongs=dir;
	Audio = new Riproduttore(dir,true,true); //Start Audio Service
	std::thread thr_menu(&dataManager::menu_thr,this);
	std::thread thr_data(&dataManager::data_thr,this);
	thr_menu.detach();
	thr_data.detach(); //Manage all type of data
	//thr_raspberry.detach();
	//thr_output.detach();

	//Inizializza tutti i servizi
	//Crea l'archivio delle tracce e lo manda alla WebApp (forse non deve stare qui!)
	//Scegli quale App tenere (prob. fai partire l'app CLI e Web e tieni in pausa quella di streaming)
	//AudioList: Generazione del JSON e invio al server WEB delle traccie presenti in archivio.
	//NB: Essendo il server Web Apache sempre attivo, le canzoni vengono caricate all'avvio del programma o
	//    se è necessario scegliere un altra canzone.
}
void dataManager::sendSongsToWeb() {
	std::string AudioList;
	int i=0; int len=Audio->Musica->elementi.size();
	AudioList+="[";
	while (i<len)
	{
		std::string canzone=Audio->Musica->elementi[i];
		AudioList+="{\"name\": \""+utilGetName(canzone)+"\"}, ";
		i++;
	}
	AudioList[AudioList.length()-2]=']';
	comandiServer.sendData(AudioList,"ListOfSongs");
}
/**
 * @name Thread riguardante la gestione dei dati
 * Nel dettaglio, questo metodo si occupa di gestire gli input e cordinare il lavoro nel seguente modo: <br>
 * Per prima cosa resetta tutte le variabili presenti che usera nel corso del programma. Tra queste le più importanti sono <br>
 * - input: Contiene il messaggio che arriva dal server <br>
 * - output: Mantine man mano la lista di messaggi che deve arrivare al server <br>
 * - azione: chiama se necessario qualche azione. invece Action è la variabile globale che utilizza l'applicazione n°0(la CLI) per memorizzare i dati. <br>
 * Viene a questo punto controllato se un client è connesso e vengono prese le relative informazioni. Il server utilizza la porta 7777 per accettare le connessioni. <br>
 * Il passo seguente è quello di valutare quale tipo di applicazione sta interagendo con il server e in base al comando ricevuto la giusta operazione da effetuare <br>
 * - 0: Comando da riga di comando <br>
 * - 1: (toDo) comando da General Purpose Input Output di Raspberry <br>
 * - 2: Portale Web: In questa sezione sono presenti inoltre i comandi di skip/pausa/precedente. <br>
 * -- I seguenti comandi fanno quindi parte delle API di questo programma: \b "songs" per richiedere i titoli delle canzoni, \b "prev" manda in riproduzione la precedente, \b "playPause", \b "skip", \b "getPuntatore"
 *    che restituisce la posizione attuale del riproduttore. Infine \b killStreaming è in grado di terminare l'esecuzione dei dispositivi mobili. <br>
 * - 3: Applicazione per dispositivi mobili <br>
 * Infine viene effettuata l'analisi sulla variabile azione per capire quale istruzioni è più opportuno eseguire.
 */
void dataManager::data_thr() {
	Riproduttore * tmp=Audio;
	while (!dataManagerQuitSignal)
	{
		std::string input="";
		std::string output="";
		int azione=-1;
		if ((comandiServer.getActived()))
		{
			if (comandiServer.isConn())
			{
				comandiServer.getData();
				app=comandiServer.getApp();
				input=comandiServer.getMessage();
			}
		}

		//Adatto la richiesta dell'applicazione
		std::hash<std::string> hash_fn;
		switch (app)
		{
		case 0:
		case 1:
			azione=action;
			break;
		case 2: //Server Web
			if (input=="songs") {
				dataManager::sendSongsToWeb();
				app=-1;
			}
			if (input=="prev") azione=1;
			if (input=="playPause") azione=2;
			if (input=="skip") azione=3;
			if (input[0]=='s'&&input[1]=='e'&&input[2]=='t') {
				input[0]=input[3];
				azione=22;
				output+="Caricamento della ";
				output+=input[0];
				output+="° canzone";
			}
			if (input=="killStreaming"&&streamActive) {
				output+="Applicazione in esecuzione. Chiedo la chiusura della stessa";
				azione=12;
			}
			if (input=="getPuntatore") {
				if (streamActive)
					output+="appAttiva";
				else
					output+=std::to_string(Audio->Musica->getPuntatore());
			}
			break;
		case 3: //Applicazione
			if (input=="hello") output+="0afa2d1d877998a438089be1487aedb6";
			if (input=="startLoading") output+="Caricamento di una nuova canzone in corso!";
			if (input=="newStreamSong") { output+="Inizializzazione della nuova canzone"; azione=11; }
			if (input=="getStreamStatus")
				if (Audio->getTrackEnded()&&streamActive==true)
					output+="nextSongRequired";
				else
					output+="server Actived";
			//if (input=="end")
		    if (input=="forcePlay"||input=="op2") azione=-1;
			break;
		}

		//Eseguo l'operazione richiesta e mando l'output

		if ((azione>=0&&azione<=3)||azione>10) Audio->lock();
		switch (azione) {
			case 0:
				{
					std::unique_lock<std::mutex> locker(Audio->lockaudio);
					Audio->stop(); // Stoppa la musica
				}
				break;
			case 1:
				{
					std::unique_lock<std::mutex> locker(Audio->lockaudio);
					Audio->prevSong(); //Canzone Precedente
					Audio->playPause(0); //Costringo il riproduttore a partire.
				}
				break;
			case 2:
				{
					std::unique_lock<std::mutex> locker(Audio->lockaudio);
					Audio->playPause(3); //Flip/Flop: Inverto lo stato del lettore (in Pausa/in Riproduzione)
				}
				break;
			case 3:
				{
					std::unique_lock<std::mutex> locker(Audio->lockaudio);
					Audio->nextSong();
					Audio->playPause(0);
				}
				break;
			case 4:
				menuActive=!menuActive; //!Controllare che ci sia almeno un processo attivo!
				break;
			case 5:
				comandiServer.SetactiveThread(!comandiServer.getActived());
				break;
			case 9:
				dataManagerQuitSignal=true;
				break;
			case 11: //Switch On App, Switch Off WebServer
				menuActive=false; streamActive=true;
				Audio->stop();
				if (disabledPlayerLocked==false) {
					disabledPlayer=Audio;
					disabledPlayerLocked=true;
				}
				delete Audio;
				Audio=new Riproduttore(dirUpload,true,false);
				Audio->nextSong();
				Audio->playPause(0);
				break;
			case 12: //Switch On WebServer, Switch Off App
				menuActive=true; streamActive=false;
				Audio->stop();
				delete Audio;
				Audio = new Riproduttore(dirSongs,true,true);
				//Audio = new Riproduttore(*disabledPlayer);
				//Audio=disabledPlayer;
				Audio->nextSong();
				Audio->playPause(0);
				disabledPlayerLocked=false;
				break;
			case 22: //Set a specific Song
				Audio->scegliCanzone((int)(input[0]-'0'));
				break;
		}

		if ((azione>=0&&azione<=3)||azione>10) Audio->unlock();

		if (output!="") {
			comandiServer.sendData("\""+output+"\"","Reply from DataManager");
		} else {
			if (app==2||app==3) { comandiServer.sendData("\"Termine funzione raggiunta, ma nessuna notifica\"","Avviso"); }
		}
		app=-1;
	}
}

void dataManager::menu_thr()
{
	int tempAction;
	while(!dataManagerQuitSignal)
	{
		if (menuActive) {
			std::cout << "What you want to do? \n";
			std::cout << "0:\tstop the player \t1:\tPlay a previus song\n"
					 "2:\tPlay/pause Comand\t3:\tSkip this song\n"
					 "4:\tDisable this CLI \t5:\tDisable Web Server\n"
					 "\n9:\tEXIT\t\t\n"
					 "(Inserisci 0-3 , 9 per uscire): "
					 ""; //Plus FX in next time
			std::cin>>tempAction; // OR ACTION BY SERVER....
			if(!std::cin) // or if(cin.fail())
			{
				std::cout<<"(bad input)";
				// user didn't input a number
				std::cin.clear(); // reset failbit
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //skip bad input
				// next, request user reinput
				action=-1;
				continue; //required if there is some code after this line for skip one while cycle
			}
			{ //Accesso esclusivo alla risorsa azione
				std::unique_lock<std::mutex> locker(lockAction);
				action=tempAction;
				app=0;
			}
		}
	}
}

dataManager::~dataManager () {
	std::cout<<"[I] Quitting all thread";
	free(Audio); //Audio->kill();
	dataManagerQuitSignal=true;
	std::cout<<"[OK]"<<std::endl<<"Bye!";
}
