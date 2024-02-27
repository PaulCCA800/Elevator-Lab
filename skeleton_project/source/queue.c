#include "queue.h"
#include "panel.h"

struct Queue queue = {.head = NULL, .size = 0};

struct Queue_ele_s* Queue_ele_constructor(int floor_, bool internal_, bool up_) {
    Queue_ele* q = malloc(sizeof(struct Queue_ele_s));
    q->floor = floor_;
    q->internal = internal_;
    q->up = up_;
    q->next = NULL;    
    q->prev = NULL;
    return q;
}

void Add_queue_ele(Queue_ele* q, int floor) {
    if(Should_be_added(q, floor)) {
        Panel_lights(q, 1);
        Queue_ele* current = queue.head;
        int previous_floor = floor;
        if (current == NULL) {
            Add_to_list(q, NULL, NULL);
        }
        while(current != NULL) {
            if (Compare_queue(current, q, previous_floor)) {
                printf("adding element prior \n");
                fflush(stdout);
                Add_to_list(q, current->prev, current);
            }
            //if last element (always add last)
            else if (current->next == NULL) {
                printf("\n shouldn't be here \n");
                fflush(stdout);
                Add_to_list(q, current, current->next);
                return;
            }
            previous_floor = current->floor;
            current = current->next;
        }
    }
    else {
        return;
    }
}

void Add_to_list(Queue_ele* q, Queue_ele* prev, Queue_ele* next) {
    if (next == NULL) {
        printf("\n huh?\n");
        fflush(stdout);
    }
    
    q->next = next;
    q->prev = prev;
    if (prev == NULL) {
        queue.head = q;
    }
    else {
        prev->next = q;
    }
    if (next != NULL) {
        next->prev = q;
    }
    queue.size ++;   
}

void Delete_queue_ele(Queue_ele *q) {
    int floor = q->floor;
    Queue_ele* current = queue.head;
    //deletes all elements on the floor in question, I also have code for deleting only in the "correct" order
    while (current != NULL) {
        if (current->floor == floor) {
            Panel_lights(current, 0);
            //checks if it's the first element
            if (current->prev == NULL) {
                //checks if it's *also* the last element
                if (current->next == NULL) {
                    Delete_from_list(current);
                    return;
                }
                else {
                current = current->next;
                Delete_from_list(current->prev);
                continue;
                }
            }
            //if it's not the first or last element :)
            else {
                current = current->prev;
                Delete_from_list(current->next);
            } 
        }
        current = current->next;
    }
}

void Delete_from_list(Queue_ele* q) {
    if (queue.head == q) {
        printf("aaa \n");
        fflush(stdout);
        queue.head = q->next;
    }
    if (q->prev != NULL) {
        q->prev->next = q->next;
    }
    if(q->next != NULL) {
        q->next->prev = q->prev;
    }
    free(q); 
    queue.size --;
}

bool Should_be_added(Queue_ele* new_queue, int floor) {
    /*if (queue.size >= 1) {
        //uh what do
        if (floor == new_queue->floor && (new_queue->internal || (new_queue->up && queue.head->floor > floor) || (!new_queue->up && queue.head->floor < floor))) {
            return false;
        }
    }*/
    Queue_ele* current = queue.head;
    while(current != NULL) {
        if (current->floor == new_queue->floor && current->internal == new_queue->internal && (new_queue->internal || (current->up == new_queue->up))) {
            return false;
        }
        current = current->next;
    }
    return true;
}

//denne er litt fuck ._.
bool Compare_queue(Queue_ele* current, Queue_ele* new_queue, int floor) {
    //prioriterer eldste hvis de skal til samme sted, ikke egentlig så farlig, men gir mulighet for forbedring utenfor specs
    if (current->floor == new_queue->floor) {
        return false;
    }
    //spesialtilfelet hvis den skal til samme etasje som første element, gitt at det eksisterer
    if (queue.head->floor == new_queue->floor) {
        if (floor > queue.head->floor && (new_queue->internal || !new_queue->up)) {
            return true;
        }
        else if (floor < queue.head->floor && (new_queue->internal || new_queue->up)) {
            return true;
        }
    }
    //prioritere current over den nye
    if((new_queue->internal && current->internal) || !(new_queue->internal)) {
        //skal oppover og nye er mellom der vi er og dit vi skal
        if (((floor > current->floor) && (floor > new_queue->floor) && (new_queue->floor >= current->floor)) && (!(new_queue->up) || new_queue->internal)) {
            return true;
        }
        //skal nedover of nye er mellom der vi er og dit vi skal
        else if(((floor < current->floor) && (floor < new_queue->floor) && (new_queue->floor <= current->floor)) && (new_queue->up || new_queue->internal)) {
            return true;
        }
        //ellers er den bak denne
        else {
            return false;
        }
    }
    //prioriterer den nye over current
    else {
        //skal oppover og current er mellom den nye og der vi er
        if(((floor > new_queue->floor) && (floor > current->floor) && (current->floor >= new_queue->floor)) && !(current->up)) {
            return false;
        }
        //skal neddover og current er mellom den nye og der vi er
        else if(((floor < new_queue->floor) && (floor < current->floor) && (current->floor <= new_queue->floor)) && current->up) {
            return false;
        }
        //ellers skal den nye forran
        else {
            return true;
        }
    }
}

void printQueue() {
    Queue_ele* current = queue.head;
    while (current != NULL) {
        printf("\n%d", current->floor);
        fflush(stdout);
        if (current->next == NULL) {
            printf("\nshit\n");
            fflush(stdout);
        }
        current = current->next;
    }
}