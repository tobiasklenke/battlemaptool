/****************************************************************************************************************************************************
 * INCLUDES                                                                                                                                         *
 ****************************************************************************************************************************************************/

#include <QApplication>
#include <QSplashScreen>
#include <QTimer>

#include "defines.h"
#include "mainwindow.h"

/****************************************************************************************************************************************************
 * CONSTANTS                                                                                                                                        *
 ****************************************************************************************************************************************************/

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
    QApplication battleMapTool(argc, argv);
    battleMapTool.setApplicationName(applicationName);
    battleMapTool.setApplicationVersion(applicationVersion);

    /* show the splash screen windows */
    QPixmap splashScreenPixmap(SPLASHSCREENIMAGE_SOURCE);

    QPainter painter(&splashScreenPixmap);
    painter.setFont(QFont("Arial", splashScreenFontSizeApplicationName, QFont::Bold));
    painter.drawText(splashScreenPixmap.rect(), Qt::AlignHCenter, battleMapTool.applicationName());
    painter.setFont(QFont("Arial", splashScreenFontSizeApplicationVersion, QFont::Bold));
    painter.drawText(splashScreenPixmap.rect(), Qt::AlignHCenter, QString("\n\n(Version ") + battleMapTool.applicationVersion() + QString(")"));
    QSplashScreen splashScreen1(splashScreenPixmap);
    QSplashScreen splashScreen2(splashScreenPixmap);

    int splashScreen1PosX = (CONFIG_MASTER_SCREEN_RESOLUTION.width() - splashScreenPixmap.width()) / 2;
    int splashScreen1PosY = (CONFIG_MASTER_SCREEN_RESOLUTION.height() - splashScreenPixmap.height()) / 2;
    int splashScreen2PosX = (CONFIG_PLAYER_SCREEN_RESOLUTION.width() - splashScreenPixmap.width()) / 2 + CONFIG_MASTER_SCREEN_RESOLUTION.width();
    int splashScreen2PosY = (CONFIG_PLAYER_SCREEN_RESOLUTION.height() - splashScreenPixmap.height()) / 2;
    splashScreen1.move(splashScreen1PosX, splashScreen1PosY);
    splashScreen2.move(splashScreen2PosX, splashScreen2PosY);
    splashScreen1.show();
    splashScreen2.show();

    QGraphicsView * playerWindow = new QGraphicsView();
    MainWindow mainWindow(playerWindow);

    /* close the splash screen windows, show the main window and player window in full screen mode and move them to the respective screen */
    QTimer::singleShot(splashScreenDuration, &splashScreen1, SLOT(close()));
    QTimer::singleShot(splashScreenDuration, &splashScreen2, SLOT(close()));
    QTimer::singleShot(splashScreenDuration, &mainWindow, SLOT(showFullScreen()));
    QTimer::singleShot(splashScreenDuration, playerWindow, SLOT(showFullScreen()));
    mainWindow.move(0, 0);
    playerWindow->move(CONFIG_MASTER_SCREEN_RESOLUTION.width(), 0);

    return battleMapTool.exec();
}
