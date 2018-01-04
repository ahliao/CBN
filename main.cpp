#include "mainwindow.h"
#include "secboxcreator.h"
#include "psobject.h"
#include "lomdialog.h"
#include "psobjectcreatedialog.h"
#include "pslibmanager.h"
#include <QApplication>
#include <QDebug>

using namespace PSCDP;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //MainWindow w;
    PSLibManager w;
    //PSCDP::LOMDialog w;
    //w.resize(500,500);
    //w.show();

    /*if (w.exec() == QDialog::Accepted) {
        PSObject psobj = w.getPSObject();
        qDebug() << "Returned: " << psobj.getName();
    }*/

    return a.exec();
}
