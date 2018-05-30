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
    hLayout = new QHBoxLayout;
    QFont font;
    font.setFamily("宋体");
    font.setLetterSpacing(QFont::AbsoluteSpacing,5);
    font.setPointSize(13);
    listWidget->setFont(font);
    listWidget->insertItem(0, tr("滤镜效果"));
    listWidget->insertItem(1, tr("颜色变换"));
    listWidget->insertItem(2, tr("RGB通道"));
    listWidget->setFlow(QListView::LeftToRight);
    listWidget->setFixedHeight(25);
    stackWidget->addWidget(filterEffect);
    stackWidget->addWidget(colorWidget);
    stackWidget->addWidget(channelWidget);
    mainLayout->addSpacing(10);
//    hLayout->addSpacing(10);
    hLayout->addWidget(listWidget);
    mainLayout->addLayout(hLayout);
    mainLayout->addWidget(stackWidget);
    connect(listWidget, SIGNAL(currentRowChanged(int)), stackWidget, SLOT(setCurrentIndex(int)));
}
