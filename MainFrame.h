#ifndef MAINFRAME_H
#define MAINFRAME_H

#include <QMainWindow>
#include <QAction>
#include <QMenu>

class FtpApp : public QMainWindow
{
    Q_OBJECT

public:
    FtpApp();

private:
    void createMenus();
    void createActions();
    void createStatusBar();

    QMenu *file;
    QMenu *upload;
    QMenu *download;
    QMenu *help;
    QAction *quitAction;

    QAction *helpAction;
    QAction *aboutAction;
private slots:
    void uploadFile();
    void aboutPopup();

};

#endif // MAINFRAME_H
