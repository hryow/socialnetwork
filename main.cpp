#include "socialnetworkwindow.h"

#include <QApplication>
#include <vector>

using namespace std;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    SocialNetworkWindow w;
    w.show();
    return a.exec();
}
