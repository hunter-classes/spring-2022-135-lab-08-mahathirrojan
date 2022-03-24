#include <iostream>
#include <array> 
#include <string> 
#include <cassert>
#include "imageio.h"
#include "functions.h"

const std::array<std::string, 2> names_of_images = {"image1.pgm", "image2.pgm"};
const std::array<std::string, 6> task = {"A", "B", "C", "D", "E", "F"}; 

typedef void (*Functions) (std::string name, std::string out_name); 


int main() { 
    std::string input; 
    std::string out_name; 

    Functions funcs[] = {invert, invert_half, box, frame, scale, pixelate}; 

    for(int z = 0; z < task.size(); z++) {
        for(int i = 0; i < names_of_images.size(); i++) {
            std::string out_name = "task" + task[z] + "-" + names_of_images[i];
            funcs[z](names_of_images[i], out_name);
        }
    }

    return 0;
}