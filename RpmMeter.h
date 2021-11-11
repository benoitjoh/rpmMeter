// **************************************************************************
//
// library to encapsulate measurement of turnarounds
// pin 2 or 3 can be used as an input pin for a signal from a light- or hallsensor e.g.
// or anything else that gives one peak each turn
//
// example of usage:
//
// #include<RpmMeter.h>
// #define PIN_SIGNAL   2  // pin for the signal of sensor
//
// void setup()
// {
// RPM.initialize(PIN_SIGNAL, 1, 1); // RpmMeter
// }
//
// //access value like this:
// myValue = RPM.getRpm();
//                                                       Johannes Benoit 2017
// **************************************************************************

#ifndef RPMMETER_H
#define RPMMETER_H

#include "Arduino.h"


class RpmMeter
{
    public:
        // methods
        void initialize(byte input_pin, byte sig_per_turn, byte samples);
        unsigned int getRpm();
        unsigned int getRps();
        unsigned long getMicrosPerTurn();
        void isrCallback();


    private:
        // properties
        unsigned long rpmCycleMics;     // timestamp of new measurement
        unsigned long rpmCycleMicsLast; // timestamp of last measurement
        unsigned long rpmCycleMicsLastSignal; // timestamp of last signal

        byte signals_per_turn;       // how many singnals we receive during on turn
        byte samples_amount;       // how many samples shall be accumulated=
        byte samples_cnt;          // singnals counter
        unsigned long rpm_factor; // conversion factor from mysecs to rpm;

    protected:


};
extern RpmMeter RPM;
#endif // RPMMETER_H
