/****************************************************************************************************************************************************
 * Includes
 ****************************************************************************************************************************************************/

#include "mainwindow.h"
#include "ui_mainwindow.h"

/****************************************************************************************************************************************************
 * Member Function Definition
 ****************************************************************************************************************************************************/

/*!
 * \brief This function is the constructor of the class MainWindow.
 */
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    pUserInterface(new Ui::MainWindow),
    pDialog_NewBattleMap(new Dialog_NewBattleMap)
{
    qDebug() << "..." << __func__;

    pUserInterface->setupUi(this);

    /* connections */
    connect(pUserInterface->Action_NewBattleMap, SIGNAL(triggered()), this, SLOT(open_Dialog_NewBattleMap()));
    connect(pUserInterface->Action_Quit, SIGNAL(triggered()), QApplication::instance(), SLOT(quit()));
}

/*!
 * \brief This function is the destructor of the class MainWindow.
 */
MainWindow::~MainWindow()
{
    qDebug() << "..." << __func__;

    delete pUserInterface;
}

/*!
 * \brief This function opens the dialog Dialog_NewBattleMap.
 */
void MainWindow::open_Dialog_NewBattleMap()
{
    qDebug() << "..." << __func__;

    pDialog_NewBattleMap = new Dialog_NewBattleMap(this);

    pDialog_NewBattleMap->setWindowModality(Qt::WindowModal);
    pDialog_NewBattleMap->open();
}
