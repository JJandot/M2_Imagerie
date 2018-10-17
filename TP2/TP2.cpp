#include <iostream>
#include <cstring>
#include <fstream>
#include "../CImg.h"

using namespace cimg_library;

int main(int argc, char *argv[]){  
    int cpt = 0;

    CImg<> img("liver_07.liver.norm.hdr");
    CImgDisplay display(img, "liver_07.liver.norm.hdr");
    
    std::ofstream histo("histo.dat");
    
    while (!display.is_closed()) {
        if(display.is_keyESC())
            break;
            
        if(display.button()){
            int x = display.mouse_x() * (float)((float)img.width() / (float)display.width());
            int y = display.mouse_y() * (float)((float)img.height() / (float)display.height());
            
            std::cout << "Clicked at : x = " << x << ", y = " << y << ". Gray level is : " << img(x, y, cpt) << std::endl;
            
            for(int i = 0; i <= 255; ++i){
                CImg<> image = img;
                CImg<> region;
                int regionSize = 0;
                unsigned char white[] = {255, 255, 255};
                image.draw_fill(x, y, cpt, white, 1, region, i);
                for(int j = 0; j < region.width(); ++j){
                    for(int k = 0; k < region.height(); ++k){
                        if(region(j, k) > 0)
                            ++regionSize;
                    }
                }
                histo << i << " " << regionSize << std::endl;
            }
            std::cout << "End procesing" << std::endl;
            histo.close();
        }
        
        if(display.wheel()){
            cpt += display.wheel();
            display.set_wheel();
        }
        display.display(img.get_slice(cpt));
        display.wait();
    }
    return 0;
}

