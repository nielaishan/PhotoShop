#ifndef DEALPICWIDGET_H
#define DEALPICWIDGET_H

#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QListWidget>
#include <QStackedWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFont>
#include "filtereffect.h"
#include "colorwidget.h"
#include "channelwidget.h"

class DealPicWidget : public QWidget
{
    Q_OBJECT
public:
    explicit DealPicWidget(QWidget *parent = nullptr);

private:
    QStackedWidget *stackWidget;
    QListWidget *listWidget;
    QVBoxLayout *mainLayout;
    FilterEffect *filterEffect;
    ColorWidget *colorWidget;
    ChannelWidget *channelWidget;
    QLabel *filterEffectLabel;
    QHBoxLayout *hLayout;
};

#endif // DEALPICWIDGET_H
