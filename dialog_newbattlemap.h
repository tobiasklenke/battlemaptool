#ifndef DIALOG_NEWBATTLEMAP_H
#define DIALOG_NEWBATTLEMAP_H

/****************************************************************************************************************************************************
 * INCLUDES                                                                                                                                         *
 ****************************************************************************************************************************************************/

#include <QDialog>
#include <QFileDialog>
#include <QGraphicsPixmapItem>
#include <QGraphicsScene>
#include <QMessageBox>

#include "battlemap.h"
#include "battlemapscene.h"
#include "defines.h"
#include "screencalc.h"

/****************************************************************************************************************************************************
 * CLASS DECLARATION                                                                                                                                *
 ****************************************************************************************************************************************************/

namespace Ui
{
    class Dialog_NewBattleMap;
}

/*!**************************************************************************************************************************************************
 * \brief This class implements the functionality needed for the creation of a new Battle Map.                                                      *
 ****************************************************************************************************************************************************/
class Dialog_NewBattleMap : public QDialog
{
    Q_OBJECT

public:

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
    Dialog_NewBattleMap(QWidget *parent = nullptr);

/*!**************************************************************************************************************************************************
 * \brief   This function is the destructor of the class Dialog_NewBattleMap.                                                                       *
 *                                                                                                                                                  *
 * \details This function deletes the objects pointed to by pUserInterface, pBattleMapScene and pBattleMap.                                         *
 *                                                                                                                                                  *
 * \return  This function does not have any return value.                                                                                           *
 ****************************************************************************************************************************************************/
    ~Dialog_NewBattleMap();

/*!**************************************************************************************************************************************************
 * \brief   This function returns the address of the newly created Battle Map object.                                                               *
 *                                                                                                                                                  *
 * \details -                                                                                                                                       *
 *                                                                                                                                                  *
 * \return  This function returns the address of the newly created Battle Map object.                                                               *
 ****************************************************************************************************************************************************/
    BattleMap * getBattleMap() const;

private slots:

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
    void toggled_RadioButton_SourceBattleMap(bool checked);

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
    void toggled_RadioButton_EmptyBattleMap(bool checked);

/*!**************************************************************************************************************************************************
 * \brief   This function handles the editing of LineEdit_Source.                                                                                   *
 *                                                                                                                                                  *
 * \details If the text string of LineEdit_Source is not empty after editing, this function shows the Battle Map image from the selected source.    *
 *                                                                                                                                                  *
 * \return  This function does not have any return value.                                                                                           *
 ****************************************************************************************************************************************************/
    void editingFinished_LineEdit_Source();

/*!**************************************************************************************************************************************************
 * \brief   This function handles a click on PushButton_SelectSource.                                                                               *
 *                                                                                                                                                  *
 * \details This function opens a file dialog in order to select the source file for the Battle Map image and synchronises the file path of the     *
 *          selected source with the text string of LineEdit_Source. Since LineEdit_Source is edited this way, the function calls the corresponding *
 *          function that handles the editing of LineEdit_Source.                                                                                   *
 *                                                                                                                                                  *
 * \return  This function does not have any return value.                                                                                           *
 ****************************************************************************************************************************************************/
    void released_PushButton_SelectSource();

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
    void editingFinished_LineEdit_NumberRows();

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
    void editingFinished_LineEdit_NumberColumns();

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
    void released_PushButton_DecrementNumberRows();

/*!**************************************************************************************************************************************************
 * \brief   This function handles a click on PushButton_IncrementNumberRows.                                                                        *
 *                                                                                                                                                  *
 * \details This function increments the number of rows. Afterwards, the function corrects the number of columns, checks and draws the Battle Map   *
 *          grid if the widget RadioButton_SourceBattleMap is checked, or checks the Battle Map grid and shows the empty Battle Map image if the    *
 *          widget RadioButton_EmptyBattleMap is checked.                                                                                           *
 *                                                                                                                                                  *
 * \return  This function does not have any return value.                                                                                           *
 ****************************************************************************************************************************************************/
    void released_PushButton_IncrementNumberRows();

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
    void released_PushButton_DecrementNumberColumns();

/*!**************************************************************************************************************************************************
 * \brief   This function handles a click on PushButton_IncrementNumberColumns.                                                                     *
 *                                                                                                                                                  *
 * \details This function increments the number of columns. Afterwards, the function corrects the number of rows, checks and draws the Battle Map   *
 *          grid if the widget RadioButton_SourceBattleMap is checked, or checks the Battle Map grid and shows the empty Battle Map image if the    *
 *          widget RadioButton_EmptyBattleMap is checked.                                                                                           *
 *                                                                                                                                                  *
 * \return  This function does not have any return value.                                                                                           *
 ****************************************************************************************************************************************************/
    void released_PushButton_IncrementNumberColumns();

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
    void selected_BattleMapSquare();

/*!**************************************************************************************************************************************************
 * \brief   This function handles a state change of CheckBox_DrawBattleMapGrid.                                                                     *
 *                                                                                                                                                  *
 * \details This function redraws the Battle Map grid.                                                                                              *
 *                                                                                                                                                  *
 * \return  This function does not have any return value.                                                                                           *
 ****************************************************************************************************************************************************/
    void stateChanged_CheckBox_DrawBattleMapGrid(int state);

/*!**************************************************************************************************************************************************
 * \brief   This function handles a click on the push button from DialogButtonBox with AcceptRole.                                                  *
 *                                                                                                                                                  *
 * \details If the widget CheckBox_DrawBattleMapGrid is checked, this function draws the selected Battle Map on the Battle Map image. Afterwards,   *
 *          it extracts each Battle Map square from the Battle Map image, scales it to the configured size and stores it in the Battle Map object.  *
 *                                                                                                                                                  *
 * \return  This function does not have any return value.                                                                                           *
 ****************************************************************************************************************************************************/
    void accepted_DialogButtonBox();

private:

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
    void showEmptyBattleMapImage();

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
    void showSourceBattleMapImage();

/*!**************************************************************************************************************************************************
 * \brief   This function corrects the number of rows considering the Battle Map squares aspect ratio.                                              *
 *                                                                                                                                                  *
 * \details If the number of columns is greater than 0, this function corrects the number of rows considering the Battle Map squares aspect ratio.  *
 *          Afterwards, the function enables or disables the widget PushButton_DecrementNumberRows depending on whether the number of rows is       *
 *          greater than 0.                                                                                                                         *
 *                                                                                                                                                  *
 * \return  This function does not have any return value.                                                                                           *
 ****************************************************************************************************************************************************/
    void correctNumberRows();

/*!**************************************************************************************************************************************************
 * \brief   This function corrects the number of columns considering the Battle Map squares aspect ratio.                                           *
 *                                                                                                                                                  *
 * \details If the number of rows is greater than 0, this function corrects the number of columns considering the Battle Map squares aspect ratio.  *
 *          Afterwards, the function enables or disables the widget PushButton_DecrementNumberColumns depending on whether the number of rows is    *
 *          greater than 0.                                                                                                                         *
 *                                                                                                                                                  *
 * \return  This function does not have any return value.                                                                                           *
 ****************************************************************************************************************************************************/
    void correctNumberColumns();

/*!**************************************************************************************************************************************************
 * \brief   This function checks the Battle Map grid for validity.                                                                                  *
 *                                                                                                                                                  *
 * \details This function checks the Battle Map grid for validity and sets the background color of the widgets LineEdit_NumberRows and              *
 *          LineEdit_NumberColumns to red if the number of rows and columns do not match the Battle Map image size. Afterwards, the function        *
 *          enables or disables the widget PushButton_DecrementNumberRows depending on whether the Battle Map grid is valid or not.                 *
 *                                                                                                                                                  *
 * \return  This function does not have any return value.                                                                                           *
 ****************************************************************************************************************************************************/
    void checkBattleMapGrid();

/*!**************************************************************************************************************************************************
 * \brief   This function draws the Battle Map grid.                                                                                                *
 *                                                                                                                                                  *
 * \details This function removes the current Battle Map grid and redraws it depending on the number of rows and columns if both are greater than   *
 *          0. If the widget CheckBox_DrawBattleMapGrid is checked, the function draws solid lines using the configured pen options. Otherwise, the *
 *          function draws dotted lines.                                                                                                            *
 *                                                                                                                                                  *
 * \return  This function does not have any return value.                                                                                           *
 ****************************************************************************************************************************************************/
    void drawBattleMapGrid();

/*!**************************************************************************************************************************************************
 * \brief This is a pointer to the user interface of the class Dialog_NewBattleMap.                                                                 *
 ****************************************************************************************************************************************************/
    Ui::Dialog_NewBattleMap *pUserInterface;

/*!**************************************************************************************************************************************************
 * \brief This is a pointer to the BattleMapScene object that is set to GraphicsView_BattleMap.                                                     *
 ****************************************************************************************************************************************************/
    BattleMapScene *pBattleMapScene;

/*!**************************************************************************************************************************************************
 * \brief This is the pixmap of the Battle Map image.                                                                                               *
 ****************************************************************************************************************************************************/
    QGraphicsPixmapItem *pBattleMapImagePixMap;

/*!**************************************************************************************************************************************************
 * \brief This is a pointer to the newly created Battle Map.                                                                                        *
 ****************************************************************************************************************************************************/
    BattleMap * pBattleMap;
};

#endif // DIALOG_NEWBATTLEMAP_H
