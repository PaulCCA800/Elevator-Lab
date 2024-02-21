#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <time.h>
#include "driver/elevio.h"
#include "panel.h"
#include "elevator.h"


int main() {
    elevio_init();
    if(elevator.initial) {
        if (elevio_floorSensor() == -1) {
            elevator.state = 'u';
            elevio_motorDirection(1);
            while (elevio_floorSensor() == -1) {
            }
            elevator.state = 's';
            elevator.initial = 0;
            elevio_motorDirection(0);
        }
        elevator.current_floor = elevio_floorSensor();
        elevator.last_floor = elevator.current_floor;
    }
    while (1) {
        Button_pressed(panel);
        if (panel.pressed) {
            if (elevator.state == 'u' || elevator.state == 'd') {
                Add_queue_ele(Queue_ele_constructor(panel.floor,panel.internal,panel.up), elevator.last_floor);
            }
            else {
                Add_queue_ele(Queue_ele_constructor(panel.floor,panel.internal,panel.up), elevator.current_floor);
            }
        }
        Run_elevator();
    }
    return 0;
}

/*
int main(){
    elevio_init();
    
    printf("=== Example Program ===\n");
    printf("Press the stop button on the elevator panel to exit\n");

    elevio_motorDirection(DIRN_UP);

    while(1){
        int floor = elevio_floorSensor();

        if(floor == 0){
            elevio_motorDirection(DIRN_UP);
        }

        if(floor == N_FLOORS-1){
            elevio_motorDirection(DIRN_DOWN);
        }


        for(int f = 0; f < N_FLOORS; f++){
            for(int b = 0; b < N_BUTTONS; b++){
                int btnPressed = elevio_callButton(f, b);
                elevio_buttonLamp(f, b, btnPressed);
            }
        }

        if(elevio_obstruction()){
            elevio_stopLamp(1);
        } else {
            elevio_stopLamp(0);
        }
        
        if(elevio_stopButton()){
            elevio_motorDirection(DIRN_STOP);
            break;
        }
        
        nanosleep(&(struct timespec){0, 20*1000*1000}, NULL);
    }

    return 0;
}
*/