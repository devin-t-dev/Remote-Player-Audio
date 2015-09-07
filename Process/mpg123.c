/** @file mpg123.c
  Riproduzione file MP3
 */
//Dynamic Linked
#include <mpg123.h>
//Static Linked
#include "mpg123.h"
#include "../Output/aosender.h"
//#include "../Process/Fx/Reverb.c" //#include "../Process/sampleConversion.c" //Commented, Only Testing
//Global Var
const int		BITS=8;
int			isPaused=0;
static mpg123_handle 	*mh;
static unsigned char 	*buffer=NULL;
static size_t 		buffer_size;
static size_t 		done;

/**
 * @name Reset delle variabili Decoder
 *
 * Questa funzione inizializza le variabili necessarie in fase di riproduzione per il decoder
 */
void resetMp3(char * song)
{
    if (buffer!=NULL) {freeMp3();}
	int err;
	int channels, encoding;
	long rate;
	/* Inizialize */
	mpg123_init();
	mh = mpg123_new(NULL, &err);
	buffer_size = mpg123_outblock(mh);
	buffer = (unsigned char*) malloc(buffer_size * sizeof(unsigned char));
	/* open the file and get the decoding format */
	mpg123_open(mh,song);
	mpg123_getformat(mh, &rate, &channels, &encoding);
	/* set the output format and open the output device */
	int bits=(mpg123_encsize(encoding) * BITS);
	initAudioDev(bits,rate,channels);
}
/**
 * @name Play MP3
 * Questa funzione si occupa di riprodurre un frame Audio
 */
int playMp3(){
  	/* decode and play */
	if (isPaused==0 && mpg123_read(mh, buffer, buffer_size, &done) == MPG123_OK)
	{
		writeAudio((char*)buffer,done);
	} else {
		if (isPaused==0) return 2;
	}
	return 0;
}
/* @name Pulizia Mp3
 * Questa funzione si occupa di liberare le variabili per riprodurre l'Mp3
 */
void freeMp3()
{
	free(buffer);
	buffer=NULL;
	mpg123_close(mh);
	mpg123_delete(mh);
	mpg123_exit();
	freeAudioDev();
	mh=NULL;
	//endResample(); // -ONLY TESTING- Check header
}
/*
 * @name Imposta lo stato (MP3)
 * Questa funzione si occupa di mettere in pausa il lettore o no
 */
void setMp3Status(int value)
{
	if(value==0||value==1)
	{
		isPaused=value;
	} else {
		isPaused=!isPaused;
	}
}
/*int mp3GetPlayStatus()
{
	return isPaused;
}*/
