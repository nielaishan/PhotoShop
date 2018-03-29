#include "dealpicwidget.h"
#include <QStackedWidget>

DealPicWidget::DealPicWidget(QWidget *parent) : QWidget(parent)
{
    stackWidget = new QStackedWidget(this);
    listWidget = new QListWidget(this);
    filterEffect  = new FilterEffect;
    colorWidget = new ColorWidget;
    channelWidget = new ChannelWidget;
    mainLayout = new QVBoxLayout(this);

    listWidget->insertItem(0, tr("滤镜效果"));


    listWidget->insertItem(1, tr("颜色变换"));
    listWidget->insertItem(2, tr("RGB通道"));
    listWidget->setFlow(QListView::LeftToRight);
    listWidget->setFixedHeight(25);
    listWidget->setStyleSheet("border:none; background-color:rgb(59,59,59); color:#d9d9d9");

    stackWidget->addWidget(filterEffect);
    stackWidget->addWidget(colorWidget);
    stackWidget->addWidget(channelWidget);
    mainLayout->addSpacing(30);
    mainLayout->addWidget(listWidget);
    mainLayout->addWidget(stackWidget);
    connect(listWidget, SIGNAL(currentRowChanged(int)), stackWidget, SLOT(setCurrentIndex(int)));
}



