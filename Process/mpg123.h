/// @file
/// mpg123.h Devin Taietta -  Riproduzione file MP3 -
/// \todo Implementare effetti particolari sull'audio
#ifndef MPG123_H_
#define MPG123_H_
///Inizializza il decoder \n @param song Percorso del file da leggere
void resetMp3(char* song);
///Riproduce un frammento d'Audio
int playMp3();
///Pulisce l'heap dai puntatori creati e resetta le variabili
void freeMp3();
///Imposta la variabile status. 0=Pausa, 1=Play /n @param value Valore intero da impostare.
void setMp3Status(int value);
//void resample();
#endif
