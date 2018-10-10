#include <iostream>
#include "../CImg.h"

using namespace cimg_library;

int main(int argc, char *argv[]){  
    int cpt = 50;
    int thresholdValue = 128;

    CImg<> img("MR_head.Coronal.hdr"), res = img.get_threshold(thresholdValue);
    CImgDisplay display(img, "MR_head.Coronal.hdr");
    
    bool algo = false;
    
    while (!display.is_closed()) {
        if(display.is_keyESC())
            break;
            
        if(display.is_keyA())
            algo = true;
        
        if(!algo){
            if(display.wheel()){
                cpt = display.wheel();
            }
                
            if(display.is_keyPADADD()){
                thresholdValue = (thresholdValue + 1) % 255;
                res = img.get_threshold(thresholdValue);
            }
            if(display.is_keyPADSUB()){
                thresholdValue = (thresholdValue - 1) % 255;
                res = img.get_threshold(thresholdValue);
            }
            display.display(res.get_slice(cpt));
        }
        else{
            std::cout << "algo inc" << std::endl;
        }
        display.wait();
    }
    
    return 0;
}

