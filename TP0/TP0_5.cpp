#include <iostream>
#include "../CImg.h"

using namespace cimg_library;

int main(int argc, char *argv[]){  
    CImg<> img("DATA/knix.hdr");
     
    
    CImgDisplay disp(img, "knix.hdr");
    
    
    int cpt = 1;
    
    int x = img.width() / 2;
    int y = img.height() / 2;
    int z = img.depth() / 2;
    
    while (!disp.is_closed()) {
        if(disp.is_keyESC())
            break;
            
        if(disp.is_keyM()){
            img.blur(2.5);
        }
            
        if(disp.wheel()){
            x = abs(x + disp.wheel())%img.height();
            y = abs(y + disp.wheel())%img.width();
            z = abs(z + disp.wheel())%img.depth();
        }
        
        disp.display(img.get_projections2d(x, y, z));
        disp.wait();
    }
    
    return 0;
}

