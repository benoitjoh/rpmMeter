#include "RpmMeter.h"
#include "Arduino.h"

RpmMeter RPM;              // preinstatiate

// if one turn lasts longer than this value, we assume rpm = 0
#define MAX_TURN_MICROSECS 1500000

// interrupt routine
void ISR_rpmSignal()
{
    // declare Interrupt routine for the
    // handle signal event from hall sensor here to measure speed of motor
    RPM.isrCallback();
}


// class
void RpmMeter::initialize(byte signal_pin, byte sig_per_turn, byte samples)
{
	// attach the above interrupt subroutine
    pinMode(signal_pin, INPUT);
    attachInterrupt(digitalPinToInterrupt(signal_pin), ISR_rpmSignal, RISING);

    signals_per_turn = sig_per_turn;
    samples_amount = samples;
    samples_cnt = 0;
    rpm_factor = 60000000 * samples_amount / signals_per_turn;
}

void RpmMeter::isrCallback()
{
    rpmCycleMicsLastSignal = micros();
    if (++samples_cnt == samples_amount)
    {
        rpmCycleMicsLast = rpmCycleMics;
        rpmCycleMics = rpmCycleMicsLastSignal;
        samples_cnt = 0;
    }
}


unsigned int RpmMeter::getRpm()
// calculates rounds per minute from microsseconds
// it returns an integer value
{
    if (micros() - rpmCycleMicsLastSignal > MAX_TURN_MICROSECS)
    {
        // return zero, if last turn was more than 1.5 sec before...
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

