#include "panel.h"
#include <stdbool.h>

struct queue {
    int floor;
    bool internal;
    bool up;
};

//need to define the entire queue object here somehow (mostly as it determines the syntax for the rest of the code)