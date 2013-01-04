#ifndef JIGSPROGRESSDIALOG_H
#define JIGSPROGRESSDIALOG_H

#include <QProgressDialog>

class JIGSProgressDialog : public QProgressDialog
{
    Q_OBJECT
private:
    qint64 total;
public:
    JIGSProgressDialog();
    void setTotal(qint64);
public slots:
    void setProgress(qint64);
    void setProgress();
};

#endif // JIGSPROGRESSDIALOG_H
