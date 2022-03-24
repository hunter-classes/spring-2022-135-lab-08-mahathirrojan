#include <iostream> 
#include <string> 
#include <cassert>
#include <vector>
#include <fstream>
#include "functions.h"
#include "imageio.h"




void invert(std::string name, std::string out_name) {
    int height, width; 
    int image[MAX_H][MAX_W];
    readImage(name, image, height, width); 

    int out[MAX_H][MAX_W];

    for (int hor = 0; hor < height; hor++) {
		for (int ver = 0; ver < width; ver++) {
			assert(image[hor][ver] < 256);
			assert(image[hor][ver] >= 0);
            int temp = image[hor][ver];
            temp = 255 - temp; 
			out[hor][ver] = temp; 
		}
	}

    writeImage(out_name, out, height, width);
    return;
}

void invert_half(std::string name, std::string out_name) {
    int height, width; 
    int image[MAX_H][MAX_W];
    readImage(name, image, height, width); 

    int out[MAX_H][MAX_W];

    for (int hor = 0; hor < height; hor++) {
		for (int ver = 0; ver < width / 2; ver++) {
			assert(image[hor][ver] < 256);
			assert(image[hor][ver] >= 0);
			out[hor][ver] = image[hor][ver];
		}

        for (int ver = width / 2; ver < width; ver++) {
			assert(image[hor][ver] < 256);
			assert(image[hor][ver] >= 0);
            int temp = image[hor][ver];
            temp = 255 - temp; 
			out[hor][ver] = temp;
		}
	}

    writeImage(out_name, out, height, width);
    return;
}

void box(std::string name, std::string out_name) {
    int height, width; 
    int image[MAX_H][MAX_W];
    readImage(name, image, height, width); 

    int out[MAX_H][MAX_W];

    for (int hor = 0; hor < height; hor++) {
		for (int ver = 0; ver < width; ver++) {
			assert(image[hor][ver] < 256);
			assert(image[hor][ver] >= 0);
        
            if((height / 4) * 3 >= hor && width / 4 <= ver && height / 4 <= hor && (width / 4) * 3 >= ver) { 
                out[hor][ver] = 255;
            } else {
                out[hor][ver] = image[hor][ver];
            }
        }
    }

    writeImage(out_name, out, height, width);
    return;
}

void frame(std::string name, std::string out_name) {
    int height, width; 
    int image[MAX_H][MAX_W];
    readImage(name, image, height, width); 

    int out[MAX_H][MAX_W];

    for (int hor = 0; hor < height; hor++) {
		for (int ver = 0; ver < width; ver++) {
			assert(image[hor][ver] < 256);
			assert(image[hor][ver] >= 0);


            if((height / 4 <= hor && height / 4 + 1 > hor && width / 4 <= ver && (width / 4) * 3 >= ver) || 
			((height / 4) * 3 >= hor && (height / 4) * 3 - 1 < hor && width / 4 <= ver && (width / 4) * 3 >= ver) || 
			(width / 4 <= ver && width / 4 + 1 > ver && height / 4 <= hor && (height / 4) * 3 >= hor) || 
			((width / 4) * 3 - 1 < ver && (width / 4) * 3 >= ver && height / 4 <= hor && (height / 4) * 3 >= hor)) { 
                out[hor][ver] = 255; 
            } else { 
                out[hor][ver] = image[hor][ver];
            }
		}
	}

    writeImage(out_name, out, height, width);
    return; 
}

void scale(std::string name, std::string out_name) {
    int height, width; 
    int image[MAX_H][MAX_W];
    readImage(name, image, height, width); 

    std::ofstream ostr;
	ostr.open(out_name);
	if (ostr.fail()) {
		std::cout << "Unable to write file\n";
		exit(1);
	};

    std::vector<int> row_vector; 


	ostr << "P2" << std::endl;

	ostr << width * 2 << ' ';
	ostr << height * 2 << std::endl;
	ostr << 255 << std::endl;

	for (int hor = 0; hor < height; hor++) {
		for (int ver = 0; ver < width; ver++) {
			assert(image[hor][ver] < 256);
			assert(image[hor][ver] >= 0);

			ostr << image[hor][ver] << ' ';
            ostr << image[hor][ver] << ' ';

            row_vector.push_back(image[hor][ver]);
            row_vector.push_back(image[hor][ver]);
		}

        for(int z = 0; z < row_vector.size(); z++) {
            ostr << row_vector[z] << " ";
        }

        ostr << std::endl;
        row_vector.clear();
	}

	ostr.close();
}

void pixelate(std::string name, std::string out_name) {
    int height, width; 
    int image[MAX_H][MAX_W];
    readImage(name, image, height, width); 

    std::ofstream ostr;
	ostr.open(out_name);
	if (ostr.fail()) {
		std::cout << "Unable to write file\n";
		exit(1);
	};


	ostr << "P2" << std::endl;

	ostr << width << ' ';
	ostr << height << std::endl;
	ostr << 255 << std::endl;

	std::vector<int> nums; 


	for (int hor = 0; hor < height; hor += 2) {
		for (int ver = 0; ver < width; ver += 2) {
			assert(image[hor][ver] < 256);
			assert(image[hor][ver] >= 0);


			double temp = (image[hor][ver] + image[hor][ver + 1] + image[hor + 1][ver] + image[hor + 1][ver + 1]) / 4;

			if(temp - (int)temp != 0) { 
				temp = (int)temp + 1; 
			}
			
			nums.push_back((int)temp);
			nums.push_back((int)temp); 

		}
		
		for(int z = 0; z < 2; z++) { 
			for(int i = 0; i < width; i++) { 
				ostr << nums[i] << ' ';
				ostr << std::endl;
			}
		}

		nums.clear();
	}

	ostr.close();
}