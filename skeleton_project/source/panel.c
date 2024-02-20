#include "panel.h"

//maybe it should have a check if the button is active? Too many for loops?
//(I mean that would be the function I made to check if something should be added to the queue so idk)
void Button_pressed(Panel panel) {
    Queue new_queue;
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