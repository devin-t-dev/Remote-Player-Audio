///@file
///Server.h - Class Server
#ifndef SERVER_H
#define SERVER_H
#include <iostream>

/// Questa classe gestisce la SocketServer e le socket di comunicazione tra dispositivi e questo programma
class Server {
public:
	/*!
	 	 Costruttore della classe Server, si occupa quindi di inizializzare il server, lanciare il thread di accettazione della connessione e impostare le variabili.
	 	 @param porta dove far partire il server. Valori accettabili sono \b 1024-49151. Sotto è sconsigliato l'uso di qualche porta e può richiedere diritti di amministrazione.
	 */
	Server(int porta);
	void SetactiveThread(bool status); //Attiva o disattiva il server.
	bool getActived(); ///< Indica se il Server è attivo @return \b bool value. \n Se True il thread del server è attivo e viceversa
	bool isConn(); ///< Test della connessione al client @return conn: Valore booleano che indica se si è connessi
	void sendData(std::string message,std::string type);
	/*! Fà una prima analisi riempendo le oppurtune variabili private. \n
	 *	Funzionamento dettagliato: \n
	 *	Codice [0]: Indica l'applicazione che ha mandato il codice \n
	 *	Questo codice verrà inserito nella variabile "App". Per ulteriori informazioni vedi la  classe dataManager \n
	 *	@see getApp() Restituisce un valore intero che raprresenta il tipo di applicazione client o locale che ha mandato il Messsaggio \n
	 *	@see ottieniData() Il messaggio viene recuperato tramite la funzione ottieniData() in ServerUtil.cpp\n
	 *	@see dataManager::data_thr()  Analisi dei codici \n
	*/
	void getData();
	int getApp(); ///< @return \b currentApp: Valore intero che rappresenta il tipo di applicazione client o locale che ha mandato il Messaggio @see data_thr()
	std::string getMessage(); ///< @return \b message: Il testo che si ottiene togliendo le altre parti del codice. Questo verrà successivamente analizzato e usato nello scopo più adatto
	~Server(); ///< Distruttore della classe Server.
private:
	bool conn; ///< Variabile privata che indica se attualmente il client è connesso.
	bool kill; ///< Variabile privata che indica se il processo deve essere killato
	bool thrActive; //If false the main thread is paused (if with skip)
	int currentApp; ///< Mantiene in memoria fino a che non viene richiesta l'app corrente
	int msgLen;
	std::string message; ///< Mantiene il messaggio fino a che non è richiesto.
	void ServerThread(); ///< Processo che gira in continuazione in attesa di nuove connessioni
};
#endif
