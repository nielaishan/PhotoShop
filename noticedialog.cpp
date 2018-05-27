#include "noticedialog.h"

NoticeDialog::NoticeDialog(QWidget *parent) :
    QDialog(parent)
{

    this->setWindowTitle(tr("提示"));
    messageLabel = new QLabel(this);
    layout = new QHBoxLayout(this);
    QRect rect = geometry();
    messageLabel->resize(100, 50);
    QFont font;
    font.setPointSize(15);
    messageLabel->setFont(font);
    messageLabel->setStyleSheet(QLatin1String("color:red;"));
    messageLabel->setGeometry(int((rect.width()-messageLabel->width())/2), int((rect.height()-messageLabel->height())/2), messageLabel->width(), messageLabel->height());
    messageLabel->show();
    messageLabel->setAlignment(Qt::AlignCenter);
    layout->addWidget(messageLabel);
    this->setLayout(layout);

    timer = new QTimer(this);
    timer->start(1000);
    connect(timer, SIGNAL(timeout()), this, SLOT(slotClose()));

    this->show();
}

NoticeDialog::~NoticeDialog(){
}

void NoticeDialog::setMessage(QString message) {
    messageLabel->setText(message);
}

void NoticeDialog::slotClose() {
    this->close();
}


