#ifndef FILTEREFFECT_H
#define FILTEREFFECT_H

#include <QWidget>
#include <QPushButton>
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
private:
    QHBoxLayout *layout0, *layout1, *layout2, *layout3, *layout4, *layout5, *layout6, *layout7;
    QVBoxLayout *VLayout;
    //素描 https://blog.csdn.net/yangtrees/article/details/9115321
    QPushButton *sketchPtn;
    //雕刻 https://blog.csdn.net/yangtrees/article/details/9090607
    QPushButton *carvePtn;
    //浮雕 https://blog.csdn.net/yangtrees/article/details/9095731
    QPushButton *reliefPtn;
    //扩张
    QPushButton *expandPtn;
    //挤压
    QPushButton *extrusionPtn;
    //怀旧 https://blog.csdn.net/yangtrees/article/details/9116337
    QPushButton *nostalgiaPtn;
    //连环画
    QPushButton *comicPtn;
    //熔铸
    QPushButton *castPtn;
    //冰冻
    QPushButton *frozenPtn;
    //毛玻璃 https://blog.csdn.net/yangtrees/article/details/9115799
    QPushButton *woolGlassPtn;
    //模糊
    QPushButton *vuguePtn;

    QPushButton *bulgePtn;
    //凸出 https://blog.csdn.net/matrix_space/article/details/42394249
    QPushButton *sunkenPtn;
    //凹陷 https://blog.csdn.net/matrix_space/article/details/42394549

    //马赛克 ：https://blog.csdn.net/matrix_space/article/details/40622159
    QPushButton *mosaicPtn;
    //强光  https://blog.csdn.net/yangtrees/article/details/9206967
    QPushButton *lightPtn;
    //去雾 https://blog.csdn.net/matrix_space/article/details/40652883
    QPushButton *fogPtn;
    //灰度 https://blog.csdn.net/matrix_space/article/details/38122673
    QPushButton *grayPtn;
    //渐变 https://blog.csdn.net/matrix_space/article/details/40477439
    QPushButton *gradietPtn;
    //黑白 底片http://www.cnblogs.com/biglucky/p/4136946.html
    //木雕 铅笔画 https://blog.csdn.net/superdont/article/details/47111501
    QPushButton *BWPtn, *negativePtn, *WoodPtn, *pencilPtn;
};

#endif // FILTEREFFECT_H
