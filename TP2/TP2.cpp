#include <iostream>
#include <cstring>
#include <fstream>
#include "../CImg.h"

using namespace cimg_library;

int main(int argc, char *argv[]){
    char cNomImgLue[250], nomHisto[250];
    if (argc != 3) {
        std::cerr << "Usage: ImageIn.hdr out/nomhisto.dat" << std::endl;
        exit(1);
    }
    sscanf(argv[1], "%s", cNomImgLue);
    sscanf(argv[2], "%s", nomHisto);

    int cpt = 0;

    CImg<> img(cNomImgLue);
    CImgDisplay display(img, cNomImgLue);
    
    std::ofstream histo(nomHisto);
    
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

