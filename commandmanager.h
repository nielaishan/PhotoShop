#ifndef COMMANDMANAGER_H
#define COMMANDMANAGER_H

#include <QStack>
#include <opencv/cv.h>
#include <QImage>
#include <QFileDialog>
#include <opencv2/opencv.hpp>
#include <opencv/highgui.h>
#include <opencv/cxcore.h>
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/imgproc/types_c.h"
#include "showwidget.h"
#include <QDebug>
#include <iostream>
#include <math.h>
#include <opencv2/core/types.hpp>
#include "noticedialog.h"
#define pi 3.1415926
using namespace std;
using namespace cv;
class CommandManager
{
public:
    CommandManager();
    static void excute(QString styleNamem, Mat img=Mat(1000, 1000, CV_8UC3));
protected:
    static void frozen();
    static void woolGlass();
    static void vugue();
    static void bulge();
    static void sunken();
    static void mosaic();
    static void light();
    static void fog();
    static void gray();
    static void BW();
    static void negative();
    static void wood();
    static void pencil();

    static void expand();
    static void sketch();
    static void carve();
    static void relief();
    static void extrusion();
    static void preprocessing();
    static void nostalgia();
    static void comic();
    static void cast();
    static void InitMat(Mat &kernel);

    static void colorTrans(int c);

    static void selectChannel(QString channel);

    static void saveImage(QString filename);

private:
    static bool isInitImg;
    static void showImage(Mat img, bool styleColor, QImage::Format formatType);
    static Mat Image;
    static Mat dealImg;
    static QStack<Mat> *undoStack;
    static QStack<Mat> *redoStack;
    static QString preOpStr;
    static Mat minRGB(Mat src);
    static Mat minFilter(Mat src, int ksize);
    static Mat grayStretch(const Mat src, double lowcut, double highcut);
    static Mat guildFilter(Mat g, Mat p, int ksize);
};

#endif // COMMANDMANAGER_H
