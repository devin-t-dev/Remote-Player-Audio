/// @file dataManagerHub.h
/// (EN) This file and his associated class manage all inputs and select the correct jobs or output
/// (IT) Questo file gestisce tutti gli input e seleziona il giusto lavoro da eseguire.
/// - Nella fase di \b input Analizza i dati che gli arrivano seguendo questo codice:
/// - Nella fase di \b risposta \b da \b server a \b client, risponde usando la codifica JSON.
/// \i anche la lista delle canzoni viene mandata in formato JSON per essere inserita poi nel database WEB.
/// - Manda inoltre i comandi alla classe/funzione Streaming che gestirà la scrittura su scheda Audio
/// - Manda comandi e informazioni al gestore delle informazioni che si occupa di scegliere il mezzo più appropriato per
///   notificare quella particolare informazione all'utente.
/// Teoria codici passati per la comunicazione
/// ------------------------------------------
/// Si è voluto cercare un sistema per permettere una comunicazione efficace tra il client e il server.
/// Il problema principale è nato dal fatto che il comportamento non è standard ma dipende dall'applicazione che
/// ha generato i dati che vengono inviati attraverso la Socket. \n
/// - Il \b primo numero in arrivo corrisponde all'applicativo che ha mandato il segnale
/// -# \b 0 Rappresenta l'interfaccia mostrata a riga di comando
/// -# \b 1 Rappresenta i tasti comunicanti attraverso la GPIO (General Purpose Input/Output) di Raspberry [DA IMPLEMENTARE]
/// -# \b 2 Rappresenta l'interfaccia WEB presente sul server Apache installato sulla macchina dove risiede il programma
/// -# \b 3 Rappresenta l'applicazione JAVA installabile su dispositivi Android che invia direttamente il frame da riprodurre

/// - La parte restante del buffer è il nostro messaggio che verrà interpretato dal thread data_thr(). In generale:
/// -# Se viene dall'interfaccia WEB, da Raspberry o dalla CLI, verrà interpretato come comando per il Riproduttore
/// -# Se viene dall'applicazione per Android la canzone verrà caricata in un nuovo riproduttore. Alla disconnessione verrà
///    ripristinato il puntatore al vecchio riproduttore. Ulteriori informazioni le trovatre nella documentazione della funzione.
/// @author Devin Taietta

#ifndef DATAMANAGER_H_
#define DATAMANAGER_H_
#include <iostream>
/// This class manage all the inputs and select the correct jobs or output
class dataManager {
public:
	///Costruttore della classe dataManager:
	/*!
	 	 Viene richiamato al momento della creazione di un istanza della classe.
	 	 std::string @param dir: E' un parametro obbligatorio dove deve essere indicato il percorso iniziale
	 	 o della pennetta o di una cartella contenente la musica. Verrà usato per la creazione di un oggetto
	 	 di classe usbData
	 */
	dataManager(std::string dir);
	void setMenu(bool status) {menuActive=status;}; ///< Attiva o disattiva il Menu da terminale @param status: TRUE=attivo FALSE=disattivo(default).
	void setStream(bool status) {streamActive=status;} ///< Imposta la variabile che ci indica se il servizio di streaming da tablet è attivo o no.
	bool killSignal() {return dataManagerQuitSignal;}; ///< Controlla se è arrivato il segnare di uscita
	/*!
	 	 Pulisce la memoria occupata nell'heap e restituisce un messaggio di arrivederci.
	 */
	~dataManager();
private:
	void menu_thr(); ///< Thread del Menu
	void data_thr(); ///< Thread che analizza ciò che arriva da Server,Raspberry e CLI ed esegue l'azione più opportuna.
	void sendSongsToWeb(); ///< Funzione che invia in formato JSON le canzoni presenti in Archivio
	bool menuActive; ///< Variabile booleana che mostra il menù del terminale o no. Và impostata tramite la funzione @see setMenu()
	bool streamActive; ///< Variabile booleana che memorizza se il servizio di streaming delle canzoni da dispositivi è attivo o no. Viene impostata a false nel costruttore. Per modificarla vedi setStream @see setStream()
	bool dataManagerQuitSignal;///< Variabile controllata nei loop sempre attivi fino alla fine del programma
};
#endif
