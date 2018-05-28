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
    sketchPtn = new QToolButton(this);
    sketchPtn->setText("素描");
    sketchPtn->setIcon(QIcon(":/image/sketch.png"));
    sketchPtn->setIconSize(QSize(60, 48));
    sketchPtn->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);

    carvePtn = new QToolButton(this);
    carvePtn->setText("雕刻");
    carvePtn->setIcon(QIcon(":/image/carve.png"));
    carvePtn->setIconSize(QSize(60, 48));
    carvePtn->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);

    reliefPtn = new QToolButton(this);
    reliefPtn->setText("浮雕");
    reliefPtn->setIcon(QIcon(":/image/relief.png"));
    reliefPtn->setIconSize(QSize(60, 48));
    reliefPtn->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);

    expandPtn = new QToolButton(this);
    expandPtn->setText("扩张");
    expandPtn->setIcon(QIcon(":/image/expand.png"));
    expandPtn->setIconSize(QSize(60, 48));
    expandPtn->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);

    extrusionPtn = new QToolButton(this);
    extrusionPtn->setText("挤压");
    extrusionPtn->setIcon(QIcon(":/image/extrusion.png"));
    extrusionPtn->setIconSize(QSize(60, 48));
    extrusionPtn->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);

    nostalgiaPtn = new QToolButton(this);
    nostalgiaPtn->setText("怀旧");
    nostalgiaPtn->setIcon(QIcon(":/image/nostalgia.png"));
    nostalgiaPtn->setIconSize(QSize(60, 48));
    nostalgiaPtn->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);

    comicPtn = new QToolButton(this);
    comicPtn->setText("连环画");
    comicPtn->setIcon(QIcon(":/image/comic.png"));
    comicPtn->setIconSize(QSize(60, 48));
    comicPtn->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);

    castPtn = new QToolButton(this);
    castPtn->setText("熔铸");
    castPtn->setIcon(QIcon(":/image/cast.png"));
    castPtn->setIconSize(QSize(60, 48));
    castPtn->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);

    frozenPtn = new QToolButton(this);
    frozenPtn->setText("冰冻");
    frozenPtn->setIcon(QIcon(":/image/frozen.png"));
    frozenPtn->setIconSize(QSize(60, 48));
    frozenPtn->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);

    woolGlassPtn = new QToolButton(this);
    woolGlassPtn->setText("毛玻璃");
    woolGlassPtn->setIcon(QIcon(":/image/woolGlass.png"));
    woolGlassPtn->setIconSize(QSize(60, 48));
    woolGlassPtn->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);

    vuguePtn = new QToolButton(this);
    vuguePtn->setText("模糊");
    vuguePtn->setIcon(QIcon(":/image/vugue.png"));
    vuguePtn->setIconSize(QSize(60, 48));
    vuguePtn->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);

    bulgePtn = new QToolButton(this);
    bulgePtn->setText("凸出");
    bulgePtn->setIcon(QIcon(":/image/bulge.png"));
    bulgePtn->setIconSize(QSize(60, 48));
    bulgePtn->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);

    sunkenPtn = new QToolButton(this);
    sunkenPtn->setText("凹陷");
    sunkenPtn->setIcon(QIcon(":/image/sunken.png"));
    sunkenPtn->setIconSize(QSize(60, 48));
    sunkenPtn->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);

    mosaicPtn = new QToolButton(this);
    mosaicPtn->setText("马赛克");
    mosaicPtn->setIcon(QIcon(":/image/mosaic.png"));
    mosaicPtn->setIconSize(QSize(60, 48));
    mosaicPtn->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);

    lightPtn = new QToolButton(this);
    lightPtn->setText("强光");
    lightPtn->setIcon(QIcon(":/image/light.png"));
    lightPtn->setIconSize(QSize(60, 48));
    lightPtn->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);

    fogPtn = new QToolButton(this);
    fogPtn->setText("去雾");
    fogPtn->setIcon(QIcon(":/image/fog.png"));
    fogPtn->setIconSize(QSize(60, 48));
    fogPtn->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);

    grayPtn = new QToolButton(this);
    grayPtn->setText("灰度");
    grayPtn->setIcon(QIcon(":/image/gray.png"));
    grayPtn->setIconSize(QSize(60, 48));
    grayPtn->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);

    BWPtn = new QToolButton(this);
    BWPtn->setText("黑白");
    BWPtn->setIcon(QIcon(":/image/BW.png"));
    BWPtn->setIconSize(QSize(60, 48));
    BWPtn->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);

    negativePtn = new QToolButton(this);
    negativePtn->setText("底片");
    negativePtn->setIcon(QIcon(":/image/negative.png"));
    negativePtn->setIconSize(QSize(60, 48));
    negativePtn->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);

    woodPtn = new QToolButton(this);
    woodPtn->setText("木雕");
    woodPtn->setIcon(QIcon(":/image/wood.png"));
    woodPtn->setIconSize(QSize(60, 48));
    woodPtn->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);

    pencilPtn = new QToolButton(this);
    pencilPtn->setText("铅笔画");
    pencilPtn->setIcon(QIcon(":/image/pencil.png"));
    pencilPtn->setIconSize(QSize(60, 48));
    pencilPtn->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);

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
