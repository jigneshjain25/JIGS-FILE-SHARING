#include <QApplication>

#include "MainFrame.h"

int main(int argc,char* argv[])
{
    QApplication app(argc,argv);
    app.setOrganizationName("JIGS");
    app.setApplicationName("JIGS File Sharing");
    new FtpApp;
    return app.exec();
}
