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
    QAction *quitAction;
};

#endif // MAINFRAME_H
