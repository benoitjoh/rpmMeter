# module rpmMeter #

This library can be used to build to measure the rotation speed of a motor in  rounds per minutes. 
To install just copy the folder with c++ sources in the library folder of Arduino IDE.

## Principle ##

A signal is initiated by the rotator. It is wired to PD2 or PD3, the two pins that can be configured for external interrupts.
One trick is to make it possible to call a class method in the interrupt routine. Therefor the class has to be pre instanciated in the cpp file. So the whole interrupt handling can be encapsulated in the classdefinition.

If a Tachogenerator is used (e.g. in a AC motor in washing machines) you can use the schema given to prepare the signal. 

Also a hall-sensor in combination with a piece of a powerful magnet attached to the rotator is possible. 

The signal invokes the interrupt and measures the time since the last interrupt. 
You have to pass the count of signals per turn to the constructor, then the rpm can be computed. 
The Rpm value then is stored an can be read by getRpm() any time you want.

## Circuit schema ##

![graphic](https://github.com/benoitjoh/rpmMeter/blob/master/schema_rpm_tachogenerator.png)

## Usage ##

### Initialization
initialize like this:

```c++
#define PIN_IN_RPM_SIGNAL   2  // pin for signal (can only be 2 or 3) 
#define SIG_PER_TURN 1    // signals during one turn
#define SAMPLES_AMOUNT 1  // amount of signals after that a calculation is done
#include <RpmMeter.h>
// RPM is preinstantiated as RpmMeter. Initialization later in setup()


setup
    {
    // RpmMeter
    RPM.initialize(PIN_IN_RPM_SIGNAL, SIG_PER_TURN, SAMPLES_AMOUNT); 
    }
```

### getRpm() ###

to get the rpm value just call getRpm()

```c++
myRoundsPerMinute = getRpm()
```
### getMicrosPerTurn() ###

you can also get the time (in microseconds) that is needed for one turn.

```c++
myRoundsPerMinute = getMicrosPerTurn()
```



(c) [Johannes Benoit 2016](mailto:jbenoit@t-online.de)


