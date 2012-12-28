#include <QApplication>
#include <QMessageBox>
#include <QSplashScreen>
#include "myinitthread.h"

#include "MainFrame.h"

int main(int argc,char* argv[])
{
    QApplication app(argc,argv);
    app.setOrganizationName("JIGS");
    app.setApplicationName("JIGS File Sharing");
    FtpApp *ftpApp = new FtpApp;
    ftpApp->show();
    return app.exec();
}
