#include "door.h"
#include <stdio.h>

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
    elevio_doorOpenLamp(0);
}

void Open_door() {
    door.door_status = 1;
    elevio_doorOpenLamp(1);
    door.timer = time(NULL);
}