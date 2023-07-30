/****************************************************************************************************************************************************
 * Includes
 ****************************************************************************************************************************************************/

#include "dialog_newbattlemap.h"
#include "ui_dialog_newbattlemap.h"

/****************************************************************************************************************************************************
 * Definition of Public Functions
 ****************************************************************************************************************************************************/

/*!
 * \brief This function is the constructor of the class Dialog_NewBattleMap.
 */
Dialog_NewBattleMap::Dialog_NewBattleMap(QWidget *parent) :
    QDialog(parent),
    pUserInterface(new Ui::Dialog_NewBattleMap),
    pBattleMapScene(NULL),
    pBattleMapImagePixMap(NULL),
    pBattleMap(new BattleMap())
{
    qDebug() << "..." << __func__;

    pUserInterface->setupUi(this);

    /* Set initial state */
    pUserInterface->RadioButton_ImageBattleMap->setChecked(true);
    pUserInterface->RadioButton_EmptyBattleMap->setChecked(false);
    pUserInterface->LineEdit_Source->setEnabled(true);
    pUserInterface->PushButton_SelectSource->setEnabled(true);
    pUserInterface->LineEdit_NumberRows->setText("0");
    pUserInterface->LineEdit_NumberColumns->setText("0");
    pUserInterface->CheckBox_DrawBattleMapGrid->setCheckState(Qt::Unchecked);
    pUserInterface->DialogButtonBox->button(QDialogButtonBox::Ok)->setEnabled(false);

    /* Set connections */
    connect(pUserInterface->RadioButton_ImageBattleMap, SIGNAL(toggled(bool)), this, SLOT(toggled_RadioButton_ImageBattleMap(bool)));
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
    connect(pUserInterface->DialogButtonBox, SIGNAL(accepted()), this, SLOT(accepted_DialogButtonBox()));
    connect(pUserInterface->DialogButtonBox, SIGNAL(rejected()), this, SLOT(reject()));

    emit pUserInterface->RadioButton_ImageBattleMap->toggled(true);
}

/*!
 * \brief This function is the destructor of the class Dialog_NewBattleMap.
 */
Dialog_NewBattleMap::~Dialog_NewBattleMap()
{
    qDebug() << "..." << __func__;

    delete pUserInterface;
    delete pBattleMapScene;
    delete pBattleMap;
}

/*!
 * \brief This function returns the pixmap of the member variable pBattleMapImagePixMap.
 */
QPixmap Dialog_NewBattleMap::getBattleMapPixmap() const
{
    qDebug() << "..." << __func__;
    return pBattleMapImagePixMap->pixmap();
}

/*!
 * \brief This function returns the address of the newly created Battle Map.
 */
BattleMap * Dialog_NewBattleMap::getBattleMap() const
{
    qDebug() << "..." << __func__;
    return pBattleMap;
}

/****************************************************************************************************************************************************
 * Definition of Protected Functions
 ****************************************************************************************************************************************************/

/* - */

/****************************************************************************************************************************************************
 * Definition of Private Slot Functions
 ****************************************************************************************************************************************************/

/*!
 * \brief This function handles a toggle of RadioButton_ImageBattleMap.
 */
void Dialog_NewBattleMap::toggled_RadioButton_ImageBattleMap(bool checked)
{
    qDebug() << "..." << __func__;

    if (checked)
    {
        /* Enable widgets for source selection */
        pUserInterface->LineEdit_Source->setEnabled(true);
        pUserInterface->PushButton_SelectSource->setEnabled(true);
        pUserInterface->CheckBox_DrawBattleMapGrid->setEnabled(true);

        /* Disable widgets for numbers of rows and columns */
        pUserInterface->LineEdit_NumberRows->setEnabled(false);
        pUserInterface->LineEdit_NumberColumns->setEnabled(false);
        pUserInterface->LineEdit_NumberRows->setStyleSheet("");
        pUserInterface->LineEdit_NumberColumns->setStyleSheet("");
        pUserInterface->PushButton_DecrementNumberRows->setEnabled(false);
        pUserInterface->PushButton_IncrementNumberRows->setEnabled(false);
        pUserInterface->PushButton_DecrementNumberColumns->setEnabled(false);
        pUserInterface->PushButton_IncrementNumberColumns->setEnabled(false);

        /* Disable push button with AcceptRole */
        pUserInterface->DialogButtonBox->button(QDialogButtonBox::Ok)->setEnabled(false);

        /* Reset source file path, number of rows and columns */
        pUserInterface->LineEdit_Source->setText("");
        pBattleMap->setNumberRows(0U);
        pBattleMap->setNumberColumns(0U);
        pUserInterface->LineEdit_NumberRows->setText(QString::number(pBattleMap->getNumberRows()));
        pUserInterface->LineEdit_NumberColumns->setText(QString::number(pBattleMap->getNumberRows()));
        pUserInterface->CheckBox_DrawBattleMapGrid->setCheckState(Qt::Unchecked);

        /* Reset Battle Map scene */
        delete pBattleMapScene;
        pBattleMapScene = new BattleMapScene();
        connect(pBattleMapScene, SIGNAL(selected_BattleMapSquare()), this, SLOT(selected_BattleMapSquare()));
        pUserInterface->GraphicsView_BattleMap->setScene(pBattleMapScene);

        pBattleMapScene->addText("Select Source.");
    }
}

/*!
 * \brief This function handles a toggle of RadioButton_EmptyBattleMap.
 */
void Dialog_NewBattleMap::toggled_RadioButton_EmptyBattleMap(bool checked)
{
    qDebug() << "..." << __func__;

    if (checked)
    {      
        /* Disable widgets for source selection */
        pUserInterface->LineEdit_Source->setEnabled(false);
        pUserInterface->PushButton_SelectSource->setEnabled(false);
        pUserInterface->CheckBox_DrawBattleMapGrid->setEnabled(false);

        /* Enable widgets for numbers of rows and columns */
        pUserInterface->LineEdit_NumberRows->setEnabled(true);
        pUserInterface->LineEdit_NumberColumns->setEnabled(true);
        pUserInterface->LineEdit_NumberRows->setStyleSheet("");
        pUserInterface->LineEdit_NumberColumns->setStyleSheet("");
        pUserInterface->PushButton_DecrementNumberRows->setEnabled(true);
        pUserInterface->PushButton_IncrementNumberRows->setEnabled(true);
        pUserInterface->PushButton_DecrementNumberColumns->setEnabled(true);
        pUserInterface->PushButton_IncrementNumberColumns->setEnabled(true);

        /* Enable push button with AcceptRole */
        pUserInterface->DialogButtonBox->button(QDialogButtonBox::Ok)->setEnabled(true);

        /* Reset source file path and check box state */
        pUserInterface->LineEdit_Source->setText("");
        pUserInterface->CheckBox_DrawBattleMapGrid->setCheckState(Qt::Checked);

        quint32 maximumNumberRows = static_cast<quint32>(calcScreenHeightInInches(PLAYER_SCREEN_DIAGONAL, PLAYER_SCREEN_RESOLUTION.height(), PLAYER_SCREEN_RESOLUTION.width()));
        quint32 maximumNumberColumns = static_cast<quint32>(calcScreenWidthInInches(PLAYER_SCREEN_DIAGONAL, PLAYER_SCREEN_RESOLUTION.height(), PLAYER_SCREEN_RESOLUTION.width()));
        pBattleMap->setNumberRows(maximumNumberRows);
        pBattleMap->setNumberColumns(maximumNumberColumns);
        pUserInterface->LineEdit_NumberRows->setText(QString::number(pBattleMap->getNumberRows()));
        pUserInterface->LineEdit_NumberColumns->setText(QString::number(pBattleMap->getNumberColumns()));

        /* Show empty battle map image */
        showEmptyBattleMapImage();
    }
}

/*!
 * \brief This function handles the editing of LineEdit_Source.
 */
void Dialog_NewBattleMap::editingFinished_LineEdit_Source()
{
    qDebug() << "..." << __func__;

    if (!pUserInterface->LineEdit_Source->text().isEmpty())
    {
        /* Show battle map image from selected source */
        showSourceBattleMapImage();
    }
}

/*!
 * \brief This function handles a click on PushButton_SelectSource.
 */
void Dialog_NewBattleMap::released_PushButton_SelectSource()
{
    qDebug() << "..." << __func__;

    /* Select source for battle map */
    QString selectedSource = QFileDialog::getOpenFileName(this, tr("Select Source"), ".", tr("Image Files (*.png *.jpg *.bmp)"));
    pUserInterface->LineEdit_Source->setText(selectedSource);

    /* LineEdit_Source has been edited, call slot function */
    editingFinished_LineEdit_Source();
}

/*!
 * \brief This function handles the editing of LineEdit_NumberRows.
 */
void Dialog_NewBattleMap::editingFinished_LineEdit_NumberRows()
{
    qDebug() << "..." << __func__;

    qint32 inputValue;
    bool validNumber;
    QMessageBox msgBox(this);

    inputValue = pUserInterface->LineEdit_NumberRows->text().toInt(&validNumber, 10);

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

    if (pUserInterface->RadioButton_ImageBattleMap->isChecked())
    {
        correctNumberColumns();
        controlNumberRowsAndColumns();
        drawBattleMapGrid();
    }
    else
    {
        controlNumberRowsAndColumns();
        showEmptyBattleMapImage();
    }
}

/*!
 * \brief This function handles the editing of LineEdit_NumberColumns.
 */
void Dialog_NewBattleMap::editingFinished_LineEdit_NumberColumns()
{
    qDebug() << "..." << __func__;

    qint32 inputValue;
    bool validNumber;
    QMessageBox msgBox(this);

    inputValue = pUserInterface->LineEdit_NumberColumns->text().toInt(&validNumber, 10);

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

    if (pUserInterface->RadioButton_ImageBattleMap->isChecked())
    {
        correctNumberRows();
        controlNumberRowsAndColumns();
        drawBattleMapGrid();
    }
    else
    {
        controlNumberRowsAndColumns();
        showEmptyBattleMapImage();
    }
}

/*!
 * \brief This function handles a click on PushButton_DecrementNumberRows.
 */
void Dialog_NewBattleMap::released_PushButton_DecrementNumberRows()
{
    qDebug() << "..." << __func__;

    quint32 numberRows = pBattleMap->getNumberRows();
    pBattleMap->setNumberRows(numberRows - 1);
    pUserInterface->LineEdit_NumberRows->setText(QString::number(pBattleMap->getNumberRows()));

    if (0U == pBattleMap->getNumberRows())
    {
        pUserInterface->PushButton_DecrementNumberRows->setEnabled(false);
    }
    else
    {
        pUserInterface->PushButton_DecrementNumberRows->setEnabled(true);
    }

    if (pUserInterface->RadioButton_ImageBattleMap->isChecked())
    {
        correctNumberColumns();
        controlNumberRowsAndColumns();
        drawBattleMapGrid();
    }
    else
    {
        controlNumberRowsAndColumns();
        showEmptyBattleMapImage();
    }
}

/*!
 * \brief This function handles a click on PushButton_IncrementNumberRows.
 */
void Dialog_NewBattleMap::released_PushButton_IncrementNumberRows()
{
    qDebug() << "..." << __func__;

    quint32 numberRows = pBattleMap->getNumberRows();
    pBattleMap->setNumberRows(numberRows + 1);
    pUserInterface->LineEdit_NumberRows->setText(QString::number(pBattleMap->getNumberRows()));

    if (0U == pBattleMap->getNumberRows())
    {
        pUserInterface->PushButton_DecrementNumberRows->setEnabled(false);
    }
    else
    {
        pUserInterface->PushButton_DecrementNumberRows->setEnabled(true);
    }

    if (pUserInterface->RadioButton_ImageBattleMap->isChecked())
    {
        correctNumberColumns();
        controlNumberRowsAndColumns();
        drawBattleMapGrid();
    }
    else
    {
        controlNumberRowsAndColumns();
        showEmptyBattleMapImage();
    }
}

/*!
 * \brief This function handles a click on PushButton_DecrementNumberColumns.
 */
void Dialog_NewBattleMap::released_PushButton_DecrementNumberColumns()
{
    qDebug() << "..." << __func__;

    quint32 numberColumns = pBattleMap->getNumberColumns();
    pBattleMap->setNumberColumns(numberColumns - 1);
    pUserInterface->LineEdit_NumberColumns->setText(QString::number(pBattleMap->getNumberColumns()));

    if (0U == pBattleMap->getNumberColumns())
    {
        pUserInterface->PushButton_DecrementNumberColumns->setEnabled(false);
    }
    else
    {
        pUserInterface->PushButton_DecrementNumberColumns->setEnabled(true);
    }

    if (pUserInterface->RadioButton_ImageBattleMap->isChecked())
    {
        correctNumberRows();
        controlNumberRowsAndColumns();
        drawBattleMapGrid();
    }
    else
    {
        controlNumberRowsAndColumns();
        showEmptyBattleMapImage();
    }
}

/*!
 * \brief This function handles a click on PushButton_IncrementNumberColumns.
 */
void Dialog_NewBattleMap::released_PushButton_IncrementNumberColumns()
{
    qDebug() << "..." << __func__;

    quint32 numberColumns = pBattleMap->getNumberColumns();
    pBattleMap->setNumberColumns(numberColumns + 1);
    pUserInterface->LineEdit_NumberColumns->setText(QString::number(pBattleMap->getNumberColumns()));

    if (0U == pBattleMap->getNumberColumns())
    {
        pUserInterface->PushButton_DecrementNumberColumns->setEnabled(false);
    }
    else
    {
        pUserInterface->PushButton_DecrementNumberColumns->setEnabled(true);
    }

    if (pUserInterface->RadioButton_ImageBattleMap->isChecked())
    {
        correctNumberRows();
        controlNumberRowsAndColumns();
        drawBattleMapGrid();
    }
    else
    {
        controlNumberRowsAndColumns();
        showEmptyBattleMapImage();
    }
}

/*!
 * \brief This function handles the selection of a Battle Map square.
 */
void Dialog_NewBattleMap::selected_BattleMapSquare()
{
    qDebug() << "..." << __func__;

    QMessageBox msgBox(this);

    QPointF selectedSquareEdges =  pBattleMapScene->getScenePosRelease() - pBattleMapScene->getScenePosPress();
    quint32 averageEdgeLength = static_cast<quint32>((abs(selectedSquareEdges.rx()) + abs(selectedSquareEdges.ry())) / 2U);
    quint32 averageEdgeLengthIncrement = averageEdgeLength;
    quint32 averageEdgeLengthDecrement = averageEdgeLength;
    quint32 counterIncrement = 0U;
    quint32 counterDecrement = 0U;
    quint32 residual;

    if (0U < averageEdgeLength)
    {
        /* optimize averageEdgeLength */
        do
        {
            residual = (pBattleMapImagePixMap->pixmap().height() % averageEdgeLengthIncrement);

            if (0U != residual)
            {
                averageEdgeLengthIncrement++;
                counterIncrement++;
            }

        } while (0U != residual);
        do
        {
            residual = (pBattleMapImagePixMap->pixmap().height() % averageEdgeLengthDecrement);

            if (0U != residual)
            {
                averageEdgeLengthDecrement--;
                counterDecrement++;
            }

        } while (0U != residual);

        if (counterIncrement < counterDecrement)
        {
            averageEdgeLength = averageEdgeLengthIncrement;
        }
        else
        {
            averageEdgeLength = averageEdgeLengthDecrement;
        }

        pBattleMap->setNumberRows(pBattleMapImagePixMap->pixmap().height() / averageEdgeLength);
        pBattleMap->setNumberColumns(pBattleMapImagePixMap->pixmap().width() / averageEdgeLength);

        /* Enable widgets for numbers of rows and columns */
        pUserInterface->LineEdit_NumberRows->setEnabled(true);
        pUserInterface->LineEdit_NumberColumns->setEnabled(true);
        pUserInterface->PushButton_DecrementNumberRows->setEnabled(true);
        pUserInterface->PushButton_IncrementNumberRows->setEnabled(true);
        pUserInterface->PushButton_DecrementNumberColumns->setEnabled(true);
        pUserInterface->PushButton_IncrementNumberColumns->setEnabled(true);

        /* Enable push button with AcceptRole */
        pUserInterface->DialogButtonBox->button(QDialogButtonBox::Ok)->setEnabled(true);
    }
    else
    {
        pBattleMap->setNumberRows(0U);
        pBattleMap->setNumberColumns(0U);

        /* Disable push button with AcceptRole */
        pUserInterface->DialogButtonBox->button(QDialogButtonBox::Ok)->setEnabled(false);
    }

    pUserInterface->LineEdit_NumberRows->setText(QString::number(pBattleMap->getNumberRows()));
    pUserInterface->LineEdit_NumberColumns->setText(QString::number(pBattleMap->getNumberColumns()));

    controlNumberRowsAndColumns();
    drawBattleMapGrid();

    if (0U < averageEdgeLength)
    {
        msgBox.setWindowTitle("Control Battle Map grid");
        msgBox.setText("Please control the Battle Map grid and readjust the number of rows and columns in case of mismatch.");
        msgBox.setIcon(QMessageBox::Question);
        msgBox.exec();
    }
}

/*!
 * \brief This function handles a state change of CheckBox_DrawBattleMapGrid.
 */
void Dialog_NewBattleMap::stateChanged_CheckBox_DrawBattleMapGrid(int state)
{
    qDebug() << "..." << __func__;

    drawBattleMapGrid();
}

/*!
 * \brief This function handles a click on the push button with AcceptRole.
 */
void Dialog_NewBattleMap::accepted_DialogButtonBox()
{
    qDebug() << "..." << __func__;

    /* Draw the selected Battle Map grid on the Battle Map image */
    if (pUserInterface->CheckBox_DrawBattleMapGrid->isChecked())
    {
        QPixmap pixmap(pBattleMapImagePixMap->pixmap());
        QPainter *painter = new QPainter(&pixmap);
        //TODO: load pen properties from configuration data
        painter->setPen(QPen(Qt::black, 3, Qt::SolidLine));
        QList<QGraphicsLineItem*> battleMapLinesToDraw = pBattleMapScene->getBattleMapLinesToDraw();
        for (quint32 lineIdx = 0U; lineIdx < battleMapLinesToDraw.count(); lineIdx++)
        {
            painter->drawLine(battleMapLinesToDraw.at(lineIdx)->line());
        }
        delete painter;
        pBattleMapImagePixMap->setPixmap(pixmap);
    }

    quint32 edgeLength = pBattleMapImagePixMap->pixmap().height() / pBattleMap->getNumberRows();

    for (quint32 rowIdx = 0U; rowIdx < pBattleMap->getNumberRows(); rowIdx++)
    {
        for (quint32 columnIdx = 0U; columnIdx < pBattleMap->getNumberColumns(); columnIdx++)
        {
            QGraphicsPixmapItem * battleMapSquarePixmap = new QGraphicsPixmapItem();
            battleMapSquarePixmap->setPixmap(pBattleMapImagePixMap->pixmap().copy(QRect(columnIdx * edgeLength, rowIdx * edgeLength, edgeLength, edgeLength)));
            //TODO: load size of Battle Map square pixmap from configuration data
            battleMapSquarePixmap->setPixmap(battleMapSquarePixmap->pixmap().scaled(QSize(BATTLEMAPSQUARE_SIZE, BATTLEMAPSQUARE_SIZE)));
            pBattleMap->setIndexedBattleMapSquarePixmap(rowIdx, battleMapSquarePixmap);
        }
    }

    this->accept();
}

/****************************************************************************************************************************************************
 * Definition of Private Functions
 ****************************************************************************************************************************************************/

/*!
 * \brief This function shows the empty Battle Map image.
 */
void Dialog_NewBattleMap::showEmptyBattleMapImage()
{
    qDebug() << "..." << __func__;

    QMessageBox msgBox(this);

    /* Reset Battle Map scene */
    delete pBattleMapScene;
    pBattleMapScene = new BattleMapScene();
    connect(pBattleMapScene, SIGNAL(selected_BattleMapSquare()), this, SLOT(selected_BattleMapSquare()));
    pUserInterface->GraphicsView_BattleMap->setScene(pBattleMapScene);

    pUserInterface->GraphicsView_BattleMap->setInteractive(false);
    pUserInterface->GraphicsView_BattleMap->viewport()->setCursor(Qt::ArrowCursor);
    pUserInterface->GraphicsView_BattleMap->setToolTip("");

    QImage emptyBattleMapSquare(EMPTY_BATTLEMAPSQUARE_SOURCE);
    emptyBattleMapSquare = emptyBattleMapSquare.scaledToWidth(BATTLEMAPSQUARE_SIZE);

    if (emptyBattleMapSquare.isNull())
    {
        pBattleMapScene->addText("Empty Battle Map square is no image file.");

        msgBox.setWindowTitle("Invalid file");
        msgBox.setText("Empty Battle Map square is no image file.");
        msgBox.setIcon(QMessageBox::Warning);
        msgBox.exec();
    }
    else if (emptyBattleMapSquare.width() != emptyBattleMapSquare.height())
    {
        pBattleMapScene->addText("Empty Battle Map square has no square format.");

        msgBox.setWindowTitle("Invalid file");
        msgBox.setText("Empty Battle Map square has no square format.");
        msgBox.setIcon(QMessageBox::Warning);
        msgBox.exec();
    }
    else
    {
        QPixmap pixmap(QSize(pBattleMap->getNumberColumns()* BATTLEMAPSQUARE_SIZE, pBattleMap->getNumberRows() * BATTLEMAPSQUARE_SIZE));
        QPainter *painter = new QPainter(&pixmap);
        for (quint32 rowIdx = 0U; rowIdx < pBattleMap->getNumberRows(); rowIdx++)
        {
            for (quint32 columnIdx = 0U; columnIdx < pBattleMap->getNumberColumns(); columnIdx++)
            {
                QRect targetRect = QRect(columnIdx * BATTLEMAPSQUARE_SIZE, rowIdx * BATTLEMAPSQUARE_SIZE, BATTLEMAPSQUARE_SIZE, BATTLEMAPSQUARE_SIZE);
                QRect sourceRect = emptyBattleMapSquare.rect();
                painter->drawPixmap(targetRect, QPixmap::fromImage(emptyBattleMapSquare), sourceRect);
            }
        }
        delete painter;

        pBattleMapImagePixMap = new QGraphicsPixmapItem();
        pBattleMapImagePixMap->setPixmap(pixmap);

        pBattleMapScene->addItem(pBattleMapImagePixMap);
        pBattleMapScene->setSceneRect(0, 0, pBattleMapImagePixMap->pixmap().width(), pBattleMapImagePixMap->pixmap().height());

        drawBattleMapGrid();

        pUserInterface->GraphicsView_BattleMap->show();
    }
}

/*!
 * \brief This function shows the Battle Map image from selected source.
 */
void Dialog_NewBattleMap::showSourceBattleMapImage()
{
    qDebug() << "..." << __func__;

    QMessageBox msgBox(this);

    /* Reset Battle Map scene */
    delete pBattleMapScene;
    pBattleMapScene = new BattleMapScene();
    connect(pBattleMapScene, SIGNAL(selected_BattleMapSquare()), this, SLOT(selected_BattleMapSquare()));
    pUserInterface->GraphicsView_BattleMap->setScene(pBattleMapScene);

    pUserInterface->GraphicsView_BattleMap->setInteractive(false);
    pUserInterface->GraphicsView_BattleMap->viewport()->setCursor(Qt::ArrowCursor);
    pUserInterface->GraphicsView_BattleMap->setToolTip("");

    QImage battleMapImage(pUserInterface->LineEdit_Source->text());

    if (battleMapImage.isNull())
    {
        pBattleMapScene->addText("Image Battle Map is no image file.");

        msgBox.setWindowTitle("Invalid file");
        msgBox.setText("Image Battle Map is no image file.");
        msgBox.setIcon(QMessageBox::Warning);
        msgBox.exec();
    }
    else
    {
        pUserInterface->GraphicsView_BattleMap->setInteractive(true);
        pUserInterface->GraphicsView_BattleMap->viewport()->setCursor(Qt::CrossCursor);
        pUserInterface->GraphicsView_BattleMap->setToolTip("Select Battle Map square");

        pBattleMapImagePixMap = new QGraphicsPixmapItem(QPixmap::fromImage(battleMapImage));
        pBattleMapScene->addItem(pBattleMapImagePixMap);
        pBattleMapScene->setSceneRect(0, 0, pBattleMapImagePixMap->pixmap().width(), pBattleMapImagePixMap->pixmap().height());

        pUserInterface->GraphicsView_BattleMap->show();

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
    qDebug() << "..." << __func__;

    if (0 < pBattleMap->getNumberColumns())
    {
        quint32 edgeLength = pBattleMapImagePixMap->pixmap().size().width() / pBattleMap->getNumberColumns();
        pBattleMap->setNumberRows(pBattleMapImagePixMap->pixmap().height() / edgeLength);
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
    qDebug() << "..." << __func__;

    if (0 < pBattleMap->getNumberRows())
    {
        quint32 edgeLength = pBattleMapImagePixMap->pixmap().height() / pBattleMap->getNumberRows();
        pBattleMap->setNumberColumns(pBattleMapImagePixMap->pixmap().width() / edgeLength);
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
 * \brief This function controls the number of rows and columns.
 */
void Dialog_NewBattleMap::controlNumberRowsAndColumns()
{
    qDebug() << "..." << __func__;

    bool validBattleMapGrid = true;

    if ((0U < pBattleMap->getNumberRows()) && (0U < pBattleMap->getNumberColumns()))
    {
        if (pUserInterface->RadioButton_ImageBattleMap->isChecked())
        {
            quint32 edgeLengthHeigth = pBattleMapImagePixMap->pixmap().height() / pBattleMap->getNumberRows();
            quint32 edgeLengthWidth = pBattleMapImagePixMap->pixmap().width() / pBattleMap->getNumberColumns();

            if (edgeLengthHeigth == edgeLengthWidth)
            {
                /* Set background color of LineEdit_NumberRows to red if number of rows does not match the image size */
                if ((edgeLengthHeigth * pBattleMap->getNumberRows()) != static_cast<quint32>(pBattleMapImagePixMap->pixmap().height()))
                {
                    pUserInterface->LineEdit_NumberRows->setStyleSheet(QString("#%1 { background-color: red; }").arg(pUserInterface->LineEdit_NumberRows->objectName()));
                    validBattleMapGrid = false;
                }
                else
                {
                    pUserInterface->LineEdit_NumberRows->setStyleSheet("");
                }

                /* Set background color of LineEdit_NumberColumns to red if number of columns does not match the image size */
                if ((edgeLengthWidth * pBattleMap->getNumberColumns()) != static_cast<quint32>(pBattleMapImagePixMap->pixmap().width()))
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
    if (validBattleMapGrid)
    {
        pUserInterface->DialogButtonBox->button(QDialogButtonBox::Ok)->setEnabled(true);
    }
    else
    {
        pUserInterface->DialogButtonBox->button(QDialogButtonBox::Ok)->setEnabled(false);
    }
}

/*!
 * \brief This function draws the Battle Map grid.
 */
void Dialog_NewBattleMap::drawBattleMapGrid()
{
    qDebug() << "..." << __func__;

    quint32 edgeLength;
    QPen pen;

    if (pUserInterface->CheckBox_DrawBattleMapGrid->isChecked())
    {
        pen = QPen(Qt::black, 3, Qt::SolidLine);
    }
    else
    {
        pen = QPen(Qt::black, 3, Qt::DashLine);
    }

    pBattleMapScene->removeBattleMapLines();

    if ((0U < pBattleMap->getNumberRows()) && (0U < pBattleMap->getNumberColumns()))
    {
        edgeLength = pBattleMapImagePixMap->pixmap().height() / pBattleMap->getNumberRows();
        for (quint32 rowIdx = 0U; rowIdx < pBattleMap->getNumberRows() + 1; rowIdx++)
        {
            pBattleMapScene->drawBattleMapLine(QLineF(0, rowIdx * edgeLength, pBattleMap->getNumberColumns() * edgeLength, rowIdx * edgeLength), pen);
        }
        edgeLength = pBattleMapImagePixMap->pixmap().width() / pBattleMap->getNumberColumns();
        for (quint32 columnIdx = 0U; columnIdx < pBattleMap->getNumberColumns() + 1; columnIdx++)
        {
            pBattleMapScene->drawBattleMapLine(QLineF(columnIdx * edgeLength, 0, columnIdx * edgeLength, pBattleMap->getNumberRows() * edgeLength), pen);
        }
    }
}
