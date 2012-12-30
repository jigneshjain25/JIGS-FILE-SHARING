#ifndef MAINFRAME_H
#define MAINFRAME_H

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

private slots:
    void uploadFile();
    void aboutPopup();
    void checkError(QNetworkReply::NetworkError);
    void uploadSuccess();
    void downloadFile();
    void writeDownloadedFile(QByteArray,QString);
};

#endif // MAINFRAME_H
