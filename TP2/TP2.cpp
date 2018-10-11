#include <iostream>
#include <cstring>
#include <vector>
#include <algorithm>
#include "../CImg.h"

using namespace cimg_library;

struct Pixel{
    int x, y, z;
};

bool contains(std::vector<Pixel> l, Pixel p){
    for(int i = 0; i < l.size(); ++i){
        if(l[i].x == p.x && l[i].y == p.y && l[i].z == p.z)
            return true;
    }
    return false;
}


int main(int argc, char *argv[]){  
    int cpt = 0;

    CImg<> img("liver_07.liver.norm.hdr");
    CImgDisplay display(img, "liver_07.liver.norm.hdr");
    
    int currentGrayLevel;
    std::vector<Pixel> l;
    int lCpt = 0;
    
    while (!display.is_closed()) {
        if(display.is_keyESC())
            break;
            
        if(display.button()){
            int x = display.mouse_x() * (float)((float)img.width() / (float)display.width());
            int y = display.mouse_y() * (float)((float)img.height() / (float)display.height());
            
            std::cout << "Clicked at : x = " << x << ", y = " << y << ". Gray level is : " << img(x, y, cpt) << std::endl;
            
            Pixel px;
            px.x = x;
            px.y = y;
            px.z = cpt;
            
            
            l.push_back(px);

            int nbAdd;
            while(true){
                nbAdd = 0;
                for(int index = lCpt; index < l.size(); ++index){
                    lCpt++;
                
                    for(int i = -1; i <= 1; ++i){
                        for(int j = -1; j <= 1; ++j){
                            for(int k = -1; k <= 1; ++k){
                                if(i == j == k == 0)
                                    continue;
                                if(img(l[index].x + i, l[index].y + j, l[index].z + k) >= currentGrayLevel){
                                    Pixel p{l[index].x + i, l[index].y + j, l[index].z + k};
                                    if(!contains(l, p)) {
                                        l.push_back(p);
                                        ++nbAdd;
                                    }
                                }
                            }
                        }
                    }
                }
                if(nbAdd == 0)
                    break;
            }
            
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

