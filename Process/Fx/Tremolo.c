/*This code has the basic functions to perform amplitude modulation

or tremolo effect on audio signals according to

(LFO signal) m [n]---->[+]------------>[*]---------------> y[n] (tremolo modulated signal)

                                   ^                   ^

                                   |                    |

                                   |                    |

                               offset              x[n](input signal)

 The LFO is a triangle signal that modulates the audio signal by means of the input

parameters to the function Tremolo_init(short effect_rate,double depth).
Source: dsprelated.com
*/
/************************Tremolo.c*************************/

#include "Tremolo.h"

static double dep;
static short counter_limit;
static short control;
static short mod;
static double offset;

void Tremolo_init(short effect_rate,double depth) {
    dep     = depth; 
    control = 1;
    mod     = 0;
    counter_limit = effect_rate;
    offset  = 1 - dep;
}

double Tremolo_process(double xin) {
    double yout;
    double m;

    m = (double)mod*dep/counter_limit;
    yout = (m + offset)*xin;
    return yout;
}

void Tremolo_sweep(void) {

            mod += control;
  
            if (mod > counter_limit) {
                control = -1;
            } 
            else if(!mod) {
                control = 1;
            }
}

/********************Tremolo.h****************************/
#ifndef __TREMOLO_H__
#define __TREMOLO_H__

extern void Tremolo_init(short effect_rate,double depth);
extern double Tremolo_process(double xin);
extern void Tremolo_sweep(void);

#endif

/*Usage example*/
#include "Tremolo.h"

void main(void) {
    double xin;
    double yout;
    Tremolo_init(4000,1);

    while(1) {
        if (new_sample_flag()) {
            /*When there's new sample at your ADC or CODEC input*/
            /*Read the sample*/
            xin = read_sample();
            /*Apply the Tremolo_process function to the sample*/
            yout = Tremolo_process(0.7*temp);

            /*Send the output value to your DAC or codec output*/
            write_output(yout);
            /*Makes LFO vary*/
            Tremolo_sweep();
        }                              
    }
}
