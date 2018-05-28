#include "colorwidget.h"
#include <QVBoxLayout>

ColorWidget::ColorWidget(QWidget *parent) :
    QWidget(parent)
{
    newParts();
    drawWidget();
    connectFunc();
}

ColorWidget::~ColorWidget()
{

}

void ColorWidget::newParts()
{
    autumnPtn = new QToolButton(this);
    autumnPtn->setText("autumn");
    autumnPtn->setIcon(QIcon(":/image/autumn.png"));
    autumnPtn->setIconSize(QSize(60, 48));
    autumnPtn->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);

    bonePtn = new QToolButton(this);
    bonePtn->setText("bone");
    bonePtn->setIcon(QIcon(":/image/bone.png"));
    bonePtn->setIconSize(QSize(60, 48));
    bonePtn->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);

    jetPtn = new QToolButton(this);
    jetPtn->setText("jet");
    jetPtn->setIcon(QIcon(":/image/jet.png"));
    jetPtn->setIconSize(QSize(60, 48));
    jetPtn->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);

    winterPtn = new QToolButton(this);
    winterPtn->setText("winter");
    winterPtn->setIcon(QIcon(":/image/winter.png"));
    winterPtn->setIconSize(QSize(60, 48));
    winterPtn->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);

    oceanPtn = new QToolButton(this);
    oceanPtn->setText("ocean");
    oceanPtn->setIcon(QIcon(":/image/ocean.png"));
    oceanPtn->setIconSize(QSize(60, 48));
    oceanPtn->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);

    summerPtn = new QToolButton(this);
    summerPtn->setText("summer");
    summerPtn->setIcon(QIcon(":/image/summer.png"));
    summerPtn->setIconSize(QSize(60, 48));
    summerPtn->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);

    springPtn = new QToolButton(this);
    springPtn->setText("spring");
    springPtn->setIcon(QIcon(":/image/spring.png"));
    springPtn->setIconSize(QSize(60, 48));
    springPtn->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);

    coolPtn = new QToolButton(this);
    coolPtn->setText("cool");
    coolPtn->setIcon(QIcon(":/image/cool.png"));
    coolPtn->setIconSize(QSize(60, 48));
    coolPtn->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);

    hsvPtn = new QToolButton(this);
    hsvPtn->setText("hsv");
    hsvPtn->setIcon(QIcon(":/image/hsv.png"));
    hsvPtn->setIconSize(QSize(60, 48));
    hsvPtn->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);

    pinkPtn = new QToolButton(this);
    pinkPtn->setText("pink");
    pinkPtn->setIcon(QIcon(":/image/pink.png"));
    pinkPtn->setIconSize(QSize(60, 48));
    pinkPtn->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);

    hotPtn = new QToolButton(this);
    hotPtn->setText("hot");
    hotPtn->setIcon(QIcon(":/image/hot.png"));
    hotPtn->setIconSize(QSize(60, 48));
    hotPtn->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);

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
    VLayout->addSpacing(300);
    this->setLayout(VLayout);
}

void ColorWidget::connectFunc() {
    connect(autumnPtn, SIGNAL(clicked(bool)), this, SLOT(setAutumn()));
    connect(bonePtn, SIGNAL(clicked(bool)), this, SLOT(setBone()));
    connect(jetPtn, SIGNAL(clicked(bool)), this, SLOT(setJet()));
    connect(winterPtn, SIGNAL(clicked(bool)), this, SLOT(setWinter()));
    connect(oceanPtn, SIGNAL(clicked(bool)), this, SLOT(setOcean()));
    connect(summerPtn, SIGNAL(clicked(bool)), this, SLOT(setSummer()));
    connect(springPtn, SIGNAL(clicked(bool)), this, SLOT(setSpring()));
    connect(coolPtn, SIGNAL(clicked(bool)), this, SLOT(setCool()));
    connect(hsvPtn, SIGNAL(clicked(bool)), this, SLOT(setHsv()));
    connect(pinkPtn, SIGNAL(clicked(bool)), this, SLOT(setPink()));
    connect(hotPtn, SIGNAL(clicked(bool)), this, SLOT(setHot()));
}
void ColorWidget::setAutumn() {
    CommandManager::excute("autumn");
}

void ColorWidget::setBone() {
    CommandManager::excute("bone");
}

void ColorWidget::setJet() {
    CommandManager::excute("jet");
}

void ColorWidget::setWinter() {
    CommandManager::excute("winter");
}

void ColorWidget::setOcean() {
    CommandManager::excute("ocean");
}

void ColorWidget::setSummer() {
    CommandManager::excute("summer");
}

void ColorWidget::setSpring() {
    CommandManager::excute("spring");
}

void ColorWidget::setCool() {
    CommandManager::excute("cool");
}

void ColorWidget::setHsv() {
    CommandManager::excute("hsv");
}

void ColorWidget::setPink() {
    CommandManager::excute("pink");
}

void ColorWidget::setHot() {
    CommandManager::excute("hot");
}
