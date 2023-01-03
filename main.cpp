#include "optecal.h"
#include "filelist.h"
#include "drawroiwindow.h"
#include <QApplication>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    OpteCAL w(argc,argv);
    w.show();

    return a.exec();
}
