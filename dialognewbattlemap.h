#ifndef DIALOGNEWBATTLEMAP_H
#define DIALOGNEWBATTLEMAP_H

/****************************************************************************************************************************************************
 * INCLUDES                                                                                                                                         *
 ****************************************************************************************************************************************************/

#include <QDialog>
#include <QFileDialog>
#include <QFrame>
#include <QGraphicsScene>
#include <QMessageBox>
#include <QPalette>

#include "battlemap.h"
#include "battlemapscenesquareselection.h"
#include "defines.h"
#include "screencalc.h"

/****************************************************************************************************************************************************
 * CLASS DECLARATION                                                                                                                                *
 ****************************************************************************************************************************************************/

namespace Ui
{
    class DialogNewBattleMap;
}

/*!
 * \brief This class implements the functionality needed for the creation of a new Battle Map.
 */
class DialogNewBattleMap : public QDialog
{
    Q_OBJECT

public:

    /*! *********************************************************************************************************************************************
     * \brief   This function is the constructor of the class DialogNewBattleMap.                                                                   *
     *                                                                                                                                              *
     * \details This function sets up the user interface, sets the background color of the graphics view to the window color and connects the       *
	 *          signals and slots of the user interface widgets. Afterwards, it handles the toggle of radioButtonSourceBattleMap as                 *
	 *          radioButtonSourceBattleMap is checked by default.                                                                                   *
     *                                                                                                                                              *
     * \param   parent                        Parent of the class DialogNewBattleMap                                                                *
     *                                                                                                                                              *
     * \return  This function does not have any return value.                                                                                       *
     ************************************************************************************************************************************************/
    DialogNewBattleMap(QWidget *parent = nullptr);

    /*! *********************************************************************************************************************************************
     * \brief   This function is the destructor of the class DialogNewBattleMap.                                                                    *
     *                                                                                                                                              *
     * \details This function deletes the objects created in the constructor.                                                                       *
     *                                                                                                                                              *
     * \return  This function does not have any return value.                                                                                       *
     ************************************************************************************************************************************************/
    ~DialogNewBattleMap();

    /*! *********************************************************************************************************************************************
     * \brief   This function returns the address of the newly created Battle Map object.                                                           *
     *                                                                                                                                              *
     * \details -                                                                                                                                   *
     *                                                                                                                                              *
     * \return  This function returns the address of the newly created Battle Map object.                                                           *
     ************************************************************************************************************************************************/
    BattleMap * getBattleMap() const;

protected: /* - */

signals: /* - */

private slots:

    /*! *********************************************************************************************************************************************
     * \brief   This function handles a toggle of radioButtonSourceBattleMap.                                                                       *
     *                                                                                                                                              *
     * \details If radioButtonSourceBattleMap is checked, this function enables, disables and resets the widgets according to their functional role *
	 *          for the Battle Map image source selection. Afterwards, it resets and reconnects the Battle Map scene, sets the Battle Map scene to  *
	 *          the graphics view and adds a text asking the user to select a source.                                                               *
     *                                                                                                                                              *
     * \param   checked                       State of radioButtonSourceBattleMap                                                                   *
     *                                                                                                                                              *
     * \return  This function does not have any return value.                                                                                       *
     ************************************************************************************************************************************************/
    void toggledRadioButtonSourceBattleMap(bool checked);

    /*! *********************************************************************************************************************************************
     * \brief   This function handles a toggle of radioButtonEmptyBattleMap.                                                                        *
     *                                                                                                                                              *
     * \details If radioButtonEmptyBattleMap is checked, this function enables, disables and resets the widgets according to their functional role  *
	 *          for the creation of an empty Battle Map. Afterwards, the function calculates the maximum number of rows and columns displayable on  *
	 *          the player screen and shows the corresponding empty Battle Map image.                                                               *
     *                                                                                                                                              *
     * \param   checked                       State of radioButtonEmptyBattleMap                                                                    *
     *                                                                                                                                              *
     * \return  This function does not have any return value.                                                                                       *
     ************************************************************************************************************************************************/
    void toggledRadioButtonEmptyBattleMap(bool checked);

    /*! *********************************************************************************************************************************************
     * \brief   This function handles the editing of lineEditSource.                                                                                *
     *                                                                                                                                              *
     * \details If the text string of lineEditSource is not empty after editing, this function resets the number of Battle Map rows and columns     *
     *          and shows the Battle Map image from the selected source.                                                                            *
     *                                                                                                                                              *
     * \return  This function does not have any return value.                                                                                       *
     ************************************************************************************************************************************************/
    void editingFinishedLineEditSource();

    /*! *********************************************************************************************************************************************
     * \brief   This function handles a click on pushButtonSelectSource.                                                                            *
     *                                                                                                                                              *
     * \details This function selects a source via a file dialog, synchronises the file path of the selected source with the text string of         *
	 *          lineEditSource and handles the editing of lineEditSource afterwards.                                                                *
     *                                                                                                                                              *
     * \return  This function does not have any return value.                                                                                       *
     ************************************************************************************************************************************************/
    void releasedPushButtonSelectSource();

    /*! *********************************************************************************************************************************************
     * \brief   This function handles the editing of lineEditNumberRows.                                                                            *
     *                                                                                                                                              *
     * \details This function checks the text string of lineEditNumberRows for a valid format and updates the number of rows according to the input *
	 *          value if the text string is interpretable as positive number. In case of an invalid format or a negative number, it shows a message *
	 *          box. Afterwards, it enables or disables the push button for decrement depending on the current number of rows. If                   *
	 *          radioButtonSourceBattleMap is checked, it corrects the number of columns considering the Battle Map image aspect ratio, checks if   *
	 *          the Battle Map grid covers the complete Battle Map image (which affects push button with AcceptRole) and draws the Battle Map grid. *
	 *          Otherwise, it checks if the number of rows and columns are both greater 0 (which affects push button with AcceptRole) and shows the *
	 *          empty Battle Map image.                                                                                                             *
     *                                                                                                                                              *
     * \return  This function does not have any return value.                                                                                       *
     ************************************************************************************************************************************************/
    void editingFinishedLineEditNumberRows();

    /*! *********************************************************************************************************************************************
     * \brief   This function handles the editing of lineEditNumberColumns.                                                                         *
     *                                                                                                                                              *
     * \details This function checks the text string of lineEditNumberColumns for a valid format and updates the number of columns according to the *
	 *          input value if the text string is interpretable as positive number. In case of an invalid format or a negative number, it shows a   *
	 *          message box. Afterwards, it enables or disables the push button for decrement depending on the current number of columns. If        *
	 *          radioButtonSourceBattleMap is checked, it corrects the number of rows considering the Battle Map image aspect ratio, checks if the  *
	 *          Battle Map grid covers the complete Battle Map image (which affects push button with AcceptRole) and draws the Battle Map grid.     *
	 *          Otherwise, it checks if the number of rows and columns are both greater 0 (which affects push button with AcceptRole) and shows the *
	 *          empty Battle Map image.                                                                                                             *
     *                                                                                                                                              *
     * \return  This function does not have any return value.                                                                                       *
     ************************************************************************************************************************************************/
    void editingFinishedLineEditNumberColumns();

    /*! *********************************************************************************************************************************************
     * \brief   This function handles a click on pushButtonDecrementNumberRows.                                                                     *
     *                                                                                                                                              *
     * \details This function decrements the number of rows. Afterwards, it enables or disables the push button for decrement depending on the      *
	 *          current number of rows. If radioButtonSourceBattleMap is checked, it corrects the number of columns considering the Battle Map      *
	 *          image aspect ratio, checks if the Battle Map grid covers the complete Battle Map image (which affects push button with AcceptRole)  *
	 *          and draws the Battle Map grid. Otherwise, it checks if the number of rows and columns are both greater 0 (which affects push button *
	 *          with AcceptRole) and shows the empty Battle Map image.                                                                              *
     *                                                                                                                                              *
     * \return  This function does not have any return value.                                                                                       *
     ************************************************************************************************************************************************/
    void releasedPushButtonDecrementNumberRows();

    /*! *********************************************************************************************************************************************
     * \brief   This function handles a click on pushButtonIncrementNumberRows.                                                                     *
     *                                                                                                                                              *
     * \details This function increments the number of rows. If radioButtonSourceBattleMap is checked, it corrects the number of columns            *
	 *          considering the Battle Map image aspect ratio, checks if the Battle Map grid covers the complete Battle Map image (which affects    *
	 *          push button with AcceptRole) and draws the Battle Map grid. Otherwise, it checks if the number of rows and columns are both greater *
	 *          0 (which affects push button with AcceptRole) and shows the empty Battle Map image.                                                 *
     *                                                                                                                                              *
     * \return  This function does not have any return value.                                                                                       *
     ************************************************************************************************************************************************/
    void releasedPushButtonIncrementNumberRows();

    /*! *********************************************************************************************************************************************
     * \brief   This function handles a click on pushButtonDecrementNumberColumns.                                                                  *
     *                                                                                                                                              *
     * \details This function decrements the number of columns. Afterwards, it enables or disables the push button for decrement depending on the   *
	 *          current number of columns. If radioButtonSourceBattleMap is checked, it corrects the number of rows considering the Battle Map      *
	 *          image aspect ratio, checks if the Battle Map grid covers the complete Battle Map image (which affects push button with AcceptRole)  *
	 *          and draws the Battle Map grid. Otherwise, it checks if the number of rows and columns are both greater 0 (which affects push button *
	 *          with AcceptRole) and shows the empty Battle Map image.                                                                              *
     *                                                                                                                                              *
     * \return  This function does not have any return value.                                                                                       *
     ************************************************************************************************************************************************/
    void releasedPushButtonDecrementNumberColumns();

    /*! *********************************************************************************************************************************************
     * \brief   This function handles a click on pushButtonIncrementNumberColumns.                                                                  *
     *                                                                                                                                              *
     * \details This function increments the number of columns. If radioButtonSourceBattleMap is checked, it corrects the number of rows            *
	 *          considering the Battle Map image aspect ratio, checks if the Battle Map grid covers the complete Battle Map image (which affects    *
	 *          push button with AcceptRole) and draws the Battle Map grid. Otherwise, it checks if the number of rows and columns are both greater *
	 *          0 (which affects push button with AcceptRole) and shows the empty Battle Map image.                                                 *
     *                                                                                                                                              *
     * \return  This function does not have any return value.                                                                                       *
     ************************************************************************************************************************************************/
    void releasedPushButtonIncrementNumberColumns();

    /*! *********************************************************************************************************************************************
     * \brief   This function handles the selection of a Battle Map square.                                                                         *
     *                                                                                                                                              *
     * \details This function calculates the average edge length of the selected Battle Map square and initializes the average edge length and      *
	 *          counter values for increment and decrement optimization. If the average edge length is not greater 0, no valid Battle Map square    *
     *          has been selected and the function resets the numbers of rows and columns and the corresponding widgets, disables the push button   *
	 *          from DialogButtonBox with AcceptRole and removes the Battle Map grid. Otherwise, if a valid Battle Map square has been selected, it *
	 *          optimizes the edge length by performing a modulo operation with the height of the Battle Map image and the edge length with the     *
	 *          goal of minimizing the residual to 0. This is done twice by incrementing and decrementing the edge length. The edge length that     *
     *          results from the optimization with fewer iterations is kept. Afterwards, the function updates the numbers of rows and columns       *
     *          according to the optimized edge length of the Battle Map squares and checks if the calculated numbers of rows and columns are       *
     *          reasonable. If this is not the case, the function shows a message box asking the user to check the resolution accuracy of the       *
     *          selected Battle Map image. Otherwise, it enables the widgets for the editing of numbers of rows and columns for readjustment,       *
     *          checks if the Battle Map grid covers the complete Battle Map image (which affects push button with AcceptRole) and draws Battle Map *
     *          grid. Finally, the function shows a message box asking the user to check the Battle Map grid and readjust the numbers of rows and   *
     *          columns in case of a mismatch.                                                                                                      *
	 *                                                                                                                                              *
     * \return  This function does not have any return value.                                                                                       *
     ************************************************************************************************************************************************/
    void selectedBattleMapSquare();

    /*! *********************************************************************************************************************************************
     * \brief   This function draws the Battle Map grid.                                                                                            *
     *                                                                                                                                              *
     * \details This function removes the current Battle Map grid and sets the pen properties according to the state of checkBoxDrawBattleMapGrid.  *
	 *          If the number of rows and columns are both greater than 0, it draws the horizontal and vertical Battle Map lines and adds them to   *
	 *          the Battle Map scene.                                                                                                               *
	 *                                                                                                                                              *
	 * \param   state                         State of checkBoxDrawBattleMapGrid (unused, only for convenience when used as private slot function)  *
     *                                                                                                                                              *
     * \return  This function does not have any return value.                                                                                       *
     ************************************************************************************************************************************************/
    void drawBattleMapGrid(int state = 0);

    /*! *********************************************************************************************************************************************
     * \brief   This function handles a click on the push button from dialogButtonBox with AcceptRole.                                              *
     *                                                                                                                                              *
     * \details This function first sets the wait cursor as the following process may take some time. If the widget checkBoxDrawBattleMapGrid is    *
	 *          checked, it draws the Battle Map grid on theBattle Map image. Afterwards, it extracts the pixmap of each Battle Map square from the *
	 *          Battle Map image, scales it to the configured size and adds it to the Battle Map. Finally, the function emits the signal            *
	 *          accepted().                                                                                                                         *
     *                                                                                                                                              *
     * \return  This function does not have any return value.                                                                                       *
     ************************************************************************************************************************************************/
    void acceptedDialogButtonBox();

    /*! *********************************************************************************************************************************************
     * \brief   This function handles a click on the push button from dialogButtonBox with RejectRole.                                              *
     *                                                                                                                                              *
     * \details This function emits the signal rejected().                                                                                          *
     *                                                                                                                                              *
     * \return  This function does not have any return value.                                                                                       *
     ************************************************************************************************************************************************/
    void rejectedDialogButtonBox();

    /*! *********************************************************************************************************************************************
     * \brief   This function handles a click on the close button.                                                                                  *
     *                                                                                                                                              *
     * \details This function handles a click on the close button as a click on the push button from dialogButtonBox with RejectRole.               *
     *                                                                                                                                              *
     * \return  This function does not have any return value.                                                                                       *
     ************************************************************************************************************************************************/
    void reject();

    /*! *********************************************************************************************************************************************
     * \brief   This function updates the member variable m_scaleFactor and redraws the Battle Map grid.                                            *
     *                                                                                                                                              *
     * \details This function redraws the Battle Map grid with the new scale factor and sets the new scale factor to the Battle Map scene.          *
     *                                                                                                                                              *
     * \return  This function does not have any return value.                                                                                       *
     ************************************************************************************************************************************************/
    void changedScaleFactor(qreal scaleFactor);

private:

    /*! *********************************************************************************************************************************************
     * \brief   This function shows the empty Battle Map image.                                                                                     *
     *                                                                                                                                              *
     * \details This function resets and reconnects the Battle Map scene and resets the graphics view. Afterwards, it loads the image of an empty   *
	 *          Battle Map square and scales it to the configured size. If the number of rows and columns are both greater 0, it constructs the     *
	 *          empty Battle Map image from a number of empty Battle Map squares according to the number of rows and columns. Finally, the function *
	 *          adds the empty Battle Map image to the Battle Map scene, draws the Battle Map grid and enables the event processing of the graphics *
	 *          view as soon as the Battle Map image is shown.                                                                                      *
     *                                                                                                                                              *
     * \return  This function does not have any return value.                                                                                       *
     ************************************************************************************************************************************************/
    void showEmptyBattleMapImage();

    /*! *********************************************************************************************************************************************
     * \brief   This function shows the Battle Map image from the selected source.                                                                  *
     *                                                                                                                                              *
     * \details This function resets and reconnects the Battle Map scene and resets the graphics view. Afterwards, it loads the Battle Map image    *
	 *          from the selected source and checks it for validity. If the loaded file is no image, the function adds a text to the Battle Map     *
	 *          scene and shows a message box both informing the user that the selected source file is no image file. Otherwise, it prepares the    *
	 *          graphics view for the selection of a Battle Map square, adds the Battle Map image to the Battle Map scene and shows a message box   *
	 *          asking the user to select a Battle Map square in order to determine the number of rows and columns of the Battle Map. Finally, it   *
	 *          enables the event processing of the graphics view as soon as the Battle Map image is shown.                                         *
     *                                                                                                                                              *
     * \return  This function does not have any return value.                                                                                       *
     ************************************************************************************************************************************************/
    void showSourceBattleMapImage();

    /*! *********************************************************************************************************************************************
     * \brief   This function corrects the number of rows considering the Battle Map squares aspect ratio.                                          *
     *                                                                                                                                              *
     * \details If the number of columns is greater than 0, this function corrects the number of rows considering the Battle Map squares aspect     *
     *          ratio. Afterwards, it enables or disables the push button for decrement depending on the current number of rows.                    *
     *                                                                                                                                              *
     * \return  This function does not have any return value.                                                                                       *
     ************************************************************************************************************************************************/
    void correctNumberRows();

    /*! *********************************************************************************************************************************************
     * \brief   This function corrects the number of columns considering the Battle Map squares aspect ratio.                                       *
     *                                                                                                                                              *
     * \details If the number of rpws is greater than 0, this function corrects the number of columns considering the Battle Map squares aspect     *
     *          ratio. Afterwards, it enables or disables the push button for decrement depending on the current number of columns.                 *
     *                                                                                                                                              *
     * \return  This function does not have any return value.                                                                                       *
     ************************************************************************************************************************************************/
    void correctNumberColumns();

    /*! *********************************************************************************************************************************************
     * \brief   This function checks the Battle Map grid for validity.                                                                              *
     *                                                                                                                                              *
     * \details This function first checks if the number of rows and columns are both greater 0 (which affects push button with AcceptRole). If so, *
	 *          it calculates the height and width of the Battle Map squares and checks, if they are equal. If this is not the case, the aspect     *
	 *          ratio of the Battle Map squares is invalid, and the function sets the background color of lineEditNumberRows and                    *
	 *          lineEditNumberColumns to red. Otherwise, if the aspect ratio of the Battle Map squares is valid, it checks if the number of rows    *
	 *          and columns match the Battle Map image size. If the number of rows or columns does not match the Battle Map image size, the         *
	 *          function sets the background color of lineEditNumberRows or lineEditNumberColumns to red. Otherwise, it resets the background color *
	 *          of lineEditNumberRows or lineEditNumberColumns. Finally, the function enables or disables the push button with AcceptRole depending *
	 *          on whether the Battle Map grid is valid or not.                                                                                     *
     *                                                                                                                                              *
     * \return  This function does not have any return value.                                                                                       *
     ************************************************************************************************************************************************/
    void checkBattleMapGrid();

    /*! *********************************************************************************************************************************************
     * \brief   This function checks the numbers of rows and columns for validity.                                                                  *
     *                                                                                                                                              *
     * \details This function checks the numbers of rows and columns for validity and enables or disables the push button with AcceptRole depending *
	 *          on whether the numbers of rows and columns are both greater 0 or not.                                                               *
     *                                                                                                                                              *
     * \return  This function returns true, if both the numbers of rows and columns are greater 0. Otherwise, it returns false.                     *
     ************************************************************************************************************************************************/
    bool checkNumberRowsAndColumns();

    /*! *********************************************************************************************************************************************
     * \brief   This function removes the Battle Map grid.                                                                                          *
     *                                                                                                                                              *
     * \details This function removes all graphics items of m_battleMapLinesToDraw from the Battle Map scene and clears m_battleMapLinesToDraw      *
	 *          afterwards.                                                                                                                         *
     *                                                                                                                                              *
     * \return  This function does not have any return value.                                                                                       *
     ************************************************************************************************************************************************/
    void removeBattleMapGrid();

    /*! *********************************************************************************************************************************************
     * \brief   This function deletes the Battle Map scene.                                                                                         *
     *                                                                                                                                              *
     * \details This function removes the Battle Map grid and all remaining graphics items from the Battle Map scene and deletes m_battleMapScene   *
	 *          afterwards.                                                                                                                         *
     *                                                                                                                                              *
     * \return  This function does not have any return value.                                                                                       *
     ************************************************************************************************************************************************/
    void deleteBattleMapScene();

    /*!
     * \brief This is a pointer to the user interface of the class DialogNewBattleMap.
     */
    Ui::DialogNewBattleMap *m_userInterface;

    /*!
     * \brief This is a pointer to the Battle Map scene that is set to GraphicsViewBattleMap.
     */
    BattleMapSceneSquareSelection *m_battleMapScene;

    /*!
     * \brief This is the text to be shown in the Battle Map scene.
     */
    QGraphicsTextItem m_sceneText;

    /*!
     * \brief This is the pixmap of the Battle Map image.
     */
    QGraphicsPixmapItem m_battleMapImagePixMap;

    /*!
     * \brief This is a list of Battle Map lines building the Battle Map grid to be drawn for control purposes.
     */
    QList<QGraphicsLineItem*> m_battleMapLinesToDraw;

    /*!
     * \brief This is the factor that is used for scaling the graphics view while scrolling.
     */
    qreal m_scaleFactor;

    /*!
     * \brief This is a pointer to the newly created Battle Map.
     */
    BattleMap *m_battleMap;
};

#endif // DIALOGNEWBATTLEMAP_H
