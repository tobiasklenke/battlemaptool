/****************************************************************************************************************************************************
 * INCLUDES                                                                                                                                         *
 ****************************************************************************************************************************************************/

#include <QApplication>

#include "mainwindow.h"

/****************************************************************************************************************************************************
 * CONSTANTS                                                                                                                                        *
 ****************************************************************************************************************************************************/

/* - */

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

/*!**************************************************************************************************************************************************
 * \brief   This function is the entry function of the application.                                                                                 *
 *                                                                                                                                                  *
 * \details This function shows the main window in full screen mode and moves it to the primary screen. Afterwards, it executes the application.    *
 *                                                                                                                                                  *
 * \param   argc                          Number of strings pointed to by parameter argv                                                            *
 * \param   argv                          Command line arguments                                                                                    *
 *                                                                                                                                                  *
 * \return  This function returns the value 0 if the application is quitted regularly. Otherwise, it returns a value unequal to 0 which indicates   *
 *          an error.                                                                                                                               *
 ****************************************************************************************************************************************************/
int main(int argc, char *argv[])
{
    qDebug() << "..." << __func__;

    QApplication battleMapTool(argc, argv);
    MainWindow mainWindow;

    /* show the main window in full screen mode and move it to the primary screen */
    mainWindow.showFullScreen();
    mainWindow.move(0, 0);

    return battleMapTool.exec();
}
