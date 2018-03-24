#include "showwidget.h"

ShowWidget::ShowWidget(QWidget *parent) : QWidget(parent)
{
    //设置显示图片的widget
    QPalette palette(this->palette());
    palette.setColor(QPalette::Background, QColor(59, 59, 59));
    this->setPalette(palette);
    scrollArea = new QScrollArea(this);
    imgLabel = new QLabel(this);
    imgLabel->resize(900, 800);
    imgLabel->setStyleSheet("background-color:rgb(59,59,59);");
    scrollArea->resize(900, 800);
    scrollArea->setWidget(imgLabel);
}

void ShowWidget::addImg(QString filename) {
    img = ImgSingleton::createImgSingleton();
    if (!(img->load(filename))) {
        QMessageBox::information(this, tr("failed!"), tr("failed"));
        delete img;
        return ;
    }
    QPixmap pixmap = QPixmap::fromImage(*img);
    pixmap = pixmap.scaled(imgLabel->width(), imgLabel->height(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
    imgLabel->setAlignment(Qt::AlignCenter);
    imgLabel->setPixmap(pixmap);
}

void ShowWidget::setWidth(int pos)
{
    scrollArea->resize(1200-pos, 800);
    imgLabel->resize(1200-pos-5, 800);
}
