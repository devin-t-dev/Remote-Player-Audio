///@file usbData.h
/*
	usbData.h - Header della ononima classe.
	Gestisce i file da Pendrive e li memorizza in un vettore (vector c++11)
*/
#ifndef usbDATA_H_
#define usbDATA_H_
#include <iostream>
#include <vector>
#include <string>
///usbData Class: Analizza cartelle in cerca di file e li carica in un vettore. Mantiene inoltre il puntatore che ci indica a quale canzone ci troviamo
class usbData
{
private:
	int puntatore;
	//void analyzeID(usbDataPlus &arcplus);
	bool isDir(std::string dir); ///< Controlla se è una cartella @param dir La cartella da analizzare @return bool vero se è una cartella o viceversa
	void riempiArchivio(std::string baseDir, bool recursive, usbData &arc); ///< Funzione interna per riempire l'archivio(in realtà il vettore) delle canzoni
public:
	usbData(std::string baseDir,bool recursive);///< Costruttore. Analizza la cartella e setta il puntatore. @param baseDir Directory iniziale @param recursive Impostare a vero se si vogliono analizzare anche le sottocartelle
	void setPuntatore(int posizione); ///< Imposta la posizione al puntatore. @param posizione
	int getPuntatore(); ///< Ottieni la posizione del puntatore @return puntatore Tipo Intero. Il Puntatore serve per sapere a quale canzone del vettore ci troviamo. \b Non è inteso come puntatore di programmazione ma nel senso comune di "Indicatore"
	std::vector<std::string> elementi; ///< Tutte le canzoni trovate. Vengono inserite dentro questo vettore accessibile.
	bool isAudio (std::string percorso,bool onlymp3); ///< Controlla l'estensione per capire se ci si trova di fronte ad un file audio. @param percorso @param onlymp3 se impostato a true limita la funzione al solo controllo dell'estensione degli mp3.
	usbData& operator = (const usbData& other) { //??
		puntatore=other.puntatore;
		elementi=other.elementi;
		return *this;
	}
};

#endif
