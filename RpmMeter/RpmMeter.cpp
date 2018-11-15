#include "RpmMeter.h"
#include "Arduino.h"

#define MEASURETIMING 1 //use pin12 as a time measuring signal for the interrupt routine

RpmMeter RPM;              // preinstatiate

void ISR_rpmSignal()
{
    // declare Interrupt routine for the
    // handle signal event from hall sensor here to measure speed of motor
    RPM.isrCallback();
}



// class

void RpmMeter::initialize(byte signal_pin, byte sig_per_turn, byte samples)
{
    pinMode(signal_pin, INPUT);
    attachInterrupt(digitalPinToInterrupt(signal_pin), ISR_rpmSignal, RISING);
    signals_per_turn = sig_per_turn;
    samples_amount = samples;
    samples_cnt = 0;
    max_turn_mics = 1800000;
    rpm_factor = 60000000 * samples_amount / signals_per_turn;
#ifdef MEASURETIMING    
    pinMode(12, OUTPUT);
#endif
}

void RpmMeter::isrCallback()
{
#ifdef MEASURETIMING    
    PORTB &= B11101111; // set LOW
#endif
    rpmCycleMicsLastSignal = micros();
    if (++samples_cnt == samples_amount)
    {
        rpmCycleMicsLast = rpmCycleMics;
        rpmCycleMics = rpmCycleMicsLastSignal;
        samples_cnt = 0;
    }
#ifdef MEASURETIMING    
    PORTB |= B00010000; // set HIGH
#endif 
}


unsigned int RpmMeter::getRpm()
// calculates rounds per minute from microsseconds
// it returns an integer value
{

    if (micros() - rpmCycleMicsLastSignal > max_turn_mics)
    {
        // return zero, if last turn was more than 1.2 sec before...
        return 0;
    }
    else
    {
        // inbetween leave the rpmResult as it is
        unsigned long delta =  rpmCycleMics - rpmCycleMicsLast;
        return int(rpm_factor / delta);
    }

}

unsigned long RpmMeter::getMicrosPerTurn()
{
    return rpmCycleMics - rpmCycleMicsLast;
};

