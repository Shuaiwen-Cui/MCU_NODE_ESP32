# ESPTIMER

## Introduction

This document introduces the use of the ESP32 timer.

!!! info "Timer"
    The timer is an integrated function of the microcontroller, which can be flexibly controlled by programming. The timing function of the microcontroller depends on the internal counter. Whenever the microcontroller experiences a machine cycle and generates a pulse, the counter will increase. The main function of the timer is to time. When the set time is reached, it will trigger an interrupt to notify the system that the timing is complete. In the interrupt service function, we can write specific programs to achieve the desired function.
