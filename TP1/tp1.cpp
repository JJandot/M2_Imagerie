#include <iostream>
#include "../CImg.h"

using namespace cimg_library;

int main(int argc, char *argv[]){  
    int cpt = 50;
    int thresholdValue = 128;

    CImg<> img("MR_head.Coronal.hdr"), res = img.get_threshold(thresholdValue);
    CImgDisplay display(img, "MR_head.Coronal.hdr");
    
    while (!display.is_closed()) {
        if(display.is_keyESC())
            break;
            
        if(display.wheel()){
            cpt = display.wheel();
            res = img.get_slice(cpt);
            std::cout << cpt << std::endl;
        }
            
        if(display.is_keyPADADD()){
            thresholdValue = (thresholdValue + 1) % 255;

        }
        if(display.is_keyPADSUB()){
            thresholdValue = (thresholdValue - 1) % 255;
            
        }
        res = img.get_threshold(thresholdValue);
        //(img.get_slice(cpt),res.normalize(0,255)).display();

        //display.display(img.get_slice(cpt));
        display.display(res.get_slice(cpt));
        display.wait();
    }
    
    return 0;
}

