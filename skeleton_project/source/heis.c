#include "heis.h"

//midlertidig, skal flyttes til main
int main() {
    while (1) {
        if (panel.pressed) {
            //add to queue
        }
        
    }
}

void Run_motor(Queue current_queue) {
    if (heis.current_floor > current_queue.floor) {
        elevio_motorDirection(-1);
    }
    else if(heis.current_floor < current_queue.floor) {
        elevio_motorDirection(1)
    }
    else {
        elevio_motorDirection(0);
    }
}