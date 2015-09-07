///@file
// Riproduttore.cpp - Sceglie la libreria da usare per riprodurre correttamente le canzoni.

#include <vector>					//Lista canzoni in memoria
//Static Linked
#include "Riproduttore.h"			//Header di riproduttore.cpp
#include "../Input/usbData.h"		//Contiene la lista delle canzoni,isAudio(percorso,bool onlymp3)
#include "util.h"					//Casting particolari (Es. conversione stringa a char*)
#include "ffmpeg.h"				//Riproduzione file Audio tranne MP3
extern "C" {
#include "mpg123.h"				//Riproduzione File MP3
}

//Multitheathering
//Used For Multithetering (-std=c++0x) -lphtreah
#include <thread>									//Libreria per il multithetering
#include <mutex>									//Blocco sezioni critiche !check or implement in the right way
#include <condition_variable>						//Eventuali condizioni variabili

Riproduttore::Riproduttore(std::string percorso, bool recursive,bool autoskip)
{
	//freeMp3(); //++ 23 giu
	RiproduttoreQuitSignal=false; endtrack=false; loopSongs=autoskip;
	Musica = new usbData(percorso,recursive);
	Musica->setPuntatore(0);
	std::thread thr_audio(&Riproduttore::riproduttore_thr,this); //Passato per riferimento
	thr_audio.detach();
}
void Riproduttore::riproduttore_thr() {
	while(!RiproduttoreQuitSignal)
	{
	if (!locked)
		{
		if (Riproduttore::getTrackEnded()==false)
			{
				{
					std::unique_lock<std::mutex> locker(lockaudio);
					Riproduttore::playPause();
				}
			}
			else
			{
				if (loopSongs)
					Riproduttore::nextSong();
				Riproduttore::playPause(0);
			}
		}
	}
}
void Riproduttore::setTrackEnded(bool value) {endtrack=value;} bool Riproduttore::getTrackEnded() {return endtrack;}
void Riproduttore::lock() {locked=true;} void Riproduttore::unlock() {locked=false;}
void Riproduttore::update(std::string percorso)
{
	Riproduttore::setTrackEnded(true);
    if (percorso=="")
    {
        if (Musica->isAudio(Musica->elementi.at(Musica->getPuntatore()),true)){
            //resetMp3((toChar(Musica->elementi[Musica->getPuntatore()])));
        	resetMp3(toChar(Musica->elementi.at(Musica->getPuntatore())));
        }else{
            //resetAudio((toChar(Musica->elementi[Musica->getPuntatore()])));
        }
     }
    else
    {
        if (Musica->isAudio(percorso,true)){
            resetMp3(toChar(percorso));
        }else{
            ///resetAudio(toChar(percorso));
        }
    }
    Riproduttore::setTrackEnded(false);
}

void Riproduttore::prevSong()
{
	if (Musica->getPuntatore()>0)
	{
		Musica->setPuntatore(Musica->getPuntatore()-1);
		Riproduttore::update();
		///Riproduttore::playPause();
	} else { Musica->setPuntatore(Musica->elementi.size());Riproduttore::prevSong();}
}

void Riproduttore::nextSong()
{
	if (Musica->getPuntatore()>=(Musica->elementi.size()-1))
		Musica->setPuntatore(-1);
	Musica->setPuntatore(Musica->getPuntatore()+1);
	Riproduttore::update();
}

void Riproduttore::playPause(int status)
{
	//bool Mp3=Musica->isAudio(Musica->elementi[Musica->getPuntatore()],true);
	bool Mp3=Musica->isAudio(Musica->elementi.at(Musica->getPuntatore()),true);
	if (status!=9) { //Imposta manualmente il valore che gli arriva 0=Play,1=pause, Altri:flip/flop !ToDO: Da invertire i valori
		if (Mp3) setMp3Status(status); //else setAudioStatus(status);
	} else {		 //Se entra nell'else, riproduce la canzone normalmente, questo valore è di default e sis ottiene con la chiamata senza argomenti
		if (Mp3){
			if (playMp3()==2)
				Riproduttore::setTrackEnded(true);
		}else{
			//if(playAudio()==2)
			//	Riproduttore::setTrackEnded(true);
		}
	}
}
void Riproduttore::scegliCanzone(int posizione) {
    if (posizione>=0&&posizione<=(Musica->elementi.size()))
    {
		Musica->setPuntatore(posizione);
		Riproduttore::update();
    } else {std::cout<<"Il puntatore ricevuto:"<<posizione<<" non e valido!";}
}
void Riproduttore::stop()
{
	if (Musica->isAudio(Musica->elementi.at(Musica->getPuntatore()),true))
		setMp3Status(1);
	//else
		//setAudioStatus(1);
	Riproduttore::update();
}

Riproduttore::~Riproduttore() {
	try {
		freeMp3();
		free(Musica);
		Musica=NULL;
		RiproduttoreQuitSignal=true;
	}catch (int e){
		std::cout<<"Ops. Ci sono stati dei problemi nel pulire la memoria del Riproduttore";
	}
}
