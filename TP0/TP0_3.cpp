#include <iostream>
#include "../CImg.h"

using namespace cimg_library;

int main(int argc, char *argv[]){  
    CImg<> img("DATA/knix.hdr");
    CImgDisplay display(img, "knix.hdr");
    
    int cpt = 1;
    
    while (!display.is_closed()) {
        if(display.is_keyESC())
            break;
            
        if(display.is_keyM()){
            img.blur(2.5);
        }
            
        if(display.wheel())
            cpt = display.wheel() % img.depth();
        
        display.display(img.get_slice(cpt));
        display.wait();
    }
    
    return 0;
}

