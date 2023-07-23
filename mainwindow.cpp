/****************************************************************************************************************************************************
 * Includes
 ****************************************************************************************************************************************************/

#include "mainwindow.h"
#include "ui_mainwindow.h"

/****************************************************************************************************************************************************
 * Definition of Public Functions
 ****************************************************************************************************************************************************/

/*!
 * \brief This function is the constructor of the class MainWindow.
 */
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    pUserInterface(new Ui::MainWindow),
    pDialog_NewBattleMap(NULL)
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

/****************************************************************************************************************************************************
 * Definition of Protected Functions
 ****************************************************************************************************************************************************/

/* - */

/****************************************************************************************************************************************************
 * Definition of Private Slot Functions
 ****************************************************************************************************************************************************/

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
    qDebug() << pDialog_NewBattleMap->getBattleMapPixmap();
    qDebug() << pDialog_NewBattleMap->getBattleMap()->getNumberRows();
    qDebug() << pDialog_NewBattleMap->getBattleMap()->getNumberColumns();

//    quint32 numberRows = pDialog_NewBattleMap->getBattleMap()->getNumberRows();
//    quint32 numberColumns = pDialog_NewBattleMap->getBattleMap()->getNumberColumns();

//    for (quint32 rowIdx = 0U; rowIdx < numberRows; rowIdx++)
//    {
//        for (quint32 columnIdx = 0U; columnIdx < numberColumns; columnIdx++)
//        {
//            pDialog_NewBattleMap->getBattleMap()->getIndexedBattleMapSquarePixmap(rowIdx, columnIdx)->pixmap().save("test/test_" + QString::number(rowIdx) + "_" + QString::number(columnIdx) +".jpg");
//        }
//    }

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

/****************************************************************************************************************************************************
 * Definition of Private Functions
 ****************************************************************************************************************************************************/

/* - */
