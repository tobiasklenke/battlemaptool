/****************************************************************************************************************************************************
 * INCLUDES                                                                                                                                         *
 ****************************************************************************************************************************************************/

#include "dialog_newbattlemap.h"
#include "ui_dialog_newbattlemap.h"

/****************************************************************************************************************************************************
 * DEFINITION OF PUBLIC FUNCTIONS                                                                                                                   *
 ****************************************************************************************************************************************************/

/*!**************************************************************************************************************************************************
 * \brief   This function is the constructor of the class Dialog_NewBattleMap.                                                                      *
 *                                                                                                                                                  *
 * \details This function sets up the user interface of the class Dialog_NewBattleMap and connects the signals and slots of the user interface      *
 *          widgets. Afterwards, the function checks the widget RadioButton_SourceBattleMap which is for the selection of the Battle Map image      *
 *          source and emits the signal that the widget RadioButton_SourceBattleMap has been toggled.                                               *
 *                                                                                                                                                  *
 * \param   parent                        Parent of the class Dialog_NewBattleMap                                                                   *
 *                                                                                                                                                  *
 * \return  This function does not have any return value.                                                                                           *
 ****************************************************************************************************************************************************/
Dialog_NewBattleMap::Dialog_NewBattleMap(QWidget *parent) :
    QDialog(parent),
    pUserInterface(new Ui::Dialog_NewBattleMap),
    pBattleMapScene(nullptr),
    pBattleMapImagePixMap(nullptr),
    pBattleMap(new BattleMap())
{
    qDebug() << "..." << __func__;

    pUserInterface->setupUi(this);

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
    connect(pUserInterface->DialogButtonBox, SIGNAL(accepted()), this, SLOT(accepted_DialogButtonBox()));
    connect(pUserInterface->DialogButtonBox, SIGNAL(rejected()), this, SLOT(reject()));

    pUserInterface->RadioButton_SourceBattleMap->setChecked(true);
    emit pUserInterface->RadioButton_SourceBattleMap->toggled(true);
}

/*!**************************************************************************************************************************************************
 * \brief   This function is the destructor of the class Dialog_NewBattleMap.                                                                       *
 *                                                                                                                                                  *
 * \details This function deletes the objects pointed to by pUserInterface, pBattleMapScene and pBattleMap.                                         *
 *                                                                                                                                                  *
 * \return  This function does not have any return value.                                                                                           *
 ****************************************************************************************************************************************************/
Dialog_NewBattleMap::~Dialog_NewBattleMap()
{
    qDebug() << "..." << __func__;

    delete pUserInterface;
    delete pBattleMapScene;
    delete pBattleMap;
}

/*!**************************************************************************************************************************************************
 * \brief   This function returns the address of the newly created Battle Map object.                                                               *
 *                                                                                                                                                  *
 * \details -                                                                                                                                       *
 *                                                                                                                                                  *
 * \return  This function returns the address of the newly created Battle Map object.                                                               *
 ****************************************************************************************************************************************************/
BattleMap * Dialog_NewBattleMap::getBattleMap() const
{
    qDebug() << "..." << __func__;

    return pBattleMap;
}

/****************************************************************************************************************************************************
 * DEFINITION OF PROTECTED FUNCTIONS                                                                                                                *
 ****************************************************************************************************************************************************/

/* - */

/****************************************************************************************************************************************************
 * DEFINITION OF PRIVATE SLOT FUNCTIONS                                                                                                             *
 ****************************************************************************************************************************************************/

/*!**************************************************************************************************************************************************
 * \brief   This function handles a toggle of RadioButton_SourceBattleMap.                                                                          *
 *                                                                                                                                                  *
 * \details If RadioButton_SourceBattleMap is checked, this function enables, disables and resets the user interface widgets according to their     *
 *          initial functional role for the Battle Map image source selection. Afterwards, the function resets and reconnects the Battle Map scene. *
 *                                                                                                                                                  *
 * \param   checked                       State of RadioButton_SourceBattleMap                                                                      *
 *                                                                                                                                                  *
 * \return  This function does not have any return value.                                                                                           *
 ****************************************************************************************************************************************************/
void Dialog_NewBattleMap::toggled_RadioButton_SourceBattleMap(bool checked)
{
    qDebug() << "..." << __func__;

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
        pUserInterface->GraphicsView_BattleMap->setInteractive(false);
        pUserInterface->GraphicsView_BattleMap->viewport()->setCursor(Qt::ArrowCursor);
        pUserInterface->GraphicsView_BattleMap->setToolTip("");

        /* reset and reconnect Battle Map scene */
        delete pBattleMapScene;
        pBattleMapScene = new BattleMapScene();
        connect(pBattleMapScene, SIGNAL(selected_BattleMapSquare()), this, SLOT(selected_BattleMapSquare()));
        pUserInterface->GraphicsView_BattleMap->setScene(pBattleMapScene);
        pBattleMapScene->addText("Select source.");
    }
}

/*!**************************************************************************************************************************************************
 * \brief   This function handles a toggle of RadioButton_EmptyBattleMap.                                                                           *
 *                                                                                                                                                  *
 * \details If RadioButton_EmptyBattleMap is checked, this function enables, disables and resets the user interface widgets according to their      *
 *          initial functional role for the creation of an empty Battle Map. Afterwards, the function calculates the maximum number of rows and     *
 *          columns displayable on the player screen and shows the corresponding empty Battle Map image.                                            *
 *                                                                                                                                                  *
 * \param   checked                       State of RadioButton_EmptyBattleMap                                                                       *
 *                                                                                                                                                  *
 * \return  This function does not have any return value.                                                                                           *
 ****************************************************************************************************************************************************/
void Dialog_NewBattleMap::toggled_RadioButton_EmptyBattleMap(bool checked)
{
    qDebug() << "..." << __func__;

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
        pUserInterface->GraphicsView_BattleMap->setInteractive(false);
        pUserInterface->GraphicsView_BattleMap->viewport()->setCursor(Qt::ArrowCursor);
        pUserInterface->GraphicsView_BattleMap->setToolTip("");

        /* calculate maximum number of rows and columns displayable on the player screen (each square is one inch high and one inch wide) */
        quint32 maximumNumberRows = static_cast<quint32>(calcScreenHeightInInches(PLAYER_SCREEN_DIAGONAL, PLAYER_SCREEN_RESOLUTION.height(), PLAYER_SCREEN_RESOLUTION.width()));
        quint32 maximumNumberColumns = static_cast<quint32>(calcScreenWidthInInches(PLAYER_SCREEN_DIAGONAL, PLAYER_SCREEN_RESOLUTION.height(), PLAYER_SCREEN_RESOLUTION.width()));
        pBattleMap->setNumberRows(maximumNumberRows);
        pBattleMap->setNumberColumns(maximumNumberColumns);
        pUserInterface->LineEdit_NumberRows->setText(QString::number(pBattleMap->getNumberRows()));
        pUserInterface->LineEdit_NumberColumns->setText(QString::number(pBattleMap->getNumberColumns()));

        showEmptyBattleMapImage();
    }
}

/*!**************************************************************************************************************************************************
 * \brief   This function handles the editing of LineEdit_Source.                                                                                   *
 *                                                                                                                                                  *
 * \details If the text string of LineEdit_Source is not empty after editing, this function shows the Battle Map image from the selected source.    *
 *                                                                                                                                                  *
 * \return  This function does not have any return value.                                                                                           *
 ****************************************************************************************************************************************************/
void Dialog_NewBattleMap::editingFinished_LineEdit_Source()
{
    qDebug() << "..." << __func__;

    if (!pUserInterface->LineEdit_Source->text().isEmpty())
    {
        showSourceBattleMapImage();
    }
}

/*!**************************************************************************************************************************************************
 * \brief   This function handles a click on PushButton_SelectSource.                                                                               *
 *                                                                                                                                                  *
 * \details This function opens a file dialog in order to select the source file for the Battle Map image and synchronises the file path of the     *
 *          selected source with the text string of LineEdit_Source. Since LineEdit_Source is edited this way, the function calls the corresponding *
 *          function that handles the editing of LineEdit_Source.                                                                                   *
 *                                                                                                                                                  *
 * \return  This function does not have any return value.                                                                                           *
 ****************************************************************************************************************************************************/
void Dialog_NewBattleMap::released_PushButton_SelectSource()
{
    qDebug() << "..." << __func__;

    QString selectedSource = QFileDialog::getOpenFileName(this, tr("Select source"), ".", tr("Image Files (*.png *.jpg *.bmp)"));
    pUserInterface->LineEdit_Source->setText(selectedSource);

    editingFinished_LineEdit_Source();
}

/*!**************************************************************************************************************************************************
 * \brief   This function handles the editing of LineEdit_NumberRows.                                                                               *
 *                                                                                                                                                  *
 * \details This function checks the input text string for validity and updates the number of rows if the input text string is interpretable as     *
 *          positive numeric value. Otherwise, the function shows a warning message box. Afterwards, the function enables or disables the widget    *
 *          PushButton_DecrementNumberRows depending on whether the number of rows is greater than 0. Finally, the function corrects the number of  *
 *          columns, checks and draws the Battle Map grid if the widget RadioButton_SourceBattleMap is checked, or checks the Battle Map grid and   *
 *          shows the empty Battle Map image if the widget RadioButton_EmptyBattleMap is checked.                                                   *
 *                                                                                                                                                  *
 * \return  This function does not have any return value.                                                                                           *
 ****************************************************************************************************************************************************/
void Dialog_NewBattleMap::editingFinished_LineEdit_NumberRows()
{
    qDebug() << "..." << __func__;

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

/*!**************************************************************************************************************************************************
 * \brief   This function handles the editing of LineEdit_NumberColumns.                                                                            *
 *                                                                                                                                                  *
 * \details This function checks the input text string for validity and updates the number of columns if the input text string is interpretable as  *
 *          positive numeric value. Otherwise, the function shows a warning message box. Afterwards, the function enables or disables the widget    *
 *          PushButton_DecrementNumberColumns depending on whether the number of columns is greater than 0. Finally, it corrects the number of      *
 *          rows, checks and draws the Battle Map grid if the widget RadioButton_SourceBattleMap is checked, or checks the Battle Map grid and      *
 *          shows the empty Battle Map image if the widget RadioButton_EmptyBattleMap is checked.                                                   *
 *                                                                                                                                                  *
 * \return  This function does not have any return value.                                                                                           *
 ****************************************************************************************************************************************************/
void Dialog_NewBattleMap::editingFinished_LineEdit_NumberColumns()
{
    qDebug() << "..." << __func__;

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

/*!**************************************************************************************************************************************************
 * \brief   This function handles a click on PushButton_DecrementNumberRows.                                                                        *
 *                                                                                                                                                  *
 * \details This function decrements the number of rows. Afterwards, the function enables or disables the widget PushButton_DecrementNumberRows     *
 *          depending on whether the number of rows is greater than 0. Finally, the function corrects the number of columns, checks and draws the   *
 *          Battle Map grid if the widget RadioButton_SourceBattleMap is checked, or checks the Battle Map grid and shows the empty Battle Map      *
 *          image if the widget RadioButton_EmptyBattleMap is checked.                                                                              *
 *                                                                                                                                                  *
 * \return  This function does not have any return value.                                                                                           *
 ****************************************************************************************************************************************************/
void Dialog_NewBattleMap::released_PushButton_DecrementNumberRows()
{
    qDebug() << "..." << __func__;

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

/*!**************************************************************************************************************************************************
 * \brief   This function handles a click on PushButton_IncrementNumberRows.                                                                        *
 *                                                                                                                                                  *
 * \details This function increments the number of rows. Afterwards, the function corrects the number of columns, checks and draws the Battle Map   *
 *          grid if the widget RadioButton_SourceBattleMap is checked, or checks the Battle Map grid and shows the empty Battle Map image if the    *
 *          widget RadioButton_EmptyBattleMap is checked.                                                                                           *
 *                                                                                                                                                  *
 * \return  This function does not have any return value.                                                                                           *
 ****************************************************************************************************************************************************/
void Dialog_NewBattleMap::released_PushButton_IncrementNumberRows()
{
    qDebug() << "..." << __func__;

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

/*!**************************************************************************************************************************************************
 * \brief   This function handles a click on PushButton_DecrementNumberColumns.                                                                     *
 *                                                                                                                                                  *
 * \details This function decrements the number of columns. Afterwards, the function enables or disables the widget                                 *
 *          PushButton_DecrementNumberColumns depending on whether the number of columns is greater than 0. Finally, the function corrects the      *
 *          number of rows, checks and draws the Battle Map grid if the widget RadioButton_SourceBattleMap is checked, or checks the Battle Map     *
 *          grid and shows the empty Battle Map image if the widget RadioButton_EmptyBattleMap is checked.                                          *
 *                                                                                                                                                  *
 * \return  This function does not have any return value.                                                                                           *
 ****************************************************************************************************************************************************/
void Dialog_NewBattleMap::released_PushButton_DecrementNumberColumns()
{
    qDebug() << "..." << __func__;

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

/*!**************************************************************************************************************************************************
 * \brief   This function handles a click on PushButton_IncrementNumberColumns.                                                                     *
 *                                                                                                                                                  *
 * \details This function increments the number of columns. Afterwards, the function corrects the number of rows, checks and draws the Battle Map   *
 *          grid if the widget RadioButton_SourceBattleMap is checked, or checks the Battle Map grid and shows the empty Battle Map image if the    *
 *          widget RadioButton_EmptyBattleMap is checked.                                                                                           *
 *                                                                                                                                                  *
 * \return  This function does not have any return value.                                                                                           *
 ****************************************************************************************************************************************************/
void Dialog_NewBattleMap::released_PushButton_IncrementNumberColumns()
{
    qDebug() << "..." << __func__;

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

/*!**************************************************************************************************************************************************
 * \brief   This function handles the selection of a Battle Map square.                                                                             *
 *                                                                                                                                                  *
 * \details This function determines the edge lengths of the selected Battle Map square and their average value. If the average edge length is not  *
 *          greater than 0, no Battle Map square has been selected and the function resets the number of rows and columns, disables the push button *
 *          from DialogButtonBox with AcceptRole and removes the current Battle Map grid. Otherwise, the function optimizes the edge length by      *
 *          performing a modulo operation with the height of the Battle Map image and the edge length with the goal of minimizing the residual to   *
 *          0. This is done twice by incrementing and decrementing the edge length. The edge length that results from the optimization with fewer   *
 *          iterations is then used for the calculation of the number of rows and columns considering the size of the Battle Map image. Afterwards, *
 *          the function enables the widgets for editing of numbers of rows and columns and the push button from DialogButtonBox with AcceptRole.   *
 *          The function checks and draws the Battle Map grid. Finally, the function shows a question message box which asks the user to check the  *
 *          Battle Map grid and readjust the number of rows and columns in case of mismatch.                                                        *
 *                                                                                                                                                  *
 * \return  This function does not have any return value.                                                                                           *
 ****************************************************************************************************************************************************/
void Dialog_NewBattleMap::selected_BattleMapSquare()
{
    qDebug() << "..." << __func__;

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


        /* edge length that results from the optimization with fewer iterations is used */
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

        pBattleMapScene->removeBattleMapLines();
    }
}

/*!**************************************************************************************************************************************************
 * \brief   This function handles a state change of CheckBox_DrawBattleMapGrid.                                                                     *
 *                                                                                                                                                  *
 * \details This function redraws the Battle Map grid.                                                                                              *
 *                                                                                                                                                  *
 * \return  This function does not have any return value.                                                                                           *
 ****************************************************************************************************************************************************/
void Dialog_NewBattleMap::stateChanged_CheckBox_DrawBattleMapGrid(int state)
{
    qDebug() << "..." << __func__;

    Q_UNUSED(state);

    drawBattleMapGrid();
}

/*!**************************************************************************************************************************************************
 * \brief   This function handles a click on the push button from DialogButtonBox with AcceptRole.                                                  *
 *                                                                                                                                                  *
 * \details If the widget CheckBox_DrawBattleMapGrid is checked, this function draws the selected Battle Map on the Battle Map image. Afterwards,   *
 *          it extracts each Battle Map square from the Battle Map image, scales it to the configured size and stores it in the Battle Map object.  *
 *                                                                                                                                                  *
 * \return  This function does not have any return value.                                                                                           *
 ****************************************************************************************************************************************************/
void Dialog_NewBattleMap::accepted_DialogButtonBox()
{
    qDebug() << "..." << __func__;

    /* draw the selected Battle Map grid on the Battle Map image */
    if (pUserInterface->CheckBox_DrawBattleMapGrid->isChecked())
    {
        QPixmap temporaryPixmap(pBattleMapImagePixMap->pixmap());
        QPainter *painter = new QPainter(&temporaryPixmap);
        painter->setPen(QPen(BATTLEMAPGRID_COLOR, BATTLEMAPGRID_LINEWIDTH, Qt::SolidLine));
        QList<QGraphicsLineItem*> battleMapLinesToDraw = pBattleMapScene->getBattleMapLinesToDraw();
        for (quint32 lineIdx = 0U; lineIdx < battleMapLinesToDraw.count(); lineIdx++)
        {
            painter->drawLine(battleMapLinesToDraw.at(lineIdx)->line());
        }
        delete painter;

        pBattleMapImagePixMap->setPixmap(temporaryPixmap);
    }

    quint32 edgeLength = pBattleMapImagePixMap->pixmap().height() / pBattleMap->getNumberRows();

    for (quint32 rowIdx = 0U; rowIdx < pBattleMap->getNumberRows(); rowIdx++)
    {
        for (quint32 columnIdx = 0U; columnIdx < pBattleMap->getNumberColumns(); columnIdx++)
        {
            /* extract Battle Map square and scale it to configured size */
            QGraphicsPixmapItem * temporaryGraphicsPixmapItem = new QGraphicsPixmapItem();
            temporaryGraphicsPixmapItem->setPixmap(pBattleMapImagePixMap->pixmap().copy(QRect(columnIdx * edgeLength, rowIdx * edgeLength, edgeLength, edgeLength)));
            temporaryGraphicsPixmapItem->setPixmap(temporaryGraphicsPixmapItem->pixmap().scaled(QSize(BATTLEMAPSQUARE_SIZE, BATTLEMAPSQUARE_SIZE)));

            pBattleMap->setIndexedBattleMapSquarePixmap(rowIdx, temporaryGraphicsPixmapItem);
        }
    }

    this->accept();
}

/****************************************************************************************************************************************************
 * DEFINITION OF PRIVATE FUNCTIONS                                                                                                                  *
 ****************************************************************************************************************************************************/

/*!**************************************************************************************************************************************************
 * \brief   This function shows the empty Battle Map image.                                                                                         *
 *                                                                                                                                                  *
 * \details This function resets and reconnects the Battle Map scene. Afterwards, it loads the image of an empty Battle Map square from the         *
 *          configured file path and checks it for validity. If the loaded file is no image or it is but has no square format, the function shows a *
 *          warning message box. Otherwise, the function scales the Battle Map square image to the configured size and constructs the empty Battle  *
 *          Map image from a number of empty Battle Map squares according to the number of rows and columns. Finally, the function adds the empty   *
 *          Battle Map image to the Battle Map scene and draws the Battle Map grid.                                                                 *
 *                                                                                                                                                  *
 * \return  This function does not have any return value.                                                                                           *
 ****************************************************************************************************************************************************/
void Dialog_NewBattleMap::showEmptyBattleMapImage()
{
    qDebug() << "..." << __func__;

    QMessageBox msgBox(this);

    /* reset and reconnect Battle Map scene */
    delete pBattleMapScene;
    pBattleMapScene = new BattleMapScene();
    connect(pBattleMapScene, SIGNAL(selected_BattleMapSquare()), this, SLOT(selected_BattleMapSquare()));
    pUserInterface->GraphicsView_BattleMap->setScene(pBattleMapScene);

    QImage emptyBattleMapSquare(EMPTY_BATTLEMAPSQUARE_SOURCE);

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
        emptyBattleMapSquare = emptyBattleMapSquare.scaledToWidth(BATTLEMAPSQUARE_SIZE);

        /* construct the empty Battle Map image from a number of empty Battle Map squares according to the number of rows and columns */
        QPixmap temporaryPixmap(QSize(pBattleMap->getNumberColumns()* BATTLEMAPSQUARE_SIZE, pBattleMap->getNumberRows() * BATTLEMAPSQUARE_SIZE));
        QPainter *painter = new QPainter(&temporaryPixmap);
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
        pBattleMapImagePixMap->setPixmap(temporaryPixmap);

        pBattleMapScene->addItem(pBattleMapImagePixMap);
        pBattleMapScene->setSceneRect(0, 0, pBattleMapImagePixMap->pixmap().width(), pBattleMapImagePixMap->pixmap().height());

        drawBattleMapGrid();

        pUserInterface->GraphicsView_BattleMap->show();
    }
}

/*!**************************************************************************************************************************************************
 * \brief   This function shows the Battle Map image from the selected source.                                                                      *
 *                                                                                                                                                  *
 * \details This function resets and reconnects the Battle Map scene. Afterwards, it loads the Battle Map image from the selected source and checks *
 *          it for validity. If the loaded file is no image, the function shows a warning message box. Otherwise, the function adds the Battle Map  *
 *          image to the Battle Map scene and shows a question message box that asks the user to select a Battle Map square in order to determine   *
 *          the number of rows and columns of the Battle Map.                                                                                       *
 *                                                                                                                                                  *
 * \return  This function does not have any return value.                                                                                           *
 ****************************************************************************************************************************************************/
void Dialog_NewBattleMap::showSourceBattleMapImage()
{
    qDebug() << "..." << __func__;

    QMessageBox msgBox(this);

    /* reset and reconnect Battle Map scene */
    delete pBattleMapScene;
    pBattleMapScene = new BattleMapScene();
    connect(pBattleMapScene, SIGNAL(selected_BattleMapSquare()), this, SLOT(selected_BattleMapSquare()));
    pUserInterface->GraphicsView_BattleMap->setScene(pBattleMapScene);

    QImage battleMapImage(pUserInterface->LineEdit_Source->text());

    if (battleMapImage.isNull())
    {
        pBattleMapScene->addText("Selected source file is no image file.");

        msgBox.setWindowTitle("Invalid file");
        msgBox.setText("Selected source file is no image file.");
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

/*!**************************************************************************************************************************************************
 * \brief   This function corrects the number of rows considering the Battle Map squares aspect ratio.                                              *
 *                                                                                                                                                  *
 * \details If the number of columns is greater than 0, this function corrects the number of rows considering the Battle Map squares aspect ratio.  *
 *          Afterwards, the function enables or disables the widget PushButton_DecrementNumberRows depending on whether the number of rows is       *
 *          greater than 0.                                                                                                                         *
 *                                                                                                                                                  *
 * \return  This function does not have any return value.                                                                                           *
 ****************************************************************************************************************************************************/
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

/*!**************************************************************************************************************************************************
 * \brief   This function corrects the number of columns considering the Battle Map squares aspect ratio.                                           *
 *                                                                                                                                                  *
 * \details If the number of rows is greater than 0, this function corrects the number of columns considering the Battle Map squares aspect ratio.  *
 *          Afterwards, the function enables or disables the widget PushButton_DecrementNumberColumns depending on whether the number of rows is    *
 *          greater than 0.                                                                                                                         *
 *                                                                                                                                                  *
 * \return  This function does not have any return value.                                                                                           *
 ****************************************************************************************************************************************************/
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

/*!**************************************************************************************************************************************************
 * \brief   This function checks the Battle Map grid for validity.                                                                                  *
 *                                                                                                                                                  *
 * \details This function checks the Battle Map grid for validity and sets the background color of the widgets LineEdit_NumberRows and              *
 *          LineEdit_NumberColumns to red if the number of rows and columns do not match the Battle Map image size. Afterwards, the function        *
 *          enables or disables the widget PushButton_DecrementNumberRows depending on whether the Battle Map grid is valid or not.                 *
 *                                                                                                                                                  *
 * \return  This function does not have any return value.                                                                                           *
 ****************************************************************************************************************************************************/
void Dialog_NewBattleMap::checkBattleMapGrid()
{
    qDebug() << "..." << __func__;

    bool validBattleMapGrid = true;

    if ((0U < pBattleMap->getNumberRows()) && (0U < pBattleMap->getNumberColumns()))
    {
        if (pUserInterface->RadioButton_SourceBattleMap->isChecked())
        {
            quint32 edgeLengthHeigth = pBattleMapImagePixMap->pixmap().height() / pBattleMap->getNumberRows();
            quint32 edgeLengthWidth = pBattleMapImagePixMap->pixmap().width() / pBattleMap->getNumberColumns();

            if (edgeLengthHeigth == edgeLengthWidth)
            {
                /* set background color of LineEdit_NumberRows to red if number of rows does not match the Battle Map image size */
                if ((edgeLengthHeigth * pBattleMap->getNumberRows()) != static_cast<quint32>(pBattleMapImagePixMap->pixmap().height()))
                {
                    pUserInterface->LineEdit_NumberRows->setStyleSheet(QString("#%1 { background-color: red; }").arg(pUserInterface->LineEdit_NumberRows->objectName()));
                    validBattleMapGrid = false;
                }
                else
                {
                    pUserInterface->LineEdit_NumberRows->setStyleSheet("");
                }

                /* set background color of LineEdit_NumberColumns to red if number of columns does not match the Battle Map image size */
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
    pUserInterface->DialogButtonBox->button(QDialogButtonBox::Ok)->setEnabled(validBattleMapGrid);
}

/*!**************************************************************************************************************************************************
 * \brief   This function draws the Battle Map grid.                                                                                                *
 *                                                                                                                                                  *
 * \details This function removes the current Battle Map grid and redraws it depending on the number of rows and columns if both are greater than   *
 *          0. If the widget CheckBox_DrawBattleMapGrid is checked, the function draws solid lines using the configured pen options. Otherwise, the *
 *          function draws dotted lines.                                                                                                            *
 *                                                                                                                                                  *
 * \return  This function does not have any return value.                                                                                           *
 ****************************************************************************************************************************************************/
void Dialog_NewBattleMap::drawBattleMapGrid()
{
    qDebug() << "..." << __func__;

    QPen pen;
    quint32 edgeLength;

    pBattleMapScene->removeBattleMapLines();

    if (pUserInterface->CheckBox_DrawBattleMapGrid->isChecked())
    {
        pen = QPen(BATTLEMAPGRID_COLOR, BATTLEMAPGRID_LINEWIDTH, Qt::SolidLine);
    }
    else
    {
        pen = QPen(Qt::black, 3, Qt::DotLine);
    }

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
