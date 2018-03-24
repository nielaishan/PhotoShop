#include "imgsingleton.h"
QImage *ImgSingleton::img = 0;

ImgSingleton::ImgSingleton()
{
}

QImage* ImgSingleton::createImgSingleton()
{
    if (img == 0) {
        img = new QImage;
    }
    return img;
}
