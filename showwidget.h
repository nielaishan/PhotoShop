#ifndef SHOWWIDGET_H
#define SHOWWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QImage>
#include <QString>
#include <QMessageBox>
#include <QScrollArea>
#include <opencv/cv.h>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <QStack>
#include "commandmanager.h"

using namespace cv;
class ShowWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ShowWidget(QWidget *parent = nullptr);
    void addImg(QString filename);
    void setWidth(int pos);
    static void showImage(QImage Image);

protected:

private:
    static QImage *img;
    static QLabel *imgLabel;
    QScrollArea *scrollArea;

signals:

public slots:
};

#endif // SHOWWIDGET_H
