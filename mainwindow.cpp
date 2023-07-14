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

    /* connections */
    connect(pDialog_NewBattleMap, SIGNAL(accepted()), this, SLOT(accepted_Dialog_NewBattleMap()));
    connect(pDialog_NewBattleMap, SIGNAL(rejected()), this, SLOT(rejected_Dialog_NewBattleMap()));

    pDialog_NewBattleMap->setWindowModality(Qt::WindowModal);
    pDialog_NewBattleMap->open();
}

/*!
 * \brief This function handels the acceptance of the dialog Dialog_NewBattleMap.
 */
void MainWindow::accepted_Dialog_NewBattleMap()
{
    qDebug() << "..." << __func__;

    //TODO: remove
    qDebug() << pDialog_NewBattleMap->getBattleMapImageSelectedFromSource();
    qDebug() << pDialog_NewBattleMap->getBattleMapImage();
    qDebug() << pDialog_NewBattleMap->getNumberRows();
    qDebug() << pDialog_NewBattleMap->getNumberColumns();
    //pDialog_NewBattleMap->getBattleMapImage().save("test.jpg");

    //TODO: Implement storation of data before deleting pDialog_NewBattleMap

    delete pDialog_NewBattleMap;
}


/*!
 * \brief This function handels the rejection of the dialog Dialog_NewBattleMap.
 */
void MainWindow::rejected_Dialog_NewBattleMap()
{
    qDebug() << "..." << __func__;

    delete pDialog_NewBattleMap;
}
