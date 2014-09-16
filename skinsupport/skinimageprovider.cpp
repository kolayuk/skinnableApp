#include "SkinImageProvider.h"

#include <QPainter>
#include <QBitmap>
#include <qDebug>
#include <QBrush>
#include <QPen>

#include <QDeclarativeEngine>

#ifdef Q_OS_SYMBIAN
    #include <avkon.mbg>
    #include <aknsbasicbackgroundcontrolcontext.h>
    #include <aknsdrawutils.h>
#endif

SkinImageProvider::SkinImageProvider() :
    QDeclarativeImageProvider(QDeclarativeImageProvider::Pixmap)
{

}

QPixmap SkinImageProvider::requestPixmap(const QString &id, QSize *size, const QSize &requestedSize)
{
#ifdef Q_OS_SYMBIAN
    int w=requestedSize.width()>0?requestedSize.width():CEikonEnv::Static()->ScreenDevice()->SizeInPixels().iWidth;
    int h=requestedSize.height()>0?requestedSize.height():CEikonEnv::Static()->ScreenDevice()->SizeInPixels().iHeight;
    if (size)
        size=new QSize(w,h);
    TSize tsize=TSize(w,h);
    MAknsSkinInstance* skin = AknsUtils::SkinInstance();
    if (id.split("/").length()<2){
        qDebug()<<"Invalid source passed to skinprovider, ID must be MAJOR_ID/MINOR_ID";
        QPixmap pix=createErrorPixmap(w,h,"INVALID PARAMS");
        return pix;
    }
    TAknsItemID idle;
    bool convertOk=false;
    idle.Set(TUid::Uid(id.split("/").at(0).toUInt(&convertOk,16)),id.split("/").at(1).toInt(&convertOk,16) );

    if (!convertOk){
        qDebug()<<"Invalid source passed to skinprovider, ID must be MAJOR_ID and MINOR_ID should be in HEX";
        QPixmap pix=createErrorPixmap(w,h,"INVALID PARAMS");
        return pix;
    }
    int error=KErrNone;
    CFbsBitmap* offScreenBitmap=NULL;
    TRAP(error,{
        CAknsBasicBackgroundControlContext* iSkinContext = CAknsBasicBackgroundControlContext::NewL( idle, TRect(TPoint(0,0),tsize), EFalse );
        offScreenBitmap = new (ELeave) CFbsBitmap();
        User::LeaveIfError( offScreenBitmap->Create( tsize, EColor16M ) );
        CFbsBitGc* bitGc = 0;
        CFbsBitmapDevice* bitmapDevice = CFbsBitmapDevice::NewL( offScreenBitmap );
        User::LeaveIfError( bitmapDevice->CreateContext( bitGc ) );

        // Draw the content on the off-screen bitmap
        AknsDrawUtils::DrawBackground( AknsUtils::SkinInstance(), iSkinContext,(CCoeControl*) this, *bitGc,TPoint(0,0), TRect(TPoint(0,0),tsize), KAknsDrawParamDefault );
    });
    if (error!=KErrNone){
    qDebug()<<"Error occured while retrieving skin element, error code: "<<error<<"May be wrong MAJOR, MINOR IDs?";
        QPixmap pix=createErrorPixmap(w,h,"ERROR "+QString::number(error)+" OCCURED");
        return pix;
    }
    QPixmap pix=QPixmap::fromSymbianCFbsBitmap(offScreenBitmap);
#else
    int w=requestedSize.width()>0?requestedSize.width():360;
    int h=requestedSize.height()>0?requestedSize.height():640;
    QPixmap pix=createErrorPixmap(w,h,"UNSUPPORTED");
#endif
    return pix;
}

void SkinImageProvider::installForViewer(QDeclarativeView *viewer)
{
    viewer->engine()->addImageProvider(QLatin1String("skin"), new SkinImageProvider);
}

QPixmap SkinImageProvider::createErrorPixmap(int w, int h,QString text)
{
    QPixmap pix=QPixmap(w,h);
    QPainter paint(&pix);
    QBrush b=paint.brush();
    b.setColor(Qt::white);
    b.setStyle(Qt::SolidPattern);
    paint.setBrush(b);
    QPen p=paint.pen();
    p.setColor(Qt::black);
    paint.setPen(p);
    paint.drawRect(0,0,w,h);
    paint.drawText(QRect(0,0,w,h),Qt::AlignCenter,text);
    return pix;
}

