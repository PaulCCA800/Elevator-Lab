#include "panel.h"

Panel panel = {.pressed = 0, .floor = -1, .internal = 0, .up = 0};

//maybe it should have a check if the button is active? Too many for loops?
//(I mean that would be the function I made to check if something should be added to the queue so idk)
void Button_pressed() {
    panel.pressed = 0;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 3; j++) {
            if(elevio_callButton(i,j)) {
                panel.pressed = 1;
                panel.floor = i;
                panel.internal = (j == 2);
                panel.up = (j == 0);
                return;
            }
        }
    }
}

void Panel_lights(struct Queue_ele_s* q, int value) {
    if (q->internal) {
        elevio_buttonLamp(q->floor, 2, value);
    }
    else {
        elevio_buttonLamp(q->floor, 1-q->up, value);
    }
}
