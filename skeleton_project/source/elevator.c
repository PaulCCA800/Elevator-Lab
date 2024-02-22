#include "elevator.h"

Elevator elevator = {.current_floor = -1, .last_floor = -1, .initial = 1, .state = 'i', .stop_button = 0};

//main function that runs for each loop in main, unsure if elevator.intial should be included here as well
void Run_elevator() {
    if (elevator.state == 'i') {
        // prolly do nothing?
    }
    else if (elevator.state == 's') {
        Stop_state();
    }
    else if (elevator.state == 'd') {
        Down_state();
    }
    else if (elevator.state == 'u') {
        Up_state();
    }
    else {
        //shit gone fucked
        elevator.state = 's';
        elevio_motorDirection(0);
    }
    elevio_floorIndicator(elevator.last_floor);
}

//what happens when elevator is in the stopped state
void Stop_state() {
    time_t fire_t = 3;
    //if stop button, remain in stopped state
    if(elevator.stop_button) {
        //clear queue
        return;
    }
    //checks door state and what to do with door
    else if(Get_door_status()) {
        if(Get_obstruction()) {
            Open_door();
            return;
        }
        else if(Get_timer() + fire_t > time(NULL)){
            return;
        }
        else {
            printf("c");
            fflush(stdout);
            Close_door();
            return;
        }
    }
    //moves onto queue
    else {
        //if top of queue is higher, sets state to up and starts moving up
        if (queue.size == 0) {
            return;
        }
        else if (Get_current().floor > elevator.current_floor) {
            elevator.state = 'u';
            elevio_motorDirection(1);
        }
        //if top of queue is lower, sets state to down and starts moving down
        else if(Get_current().floor < elevator.current_floor) {
            elevator.state = 'd';
            elevio_motorDirection(-1);
        }
        //if top of queue goes to current floor, reset state (not necessary, but a formality) and open the door
        else if(Get_current().floor == elevator.current_floor) {
            elevator.state = 's';
            Open_door();
            Delete_queue_ele(queue.head);
        }
        //nothing in queue? does nothing
        else {
            return;
        }
    }
}

//What happens when the elevator is in the up state
void Up_state() {
    //checks where elevator is and updates variables accordingly
    elevator.current_floor = elevio_floorSensor();
    if(elevator.current_floor != -1) {
        elevator.last_floor = elevator.current_floor;
        elevio_floorIndicator(elevator.last_floor);
    }
    //stop button stops elevator
    if(elevator.stop_button) {
        elevator.state = 's';
        elevio_motorDirection(0);
        //Dette er smålig cursed, men tror det burde funke helt greit
        //altså skal cleare hele queue
        while (queue.head != NULL) {
            Delete_queue_ele(queue.head);
        }
        return;
    }
    //arrived at floor
    if(Get_current().floor == elevator.current_floor) {
        elevator.state = 's';
        elevio_motorDirection(0);
        Open_door();
        Delete_queue_ele(queue.head);
    }
    //else it's still travelling and nothing happens
}

//What happens when the elevator is in the down state, identical to what happens in the up state, only difference is the flag used for initilization and queue handling
void Down_state() {
    //checks where elevator is and updates variables accordingly
    elevator.current_floor = elevio_floorSensor();
    if(elevator.current_floor != -1) {
        elevator.last_floor = elevator.current_floor;
        elevio_floorIndicator(elevator.last_floor);
    }
    //stop button stops elevator
    if(elevator.stop_button) {
        elevator.state = 's';
        elevio_motorDirection(0);
        //Dette er smålig cursed, men tror det burde funke helt greit
        //altså skal cleare hele queue
        while (queue.head != NULL) {
            Delete_queue_ele(queue.head);
        }
        return;
    }
    //arrived at floor
    if(Get_current().floor == elevator.current_floor) {
        elevator.state = 's';
        elevio_motorDirection(0);
        Open_door();
        Delete_queue_ele(queue.head);
    }
    //else it's still travelling and nothing happens
}