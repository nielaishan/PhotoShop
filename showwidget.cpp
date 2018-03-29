#include "showwidget.h"
#include <QDebug>

QImage *ShowWidget::img = 0;
QLabel *ShowWidget::imgLabel = 0;

ShowWidget::ShowWidget(QWidget *parent) : QWidget(parent)
{
    //设置显示图片的widget
    QPalette palette(this->palette());
    palette.setColor(QPalette::Background, QColor(59, 59, 59));
    this->setPalette(palette);
    scrollArea = new QScrollArea(this);
    imgLabel = new QLabel(this);
    imgLabel->resize(900, 800);
    imgLabel->setStyleSheet("background-color:rgb(33,33,33);");
    scrollArea->resize(900, 800);
    scrollArea->setWidget(imgLabel);
}

void ShowWidget::addImg(QString filename) {
    //opencv打开图片处理
    if (filename.size() == 0)
        return ;
    Mat cvImage = imread(filename.toLatin1().data(), 1);
    CommandManager::excute("preprocessing", cvImage);
}

void ShowWidget::showImage(QImage Image) {
    img = &Image;
    QPixmap pixmap = QPixmap::fromImage(*img);
    //进行合理放置图片
    imgLabel->clear();
    pixmap = pixmap.scaled(imgLabel->width(), imgLabel->height(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
    //图片居中
    imgLabel->setAlignment(Qt::AlignCenter);
    imgLabel->setPixmap(pixmap);
}

void ShowWidget::setWidth(int pos)
{
    scrollArea->resize(1200-pos, 800);
    imgLabel->resize(1200-pos-5, 800);
}
