#ifndef IMGSINGLETON_H
#define IMGSINGLETON_H

#include <QImage>
#include <iostream>
using namespace std;

class ImgSingleton
{
protected:
    ImgSingleton();
public:
    static QImage* createImgSingleton();
private:
    static QImage *img;
};

#endif // IMGSINGLETON_H
