#include "panel.h"

queue Button_pressed() {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 3; j++) {
            if(elevio_callButton(i,j)) {
                queue new_queue;
                new.floor = i;
                new.internal = (j == 2);
                new.up = (j == 0);
                return new_queue;
            }
        }
    }
}

