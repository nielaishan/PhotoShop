#ifndef CHANNELWIDGET_H
#define CHANNELWIDGET_H

#include <QWidget>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include "commandmanager.h"

class ChannelWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ChannelWidget(QWidget *parent = 0);
    ~ChannelWidget();

protected:
    void drawWidget();
    void connectFunc();
    void newParts();

protected slots:
    void setR();
    void setG();
    void setB();

private:
    QHBoxLayout *layout0;
    QVBoxLayout *VLayout;
    //三通道 https://blog.csdn.net/matrix_space/article/details/39896567
    QPushButton *RPtn, *GPtn, *BPtn;
};

#endif // CHANNELWIDGET_H
