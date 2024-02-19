#pragma once


#define N_FLOORS 4

typedef enum { 
    DIRN_DOWN   = -1,
    DIRN_STOP   = 0,
    DIRN_UP     = 1
} MotorDirection;


#define N_BUTTONS 3

typedef enum { 
    BUTTON_HALL_UP      = 0,
    BUTTON_HALL_DOWN    = 1,
    BUTTON_CAB          = 2
} ButtonType;


void elevio_init(void);

//elevator inputs
void elevio_motorDirection(MotorDirection dirn); //assuming it drives the motor based on input (-1, 0, 1)
void elevio_buttonLamp(int floor, ButtonType button, int value); //assuming it activates the specified button
void elevio_floorIndicator(int floor); //assuming it lights up floor indicator based on input
void elevio_doorOpenLamp(int value); //assuming it lights door lamp based on input
void elevio_stopLamp(int value); //assuming it lights up stop lamp based on input

//elevator outputs
int elevio_callButton(int floor, ButtonType button); //what
int elevio_floorSensor(void); //returns value from floor sensor (-1 if no valid output)
int elevio_stopButton(void); //assume returns if stop button is pressed
int elevio_obstruction(void); //what

