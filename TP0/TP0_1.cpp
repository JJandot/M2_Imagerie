#include <iostream>
#include "../CImg.h"

using namespace cimg_library;

int main(int argc, char *argv[]){
    CImg<> img;   
    float voxelSize[3];

    img.load_analyze("DATA/knix.hdr", voxelSize);
    
    std::cout << "--------------knix.hdr--------------" << std::endl; 
    
    int hauteur, largeur, profondeur;
    float minVal, maxVal;
    
    hauteur = img.height();
    largeur = img.width();
    profondeur = img.depth();
    
    std::cout << "Hauteur : " << hauteur << ", largeur : " << largeur << ", profondeur : " << profondeur << std::endl;
    std::cout << "Taille du voxel : " << voxelSize[0] << ", " << voxelSize[1] << ", " << voxelSize[2] << std::endl;
    
    float tailleHauteur = hauteur * voxelSize[0];
    float tailleLargeur = largeur * voxelSize[1];
    float tailleProfondeur = profondeur * voxelSize[2];
    
    std::cout << "La taille de l'image est de : " << tailleHauteur << ", " << tailleLargeur << ", " << tailleProfondeur << std::endl;
    
    minVal = img.min();
    maxVal = img.max();
    
    std::cout << "Valeur minimale : " << minVal << ", valeur maximale : " << maxVal << std::endl;
    
    float voxelValue = img(256, 256, 12);
    
    std::cout << "La valeur du voxel (256, 256, 12) est de : " << voxelValue << std::endl;
    
    std::cout << "------------------------------------" << std::endl;
    
    return 0;
}

