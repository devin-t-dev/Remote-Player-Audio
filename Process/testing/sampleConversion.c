#include <assert.h>
#include <stdlib.h>
#include <stdlib.h>
#include <stdio.h>
#include "libavcodec/avcodec.h"

#define LENGTH_MS 1000		// how many milliseconds of speech to store 0,5s:x=1:44100 x=22050 sample da memorizzare
#define RATE 44100		// the sampling rate (input)

struct AVResampleContext* audio_cntx = 0;
int samples_consumed;
//(LENGTH_MS*RATE*16*CHANNELS)/8000
void inizializeResample(int inRate, int outRate, int buffer_size)
{
	audio_cntx = av_resample_init(outRate, //out rate
		inRate, //in rate
		16, //filter length 16
		10, //phase count 10
		0, //linear FIR filter
		0.6 ); //cutoff frequency
	assert( audio_cntx && "Failed to create resampling context!");
}
void resample(char dataIn[],char dataOut[],int nsamples)
{
	//*out_buffer = malloc(sizeof(in_buffer));
	//out_buffer = malloc(sizeof(out_buffer)*(LENGTH_MS*RATE*16*1)/8000);
	int samples_output = av_resample( audio_cntx, //resample context
	(short*)dataOut,	//buffout
	(short*)dataIn,		//buffin
	&samples_consumed,	//&consumed
	nsamples,		//nb_samples
	(sizeof(char)*nsamples),//lenout sizeof(dataOut)/2
	0);//is_last
	assert( samples_output > 0 && "Error calling av_resample()!" );
	//printf("\nValori Buffer:%s (%i) | Nuovo Buffer:%s (%i) \t\n Numero Sample OUT:%i,Valore DONE:%i\n\n\n\n",dataIn,sizeof(dataIn),dataOut,sizeof(dataOut),samples_output,nsamples);
}

void endResample()
{
	av_resample_close( audio_cntx );	
}