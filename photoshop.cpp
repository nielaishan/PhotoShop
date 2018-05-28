#include "photoshop.h"
#include <QDesktopWidget>
#include <QMouseEvent>
#include <QDebug>
#include <QStackedWidget>

PhotoShop::PhotoShop(QWidget *parent)
    : QMainWindow(parent)
{
    haveImage = false;
    setWidget();
    createActions();
    createToolBar();
    createMenu();
}

void PhotoShop::setWidget() {
    splitter = new QSplitter(this);
    this->setWindowTitle(tr("Photo shop"));
    this->setWindowFlags(Qt::WindowCloseButtonHint);

    //设置背景颜色
    QPalette palette(this->palette());
    palette.setColor(QPalette::Background, QColor(245,245,245));
    this->setPalette(palette);
    this->resize(QSize(1200, 700));
//    this->setWindowIcon(QIcon(":/new/prefix1/icon"));       //窗体图标

    showWidget = new ShowWidget;
    dealPicWidget = new DealPicWidget;

    showWidget->resize(900, height());
    dealPicWidget->resize(300, height());
    showWidget->setMinimumWidth(900);
    dealPicWidget->setMaximumWidth(300);

    splitter->addWidget(dealPicWidget);
    splitter->addWidget(showWidget);
    splitter->handle(1)->installEventFilter(this);
    splitter->setHandleWidth(1);
    connect(splitter, SIGNAL(splitterMoved(int,int)), this, SLOT(slotSplitterMoved(int,int)));

    pushButton = new QPushButton(this);
    pushButton->setFocusPolicy(Qt::NoFocus);
    pushButton->resize(13, 13);
    pushButton->setText(tr("x"));
    pushButton->setStyleSheet("border:none; background-color:rgb(255,255,255); color:#000000");

    beforeBtn = new QPushButton(this);
    beforeBtn->setText(tr("原图"));
    beforeBtn->setStyleSheet("border:0px groove gray;border-radius:10px;padding:2px 4px; background-color:rgb(248,248,255);color:#778899;");
    beforeBtn->resize(50, 30);
    beforeBtn->move(1100, 25);
    connect(beforeBtn, SIGNAL(released()), this, SLOT(slotSetDealImg()));
    connect(beforeBtn, SIGNAL(pressed()), this, SLOT(slotSetSrcImg()));

    pushButton->move(dealPicWidget->width()-pushButton->width()-2, 25);
    connect(pushButton, SIGNAL(clicked()), this, SLOT(slotClickedBtn()));

//    dealPicWidget->setStyleSheet("color:#d9d9d9;");
    dealPicWidget->setMouseTracking(true);
    showWidget->setMouseTracking(true);
    dealPicWidget->installEventFilter(this);
    showWidget->installEventFilter(this);
}

void PhotoShop::slotSetSrcImg() {
    ShowWidget::compareImg(true);
}

void PhotoShop::slotSetDealImg() {
    ShowWidget::compareImg(false);
}

void PhotoShop::resizeEvent(QResizeEvent *event)
{
    splitter->setGeometry(0, 0, width(), height());
    move((QApplication::desktop()->width() - width())/2,  (QApplication::desktop()->height() - height())/2);
    QWidget::resizeEvent(event);
}
//设置按钮的位置
void PhotoShop::setBtnPos()
{
    if (dealPicWidget->width() == 0) {
        pushButton->resize(13, 42);
        pushButton->move(dealPicWidget->width()+2, (dealPicWidget->height() - pushButton->height())/2);
    }
    else {
        pushButton->resize(13, 13);
        pushButton->move(dealPicWidget->width()-pushButton->width()-2, 25);
    }
}
//设置按钮的箭头
void PhotoShop::setBtnIcon()
{
    if (dealPicWidget->width() == 0) {
        pushButton->setText(tr(">"));
    }
    else {
        pushButton->setText(tr("x"));
    }
}
//按钮的槽函数
void PhotoShop::slotClickedBtn()
{
    QList <int> sizeList;
    sizeList.clear();
    if (dealPicWidget->width() != 0) {
        sizeList.append(0);
        sizeList.append(1200);
    }
    else {
        sizeList.append(300);
        sizeList.append(900);
    }
    splitter->setSizes(sizeList);
    setBtnIcon();
    setBtnPos();
    showWidget->setWidth(sizeList[0]);
    pushButton->show();
}
//移动
void PhotoShop::slotSplitterMoved(int pos, int index)
{
    Q_UNUSED(pos)
    Q_UNUSED(index)
    setBtnIcon();
    setBtnPos();
    //刷新showWidget的Label大小
    showWidget->setWidth(pos);
    showWidget->update();
}

void PhotoShop::mousePressEvent ( QMouseEvent * event)
{
    bPressFlag = true;
    dragPosition = event->pos();
    QWidget::mousePressEvent(event);
}

void PhotoShop::mouseMoveEvent(QMouseEvent *event)
{
    if (bPressFlag) {
        QPoint relaPos(QCursor::pos() - dragPosition);
        move(relaPos);
    }
    QWidget::mouseMoveEvent(event);
}

void PhotoShop::mouseReleaseEvent(QMouseEvent *event)
{
    bPressFlag = false;
    QWidget::mouseReleaseEvent(event);
}

PhotoShop::~PhotoShop()
{
}
//建立菜单栏
void PhotoShop::createMenu() {
    //File菜单栏
    fileMenu = menuBar()->addMenu(tr(" File "));
    fileMenu->addAction(openFileAction);
    fileMenu->addAction(receFileAction);
    fileMenu->addAction(saveFileAction);
    fileMenu->addSeparator();
    fileMenu->addAction(closeFileAction);
    //Edit菜单栏
    editMenu = menuBar()->addMenu(tr(" Edit "));
    editMenu->addAction(zoomInAction);
    editMenu->addAction(zoomOutAction);
    //Window菜单栏
    windowMenu = menuBar()->addMenu(tr(" Window "));
    //help菜单栏
    helpMenu = menuBar()->addMenu(tr(" Help "));
    helpMenu->addAction(docuAction);
}
//设置工具栏
void PhotoShop::createToolBar() {
    toolBar = new QToolBar(this);
    toolBar->addAction(openFileAction);
    toolBar->addAction(saveFileAction);
    toolBar->setStyleSheet("border: 10px;background-color:rgb(245,245,245);color:#d9d9d9");
    toolBar->setIconSize(QSize(15, 15));
//    pushButton->setStyleSheet("border:none;");
}

//建立action
void PhotoShop::createActions() {
    //打开图片
    openFileAction = new QAction(QIcon(":/image/document-open.png"), tr("open"), this);
    openFileAction->setShortcut(tr("Ctrl+O"));
    openFileAction->setStatusTip(tr("open a file"));
    connect(openFileAction, SIGNAL(triggered()), this, SLOT(openFileSlot()));
    //最近图片
    receFileAction = new QAction(tr("recent Files"), this);
    receFileAction->setShortcut(tr("Ctrl+R"));
    //保存图片
    saveFileAction = new QAction(QIcon(":/image/document-save.png"), tr("save"), this);
    saveFileAction->setShortcut(tr("Ctrl+S"));
    openFileAction->setStatusTip(tr("save picture"));
    connect(saveFileAction, SIGNAL(triggered()), this, SLOT(saveFileSlot()));
    //关闭图片
    closeFileAction = new QAction(tr("close"), this);
    closeFileAction->setShortcut(tr("Ctrl+Q"));
    //文档说明
    docuAction = new QAction(tr("document"), this);
    //放大
    zoomInAction = new QAction(tr("zoom in"), this);
    zoomOutAction = new QAction(tr("zoom out"), this);
}
//打开文件的槽函数
void PhotoShop::openFileSlot()
{
    QString filename;
    filename=QFileDialog::getOpenFileName(this,tr("选择图像"),"",tr("Images (*.png *.bmp *.jpg *.tif *.GIF *.jpeg)"));
    if (showWidget->addImg(filename))
        haveImage = true;
    else
        haveImage = false;
}

void PhotoShop::saveFileSlot() {
    if (!haveImage) {
        NoticeDialog *noticeDialog = new NoticeDialog(this);
        noticeDialog->setMessage("请先打开图片");
    }
    else {
        QString filename = QFileDialog::getSaveFileName(this, tr("Save Image"),"",tr("Images (*.png *.bmp *.jpg)")); //选择路径
        CommandManager::excute(filename);
    }
}
