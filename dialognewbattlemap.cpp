/****************************************************************************************************************************************************
 * INCLUDES                                                                                                                                         *
 ****************************************************************************************************************************************************/

#include "dialognewbattlemap.h"
#include "ui_dialognewbattlemap.h"

/****************************************************************************************************************************************************
 * DEFINITION OF PUBLIC FUNCTIONS                                                                                                                   *
 ****************************************************************************************************************************************************/

/*!
 * \brief This function is the constructor of the class DialogNewBattleMap.
 */
DialogNewBattleMap::DialogNewBattleMap(QWidget *parent) :
    QDialog(parent),
    m_userInterface(new Ui::DialogNewBattleMap),
    m_battleMapScene(new BattleMapSceneSquareSelection()),
    m_scaleFactor(1.0),
    m_battleMap(new BattleMap())
{
    /* set up the user interface */
    m_userInterface->setupUi(this);

    /* set background color of graphics view to window color */
    QPalette palette;
    m_userInterface->graphicsViewNewBattleMap->setBackgroundBrush(QBrush(palette.color(QPalette::Window)));

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
    connect(m_userInterface->dialogButtonBox, SIGNAL(accepted()), this, SLOT(acceptedDialogButtonBox()));
    connect(m_userInterface->dialogButtonBox, SIGNAL(rejected()), this, SLOT(rejectedDialogButtonBox()));

    /* handle toggle of radioButtonSourceBattleMap as radioButtonSourceBattleMap is checked by default */
    toggledRadioButtonSourceBattleMap(true);
}

/*!
 * \brief This function is the destructor of the class DialogNewBattleMap.
 */
DialogNewBattleMap::~DialogNewBattleMap()
{
    /* delete objects created in the constructor */
    delete m_userInterface;
    deleteBattleMapScene();
    delete m_battleMap;
}

/*!
 * \brief This function returns the address of the newly created Battle Map object.
 */
BattleMap * DialogNewBattleMap::getBattleMap() const
{
    return m_battleMap;
}

/****************************************************************************************************************************************************
 * DEFINITION OF PROTECTED FUNCTIONS                                                                                                                *
 ****************************************************************************************************************************************************/

/* - */

/****************************************************************************************************************************************************
 * DEFINITION OF PRIVATE SLOT FUNCTIONS                                                                                                             *
 ****************************************************************************************************************************************************/

/*!
 * \brief This function handles a toggle of radioButtonSourceBattleMap.
 */
void DialogNewBattleMap::toggledRadioButtonSourceBattleMap(bool checked)
{
    if (checked)
    {
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
        m_userInterface->dialogButtonBox->button(QDialogButtonBox::Ok)->setEnabled(false);

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
void DialogNewBattleMap::toggledRadioButtonEmptyBattleMap(bool checked)
{
    if (checked)
    {
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
        m_userInterface->dialogButtonBox->button(QDialogButtonBox::Ok)->setEnabled(true);

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
        quint32 maximumNumberRows = static_cast<quint32>(calcScreenHeightInInches(CONFIG_PLAYER_SCREEN_DIAGONAL, CONFIG_PLAYER_SCREEN_RESOLUTION.height(), CONFIG_PLAYER_SCREEN_RESOLUTION.width()));
        quint32 maximumNumberColumns = static_cast<quint32>(calcScreenWidthInInches(CONFIG_PLAYER_SCREEN_DIAGONAL, CONFIG_PLAYER_SCREEN_RESOLUTION.height(), CONFIG_PLAYER_SCREEN_RESOLUTION.width()));
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
void DialogNewBattleMap::editingFinishedLineEditSource()
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
void DialogNewBattleMap::releasedPushButtonSelectSource()
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
void DialogNewBattleMap::editingFinishedLineEditNumberRows()
{
    /* check text string for valid format (decimal number) */
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
    if (BATTLEMAP_MINIMUMNUMBERROWSANDCOLUMNS == m_battleMap->getNumberRows())
    {
        m_userInterface->pushButtonDecrementNumberRows->setEnabled(false);
    }
    else
    {
        m_userInterface->pushButtonDecrementNumberRows->setEnabled(true);
    }

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
        /* check if number of rows and columns are both greater 0 (which affects push button with AcceptRole) and show empty Battle Map image */
        checkNumberRowsAndColumns();
        showEmptyBattleMapImage();
    }
}

/*!
 * \brief This function handles the editing of lineEditNumberColumns.
 */
void DialogNewBattleMap::editingFinishedLineEditNumberColumns()
{
    /* check text string for valid format (decimal number) */
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
    if (BATTLEMAP_MINIMUMNUMBERROWSANDCOLUMNS == m_battleMap->getNumberColumns())
    {
        m_userInterface->pushButtonDecrementNumberColumns->setEnabled(false);
    }
    else
    {
        m_userInterface->pushButtonDecrementNumberColumns->setEnabled(true);
    }

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
        /* check if number of rows and columns are both greater 0 (which affects push button with AcceptRole) and show empty Battle Map image */
        checkNumberRowsAndColumns();
        showEmptyBattleMapImage();
    }
}

/*!
 * \brief This function handles a click on pushButtonDecrementNumberRows.
 */
void DialogNewBattleMap::releasedPushButtonDecrementNumberRows()
{
    /* decrement number of rows */
    m_battleMap->setNumberRows(m_battleMap->getNumberRows() - 1);
    m_userInterface->lineEditNumberRows->setText(QString::number(m_battleMap->getNumberRows()));

    /* enable or disable push button for decrement depending on current number of rows */
    if (BATTLEMAP_MINIMUMNUMBERROWSANDCOLUMNS == m_battleMap->getNumberRows())
    {
        m_userInterface->pushButtonDecrementNumberRows->setEnabled(false);
    }
    else
    {
        m_userInterface->pushButtonDecrementNumberRows->setEnabled(true);
    }

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
        /* check if number of rows and columns are both greater 0 (which affects push button with AcceptRole) and show empty Battle Map image */
        checkNumberRowsAndColumns();
        showEmptyBattleMapImage();
    }
}

/*!
 * \brief This function handles a click on pushButtonIncrementNumberRows.
 */
void DialogNewBattleMap::releasedPushButtonIncrementNumberRows()
{
    /* increment number of rows */
    m_battleMap->setNumberRows(m_battleMap->getNumberRows() + 1);
    m_userInterface->lineEditNumberRows->setText(QString::number(m_battleMap->getNumberRows()));

    /* enable push button for decrement depending on current number of rows */
    if (BATTLEMAP_MINIMUMNUMBERROWSANDCOLUMNS < m_battleMap->getNumberRows())
    {
        m_userInterface->pushButtonDecrementNumberRows->setEnabled(true);
    }

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
        /* check if number of rows and columns are both greater 0 (which affects push button with AcceptRole) and show empty Battle Map image */
        checkNumberRowsAndColumns();
        showEmptyBattleMapImage();
    }
}

/*!
 * \brief This function handles a click on pushButtonDecrementNumberColumns.
 */
void DialogNewBattleMap::releasedPushButtonDecrementNumberColumns()
{
    /* decrement number of columns */
    m_battleMap->setNumberColumns(m_battleMap->getNumberColumns() - 1);
    m_userInterface->lineEditNumberColumns->setText(QString::number(m_battleMap->getNumberColumns()));

    /* enable or disable push button for decrement depending on current number of columns */
    if (BATTLEMAP_MINIMUMNUMBERROWSANDCOLUMNS == m_battleMap->getNumberColumns())
    {
        m_userInterface->pushButtonDecrementNumberColumns->setEnabled(false);
    }
    else
    {
        m_userInterface->pushButtonDecrementNumberColumns->setEnabled(true);
    }

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
        /* check if number of rows and columns are both greater 0 (which affects push button with AcceptRole) and show empty Battle Map image */
        checkNumberRowsAndColumns();
        showEmptyBattleMapImage();
    }
}

/*!
 * \brief This function handles a click on pushButtonIncrementNumberColumns.
 */
void DialogNewBattleMap::releasedPushButtonIncrementNumberColumns()
{
    /* increment number of columns */
    m_battleMap->setNumberColumns(m_battleMap->getNumberColumns() + 1);
    m_userInterface->lineEditNumberColumns->setText(QString::number(m_battleMap->getNumberColumns()));

    /* enable push button for decrement depending on current number of columns */
    if (BATTLEMAP_MINIMUMNUMBERROWSANDCOLUMNS < m_battleMap->getNumberColumns())
    {
        m_userInterface->pushButtonDecrementNumberColumns->setEnabled(true);
    }

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
        /* check if number of rows and columns are both greater 0 (which affects push button with AcceptRole) and show empty Battle Map image */
        checkNumberRowsAndColumns();
        showEmptyBattleMapImage();
    }
}

/*!
 * \brief This function handles the selection of a Battle Map square.
 */
void DialogNewBattleMap::selectedBattleMapSquare()
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

        /* disable push button from DialogButtonBox with AcceptRole as no valid Battle Map square has been selected */
        m_userInterface->dialogButtonBox->button(QDialogButtonBox::Ok)->setEnabled(false);

        /* remove Battle Map grid as no valid Battle Map square has been selected */
        removeBattleMapGrid();
    }
}

/*!
 * \brief This function draws the Battle Map grid.
 */
void DialogNewBattleMap::drawBattleMapGrid(int state)
{
    Q_UNUSED(state);

    /* remove current Battle Map grid from Battle Map scene */
    removeBattleMapGrid();

    /* set pen properties according to state of checkBoxDrawBattleMapGrid */
    QPen pen;
    if (m_userInterface->checkBoxDrawBattleMapGrid->isChecked())
    {
        pen = QPen(CONFIG_BATTLEMAPGRID_COLOR, CONFIG_BATTLEMAPGRID_LINEWIDTH * (1 / m_scaleFactor), Qt::SolidLine);
    }
    else
    {
        pen = QPen(BATTLEMAPGRID_COLOR, BATTLEMAPGRID_LINEWIDTH * (1 / m_scaleFactor), Qt::DotLine);
    }

    quint32 edgeLength;
    if (checkNumberRowsAndColumns())
    {
        /* draw horizontal Battle Map lines and add them to Battle Map scene */
        edgeLength = m_battleMapImagePixMap.pixmap().height() / m_battleMap->getNumberRows();
        for (quint32 rowIdx = 0U; rowIdx < m_battleMap->getNumberRows() + 1; rowIdx++)
        {
            QGraphicsLineItem * battleMapLineToDraw = new QGraphicsLineItem(QLineF(0, rowIdx * edgeLength, m_battleMap->getNumberColumns() * edgeLength, rowIdx * edgeLength));
            battleMapLineToDraw->setPen(pen);
            m_battleMapLinesToDraw.append(battleMapLineToDraw);
            m_battleMapScene->addItem(m_battleMapLinesToDraw.last());
        }

        /* draw vertical Battle Map lines and add them to Battle Map scene */
        edgeLength = m_battleMapImagePixMap.pixmap().width() / m_battleMap->getNumberColumns();
        for (quint32 columnIdx = 0U; columnIdx < m_battleMap->getNumberColumns() + 1; columnIdx++)
        {
            QGraphicsLineItem * battleMapLineToDraw = new QGraphicsLineItem(QLineF(columnIdx * edgeLength, 0, columnIdx * edgeLength, m_battleMap->getNumberRows() * edgeLength));
            battleMapLineToDraw->setPen(pen);
            m_battleMapLinesToDraw.append(battleMapLineToDraw);
            m_battleMapScene->addItem(m_battleMapLinesToDraw.last());
        }
    }
}

/*!
 * \brief This function handles a click on the push button from dialogButtonBox with AcceptRole.
 */
void DialogNewBattleMap::acceptedDialogButtonBox()
{
    /* set wait cursor as the following process may take some time */
    setCursor(Qt::WaitCursor);

    if (m_userInterface->checkBoxDrawBattleMapGrid->isChecked())
    {
        /* draw Battle Map grid on Battle Map image */
        QPixmap temporaryPixmap(m_battleMapImagePixMap.pixmap());
        QPainter *painter = new QPainter(&temporaryPixmap);
        painter->setPen(QPen(CONFIG_BATTLEMAPGRID_COLOR, CONFIG_BATTLEMAPGRID_LINEWIDTH, Qt::SolidLine));
        for (QGraphicsLineItem * item : m_battleMapLinesToDraw)
        {
            painter->drawLine(item->line());
        }
        delete painter;
        m_battleMapImagePixMap.setPixmap(temporaryPixmap);
    }

    quint32 edgeLength = m_battleMapImagePixMap.pixmap().height() / m_battleMap->getNumberRows();

    for (quint32 rowIdx = 0U; rowIdx < m_battleMap->getNumberRows(); rowIdx++)
    {
        for (quint32 columnIdx = 0U; columnIdx < m_battleMap->getNumberColumns(); columnIdx++)
        {
            /* extract pixmap of Battle Map square from Battle Map image and scale it to configured size */
            QPixmap temporaryPixmap;
            temporaryPixmap = m_battleMapImagePixMap.pixmap().copy(QRect(columnIdx * edgeLength, rowIdx * edgeLength, edgeLength, edgeLength));
            temporaryPixmap = temporaryPixmap.scaled(QSize(CONFIG_BATTLEMAPSQUARE_SIZE, CONFIG_BATTLEMAPSQUARE_SIZE));

            /* add Battle Map square pixmap to Battle Map */
            m_battleMap->setBattleMapSquarePixmap(rowIdx, temporaryPixmap);
        }
    }

    emit accepted();
}

/*!
 * \brief This function handles a click on the push button from dialogButtonBox with RejectRole.
 */
void DialogNewBattleMap::rejectedDialogButtonBox()
{
    emit rejected();
}

/*!
 * \brief This function handles a click on the close button.
 */
void DialogNewBattleMap::reject()
{
    /* handle click on close button as click on the push button from dialogButtonBox with RejectRole */
    rejectedDialogButtonBox();
}

/*!
 * \brief This function updates the member variable m_scaleFactor and redraws the Battle Map grid.
 */
void DialogNewBattleMap::changedScaleFactor(qreal scaleFactor)
{
    /* redraw Battle Map grid with new scale factor */
    m_scaleFactor = scaleFactor;
    drawBattleMapGrid();

    /* set new scale factor to Battle Map scene */
    m_battleMapScene->changedScaleFactor(scaleFactor);
}

/****************************************************************************************************************************************************
 * DEFINITION OF PRIVATE FUNCTIONS                                                                                                                  *
 ****************************************************************************************************************************************************/

/*!
 * \brief This function shows the empty Battle Map image.
 */
void DialogNewBattleMap::showEmptyBattleMapImage()
{
    /* reset and reconnect Battle Map scene */
    deleteBattleMapScene();
    m_battleMapScene = new BattleMapSceneSquareSelection();
    m_userInterface->graphicsViewNewBattleMap->setScene(m_battleMapScene);

    /* reset graphics view */
    m_userInterface->graphicsViewNewBattleMap->setFrameShape(QFrame::NoFrame);

    /* load image of empty Battle Map square and scale it to configured size */
    QImage emptyBattleMapSquare(EMPTYBATTLEMAPSQUAREIMAGE_SOURCE);
    emptyBattleMapSquare = emptyBattleMapSquare.scaledToWidth(CONFIG_BATTLEMAPSQUARE_SIZE);

    if (checkNumberRowsAndColumns())
    {
        /* construct empty Battle Map image from number of empty Battle Map squares according to number of rows and columns */
        QPixmap temporaryPixmap(QSize(m_battleMap->getNumberColumns()* CONFIG_BATTLEMAPSQUARE_SIZE, m_battleMap->getNumberRows() * CONFIG_BATTLEMAPSQUARE_SIZE));
        QPainter *painter = new QPainter(&temporaryPixmap);
        for (quint32 rowIdx = 0U; rowIdx < m_battleMap->getNumberRows(); rowIdx++)
        {
            for (quint32 columnIdx = 0U; columnIdx < m_battleMap->getNumberColumns(); columnIdx++)
            {
                QRect targetRect = QRect(columnIdx * CONFIG_BATTLEMAPSQUARE_SIZE, rowIdx * CONFIG_BATTLEMAPSQUARE_SIZE, CONFIG_BATTLEMAPSQUARE_SIZE, CONFIG_BATTLEMAPSQUARE_SIZE);
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
}

/*!
 * \brief This function shows the Battle Map image from the selected source.
 */
void DialogNewBattleMap::showSourceBattleMapImage()
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
        /* add text to Battle Map scene informing user that selected source file is no image file */
        m_sceneText.setPlainText("Selected source file is no image file.");
        m_battleMapScene->addItem(&m_sceneText);

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
void DialogNewBattleMap::correctNumberRows()
{
    if (0 < m_battleMap->getNumberColumns())
    {
        /* correct number of rows considering Battle Map squares aspect ratio */
        quint32 edgeLength = m_battleMapImagePixMap.pixmap().size().width() / m_battleMap->getNumberColumns();
        m_battleMap->setNumberRows(m_battleMapImagePixMap.pixmap().height() / edgeLength);
        m_userInterface->lineEditNumberRows->setText(QString::number(m_battleMap->getNumberRows()));
    }

    /* enable or disable push button for decrement depending on current number of rows */
    if (0U == m_battleMap->getNumberRows())
    {
        m_userInterface->pushButtonDecrementNumberRows->setEnabled(false);
    }
    else
    {
        m_userInterface->pushButtonDecrementNumberRows->setEnabled(true);
    }
}

/*!
 * \brief This function corrects the number of columns considering the Battle Map squares aspect ratio.
 */
void DialogNewBattleMap::correctNumberColumns()
{
    if (0 < m_battleMap->getNumberRows())
    {
        /* correct number of columns considering Battle Map squares aspect ratio */
        quint32 edgeLength = m_battleMapImagePixMap.pixmap().height() / m_battleMap->getNumberRows();
        m_battleMap->setNumberColumns(m_battleMapImagePixMap.pixmap().width() / edgeLength);
        m_userInterface->lineEditNumberColumns->setText(QString::number(m_battleMap->getNumberColumns()));
    }

    /* enable or disable push button for decrement depending on current number of columns */
    if (0U == m_battleMap->getNumberColumns())
    {
        m_userInterface->pushButtonDecrementNumberColumns->setEnabled(false);
    }
    else
    {
        m_userInterface->pushButtonDecrementNumberColumns->setEnabled(true);
    }
}

/*!
 * \brief This function checks the Battle Map grid for validity.
 */
void DialogNewBattleMap::checkBattleMapGrid()
{
    bool validBattleMapGrid = true;

    if (checkNumberRowsAndColumns())
    {
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
    }

    /* Enable or disable push button with AcceptRole */
    m_userInterface->dialogButtonBox->button(QDialogButtonBox::Ok)->setEnabled(validBattleMapGrid);
}

/*!
 * \brief This function checks the numbers of rows and columns for validity.
 */
bool DialogNewBattleMap::checkNumberRowsAndColumns()
{
    /* check numbers of rows and columns for validity */
    bool validNumberRowsAndColumns = ((0U < m_battleMap->getNumberRows()) && (0U < m_battleMap->getNumberColumns()));

    /* Enable or disable push button with AcceptRole */
    m_userInterface->dialogButtonBox->button(QDialogButtonBox::Ok)->setEnabled(validNumberRowsAndColumns);

    return validNumberRowsAndColumns;
}

/*!
 * \brief This function removes the Battle Map grid.
 */
void DialogNewBattleMap::removeBattleMapGrid()
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
void DialogNewBattleMap::deleteBattleMapScene()
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
