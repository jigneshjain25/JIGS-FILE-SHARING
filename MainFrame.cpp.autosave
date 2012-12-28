#include <QtGui>
#include <QMenuBar>
#include <QStatusBar>
#include <QLabel>

#include "MainFrame.h"

FtpApp::FtpApp()
{
    setWindowTitle("JIGS File Sharing");
    setGeometry(300,300,700,500);
    QPalette palette;
    palette.setColor(backgroundRole(), Qt::cyan);
    setPalette(palette);
    createStatusBar();
    createActions();
    createMenus();
}

void FtpApp::createMenus()
{
    file = menuBar()->addMenu(tr("&File"));
    file->addAction(quitAction);
    upload = menuBar()->addMenu(tr("&Upload"));
    download = menuBar()->addMenu(tr("&Download"));
    help=menuBar()->addMenu(tr("&Help"));
    help->addAction(helpAction);

}

void FtpApp::createActions()
{
    quitAction = new QAction(tr("&Quit"),this);
    quitAction->setStatusTip("Quit the JIGS File Sharing");
    quitAction->setShortcut(tr("Ctrl+Q"));
    connect(quitAction, SIGNAL(triggered()), this, SLOT(close()));
    helpAction=new QAction(tr("&About"),this);
    helpAction->setStatusTip("About JIGS File Sharing");

}

void FtpApp::createStatusBar()
{
    statusBar()->addWidget(new QLabel("Status"));
}
