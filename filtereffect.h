#ifndef FILTEREFFECT_H
#define FILTEREFFECT_H

#include <QWidget>
#include <QPushButton>
#include <QToolButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <opencv/cv.h>
#include <QStack>
#include "commandmanager.h"

using namespace cv;
class FilterEffect : public QWidget
{
    Q_OBJECT

public:
    explicit FilterEffect(QWidget *parent = 0);
    ~FilterEffect();

protected:
    void newParts();
    void drawWidget();
    void connectFunc();

protected slots:
    void setSketch();
    void setCarve();
    void setRelief();
    void setExpand();
    void setExtrusion();
    void setNostalgia();
    void setComic();
    void setCast();
    void setFrozen();
    void setWoolGlass();
    void setVugue();
    void setBulge();
    void setSunken();
    void setMosaic();
    void setLight();
    void setFog();
    void setGray();
    void setBW();
    void setNegative();
    void setWood();
    void setPencil();

private:
    QHBoxLayout *layout0, *layout1, *layout2, *layout3, *layout4, *layout5, *layout6, *layout7;
    QVBoxLayout *VLayout;
    //素描 https://blog.csdn.net/yangtrees/article/details/9115321
    QToolButton *sketchPtn;
    //雕刻 https://blog.csdn.net/yangtrees/article/details/9090607
    QToolButton *carvePtn;
    //浮雕 https://blog.csdn.net/yangtrees/article/details/9095731
    QToolButton *reliefPtn;
    //扩张
    QToolButton *expandPtn;
    //挤压
    QToolButton *extrusionPtn;
    //怀旧 https://blog.csdn.net/yangtrees/article/details/9116337
    QToolButton *nostalgiaPtn;
    //连环画
    QToolButton *comicPtn;
    //熔铸
    QToolButton *castPtn;
    //冰冻
    QToolButton *frozenPtn;
    //毛玻璃 https://blog.csdn.net/yangtrees/article/details/9115799
    QToolButton *woolGlassPtn;
    //模糊
    QToolButton *vuguePtn;

    QToolButton *bulgePtn;
    //凸出 https://blog.csdn.net/matrix_space/article/details/42394249
    QToolButton *sunkenPtn;
    //凹陷 https://blog.csdn.net/matrix_space/article/details/42394549

    //马赛克 ：https://blog.csdn.net/matrix_space/article/details/40622159
    QToolButton *mosaicPtn;
    //强光  https://blog.csdn.net/yangtrees/article/details/9206967
    QToolButton *lightPtn;
    //去雾 https://blog.csdn.net/matrix_space/article/details/40652883
    QToolButton *fogPtn;
    //灰度 https://blog.csdn.net/matrix_space/article/details/38122673
    QToolButton *grayPtn;
    //黑白 底片http://www.cnblogs.com/biglucky/p/4136946.html
    //木雕 铅笔画 https://blog.csdn.net/superdont/article/details/47111501
    QToolButton *BWPtn, *negativePtn, *woodPtn, *pencilPtn;
};

#endif // FILTEREFFECT_H
