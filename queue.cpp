#include "queue.h"

queue make_random_queue_object() {
    std::random_device rd;
    std::default_random_engine generator(rd());
    std::uniform_int_distribution<int> distribution(1,4);
    int num = distribution(generator);
    queue new_queue;
    new_queue.floor = num;
    std::uniform_int_distribution<int> bool_distribution(0,1);
    bool num2 = bool_distribution(generator);
    new_queue.internal = num2;
    bool num3 = bool_distribution(generator);
    new_queue.up = num3;
    return new_queue;
}

std::vector<queue> make_queue(int number, int floor) {
    std::vector<queue> new_queue;
    new_queue.push_back(make_random_queue_object());
    for (int i = 1; i < number; i++) {
        add_queue(new_queue, make_random_queue_object(), floor);
    }
    return new_queue;
}

void print_queue_object(queue current) {
    std::cout << std::endl << "Floor: " << current.floor << std::endl;
    std::cout << "Internal: " << current.internal << std::endl;
    std::cout << "Up: " << current.up;
}

bool compare_queue(queue current, queue added, int floor, int next) {
    //prioriterer alltid eldste hvis de skal til samme sted (usikker på denne egentlig, ment tror den nese fikser?)
    if (current.floor == added.floor) {
        return false;
    }

    //spesialtilfelet hvis den skal til samme etasje som første element
    if (next == added.floor) {
        if (floor > next && (added.internal || !added.up)) {
            return true;
        }
        else if (floor < next && (added.internal || added.up)) {
            return true;
        }
    }
    
    //prioritere current over den nye
    if((added.internal && current.internal) || !added.internal) {
        if ((floor > current.floor && floor > added.floor && added.floor >= current.floor) && (!added.up || added.internal)) {
            return true;
        }
        else if((floor < current.floor && floor < added.floor && added.floor <= current.floor) && (added.up || added.internal)) {
            return true;
        }
        else {
            return false;
        }
    }
    //prioriterer den nye over current
    else {
        //skal oppover og current er mellom målet og der vi er
        if((floor > added.floor && floor > current.floor && current.floor >= added.floor) && !current.up) {
            return false;
        }
        else if((floor < added.floor && floor < current.floor && current.floor <= added.floor) && current.up) {
            return false;
        }
        else {
            return true;
        }
    }
}

//something fuck (not anymore?)
bool should_be_added(std::vector<queue> current, queue added, int floor) {
    if (current.size() >= 1) {
        if (floor == added.floor && (added.internal || (added.up && current.at(0).floor > floor) || (!added.up && current.at(0).floor < floor))) {
            return false;
        }
    }
    else {
        if(floor == added.floor) {
            return false;
        }
    }
    for (int i = 0; i < current.size(); i++) {
        if (current.at(i).floor == added.floor && current.at(i).internal == added.internal && (added.internal || (current.at(i).up == added.up))) {
            return false;
        }
    }
    return true;
}

void add_queue(std::vector<queue> &current, queue added, int floor) {
    if (!should_be_added(current, added, floor)) {
        return;
    }
    int next = 0;
    int previous_floor = floor;
    if (current.size() > 0) {
        next = current.at(0).floor;
    }
    for (int i = 0; i < current.size(); i++) {
        if (compare_queue(current.at(i), added, previous_floor, next)) {
            current.insert(current.begin() + i, added);
            return;
        }
        previous_floor = current.at(i).floor;
    }
    current.insert(current.end(),added);
}

void remove_queue(std::vector<queue> &current) {
    int floor = current.at(0).floor;
    current.erase(current.begin());
    std::vector<int> to_delete;
    for (int i = 0; i < current.size(); i++) {
        if(floor == current.at(i).floor && (((current.at(0).floor <= floor) && !current.at(i).up) || ((current.at(0).floor >= floor) && current.at(i).up))) {
            to_delete.push_back(i);
        }
    }
    for (int i = 0; i < to_delete.size(); i++) {
        current.erase(current.begin() + to_delete.at(i) - i);
    }
    
}

void print_queue(std::vector<queue> current) {
    for (int i = 0; i < current.size(); i++) {
        print_queue_object(current.at(i));
        std::cout << std::endl;
    }
}