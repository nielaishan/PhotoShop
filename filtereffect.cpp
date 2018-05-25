#include "filtereffect.h"
#include <QDebug>

FilterEffect::FilterEffect(QWidget *parent) :
    QWidget(parent)
{
    newParts();
    drawWidget();
    connectFunc();
}

void FilterEffect::drawWidget() {
    VLayout = new QVBoxLayout(this);

    layout0 = new QHBoxLayout;
    layout1 = new QHBoxLayout;
    layout2 = new QHBoxLayout;
    layout3 = new QHBoxLayout;
    layout4 = new QHBoxLayout;
    layout5 = new QHBoxLayout;
    layout6 = new QHBoxLayout;

    layout0->addWidget(sketchPtn);
    layout0->addWidget(carvePtn);
    layout0->addWidget(reliefPtn);

    VLayout->addLayout(layout0);

    layout1->addWidget(expandPtn);
    layout1->addWidget(extrusionPtn);
    layout1->addWidget(nostalgiaPtn);

    VLayout->addLayout(layout1);

    layout2->addWidget(comicPtn);
    layout2->addWidget(castPtn);
    layout2->addWidget(frozenPtn);

    VLayout->addLayout(layout2);

    layout3->addWidget(woolGlassPtn);
    layout3->addWidget(vuguePtn);
    layout3->addWidget(bulgePtn);

    VLayout->addLayout(layout3);

    layout4->addWidget(sunkenPtn);
    layout4->addWidget(mosaicPtn);
    layout4->addWidget(lightPtn);

    VLayout->addLayout(layout4);

    layout5->addWidget(fogPtn);
    layout5->addWidget(grayPtn);
    layout5->addWidget(pencilPtn);

    VLayout->addLayout(layout5);

    layout6->addWidget(BWPtn);
    layout6->addWidget(negativePtn);
    layout6->addWidget(woodPtn);

    VLayout->addLayout(layout6);

    this->setLayout(VLayout);
}

FilterEffect::~FilterEffect()
{
}

void FilterEffect::newParts()
{
    sketchPtn = new QPushButton(this);
    sketchPtn->setText("素描");
    carvePtn = new QPushButton(this);
    carvePtn->setText("雕刻");
    reliefPtn = new QPushButton(this);
    reliefPtn->setText("浮雕");
    expandPtn = new QPushButton(this);
    expandPtn->setText("扩张");
    extrusionPtn = new QPushButton(this);
    extrusionPtn->setText("挤压");
    nostalgiaPtn = new QPushButton(this);
    nostalgiaPtn->setText("怀旧");
    comicPtn = new QPushButton(this);
    comicPtn->setText("连环画");
    castPtn = new QPushButton(this);
    castPtn->setText("熔铸");
    frozenPtn = new QPushButton(this);
    frozenPtn->setText("冰冻");
    woolGlassPtn = new QPushButton(this);
    woolGlassPtn->setText("毛玻璃");
    vuguePtn = new QPushButton(this);
    vuguePtn->setText("模糊");
    bulgePtn = new QPushButton(this);
    bulgePtn->setText("凸出");
    sunkenPtn = new QPushButton(this);
    sunkenPtn->setText("凹陷");
    mosaicPtn = new QPushButton(this);
    mosaicPtn->setText("马赛克");
    lightPtn = new QPushButton(this);
    lightPtn->setText("强光");
    fogPtn = new QPushButton(this);
    fogPtn->setText("去雾");
    grayPtn = new QPushButton(this);
    grayPtn->setText("灰度");
    BWPtn = new QPushButton(this);
    BWPtn->setText("黑白");
    negativePtn = new QPushButton(this);
    negativePtn->setText("底片");
    woodPtn = new QPushButton(this);
    woodPtn->setText("木雕");
    pencilPtn = new QPushButton(this);
    pencilPtn->setText("铅笔画");
}

void FilterEffect::connectFunc() {
    connect(sketchPtn, SIGNAL(clicked(bool)), this, SLOT(setSketch()));
    connect(carvePtn, SIGNAL(clicked(bool)), this, SLOT(setCarve()));
    connect(reliefPtn, SIGNAL(clicked(bool)), this, SLOT(setRelief()));
    connect(expandPtn, SIGNAL(clicked(bool)), this, SLOT(setExpand()));
    connect(extrusionPtn, SIGNAL(clicked(bool)), this, SLOT(setExtrusion()));
    connect(nostalgiaPtn, SIGNAL(clicked(bool)), this, SLOT(setNostalgia()));
    connect(comicPtn, SIGNAL(clicked(bool)), this, SLOT(setComic()));
    connect(castPtn, SIGNAL(clicked(bool)), this, SLOT(setCast()));
    connect(frozenPtn, SIGNAL(clicked(bool)), this, SLOT(setFrozen()));
    connect(woolGlassPtn, SIGNAL(clicked(bool)), this, SLOT(setWoolGlass()));
    connect(vuguePtn, SIGNAL(clicked(bool)), this, SLOT(setVugue()));
    connect(bulgePtn, SIGNAL(clicked(bool)), this, SLOT(setBulge()));
    connect(sunkenPtn, SIGNAL(clicked(bool)), this, SLOT(setSunken()));
    connect(mosaicPtn, SIGNAL(clicked(bool)), this, SLOT(setMosaic()));
    connect(lightPtn, SIGNAL(clicked(bool)), this, SLOT(setLight()));
    connect(fogPtn, SIGNAL(clicked(bool)), this, SLOT(setFog()));
    connect(grayPtn, SIGNAL(clicked(bool)), this, SLOT(setGray()));
    connect(BWPtn, SIGNAL(clicked(bool)), this, SLOT(setBW()));
    connect(negativePtn, SIGNAL(clicked(bool)), this, SLOT(setNegative()));
    connect(woodPtn, SIGNAL(clicked(bool)), this, SLOT(setWood()));
    connect(pencilPtn, SIGNAL(clicked(bool)), this, SLOT(setPencil()));
}

void FilterEffect::setPencil() {
    CommandManager::excute("pencil");
}
void FilterEffect::setWood() {
    CommandManager::excute("wood");
}
void FilterEffect::setNegative() {
    CommandManager::excute("negative");
}
void FilterEffect::setBW() {
    CommandManager::excute("BW");
}

void FilterEffect::setGray() {
    CommandManager::excute("gray");
}
void FilterEffect::setFog() {
    CommandManager::excute("fog");
}
void FilterEffect::setLight() {
    CommandManager::excute("light");
}
void FilterEffect::setMosaic() {
    CommandManager::excute("mosaic");
}
void FilterEffect::setSunken() {
    CommandManager::excute("sunken");
}
void FilterEffect::setBulge() {
    CommandManager::excute("bulge");
}
void FilterEffect::setVugue() {
    CommandManager::excute("vugue");
}
void FilterEffect::setWoolGlass() {
    CommandManager::excute("woolglass");
}
void FilterEffect::setFrozen() {
    CommandManager::excute("frozen");
}
void FilterEffect::setSketch() {
    CommandManager::excute("sketch");
}

void FilterEffect::setCarve() {
    CommandManager::excute("carve");
}

void FilterEffect::setRelief() {
    CommandManager::excute("relief");
}

void FilterEffect::setExpand() {
    CommandManager::excute("expand");
}

void FilterEffect::setExtrusion() {
    CommandManager::excute("extrusion");
}

void FilterEffect::setNostalgia() {
    CommandManager::excute("nostalgia");
}

void FilterEffect::setComic() {
    CommandManager::excute("comic");
}

void FilterEffect::setCast() {
    CommandManager::excute("cast");
}
