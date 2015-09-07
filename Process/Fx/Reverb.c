
void applyReverb(short buffer[])
{
	int delayMilliseconds = 500; // half a second
	int delaySamples = 
		  (int)((float)delayMilliseconds * 44.1f); // assumes 44100 Hz sample rate
	float decay = 0.5f;
    int i=0;
    /*for (i = 0; i < buffer.length - delaySamples; i++)
	{
		  // WARNING: overflow potential
		  buffer[i + delaySamples] += (short)((float)buffer[i] * decay);
    }*/
}
