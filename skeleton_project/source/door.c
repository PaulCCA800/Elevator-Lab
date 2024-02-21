#include "door.h"

Door door = {.timer = 0, .door_status = 0, .obstruction = 0};

int Get_timer() {
    return door.timer;
}

bool Get_door_status() {
    return door.door_status;
}

bool Get_obstruction() {
    return door.obstruction;
}

void Close_door() {
    door.door_status = 0;
    //light shit
    elevio_doorOpenLamp(0);
    //timer shit (unecessary? I reset the timer when the door opens)
}

void Open_door() {
    door.door_status = 1;
    //light shit
    elevio_doorOpenLamp(1);
    door.timer = time(NULL);
}