/** @file aosender.c
 * Questo file si occupa di scrivere sull'hardware
 */

// Devin Taietta -- aosender.c -- Scrittura su dispositivo Audio.
#include <ao/ao.h>
#include "aosender.h"
static ao_device 	*dev;
/**
 * @name Inizializza Audio
 * Questa funzione inizializza la scrittura sull'audio
 */
void initAudioDev(int bits, long rate,int channels)
{
	int driver;
	ao_initialize();
	driver = ao_default_driver_id();
	ao_sample_format format;
	format.bits = bits;
	format.rate = rate;
	format.channels = channels;
	format.byte_format = AO_FMT_NATIVE;
	format.matrix = 0;
	dev = ao_open_live(driver, &format, NULL);
}
/**
 * @name Libera Audio
 * Questa funzione libera la scrittura sull'audio
 */
void freeAudioDev()
{
	ao_close(dev);
	dev=NULL;
	ao_shutdown();
}
/**
 * @name Scrivi Audio
 * Questa funzione scrive un frammento Audio.
 */
int writeAudio(char* buffer, uint_32 numBytesMemory)
{
        if((ao_play(dev, (char*)buffer, numBytesMemory)==0)){
			return 1;
		}
}
