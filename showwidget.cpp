#include "showwidget.h"
#include <QDebug>

QImage *ShowWidget::img = 0;
QLabel *ShowWidget::imgLabel = 0;
QLabel *ShowWidget::srcLabel = 0;
QWidget *ShowWidget::widget = 0;
ShowWidget::ShowWidget(QWidget *parent) : QWidget(parent)
{
    //设置显示图片的widget
    QPalette palette(this->palette());
    palette.setColor(QPalette::Background, QColor(59, 59, 59));
    this->setPalette(palette);
    widget = new QWidget(this);
    widget->resize(900, 800);
    widget->setStyleSheet("border:none;background-color:rgb(33,33,33);");
    QHBoxLayout *widgetLayout = new QHBoxLayout;
    scrollArea = new QScrollArea(this);
    imgLabel = new QLabel(widget);
    imgLabel->resize(900, 800);;
    imgLabel->setStyleSheet("background-color:rgb(33,33,33);");
    widgetLayout->addWidget(imgLabel);
    srcLabel = new QLabel(widget);
    srcLabel->setStyleSheet("background-color:rgb(33,33,33);");
    srcLabel->resize(900, 800);
    srcLabel->hide();
    widgetLayout->addWidget(srcLabel);
    widget->setLayout(widgetLayout);
    scrollArea->resize(900, 800);
    scrollArea->setWidget(widget);
}

bool ShowWidget::addImg(QString filename) {
    //opencv打开图片处理
    if (filename.size() == 0)
        return false;
    QImage *image = new QImage;
    image->load(filename);
    Mat cvImage = imread(filename.toLatin1().data(), 1);
    CommandManager::excute("preprocessing", cvImage);
    if(!cvImage.empty())
        return true;
    return false;
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

void ShowWidget::showSrcImage() {
    QPixmap srcPixmap = QPixmap::fromImage(*img);
    srcPixmap = srcPixmap.scaled(srcLabel->width(), srcLabel->height(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
    //图片居中
    srcLabel->setAlignment(Qt::AlignCenter);
    srcLabel->setPixmap(srcPixmap);
}

void ShowWidget::setWidth(int pos)
{
    scrollArea->resize(1200-pos, 800);
    widget->resize(1200-pos-5, 800);
}

void ShowWidget::compareImg(bool isCompare) {
    if (isCompare) {
        srcLabel->show();
        imgLabel->hide();
    }
    else {
        srcLabel->hide();
        imgLabel->show();
    }
}

