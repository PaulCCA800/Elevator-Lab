#pragma once
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include "driver/elevio.h"
#include "elevator.h"

typedef struct Queue_ele_s {
    int floor;
    bool internal;
    bool up;

    struct Queue_ele_s* next;
    struct Queue_ele_s* prev;
} Queue_ele;

struct Queue {
    struct Queue_ele_s* head;
    int size;
};

extern struct Queue queue;

//need to define the entire queue object here somehow (mostly as it determines the syntax for the rest of the code)

Queue_ele* Queue_ele_constructor(int floor, bool internal, bool up);

void Add_queue_ele(Queue_ele* q, int floor);
void Add_to_list(Queue_ele* q, Queue_ele* prev, Queue_ele* next);
void Delete_queue_ele(Queue_ele* q);
void Delete_from_list(Queue_ele* q);

bool Should_be_added(Queue_ele* new_queue, int floor);
bool Compare_queue(Queue_ele* current, Queue_ele* new_queue, int floor);

void printQueue();