/****************************************************************************************************************************************************
 * INCLUDES                                                                                                                                         *
 ****************************************************************************************************************************************************/

#include <QApplication>
#include <QSplashScreen>
#include <QTimer>

#include "defines.h"
#include "mainwindow.h"
#include "screencalc.h"

/****************************************************************************************************************************************************
 * CONSTANTS                                                                                                                                        *
 ****************************************************************************************************************************************************/

/*!
 * \brief This is the name of the organization.
 */
const QString organizationName = QString("Battle Map Tool");

/*!
 * \brief This is the name of the application.
 */
const QString applicationName = QString("Battle Map Tool");

/*!
 * \brief This is the version of the application.
 */
const QString applicationVersion = QString("0.9.1");

/*!
 * \brief This is the period of time in milliseconds that the splash screens at application start are shown.
 */
const int splashScreenDuration = 3000;

/*!
 * \brief This is the font size of the application name shown on the splash screens.
 */
const int splashScreenFontSizeApplicationName = 24;

/*!
 * \brief This is the font size of the application version shown on the splash screens.
 */
const int splashScreenFontSizeApplicationVersion = 12;

/****************************************************************************************************************************************************
 * GLOBAL VARIABLES                                                                                                                                 *
 ****************************************************************************************************************************************************/

/* - */

/****************************************************************************************************************************************************
 * GLOBAL FUNCTIONS                                                                                                                                 *
 ****************************************************************************************************************************************************/

/* - */

/****************************************************************************************************************************************************
 * LOCAL FUNCTIONS                                                                                                                                  *
 ****************************************************************************************************************************************************/

/*!
 * \brief This function is the entry function of the application.
 */
int main(int argc, char *argv[])
{
    /* initialize application with organization name and also application name and version, which are shown on the splash screens */
    QApplication battleMapTool(argc, argv);
    battleMapTool.setOrganizationName(organizationName);
    battleMapTool.setApplicationName(applicationName);
    battleMapTool.setApplicationVersion(applicationVersion);

    /* determine master screen resolution of screen associated with the windowing system the application is connected to */
    int masterScreenResolutionWidth = QGuiApplication::screens().at(MASTERSCREEN_INDEX)->size().width();
    int masterScreenResolutionHeight = QGuiApplication::screens().at(MASTERSCREEN_INDEX)->size().height();

    /* load splash screen image and draw text onto it containing application name and application version */
    QPixmap splashScreenPixmap(SPLASHSCREENIMAGE_SOURCE);
    QPainter painter(&splashScreenPixmap);
    painter.setFont(QFont("Arial", splashScreenFontSizeApplicationName, QFont::Bold));
    painter.drawText(splashScreenPixmap.rect(), Qt::AlignHCenter, battleMapTool.applicationName());
    painter.setFont(QFont("Arial", splashScreenFontSizeApplicationVersion, QFont::Bold));
    painter.drawText(splashScreenPixmap.rect(), Qt::AlignHCenter, QString("\n\n(Version ") + battleMapTool.applicationVersion() + QString(")"));

    QSplashScreen splashScreen1(splashScreenPixmap);
    QSplashScreen splashScreen2(splashScreenPixmap);

    /* show splash screen centrally on main window */
    int splashScreen1PosX = (masterScreenResolutionWidth - splashScreenPixmap.width()) / 2;
    int splashScreen1PosY = (masterScreenResolutionHeight - splashScreenPixmap.height()) / 2;
    splashScreen1.move(splashScreen1PosX, splashScreen1PosY);
    splashScreen1.show();

    /* construct player window and main window and pass the former to the latter for later handling */
    QGraphicsView playerWindow;
    MainWindow mainWindow(&playerWindow);

    /* check whether player screen is available */
    if (FULLNUMBER_SCREENS <= QGuiApplication::screens().count())
    {
        /* determine player screen resolution of screen associated with the windowing system the application is connected to */
        int playerScreenResolutionWidth = QGuiApplication::screens().at(PLAYERSCREEN_INDEX)->size().width();
        int playerScreenResolutionHeight = QGuiApplication::screens().at(PLAYERSCREEN_INDEX)->size().height();

        /* show splash screen centrally on player window */
        int splashScreen2PosX = (playerScreenResolutionWidth - splashScreenPixmap.width()) / 2 + masterScreenResolutionWidth;
        int splashScreen2PosY = (playerScreenResolutionHeight - splashScreenPixmap.height()) / 2;
        splashScreen2.move(splashScreen2PosX, splashScreen2PosY);
        splashScreen2.show();

        /* after splash screen duration, close splash screen */
        QTimer::singleShot(splashScreenDuration, &splashScreen2, SLOT(close()));
    }

    /* after splash screen duration, show player window in full screen mode */
    QTimer::singleShot(splashScreenDuration, &playerWindow, SLOT(showFullScreen()));

    /* after splash screen duration, close splash screen and show main window in full screen mode */
    QTimer::singleShot(splashScreenDuration, &splashScreen1, SLOT(close()));
    QTimer::singleShot(splashScreenDuration, &mainWindow, SLOT(showFullScreen()));

    return battleMapTool.exec();
}
