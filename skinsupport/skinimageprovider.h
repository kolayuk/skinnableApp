#ifndef SKINIMAGEPROVIDER_H
#define SKINIMAGEPROVIDER_H

#include <QDeclarativeImageProvider>
#include <QDeclarativeView>

#ifdef Q_OS_SYMBIAN
    #include <gulicon.h>
    #include <apgcli.h>
    #include <bautils.h>
    #include <aknutils.h>
    #include <akniconutils.h>
    #include <aknsutils.h>
    #include <coecntrl.h>
#endif
class SkinImageProvider :  public QObject, public QDeclarativeImageProvider
#ifdef Q_OS_SYMBIAN
,public CCoeControl
#endif

{
    Q_OBJECT
private:
    QPixmap createErrorPixmap(int w, int h,QString text);
public:
    explicit SkinImageProvider();
    QPixmap requestPixmap(const QString &id, QSize *size, const QSize &requestedSize);
    static void installForViewer(QDeclarativeView* viewer);
signals:

public slots:

};

#endif // SKINIMAGEPROVIDER_H
