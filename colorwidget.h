#ifndef COLORWIDGET_H
#define COLORWIDGET_H

#include <QWidget>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <math.h>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "commandmanager.h"

class ColorWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ColorWidget(QWidget *parent = 0);
    ~ColorWidget();
protected:
    void drawWidget();
    void connectFunc();
    void newParts();

protected slots:
    void setAutumn();
    void setBone();
    void setJet();
    void setWinter();
    void setOcean();
    void setSummer();
    void setSpring();
    void setCool();
    void setHsv();
    void setPink();
    void setHot();

private:
    //颜色变换 https://blog.csdn.net/yangtrees/article/details/9096435
    QPushButton *autumnPtn, *bonePtn, *jetPtn, *winterPtn, *oceanPtn, *summerPtn, *springPtn, *coolPtn, *hsvPtn, *pinkPtn, *hotPtn;

    QHBoxLayout *layout0, *layout1, *layout2, *layout3;
    QVBoxLayout *VLayout;
};

#endif // COLORWIDGET_H
