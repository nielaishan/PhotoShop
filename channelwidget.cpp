#include "channelwidget.h"

ChannelWidget::ChannelWidget(QWidget *parent) :
    QWidget(parent)
{
    newParts();
    drawWidget();
    connectFunc();
}

ChannelWidget::~ChannelWidget(){}

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

void ChannelWidget::connectFunc() {
    connect(RPtn, SIGNAL(clicked(bool)), this, SLOT(setR()));
    connect(GPtn, SIGNAL(clicked(bool)), this, SLOT(setG()));
    connect(BPtn, SIGNAL(clicked(bool)), this, SLOT(setB()));
}

void ChannelWidget::setR() {
    CommandManager::excute("R");
}

void ChannelWidget::setG() {
    CommandManager::excute("G");
}

void ChannelWidget::setB() {
    CommandManager::excute("B");
}
