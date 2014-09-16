#include <QtGui/QApplication>
#include "qmlapplicationviewer.h"

//dont forget to add include
#include <skinsupport/skinimageprovider.h>

Q_DECL_EXPORT int main(int argc, char *argv[])
{
    QScopedPointer<QApplication> app(createApplication(argc, argv));

    QmlApplicationViewer viewer;
    viewer.setOrientation(QmlApplicationViewer::ScreenOrientationAuto);

    //add this line
    SkinImageProvider::installForViewer(&viewer);

    viewer.setMainQmlFile(QLatin1String("qml/skinableApp/main.qml"));
    viewer.showExpanded();
    return app->exec();
}
