#include "colorwidget.h"
#include <QVBoxLayout>

ColorWidget::ColorWidget(QWidget *parent) :
    QWidget(parent)
{
    newParts();
    drawWidget();
}

ColorWidget::~ColorWidget()
{

}

void ColorWidget::newParts()
{
    autumnPtn = new QPushButton(this);
    autumnPtn->setText("autumn");
    bonePtn = new QPushButton(this);
    bonePtn->setText("bone");
    jetPtn = new QPushButton(this);
    jetPtn->setText("jet");
    winterPtn = new QPushButton(this);
    winterPtn->setText("winter");
    oceanPtn = new QPushButton(this);
    oceanPtn->setText("ocean");
    summerPtn = new QPushButton(this);
    summerPtn->setText("summer");
    springPtn = new QPushButton(this);
    springPtn->setText("spring");
    coolPtn = new QPushButton(this);
    coolPtn->setText("cool");
    hsvPtn = new QPushButton(this);
    hsvPtn->setText("hsv");
    pinkPtn = new QPushButton(this);
    pinkPtn->setText("pink");
    hotPtn = new QPushButton(this);
    hotPtn->setText("hot");
}

void ColorWidget::drawWidget() {
    VLayout = new QVBoxLayout(this);

    layout0 = new QHBoxLayout;
    layout1 = new QHBoxLayout;
    layout2 = new QHBoxLayout;
    layout3 = new QHBoxLayout;

    layout0->addWidget(autumnPtn);
    layout0->addWidget(bonePtn);
    layout0->addWidget(jetPtn);

    VLayout->addLayout(layout0);

    layout1->addWidget(winterPtn);
    layout1->addWidget(oceanPtn);
    layout1->addWidget(summerPtn);

    VLayout->addLayout(layout1);

    layout2->addWidget(springPtn);
    layout2->addWidget(coolPtn);
    layout2->addWidget(hsvPtn);

    VLayout->addLayout(layout2);

    layout3->addWidget(pinkPtn);
    layout3->addWidget(hotPtn);
    layout3->addSpacing(92);

    VLayout->addLayout(layout3);

    this->setLayout(VLayout);


}

