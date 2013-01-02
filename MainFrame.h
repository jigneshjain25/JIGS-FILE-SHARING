#ifndef MAINFRAME_H
#define MAINFRAME_H
#include <QProgressBar>
#include<QLabel>
#include <QMainWindow>
#include <QAction>
#include <QMenu>

#include "JIGSNetworkReply.h"

class FtpApp : public QMainWindow
{
    Q_OBJECT

public:
    FtpApp();

private:

    void createMenus();
    void createActions();
    void createStatusBar();

    QLabel *statusLabel;

    QMenu *file;
    QMenu *upload;
    QMenu *download;
    QMenu *help;

    QAction *quitAction;
    QAction *downloadFileAction;
    QAction *helpAction;
    QAction *aboutAction;
    QAction *uploadFileAction;
    QProgressBar *progressBar;

    QNetworkAccessManager *manager;
    QUrl url;

private slots:
    void uploadFile();
    void aboutPopup();
    void checkError(QNetworkReply::NetworkError e);
    void uploadSuccess(QNetworkReply *reply);
    void setMyValue(qint64,qint64);
    void downloadFile();
    void writeDownloadedFile(QByteArray,QString);
};

#endif // MAINFRAME_H
