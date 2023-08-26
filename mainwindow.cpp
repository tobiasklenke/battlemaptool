/****************************************************************************************************************************************************
 * INCLUDES                                                                                                                                         *
 ****************************************************************************************************************************************************/

#include "mainwindow.h"
#include "ui_mainwindow.h"

/****************************************************************************************************************************************************
 * DEFINITION OF PUBLIC FUNCTIONS                                                                                                                   *
 ****************************************************************************************************************************************************/

/*!
 * \brief This function is the constructor of the class MainWindow.
 */
MainWindow::MainWindow(QGraphicsView *playerWindow, QWidget *parent) :
    QMainWindow(parent),
    pUserInterface(new Ui::MainWindow),
    pDialog_NewBattleMap(nullptr),
    pPlayerScreenWindow(playerWindow),
    pBattleMapSceneMasterScreen(new BattleMapSceneMasterScreen()),
    pBattleMap(nullptr)
{
    pUserInterface->setupUi(this);

    /* connect signals and slots of the main window actions */
    connect(pUserInterface->Action_NewBattleMap, SIGNAL(triggered()), this, SLOT(open_Dialog_NewBattleMap()));
    connect(pUserInterface->Action_Quit, SIGNAL(triggered()), QApplication::instance(), SLOT(quit()));

    pUserInterface->GraphicsView_BattleMap->setScene(pBattleMapSceneMasterScreen);
    pBattleMapSceneMasterScreen->addText("New Battle Map\t[Ctrl+N]\nOpen Battle Map\t[Ctrl+O]");
    pBattleMapSceneMasterScreen->setBackgroundBrush(QBrush(Qt::lightGray));
}

/*!
 * \brief This function is the destructor of the class MainWindow.
 */
MainWindow::~MainWindow()
{
    delete pUserInterface;
    delete pPlayerScreenWindow;
    delete pBattleMap;
}

/****************************************************************************************************************************************************
 * DEFINITION OF PROTECTED FUNCTIONS                                                                                                                *
 ****************************************************************************************************************************************************/

/* - */

/****************************************************************************************************************************************************
 * DEFINITION OF PRIVATE SLOT FUNCTIONS                                                                                                             *
 ****************************************************************************************************************************************************/

/*!
 * \brief This function handles the action Action_NewBattleMap and opens the dialog Dialog_NewBattleMap.
 */
void MainWindow::open_Dialog_NewBattleMap()
{
    pDialog_NewBattleMap = new Dialog_NewBattleMap(this);

    /* connect signals and slots of the dialog button box actions of the dialog */
    connect(pDialog_NewBattleMap, SIGNAL(accepted()), this, SLOT(accepted_Dialog_NewBattleMap()));
    connect(pDialog_NewBattleMap, SIGNAL(rejected()), this, SLOT(rejected_Dialog_NewBattleMap()));

    pDialog_NewBattleMap->open();
}

/*!
 * \brief This function handles the acceptance of the dialog Dialog_NewBattleMap.
 */
void MainWindow::accepted_Dialog_NewBattleMap()
{
    pBattleMap = new BattleMap(*pDialog_NewBattleMap->getBattleMap());
    delete pDialog_NewBattleMap;

    showBattleMapImageOnMasterScreen();
}

/*!
 * \brief This function handles the rejection of the dialog Dialog_NewBattleMap.
 */
void MainWindow::rejected_Dialog_NewBattleMap()
{
    delete pDialog_NewBattleMap;
}

/****************************************************************************************************************************************************
 * DEFINITION OF PRIVATE FUNCTIONS                                                                                                                  *
 ****************************************************************************************************************************************************/

/*!
 * \brief This function shows the Battle Map image on the master screen.
 */
void MainWindow::showBattleMapImageOnMasterScreen()
{
    /* reset Battle Map scene */
    delete pBattleMapSceneMasterScreen;
    pBattleMapSceneMasterScreen = new BattleMapSceneMasterScreen();
    pUserInterface->GraphicsView_BattleMap->setScene(pBattleMapSceneMasterScreen);

    for (quint32 rowIdx = 0U; rowIdx < pBattleMap->getNumberRows(); rowIdx++)
    {
        for (quint32 columnIdx = 0U; columnIdx < pBattleMap->getNumberColumns(); columnIdx++)
        {
            pBattleMap->getIndexedBattleMapSquare(rowIdx, columnIdx)->setPos(columnIdx * BATTLEMAPSQUARE_SIZE, rowIdx * BATTLEMAPSQUARE_SIZE);
            pBattleMapSceneMasterScreen->addItem(pBattleMap->getIndexedBattleMapSquare(rowIdx, columnIdx));
        }
    }

    pBattleMapSceneMasterScreen->setSceneRect(0, 0, pBattleMap->getNumberColumns()* BATTLEMAPSQUARE_SIZE, pBattleMap->getNumberRows() * BATTLEMAPSQUARE_SIZE);
}
