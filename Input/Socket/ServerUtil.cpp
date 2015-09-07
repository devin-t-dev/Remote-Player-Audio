///	@file
/// (EN) A simple server in the internet domain using TCP. \n
/// (IT) Un semplice server nel dominio internet che usa il TCP (Protocollo orientato alla connessione)
#ifndef SRVUTIL
#define SVRUTIL
#include <iostream>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>

static int sockfd, newsockfd, portno, clilen;
static struct sockaddr_in serv_addr, cli_addr;

static void error( char *msg ) {
  perror(  msg );
  exit(1);
}
/*!
 	 Funzione che inizializza il server. Qui viene solamente aperta una Server Socket (variabile sockfd)
 	 Intero @param port: Porta per la quale far partire il Server
 */
static int initServer(int port) {
     portno = port;
     //char buffer[1024]; //To resize to right size every time as 'contenuto'
     printf( "\n [I] Inizializzazione del Server (usando la porta #%d) \n", portno );

     sockfd = socket(AF_INET, SOCK_STREAM, 0);
     if (sockfd < 0)
         error( const_cast<char *>("ERROR opening socket") );
     bzero((char *) &serv_addr, sizeof(serv_addr));

     serv_addr.sin_family = AF_INET;
     serv_addr.sin_addr.s_addr = INADDR_ANY;
     serv_addr.sin_port = htons( portno );
     if (bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) {
       /*error( const_cast<char *>( "[E] ERROR on binding" ) );*/
    	 	 	 printf("\n [E] Porta Attualmente in uso... Ritento");
    	 	 	 sleep(2);
    	 	 	 initServer(portno);
    	 	 	 return false;
     }
     listen(sockfd,5);
     clilen = sizeof(cli_addr);
     return 0;
}
/// Restituisce al Client una risposta
/// @param data Puntatore a variabile char che contiene i dati
/// @param len Intero, lunghezza dei dati da trasmettere
void mandaData(char * data,int len)  {
  int n;
  char buffer[len];
  sprintf( buffer, "%s\n", data );
  if ( (n = write(newsockfd, buffer, strlen(buffer) ) ) < 0 )
    error( const_cast<char *>( "ERROR writing to socket") );
  buffer[n] = '\0';
}

/// Funzione Statica OttieniData()
/*
 	 Ottiene dal client un messaggio
 */
/// @return Puntatore a un indirizzo contenente Char. (Char*).
/*static*/ char * ottieniData() {
  char buffer[1024];
  int n;

  if ( (n = read(newsockfd,buffer,31) ) < 0 )
    error( const_cast<char *>( "ERROR reading from socket") );
  buffer[n] = '\0';
  return buffer;
}
/*
 * Rimane in attesa di un client
 */
void acceptClient() {
//--- wait on a connection ---
	if ( ( newsockfd = accept( sockfd, (struct sockaddr *) &cli_addr, (socklen_t*) &clilen) ) < 0 )
		error( const_cast<char *>("ERROR on accept") );
}
/*
 * Funzione di chiusura della Socket
 */
void closeServer() {
   close(newsockfd);
}
/*
 * Funzione per chiudere pulire la ServerSocket
 */
void killServer() {
	close(newsockfd);
	close(sockfd);
}
/*
 * @name JSON Codifica
 * Questa funzione restituisce il messaggio correttamente formattato per l'invio del file JSON
 * @param message Messaggio da includere come valore. Questa \b stringa verrà usata dal Client
 * @param type \b Stringa che indica il tipo del messaggio. Usato dal client prevalentemente per motivi di \b debug
 */
std::string JSONEncode(std::string message, std::string type) {
	/* Example of a JSON file
	 * {
	"type": "menu",
	"value": "File",
	"items": [
		{"value": "New", "action": "CreateNewDoc"},
		{"value": "Open", "action": "OpenDoc"},
		{"value": "Close", "action": "CloseDoc"}
	]
}
	 */
	std::string partialEncode;
	partialEncode+="{";
	partialEncode+="\"app\": 4,";
	partialEncode+="\"type\": \""+type+"\",";
	partialEncode+="\"value\": "+message;
	partialEncode+="}";
	return partialEncode;
}
#endif
