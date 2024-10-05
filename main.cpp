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
 * \brief This is the index of the master screen.
 */
const int masterScreenIndex = 0;

/*!
 * \brief This is the index of the player screen.
 */
const int playerScreenIndex = 1;

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

    /* determine master and player screen resolution and size values of screens associated with the windowing system the application is connected to */
    int masterScreenResolutionWidth = QGuiApplication::screens().at(masterScreenIndex)->size().width();
    int masterScreenResolutionHeight = QGuiApplication::screens().at(masterScreenIndex)->size().height();
    int playerScreenResolutionWidth = QGuiApplication::screens().at(playerScreenIndex)->size().width();
    int playerScreenResolutionHeight = QGuiApplication::screens().at(playerScreenIndex)->size().height();
    int playerScreenSizeWidth = QGuiApplication::screens().at(playerScreenIndex)->physicalSize().width();
    int playerScreenSizeHeight = QGuiApplication::screens().at(playerScreenIndex)->physicalSize().height();

    /* check whether application is not yet initially configured */
    QSettings settings;
    if (!settings.value(CONFIGKEY_GENERAL_INITIALLY_CONFIGURED).toBool())
    {
        /* set configuration parameters of player screen resolution and diagonal size according to second screen associated with the windowing system the application is connected to */
        settings.setValue(CONFIGKEY_PLAYERSCREEN_RESOLUTION_WIDTH, playerScreenResolutionWidth);
        settings.setValue(CONFIGKEY_PLAYERSCREEN_RESOLUTION_HEIGHT, playerScreenResolutionHeight);
        settings.setValue(CONFIGKEY_PLAYERSCREEN_DIAGONAL, roundToDecimalPlaces(calcScreenDiagonalInInches(playerScreenSizeWidth, playerScreenSizeHeight), PLAYERSCREEN_DIAGONAL_DECIMAL_PLACES));

        /* set configuration parameter containing information whether application is initially configured */
        settings.setValue(CONFIGKEY_GENERAL_INITIALLY_CONFIGURED, true);
    }

    /* load splash screen image and draw text onto it containing application name and application version */
    QPixmap splashScreenPixmap(SPLASHSCREENIMAGE_SOURCE);
    QPainter painter(&splashScreenPixmap);
    painter.setFont(QFont("Arial", splashScreenFontSizeApplicationName, QFont::Bold));
    painter.drawText(splashScreenPixmap.rect(), Qt::AlignHCenter, battleMapTool.applicationName());
    painter.setFont(QFont("Arial", splashScreenFontSizeApplicationVersion, QFont::Bold));
    painter.drawText(splashScreenPixmap.rect(), Qt::AlignHCenter, QString("\n\n(Version ") + battleMapTool.applicationVersion() + QString(")"));

    /* show splash screens centrally on both main window and player window */
    QSplashScreen splashScreen1(splashScreenPixmap);
    QSplashScreen splashScreen2(splashScreenPixmap);
    int splashScreen1PosX = (masterScreenResolutionWidth - splashScreenPixmap.width()) / 2;
    int splashScreen1PosY = (masterScreenResolutionHeight - splashScreenPixmap.height()) / 2;
    int splashScreen2PosX = (playerScreenResolutionWidth - splashScreenPixmap.width()) / 2 + masterScreenResolutionWidth;
    int splashScreen2PosY = (playerScreenResolutionHeight - splashScreenPixmap.height()) / 2;
    splashScreen1.move(splashScreen1PosX, splashScreen1PosY);
    splashScreen2.move(splashScreen2PosX, splashScreen2PosY);
    splashScreen1.show();
    splashScreen2.show();

    /* construct player window and main window and pass the former to the latter for later handling */
    QGraphicsView playerWindow;
    MainWindow mainWindow(&playerWindow);

    /* after splash screen duration, close splash screens and show main window and player window in full screen mode */
    QTimer::singleShot(splashScreenDuration, &splashScreen1, SLOT(close()));
    QTimer::singleShot(splashScreenDuration, &splashScreen2, SLOT(close()));
    QTimer::singleShot(splashScreenDuration, &mainWindow, SLOT(showFullScreen()));
    QTimer::singleShot(splashScreenDuration, &playerWindow, SLOT(showFullScreen()));

    /* move main window and player window to respective screens */
    mainWindow.move(0, 0);
    playerWindow.move(masterScreenResolutionWidth, 0);

    return battleMapTool.exec();
}
