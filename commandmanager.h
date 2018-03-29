#ifndef COMMANDMANAGER_H
#define COMMANDMANAGER_H

#include <QStack>
#include <opencv/cv.h>
#include <QImage>
#include <opencv2/opencv.hpp>
#include <opencv/highgui.h>
#include <opencv2/imgproc/imgproc.hpp>
#include "showwidget.h"
#include <QDebug>
#include <iostream>
#include <math.h>

using namespace std;
using namespace cv;
class CommandManager
{
public:
    CommandManager();
    static void excute(QString styleNamem, Mat img=Mat(1000, 1000, CV_8UC1));

protected:
    static void expand();
    static void sketch();
    static void carve();
    static void relief();
    static void extrusion();
    static void preprocessing();
    static void InitMat(Mat &kernel);

private:
    static Mat Image;
    static Mat dealImg;
    static QString preOpStr;
    static QStack<Mat> *undoStack;
    static QStack<Mat> *redoStack;
};

#endif // COMMANDMANAGER_H
