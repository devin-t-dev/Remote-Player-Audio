///@file ffmpeg.cpp
// Devin Taietta - (C) GarageAudioLabs - Riproduzione audio diverso da MP3

//Static Linked
#include "ffmpeg.h"
//#include "../Process/EditAudio.cpp"
//Dynamic Linked
extern "C" {
	#include <libavutil/mathematics.h>
	#include <libavformat/avformat.h>
	#include <libswscale/swscale.h>
	#include <libavcodec/avcodec.h>
	#include "../Output/aosender.h"
}
//Constants and Global Var
#define AUDIO_INBUF_SIZE 20480

int FFMPEG_isPaused;
static AVFormatContext*			container;
static int				stream_id;
static AVCodecContext			*ctx;
static AVCodec				*codec;
static int				driver;
static AVPacket				packet;
static AVSampleFormat			sfmt;

const int	buffer_size=AUDIO_INBUF_SIZE + FF_INPUT_BUFFER_PADDING_SIZE;
static uint8_t buffer[buffer_size];
static AVFrame *frame;
void die(const char *msg)
{
	#include <stdlib.h>
	#include <stdio.h>
	#include <string.h>
	#include <math.h>
	fprintf(stderr,"%s\n",msg);
	exit(1);
}

void resetAudio(char * song)
{
	//Record basic information file
	int bits;
	av_register_all();
	AVFormatContext* container=avformat_alloc_context();
	if (avformat_open_input(&container,song,NULL,NULL)<0) die("Impossible to open file");
	if (avformat_find_stream_info(container,NULL)<0) die("Impossible to find any stream");
	av_dump_format(container,0,song,false);
	//Try to find any audio stream in audio file
	stream_id=-1;
	int i;
	for (i=0;i<container->nb_streams;i++){
		if (container->streams[i]->codec->codec_type==AVMEDIA_TYPE_AUDIO)
		{
			stream_id=i;
			break;
		}
	}
	if(stream_id==-1) die("");
	//Try to open audio stream with appropriate codec
	ctx=container->streams[stream_id]->codec;
	codec=avcodec_find_decoder(ctx->codec_id);
	if (codec==NULL) die("There aren't any valid codec for this audio");
	if (avcodec_open2(ctx,codec,NULL)<0) die("Codec can't open this file");
	//Find information for AO
	sfmt=ctx->sample_fmt;
	//asign device sample rate depend on the input stream
	if (sfmt==AV_SAMPLE_FMT_U8){
		bits=8;
	}else if(sfmt==AV_SAMPLE_FMT_S16){
		bits=16;
	}else if (sfmt==AV_SAMPLE_FMT_S32){
		bits=32;
	}
	initAudioDev(bits, (ctx->sample_rate), (ctx->channels));
	//data packet read from the stream
	av_init_packet(&packet);
	packet.data=buffer;
	packet.size=buffer_size;
	//allocating memory for frame, where the decoded data will be writen
	frame=avcodec_alloc_frame();
}
int playAudio()
{
	int frameFinished=0;
	if (av_read_frame(container,&packet)>0&&FFMPEG_isPaused==0)
	{
		if(packet.stream_index==stream_id){
			int len=avcodec_decode_audio4(ctx,frame,&frameFinished,&packet);
			if(frameFinished){
				writeAudio((char*)frame->extended_data[0],frame->linesize[0]);				
			}
		}
	}else{
		if(FFMPEG_isPaused==0) return 2;
	}
	return 0;
}
void freeAudio()
{
	freeAudioDev();
}

void setAudioStatus(int value)
{
	if(value==0||value==1)
	{
		FFMPEG_isPaused=value;
	} else {
		FFMPEG_isPaused=!FFMPEG_isPaused;
	}
}
