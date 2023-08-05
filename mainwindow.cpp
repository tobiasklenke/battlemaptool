/****************************************************************************************************************************************************
 * INCLUDES                                                                                                                                         *
 ****************************************************************************************************************************************************/

#include "mainwindow.h"
#include "ui_mainwindow.h"

/****************************************************************************************************************************************************
 * DEFINITION OF PUBLIC FUNCTIONS                                                                                                                   *
 ****************************************************************************************************************************************************/

/*!**************************************************************************************************************************************************
 * \brief   This function is the constructor of the class MainWindow.                                                                               *
 *                                                                                                                                                  *
 * \details This function sets up the user interface of the class MainWindow and connects the signals and slots of the main window actions.         *
 *          Afterwards, it shows the player window in full screen mode and moves it to the secondary screen.                                        *
 *                                                                                                                                                  *
 * \param   parent                        Parent of the class MainWindow                                                                            *
 *                                                                                                                                                  *
 * \return  This function does not have any return value.                                                                                           *
 ****************************************************************************************************************************************************/
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    pUserInterface(new Ui::MainWindow),
    pDialog_NewBattleMap(nullptr),
    pPlayerScreenWindow(new QGraphicsView)
{
    qDebug() << "..." << __func__;

    pUserInterface->setupUi(this);

    /* connect signals and slots of the main window actions */
    connect(pUserInterface->Action_NewBattleMap, SIGNAL(triggered()), this, SLOT(open_Dialog_NewBattleMap()));
    connect(pUserInterface->Action_Quit, SIGNAL(triggered()), QApplication::instance(), SLOT(quit()));

    /* show the player window in full screen mode and move it to the secondary screen */
    pPlayerScreenWindow->showFullScreen();
    pPlayerScreenWindow->move(MASTER_SCREEN_RESOLUTION.width(), 0);
}

/*!**************************************************************************************************************************************************
 * \brief   This function is the destructor of the class MainWindow.                                                                                *
 *                                                                                                                                                  *
 * \details This function deletes the object pointed to by pUserInterface.                                                                          *
 *                                                                                                                                                  *
 * \return  This function does not have any return value.                                                                                           *
 ****************************************************************************************************************************************************/
MainWindow::~MainWindow()
{
    qDebug() << "..." << __func__;

    delete pUserInterface;
}

/****************************************************************************************************************************************************
 * DEFINITION OF PROTECTED FUNCTIONS                                                                                                                *
 ****************************************************************************************************************************************************/

/* - */

/****************************************************************************************************************************************************
 * DEFINITION OF PRIVATE SLOT FUNCTIONS                                                                                                             *
 ****************************************************************************************************************************************************/

/*!**************************************************************************************************************************************************
 * \brief   This function handles the action Action_NewBattleMap and opens the dialog Dialog_NewBattleMap.                                          *
 *                                                                                                                                                  *
 * \details This function creates a dialog Dialog_NewBattleMap and connects the signals and slots of the dialog button box actions of the dialog    *
 *          Dialog_NewBattleMap. Afterwards, it opens the dialog Dialog_NewBattleMap.                                                               *
 *                                                                                                                                                  *
 * \return  This function does not have any return value.                                                                                           *
 ****************************************************************************************************************************************************/
void MainWindow::open_Dialog_NewBattleMap()
{
    qDebug() << "..." << __func__;

    pDialog_NewBattleMap = new Dialog_NewBattleMap(this);

    /* connect signals and slots of the dialog button box actions of the dialog */
    connect(pDialog_NewBattleMap, SIGNAL(accepted()), this, SLOT(accepted_Dialog_NewBattleMap()));
    connect(pDialog_NewBattleMap, SIGNAL(rejected()), this, SLOT(rejected_Dialog_NewBattleMap()));

    pDialog_NewBattleMap->open();
}

/*!**************************************************************************************************************************************************
 * \brief   This function handles the acceptance of the dialog Dialog_NewBattleMap.                                                                 *
 *                                                                                                                                                  *
 * \details This function stores the Battle Map object created via the dialog Dialog_NewBattleMap. Afterwards, it deletes the object pointed to by  *
 *          pDialog_NewBattleMap.                                                                                                                   *
 *                                                                                                                                                  *
 * \return  This function does not have any return value.                                                                                           *
 ****************************************************************************************************************************************************/
void MainWindow::accepted_Dialog_NewBattleMap()
{
    qDebug() << "..." << __func__;

    //TODO: Implement storation of data before deleting pDialog_NewBattleMap

    delete pDialog_NewBattleMap;
}

/*!**************************************************************************************************************************************************
 * \brief   This function handles the rejection of the dialog Dialog_NewBattleMap.                                                                  *
 *                                                                                                                                                  *
 * \details This function deletes the object pointed to by pDialog_NewBattleMap.                                                                    *
 *                                                                                                                                                  *
 * \return  This function does not have any return value.                                                                                           *
 ****************************************************************************************************************************************************/
void MainWindow::rejected_Dialog_NewBattleMap()
{
    qDebug() << "..." << __func__;

    delete pDialog_NewBattleMap;
}

/****************************************************************************************************************************************************
 * DEFINITION OF PRIVATE FUNCTIONS                                                                                                                  *
 ****************************************************************************************************************************************************/

/* - */
