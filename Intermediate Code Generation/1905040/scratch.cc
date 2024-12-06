#include "PPMEncoder.h"
#define intr1 2
#define intr2 3
#define intr3 18
#define intr4 19
#define intr5 20
#define intr6 21
#define PPM_OUT 10
#define CHANNELS 6
volatile long current_time = 0;
volatile long start_time[CHANNELS] = {0};
volatile long pulse[CHANNELS] = {0};
volatile long pulse_width = 0;
const int pulse_max = 2000;
void setup()
{
    Serial.begin(9600);
    pinMode(intr1, INPUT_PULLUP);
    attachInterrupt(digitalPinToInterrupt(intr1), pulse_intr1, CHANGE);
    pinMode(intr2, INPUT_PULLUP);
    attachInterrupt(digitalPinToInterrupt(intr2), pulse_intr2, CHANGE);
    pinMode(intr3, INPUT_PULLUP);
    attachInterrupt(digitalPinToInterrupt(intr3), pulse_intr3, CHANGE);
    pinMode(intr4, INPUT_PULLUP);
    attachInterrupt(digitalPinToInterrupt(intr4), pulse_intr4, CHANGE);
    pinMode(intr5, INPUT_PULLUP);
    attachInterrupt(digitalPinToInterrupt(intr5), pulse_intr5, CHANGE);
    pinMode(intr6, INPUT_PULLUP);
    attachInterrupt(digitalPinToInterrupt(intr6), pulse_intr6, CHANGE);
    ppmEncoder.begin(PPM_OUT);
}
void loop()
{
    // int ppm_out = digitalRead(PPM_OUT);
    // Serial.println(ppm_out);
    // if(pulse[5] < pulse_max){ // Serial.println(pulse[5]); // }
}
void update_channel(int channel)
{
    current_time = micros();
    if (current_time > start_time[channel])
    {
        pulse[channel] = current_time - start_time[channel];
        start_time[channel] = current_time;
    }
    if (pulse[channel] < pulse_max)
    {
        ppmEncoder.setChannel(channel, pulse[channel]);
    }
}
void pulse_intr1() { update_channel(0); }
void pulse_intr2() { update_channel(1); }
void pulse_intr3() { update_channel(2); }
void pulse_intr4() { update_channel(3); }
void pulse_intr5() { update_channel(4); }
void pulse_intr6() { update_channel(5); }