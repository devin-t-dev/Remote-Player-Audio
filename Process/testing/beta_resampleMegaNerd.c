#include <assert.h>
#include <stdlib.h>
#include <stdlib.h>
#include <stdio.h>
#include "libavcodec/avcodec.h"

#define LENGTH_MS 1000		// how many milliseconds of speech to store 0,5s:x=1:44100 x=22050 sample da memorizzare
#define RATE 44100		// the sampling rate (input)

struct AVResampleContext* audio_cntx = 0;
int samples_consumed;
CALLBACK_DATA	*databack ;
int error;
//(LENGTH_MS*RATE*16*CHANNELS)/8000
void inizializeResample(int inRate, int outRate, char firstData, )
{
	SRC_STATE * stato = src_callback_new (src_callback_t func, //il puntatore a cui può essere richiamata
	                      1/*converter type*/,
	                      2/*int channel*/,
	                      *error, databack) ;
	assert( stato && "Failed to create resampling context!");
}
void resample(char dataIn[],char dataOut[],int nsamples,int inRate, int outRate)
{
    double scr_ratio=inRate/outRate;
    data=(float)dataIN;
    src_callback_read (stato, src_ratio,nsamples, *data);
	//*out_buffer = malloc(sizeof(in_buffer));
	//out_buffer = malloc(sizeof(out_buffer)*(LENGTH_MS*RATE*16*1)/8000);
	
	int samples_output = av_resample( audio_cntx, //resample context
	(short*)dataOut,	//buffout
	(short*)dataIn,		//buffin
	&samples_consumed,	//&consumed
	nsamples,		//nb_samples
	(sizeof(dataOut)*nsamples),//lenout sizeof(out_buffer)/2
	0);//is_last
	assert( samples_output > 0 && "Error calling av_resample()!" );
	//printf("\nValori Buffer:%s (%i) | Nuovo Buffer:%s (%i) \t\n Numero Sample OUT:%i,Valore DONE:%i\n\n\n\n",dataIn,sizeof(dataIn),dataOut,sizeof(dataOut),samples_output,nsamples);
}

void endResample()
{
    src_delete(stato);
}

int channels=2;
float data_samplerate;


/////////////////////////////////////////////////////
/////////////////////////////////////////////////////
float datiAudio; int nFrame;
void getDasData(float **dst,int num_frames){
  /* Provide sound data here, and only here. */
  **datiAudio=**dst;
  nFrame=num_frames;
}
/////////////////////////////////////////////////////
/////////////////////////////////////////////////////



long getDasResampledData_callback(void *cb_data, float **data){
  static float ret[1024];
  static float ret3[1024];
  static float *ret2[2]={&ret[0],&ret[512]};
  getDasData(ret2,512);
  for(int i=0;i<512;i++){
    ret3[i*2]=ret2[0][i];
    ret3[i*2+1]=ret2[1][i];
  }
  *data=&ret3[0];
  return 512;
}

void getDasResampledData(float **dst,int num_frames){
  double ratio=samplerate/getSourceRate();
  float outsound[num_frames*2];
  long read=src_callback_read(dassrc_state,ratio,num_frames,outsound);
  //fprintf(stderr,"read: %d, num_frames: %d\n",read,num_frames);
  for(int i=0;i<read;i++){
      dst[0][i]=outsound[i*2];
      dst[1][i]=outsound[i*2+1];
  }
  if(read<num_frames){
    float *newdst[2]={dst[0]+read,dst[1]+read};
    getDasResampledData(newdst,num_frames-read);
  }
}


static int process (char inputBuffer, int nframes){
  int ch;
  sample_t *out[channels];
  struct iBuffer {
    float input;
    int size;
  };
  iBuffer inBuffer=malloc(1,sizeof(iBuffer));
  inBuffer.input=(float)inputBuffer;
  inBuffer.size=nframes;
  for(ch=0;ch<channels;ch++){
    out[ch]=(sample_t*)inBuffer.input[ch];
  }
0
  if( (fabs(data_samplerate - 44100 /*Ottenere reale*/)) > 0.1)
    getDasResampledData(out,numSamples);
  else
    getDasData(outputChannelData,numSamples);
  return;

  audioCallback(NULL,0,out,channels,nframes);
} 

int resampleAudio(char input,int done){
  dassrc_state=src_callback_new(getDasResampledData_callback,SRC_QUALITY,2,NULL,NULL);  
  process(input,done);
}

