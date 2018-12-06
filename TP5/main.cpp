#include <iostream>
#include <cstring>
#include "../CImg.h"

using namespace cimg_library;

int main(int argc, char *argv[]){
    char cNomImgF[250], cNomImgG[250];
    int nbIteration;
    if (argc != 4) {
        std::cerr << "Usage: ImageF.hdr ImageG.hdr nbIteration" << std::endl;
        exit(1);
    }
    sscanf(argv[1], "%s", cNomImgF);
    sscanf(argv[2], "%s", cNomImgG);
    sscanf(argv[3], "%d", &nbIteration);

    CImg<> imgF(cNomImgF);
    CImgDisplay displayF(imgF, cNomImgF);
    
    CImg<> imgG(cNomImgG);
    CImgDisplay displayG(imgG, cNomImgG);
    
    CImgList<> list(imgF, imgG);

    int cpt = imgG.depth() / 2;
    int cptIteration = nbIteration;

    CImg<> def(imgF.width(), imgF.height(), imgF.depth());
    
    while (!displayF.is_closed()) {
        if(displayF.is_keyESC())
            break;
            
        if(displayF.wheel()){
            cpt += displayF.wheel();
            displayF.set_wheel();
        }
        CImgList<> list = imgF.get_gradient("xyz");



        while(nbIteration > 0){        
            


            for(int i = 0; i < imgG.width(); ++i){
                for(int j = 0; j < imgG.height(); ++j){
                    for(int k = 0; k < imgG.depth(); ++k){
                        float x = list[0](i, j);
                        float y = list[1](i, j);
                        float z = list[2](i, j);

                        //deltaF = intensité
                        float vx, vy, vz;

                        //float deltaF = g(i, j, k) - f(i, j, k);

                        //  vx = ()

                        if(imgF(i, j, k) > imgG(i, j, k)){
                            //DEPLACEMENT
                            imgG(i, j, k) = imgF(i + x, j + y, k + z);
                        }
                    }
                }
            }
            --nbIteration;
        }
        nbIteration = cptIteration;
        
        displayF.display(imgF.get_slice(cpt));
        displayG.display(imgG.get_slice(cpt));

        displayF.wait();
    }
    return 0;
}