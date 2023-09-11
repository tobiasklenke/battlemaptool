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
    pUserInterface->GraphicsView_BattleMapMasterScreen->setBackgroundBrush(QBrush(palette.color(QPalette::Window)));

    /* connect signals and slots of the main window actions */
    connect(pUserInterface->Action_NewBattleMap, SIGNAL(triggered()), this, SLOT(open_Dialog_NewBattleMap()));
    connect(pUserInterface->Action_Quit, SIGNAL(triggered()), QApplication::instance(), SLOT(quit()));
    connect(pUserInterface->GraphicsView_BattleMapMasterScreen, SIGNAL(changed_ScaleFactor(qreal)), this, SLOT(changed_ScaleFactor(qreal)));

    pUserInterface->Label_ScaleFactor->setVisible(false);
    pUserInterface->GraphicsView_BattleMapMasterScreen->setScene(pBattleMapSceneMasterScreen);
    pBattleMapSceneMasterScreen->addText("New Battle Map\t[Ctrl+N]\nOpen Battle Map\t[Ctrl+O]");

    //TODO: OUTSOURCE IN FUNCTION ->->->

    /* calculate maximum number of rows and columns displayable on the player screen (each square is one inch high and one inch wide) */
    m_maximumNumberRowsOnPlayerScreen = static_cast<quint32>(calcScreenHeightInInches(CONFIG_PLAYER_SCREEN_DIAGONAL, CONFIG_PLAYER_SCREEN_RESOLUTION.height(), CONFIG_PLAYER_SCREEN_RESOLUTION.width()));
    m_maximumNumberColumnsOnPlayerScreen = static_cast<quint32>(calcScreenWidthInInches(CONFIG_PLAYER_SCREEN_DIAGONAL, CONFIG_PLAYER_SCREEN_RESOLUTION.height(), CONFIG_PLAYER_SCREEN_RESOLUTION.width()));

    //TODO: OUTSOURCE IN FUNCTION <-<-<-
}

/*!
 * \brief This function is the destructor of the class MainWindow.
 */
MainWindow::~MainWindow()
{
    resetBattleMapSceneMasterScreen();
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

/*!
 * \brief This function updates the label that shows the value of the scale factor.
 */
void MainWindow::changed_ScaleFactor(qreal scaleFactor)
{
    pUserInterface->Label_ScaleFactor->setText(QString::number(static_cast<quint32>(scaleFactor * 100)) + QString("%"));
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
    resetBattleMapSceneMasterScreen();
    pBattleMapSceneMasterScreen = new BattleMapSceneMasterScreen();
    pUserInterface->GraphicsView_BattleMapMasterScreen->resetScaling();
    pUserInterface->GraphicsView_BattleMapMasterScreen->setScene(pBattleMapSceneMasterScreen);
    pUserInterface->Label_ScaleFactor->setVisible(true);

    for (quint32 rowIdx = 0U; rowIdx < pBattleMap->getNumberRows(); rowIdx++)
    {
        for (quint32 columnIdx = 0U; columnIdx < pBattleMap->getNumberColumns(); columnIdx++)
        {
            pBattleMap->getIndexedBattleMapSquare(rowIdx, columnIdx)->setPos(columnIdx * CONFIG_BATTLEMAPSQUARE_SIZE, rowIdx * CONFIG_BATTLEMAPSQUARE_SIZE);
            pBattleMapSceneMasterScreen->addItem(pBattleMap->getIndexedBattleMapSquare(rowIdx, columnIdx));
        }
    }

    pBattleMapSceneMasterScreen->setSceneRect(0, 0, pBattleMap->getNumberColumns() * CONFIG_BATTLEMAPSQUARE_SIZE, pBattleMap->getNumberRows() * CONFIG_BATTLEMAPSQUARE_SIZE);
    pBattleMapSceneMasterScreen->addRect(pBattleMapSceneMasterScreen->sceneRect(), QPen(Qt::black, BATTLEMAPGRID_LINEWIDTH, Qt::SolidLine));
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
