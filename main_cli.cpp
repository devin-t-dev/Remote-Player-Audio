///@file
/**
*  Last Edit mer 24 giu 2015 18:24:02 CEST <br>
*  All rights reserved to respective authors. This "Player" Project contains some
*  open source library for all info see main page.
*  @author Devin Taietta
*/
/* --------------------------------------------------------------------------------
*   \b main_cli.cpp - Main of console program <br>
*     Richiede il nuovo C++ v.11
*/
/*! \mainpage Progetto Player Audio
 *
 * \section intro_sec Introduzione
 * Questo progetto riguarda la realizzazione di un player Audio.
 * L'obbiettivo iniziale è stato quello di realizzare i semplici comandi di pausa, successivo, precedente e lo studio base di come funziona l'audio contenuto nelle tracce (DSP).
 * Una volta realizzato, si è deciso di sperimentare l'uso delle Socket studiate durante il quinto anno.
 * E' stato quindi creato il sito client di interfacciamento e il Server per la gestione dei dati in arrivo.
 * L'ultima implementazione è stata quella della trasmissione delle canzoni attraverso dispositivi Mobili come Smartphone e/o tablet attraverso lo strumento di sviluppo "Cordova" che
 * permette di realizzare le applicazioni mobili per tutte le piattaforme. <br>
 * \section install_sec Installazione
 * Per eseguire il file una volta eseguita la compilazione e' necessario avere installate le seguenti librerie:
 * - LibAo -> Necessaria per scrivere sull'interfaccia audio
 * - LibMpg123 -> Decoding (Ottenimento dai frammenti audio interlacciati e compressi di frammenti non compressi in formato PCM) dei file mp3
 * - ffMpeg (avcodec,avformat) -> Decoding file audio in altri formati
 * <br>
 * Per la compilazione del progetto si usano gli strumenti gcc e g++. Se si vuole effettuare il debug dell'app allora si deve aggiungere l'opzione -g.
 * E' inoltre necessaria l'opzione -std=c++0x che indica al compilatore che il progetto è stato realizzato con la nuova versione del C++ introdotta nel 2011 (Necessario per la libreria pthread del multithreading)
 * Esempio di compilazione
 * \code{.sh}
 * gcc -c -g "Process/mpg123.c" "Output/aosender.c"
 * g++ -g "aosender.o" "Input/usbData.cpp" "Input/Socket/Server.cpp" "Process/dataManagerHub.cpp" "Process/util.cpp" "mpg123.o" "Process/Riproduttore.cpp" "main_cli.cpp" -lao -lmpg123  -lavcodec -lavformat -std=c++0x -o AudioPlayer
 * \endcode
 * <br> Il sistema di versioning è gestito tramite Git. Si può vedere la lista dei commit digitando git log sul branch di sviluppo.
 * <br> Successivamente è possibile eseguirlo digitando il nome dell'applicazione e il media esterno da tenere d'occhio.
 * \code{.sh} AudioPlayer "/mnt/" \endcode
 * <em>Nota: Non tutte le implementazioni del kernel Linux montano le pendrive sul percorso /mnt/. Se si sta adattando il progetto ad una diversa distribuzione bisogna inserire il
 * percorso corretto !</em>
 * \section hardware Hardware e Infrastrutture
 * \b
 * <br>
 * Le comunicazioni invece avvengono tramite connessione WiFi (IEEE 802.11). E' un tipo di trasmissione che utilizza come mezza trasmissivo l'aria per trasmettere le informazioni. Attraverso onde radio ad alta frequenza
 * (solitamente 2,4 Ghz) o (5 Ghz) siamo in grado quindi di connettere dispositivi senza la necessita di fastidiosi cavi. I vantaggi principali sono
 * - L'uso senza cavi dei dispositivi: fino a che abbiamo copertura, la connettività al modem è garantita in qualsiasi posto e in qualsiasi momento.
 * - Il basso costo d'installazione: cablare un edificio è molto più costoso della distribuzione del segnale attraverso un Access Point.
 *
 * Dobbiamo però ricordarci che le informazioni che passano via aria possono essere intercettate. E' per questo motivo che vengono utilizzate tecnologie come WEP e WPA2 per proteggere le reti.
 * \section serverStruct Struttura e codice del Server
 * Il Server viene sviluppato con il codice C (strutturato, linguaggio di medio livello) e C++ orientato agli oggetti. E' stato preferito questo linguaggio per il largo numero di librerie e per la sua velocità di esecuzione.
 * - Le funzioni del server possono essere trovate sulla classe Server @see Server
 * - La gestione dell'archivio su supporto di memorizzazione esterna viene affidata alla classe usbData @see usbData
 * - La gestione invece dell'audio è affidata alla classe Riproduttore @see Riproduttore
 * - Il cordinamento di tutte le attività avviene tramite il dataManagerHub @see dataManager
 *
 * L'uso di tutte le classi e gli oggetti all'interno del programma è stato suddiviso secondo dove vanno ad operare.
 * Abbiamo gli oggetti che si occupano di gestire l'input, quello che gestiscono il processamento dei dati e quelli che si occupano dei dati.
 * @image html schemaPlayer.png "Schema del funzionamento principale del programma. In blu le classi e in rosso ci sono le funzioni più importanti"
 * <br>
 * \section webStruct Struttura e codice della parte Web
 * La parte web è realizzata usando
 * - \b HTML5: lingaggio di formattazione attraverso marcatori
 * - \b Jquery(con Ajax): Linguaggio derivato dal JavaScript che usa selettori sugli elementi DOM per
 *      effettuare le operazioni. AJAX è l'acronimo di Asynchronus Javascript and XML e viene usato per
 *      interagire con il server senza richiedere al client di ricaricare la pagina.
 * - \b PHP: E' un linguaggio lato server viene usato nel progetto per interrogare il database e per gestire
 *      socket Server <--> Client
 * - \b CSS (Bootstrap): Il framework per il CSS che viene usato è Bootstrap. il CSS rappresenta delle regole di
 *      formattazione di documenti HTML.
 * \section appMobileStruct Struttura dell'app mobile
 * L'applicazione mobile è scritta in Java per Android o Objective C per IOS. La struttura viene creata grazie al framework \b Apache \b Cordova. Grazie alle capacità della piattaforma è possibile integrare nello spazio web,
 * in compatibilità con tutti i sistemi operativi più famosi, funzionalità d'interfacciamento al dispositivo come ad esempio l'accesso alla memoria di massa o l'upload di un file locale senza immissione manuale da parte
 * dell'utente.
 * Il codice delle pagine viene mostrato a parte e si basa principalmente sullo scambio di file JSON tra app e server WEB.
 * Vengono sfruttate quindi le webview per mostrare un sito con cui interfacciarsi al server.
 * \section usage_sec "Come si usa?"
 * \subsection fromConsole Da console
 * All'avvio dell'applicazione viene mostrato su schermo un menu che rappresenta tutte le operazioni svolgibili. Basta inserire il numero dell'operazione da svolgere per ottenere l'effetto desiderato.
 * \subsection fromWeb Da sito web
 * Bisogna conoscere l'indirizzo IP del server per poter ottenere l'acccesso da web. Un impletazione futura vede uno schermo LCD dove sarà possibile attraverso pulsanti conoscere l'IP del server e configurare la connessione WiFi in maniera più personalizzata.ù
 * Una volta acceduto attraverso un normale browser all'indirizzo sarà possibile interagire con l'applicazione attraverso una socket. 
 * \subsection fromApp Da applicazione mobile
 * Per semplificare l'accesso al server viene fornita un applicazione client. Automaticamente è in grado di effettuare la scansione sugli host della rete una volta conosciuto il dominio.
 * L'applicazione inoltre fornisce la possibilita di fare l'upload delle proprie canzoni in maniera da riprodurla sul Server.
 * \section praticalUse Applicazioni pratiche
 * L'idea principale di impiego per cui si presta questo progetto è da applicarsi ad un locale dove si vede l'installazione di una cassa installata fissa da una parte (lontano da malintenzionati) con un hardDisk integrato.
 * A chi viene fornita la password di accesso (solitamente il personale, ma può essere estesa questa possibilità anche ai clienti) può comodamente da remoto scegliere la canzone da riprodurre o la playlist.
 *
 * Altre applicazioni a cui si presta bene questo progetto o può essere facilmente adattato sono:
 * - Una radio per una macchina: Devono essere aggiunti uno schermo e una radio FM. Adattando la parte esterna allo slot della macchina può essere realizzata una radio.
 * - Player Audio grafico locale: Il progetto è stato realizzato in maniera da tenere CLI e Core dell'app separati, volendo sviluppare con Qt un applicazione grafica è possibile farlo.
 * - Una console per DJ (+ controllo remoto). Aggiungendo effetti sui frame audio e sfruttando la GPOI di Raspberry per l'input dei pulsanti e collegando uno schermo per l'output il progetto si può trasformare
 * in una console.
 * <br>
 * \section Funzionalità future
 * Il progetto e' in continua evoluzione e vede molte funzioni da aggiungere:
 * \subsection apiIntegration Integrazione di API
 * \todo l'Applicazione dovra essere in grado di interfacciarsi automaticamente con i propri account di Youtube e Spotify per ottenere le playlist da riprodurre.
 * \subsection automaticWakeUp Risveglio automatico
 * \todo Ad una certa ora l'applicazione sarà in grado di riaccendere la cassa attraverso la GPIO e un relé. Inizierà subito dopo la riproduzione.
 * \subsection Integrazione della General Purpose Input Output di raspberry.
 * Raspberry possiede un interfaccia con dei piedini dove vengono erogati 5V. Quest'ultimi per l'appunto possono erogare solo due tensioni fisiche 0V e 5V che corrispondo allo 0 e 1 logici.
 * Molti componenti possono essere integrati tramite questo funzionamento, specialmente tutti quelli digitali.
 * Per quanto riguarda i componenti come i LED, bisogna abbassare il voltaggio e assicurarsi di avere il massimo voltaggio consentito a partire da quei 5V. Per accenderlo ci basterà scrivere 1
 * sull'interfaccia e per spegnerlo 0.
 * Lo stesso discorso si applica ad esempio per i transistor che possono attivare altri componenti (è per l'appunto uno dei loro scopi).
 * Questi componenti verrano integrati quindi per fornire un indicazione visiva sulla cassa di cosa accade.
 */
//Dynamic Linked
#include <iostream>								//Libreria Input / Output
#include <string>									//Libreria per gestire le stringhe
//Static Linked
#include "main_cli.h"
#include "Process/dataManagerHub.h" //Gestisce tutte le entrate
/**
 * @name Main
 * Questa funzione inizializza il programma
 */
int main(int argc, char* argv[])
{
	/*if (argv[1]==NULL) { std::cout<<"Percorso standard "<<std::endl; argv[1]="/mnt/";}*/
	dataManager Gestore(argv[1]); //= new dataManager();
	Gestore.setMenu(true); //Not a pointer because not need a huge RAM
	while(!Gestore.killSignal()){}
}
