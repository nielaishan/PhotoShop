#ifndef PHOTOSHOP_H
#define PHOTOSHOP_H

#include <QMainWindow>
#include <QMenuBar>
#include <QMenu>
#include <QAction>
#include <QWidget>
#include <QPalette>
#include <QToolBar>
#include <QString>
#include <QFileDialog>
#include <QGridLayout>
#include <QWidget>
#include <QSplitter>
#include <QPushButton>
#include <QApplication>
#include <QToolBar>
#include "noticedialog.h"
#include "showwidget.h"
#include "dealpicwidget.h"
class PhotoShop : public QMainWindow
{
    Q_OBJECT

public:
    PhotoShop(QWidget *parent = 0);
    ~PhotoShop();
    void createMenu();
    void createActions();
    void setWidget();
    void createToolBar();

protected:
    void mousePressEvent ( QMouseEvent * event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void resizeEvent(QResizeEvent *event);

private slots:
    void openFileSlot();
    void saveFileSlot();
    void slotClickedBtn();
    void slotSplitterMoved(int pos, int index);
    void slotSetSrcImg();
    void slotSetDealImg();

private:
    ShowWidget *showWidget;
    QSplitter *splitter;
    DealPicWidget *dealPicWidget;
    QPushButton *pushButton;
    QPushButton *beforeBtn;
    QToolBar *toolBar;

    QMenu *fileMenu;
    QMenu *editMenu;
    QMenu *windowMenu;
    QMenu *helpMenu;

    QAction *openFileAction;
    QAction *receFileAction;
    QAction *saveFileAction;
    QAction *closeFileAction;

    QAction *docuAction;

    QAction *zoomInAction;
    QAction *zoomOutAction;

    QPoint dragPosition;
    bool bPressFlag;

    void setBtnPos();
    void setBtnIcon();

    bool haveImage;
};

#endif // PHOTOSHOP_H
