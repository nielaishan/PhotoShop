#ifndef SHOWWIDGET_H
#define SHOWWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QImage>
#include <QString>
#include <QMessageBox>
#include <QScrollArea>
#include "imgsingleton.h"

class ShowWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ShowWidget(QWidget *parent = nullptr);
    void addImg(QString filename);
    void setWidth(int pos);
private:
    QImage *img;
    QLabel *imgLabel;
    QScrollArea *scrollArea;
signals:

public slots:
};

#endif // SHOWWIDGET_H
