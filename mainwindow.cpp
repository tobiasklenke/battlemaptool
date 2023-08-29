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
    pBattleMap(new BattleMap())
{
    pUserInterface->setupUi(this);

    QPalette palette;
    pUserInterface->GraphicsView_BattleMap->setBackgroundBrush(QBrush(palette.color(QPalette::Window)));

    /* connect signals and slots of the main window actions */
    connect(pUserInterface->Action_NewBattleMap, SIGNAL(triggered()), this, SLOT(open_Dialog_NewBattleMap()));
    connect(pUserInterface->Action_Quit, SIGNAL(triggered()), QApplication::instance(), SLOT(quit()));

    pUserInterface->GraphicsView_BattleMap->setScene(pBattleMapSceneMasterScreen);
    pBattleMapSceneMasterScreen->addText("New Battle Map\t[Ctrl+N]\nOpen Battle Map\t[Ctrl+O]");

    //TODO: OUTSOURCE IN FUNCTION ->->->

    /* calculate maximum number of rows and columns displayable on the player screen (each square is one inch high and one inch wide) */
    m_maximumNumberRowsOnPlayerScreen = static_cast<quint32>(calcScreenHeightInInches(PLAYER_SCREEN_DIAGONAL, PLAYER_SCREEN_RESOLUTION.height(), PLAYER_SCREEN_RESOLUTION.width()));
    m_maximumNumberColumnsOnPlayerScreen = static_cast<quint32>(calcScreenWidthInInches(PLAYER_SCREEN_DIAGONAL, PLAYER_SCREEN_RESOLUTION.height(), PLAYER_SCREEN_RESOLUTION.width()));

    /* calculate maximum Battle Map square size which allows to display the complete Battle Map section on the master screen that is displayable on the player screen */
    if ((pUserInterface->GraphicsView_BattleMap->height() / m_maximumNumberRowsOnPlayerScreen) > (pUserInterface->GraphicsView_BattleMap->width() / m_maximumNumberColumnsOnPlayerScreen))
    {
        m_battleMapSquareSizeOnMasterScreen = pUserInterface->GraphicsView_BattleMap->width() / m_maximumNumberColumnsOnPlayerScreen;
    }
    else
    {
        m_battleMapSquareSizeOnMasterScreen = pUserInterface->GraphicsView_BattleMap->height() / m_maximumNumberRowsOnPlayerScreen;
    }

    /* round off maximum Battle Map square size to second decimal place */
    m_battleMapSquareSizeOnMasterScreen = m_battleMapSquareSizeOnMasterScreen / 10U;
    m_battleMapSquareSizeOnMasterScreen = m_battleMapSquareSizeOnMasterScreen * 10U;

    //TODO: OUTSOURCE IN FUNCTION <-<-<-
}

/*!
 * \brief This function is the destructor of the class MainWindow.
 */
MainWindow::~MainWindow()
{
    delete pUserInterface;
    delete pPlayerScreenWindow;
    resetBattleMapSceneMasterScreen();
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
    setCursor(Qt::WaitCursor);

    /* reset Battle Map */
    delete pBattleMap;
    pBattleMap = new BattleMap(*pDialog_NewBattleMap->getBattleMap());
    delete pDialog_NewBattleMap;

    showBattleMapImageOnMasterScreen();

    setCursor(Qt::ArrowCursor);
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
            pBattleMap->scaleIndexedBattleMapSquarePixmap(rowIdx, columnIdx, m_battleMapSquareSizeOnMasterScreen);
            pBattleMap->getIndexedBattleMapSquare(rowIdx, columnIdx)->setPos(columnIdx * m_battleMapSquareSizeOnMasterScreen, rowIdx * m_battleMapSquareSizeOnMasterScreen);
            pBattleMapSceneMasterScreen->addItem(pBattleMap->getIndexedBattleMapSquare(rowIdx, columnIdx));
        }
    }

    pBattleMapSceneMasterScreen->setSceneRect(0, 0, pBattleMap->getNumberColumns() * m_battleMapSquareSizeOnMasterScreen, pBattleMap->getNumberRows() * m_battleMapSquareSizeOnMasterScreen);
}

/*!
 * \brief This function resets the Battle Map scene.
 */
void MainWindow::resetBattleMapSceneMasterScreen()
{
    for (QGraphicsItem * item : pBattleMapSceneMasterScreen->items())
    {
        pBattleMapSceneMasterScreen->removeItem(item);
    }

    delete pBattleMapSceneMasterScreen;
}
