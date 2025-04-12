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
    m_userInterface(new Ui::MainWindow),
    m_playerWindow(playerWindow),
    m_undoStack(new QUndoStack(this)),
    m_operationModeActionGroup(new QActionGroup(this)),
    m_windRoseOrientationActionGroup(new QActionGroup(this)),
    m_wizardNewBattleMap(nullptr),
    m_battleMap(new BattleMap())
{
    QSettings settings;

    /* set up the user interface */
    m_userInterface->setupUi(this);

    /* move player window to respective screen */
    m_playerWindow->move(QGuiApplication::screens().at(MASTERSCREEN_INDEX)->size().width(), 0);

    /* add undo stack actions to menu */
    m_undoAction = m_undoStack->createUndoAction(this, "Undo");
    m_undoAction->setIcon(QIcon(UNDOICON_SOURCE));
    m_undoAction->setShortcuts(QKeySequence::Undo);
    m_redoAction = m_undoStack->createRedoAction(this, "Redo");
    m_redoAction->setIcon(QIcon(REDOICON_SOURCE));
    m_redoAction->setShortcuts(QKeySequence::Redo);
    m_userInterface->menuEdit->insertActions(m_userInterface->menuEdit->actions().at(0), QList<QAction *>({m_undoAction, m_redoAction}));

    /* pass graphics views and Battle Map scene sections to master and player screen handlers */
    m_masterScreenHandler.setGraphicsView(m_userInterface->graphicsViewBattleMapMasterScreen);
    m_masterScreenHandler.setBattleMapSceneSection(&m_battleMapSceneSection);
    m_playerScreenHandler.setGraphicsView(m_playerWindow);
    m_playerScreenHandler.setBattleMapSceneSection(&m_battleMapSceneSection);

    /* create action group for operation mode */
    m_operationModeActionGroup->addAction(m_userInterface->modeSelect);
    m_operationModeActionGroup->addAction(m_userInterface->modeCoverBattleMap);
    m_operationModeActionGroup->addAction(m_userInterface->modeUncoverBattleMap);
    m_operationModeActionGroup->setExclusionPolicy(QActionGroup::ExclusionPolicy::Exclusive);

    /* create action group for wind rose orientation */
    m_windRoseOrientationActionGroup->addAction(m_userInterface->actionWindRoseOrientationNorth);
    m_windRoseOrientationActionGroup->addAction(m_userInterface->actionWindRoseOrientationEast);
    m_windRoseOrientationActionGroup->addAction(m_userInterface->actionWindRoseOrientationSouth);
    m_windRoseOrientationActionGroup->addAction(m_userInterface->actionWindRoseOrientationWest);
    m_windRoseOrientationActionGroup->setExclusionPolicy(QActionGroup::ExclusionPolicy::ExclusiveOptional);

    /* connect signals of QGuiApplication and slots */
    connect(QGuiApplication::instance(), SIGNAL(screenAdded(QScreen*)), this, SLOT(screenAdded(QScreen*)));
    connect(QGuiApplication::instance(), SIGNAL(screenRemoved(QScreen*)), this, SLOT(screenRemoved(QScreen*)));

    /* connect signals and slots of actions from menu File */
    connect(m_userInterface->actionNewBattleMap, SIGNAL(triggered()), this, SLOT(triggeredActionNewBattleMap()));
    connect(m_userInterface->actionOpenBattleMap, SIGNAL(triggered()), this, SLOT(triggeredActionOpenBattleMap()));
    connect(m_userInterface->actionQuit, SIGNAL(triggered()), QApplication::instance(), SLOT(quit()));

    /* connect signals and slots of actions from menu Edit */
    connect(m_userInterface->actionCopy, SIGNAL(triggered()), this, SLOT(triggeredActionCopy()));
    connect(m_userInterface->actionPaste, SIGNAL(triggered()), this, SLOT(triggeredActionPaste()));
    connect(m_userInterface->actionInsertRowAbove, SIGNAL(triggered()), this, SLOT(triggeredActionInsertRowAbove()));
    connect(m_userInterface->actionInsertRowBelow, SIGNAL(triggered()), this, SLOT(triggeredActionInsertRowBelow()));
    connect(m_userInterface->actionInsertColumnLeft, SIGNAL(triggered()), this, SLOT(triggeredActionInsertColumnLeft()));
    connect(m_userInterface->actionInsertColumnRight, SIGNAL(triggered()), this, SLOT(triggeredActionInsertColumnRight()));
    connect(m_userInterface->actionDeleteRowAbove, SIGNAL(triggered()), this, SLOT(triggeredActionDeleteRowAbove()));
    connect(m_userInterface->actionDeleteRowBelow, SIGNAL(triggered()), this, SLOT(triggeredActionDeleteRowBelow()));
    connect(m_userInterface->actionDeleteColumnLeft, SIGNAL(triggered()), this, SLOT(triggeredActionDeleteColumnLeft()));
    connect(m_userInterface->actionDeleteColumnRight, SIGNAL(triggered()), this, SLOT(triggeredActionDeleteColumnRight()));
    connect(m_userInterface->actionRotateBattleMapLeft, SIGNAL(triggered()), this, SLOT(triggeredActionRotateBattleMapLeft()));
    connect(m_userInterface->actionRotateBattleMapRight, SIGNAL(triggered()), this, SLOT(triggeredActionRotateBattleMapRight()));

    /* connect signals and slots of master screen handler */
    connect(&m_masterScreenHandler, SIGNAL(changedSelection(bool)), this, SLOT(changedSelection(bool)));

    /* connect signals and slots of actions from menu View */
    connect(m_userInterface->actionUpdatePlayerScreen, SIGNAL(triggered()), this, SLOT(triggeredActionUpdatePlayerScreen()));
    connect(m_userInterface->actionWindRoseOrientationNorth, SIGNAL(triggered()), this, SLOT(triggeredActionWindRoseOrientation()));
    connect(m_userInterface->actionWindRoseOrientationEast, SIGNAL(triggered()), this, SLOT(triggeredActionWindRoseOrientation()));
    connect(m_userInterface->actionWindRoseOrientationSouth, SIGNAL(triggered()), this, SLOT(triggeredActionWindRoseOrientation()));
    connect(m_userInterface->actionWindRoseOrientationWest, SIGNAL(triggered()), this, SLOT(triggeredActionWindRoseOrientation()));
    connect(m_userInterface->modeSelect, SIGNAL(toggled(bool)), this, SLOT(toggledModeSelect(bool)));
    connect(m_userInterface->modeCoverBattleMap, SIGNAL(toggled(bool)), this, SLOT(toggledModeCoverBattleMap(bool)));
    connect(m_userInterface->modeUncoverBattleMap, SIGNAL(toggled(bool)), this, SLOT(toggledModeUncoverBattleMap(bool)));

    /* connect signals and slots of actions from menu Settings */
    connect(m_userInterface->actionOpenSettings, SIGNAL(triggered()), this, SLOT(triggeredActionOpenSettings()));

    /* connect signals and slots of actions from menu shown on right mouse button click */
    connect(m_userInterface->actionCoverBattleMap, SIGNAL(triggered()), this, SLOT(triggeredActionCoverBattleMap()));
    connect(m_userInterface->actionUncoverBattleMap, SIGNAL(triggered()), this, SLOT(triggeredActionUncoverBattleMap()));

    /* connect signals and slots of other user interface widges */
    connect(m_userInterface->graphicsViewBattleMapMasterScreen, SIGNAL(changedScaleFactor(qreal)), this, SLOT(changedScaleFactor(qreal)));
    connect(m_userInterface->graphicsViewBattleMapMasterScreen, SIGNAL(pressedRightMouseButton(QPoint)), this, SLOT(pressedRightMouseButton(QPoint)));

    /* make labels invisible so that they are not shown initially when there is no Battle Map */
    m_userInterface->labelWindRose->setVisible(false);
    m_userInterface->labelScaleFactor->setVisible(false);

    /* make labels transparent for mouse events so that they do not process them instead of the graphics view */
    m_userInterface->labelWindRose->setAttribute(Qt::WA_TransparentForMouseEvents);
    m_userInterface->labelScaleFactor->setAttribute(Qt::WA_TransparentForMouseEvents);

    /* check whether application is initially configured */
    if (!settings.value(CONFIGKEY_GENERAL_INITIALLY_CONFIGURED).toBool())
    {
        /* check whether player screen is available */
        if (FULLNUMBER_SCREENS <= QGuiApplication::screens().count())
        {
            /* apply settings of player screen */
            applyPlayerScreenSettings();
        }
        else
        {
            /* apply default settings */
            settings.setValue(CONFIGKEY_PLAYERSCREEN_RESOLUTION_WIDTH, DEFAULTVALUE_PLAYERSCREEN_RESOLUTION_WIDTH);
            settings.setValue(CONFIGKEY_PLAYERSCREEN_RESOLUTION_HEIGHT, DEFAULTVALUE_PLAYERSCREEN_RESOLUTION_HEIGHT);
            settings.setValue(CONFIGKEY_PLAYERSCREEN_DIAGONAL, DEFAULTVALUE_PLAYERSCREEN_DIAGONAL);
        }

        /* set configuration parameter containing information whether application is initially configured */
        settings.setValue(CONFIGKEY_GENERAL_INITIALLY_CONFIGURED, true);
    }
}

/*!
 * \brief This function is the destructor of the class MainWindow.
 */
MainWindow::~MainWindow()
{
    /* delete objects created in the constructor except m_wizardNewBattleMap */
    delete m_userInterface;
    delete m_operationModeActionGroup;
    delete m_windRoseOrientationActionGroup;
    delete m_battleMap;
}

/****************************************************************************************************************************************************
 * DEFINITION OF PROTECTED FUNCTIONS                                                                                                                *
 ****************************************************************************************************************************************************/

/* - */

/****************************************************************************************************************************************************
 * DEFINITION OF PRIVATE SLOT FUNCTIONS                                                                                                             *
 ****************************************************************************************************************************************************/

/*!
 * \brief This function handles the addition of a screen.
 */
void MainWindow::screenAdded(QScreen *screen)
{
    QSettings settings;

    /* move player window to respective screen */
    m_playerWindow->move(QGuiApplication::screens().at(MASTERSCREEN_INDEX)->size().width(), 0);

    if (PLAYERSCREEN_INDEX == QGuiApplication::screens().indexOf(screen))
    {
        /* determine resolution and size values of screen associated with the windowing system the application is connected to */
        int addedScreenResolutionWidth = QGuiApplication::screens().at(PLAYERSCREEN_INDEX)->size().width();
        int addedScreenResolutionHeight = QGuiApplication::screens().at(PLAYERSCREEN_INDEX)->size().height();
        int addedScreenSizeWidth = QGuiApplication::screens().at(PLAYERSCREEN_INDEX)->physicalSize().width();
        int addedScreenSizeHeight = QGuiApplication::screens().at(PLAYERSCREEN_INDEX)->physicalSize().height();
        qreal addedScreenDiagonal = roundToDecimalPlaces(calcScreenDiagonalInInches(addedScreenSizeWidth, addedScreenSizeHeight), PLAYERSCREEN_DIAGONAL_DECIMAL_PLACES);

        /* check whether settings of added screen differ from current player screen settings */
        if ((addedScreenDiagonal != settings.value(CONFIGKEY_PLAYERSCREEN_DIAGONAL).toReal()) ||
            (addedScreenResolutionWidth != settings.value(CONFIGKEY_PLAYERSCREEN_RESOLUTION_WIDTH).toInt()) ||
            (addedScreenResolutionHeight != settings.value(CONFIGKEY_PLAYERSCREEN_RESOLUTION_HEIGHT).toInt()))
        {
            /* show message box informing user that settings of added screen differ from current player screen settings and asking user whether settings of added screen shall be applied */
            QMessageBox msgBox(this);
            msgBox.setWindowTitle("Apply settings of added screen");
            msgBox.setText("The settings of the added screen differ from the current settings of the player screen.\n\nWould you like to apply these changes?");
            msgBox.setIcon(QMessageBox::Question);
            msgBox.setStandardButtons(QMessageBox::Apply | QMessageBox::Cancel);
            msgBox.setDefaultButton(QMessageBox::Apply);

            if (QMessageBox::Apply == msgBox.exec())
            {
                /* apply settings of player screen */
                applyPlayerScreenSettings();

                /* check if valid Battle Map is initialized */
                if(m_battleMap->getInitialized())
                {
                    /* update Battle Map scene section */
                    updateBattleMapSceneSection();

                    /* show Battle Map image on master screen and initialize Battle Map image on player screen */
                    m_masterScreenHandler.showBattleMapImage();
                    m_playerScreenHandler.initBattleMapImage();
                }

                /* update wind rose image position on player screen */
                triggeredActionWindRoseOrientation();
            }
        }
    }

    /* enable action that shall only be available when Battle Map is initialized and player screen is available */
    m_userInterface->actionUpdatePlayerScreen->setEnabled(m_battleMap->getInitialized() && (FULLNUMBER_SCREENS <= QGuiApplication::screens().count()));
}

/*!
 * \brief This function handles the removal of a screen.
 */
void MainWindow::screenRemoved(QScreen *screen)
{
    Q_UNUSED(screen);

    /* enable action that shall only be available when Battle Map is initialized and player screen is available */
    m_userInterface->actionUpdatePlayerScreen->setEnabled(m_battleMap->getInitialized() && (FULLNUMBER_SCREENS <= QGuiApplication::screens().count()));
}

/*!
 * \brief This function handles the action actionNewBattleMap.
 */
void MainWindow::triggeredActionNewBattleMap()
{
    /* create wizard WizardNewBattleMap */
    m_wizardNewBattleMap = new WizardNewBattleMap(this);

    /* connect signals and slots of the wizard WizardNewBattleMap */
    connect(m_wizardNewBattleMap, SIGNAL(accepted()), this, SLOT(acceptedWizardNewBattleMap()));
    connect(m_wizardNewBattleMap, SIGNAL(rejected()), this, SLOT(rejectedWizardNewBattleMap()));

    /* open wizard WizardNewBattleMap */
    m_wizardNewBattleMap->open();
}

/*!
 * \brief This function handles the acceptance of the wizard WizardNewBattleMap.
 */
void MainWindow::acceptedWizardNewBattleMap()
{
    /* set wait cursor as the following process may take some time */
    setCursor(Qt::WaitCursor);

    /* store Battle Map from accepted wizard WizardNewBattleMap and delete wizard afterwards */
    delete m_battleMap;
    m_battleMap = new BattleMap(*m_wizardNewBattleMap->getBattleMap());
    m_battleMap->setInitialized();
    delete m_wizardNewBattleMap;

    /* update Battle Map scene section */
    updateBattleMapSceneSection();

    /* share Battle Map with screen handlers */
    m_masterScreenHandler.setBattleMap(m_battleMap);
    m_playerScreenHandler.setBattleMap(m_battleMap);

    /* show Battle Map image on master screen and initialize Battle Map image on player screen */
    m_masterScreenHandler.showBattleMapImage();
    m_playerScreenHandler.initBattleMapImage();

    /* enable actions that shall only be available when Battle Map is initialized */
    m_userInterface->submenuExpandBattleMap->setEnabled(m_battleMap->getInitialized());
    m_userInterface->actionInsertRowAbove->setEnabled(m_battleMap->getInitialized());
    m_userInterface->actionInsertRowBelow->setEnabled(m_battleMap->getInitialized());
    m_userInterface->actionInsertColumnLeft->setEnabled(m_battleMap->getInitialized());
    m_userInterface->actionInsertColumnRight->setEnabled(m_battleMap->getInitialized());
    m_userInterface->submenuReduceBattleMap->setEnabled(m_battleMap->getInitialized());
    m_userInterface->actionDeleteRowAbove->setEnabled(m_battleMap->getInitialized());
    m_userInterface->actionDeleteRowBelow->setEnabled(m_battleMap->getInitialized());
    m_userInterface->actionDeleteColumnLeft->setEnabled(m_battleMap->getInitialized());
    m_userInterface->actionDeleteColumnRight->setEnabled(m_battleMap->getInitialized());
    m_userInterface->actionRotateBattleMapLeft->setEnabled(m_battleMap->getInitialized());
    m_userInterface->actionRotateBattleMapRight->setEnabled(m_battleMap->getInitialized());
    m_userInterface->actionUpdatePlayerScreen->setEnabled(m_battleMap->getInitialized() && (FULLNUMBER_SCREENS <= QGuiApplication::screens().count()));
    m_userInterface->submenuWindRoseOrientation->setEnabled(m_battleMap->getInitialized());
    for (QAction *action : m_windRoseOrientationActionGroup->actions())
    {
        action->setEnabled(m_battleMap->getInitialized());
    }
    for (QAction *action : m_operationModeActionGroup->actions())
    {
        action->setEnabled(m_battleMap->getInitialized());
    }

    /* make label labelScaleFactor visible so that it is shown when Battle Map is initialized */
    m_userInterface->labelScaleFactor->setVisible(m_battleMap->getInitialized());

    /* reset arrow cursor as the process which takes some time is completed */
    setCursor(Qt::ArrowCursor);
}

/*!
 * \brief This function handles the rejection of the wizard WizardNewBattleMap.
 */
void MainWindow::rejectedWizardNewBattleMap()
{
    /* delete wizard QizardNewBattleMap */
    delete m_wizardNewBattleMap;
}

/*!
 * \brief This function handles the action actionOpenBattleMap.
 */
void MainWindow::triggeredActionOpenBattleMap()
{
    qDebug() << __func__;
}

/*!
 * \brief This function handles the acceptance of the wizard WizardOpenBattleMap.
 */
void MainWindow::acceptedWizardOpenBattleMap()
{
    qDebug() << __func__;
}

/*!
 * \brief This function handles the rejection of the wizard WizardOpenBattleMap.
 */
void MainWindow::rejectedWizardOpenBattleMap()
{
    qDebug() << __func__;

    /* delete wizard WizardOpenBattleMap */
}

/*!
 * \brief This function handles the action actionCopy.
 */
void MainWindow::triggeredActionCopy()
{
    /* get pixmaps of Battle Map squares from selection area */
    m_copiedPixmaps = m_masterScreenHandler.getPixmapsFromSelectionArea();

    /* enable action actionPaste since pixmaps of Battle Map squares from selection area have been copied */
    m_userInterface->actionPaste->setEnabled(true);
}

/*!
 * \brief This function handles the action actionPaste.
 */
void MainWindow::triggeredActionPaste()
{
    /* push command UndoCommandPaste to undo stack and apply it by calling its function redo() */
    m_undoStack->push(new UndoCommandPaste(m_copiedPixmaps, m_battleMap, &m_masterScreenHandler));
}

/*!
 * \brief This function handles the action actionInsertRowAbove.
 */
void MainWindow::triggeredActionInsertRowAbove()
{
    /* push command UndoCommandInsertRowAbove to undo stack and apply it by calling its function redo() */
    m_undoStack->push(new UndoCommandInsertRowAbove(m_userInterface, m_battleMap, &m_battleMapSceneSection, &m_masterScreenHandler, &m_playerScreenHandler));
}

/*!
 * \brief This function handles the action actionInsertRowBelow.
 */
void MainWindow::triggeredActionInsertRowBelow()
{
    /* push command UndoCommandInsertRowBelow to undo stack and apply it by calling its function redo() */
    m_undoStack->push(new UndoCommandInsertRowBelow(m_userInterface, m_battleMap, &m_battleMapSceneSection, &m_masterScreenHandler, &m_playerScreenHandler));
}

/*!
 * \brief This function handles the action actionInsertColumnLeft.
 */
void MainWindow::triggeredActionInsertColumnLeft()
{
    /* push command UndoCommandInsertColumnLeft to undo stack and apply it by calling its function redo() */
    m_undoStack->push(new UndoCommandInsertColumnLeft(m_userInterface, m_battleMap, &m_battleMapSceneSection, &m_masterScreenHandler, &m_playerScreenHandler));
}

/*!
 * \brief This function handles the action actionInsertColumnRight.
 */
void MainWindow::triggeredActionInsertColumnRight()
{
    /* push command UndoCommandInsertColumnRight to undo stack and apply it by calling its function redo() */
    m_undoStack->push(new UndoCommandInsertColumnRight(m_userInterface, m_battleMap, &m_battleMapSceneSection, &m_masterScreenHandler, &m_playerScreenHandler));
}

/*!
 * \brief This function handles the action actionDeleteRowAbove.
 */
void MainWindow::triggeredActionDeleteRowAbove()
{
    /* push command UndoCommandDeleteRowAbove to undo stack and apply it by calling its function redo() */
    m_undoStack->push(new UndoCommandDeleteRowAbove(m_userInterface, m_battleMap, &m_battleMapSceneSection, &m_masterScreenHandler, &m_playerScreenHandler));
}

/*!
 * \brief This function handles the action actionDeleteRowBelow.
 */
void MainWindow::triggeredActionDeleteRowBelow()
{
    /* push command UndoCommandDeleteRowBelow to undo stack and apply it by calling its function redo() */
    m_undoStack->push(new UndoCommandDeleteRowBelow(m_userInterface, m_battleMap, &m_battleMapSceneSection, &m_masterScreenHandler, &m_playerScreenHandler));
}

/*!
 * \brief This function handles the action actionDeleteColumnLeft.
 */
void MainWindow::triggeredActionDeleteColumnLeft()
{
    /* push command UndoCommandDeleteColumnLeft to undo stack and apply it by calling its function redo() */
    m_undoStack->push(new UndoCommandDeleteColumnLeft(m_userInterface, m_battleMap, &m_battleMapSceneSection, &m_masterScreenHandler, &m_playerScreenHandler));
}

/*!
 * \brief This function handles the action actionDeleteColumnRight.
 */
void MainWindow::triggeredActionDeleteColumnRight()
{
    /* push command UndoCommandDeleteColumnRight to undo stack and apply it by calling its function redo() */
    m_undoStack->push(new UndoCommandDeleteColumnRight(m_userInterface, m_battleMap, &m_battleMapSceneSection, &m_masterScreenHandler, &m_playerScreenHandler));
}

/*!
 * \brief This function handles the action triggeredActionRotateBattleMapLeft.
 */
void MainWindow::triggeredActionRotateBattleMapLeft()
{
    /* push command UndoCommandRotateBattleMapLeft to undo stack and apply it by calling its function redo() */
    m_undoStack->push(new UndoCommandRotateBattleMapLeft(m_userInterface, m_battleMap, &m_battleMapSceneSection, &m_masterScreenHandler, &m_playerScreenHandler));
}

/*!
 * \brief This function handles the action triggeredActionRotateBattleMapRight.
 */
void MainWindow::triggeredActionRotateBattleMapRight()
{
    /* push command UndoCommandRotateBattleMapRight to undo stack and apply it by calling its function redo() */
    m_undoStack->push(new UndoCommandRotateBattleMapRight(m_userInterface, m_battleMap, &m_battleMapSceneSection, &m_masterScreenHandler, &m_playerScreenHandler));
}

/*!
 * \brief This function handles the action actionUpdatePlayerScreen.
 */
void MainWindow::triggeredActionUpdatePlayerScreen()
{
    /*  update Battle Map image on player screen */
    m_playerScreenHandler.updateBattleMapImage();

    /* clear undo stack */
    m_undoStack->clear();
}

/*!
 * \brief This function handles the actions actionWindRoseOrientationNorth to actionWindRoseOrientationWest.
 */
void MainWindow::triggeredActionWindRoseOrientation()
{
    qreal orientation;

    /* choose wind rose orientation depending on action and update visibility of wind rose on master and player screen */
    if (m_userInterface->actionWindRoseOrientationNorth->isChecked())
    {
        orientation = ORIENTATION_0_DEGREES;
        m_userInterface->labelWindRose->setVisible(true);
        m_playerScreenHandler.setWindRoseGraphicsItemVisibility(true);
    }
    else if (m_userInterface->actionWindRoseOrientationEast->isChecked())
    {
        orientation = ORIENTATION_270_DEGREES;
        m_userInterface->labelWindRose->setVisible(true);
        m_playerScreenHandler.setWindRoseGraphicsItemVisibility(true);
    }
    else if (m_userInterface->actionWindRoseOrientationSouth->isChecked())
    {
        orientation = ORIENTATION_180_DEGREES;
        m_userInterface->labelWindRose->setVisible(true);
        m_playerScreenHandler.setWindRoseGraphicsItemVisibility(true);
    }
    else if (m_userInterface->actionWindRoseOrientationWest->isChecked())
    {
        orientation = ORIENTATION_90_DEGREES;
        m_userInterface->labelWindRose->setVisible(true);
        m_playerScreenHandler.setWindRoseGraphicsItemVisibility(true);
    }
    else
    {
        orientation = ORIENTATION_0_DEGREES;
        m_userInterface->labelWindRose->setVisible(false);
        m_playerScreenHandler.setWindRoseGraphicsItemVisibility(false);
    }

    /* rotate wind rose image according to chosen wind rose orientation */
    QImage windRoseImage = QImage(WINDROSEIMAGE_SOURCE).transformed(QTransform().rotate(orientation));

    /* set wind rose pixmap to screen handlers */
    m_userInterface->labelWindRose->setPixmap(QPixmap::fromImage(windRoseImage).scaled(m_userInterface->labelWindRose->size()));
    m_playerScreenHandler.setWindRoseGraphicsItemPixmap(QPixmap::fromImage(windRoseImage));
}

/*!
 * \brief This function handles a toggle of modeSelect.
 */
void MainWindow::toggledModeSelect(bool checked)
{
    if(checked)
    {
        /* set operation mode of master and player screen handlers to Select */
        m_masterScreenHandler.setOperationMode(Select);
        m_playerScreenHandler.setOperationMode(Select);
    }
}

/*!
 * \brief This function handles a toggle of modeCoverBattleMap.
 */
void MainWindow::toggledModeCoverBattleMap(bool checked)
{
    if(checked)
    {
        /* set operation mode of master and player screen handlers to CoverBattleMap */
        m_masterScreenHandler.setOperationMode(CoverBattleMap);
        m_playerScreenHandler.setOperationMode(CoverBattleMap);
    }
}

/*!
 * \brief This function handles the action actionCoverBattleMap.
 */
void MainWindow::triggeredActionCoverBattleMap()
{
    /* cover selected Battle Map squares on master screen */
    m_masterScreenHandler.handleCoverBattleMap(true);
}

/*!
 * \brief This function handles a toggle of modeUncoverBattleMap.
 */
void MainWindow::toggledModeUncoverBattleMap(bool checked)
{
    if(checked)
    {
        /* set operation mode of master and player screen handlers to UncoverBattleMap */
        m_masterScreenHandler.setOperationMode(UncoverBattleMap);
        m_playerScreenHandler.setOperationMode(UncoverBattleMap);
    }
}

/*!
 * \brief This function handles the action actionUncoverBattleMap.
 */
void MainWindow::triggeredActionUncoverBattleMap()
{
    /* uncover selected Battle Map squares on master screen */
    m_masterScreenHandler.handleCoverBattleMap(false);
}

/*!
 * \brief This function handles the action actionOpenSettings.
 */
void MainWindow::triggeredActionOpenSettings()
{
    /* create dialog DialogSettings */
    m_dialogSettings = new DialogSettings(this);

    /* connect signals and slots of the dialog button box actions of the dialog DialogSettings */
    connect(m_dialogSettings, SIGNAL(accepted()), this, SLOT(acceptedDialogSettings()));
    connect(m_dialogSettings, SIGNAL(rejected()), this, SLOT(rejectedDialogSettings()));

    /* open dialog DialogSettings */
    m_dialogSettings->open();
}

/*!
 * \brief This function handles the acceptance of the dialog DialogSettings.
 */
void MainWindow::acceptedDialogSettings()
{
    if (m_dialogSettings->getSettingsChanged())
    {
        /* check if valid Battle Map is initialized */
        if(m_battleMap->getInitialized())
        {
            /* update Battle Map scene section */
            updateBattleMapSceneSection();

            /* show Battle Map image on master screen and initialize Battle Map image on player screen */
            m_masterScreenHandler.showBattleMapImage();
            m_playerScreenHandler.initBattleMapImage();
        }

        /* update wind rose image position on player screen */
        triggeredActionWindRoseOrientation();
    }

    /* delete dialog DialogSettings */
    delete m_dialogSettings;
}

/*!
 * \brief This function handles the rejection of the dialog DialogSettings.
 */
void MainWindow::rejectedDialogSettings()
{
    /* delete dialog DialogSettings */
    delete m_dialogSettings;
}

/*!
 * \brief This function updates the label that shows the value of the scale factor.
 */
void MainWindow::changedScaleFactor(qreal scaleFactor)
{
    m_userInterface->labelScaleFactor->setText(QString::number(static_cast<quint32>(scaleFactor * HUNDRED_PERCENTAGE)) + QString("%"));
}

/*!
 * \brief This function handles a press of the right mouse button.
 */
void MainWindow::pressedRightMouseButton(QPoint position)
{
    /* check whether the mouse button press was positioned at the Battle Map scene */
    QPointF positionOnScene = m_userInterface->graphicsViewBattleMapMasterScreen->mapToScene(position);
    if ((0 <= positionOnScene.x()) && (positionOnScene.x() <= m_userInterface->graphicsViewBattleMapMasterScreen->scene()->width()) &&
            (0 <= positionOnScene.y()) && (positionOnScene.y() <= m_userInterface->graphicsViewBattleMapMasterScreen->scene()->height()))
    {
        /* create menu, add actions and show it at right mouse button press position */
        QMenu *menu = new QMenu();
        menu->setAttribute(Qt::WA_DeleteOnClose);
        menu->addAction(m_userInterface->actionCopy);
        menu->addAction(m_userInterface->actionPaste);
        menu->addSeparator();
        menu->addAction(m_userInterface->actionCoverBattleMap);
        menu->addAction(m_userInterface->actionUncoverBattleMap);
        menu->popup(m_userInterface->graphicsViewBattleMapMasterScreen->viewport()->mapToGlobal(position));
    }
}

/*!
 * \brief This function enables or disables the actions actionCopy and actionPaste.
 */
void MainWindow::changedSelection(bool selectionCopyable)
{
    /* enable action actionCopy if pixmaps of selected Battle Map squares are copyable */
    m_userInterface->actionCopy->setEnabled(selectionCopyable);

    /* enable action actionPaste if pixmaps of selected Battle Map squares are copyable and if pixmaps of Battle Map squares have already been copied */
    m_userInterface->actionPaste->setEnabled(selectionCopyable && !m_copiedPixmaps.isEmpty());
}

/****************************************************************************************************************************************************
 * DEFINITION OF PRIVATE FUNCTIONS                                                                                                                  *
 ****************************************************************************************************************************************************/

/*!
 * \brief This function updates the Battle Map scene section.
 */
void MainWindow::updateBattleMapSceneSection()
{
    QSettings settings;

    /* reset indexes of first row and column of Battle Map scene section */
    m_battleMapSceneSection.setIndexFirstRowSceneSection(0U);
    m_battleMapSceneSection.setIndexFirstColumnSceneSection(0U);

    /* check whether number of rows displayable on player screen is less than total number of rows of Battle Map and set number of rows of Battle Map scene section to less number */
    quint32 numberRowsOnPlayerScreen = static_cast<quint32>(calcScreenHeightInInches(settings.value(CONFIGKEY_PLAYERSCREEN_DIAGONAL).toReal(), settings.value(CONFIGKEY_PLAYERSCREEN_RESOLUTION_HEIGHT).toUInt(), settings.value(CONFIGKEY_PLAYERSCREEN_RESOLUTION_WIDTH).toUInt()));
    if (numberRowsOnPlayerScreen < m_battleMap->getNumberRows())
    {
        m_battleMapSceneSection.setNumberRowsSceneSection(numberRowsOnPlayerScreen);
    }
    else
    {
        m_battleMapSceneSection.setNumberRowsSceneSection(m_battleMap->getNumberRows());
    }

    /* check whether number of columns displayable on player screen is less than total number of columns of Battle Map and set number of columns of Battle Map scene section to less number */
    quint32 numberColumnsOnPlayerScreen = static_cast<quint32>(calcScreenWidthInInches(settings.value(CONFIGKEY_PLAYERSCREEN_DIAGONAL).toReal(), settings.value(CONFIGKEY_PLAYERSCREEN_RESOLUTION_HEIGHT).toUInt(), settings.value(CONFIGKEY_PLAYERSCREEN_RESOLUTION_WIDTH).toUInt()));
    if (numberColumnsOnPlayerScreen < m_battleMap->getNumberColumns())
    {
        m_battleMapSceneSection.setNumberColumnsSceneSection(numberColumnsOnPlayerScreen);
    }
    else
    {
        m_battleMapSceneSection.setNumberColumnsSceneSection(m_battleMap->getNumberColumns());
    }
}

/*!
 * \brief This function applies the settings of the screen associated with the windowing system the application is connected to.
 */
void MainWindow::applyPlayerScreenSettings()
{
    QSettings settings;

    /* determine resolution and size values of screen associated with the windowing system the application is connected to */
    int playerScreenResolutionWidth = QGuiApplication::screens().at(PLAYERSCREEN_INDEX)->size().width();
    int playerScreenResolutionHeight = QGuiApplication::screens().at(PLAYERSCREEN_INDEX)->size().height();
    int playerScreenSizeWidth = QGuiApplication::screens().at(PLAYERSCREEN_INDEX)->physicalSize().width();
    int playerScreenSizeHeight = QGuiApplication::screens().at(PLAYERSCREEN_INDEX)->physicalSize().height();
    qreal playerScreenDiagonal = roundToDecimalPlaces(calcScreenDiagonalInInches(playerScreenSizeWidth, playerScreenSizeHeight), PLAYERSCREEN_DIAGONAL_DECIMAL_PLACES);

    /* apply settings of player screen size */
    settings.setValue(CONFIGKEY_PLAYERSCREEN_RESOLUTION_WIDTH, playerScreenResolutionWidth);
    settings.setValue(CONFIGKEY_PLAYERSCREEN_RESOLUTION_HEIGHT, playerScreenResolutionHeight);
    settings.setValue(CONFIGKEY_PLAYERSCREEN_DIAGONAL, playerScreenDiagonal);
}
