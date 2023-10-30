/****************************************************************************************************************************************************
 * INCLUDES                                                                                                                                         *
 ****************************************************************************************************************************************************/

#include "dialog_newbattlemap.h"
#include "ui_dialog_newbattlemap.h"

/****************************************************************************************************************************************************
 * DEFINITION OF PUBLIC FUNCTIONS                                                                                                                   *
 ****************************************************************************************************************************************************/

/*!
 * \brief This function is the constructor of the class Dialog_NewBattleMap.
 */
Dialog_NewBattleMap::Dialog_NewBattleMap(QWidget *parent) :
    QDialog(parent),
    pUserInterface(new Ui::Dialog_NewBattleMap),
    pBattleMapScene(new BattleMapSceneSquareSelection()),
    m_scaleFactor(1.0),
    pBattleMap(new BattleMap())
{
    pUserInterface->setupUi(this);

    QPalette palette;
    pUserInterface->GraphicsView_NewBattleMap->setBackgroundBrush(QBrush(palette.color(QPalette::Window)));

    /* connect signals and slots of the user interface widgets */
    connect(pUserInterface->RadioButton_SourceBattleMap, SIGNAL(toggled(bool)), this, SLOT(toggled_RadioButton_SourceBattleMap(bool)));
    connect(pUserInterface->RadioButton_EmptyBattleMap, SIGNAL(toggled(bool)), this, SLOT(toggled_RadioButton_EmptyBattleMap(bool)));
    connect(pUserInterface->LineEdit_Source, SIGNAL(editingFinished()), this, SLOT(editingFinished_LineEdit_Source()));
    connect(pUserInterface->PushButton_SelectSource, SIGNAL(released()), this, SLOT(released_PushButton_SelectSource()));
    connect(pUserInterface->LineEdit_NumberRows, SIGNAL(editingFinished()), this, SLOT(editingFinished_LineEdit_NumberRows()));
    connect(pUserInterface->LineEdit_NumberColumns, SIGNAL(editingFinished()), this, SLOT(editingFinished_LineEdit_NumberColumns()));
    connect(pUserInterface->PushButton_DecrementNumberRows, SIGNAL(released()), this, SLOT(released_PushButton_DecrementNumberRows()));
    connect(pUserInterface->PushButton_IncrementNumberRows, SIGNAL(released()), this, SLOT(released_PushButton_IncrementNumberRows()));
    connect(pUserInterface->PushButton_DecrementNumberColumns, SIGNAL(released()), this, SLOT(released_PushButton_DecrementNumberColumns()));
    connect(pUserInterface->PushButton_IncrementNumberColumns, SIGNAL(released()), this, SLOT(released_PushButton_IncrementNumberColumns()));
    connect(pUserInterface->CheckBox_DrawBattleMapGrid, SIGNAL(stateChanged(int)), this, SLOT(stateChanged_CheckBox_DrawBattleMapGrid(int)));
    connect(pUserInterface->GraphicsView_NewBattleMap, SIGNAL(changed_ScaleFactor(qreal)), this, SLOT(changed_ScaleFactor(qreal)));
    connect(pUserInterface->DialogButtonBox, SIGNAL(accepted()), this, SLOT(accepted_DialogButtonBox()));
    connect(pUserInterface->DialogButtonBox, SIGNAL(rejected()), this, SLOT(rejected_DialogButtonBox()));

    pUserInterface->RadioButton_SourceBattleMap->setChecked(true);
    emit pUserInterface->RadioButton_SourceBattleMap->toggled(true);
}

/*!
 * \brief This function is the destructor of the class Dialog_NewBattleMap.
 */
Dialog_NewBattleMap::~Dialog_NewBattleMap()
{
    deleteBattleMapScene();
    delete pUserInterface;
    delete pBattleMap;
}

/*!
 * \brief This function returns the address of the newly created Battle Map object.
 */
BattleMap * Dialog_NewBattleMap::getBattleMap() const
{
    return pBattleMap;
}

/****************************************************************************************************************************************************
 * DEFINITION OF PROTECTED FUNCTIONS                                                                                                                *
 ****************************************************************************************************************************************************/

/* - */

/****************************************************************************************************************************************************
 * DEFINITION OF PRIVATE SLOT FUNCTIONS                                                                                                             *
 ****************************************************************************************************************************************************/

/*!
 * \brief This function handles a toggle of RadioButton_SourceBattleMap.
 */
void Dialog_NewBattleMap::toggled_RadioButton_SourceBattleMap(bool checked)
{
    if (checked)
    {
        /* enable and disable widgets according to their functional role for the Battle Map image source selection */
        pUserInterface->LineEdit_Source->setEnabled(true);
        pUserInterface->PushButton_SelectSource->setEnabled(true);
        pUserInterface->CheckBox_DrawBattleMapGrid->setEnabled(true);
        pUserInterface->LineEdit_NumberRows->setEnabled(false);
        pUserInterface->LineEdit_NumberRows->setStyleSheet("");
        pUserInterface->LineEdit_NumberColumns->setEnabled(false);
        pUserInterface->LineEdit_NumberColumns->setStyleSheet("");
        pUserInterface->PushButton_DecrementNumberRows->setEnabled(false);
        pUserInterface->PushButton_IncrementNumberRows->setEnabled(false);
        pUserInterface->PushButton_DecrementNumberColumns->setEnabled(false);
        pUserInterface->PushButton_IncrementNumberColumns->setEnabled(false);
        pUserInterface->DialogButtonBox->button(QDialogButtonBox::Ok)->setEnabled(false);

        /* reset widgets according to their functional role for the Battle Map image source selection */
        pUserInterface->LineEdit_Source->setText("");
        pBattleMap->setNumberRows(0U);
        pBattleMap->setNumberColumns(0U);
        pUserInterface->LineEdit_NumberRows->setText(QString::number(pBattleMap->getNumberRows()));
        pUserInterface->LineEdit_NumberColumns->setText(QString::number(pBattleMap->getNumberRows()));
        pUserInterface->CheckBox_DrawBattleMapGrid->setCheckState(Qt::Unchecked);
        pUserInterface->GraphicsView_NewBattleMap->setInteractive(false);
        pUserInterface->GraphicsView_NewBattleMap->viewport()->setCursor(Qt::ArrowCursor);
        pUserInterface->GraphicsView_NewBattleMap->setToolTip("");
        pUserInterface->GraphicsView_NewBattleMap->setFrameShape(QFrame::Box);

        /* reset and reconnect Battle Map scene */
        deleteBattleMapScene();
        pBattleMapScene = new BattleMapSceneSquareSelection();
        connect(pBattleMapScene, SIGNAL(selected_BattleMapSquare()), this, SLOT(selected_BattleMapSquare()));
        pUserInterface->GraphicsView_NewBattleMap->setScene(pBattleMapScene);

        m_sceneText.setPlainText("Select source");
        pBattleMapScene->addItem(&m_sceneText);
    }
}

/*!
 * \brief This function handles a toggle of RadioButton_EmptyBattleMap.
 */
void Dialog_NewBattleMap::toggled_RadioButton_EmptyBattleMap(bool checked)
{
    if (checked)
    {
        /* enable and disable widgets according to their functional role for the creation of an empty Battle Map */
        pUserInterface->LineEdit_Source->setEnabled(false);
        pUserInterface->PushButton_SelectSource->setEnabled(false);
        pUserInterface->CheckBox_DrawBattleMapGrid->setEnabled(false);
        pUserInterface->LineEdit_NumberRows->setEnabled(true);
        pUserInterface->LineEdit_NumberRows->setStyleSheet("");
        pUserInterface->LineEdit_NumberColumns->setEnabled(true);
        pUserInterface->LineEdit_NumberColumns->setStyleSheet("");
        pUserInterface->PushButton_DecrementNumberRows->setEnabled(true);
        pUserInterface->PushButton_IncrementNumberRows->setEnabled(true);
        pUserInterface->PushButton_DecrementNumberColumns->setEnabled(true);
        pUserInterface->PushButton_IncrementNumberColumns->setEnabled(true);
        pUserInterface->DialogButtonBox->button(QDialogButtonBox::Ok)->setEnabled(true);

        /* reset widgets according to their functional role for the creation of an empty Battle Map */
        pUserInterface->LineEdit_Source->setText("");
        pUserInterface->CheckBox_DrawBattleMapGrid->setCheckState(Qt::Checked);
        pUserInterface->GraphicsView_NewBattleMap->setInteractive(false);
        pUserInterface->GraphicsView_NewBattleMap->viewport()->setCursor(Qt::ArrowCursor);
        pUserInterface->GraphicsView_NewBattleMap->setToolTip("");
        pUserInterface->GraphicsView_NewBattleMap->setFrameShape(QFrame::Box);

        /* calculate maximum number of rows and columns displayable on the player screen (each square is one inch high and one inch wide) */
        quint32 maximumNumberRows = static_cast<quint32>(calcScreenHeightInInches(CONFIG_PLAYER_SCREEN_DIAGONAL, CONFIG_PLAYER_SCREEN_RESOLUTION.height(), CONFIG_PLAYER_SCREEN_RESOLUTION.width()));
        quint32 maximumNumberColumns = static_cast<quint32>(calcScreenWidthInInches(CONFIG_PLAYER_SCREEN_DIAGONAL, CONFIG_PLAYER_SCREEN_RESOLUTION.height(), CONFIG_PLAYER_SCREEN_RESOLUTION.width()));
        pBattleMap->setNumberRows(maximumNumberRows);
        pBattleMap->setNumberColumns(maximumNumberColumns);
        pUserInterface->LineEdit_NumberRows->setText(QString::number(pBattleMap->getNumberRows()));
        pUserInterface->LineEdit_NumberColumns->setText(QString::number(pBattleMap->getNumberColumns()));

        showEmptyBattleMapImage();
    }
}

/*!
 * \brief This function handles the editing of LineEdit_Source.
 */
void Dialog_NewBattleMap::editingFinished_LineEdit_Source()
{
    if (!pUserInterface->LineEdit_Source->text().isEmpty())
    {
        /* reset number of Battle Map rows and columns */
        pBattleMap->setNumberRows(0U);
        pBattleMap->setNumberColumns(0U);
        pUserInterface->LineEdit_NumberRows->setText(QString::number(pBattleMap->getNumberRows()));
        pUserInterface->LineEdit_NumberColumns->setText(QString::number(pBattleMap->getNumberRows()));

        showSourceBattleMapImage();
    }
}

/*!
 * \brief This function handles a click on PushButton_SelectSource.
 */
void Dialog_NewBattleMap::released_PushButton_SelectSource()
{
    QString selectedSource = QFileDialog::getOpenFileName(this, tr("Select source"), ".", tr("Image Files (*.png *.jpg)"));
    pUserInterface->LineEdit_Source->setText(selectedSource);

    editingFinished_LineEdit_Source();
}

/*!
 * \brief This function handles the editing of LineEdit_NumberRows.
 */
void Dialog_NewBattleMap::editingFinished_LineEdit_NumberRows()
{
    bool validNumber;
    qint32 inputValue = pUserInterface->LineEdit_NumberRows->text().toInt(&validNumber, 10);
    QMessageBox msgBox(this);

    if (!validNumber || 0 > inputValue)
    {
        msgBox.setWindowTitle("Invalid input");
        msgBox.setText("Input '" + pUserInterface->LineEdit_NumberRows->text() + "' is invalid.");
        msgBox.setIcon(QMessageBox::Warning);
        msgBox.exec();

        pUserInterface->LineEdit_NumberRows->setText(QString::number(pBattleMap->getNumberRows()));;
    }
    else
    {
        pBattleMap->setNumberRows(inputValue);
    }

    if (0U == pBattleMap->getNumberRows())
    {
        pUserInterface->PushButton_DecrementNumberRows->setEnabled(false);
    }
    else
    {
        pUserInterface->PushButton_DecrementNumberRows->setEnabled(true);
    }

    if (pUserInterface->RadioButton_SourceBattleMap->isChecked())
    {
        correctNumberColumns();
        checkBattleMapGrid();
        drawBattleMapGrid();
    }
    else
    {
        checkBattleMapGrid();
        showEmptyBattleMapImage();
    }
}

/*!
 * \brief This function handles the editing of LineEdit_NumberColumns.
 */
void Dialog_NewBattleMap::editingFinished_LineEdit_NumberColumns()
{
    bool validNumber;
    qint32 inputValue = pUserInterface->LineEdit_NumberColumns->text().toInt(&validNumber, 10);
    QMessageBox msgBox(this);

    if (!validNumber || 0 > inputValue)
    {
        msgBox.setWindowTitle("Invalid input");
        msgBox.setText("Input '" + pUserInterface->LineEdit_NumberColumns->text() + "' is invalid.");
        msgBox.setIcon(QMessageBox::Warning);
        msgBox.exec();

        pUserInterface->LineEdit_NumberColumns->setText(QString::number(pBattleMap->getNumberColumns()));;
    }
    else
    {
        pBattleMap->setNumberColumns(inputValue);
    }

    if (0U == pBattleMap->getNumberColumns())
    {
        pUserInterface->PushButton_DecrementNumberColumns->setEnabled(false);
    }
    else
    {
        pUserInterface->PushButton_DecrementNumberColumns->setEnabled(true);
    }

    if (pUserInterface->RadioButton_SourceBattleMap->isChecked())
    {
        correctNumberRows();
        checkBattleMapGrid();
        drawBattleMapGrid();
    }
    else
    {
        checkBattleMapGrid();
        showEmptyBattleMapImage();
    }
}

/*!
 * \brief This function handles a click on PushButton_DecrementNumberRows.
 */
void Dialog_NewBattleMap::released_PushButton_DecrementNumberRows()
{
    pBattleMap->setNumberRows(pBattleMap->getNumberRows() - 1);
    pUserInterface->LineEdit_NumberRows->setText(QString::number(pBattleMap->getNumberRows()));

    if (0U == pBattleMap->getNumberRows())
    {
        pUserInterface->PushButton_DecrementNumberRows->setEnabled(false);
    }
    else
    {
        pUserInterface->PushButton_DecrementNumberRows->setEnabled(true);
    }

    if (pUserInterface->RadioButton_SourceBattleMap->isChecked())
    {
        correctNumberColumns();
        checkBattleMapGrid();
        drawBattleMapGrid();
    }
    else
    {
        checkBattleMapGrid();
        showEmptyBattleMapImage();
    }
}

/*!
 * \brief This function handles a click on PushButton_IncrementNumberRows.
 */
void Dialog_NewBattleMap::released_PushButton_IncrementNumberRows()
{
    pBattleMap->setNumberRows(pBattleMap->getNumberRows() + 1);
    pUserInterface->LineEdit_NumberRows->setText(QString::number(pBattleMap->getNumberRows()));

    if (pUserInterface->RadioButton_SourceBattleMap->isChecked())
    {
        correctNumberColumns();
        checkBattleMapGrid();
        drawBattleMapGrid();
    }
    else
    {
        checkBattleMapGrid();
        showEmptyBattleMapImage();
    }
}

/*!
 * \brief This function handles a click on PushButton_DecrementNumberColumns.
 */
void Dialog_NewBattleMap::released_PushButton_DecrementNumberColumns()
{
    pBattleMap->setNumberColumns(pBattleMap->getNumberColumns() - 1);
    pUserInterface->LineEdit_NumberColumns->setText(QString::number(pBattleMap->getNumberColumns()));

    if (0U == pBattleMap->getNumberColumns())
    {
        pUserInterface->PushButton_DecrementNumberColumns->setEnabled(false);
    }
    else
    {
        pUserInterface->PushButton_DecrementNumberColumns->setEnabled(true);
    }

    if (pUserInterface->RadioButton_SourceBattleMap->isChecked())
    {
        correctNumberRows();
        checkBattleMapGrid();
        drawBattleMapGrid();
    }
    else
    {
        checkBattleMapGrid();
        showEmptyBattleMapImage();
    }
}

/*!
 * \brief This function handles a click on PushButton_IncrementNumberColumns.
 */
void Dialog_NewBattleMap::released_PushButton_IncrementNumberColumns()
{
    pBattleMap->setNumberColumns(pBattleMap->getNumberColumns() + 1);
    pUserInterface->LineEdit_NumberColumns->setText(QString::number(pBattleMap->getNumberColumns()));

    if (pUserInterface->RadioButton_SourceBattleMap->isChecked())
    {
        correctNumberRows();
        checkBattleMapGrid();
        drawBattleMapGrid();
    }
    else
    {
        checkBattleMapGrid();
        showEmptyBattleMapImage();
    }
}

/*!
 * \brief This function handles the selection of a Battle Map square.
 */
void Dialog_NewBattleMap::selected_BattleMapSquare()
{
    QMessageBox msgBox(this);

    QPointF edgeLengths =  pBattleMapScene->getScenePosRelease() - pBattleMapScene->getScenePosPress();
    quint32 averageEdgeLength = static_cast<quint32>((abs(edgeLengths.rx()) + abs(edgeLengths.ry())) / 2U);
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
                averageEdgeLengthIncrement++;
                counterIncrement++;
            }

        } while (0U != residual);
        do
        {
            residual = (m_battleMapImagePixMap.pixmap().height() % averageEdgeLengthDecrement);

            if (0U != residual)
            {
                averageEdgeLengthDecrement--;
                counterDecrement++;
            }

        } while (0U != residual);


        /* edge length that results from the optimization with fewer iterations is used */
        if (counterIncrement < counterDecrement)
        {
            averageEdgeLength = averageEdgeLengthIncrement;
        }
        else
        {
            averageEdgeLength = averageEdgeLengthDecrement;
        }

        pBattleMap->setNumberRows(m_battleMapImagePixMap.pixmap().height() / averageEdgeLength);
        pBattleMap->setNumberColumns(m_battleMapImagePixMap.pixmap().width() / averageEdgeLength);
        pUserInterface->LineEdit_NumberRows->setText(QString::number(pBattleMap->getNumberRows()));
        pUserInterface->LineEdit_NumberColumns->setText(QString::number(pBattleMap->getNumberColumns()));

        /* enable widgets for editing of numbers of rows and columns */
        pUserInterface->LineEdit_NumberRows->setEnabled(true);
        pUserInterface->LineEdit_NumberColumns->setEnabled(true);
        pUserInterface->PushButton_DecrementNumberRows->setEnabled(true);
        pUserInterface->PushButton_IncrementNumberRows->setEnabled(true);
        pUserInterface->PushButton_DecrementNumberColumns->setEnabled(true);
        pUserInterface->PushButton_IncrementNumberColumns->setEnabled(true);

        /* enable push button from DialogButtonBox with AcceptRole */
        pUserInterface->DialogButtonBox->button(QDialogButtonBox::Ok)->setEnabled(true);

        checkBattleMapGrid();
        drawBattleMapGrid();

        msgBox.setWindowTitle("Check Battle Map grid");
        msgBox.setText("Please check the Battle Map grid and readjust the number of rows and columns in case of mismatch.");
        msgBox.setIcon(QMessageBox::Question);
        msgBox.exec();
    }
    else
    {
        pBattleMap->setNumberRows(0U);
        pBattleMap->setNumberColumns(0U);
        pUserInterface->LineEdit_NumberRows->setText(QString::number(pBattleMap->getNumberRows()));
        pUserInterface->LineEdit_NumberRows->setStyleSheet("");
        pUserInterface->LineEdit_NumberColumns->setText(QString::number(pBattleMap->getNumberColumns()));
        pUserInterface->LineEdit_NumberColumns->setStyleSheet("");

        /* disable push button from DialogButtonBox with AcceptRole */
        pUserInterface->DialogButtonBox->button(QDialogButtonBox::Ok)->setEnabled(false);

        removeBattleMapGrid();
    }
}

/*!
 * \brief This function handles a state change of CheckBox_DrawBattleMapGrid.
 */
void Dialog_NewBattleMap::stateChanged_CheckBox_DrawBattleMapGrid(int state)
{
    Q_UNUSED(state);

    drawBattleMapGrid();
}

/*!
 * \brief This function handles a click on the push button from DialogButtonBox with AcceptRole.
 */
void Dialog_NewBattleMap::accepted_DialogButtonBox()
{
    setCursor(Qt::WaitCursor);

    /* draw the selected Battle Map grid on the Battle Map image */
    if (pUserInterface->CheckBox_DrawBattleMapGrid->isChecked())
    {
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

    quint32 edgeLength = m_battleMapImagePixMap.pixmap().height() / pBattleMap->getNumberRows();

    for (quint32 rowIdx = 0U; rowIdx < pBattleMap->getNumberRows(); rowIdx++)
    {
        for (quint32 columnIdx = 0U; columnIdx < pBattleMap->getNumberColumns(); columnIdx++)
        {
            /* extract pixmap of Battle Map square and scale it to configured size */
            QPixmap temporaryPixmap;
            temporaryPixmap = m_battleMapImagePixMap.pixmap().copy(QRect(columnIdx * edgeLength, rowIdx * edgeLength, edgeLength, edgeLength));
            temporaryPixmap = temporaryPixmap.scaled(QSize(CONFIG_BATTLEMAPSQUARE_SIZE, CONFIG_BATTLEMAPSQUARE_SIZE));

            pBattleMap->setBattleMapSquarePixmap(rowIdx, temporaryPixmap);
        }
    }

    emit accepted();
}

/*!
 * \brief This function handles a click on the push button from DialogButtonBox with RejectRole.
 */
void Dialog_NewBattleMap::rejected_DialogButtonBox()
{
    emit rejected();
}

/*!
 * \brief This function updates the member variable m_scaleFactor and redraws the Battle Map grid.
 */
void Dialog_NewBattleMap::changed_ScaleFactor(qreal scaleFactor)
{
    m_scaleFactor = scaleFactor;

    drawBattleMapGrid();

    pBattleMapScene->changed_ScaleFactor(scaleFactor);
}

/****************************************************************************************************************************************************
 * DEFINITION OF PRIVATE FUNCTIONS                                                                                                                  *
 ****************************************************************************************************************************************************/

/*!
 * \brief This function shows the empty Battle Map image.
 */
void Dialog_NewBattleMap::showEmptyBattleMapImage()
{
    QMessageBox msgBox(this);

    /* reset and reconnect Battle Map scene */
    deleteBattleMapScene();
    pBattleMapScene = new BattleMapSceneSquareSelection();
    pUserInterface->GraphicsView_NewBattleMap->setScene(pBattleMapScene);
    pUserInterface->GraphicsView_NewBattleMap->setFrameShape(QFrame::NoFrame);

    QImage emptyBattleMapSquare(EMPTYBATTLEMAPSQUAREIMAGE_SOURCE);

    if (emptyBattleMapSquare.isNull())
    {
        m_sceneText.setPlainText("Empty Battle Map square is no image file.");
        pBattleMapScene->addItem(&m_sceneText);

        msgBox.setWindowTitle("Invalid file");
        msgBox.setText("Empty Battle Map square is no image file.");
        msgBox.setIcon(QMessageBox::Warning);
        msgBox.exec();
    }
    else if (emptyBattleMapSquare.width() != emptyBattleMapSquare.height())
    {
        m_sceneText.setPlainText("Empty Battle Map square has no square format.");
        pBattleMapScene->addItem(&m_sceneText);

        msgBox.setWindowTitle("Invalid file");
        msgBox.setText("Empty Battle Map square has no square format.");
        msgBox.setIcon(QMessageBox::Warning);
        msgBox.exec();
    }
    else
    {
        if ((0U < pBattleMap->getNumberRows()) && (0U < pBattleMap->getNumberColumns()))
        {
            emptyBattleMapSquare = emptyBattleMapSquare.scaledToWidth(CONFIG_BATTLEMAPSQUARE_SIZE);

            /* construct the empty Battle Map image from a number of empty Battle Map squares according to the number of rows and columns */
            QPixmap temporaryPixmap(QSize(pBattleMap->getNumberColumns()* CONFIG_BATTLEMAPSQUARE_SIZE, pBattleMap->getNumberRows() * CONFIG_BATTLEMAPSQUARE_SIZE));
            QPainter *painter = new QPainter(&temporaryPixmap);
            for (quint32 rowIdx = 0U; rowIdx < pBattleMap->getNumberRows(); rowIdx++)
            {
                for (quint32 columnIdx = 0U; columnIdx < pBattleMap->getNumberColumns(); columnIdx++)
                {
                    QRect targetRect = QRect(columnIdx * CONFIG_BATTLEMAPSQUARE_SIZE, rowIdx * CONFIG_BATTLEMAPSQUARE_SIZE, CONFIG_BATTLEMAPSQUARE_SIZE, CONFIG_BATTLEMAPSQUARE_SIZE);
                    QRect sourceRect = emptyBattleMapSquare.rect();
                    painter->drawPixmap(targetRect, QPixmap::fromImage(emptyBattleMapSquare), sourceRect);
                }
            }
            delete painter;

            m_battleMapImagePixMap.setPixmap(temporaryPixmap);

            pBattleMapScene->addItem(&m_battleMapImagePixMap);
            pBattleMapScene->setSceneRect(0, 0, m_battleMapImagePixMap.pixmap().width(), m_battleMapImagePixMap.pixmap().height());

            drawBattleMapGrid();

            pUserInterface->GraphicsView_NewBattleMap->setEventProcessingEnabled(true);
        }
    }
}

/*!
 * \brief This function shows the Battle Map image from the selected source.
 */
void Dialog_NewBattleMap::showSourceBattleMapImage()
{
    QMessageBox msgBox(this);

    /* reset and reconnect Battle Map scene */
    deleteBattleMapScene();
    pBattleMapScene = new BattleMapSceneSquareSelection();
    connect(pBattleMapScene, SIGNAL(selected_BattleMapSquare()), this, SLOT(selected_BattleMapSquare()));
    pUserInterface->GraphicsView_NewBattleMap->setScene(pBattleMapScene);
    pUserInterface->GraphicsView_NewBattleMap->setFrameShape(QFrame::NoFrame);

    QImage battleMapImage(pUserInterface->LineEdit_Source->text());

    if (battleMapImage.isNull())
    {
        m_sceneText.setPlainText("Selected source file is no image file.");
        pBattleMapScene->addItem(&m_sceneText);

        msgBox.setWindowTitle("Invalid file");
        msgBox.setText("Selected source file is no image file.");
        msgBox.setIcon(QMessageBox::Warning);
        msgBox.exec();
    }
    else
    {
        pUserInterface->GraphicsView_NewBattleMap->setInteractive(true);
        pUserInterface->GraphicsView_NewBattleMap->setEventProcessingEnabled(true);
        pUserInterface->GraphicsView_NewBattleMap->viewport()->setCursor(Qt::CrossCursor);
        pUserInterface->GraphicsView_NewBattleMap->setToolTip("Select Battle Map square");

        m_battleMapImagePixMap.setPixmap(QPixmap::fromImage(battleMapImage));
        pBattleMapScene->addItem(&m_battleMapImagePixMap);
        pBattleMapScene->setSceneRect(0, 0, m_battleMapImagePixMap.pixmap().width(), m_battleMapImagePixMap.pixmap().height());

        msgBox.setWindowTitle("Select Battle Map square");
        msgBox.setText("Please select a Battle Map square in order to determine the number of rows and columns of the Battle Map.");
        msgBox.setIcon(QMessageBox::Question);
        msgBox.exec();
    }
}

/*!
 * \brief This function corrects the number of rows considering the Battle Map squares aspect ratio.
 */
void Dialog_NewBattleMap::correctNumberRows()
{
    if (0 < pBattleMap->getNumberColumns())
    {
        quint32 edgeLength = m_battleMapImagePixMap.pixmap().size().width() / pBattleMap->getNumberColumns();
        pBattleMap->setNumberRows(m_battleMapImagePixMap.pixmap().height() / edgeLength);
        pUserInterface->LineEdit_NumberRows->setText(QString::number(pBattleMap->getNumberRows()));
    }

    if (0U == pBattleMap->getNumberRows())
    {
        pUserInterface->PushButton_DecrementNumberRows->setEnabled(false);
    }
    else
    {
        pUserInterface->PushButton_DecrementNumberRows->setEnabled(true);
    }
}

/*!
 * \brief This function corrects the number of columns considering the Battle Map squares aspect ratio.
 */
void Dialog_NewBattleMap::correctNumberColumns()
{
    if (0 < pBattleMap->getNumberRows())
    {
        quint32 edgeLength = m_battleMapImagePixMap.pixmap().height() / pBattleMap->getNumberRows();
        pBattleMap->setNumberColumns(m_battleMapImagePixMap.pixmap().width() / edgeLength);
        pUserInterface->LineEdit_NumberColumns->setText(QString::number(pBattleMap->getNumberColumns()));
    }

    if (0U == pBattleMap->getNumberColumns())
    {
        pUserInterface->PushButton_DecrementNumberColumns->setEnabled(false);
    }
    else
    {
        pUserInterface->PushButton_DecrementNumberColumns->setEnabled(true);
    }
}

/*!
 * \brief This function checks the Battle Map grid for validity.
 */
void Dialog_NewBattleMap::checkBattleMapGrid()
{
    bool validBattleMapGrid = true;

    if ((0U < pBattleMap->getNumberRows()) && (0U < pBattleMap->getNumberColumns()))
    {
        if (pUserInterface->RadioButton_SourceBattleMap->isChecked())
        {
            quint32 edgeLengthHeigth = m_battleMapImagePixMap.pixmap().height() / pBattleMap->getNumberRows();
            quint32 edgeLengthWidth = m_battleMapImagePixMap.pixmap().width() / pBattleMap->getNumberColumns();

            if (edgeLengthHeigth == edgeLengthWidth)
            {
                /* set background color of LineEdit_NumberRows to red if number of rows does not match the Battle Map image size */
                if ((edgeLengthHeigth * pBattleMap->getNumberRows()) != static_cast<quint32>(m_battleMapImagePixMap.pixmap().height()))
                {
                    pUserInterface->LineEdit_NumberRows->setStyleSheet(QString("#%1 { background-color: red; }").arg(pUserInterface->LineEdit_NumberRows->objectName()));
                    validBattleMapGrid = false;
                }
                else
                {
                    pUserInterface->LineEdit_NumberRows->setStyleSheet("");
                }

                /* set background color of LineEdit_NumberColumns to red if number of columns does not match the Battle Map image size */
                if ((edgeLengthWidth * pBattleMap->getNumberColumns()) != static_cast<quint32>(m_battleMapImagePixMap.pixmap().width()))
                {
                    pUserInterface->LineEdit_NumberColumns->setStyleSheet(QString("#%1 { background-color: red; }").arg(pUserInterface->LineEdit_NumberColumns->objectName()));
                    validBattleMapGrid = false;
                }
                else
                {
                    pUserInterface->LineEdit_NumberColumns->setStyleSheet("");
                }
            }
            else
            {
                pUserInterface->LineEdit_NumberRows->setStyleSheet(QString("#%1 { background-color: red; }").arg(pUserInterface->LineEdit_NumberRows->objectName()));
                pUserInterface->LineEdit_NumberColumns->setStyleSheet(QString("#%1 { background-color: red; }").arg(pUserInterface->LineEdit_NumberColumns->objectName()));
                validBattleMapGrid = false;
            }
        }
    }
    else
    {
        validBattleMapGrid = false;
    }

    /* Enable or disable push button with AcceptRole */
    pUserInterface->DialogButtonBox->button(QDialogButtonBox::Ok)->setEnabled(validBattleMapGrid);
}

/*!
 * \brief This function draws the Battle Map grid.
 */
void Dialog_NewBattleMap::drawBattleMapGrid()
{
    QPen pen;
    quint32 edgeLength;

    removeBattleMapGrid();

    if (pUserInterface->CheckBox_DrawBattleMapGrid->isChecked())
    {
        pen = QPen(CONFIG_BATTLEMAPGRID_COLOR, CONFIG_BATTLEMAPGRID_LINEWIDTH * (1 / m_scaleFactor), Qt::SolidLine);
    }
    else
    {
        pen = QPen(BATTLEMAPGRID_COLOR, BATTLEMAPGRID_LINEWIDTH * (1 / m_scaleFactor), Qt::DotLine);
    }

    if ((0U < pBattleMap->getNumberRows()) && (0U < pBattleMap->getNumberColumns()))
    {
        edgeLength = m_battleMapImagePixMap.pixmap().height() / pBattleMap->getNumberRows();
        for (quint32 rowIdx = 0U; rowIdx < pBattleMap->getNumberRows() + 1; rowIdx++)
        {
            QGraphicsLineItem * battleMapLineToDraw = new QGraphicsLineItem(QLineF(0, rowIdx * edgeLength, pBattleMap->getNumberColumns() * edgeLength, rowIdx * edgeLength));
            battleMapLineToDraw->setPen(pen);
            m_battleMapLinesToDraw.append(battleMapLineToDraw);
            pBattleMapScene->addItem(m_battleMapLinesToDraw.last());
        }
        edgeLength = m_battleMapImagePixMap.pixmap().width() / pBattleMap->getNumberColumns();
        for (quint32 columnIdx = 0U; columnIdx < pBattleMap->getNumberColumns() + 1; columnIdx++)
        {
            QGraphicsLineItem * battleMapLineToDraw = new QGraphicsLineItem(QLineF(columnIdx * edgeLength, 0, columnIdx * edgeLength, pBattleMap->getNumberRows() * edgeLength));
            battleMapLineToDraw->setPen(pen);
            m_battleMapLinesToDraw.append(battleMapLineToDraw);
            pBattleMapScene->addItem(m_battleMapLinesToDraw.last());
        }
    }
}

/*!
 * \brief This function removes the Battle Map grid.
 */
void Dialog_NewBattleMap::removeBattleMapGrid()
{
    for(QGraphicsLineItem * item : m_battleMapLinesToDraw)
    {
        pBattleMapScene->removeItem(item);
        delete item;
    }

    m_battleMapLinesToDraw.clear();
}

/*!
 * \brief This function deletes the Battle Map scene.
 */
void Dialog_NewBattleMap::deleteBattleMapScene()
{
    removeBattleMapGrid();

    for (QGraphicsItem * item : pBattleMapScene->items())
    {
        pBattleMapScene->removeItem(item);
    }

    delete pBattleMapScene;
}
