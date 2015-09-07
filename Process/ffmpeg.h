///@file
///Devin Taietta - ffmpeg.h Riproduzione file Flac,Wav
#ifndef FFMPEG_H_
#define FFMPEG_H_
void resetAudio(char * song);
int playAudio();
void freeAudio();
void setAudioStatus(int value);
//int audioGetPlayStatus();
#endif
