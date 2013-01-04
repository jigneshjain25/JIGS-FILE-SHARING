#ifndef MAINFRAME_H
#define MAINFRAME_H
#include <QProgressBar>
#include<QLabel>
#include <QMainWindow>
#include <QAction>
#include <QMenu>
#include <QTreeWidget>

#include "JIGSNetworkReply.h"
#include "qftp.h"

class FtpApp : public QMainWindow
{
    Q_OBJECT

public:
    FtpApp();

private:

    void createMenus();
    void createActions();
    void createStatusBar();
    void getFiles();

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

    QTreeWidget *fileList;

    QFtp *ftp;

    QNetworkAccessManager *manager;
    QUrl url;

    QHash<QString, qint64> fileSize;

private slots:
    void quit();
    void uploadFile();
    void aboutPopup();
    void checkError(QNetworkReply::NetworkError e);
    void uploadSuccess(QNetworkReply *reply);
    void setMyValue(qint64,qint64);
    void downloadFile();
    void writeDownloadedFile(QByteArray,QString);
    void addToList(const QUrlInfo&);
    void changeOfState(int);
    void downloadFile(QTreeWidgetItem*);
};

#endif // MAINFRAME_H
