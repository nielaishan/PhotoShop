#ifndef NOTICEDIALOG_H
#define NOTICEDIALOG_H

#include <QDialog>
#include <QLabel>
#include <QTimer>
#include <QHBoxLayout>
class NoticeDialog : public QDialog
{
    Q_OBJECT

public:
    explicit NoticeDialog(QWidget *parent = 0);
    ~NoticeDialog();
    void setMessage(QString message);

private slots:
    void slotClose();
private:
    QLabel *messageLabel;
    QTimer *timer;
    QHBoxLayout *layout;
};

#endif // NOTICEDIALOG_H
