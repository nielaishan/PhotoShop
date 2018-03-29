#include "channelwidget.h"

ChannelWidget::ChannelWidget(QWidget *parent) :
    QWidget(parent)
{
    newParts();
    drawWidget();
}

ChannelWidget::~ChannelWidget()
{
}

void ChannelWidget::newParts()
{
    RPtn = new QPushButton(this);
    RPtn->setText("R通道");
    GPtn = new QPushButton(this);
    GPtn->setText("G通道");
    BPtn = new QPushButton(this);
    BPtn->setText("B通道");
}

void ChannelWidget::drawWidget() {
    VLayout = new QVBoxLayout(this);

    layout0 = new QHBoxLayout;

    layout0->addWidget(RPtn);
    layout0->addWidget(GPtn);
    layout0->addWidget(BPtn);

    VLayout->addLayout(layout0);
    VLayout->addSpacing(600);
    this->setLayout(VLayout);
}
