/// @file Riproduttore.h
/// (EN) This file allow us to do basic action on song like skip current track or pause current track. \n
/// (IT) Questo file ci consente di eseguire delle azioni sulle canzoni come passare alla precedente o successiva traccia
/// o mettere la musica in pausa.
/// @author Devin Taietta
#ifndef RIPRODUTTORE_H_
#define RIPRODUTTORE_H_
//Static Linked
#include "../Input/usbData.h"
//Dynamic Linked
#include <iostream>
#include <string>
#include <thread>			///Libreria per il multithetering
#include <mutex>			///Blocco sezioni critiche !check or implement in the right way

/// Classe Riproduttore usata per gesitre le azioni sulle canzoni, scegliendo la libreria più adatta
class Riproduttore
{
public:
	/*! La funzione Riproduttore::Riproduttore corrisponde al costruttore dell'ononima classe. <br>
		Prende in ingresso due parametri e si occupa di: <br>
		1) Inizializzare le variabili private <br>
		2) Analizzare un percorso di dati per trovare tutti i file audio al suo interno <br>
		3) Impostare il puntatore a 0 (Prima traccia) <br>
		4) Far partire in background il processo che gestisce l'audio <br>

		@param percorso \b (Stringa) Cartella da analizzare per scoprire le tracce audio.
		@param recursive \b (Booleano) Impostare a vero se si vuole ottenere la scansione delle \b sotto-directory.
		@param autoskip \b (booleano): Indica se le traccie devono essere scorse automaticamente
	 */
	Riproduttore(std::string percorso, bool recursive,bool autoskip);
	usbData* Musica; ///< Puntatore "Musica" per un oggetto di tipo usbData @see usbData.*/
	/*!
		La funzione update ha duplice scopo: <br>
		Con percorso impostato si occupa di riprodurre esattamente il file che gli viene passato.
		Reset @see resetMp3() @see resetAudio() <br>

		@param percorso (Stringa) Senza parametri inseriti, quindi con percorso valore "",
		la funzione verifica se ciò che arriva è un MP3 o un altro file audio e chiama il corretto Reset
	 */
    void update(std::string percorso="");
    void scegliCanzone(int posizione);
	void prevSong(); ///<La funzione prevSong() viene usata per scegliere la canzone precedente e riprodurla
	void nextSong(); ///<La funzione next nextSong() viene usata per scegliere la canzone successiva e riprodurla

	/*!
	 	 La funzione playPause serve per gestire lo stato del lettore.
	 	 Si può quindi decidere se stiamo in riproduzione o in pausa

	 	 @param status (intero) Può assumere questi valori: <br>
	 	 	 \b 9 (Predefinito): Dopo aver controllato che la traccia non è finita, riproduci il frammento Audio <br>
	 	 	 \b 0: Metti in pausa il decoder audio <br>
	 	 	 \b 1: Metti in Play il decoder audio <br>
	 	 	 \b Altro: Se viene impostato un altro numero (Es. 3) il decoder inverte il suo stato tramite il flip/flop della variabile booleana
	 */
	void playPause(int status=9);
	void stop(); ///< Stoppa la riproduzione dell'audio
	void setTrackEnded(bool value); ///< Imposta l'attuale stato della traccia @param value (Booleano) Impostare a TRUE per indicare la fine della traccia
	bool getTrackEnded(); ///< Ottiene se l'attuale traccia è terminata o no
	void lock(); ///< Set the thread in wait
	void unlock(); ///< Set the thread in resume
	mutable std::mutex	lockaudio;		  ///< Usato nelle sezioni critiche per ottenere l'accesso esclusivo al processo
	/// Kill the player(so the thread)
	void kill() {RiproduttoreQuitSignal=true;};
	/*!
	 	 Il distruttore si occuperà di: <br>
	 	  1) liberare la memoria occupata dal vettore contenente le posizioni <br>
	 	  2) liberare la memoria occupata dal decoder <br>
	 	  3) Terminare il processo di riproduzione dei frammenti audio <br>
	 	  4) Eliminare la classe
	 */
	~Riproduttore();
	/// Costruttore in fase di copia. Necessario per il fatto che il mutex non è copiabile ed elimina quindi il suddetto metodo.
	Riproduttore( const Riproduttore &other) {
		std::lock_guard<std::mutex> lock(other.lockaudio);
		loopSongs = other.loopSongs;
		endtrack = true;
		locked=true;
		// deep copy
		try {
		Musica = new usbData(*other.Musica); // Allocazione di un nuovo puntatore necessaria perche la dimensione della musica cambia !check
		} catch (std::bad_alloc&) {
			std::cout<<"Memoria insufficente per creare l'archivio musicale";
			delete Musica;
			throw;
		}
		RiproduttoreQuitSignal = false;
	}
	//Copy assignment
	/// Overload dell'operatore di copia, necessario perchè senno il mutex non è copiabile
	Riproduttore& operator = (const Riproduttore& other) {
		if (this!=&other) {
			locked=true;
			loopSongs = other.loopSongs;
			endtrack = other.endtrack;
			*Musica = *other.Musica;
			//Musica = new usbData(*other.Musica);
			RiproduttoreQuitSignal = false;;
			locked=false;
		}
		return *this;
	}
private:
	bool loopSongs; ///< Questa variabile ci indica se le canzoni dovranno essere riprodotte in successione o no.
    bool endtrack; ///< Indica se la traccia è attualmente finita.
    bool locked; ///< Variabile usata per mettere in pausa il processo.
    bool RiproduttoreQuitSignal; ///< Se impostata a Vero termina si termina il processo riproduttore_thr e si chiama il distruttore.
    void riproduttore_thr();
};
#endif
