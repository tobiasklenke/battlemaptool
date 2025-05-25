/****************************************************************************************************************************************************
 * INCLUDES                                                                                                                                         *
 ****************************************************************************************************************************************************/

#include "wizardpagenewbattlemapdisguise.h"
#include "ui_wizardpagenewbattlemapdisguise.h"

/****************************************************************************************************************************************************
 * DEFINITION OF PUBLIC FUNCTIONS                                                                                                                   *
 ****************************************************************************************************************************************************/

/*!
 * \brief This function is the constructor of the class WizardPageNewBattleMapDisguise.
 */
WizardPageNewBattleMapDisguise::WizardPageNewBattleMapDisguise(BattleMap *battleMap, QWidget *parent) :
    QWizardPage(parent),
    m_userInterface(new Ui::WizardPageNewBattleMapDisguise),
    m_completePage(false),
    m_battleMapScene(new BattleMapScene()),
    m_battleMapSquareGraphicsItems(QList<QList<QGraphicsPixmapItem*>>()),
    m_scaleFactor(1.0),
    m_battleMap(battleMap)
{
    /* set up the user interface */
    m_userInterface->setupUi(this);

    /* set background color of graphics view to window color */
    m_userInterface->graphicsViewNewBattleMap->setBackgroundRole(QPalette::Window);

    /* connect signals and slots of user interface widgets */
    connect(m_userInterface->lineEditSource, &QLineEdit::editingFinished, this, &WizardPageNewBattleMapDisguise::editingFinishedLineEditSource);
    connect(m_userInterface->pushButtonSelectSource, &QPushButton::released, this, &WizardPageNewBattleMapDisguise::releasedPushButtonSelectSource);

    /* connect signals and slots of timer for toggling the original and disguise pixmaps of Battle Map squares */
    connect(&m_pixmapToggleTimer, &QTimer::timeout, this, &WizardPageNewBattleMapDisguise::togglePixmaps);

    /* initialize timer for toggling the original and disguise pixmaps of Battle Map squares */
    m_pixmapToggleTimer.setInterval(TIMERINTERVAL_TOGGLEBATTLEMAPSQUAREPIXMAPS);

    /* set Battle Map scene to graphics view and add text asking user to select source */
    m_userInterface->graphicsViewNewBattleMap->setScene(m_battleMapScene);
    m_sceneText.setPlainText("Select source");
    m_battleMapScene->addItem(&m_sceneText);
}

/*!
 * \brief This function is the destructor of the class WizardPageNewBattleMapDisguise.
 */
WizardPageNewBattleMapDisguise::~WizardPageNewBattleMapDisguise()
{
    /* delete objects created in the constructor */
    delete m_userInterface;
    deleteBattleMapScene();
    deleteBattleMapSquareGraphicsItems();
}

/*!
 * \brief This function prepares the page just before it is shown.
 */
void WizardPageNewBattleMapDisguise::initializePage()
{
    /* connect signals and slots of push buttons of wizard */
    connect(wizard()->button(QWizard::BackButton), &QAbstractButton::released, this, &WizardPageNewBattleMapDisguise::releasedWizardPushButtonBack);
}

/*!
 * \brief This function determines whether the Finish button should be shown for this page or not.
 */
bool WizardPageNewBattleMapDisguise::isComplete() const
{
    return m_completePage;
}

/****************************************************************************************************************************************************
 * DEFINITION OF PROTECTED FUNCTIONS                                                                                                                *
 ****************************************************************************************************************************************************/

/* - */

/****************************************************************************************************************************************************
 * DEFINITION OF PRIVATE SLOT FUNCTIONS                                                                                                             *
 ****************************************************************************************************************************************************/

/*!
 * \brief This function handles a click on the Back button of the wizard.
 */
void WizardPageNewBattleMapDisguise::releasedWizardPushButtonBack()
{
    /* check whether page is currently shown */
    if (wizard()->page(wizard()->currentId()) == this)
    {
        /* delete Battle Map scene and Battle Map square graphics items */
        deleteBattleMapScene();
        deleteBattleMapSquareGraphicsItems();

        /* set Battle Map scene to graphics view and add text asking user to select source */
        m_battleMapScene = new BattleMapScene();
        m_userInterface->graphicsViewNewBattleMap->setScene(m_battleMapScene);
        m_sceneText.setPlainText("Select source");
        m_battleMapScene->addItem(&m_sceneText);

        /* reset widgets according to their functional role for the Battle Map image source selection */
        m_userInterface->lineEditSource->setText("");
        m_userInterface->graphicsViewNewBattleMap->setFrameShape(QFrame::Box);
        m_userInterface->graphicsViewNewBattleMap->setInteractive(false);
        m_userInterface->graphicsViewNewBattleMap->setEventProcessingEnabled(false);
        m_userInterface->graphicsViewNewBattleMap->resetScaling();

        /* stop timer for toggling the original and disguise pixmaps of Battle Map squares */
        m_pixmapToggleTimer.stop();

        /* reset Battle Map */
        m_battleMap->setNumberRows(0U);
        m_battleMap->setNumberColumns(0U);
        m_battleMap->deleteBattleMapSquares();

        /* reset complete page since back button has been released */
        setCompletePage(false);
    }
}

/*!
 * \brief This function handles the editing of lineEditSource.
 */
void WizardPageNewBattleMapDisguise::editingFinishedLineEditSource()
{
    if (!m_userInterface->lineEditSource->text().isEmpty())
    {
        /* reset and reconnect Battle Map scene */
        deleteBattleMapScene();
        m_battleMapScene = new BattleMapScene();
        m_userInterface->graphicsViewNewBattleMap->setScene(m_battleMapScene);

        /* reset graphics view */
        m_userInterface->graphicsViewNewBattleMap->setFrameShape(QFrame::NoFrame);
        m_userInterface->graphicsViewNewBattleMap->resetScaling();

        /* load Battle Map image from selected source */
        QImage battleMapImage(m_userInterface->lineEditSource->text());
        m_battleMapImagePixmap.setPixmap(QPixmap::fromImage(battleMapImage));

        if (battleMapImage.isNull())
        {
            /* reset widgets according to their functional role for the Battle Map image source selection */
            m_userInterface->lineEditSource->setText("");
            m_userInterface->graphicsViewNewBattleMap->setFrameShape(QFrame::Box);
            m_userInterface->graphicsViewNewBattleMap->setInteractive(false);
            m_userInterface->graphicsViewNewBattleMap->setEventProcessingEnabled(false);
            m_userInterface->graphicsViewNewBattleMap->resetScaling();

            /* set Battle Map scene to graphics view and add text asking user to select source */
            m_userInterface->graphicsViewNewBattleMap->setScene(m_battleMapScene);
            m_sceneText.setPlainText("Select source");
            m_battleMapScene->addItem(&m_sceneText);

            /* show message box informing user that selected source file is no image file */
            QMessageBox msgBox(this);
            msgBox.setWindowTitle("Invalid file");
            msgBox.setText("Selected source file is no image file.");
            msgBox.setIcon(QMessageBox::Warning);
            msgBox.exec();

            /* reset complete page since selected source is no image file */
            setCompletePage(false);
        }
        else
        {
            /* check aspect ratio of original and disguise battle map images for equality */
            qreal battleMapOriginalAspectRatio = static_cast<qreal>(m_battleMap->getNumberRows()) / static_cast<qreal>(m_battleMap->getNumberColumns());
            qreal battleMapDisguiseAspectRatio = static_cast<qreal>(battleMapImage.height()) / static_cast<qreal>(battleMapImage.width());

            if (battleMapOriginalAspectRatio == battleMapDisguiseAspectRatio)
            {
                extractBattleMap();

                updateBattleMapSquareGraphicsItems();

                showBattleMapImages();

                if (!checkForDisguise())
                {
                    /* show message box informing user that selected source file is equal to original Battle Map image */
                    QMessageBox msgBox(this);
                    msgBox.setWindowTitle("Missing disguise");
                    msgBox.setText("Selected image file is equal to original Battle Map image.");
                    msgBox.setIcon(QMessageBox::Information);
                    msgBox.exec();
                }

                /* enable event processing of graphics view as soon as Battle Map image is shown */
                m_userInterface->graphicsViewNewBattleMap->setInteractive(true);
                m_userInterface->graphicsViewNewBattleMap->setEventProcessingEnabled(true);

                /* set complete page since selected image is valid */
                setCompletePage(true);
            }
            else
            {
                /* reset widgets according to their functional role for the Battle Map image source selection */
                m_userInterface->lineEditSource->setText("");
                m_userInterface->graphicsViewNewBattleMap->setFrameShape(QFrame::Box);
                m_userInterface->graphicsViewNewBattleMap->setInteractive(false);
                m_userInterface->graphicsViewNewBattleMap->setEventProcessingEnabled(false);
                m_userInterface->graphicsViewNewBattleMap->resetScaling();

                /* set Battle Map scene to graphics view and add text asking user to select source */
                m_userInterface->graphicsViewNewBattleMap->setScene(m_battleMapScene);
                m_sceneText.setPlainText("Select source");
                m_battleMapScene->addItem(&m_sceneText);

                /* show message box informing user that selected source file does not match aspect ratio of original Battle Map image */
                QMessageBox msgBox(this);
                msgBox.setWindowTitle("Invalid aspect ratio");
                msgBox.setText("Selected image file does not match aspect ratio of original Battle Map image.");
                msgBox.setIcon(QMessageBox::Warning);
                msgBox.exec();

                /* reset complete page since selected source file does not match aspect ratio of original Battle Map image */
                setCompletePage(false);
            }
        }
    }
}

/*!
 * \brief This function handles a click on pushButtonSelectSource.
 */
void WizardPageNewBattleMapDisguise::releasedPushButtonSelectSource()
{
    /* select source via file dialog and synchronise file path of selected source with text string of lineEditSource */
    QString selectedSource = QFileDialog::getOpenFileName(this, tr("Select source"), ".", tr("Image Files (*.png *.jpg)"));
    m_userInterface->lineEditSource->setText(selectedSource);

    /* handle editing of lineEditSource */
    editingFinishedLineEditSource();
}

/*!
 * \brief This function toggles the original and the disguise pixmaps.
 */
void WizardPageNewBattleMapDisguise::togglePixmaps()
{
    static bool showDisguisePixmaps = false;

    /* toggle information whether disguise pixmaps shall be shown */
    showDisguisePixmaps = !showDisguisePixmaps;

    for (quint32 rowIdx = 0U; rowIdx < m_battleMap->getNumberRows(); rowIdx++)
    {
        for (quint32 columnIdx = 0U; columnIdx < m_battleMap->getNumberColumns(); columnIdx++)
        {
            /* if Battle Map square is disguisable, set pixmap according to information whether disguise pixmaps shall be shown */
            if (m_battleMap->getBattleMapSquareDisguisable(rowIdx, columnIdx))
            {
                if (showDisguisePixmaps)
                {
                    m_battleMapSquareGraphicsItems[rowIdx][columnIdx]->setPixmap(m_battleMap->getBattleMapSquareDisguisePixmap(rowIdx, columnIdx));
                }
                else
                {
                    m_battleMapSquareGraphicsItems[rowIdx][columnIdx]->setPixmap(m_battleMap->getBattleMapSquareOriginalPixmap(rowIdx, columnIdx));
                }
            }
        }
    }

    /* start timer for toggling original and disguise pixmaps of Battle Map squares */
    m_pixmapToggleTimer.start();
}

/****************************************************************************************************************************************************
 * DEFINITION OF PRIVATE FUNCTIONS                                                                                                                  *
 ****************************************************************************************************************************************************/

/*!
 * \brief This function changes the member variable m_completePage and emits the signal completeChanged().
 */
void WizardPageNewBattleMapDisguise::setCompletePage(bool completePage)
{
    m_completePage = completePage;
    emit completeChanged();
}

/*!
 * \brief This function deletes the graphics items of the Battle Map squares.
 */
void WizardPageNewBattleMapDisguise::deleteBattleMapSquareGraphicsItems()
{
    for (quint32 rowIdx = 0U; rowIdx < m_battleMapSquareGraphicsItems.count(); rowIdx++)
    {
        for (quint32 columnIdx = 0U; columnIdx < m_battleMapSquareGraphicsItems[rowIdx].count(); columnIdx++)
        {
            /* delete graphics items */
            delete m_battleMapSquareGraphicsItems[rowIdx][columnIdx];
        }
    }

    /* remove all graphics items from list */
    m_battleMapSquareGraphicsItems.clear();
}

/*!
 * \brief This function updates the graphics items of the Battle Map squares.
 */
void WizardPageNewBattleMapDisguise::updateBattleMapSquareGraphicsItems()
{
    /* delete Battle Map squares of previous Battle Map */
    deleteBattleMapSquareGraphicsItems();

    for (quint32 rowIdx = 0U; rowIdx < m_battleMap->getNumberRows(); rowIdx++)
    {
        /* append row to nested QList member variables m_battleMapSquaresGraphicsItems if row does not already exist */
        if (rowIdx + 1 > m_battleMapSquareGraphicsItems.count())
        {
            m_battleMapSquareGraphicsItems.append(QList<QGraphicsPixmapItem*>());
        }

        for (quint32 columnIdx = 0U; columnIdx < m_battleMap->getNumberColumns(); columnIdx++)
        {
            /* append graphics item of Battle Map square to row of nested QList member variable m_battleMapSquaresGraphicsItems */
            m_battleMapSquareGraphicsItems[rowIdx].append(new QGraphicsPixmapItem(m_battleMap->getBattleMapSquareOriginalPixmap(rowIdx, columnIdx)));
        }
    }
}

/*!
 * \brief This function deletes the Battle Map scene.
 */
void WizardPageNewBattleMapDisguise::deleteBattleMapScene()
{
    /* remove all graphics items from Battle Map scene */
    for (QGraphicsItem * item : m_battleMapScene->items())
    {
        m_battleMapScene->removeItem(item);
    }

    delete m_battleMapScene;
}

/*!
 * \brief This function extracts the Battle Map.
 */
void WizardPageNewBattleMapDisguise::extractBattleMap()
{
    /* set wait cursor as the following process may take some time */
    QApplication::setOverrideCursor(Qt::WaitCursor);

    if (field("checkBoxDrawBattleMapGrid").toBool())
    {
        /* draw Battle Map grid on Battle Map image */
        QPixmap temporaryPixmap(m_battleMapImagePixmap.pixmap());
        QPainter *painter = new QPainter(&temporaryPixmap);
        painter->setPen(QPen(BATTLEMAPGRID_COLOR, BATTLEMAPGRID_LINEWIDTH, Qt::SolidLine));
        for (QGraphicsLineItem * item : m_battleMapLinesToDraw)
        {
            painter->drawLine(item->line());
        }
        delete painter;
        m_battleMapImagePixmap.setPixmap(temporaryPixmap);
    }

    quint32 edgeLength = m_battleMapImagePixmap.pixmap().height() / m_battleMap->getNumberRows();

    for (quint32 rowIdx = 0U; rowIdx < m_battleMap->getNumberRows(); rowIdx++)
    {
        for (quint32 columnIdx = 0U; columnIdx < m_battleMap->getNumberColumns(); columnIdx++)
        {
            /* extract pixmap of Battle Map square from Battle Map image and scale it to configured size */
            QPixmap temporaryPixmap;
            temporaryPixmap = m_battleMapImagePixmap.pixmap().copy(QRect(columnIdx * edgeLength, rowIdx * edgeLength, edgeLength, edgeLength));
            temporaryPixmap = temporaryPixmap.scaled(QSize(BATTLEMAPSQUARE_SIZE, BATTLEMAPSQUARE_SIZE));

            /* add Battle Map square pixmap to Battle Map */
            m_battleMap->setBattleMapSquareDisguisePixmap(rowIdx, columnIdx, temporaryPixmap);
        }
    }

    /* reset arrow cursor as the process which takes some time is completed */
    QApplication::restoreOverrideCursor();
}

/*!
 * \brief This function shows the original and the disguise Battle Map images.
 */
void WizardPageNewBattleMapDisguise::showBattleMapImages()
{
    /* add Battle Map squares to Battle Map scene */
    for (quint32 rowIdx = 0U; rowIdx < m_battleMap->getNumberRows(); rowIdx++)
    {
        for (quint32 columnIdx = 0U; columnIdx < m_battleMap->getNumberColumns(); columnIdx++)
        {
            m_battleMapSquareGraphicsItems[rowIdx][columnIdx]->setPos(columnIdx * BATTLEMAPSQUARE_SIZE, rowIdx * BATTLEMAPSQUARE_SIZE);

            if (!m_battleMap->getBattleMapSquareDisguisable(rowIdx, columnIdx))
            {
                m_battleMapSquareGraphicsItems[rowIdx][columnIdx]->setOpacity(BATTLEMAPSQUAREUNDISGUISABLE_OPACITY);
            }

            m_battleMapScene->addItem(m_battleMapSquareGraphicsItems[rowIdx][columnIdx]);
        }
    }

    /* start timer for toggling the original and disguise pixmaps of Battle Map squares */
    m_pixmapToggleTimer.start();
}

/*!
 * \brief This function checks whether the Battle Map is disguisable.
 */
bool WizardPageNewBattleMapDisguise::checkForDisguise()
{
    bool foundDisguisableBattleMapSquare = false;

    for (quint32 rowIdx = 0U; rowIdx < m_battleMap->getNumberRows(); rowIdx++)
    {
        for (quint32 columnIdx = 0U; columnIdx < m_battleMap->getNumberColumns(); columnIdx++)
        {
            if (m_battleMap->getBattleMapSquareDisguisable(rowIdx, columnIdx))
            {
                foundDisguisableBattleMapSquare = true;
                break;
            }
        }
    }

    return foundDisguisableBattleMapSquare;
}
