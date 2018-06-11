#ifndef SHOWWIDGET_H
#define SHOWWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QImage>
#include <QString>
#include <QMessageBox>
#include <QScrollArea>
#include <QHBoxLayout>
#include <QWidget>
#include <opencv/cv.h>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <QStack>
#include "commandmanager.h"
#include "showwidget.h"
#include <QDebug>

using namespace cv;
class ShowWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ShowWidget(QWidget *parent = nullptr);
    bool addImg(QString filename);
    void setWidth(int pos);
    static void showImage(QImage Image);
    static void showSrcImage();
    static void compareImg(bool isCompare);
    static QImage *img;
private:

    static QLabel *imgLabel;
    static QLabel *srcLabel;
    QScrollArea *scrollArea;
    static QWidget *widget;
};

#endif // SHOWWIDGET_H
