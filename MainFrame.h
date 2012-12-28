#ifndef MAINFRAME_H
#define MAINFRAME_H

#include<QLabel>
#include <QMainWindow>
#include <QAction>
#include <QMenu>
#include <QNetworkReply>

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

    QAction *helpAction;
    QAction *aboutAction;

    QAction *uploadFileAction;
private slots:
    void uploadFile();
    void aboutPopup();
    void checkError(QNetworkReply::NetworkError);
    void uploadSuccess();
};

#endif // MAINFRAME_H
