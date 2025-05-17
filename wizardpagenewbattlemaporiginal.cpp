/****************************************************************************************************************************************************
 * INCLUDES                                                                                                                                         *
 ****************************************************************************************************************************************************/

#include "wizardpagenewbattlemaporiginal.h"
#include "ui_wizardpagenewbattlemaporiginal.h"

/****************************************************************************************************************************************************
 * DEFINITION OF PUBLIC FUNCTIONS                                                                                                                   *
 ****************************************************************************************************************************************************/

/*!
 * \brief This function is the constructor of the class WizardPageNewBattleMapOriginal.
 */
WizardPageNewBattleMapOriginal::WizardPageNewBattleMapOriginal(BattleMap *battleMap, QWidget *parent) :
    QWizardPage(parent),
    m_userInterface(new Ui::WizardPageNewBattleMapOriginal),
    m_completePage(false),
    m_battleMapScene(new BattleMapSceneSquareSelection()),
    m_scaleFactor(1.0),
    m_battleMap(battleMap)
{
    /* set up the user interface */
    m_userInterface->setupUi(this);

    /* register field checkBoxDrawBattleMapGrid */
    registerField("checkBoxDrawBattleMapGrid", m_userInterface->checkBoxDrawBattleMapGrid);

    /* set background color of graphics view to window color */
    m_userInterface->graphicsViewNewBattleMap->setBackgroundRole(QPalette::Window);

    /* connect signals and slots of user interface widgets */
    connect(m_userInterface->radioButtonSourceBattleMap, SIGNAL(toggled(bool)), this, SLOT(toggledRadioButtonSourceBattleMap(bool)));
    connect(m_userInterface->radioButtonEmptyBattleMap, SIGNAL(toggled(bool)), this, SLOT(toggledRadioButtonEmptyBattleMap(bool)));
    connect(m_userInterface->lineEditSource, SIGNAL(editingFinished()), this, SLOT(editingFinishedLineEditSource()));
    connect(m_userInterface->pushButtonSelectSource, SIGNAL(released()), this, SLOT(releasedPushButtonSelectSource()));
    connect(m_userInterface->lineEditNumberRows, SIGNAL(editingFinished()), this, SLOT(editingFinishedLineEditNumberRows()));
    connect(m_userInterface->lineEditNumberColumns, SIGNAL(editingFinished()), this, SLOT(editingFinishedLineEditNumberColumns()));
    connect(m_userInterface->pushButtonDecrementNumberRows, SIGNAL(released()), this, SLOT(releasedPushButtonDecrementNumberRows()));
    connect(m_userInterface->pushButtonIncrementNumberRows, SIGNAL(released()), this, SLOT(releasedPushButtonIncrementNumberRows()));
    connect(m_userInterface->pushButtonDecrementNumberColumns, SIGNAL(released()), this, SLOT(releasedPushButtonDecrementNumberColumns()));
    connect(m_userInterface->pushButtonIncrementNumberColumns, SIGNAL(released()), this, SLOT(releasedPushButtonIncrementNumberColumns()));
    connect(m_userInterface->checkBoxDrawBattleMapGrid, SIGNAL(stateChanged(int)), this, SLOT(drawBattleMapGrid(int)));
    connect(m_userInterface->graphicsViewNewBattleMap, SIGNAL(changedScaleFactor(qreal)), this, SLOT(changedScaleFactor(qreal)));

    toggledRadioButtonSourceBattleMap(true);
}

/*!
 * \brief This function is the destructor of the class WizardPageNewBattleMapOriginal.
 */
WizardPageNewBattleMapOriginal::~WizardPageNewBattleMapOriginal()
{
    /* delete objects created in the constructor */
    delete m_userInterface;
    deleteBattleMapScene();
}

/*!
 * \brief This function prepares the page just before it is shown.
 */
void WizardPageNewBattleMapOriginal::initializePage()
{
    /* connect signals and slots of push buttons of wizard */
    connect(wizard()->button(QWizard::NextButton), SIGNAL(released()), this, SLOT(releasedWizardPushButtonNext()));
    connect(wizard()->button(QWizard::FinishButton), SIGNAL(released()), this, SLOT(releasedWizardPushButtonFinish()));
}

/*!
 * \brief This function determines whether the Next and the Finish button should be shown for this page or not.
 */
bool WizardPageNewBattleMapOriginal::isComplete() const
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
 * \brief This function handles a click on the Next button of the wizard.
 */
void WizardPageNewBattleMapOriginal::releasedWizardPushButtonNext()
{
    /* check whether page is currently shown */
    if (wizard()->page(wizard()->currentId()) == this)
    {
        extractBattleMap();
    }
}

/*!
 * \brief This function handles a click on the Finish button of the wizard.
 */
void WizardPageNewBattleMapOriginal::releasedWizardPushButtonFinish()
{
    /* check whether page is currently shown */
    if (wizard()->page(wizard()->currentId()) == this)
    {
        extractBattleMap();
    }
}

/*!
 * \brief This function handles a toggle of radioButtonSourceBattleMap.
 */
void WizardPageNewBattleMapOriginal::toggledRadioButtonSourceBattleMap(bool checked)
{
    if (checked)
    {
        /* set final page so that wizard can be accepted if page is complete */
        setFinalPage(true);

        /* reset complete page since new Battle Map must be selected from source */
        setCompletePage(false);

        /* enable and disable widgets according to their functional role for the Battle Map image source selection */
        m_userInterface->lineEditSource->setEnabled(true);
        m_userInterface->pushButtonSelectSource->setEnabled(true);
        m_userInterface->checkBoxDrawBattleMapGrid->setEnabled(true);
        m_userInterface->lineEditNumberRows->setEnabled(false);
        m_userInterface->lineEditNumberColumns->setEnabled(false);
        m_userInterface->pushButtonDecrementNumberRows->setEnabled(false);
        m_userInterface->pushButtonIncrementNumberRows->setEnabled(false);
        m_userInterface->pushButtonDecrementNumberColumns->setEnabled(false);
        m_userInterface->pushButtonIncrementNumberColumns->setEnabled(false);

        /* reset widgets according to their functional role for the Battle Map image source selection */
        m_userInterface->lineEditSource->setText("");
        m_battleMap->setNumberRows(0U);
        m_userInterface->lineEditNumberRows->setText(QString::number(m_battleMap->getNumberRows()));
        m_userInterface->lineEditNumberRows->setStyleSheet("");
        m_battleMap->setNumberColumns(0U);
        m_userInterface->lineEditNumberColumns->setText(QString::number(m_battleMap->getNumberRows()));
        m_userInterface->lineEditNumberColumns->setStyleSheet("");
        m_userInterface->checkBoxDrawBattleMapGrid->setCheckState(Qt::Unchecked);
        m_userInterface->graphicsViewNewBattleMap->setInteractive(false);
        m_userInterface->graphicsViewNewBattleMap->setEventProcessingEnabled(false);
        m_userInterface->graphicsViewNewBattleMap->resetScaling();
        m_userInterface->graphicsViewNewBattleMap->viewport()->setCursor(Qt::ArrowCursor);
        m_userInterface->graphicsViewNewBattleMap->setToolTip("");
        m_userInterface->graphicsViewNewBattleMap->setFrameShape(QFrame::Box);

        /* reset and reconnect Battle Map scene */
        deleteBattleMapScene();
        m_battleMapScene = new BattleMapSceneSquareSelection();
        connect(m_battleMapScene, SIGNAL(selectedBattleMapSquare()), this, SLOT(selectedBattleMapSquare()));

        /* set Battle Map scene to graphics view and add text asking user to select source */
        m_userInterface->graphicsViewNewBattleMap->setScene(m_battleMapScene);
        m_sceneText.setPlainText("Select source");
        m_battleMapScene->addItem(&m_sceneText);
    }
}

/*!
 * \brief This function handles a toggle of radioButtonEmptyBattleMap.
 */
void WizardPageNewBattleMapOriginal::toggledRadioButtonEmptyBattleMap(bool checked)
{
    QSettings settings;

    if (checked)
    {
        /* set final page so that wizard can be accepted if page is complete */
        setFinalPage(true);

        /* set complete page since new empty Battle Map is selected */
        setCompletePage(true);

        /* disable Next button since disguise is no option for empty Battle Map */
        wizard()->button(QWizard::NextButton)->setEnabled(false);

        /* enable and disable widgets according to their functional role for the creation of an empty Battle Map */
        m_userInterface->lineEditSource->setEnabled(false);
        m_userInterface->pushButtonSelectSource->setEnabled(false);
        m_userInterface->checkBoxDrawBattleMapGrid->setEnabled(false);
        m_userInterface->lineEditNumberRows->setEnabled(true);
        m_userInterface->lineEditNumberColumns->setEnabled(true);
        m_userInterface->pushButtonDecrementNumberRows->setEnabled(true);
        m_userInterface->pushButtonIncrementNumberRows->setEnabled(true);
        m_userInterface->pushButtonDecrementNumberColumns->setEnabled(true);
        m_userInterface->pushButtonIncrementNumberColumns->setEnabled(true);

        /* reset widgets according to their functional role for the creation of an empty Battle Map */
        m_userInterface->lineEditSource->setText("");
        m_userInterface->lineEditNumberRows->setStyleSheet("");
        m_userInterface->lineEditNumberColumns->setStyleSheet("");
        m_userInterface->checkBoxDrawBattleMapGrid->setCheckState(Qt::Checked);
        m_userInterface->graphicsViewNewBattleMap->setInteractive(false);
        m_userInterface->graphicsViewNewBattleMap->setEventProcessingEnabled(false);
        m_userInterface->graphicsViewNewBattleMap->resetScaling();
        m_userInterface->graphicsViewNewBattleMap->viewport()->setCursor(Qt::ArrowCursor);
        m_userInterface->graphicsViewNewBattleMap->setToolTip("");
        m_userInterface->graphicsViewNewBattleMap->setFrameShape(QFrame::Box);

        /* calculate maximum number of rows and columns displayable on the player screen (each square is one inch high and one inch wide) */
        quint32 maximumNumberRows = static_cast<quint32>(calcScreenHeightInInches(settings.value(CONFIGKEY_PLAYERSCREEN_DIAGONAL).toReal(), settings.value(CONFIGKEY_PLAYERSCREEN_RESOLUTION_HEIGHT).toUInt(), settings.value(CONFIGKEY_PLAYERSCREEN_RESOLUTION_WIDTH).toUInt()));
        quint32 maximumNumberColumns = static_cast<quint32>(calcScreenWidthInInches(settings.value(CONFIGKEY_PLAYERSCREEN_DIAGONAL).toReal(), settings.value(CONFIGKEY_PLAYERSCREEN_RESOLUTION_HEIGHT).toUInt(), settings.value(CONFIGKEY_PLAYERSCREEN_RESOLUTION_WIDTH).toUInt()));
        m_battleMap->setNumberRows(maximumNumberRows);
        m_battleMap->setNumberColumns(maximumNumberColumns);
        m_userInterface->lineEditNumberRows->setText(QString::number(m_battleMap->getNumberRows()));
        m_userInterface->lineEditNumberColumns->setText(QString::number(m_battleMap->getNumberColumns()));

        showEmptyBattleMapImage();
    }
}

/*!
 * \brief This function handles the editing of lineEditSource.
 */
void WizardPageNewBattleMapOriginal::editingFinishedLineEditSource()
{
    if (!m_userInterface->lineEditSource->text().isEmpty())
    {
        /* reset number of Battle Map rows and columns */
        m_battleMap->setNumberRows(0U);
        m_battleMap->setNumberColumns(0U);
        m_userInterface->lineEditNumberRows->setText(QString::number(m_battleMap->getNumberRows()));
        m_userInterface->lineEditNumberColumns->setText(QString::number(m_battleMap->getNumberRows()));

        showSourceBattleMapImage();
    }
}

/*!
 * \brief This function handles a click on pushButtonSelectSource.
 */
void WizardPageNewBattleMapOriginal::releasedPushButtonSelectSource()
{
    /* select source via file dialog and synchronise file path of selected source with text string of lineEditSource */
    QString selectedSource = QFileDialog::getOpenFileName(this, tr("Select source"), ".", tr("Image Files (*.png *.jpg)"));
    m_userInterface->lineEditSource->setText(selectedSource);

    /* handle editing of lineEditSource */
    editingFinishedLineEditSource();
}

/*!
 * \brief This function handles the editing of lineEditNumberRows.
 */
void WizardPageNewBattleMapOriginal::editingFinishedLineEditNumberRows()
{
    /* check text string for valid format (integer number) */
    bool validNumber;
    qint32 inputValue = m_userInterface->lineEditNumberRows->text().toInt(&validNumber, 10);

    if (!validNumber || BATTLEMAP_MINIMUMNUMBERROWSANDCOLUMNS > inputValue)
    {
        /* show message box in case of invalid format or not positive number */
        QMessageBox msgBox(this);
        msgBox.setWindowTitle("Invalid input");
        msgBox.setText("Input '" + m_userInterface->lineEditNumberRows->text() + "' is invalid.");
        msgBox.setIcon(QMessageBox::Warning);
        msgBox.exec();

        /* reset text to last valid number of rows */
        m_userInterface->lineEditNumberRows->setText(QString::number(m_battleMap->getNumberRows()));
    }
    else
    {
        /* update number of rows according to input value */
        m_battleMap->setNumberRows(inputValue);
    }

    /* enable or disable push button for decrement depending on current number of rows */
    m_userInterface->pushButtonDecrementNumberRows->setEnabled(!(BATTLEMAP_MINIMUMNUMBERROWSANDCOLUMNS == m_battleMap->getNumberRows()));

    if (m_userInterface->radioButtonSourceBattleMap->isChecked())
    {
        /* correct number of columns considering Battle Map image aspect ratio */
        correctNumberColumns();

        /* check if Battle Map grid covers complete Battle Map image (which affects push button with AcceptRole) and draw Battle Map grid */
        checkBattleMapGrid();
        drawBattleMapGrid();
    }
    else
    {
        showEmptyBattleMapImage();
    }
}

/*!
 * \brief This function handles the editing of lineEditNumberColumns.
 */
void WizardPageNewBattleMapOriginal::editingFinishedLineEditNumberColumns()
{
    /* check text string for valid format (integer number) */
    bool validNumber;
    qint32 inputValue = m_userInterface->lineEditNumberColumns->text().toInt(&validNumber, 10);

    if (!validNumber || BATTLEMAP_MINIMUMNUMBERROWSANDCOLUMNS > inputValue)
    {
        /* show message box in case of invalid format or not positive number */
        QMessageBox msgBox(this);
        msgBox.setWindowTitle("Invalid input");
        msgBox.setText("Input '" + m_userInterface->lineEditNumberColumns->text() + "' is invalid.");
        msgBox.setIcon(QMessageBox::Warning);
        msgBox.exec();

        /* reset text to last valid number of columns */
        m_userInterface->lineEditNumberColumns->setText(QString::number(m_battleMap->getNumberColumns()));;
    }
    else
    {
        /* update number of columns according to input value */
        m_battleMap->setNumberColumns(inputValue);
    }

    /* enable or disable push button for decrement depending on current number of columns */
    m_userInterface->pushButtonDecrementNumberColumns->setEnabled(!(BATTLEMAP_MINIMUMNUMBERROWSANDCOLUMNS == m_battleMap->getNumberColumns()));

    if (m_userInterface->radioButtonSourceBattleMap->isChecked())
    {
        /* correct number of rows considering Battle Map image aspect ratio */
        correctNumberRows();

        /* check if Battle Map grid covers complete Battle Map image (which affects push button with AcceptRole) and draw Battle Map grid */
        checkBattleMapGrid();
        drawBattleMapGrid();
    }
    else
    {
        showEmptyBattleMapImage();
    }
}

/*!
 * \brief This function handles a click on pushButtonDecrementNumberRows.
 */
void WizardPageNewBattleMapOriginal::releasedPushButtonDecrementNumberRows()
{
    /* decrement number of rows */
    m_battleMap->setNumberRows(m_battleMap->getNumberRows() - 1);
    m_userInterface->lineEditNumberRows->setText(QString::number(m_battleMap->getNumberRows()));

    /* enable or disable push button for decrement depending on current number of rows */
    m_userInterface->pushButtonDecrementNumberRows->setEnabled(!(BATTLEMAP_MINIMUMNUMBERROWSANDCOLUMNS == m_battleMap->getNumberRows()));

    if (m_userInterface->radioButtonSourceBattleMap->isChecked())
    {
        /* correct number of columns considering Battle Map image aspect ratio */
        correctNumberColumns();

        /* check if Battle Map grid covers complete Battle Map image (which affects push button with AcceptRole) and draw Battle Map grid */
        checkBattleMapGrid();
        drawBattleMapGrid();
    }
    else
    {
        showEmptyBattleMapImage();
    }
}

/*!
 * \brief This function handles a click on pushButtonIncrementNumberRows.
 */
void WizardPageNewBattleMapOriginal::releasedPushButtonIncrementNumberRows()
{
    /* increment number of rows */
    m_battleMap->setNumberRows(m_battleMap->getNumberRows() + 1);
    m_userInterface->lineEditNumberRows->setText(QString::number(m_battleMap->getNumberRows()));

    /* enable push button for decrement */
    m_userInterface->pushButtonDecrementNumberRows->setEnabled(true);

    if (m_userInterface->radioButtonSourceBattleMap->isChecked())
    {
        /* correct number of columns considering Battle Map image aspect ratio */
        correctNumberColumns();

        /* check if Battle Map grid covers complete Battle Map image (which affects push button with AcceptRole) and draw Battle Map grid */
        checkBattleMapGrid();
        drawBattleMapGrid();
    }
    else
    {
        showEmptyBattleMapImage();
    }
}

/*!
 * \brief This function handles a click on pushButtonDecrementNumberColumns.
 */
void WizardPageNewBattleMapOriginal::releasedPushButtonDecrementNumberColumns()
{
    /* decrement number of columns */
    m_battleMap->setNumberColumns(m_battleMap->getNumberColumns() - 1);
    m_userInterface->lineEditNumberColumns->setText(QString::number(m_battleMap->getNumberColumns()));

    /* enable or disable push button for decrement depending on current number of columns */
    m_userInterface->pushButtonDecrementNumberColumns->setEnabled(!(BATTLEMAP_MINIMUMNUMBERROWSANDCOLUMNS == m_battleMap->getNumberColumns()));

    if (m_userInterface->radioButtonSourceBattleMap->isChecked())
    {
        /* correct number of rows considering Battle Map image aspect ratio */
        correctNumberRows();

        /* check if Battle Map grid covers complete Battle Map image (which affects push button with AcceptRole) and draw Battle Map grid */
        checkBattleMapGrid();
        drawBattleMapGrid();
    }
    else
    {
        showEmptyBattleMapImage();
    }
}

/*!
 * \brief This function handles a click on pushButtonIncrementNumberColumns.
 */
void WizardPageNewBattleMapOriginal::releasedPushButtonIncrementNumberColumns()
{
    /* increment number of columns */
    m_battleMap->setNumberColumns(m_battleMap->getNumberColumns() + 1);
    m_userInterface->lineEditNumberColumns->setText(QString::number(m_battleMap->getNumberColumns()));

    /* enable push button for decrement */
    m_userInterface->pushButtonDecrementNumberColumns->setEnabled(true);

    if (m_userInterface->radioButtonSourceBattleMap->isChecked())
    {
        /* correct number of rows considering Battle Map image aspect ratio */
        correctNumberRows();

        /* check if Battle Map grid covers complete Battle Map image (which affects push button with AcceptRole) and draw Battle Map grid */
        checkBattleMapGrid();
        drawBattleMapGrid();
    }
    else
    {
        showEmptyBattleMapImage();
    }
}

/*!
 * \brief This function handles the selection of a Battle Map square.
 */
void WizardPageNewBattleMapOriginal::selectedBattleMapSquare()
{
    /* calculate average edge length of selected Battle Map square */
    QPointF edgeLengths =  m_battleMapScene->getScenePosRelease() - m_battleMapScene->getScenePosPress();
    quint32 averageEdgeLength = static_cast<quint32>((abs(edgeLengths.rx()) + abs(edgeLengths.ry())) / 2U);

    /* initialize average edge length and counter values for increment and decrement optimization */
    quint32 averageEdgeLengthIncrement = averageEdgeLength;
    quint32 averageEdgeLengthDecrement = averageEdgeLength;
    quint32 counterIncrement = 0U;
    quint32 counterDecrement = 0U;

    quint32 residual;
    if (0U < averageEdgeLength)
    {
        /* optimize the edge length by performing a modulo operation with the height of the Battle Map image and the edge length */
        do
        {
            residual = (m_battleMapImagePixMap.pixmap().height() % averageEdgeLengthIncrement);

            if (0U != residual)
            {
                /* increment average edge length and counter value for increment */
                averageEdgeLengthIncrement++;
                counterIncrement++;
            }

        } while (0U != residual);
        do
        {
            residual = (m_battleMapImagePixMap.pixmap().height() % averageEdgeLengthDecrement);

            if (0U != residual)
            {
                /* decrement average edge length and counter value for decrement */
                averageEdgeLengthDecrement--;
                counterDecrement++;
            }

        } while (0U != residual);

        /* keep edge length that results from optimization with fewer iterations */
        if (counterIncrement < counterDecrement)
        {
            averageEdgeLength = averageEdgeLengthIncrement;
        }
        else
        {
            averageEdgeLength = averageEdgeLengthDecrement;
        }

        /* update number of rows and columns according to optimized edge length of Battle Map squares */
        m_battleMap->setNumberRows(m_battleMapImagePixMap.pixmap().height() / averageEdgeLength);
        m_battleMap->setNumberColumns(m_battleMapImagePixMap.pixmap().width() / averageEdgeLength);
        m_userInterface->lineEditNumberRows->setText(QString::number(m_battleMap->getNumberRows()));
        m_userInterface->lineEditNumberColumns->setText(QString::number(m_battleMap->getNumberColumns()));

        /* check if calculated numbers of rows and columns are reasonable */
        if (BATTLEMAPSELECTION_MAXIMUMNUMBERROWS < m_battleMap->getNumberRows() || BATTLEMAPSELECTION_MAXIMUMNUMBERCOLUMNS < m_battleMap->getNumberColumns())
        {
            /* handle toggle of radioButtonSourceBattleMap as error in number of rows or columns requires reselection of source */
            toggledRadioButtonSourceBattleMap(true);

            /* show message box asking user to check resolution accuracy of selected Battle Map image */
            QMessageBox msgBox(this);
            msgBox.setWindowTitle("Battle Map square selection failed");
            msgBox.setText("Please check the resolution accuracy of the selected Battle Map image.");
            msgBox.setIcon(QMessageBox::Warning);
            msgBox.exec();
        }
        else
        {
            /* enable widgets for editing of numbers of rows and columns for readjustment */
            m_userInterface->lineEditNumberRows->setEnabled(true);
            m_userInterface->lineEditNumberColumns->setEnabled(true);
            m_userInterface->pushButtonDecrementNumberRows->setEnabled(true);
            m_userInterface->pushButtonIncrementNumberRows->setEnabled(true);
            m_userInterface->pushButtonDecrementNumberColumns->setEnabled(true);
            m_userInterface->pushButtonIncrementNumberColumns->setEnabled(true);

            /* check if Battle Map grid covers complete Battle Map image (which affects push button with AcceptRole) and draw Battle Map grid */
            checkBattleMapGrid();
            drawBattleMapGrid();

            /* show message box asking user to check Battle Map grid and readjust number of rows and columns in case of mismatch */
            QMessageBox msgBox(this);
            msgBox.setWindowTitle("Check Battle Map grid");
            msgBox.setText("Please check the Battle Map grid and readjust the number of rows and columns in case of mismatch.");
            msgBox.setIcon(QMessageBox::Question);
            msgBox.exec();
        }
    }
    else
    {
        /* reset number of rows and columns and corresponding widgets as no valid Battle Map square has been selected */
        m_battleMap->setNumberRows(0U);
        m_userInterface->lineEditNumberRows->setText(QString::number(m_battleMap->getNumberRows()));
        m_userInterface->lineEditNumberRows->setStyleSheet("");
        m_battleMap->setNumberColumns(0U);
        m_userInterface->lineEditNumberColumns->setText(QString::number(m_battleMap->getNumberColumns()));
        m_userInterface->lineEditNumberColumns->setStyleSheet("");

        /* disable widgets for editing of numbers of rows and columns for readjustment */
        m_userInterface->lineEditNumberRows->setEnabled(false);
        m_userInterface->lineEditNumberColumns->setEnabled(false);
        m_userInterface->pushButtonDecrementNumberRows->setEnabled(false);
        m_userInterface->pushButtonIncrementNumberRows->setEnabled(false);
        m_userInterface->pushButtonDecrementNumberColumns->setEnabled(false);
        m_userInterface->pushButtonIncrementNumberColumns->setEnabled(false);

        /* reset complete page since Battle Map square must be selected */
        setCompletePage(false);

        /* remove Battle Map grid as no valid Battle Map square has been selected */
        removeBattleMapGrid();
    }
}

/*!
 * \brief This function draws the Battle Map grid.
 */
void WizardPageNewBattleMapOriginal::drawBattleMapGrid(int state)
{
    /* unused, only for convenience when used as private slot function */
    Q_UNUSED(state);

    /* remove current Battle Map grid from Battle Map scene */
    removeBattleMapGrid();

    /* set pen properties according to state of checkBoxDrawBattleMapGrid */
    QPen pen;
    if (m_userInterface->checkBoxDrawBattleMapGrid->isChecked())
    {
        pen = QPen(BATTLEMAPGRID_COLOR, BATTLEMAPGRID_LINEWIDTH * (1 / m_scaleFactor), Qt::SolidLine);
    }
    else
    {
        pen = QPen(BATTLEMAPGRID_COLOR, BATTLEMAPGRID_LINEWIDTH * (1 / m_scaleFactor), Qt::DotLine);
    }

    if (0U < m_battleMap->getNumberRows() && 0U < m_battleMap->getNumberColumns())
    {
        /* draw horizontal Battle Map lines and add them to Battle Map scene */
        quint32 edgeLengthRows = m_battleMapImagePixMap.pixmap().height() / m_battleMap->getNumberRows();
        for (quint32 rowIdx = 0U; rowIdx < m_battleMap->getNumberRows() + 1; rowIdx++)
        {
            QGraphicsLineItem * battleMapLineToDraw = new QGraphicsLineItem(QLineF(0, rowIdx * edgeLengthRows, m_battleMap->getNumberColumns() * edgeLengthRows, rowIdx * edgeLengthRows));
            battleMapLineToDraw->setPen(pen);
            m_battleMapLinesToDraw.append(battleMapLineToDraw);
            m_battleMapScene->addItem(m_battleMapLinesToDraw.last());
        }

        /* draw vertical Battle Map lines and add them to Battle Map scene */
        quint32 edgeLengthColumns = m_battleMapImagePixMap.pixmap().width() / m_battleMap->getNumberColumns();
        for (quint32 columnIdx = 0U; columnIdx < m_battleMap->getNumberColumns() + 1; columnIdx++)
        {
            QGraphicsLineItem * battleMapLineToDraw = new QGraphicsLineItem(QLineF(columnIdx * edgeLengthColumns, 0, columnIdx * edgeLengthColumns, m_battleMap->getNumberRows() * edgeLengthColumns));
            battleMapLineToDraw->setPen(pen);
            m_battleMapLinesToDraw.append(battleMapLineToDraw);
            m_battleMapScene->addItem(m_battleMapLinesToDraw.last());
        }
    }
}

/*!
 * \brief This function updates the member variable m_scaleFactor and redraws the Battle Map grid.
 */
void WizardPageNewBattleMapOriginal::changedScaleFactor(qreal scaleFactor)
{
    /* update scale factor and redraw Battle Map grid*/
    m_scaleFactor = scaleFactor;
    drawBattleMapGrid();

    /* set new scale factor to Battle Map scene */
    m_battleMapScene->changedScaleFactor(scaleFactor);
}

/****************************************************************************************************************************************************
 * DEFINITION OF PROTECTED FUNCTIONS                                                                                                                *
 ****************************************************************************************************************************************************/

/* - */

/****************************************************************************************************************************************************
 * DEFINITION OF PRIVATE SLOT FUNCTIONS                                                                                                             *
 ****************************************************************************************************************************************************/

/* - */

/****************************************************************************************************************************************************
 * DEFINITION OF PRIVATE FUNCTIONS                                                                                                                  *
 ****************************************************************************************************************************************************/

/*!
 * \brief This function changes the member variable m_completePage and emits the signal completeChanged().
 */
void WizardPageNewBattleMapOriginal::setCompletePage(bool completePage)
{
    m_completePage = completePage;
    emit completeChanged();
}

/*!
 * \brief This function shows the empty Battle Map image.
 */
void WizardPageNewBattleMapOriginal::showEmptyBattleMapImage()
{
    /* reset and reconnect Battle Map scene */
    deleteBattleMapScene();
    m_battleMapScene = new BattleMapSceneSquareSelection();
    m_userInterface->graphicsViewNewBattleMap->setScene(m_battleMapScene);

    /* reset graphics view */
    m_userInterface->graphicsViewNewBattleMap->setFrameShape(QFrame::NoFrame);

    /* load image of empty Battle Map square and scale it to configured size */
    QImage emptyBattleMapSquare(EMPTYBATTLEMAPSQUAREIMAGE_SOURCE);
    emptyBattleMapSquare = emptyBattleMapSquare.scaledToWidth(BATTLEMAPSQUARE_SIZE);

    /* construct empty Battle Map image from number of empty Battle Map squares according to number of rows and columns */
    QPixmap temporaryPixmap(QSize(m_battleMap->getNumberColumns()* BATTLEMAPSQUARE_SIZE, m_battleMap->getNumberRows() * BATTLEMAPSQUARE_SIZE));
    QPainter *painter = new QPainter(&temporaryPixmap);
    for (quint32 rowIdx = 0U; rowIdx < m_battleMap->getNumberRows(); rowIdx++)
    {
        for (quint32 columnIdx = 0U; columnIdx < m_battleMap->getNumberColumns(); columnIdx++)
        {
            QRect targetRect = QRect(columnIdx * BATTLEMAPSQUARE_SIZE, rowIdx * BATTLEMAPSQUARE_SIZE, BATTLEMAPSQUARE_SIZE, BATTLEMAPSQUARE_SIZE);
            QRect sourceRect = emptyBattleMapSquare.rect();
            painter->drawPixmap(targetRect, QPixmap::fromImage(emptyBattleMapSquare), sourceRect);
        }
    }
    delete painter;

    /* add Battle Map pixmap to Battle Map scene */
    m_battleMapImagePixMap.setPixmap(temporaryPixmap);
    m_battleMapScene->addItem(&m_battleMapImagePixMap);
    m_battleMapScene->setSceneRect(0, 0, m_battleMapImagePixMap.pixmap().width(), m_battleMapImagePixMap.pixmap().height());

    drawBattleMapGrid();

    /* enable event processing of graphics view as soon as Battle Map image is shown */
    m_userInterface->graphicsViewNewBattleMap->setEventProcessingEnabled(true);
}

/*!
 * \brief This function shows the Battle Map image from the selected source.
 */
void WizardPageNewBattleMapOriginal::showSourceBattleMapImage()
{
    /* reset and reconnect Battle Map scene */
    deleteBattleMapScene();
    m_battleMapScene = new BattleMapSceneSquareSelection();
    connect(m_battleMapScene, SIGNAL(selectedBattleMapSquare()), this, SLOT(selectedBattleMapSquare()));
    m_userInterface->graphicsViewNewBattleMap->setScene(m_battleMapScene);

    /* reset graphics view */
    m_userInterface->graphicsViewNewBattleMap->setFrameShape(QFrame::NoFrame);
    m_userInterface->graphicsViewNewBattleMap->resetScaling();

    /* load Battle Map image from selected source */
    QImage battleMapImage(m_userInterface->lineEditSource->text());

    if (battleMapImage.isNull())
    {
        /* handle toggle of radioButtonSourceBattleMap as error of selected source requires reselection of source */
        toggledRadioButtonSourceBattleMap(true);

        /* show message box informing user that selected source file is no image file */
        QMessageBox msgBox(this);
        msgBox.setWindowTitle("Invalid file");
        msgBox.setText("Selected source file is no image file.");
        msgBox.setIcon(QMessageBox::Warning);
        msgBox.exec();
    }
    else
    {
        /* prepare graphics view for selection of Battle Map square */
        m_userInterface->graphicsViewNewBattleMap->setInteractive(true);
        m_userInterface->graphicsViewNewBattleMap->viewport()->setCursor(Qt::CrossCursor);
        m_userInterface->graphicsViewNewBattleMap->setToolTip("Select Battle Map square");

        /* add Battle Map pixmap to Battle Map scene */
        m_battleMapImagePixMap.setPixmap(QPixmap::fromImage(battleMapImage));
        m_battleMapScene->addItem(&m_battleMapImagePixMap);
        m_battleMapScene->setSceneRect(0, 0, m_battleMapImagePixMap.pixmap().width(), m_battleMapImagePixMap.pixmap().height());

        /* show message box asking user to select Battle Map square */
        QMessageBox msgBox(this);
        msgBox.setWindowTitle("Select Battle Map square");
        msgBox.setText("Please select a Battle Map square in order to determine the number of rows and columns of the Battle Map.");
        msgBox.setIcon(QMessageBox::Question);
        msgBox.exec();

        /* enable event processing of graphics view as soon as Battle Map image is shown */
        m_userInterface->graphicsViewNewBattleMap->setEventProcessingEnabled(true);
    }
}

/*!
 * \brief This function corrects the number of rows considering the Battle Map squares aspect ratio.
 */
void WizardPageNewBattleMapOriginal::correctNumberRows()
{
    /* correct number of rows considering Battle Map squares aspect ratio */
    quint32 edgeLength = m_battleMapImagePixMap.pixmap().width() / m_battleMap->getNumberColumns();
    quint32 numberRows = m_battleMapImagePixMap.pixmap().height() / edgeLength;

    /* do not decrement number of rows to 0 */
    if (0U < numberRows)
    {
        m_battleMap->setNumberRows(numberRows);
        m_userInterface->lineEditNumberRows->setText(QString::number(m_battleMap->getNumberRows()));

        /* enable or disable push button for decrement depending on current number of rows */
        m_userInterface->pushButtonDecrementNumberRows->setEnabled(!(BATTLEMAP_MINIMUMNUMBERROWSANDCOLUMNS == m_battleMap->getNumberRows()));
    }
}

/*!
 * \brief This function corrects the number of columns considering the Battle Map squares aspect ratio.
 */
void WizardPageNewBattleMapOriginal::correctNumberColumns()
{
    /* correct number of columns considering Battle Map squares aspect ratio */
    quint32 edgeLength = m_battleMapImagePixMap.pixmap().height() / m_battleMap->getNumberRows();
    quint32 numberColumns = m_battleMapImagePixMap.pixmap().width() / edgeLength;

    /* do not decrement number of columns to 0 */
    if (0U < numberColumns)
    {
        m_battleMap->setNumberColumns(numberColumns);
        m_userInterface->lineEditNumberColumns->setText(QString::number(m_battleMap->getNumberColumns()));

        /* enable or disable push button for decrement depending on current number of columns */
        m_userInterface->pushButtonDecrementNumberColumns->setEnabled(!(BATTLEMAP_MINIMUMNUMBERROWSANDCOLUMNS == m_battleMap->getNumberColumns()));
    }
}

/*!
 * \brief This function checks the Battle Map grid for validity.
 */
void WizardPageNewBattleMapOriginal::checkBattleMapGrid()
{
    bool validBattleMapGrid = true;

    /* calculate height and width of Battle Map squares */
    quint32 edgeLengthHeigth = m_battleMapImagePixMap.pixmap().height() / m_battleMap->getNumberRows();
    quint32 edgeLengthWidth = m_battleMapImagePixMap.pixmap().width() / m_battleMap->getNumberColumns();

    if (edgeLengthHeigth == edgeLengthWidth)
    {
        if ((edgeLengthHeigth * m_battleMap->getNumberRows()) != static_cast<quint32>(m_battleMapImagePixMap.pixmap().height()))
        {
            /* set background color of lineEditNumberRows to red if number of rows does not match Battle Map image size */
            m_userInterface->lineEditNumberRows->setStyleSheet(QString("#%1 { background-color: red; }").arg(m_userInterface->lineEditNumberRows->objectName()));
            validBattleMapGrid = false;
        }
        else
        {
            /* reset background color of lineEditNumberRows as number of rows matches Battle Map image size */
            m_userInterface->lineEditNumberRows->setStyleSheet("");
        }

        if ((edgeLengthWidth * m_battleMap->getNumberColumns()) != static_cast<quint32>(m_battleMapImagePixMap.pixmap().width()))
        {
            /* set background color of lineEditNumberColumns to red if number of columns does not match Battle Map image size */
            m_userInterface->lineEditNumberColumns->setStyleSheet(QString("#%1 { background-color: red; }").arg(m_userInterface->lineEditNumberColumns->objectName()));
            validBattleMapGrid = false;
        }
        else
        {
            /* reset background color of lineEditNumberColumns as number of columns matches Battle Map image size */
            m_userInterface->lineEditNumberColumns->setStyleSheet("");
        }
    }
    else
    {
        /* set background color of lineEditNumberRows and lineEditNumberColumns to red if aspect ratio of Battle Map squares is invalid */
        m_userInterface->lineEditNumberRows->setStyleSheet(QString("#%1 { background-color: red; }").arg(m_userInterface->lineEditNumberRows->objectName()));
        m_userInterface->lineEditNumberColumns->setStyleSheet(QString("#%1 { background-color: red; }").arg(m_userInterface->lineEditNumberColumns->objectName()));
        validBattleMapGrid = false;
    }

    /* set or reset complete page, depending on validity of Battle Map grid */
    setCompletePage(validBattleMapGrid);
}

/*!
 * \brief This function removes the Battle Map grid.
 */
void WizardPageNewBattleMapOriginal::removeBattleMapGrid()
{
    /* remove all graphics items of m_battleMapLinesToDraw from Battle Map scene */
    for(QGraphicsLineItem * item : m_battleMapLinesToDraw)
    {
        m_battleMapScene->removeItem(item);
        delete item;
    }

    m_battleMapLinesToDraw.clear();
}

/*!
 * \brief This function deletes the Battle Map scene.
 */
void WizardPageNewBattleMapOriginal::deleteBattleMapScene()
{
    /* remove Battle Map grid from Battle Map scene */
    removeBattleMapGrid();

    /* remove all remaining graphics items from Battle Map scene */
    for (QGraphicsItem * item : m_battleMapScene->items())
    {
        m_battleMapScene->removeItem(item);
    }

    delete m_battleMapScene;
}

/*!
 * \brief This function extracts the Battle Map.
 */
void WizardPageNewBattleMapOriginal::extractBattleMap()
{
    /* set wait cursor as the following process may take some time */
    QApplication::setOverrideCursor(Qt::WaitCursor);

    if (m_userInterface->checkBoxDrawBattleMapGrid->isChecked())
    {
        /* draw Battle Map grid on Battle Map image */
        QPixmap temporaryPixmap(m_battleMapImagePixMap.pixmap());
        QPainter *painter = new QPainter(&temporaryPixmap);
        painter->setPen(QPen(BATTLEMAPGRID_COLOR, BATTLEMAPGRID_LINEWIDTH, Qt::SolidLine));
        for (QGraphicsLineItem * item : m_battleMapLinesToDraw)
        {
            painter->drawLine(item->line());
        }
        delete painter;
        m_battleMapImagePixMap.setPixmap(temporaryPixmap);
    }

    quint32 edgeLength = m_battleMapImagePixMap.pixmap().height() / m_battleMap->getNumberRows();

    m_battleMap->initBattleMapSquares();
    for (quint32 rowIdx = 0U; rowIdx < m_battleMap->getNumberRows(); rowIdx++)
    {
        for (quint32 columnIdx = 0U; columnIdx < m_battleMap->getNumberColumns(); columnIdx++)
        {
            /* extract pixmap of Battle Map square from Battle Map image and scale it to configured size */
            QPixmap temporaryPixmap;
            temporaryPixmap = m_battleMapImagePixMap.pixmap().copy(QRect(columnIdx * edgeLength, rowIdx * edgeLength, edgeLength, edgeLength));
            temporaryPixmap = temporaryPixmap.scaled(QSize(BATTLEMAPSQUARE_SIZE, BATTLEMAPSQUARE_SIZE));

            /*  Add pixmaps to Battle Map */
            m_battleMap->setBattleMapSquareOriginalPixmap(rowIdx, columnIdx, temporaryPixmap);
        }
    }

    /* reset arrow cursor as the process which takes some time is completed */
    QApplication::restoreOverrideCursor();
}
