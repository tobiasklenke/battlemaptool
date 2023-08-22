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
    painter.setFont(QFont("Arial", 24, QFont::Bold));
    painter.drawText(splashScreenPixmap.rect(), Qt::AlignHCenter, battleMapTool.applicationName());
    painter.setFont(QFont("Arial", 12, QFont::Bold));
    painter.drawText(splashScreenPixmap.rect(), Qt::AlignHCenter, QString("\n\n(Version ") + battleMapTool.applicationVersion() + QString(")"));
    QSplashScreen splashScreen1(splashScreenPixmap);
    QSplashScreen splashScreen2(splashScreenPixmap);

    int splashScreen1PosX = (MASTER_SCREEN_RESOLUTION.width() - splashScreenPixmap.width()) / 2;
    int splashScreen1PosY = (MASTER_SCREEN_RESOLUTION.height() - splashScreenPixmap.height()) / 2;
    int splashScreen2PosX = MASTER_SCREEN_RESOLUTION.width() + (PLAYER_SCREEN_RESOLUTION.width() - splashScreenPixmap.width()) / 2;
    int splashScreen2PosY = (PLAYER_SCREEN_RESOLUTION.height() - splashScreenPixmap.height()) / 2;
    splashScreen1.move(splashScreen1PosX, splashScreen1PosY);
    splashScreen2.move(splashScreen2PosX, splashScreen2PosY);
    splashScreen1.show();
    splashScreen2.show();

    QGraphicsView * playerWindow = new QGraphicsView();
    MainWindow mainWindow(playerWindow);

    /* close the splash screen windows, show the main window and player window in full screen mode and move them to the respective screen */
    QTimer::singleShot(SPLASHSCREENDURATION, &splashScreen1, SLOT(close()));
    QTimer::singleShot(SPLASHSCREENDURATION, &splashScreen2, SLOT(close()));
    QTimer::singleShot(SPLASHSCREENDURATION, &mainWindow, SLOT(showFullScreen()));
    QTimer::singleShot(SPLASHSCREENDURATION, playerWindow, SLOT(showFullScreen()));
    mainWindow.move(0, 0);
    playerWindow->move(MASTER_SCREEN_RESOLUTION.width(), 0);

    return battleMapTool.exec();
}
