#include <ao/ao.h>

void initAudioDev(int bits, long rate,int channels);
void freeAudioDev();
int writeAudio(char* buffer, uint_32 numBytesMemory);
