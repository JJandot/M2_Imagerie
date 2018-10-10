#include <iostream>
#include <cstring>
#include "../CImg.h"

using namespace cimg_library;

int main(int argc, char *argv[]){  
    int cpt = 100;
    int thresholdValue = 70;
    int erosionCpt = 5;

    CImg<> img("MR_head.Coronal.hdr"), res = img.get_threshold(thresholdValue);
    CImgDisplay display(img, "MR_head.Coronal.hdr");
    
    bool algo = false;
    
    while (!display.is_closed()) {
        if(display.is_keyESC())
            break;
            
        if(display.is_keyA())
            algo = true;
        
    
        if(display.wheel()){
            cpt += display.wheel();
            display.set_wheel();
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
        
        if(algo){
            std::cout << "Start erosion" << std::endl;
            for(int i = 0; i < erosionCpt; ++i)
                res.erode(2, 2, 2);

            res.label(0, 0);
            
            
            int histo[256];
            memset(histo, 0, sizeof(histo));

            for(int i = 0; i < img.width(); ++i){
                for(int j = 0; j < img.height(); ++j){
                    for(int k = 0; k < img.depth(); ++k){
                        histo[(int)res(i, j, k)]++;
                    }
                }
            }
            
            int max = 0;
            int maxI = 0;
            for(int i = 0; i < 256; ++i){
                if(histo[i] > max){
                    max = histo[i];
                    maxI = i;
                }
            }

            for(int i = 0; i < img.width(); ++i){
                for(int j = 0; j < img.height(); ++j){
                    for(int k = 0; k < img.depth(); ++k){
                        if(res(i, j, k) == maxI)
                            res(i, j, k) = 0;
                        else
                            res(i, j, k) = 255;
                    }
                }
            }
            
            
            for(int i = 0; i < erosionCpt; ++i)
                res.dilate(2, 2, 2);
                
            display.display(res.get_slice(cpt));
            algo = false;
        }
        display.wait();
    }
    return 0;
}

