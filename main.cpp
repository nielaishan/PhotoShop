#include "photoshop.h"
#include <QApplication>
#include <QStack>
#include <opencv/cv.h>
#include <opencv/highgui.h>
using namespace std;
using namespace cv;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    PhotoShop w;
    w.show();
    QFile styleFile(":/qss/qss.qss");
    styleFile.open(QIODevice::ReadOnly);
    QString setStyleSheet(styleFile.readAll());;
    a.setStyleSheet(setStyleSheet);
    return a.exec();
}
