#ifndef DEALPICWIDGET_H
#define DEALPICWIDGET_H

#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QListWidget>
#include <QStackedWidget>
#include <QVBoxLayout>
#include "filtereffect.h"
#include "colorwidget.h"
#include "channelwidget.h"

class DealPicWidget : public QWidget
{
    Q_OBJECT
public:
    explicit DealPicWidget(QWidget *parent = nullptr);
    void newParts();
signals:

public slots:

protected:
    void newPtn(QPushButton *ptn, QString s);

private:

    QStackedWidget *stackWidget;
    QListWidget *listWidget;
    QVBoxLayout *mainLayout;
    FilterEffect *filterEffect;
    ColorWidget *colorWidget;
    ChannelWidget *channelWidget;
    QLabel *filterEffectLabel;

};

#endif // DEALPICWIDGET_H
