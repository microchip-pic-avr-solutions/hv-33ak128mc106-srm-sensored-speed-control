# hv-33ak128mc106-srm-sensored-speed-control v1.0.1
### Release Highlights
This is the second revision of the code for magnetic rotor position sensor-based speed control of Switched Reluctance Motor (SRM) on high voltage development platform with dsPIC33AK128MC106 MC DIM(EV62P66A).  
The code is set up for running custom made 4phase 8/6 pole SR Motor.
This speed control firmware is tested under loading up to the rated current of the motor.

### Features Added\Updated
Updated hal for latest toolboxes.
Updated readme.

# hv-33ak128mc106-srm-sensored-speed-control v1.0.0
### Release Highlights
This is the first version of code for magnetic rotor position sensor-based speed control of Switched Reluctance Motor (SRM) on high voltage development platform with dsPIC33AK128MC106 MC DIM(EV62P66A). 
The code is set up for running custom made 4phase 8/6 pole SR Motor.
This speed control firmware is tested under loading up to the rated current of the motor.


### Features Added\Updated
- Code flow is managed by State Machines to allow seamless control of SRM.
- Speed and Current control of SRM in both forward and reverse direction.
- PI control for speed loop and hysteresis current controller for current control.
- Supports Shunt or Contact current sensors for current measurement.
- Assigned functions of push buttons and potentiometer in the firmware:
	1. Push Button #1(BUTTON 1) starts and stops motor. 
	2. Push Button #2(BUTTON 2) changes the direction of rotation
	3. The Speed of the motor can be controlled using potentiometer(POT) in its entire speed range.
- Over Current and Over Voltage Fault.
- Software limit on the phase current.
- DC Bus current and voltage protection using dsPIC� features such as PWM PCI.
- Phase over current protection with contact current sensors using dsPIC� features such as PWM PCI.


