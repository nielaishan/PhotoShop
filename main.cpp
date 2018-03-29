#include "photoshop.h"
#include <QApplication>
#include <QStack>
#include <opencv/cv.h>
using namespace std;
using namespace cv;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    PhotoShop w;
    w.show();
    return a.exec();
}
