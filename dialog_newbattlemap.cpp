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
    m_battleMapImageSelectedFromSource(false),
    pBattleMapImagePixMap(NULL),
    m_numberRows(0U),
    m_numberColumns(0U)
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
    delete pBattleMapImagePixMap;
}

/*!
 * \brief This function returns the value of the member variable m_battleMapImageSelectedFromSource.
 */
bool Dialog_NewBattleMap::getBattleMapImageSelectedFromSource() const
{
    qDebug() << "..." << __func__;
    return m_battleMapImageSelectedFromSource;
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
 * \brief This function returns the value of the member variable m_numberRows.
 */
quint32 Dialog_NewBattleMap::getNumberRows() const
{
    qDebug() << "..." << __func__;
    return m_numberRows;
}

/*!
 * \brief This function returns the value of the member variable m_numberColumns.
 */
quint32 Dialog_NewBattleMap::getNumberColumns() const
{
    qDebug() << "..." << __func__;
    return m_numberColumns;
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

        /* Disable widgets for numbers of rows and columns */
        pUserInterface->LineEdit_NumberRows->setEnabled(false);
        pUserInterface->LineEdit_NumberColumns->setEnabled(false);
        pUserInterface->PushButton_DecrementNumberRows->setEnabled(false);
        pUserInterface->PushButton_IncrementNumberRows->setEnabled(false);
        pUserInterface->PushButton_DecrementNumberColumns->setEnabled(false);
        pUserInterface->PushButton_IncrementNumberColumns->setEnabled(false);

        /* Disable push button with AcceptRole */
        pUserInterface->DialogButtonBox->button(QDialogButtonBox::Ok)->setEnabled(false);

        /* Reset source file path, number of rows and columns */
        pUserInterface->LineEdit_Source->setText("");
        m_numberRows = 0U;
        m_numberColumns = 0U;
        pUserInterface->LineEdit_NumberRows->setText(QString::number(m_numberRows));
        pUserInterface->LineEdit_NumberColumns->setText(QString::number(m_numberColumns));

        /* Reset Battle Map scene */
        delete pBattleMapScene;
        pBattleMapScene = new BattleMapScene();
        connect(pBattleMapScene, SIGNAL(selected_BattleMapSquare()), this, SLOT(selected_BattleMapSquare()));
        pUserInterface->GraphicsView_BattleMap->setScene(pBattleMapScene);

        pBattleMapScene->addText("Select Source.");

        /* Reset information whether the Battle Map image has been selected from source */
        m_battleMapImageSelectedFromSource = false;
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

        /* Enable widgets for numbers of rows and columns */
        pUserInterface->LineEdit_NumberRows->setEnabled(true);
        pUserInterface->LineEdit_NumberColumns->setEnabled(true);
        pUserInterface->PushButton_DecrementNumberRows->setEnabled(true);
        pUserInterface->PushButton_IncrementNumberRows->setEnabled(true);
        pUserInterface->PushButton_DecrementNumberColumns->setEnabled(true);
        pUserInterface->PushButton_IncrementNumberColumns->setEnabled(true);

        /* Disable push button with AcceptRole */
        pUserInterface->DialogButtonBox->button(QDialogButtonBox::Ok)->setEnabled(false);

        /* Reset source file path, number of rows and columns */
        pUserInterface->LineEdit_Source->setText("");
        m_numberRows = 0U;
        m_numberColumns = 0U;
        pUserInterface->LineEdit_NumberRows->setText(QString::number(m_numberRows));
        pUserInterface->LineEdit_NumberColumns->setText(QString::number(m_numberColumns));

        /* Reset information whether the Battle Map image has been selected from source */
        m_battleMapImageSelectedFromSource = false;

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

        pUserInterface->LineEdit_NumberRows->setText(QString::number(m_numberRows));;
    }
    else
    {
        m_numberRows = inputValue;
    }

    if (pUserInterface->RadioButton_ImageBattleMap->isChecked())
    {
        correctNumberColumns();
        controlNumberRowsAndColumns();
        drawBattleMapGrid();
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

        pUserInterface->LineEdit_NumberColumns->setText(QString::number(m_numberColumns));;
    }
    else
    {
        m_numberColumns = inputValue;
    }

    if (pUserInterface->RadioButton_ImageBattleMap->isChecked())
    {
        correctNumberRows();
        controlNumberRowsAndColumns();
        drawBattleMapGrid();
    }
}

/*!
 * \brief This function handles a click on PushButton_DecrementNumberRows.
 */
void Dialog_NewBattleMap::released_PushButton_DecrementNumberRows()
{
    qDebug() << "..." << __func__;

    if (0U < m_numberRows)
    {
        pUserInterface->LineEdit_NumberRows->setText(QString::number(--m_numberRows));

        if (pUserInterface->RadioButton_ImageBattleMap->isChecked())
        {
            correctNumberColumns();
            controlNumberRowsAndColumns();
            drawBattleMapGrid();
        }
    }
}

/*!
 * \brief This function handles a click on PushButton_IncrementNumberRows.
 */
void Dialog_NewBattleMap::released_PushButton_IncrementNumberRows()
{
    qDebug() << "..." << __func__;

    pUserInterface->LineEdit_NumberRows->setText(QString::number(++m_numberRows));

    if (pUserInterface->RadioButton_ImageBattleMap->isChecked())
    {
        correctNumberColumns();
        controlNumberRowsAndColumns();
        drawBattleMapGrid();
    }
}

/*!
 * \brief This function handles a click on PushButton_DecrementNumberColumns.
 */
void Dialog_NewBattleMap::released_PushButton_DecrementNumberColumns()
{
    qDebug() << "..." << __func__;

    if (0U < m_numberColumns)
    {
        pUserInterface->LineEdit_NumberColumns->setText(QString::number(--m_numberColumns));

        if (pUserInterface->RadioButton_ImageBattleMap->isChecked())
        {
            correctNumberRows();
            controlNumberRowsAndColumns();
            drawBattleMapGrid();
        }
    }
}

/*!
 * \brief This function handles a click on PushButton_IncrementNumberColumns.
 */
void Dialog_NewBattleMap::released_PushButton_IncrementNumberColumns()
{
    qDebug() << "..." << __func__;

    pUserInterface->LineEdit_NumberColumns->setText(QString::number(++m_numberColumns));

    if (pUserInterface->RadioButton_ImageBattleMap->isChecked())
    {
        correctNumberRows();
        controlNumberRowsAndColumns();
        drawBattleMapGrid();
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

        m_numberRows = pBattleMapImagePixMap->pixmap().height() / averageEdgeLength;
        m_numberColumns = pBattleMapImagePixMap->pixmap().width() / averageEdgeLength;

        /* Enable widgets for numbers of rows and columns */
        pUserInterface->LineEdit_NumberRows->setEnabled(true);
        pUserInterface->LineEdit_NumberColumns->setEnabled(true);
        pUserInterface->PushButton_DecrementNumberRows->setEnabled(true);
        pUserInterface->PushButton_IncrementNumberRows->setEnabled(true);
        pUserInterface->PushButton_DecrementNumberColumns->setEnabled(true);
        pUserInterface->PushButton_IncrementNumberColumns->setEnabled(true);

        /* Set information whether the Battle Map image has been selected from source */
        m_battleMapImageSelectedFromSource = true;

        /* Enable push button with AcceptRole */
        pUserInterface->DialogButtonBox->button(QDialogButtonBox::Ok)->setEnabled(true);
    }
    else
    {
        m_numberRows = 0U;
        m_numberColumns = 0U;

        /* Disable push button with AcceptRole */
        pUserInterface->DialogButtonBox->button(QDialogButtonBox::Ok)->setEnabled(false);
    }

    pUserInterface->LineEdit_NumberRows->setText(QString::number(m_numberRows));
    pUserInterface->LineEdit_NumberColumns->setText(QString::number(m_numberColumns));

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
 * \brief This function handles a click on the push button with AcceptRole.
 */
void Dialog_NewBattleMap::accepted_DialogButtonBox()
{
    qDebug() << "..." << __func__;

    /* Draw the selected Battle Map grid on the empty Battle Map image */
    if (!m_battleMapImageSelectedFromSource)
    {
        QPainter painter;
        painter.setPen(QPen(Qt::black, 3, Qt::SolidLine));
        QList<QGraphicsLineItem*> battleMapLinesToDraw = pBattleMapScene->getBattleMapLinesToDraw();
        for (quint32 lineIdx = 0U; lineIdx < battleMapLinesToDraw.count(); lineIdx++)
        {
            painter.drawLine(battleMapLinesToDraw.at(lineIdx)->line());
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

    //TODO load from configuration data
    QImage battleMapImage(EMPTY_BATTLEMAP_SOURCE);

    if (battleMapImage.isNull())
    {
        pBattleMapScene->addText("Empty Battle Map is no image file.");

        msgBox.setWindowTitle("Invalid file");
        msgBox.setText("Empty Battle Map is no image file.");
        msgBox.setIcon(QMessageBox::Warning);
        msgBox.exec();
    }
    else
    {
        pBattleMapImagePixMap = new QGraphicsPixmapItem(QPixmap::fromImage(battleMapImage));
        pBattleMapScene->addItem(pBattleMapImagePixMap);
        pBattleMapScene->setSceneRect(0, 0, pBattleMapImagePixMap->pixmap().width(), pBattleMapImagePixMap->pixmap().height());

        pUserInterface->GraphicsView_BattleMap->show();

        //TODO: Must been done when the standard button with AcceptRole has been enabled for the empty map
        /* Reset information whether the Battle Map image has been selected from source */
        m_battleMapImageSelectedFromSource = false;
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

    if (0 < m_numberColumns)
    {
        quint32 edgeLength = pBattleMapImagePixMap->pixmap().size().width() / m_numberColumns;
        m_numberRows = pBattleMapImagePixMap->pixmap().height() / edgeLength;
        pUserInterface->LineEdit_NumberRows->setText(QString::number(m_numberRows));
    }

}

/*!
 * \brief This function corrects the number of columns considering the Battle Map squares aspect ratio.
 */
void Dialog_NewBattleMap::correctNumberColumns()
{
    qDebug() << "..." << __func__;

    if (0 < m_numberRows)
    {
        quint32 edgeLength = pBattleMapImagePixMap->pixmap().height() / m_numberRows;
        m_numberColumns = pBattleMapImagePixMap->pixmap().width() / edgeLength;
        pUserInterface->LineEdit_NumberColumns->setText(QString::number(m_numberColumns));
    }

}

/*!
 * \brief This function controls the number of rows and columns.
 */
void Dialog_NewBattleMap::controlNumberRowsAndColumns()
{
    qDebug() << "..." << __func__;

    if ((0U < m_numberRows) && (0U < m_numberColumns))
    {
        bool invalidBattleMapGrid = false;
        quint32 edgeLengthHeigth = pBattleMapImagePixMap->pixmap().height() / m_numberRows;
        quint32 edgeLengthWidth = pBattleMapImagePixMap->pixmap().width() / m_numberColumns;

        /* Set background color of LineEdit_NumberRows to red if m_numberRows does not match the image size */
        if ((edgeLengthHeigth * m_numberRows) != static_cast<quint32>(pBattleMapImagePixMap->pixmap().height()))
        {
            pUserInterface->LineEdit_NumberRows->setStyleSheet(QString("#%1 { background-color: red; }").arg(pUserInterface->LineEdit_NumberRows->objectName()));
            invalidBattleMapGrid = true;
        }
        else
        {
            pUserInterface->LineEdit_NumberRows->setStyleSheet("");
        }

        /* Set background color of LineEdit_NumberColumns to red if m_numberColumns does not match the image size */
        if ((edgeLengthWidth * m_numberColumns) != static_cast<quint32>(pBattleMapImagePixMap->pixmap().width()))
        {
            pUserInterface->LineEdit_NumberColumns->setStyleSheet(QString("#%1 { background-color: red; }").arg(pUserInterface->LineEdit_NumberColumns->objectName()));
            invalidBattleMapGrid = true;
        }
        else
        {
            pUserInterface->LineEdit_NumberColumns->setStyleSheet("");
        }

        /* Enable or disable push button with AcceptRole */
        if (invalidBattleMapGrid)
        {
            pUserInterface->DialogButtonBox->button(QDialogButtonBox::Ok)->setEnabled(false);
        }
        else
        {
            pUserInterface->DialogButtonBox->button(QDialogButtonBox::Ok)->setEnabled(true);
        }
    }
}

/*!
 * \brief This function draws the Battle Map grid.
 */
void Dialog_NewBattleMap::drawBattleMapGrid()
{
    qDebug() << "..." << __func__;

    quint32 edgeLength;

    pBattleMapScene->removeBattleMapLines();

    if ((0U < m_numberRows) && (0U < m_numberColumns))
    {
        edgeLength = pBattleMapImagePixMap->pixmap().height() / m_numberRows;

        for (quint32 rowIdx = 0U; rowIdx < m_numberRows + 1; rowIdx++)
        {
            pBattleMapScene->drawBattleMapLine(QLineF(0, rowIdx * edgeLength, m_numberColumns * edgeLength, rowIdx * edgeLength));
        }

        edgeLength = pBattleMapImagePixMap->pixmap().width() / m_numberColumns;

        for (quint32 columnIdx = 0U; columnIdx < m_numberColumns + 1; columnIdx++)
        {
            pBattleMapScene->drawBattleMapLine(QLineF(columnIdx * edgeLength, 0, columnIdx * edgeLength, m_numberRows * edgeLength));
        }
    }
}
