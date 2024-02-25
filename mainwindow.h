#ifndef MAINWINDOW_H
#define MAINWINDOW_H

/****************************************************************************************************************************************************
 * INCLUDES                                                                                                                                         *
 ****************************************************************************************************************************************************/

#include <QActionGroup>
#include <QMainWindow>

#include "battlemap.h"
#include "battlemapscenesection.h"
#include "dialognewbattlemap.h"
#include "playerscreenhandler.h"
#include "masterscreenhandler.h"

/****************************************************************************************************************************************************
 * CLASS DECLARATION                                                                                                                                *
 ****************************************************************************************************************************************************/

QT_BEGIN_NAMESPACE
namespace Ui
{
    class MainWindow;
}
QT_END_NAMESPACE

/*!
 * \brief This class implements the main functionality of the application.
 */
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:

    /*! *********************************************************************************************************************************************
     * \brief   This function is the constructor of the class MainWindow.                                                                           *
     *                                                                                                                                              *
     * \details This function sets up the user interface, passes the graphics views and Battle Map scene sections to the master and player screen   *
	 *          handlers and creates the action groups for the operation mode and the wind rose orientation. Afterwards, it connects several        *
	 *          signals and slots. Finally, it makes the labels invisible so that they are not shown initially when there is no Battle Map and also *
	 *          makes the labels transparent for mouse events so that they do not process them instead of the graphics view.                        *
     *                                                                                                                                              *
     * \param   playerWindow                  Address of the graphics view to display the players window                                            *
     * \param   parent                        Parent of the class MainWindow                                                                        *
     *                                                                                                                                              *
     * \return  This function does not have any return value.                                                                                       *
     ************************************************************************************************************************************************/
    MainWindow(QGraphicsView *playerWindow, QWidget *parent = nullptr);

    /*! *********************************************************************************************************************************************
     * \brief   This function is the destructor of the class MainWindow.                                                                            *
     *                                                                                                                                              *
     * \details This function deletes the objects created in the constructor except m_dialogNewBattleMap.                                           *
     *                                                                                                                                              *
     * \return  This function does not have any return value.                                                                                       *
     ************************************************************************************************************************************************/
    ~MainWindow();

protected: /* - */

signals: /* - */

private slots:

    /*! *********************************************************************************************************************************************
     * \brief   This function handles the action actionNewBattleMap.                                                                                *
     *                                                                                                                                              *
     * \details This function creates the dialog DialogNewBattleMap and connects the signals and slots of the dialog button box actions of the      *
     *          dialog DialogNewBattleMap. Afterwards, it opens the dialog DialogNewBattleMap.                                                      *
     *                                                                                                                                              *
     * \return  This function does not have any return value.                                                                                       *
     ************************************************************************************************************************************************/
    void triggeredActionNewBattleMap();

    /*! *********************************************************************************************************************************************
     * \brief   This function handles the acceptance of the dialog DialogNewBattleMap.                                                              *
     *                                                                                                                                              *
     * \details This function first sets the wait cursor as the following process may take some time, stores the Battle Map from the accepted       *
	 *          dialog DialogNewBattleMap and deletes the dialog afterwards. Then, it resets the indexes of the first row and column of the Battle  *
	 *          Map scene section, checks whether the number of rows respectively columns displayable on the player screen is less than the total   *
	 *          number of rows respectively columns of the Battle Map and sets the number of rows respectively columns of the Battle Map scene      *
	 *          section to the less number. It shares the Battle Map with the screen handlers, shows the Battle Map image on the master screen and  *
	 *          initializes the Battle Map image on the player screen. Afterwards, it enables the actions that shall only be available when the     *
	 *          Battle Map is shared with the screen handlers and it also makes the label labelScaleFactor visible so that it is shown when Battle  *
	 *          Map is shared with the screen handlers. Finally, it resets the arrow cursor as the process which takes some time is completed.      *
     *                                                                                                                                              *
     * \return  This function does not have any return value.                                                                                       *
     ************************************************************************************************************************************************/
    void acceptedDialogNewBattleMap();

    /*! *********************************************************************************************************************************************
     * \brief   This function handles the rejection of the dialog DialogNewBattleMap.                                                               *
     *                                                                                                                                              *
     * \details This function deletes the dialog m_dialogNewBattleMap.                                                                              *
     *                                                                                                                                              *
     * \return  This function does not have any return value.                                                                                       *
     ************************************************************************************************************************************************/
    void rejectedDialogNewBattleMap();

    /*! *********************************************************************************************************************************************
     * \brief   This function handles the action actionUndo.                                                                                        *
     *                                                                                                                                              *
     * \details TODO                                                                                                                                *
     *                                                                                                                                              *
     * \return  This function does not have any return value.                                                                                       *
     ************************************************************************************************************************************************/
    void triggeredActionUndo();

    /*! *********************************************************************************************************************************************
     * \brief   This function handles the action actionRedo.                                                                                        *
     *                                                                                                                                              *
     * \details TODO                                                                                                                                *
     *                                                                                                                                              *
     * \return  This function does not have any return value.                                                                                       *
     ************************************************************************************************************************************************/
    void triggeredActionRedo();

    /*! *********************************************************************************************************************************************
     * \brief   This function handles the action actionInsertRowAbove.                                                                              *
     *                                                                                                                                              *
     * \details This function inserts a new row above the Battle Map. Afterwards, it checks whether the number of rows displayable on the player    *
	 *          screen is greater than or equal to the total number of rows of the Battle Map. If so, it increments the number of rows of the       *
	 *          Battle Map scene section. Otherwise, it increments the index of the first row of the Battle Map scene section. Finally, it calls    *
	 *          the respective functions of the screen handlers for inserting new Battle Map square graphics items.                                 *
     *                                                                                                                                              *
     * \return  This function does not have any return value.                                                                                       *
     ************************************************************************************************************************************************/
    void triggeredActionInsertRowAbove();

    /*! *********************************************************************************************************************************************
     * \brief   This function handles the action actionInsertRowBelow.                                                                              *
     *                                                                                                                                              *
     * \details This function inserts a new row below the Battle Map. Afterwards, it checks whether the number of rows displayable on the player    *
	 *          screen is greater than or equal to the total number of rows of the Battle Map. If so, it increments the number of rows of the       *
	 *          Battle Map scene section. Finally, it calls the respective functions of the screen handlers for inserting new Battle Map square     *
	 *          graphics items.                                                                                                                     *
     *                                                                                                                                              *
     * \return  This function does not have any return value.                                                                                       *
     ************************************************************************************************************************************************/
    void triggeredActionInsertRowBelow();

    /*! *********************************************************************************************************************************************
     * \brief   This function handles the action actionInsertColumnLeft.                                                                            *
     *                                                                                                                                              *
     * \details This function inserts a new column to the left of the Battle Map. Afterwards, it checks whether the number of columns displayable   *
	 *          on the player screen is greater than or equal to the total number of columns of the Battle Map. If so, it increments the number of  *
	 *          columns of the Battle Map scene section. Otherwise, it increments the index of the first column of the Battle Map scene section.    *
	 *          Finally, it calls the respective functions of the screen handlers for inserting new Battle Map square graphics items.               *
     *                                                                                                                                              *
     * \return  This function does not have any return value.                                                                                       *
     ************************************************************************************************************************************************/
    void triggeredActionInsertColumnLeft();

    /*! *********************************************************************************************************************************************
     * \brief   This function handles the action actionInsertColumnRight.                                                                           *
     *                                                                                                                                              *
     * \details This function inserts a new column to the right of the Battle Map. Afterwards, it checks whether the number of columns displayable  *
	 *          on the player screen is greater than or equal to the total number of columns of the Battle Map. If so, it increments the number of  *
	 *          columns of the Battle Map scene section. Finally, it calls the respective functions of the screen handlers for inserting new Battle *
	 *          Map square graphics items.                                                                                                          *
     *                                                                                                                                              *
     * \return  This function does not have any return value.                                                                                       *
     ************************************************************************************************************************************************/
    void triggeredActionInsertColumnRight();

    /*! *********************************************************************************************************************************************
     * \brief   This function handles the action actionDeleteRowAbove.                                                                              *
     *                                                                                                                                              *
     * \details This function deletes a row above the Battle Map. Afterwards, it checks whether the number of rows displayable on the player screen *
	 *          is greater than the total number of rows of the Battle Map. If so, it decrements the number of rows of the Battle Map scene         *
	 *          section. Otherwise, and if the index of the first row of the Battle Map scene section is greater than 0, it decrements the index of *
	 *          the first row of the Battle Map scene section. Finally, it calls the respective functions of the screen handlers for deleting       *
	 *          Battle Map square graphics items.                                                                                                   *
     *                                                                                                                                              *
     * \return  This function does not have any return value.                                                                                       *
     ************************************************************************************************************************************************/
    void triggeredActionDeleteRowAbove();

    /*! *********************************************************************************************************************************************
     * \brief   This function handles the action actionDeleteRowBelow.                                                                              *
     *                                                                                                                                              *
     * \details This function deletes a row below the Battle Map. Afterwards, it checks whether the number of rows displayable on the player screen *
	 *          is greater than the total number of rows of the Battle Map. If so, it decrements the number of rows of the Battle Map scene         *
	 *          section. Otherwise, and if the index of the last row of the Battle Map scene section is greater than the total number of rows of    *
	 *          the Battle Map, it decrements the index of the first row of the Battle Map scene section. Finally, it calls the respective          *
	 *          functions of the screen handlers for deleting Battle Map square graphics items.                                                     *
     *                                                                                                                                              *
     * \return  This function does not have any return value.                                                                                       *
     ************************************************************************************************************************************************/
    void triggeredActionDeleteRowBelow();

    /*! *********************************************************************************************************************************************
     * \brief   This function handles the action actionDeleteColumnLeft.                                                                            *
     *                                                                                                                                              *
     * \details This function deletes a column to the left of the Battle Map. Afterwards, it checks whether the number of columns displayable on    *
	 *          the player screen is greater than the total number of columns of the Battle Map. If so, it decrements the number of columns of the  *
	 *          Battle Map scene section. Otherwise, and if the index of the first column of the Battle Map scene section is greater than 0, it     *
	 *          decrements the index of the first column of the Battle Map scene section. Finally, it calls the respective functions of the screen  *
	 *          handlers for deleting Battle Map square graphics items.                                                                             *
     *                                                                                                                                              *
     * \return  This function does not have any return value.                                                                                       *
     ************************************************************************************************************************************************/
    void triggeredActionDeleteColumnLeft();

    /*! *********************************************************************************************************************************************
     * \brief   This function handles the action actionDeleteColumnRight.                                                                           *
     *                                                                                                                                              *
     * \details This function deletes a column to the right of the Battle Map. Afterwards, it checks whether the number of columns displayable on   *
	 *          the player screen is greater than the total number of columns of the Battle Map. If so, it decrements the number of columns of the  *
	 *          Battle Map scene section. Otherwise, and if the index of the last column of the Battle Map scene section is greater than the total  *
	 *          number of columns of the Battle Map, it decrements the index of the first column of the Battle Map scene section. Finally, it calls *
	 *          the respective functions of the screen handlers for deleting Battle Map square graphics items.                                      *
     *                                                                                                                                              *
     * \return  This function does not have any return value.                                                                                       *
     ************************************************************************************************************************************************/
    void triggeredActionDeleteColumnRight();

    /*! *********************************************************************************************************************************************
     * \brief   This function handles the action actionUpdatePlayerScreen.                                                                          *
     *                                                                                                                                              *
     * \details This function updates the Battle Map image on the player screen.                                                                    *
     *                                                                                                                                              *
     * \return  This function does not have any return value.                                                                                       *
     ************************************************************************************************************************************************/
    void triggeredActionUpdatePlayerScreen();

    /*! *********************************************************************************************************************************************
     * \brief   This function handles the actions actionWindRoseOrientationNorth to actionWindRoseOrientationWest.                                  *
     *                                                                                                                                              *
     * \details This function chooses the wind rose orientation depending on the action and updates the visibility of the wind rose on master and   *
	 *          player screen. Afterwards, it rotates the wind rose image according to the chosen wind rose orientation and sets the wind rose      *
	 *          pixmap to the screen handlers.                                                                                                      *
     *                                                                                                                                              *
     * \return  This function does not have any return value.                                                                                       *
     ************************************************************************************************************************************************/
    void triggeredActionWindRoseOrientation();

    /*! *********************************************************************************************************************************************
     * \brief   This function handles a toggle of modeSelect.                                                                                       *
     *                                                                                                                                              *
     * \details This function sets the operation mode of the master and the player screen handlers to Select.                                       *
     *                                                                                                                                              *
     * \return  This function does not have any return value.                                                                                       *
     ************************************************************************************************************************************************/
    void toggledModeSelect(bool checked);

    /*! *********************************************************************************************************************************************
     * \brief   This function handles a toggle of modeCoverBattleMap.                                                                               *
     *                                                                                                                                              *
     * \details This function sets the operation mode of the master and the player screen handlers to CoverBattleMap.                               *
     *                                                                                                                                              *
     * \return  This function does not have any return value.                                                                                       *
     ************************************************************************************************************************************************/
    void toggledModeCoverBattleMap(bool checked);

    /*! *********************************************************************************************************************************************
     * \brief   This function handles the action actionCoverBattleMap.                                                                              *
     *                                                                                                                                              *
     * \details This function covers the selected Battle Map squares on the master screen.                                                          *
     *                                                                                                                                              *
     * \return  This function does not have any return value.                                                                                       *
     ************************************************************************************************************************************************/
    void triggeredActionCoverBattleMap();

    /*! *********************************************************************************************************************************************
     * \brief   This function handles a toggle of modeUncoverBattleMap.                                                                             *
     *                                                                                                                                              *
     * \details This function sets the operation mode of the master and the player screen handlers to UncoverBattleMap.                             *
     *                                                                                                                                              *
     * \return  This function does not have any return value.                                                                                       *
     ************************************************************************************************************************************************/
    void toggledModeUncoverBattleMap(bool checked);

    /*! *********************************************************************************************************************************************
     * \brief   This function handles the action actionUncoverBattleMap.                                                                            *
     *                                                                                                                                              *
     * \details This function uncovers the selected Battle Map squares on the master screen.                                                        *
     *                                                                                                                                              *
     * \return  This function does not have any return value.                                                                                       *
     ************************************************************************************************************************************************/
    void triggeredActionUncoverBattleMap();

    /*! *********************************************************************************************************************************************
     * \brief   This function updates the label that shows the value of the scale factor.                                                           *
     *                                                                                                                                              *
     * \details -                                                                                                                                   *
     *                                                                                                                                              *
     * \return  This function does not have any return value.                                                                                       *
     ************************************************************************************************************************************************/
    void changedScaleFactor(qreal scaleFactor);

    /*! *********************************************************************************************************************************************
     * \brief   This function handles a press of the right mouse button.                                                                            *
     *                                                                                                                                              *
     * \details This function checks whether the mouse button press was positioned at the Battle Map scene and if so, creates a menu, adds the      *
     *          actions and shows it at the right mouse button press position.                                                                      *
     *                                                                                                                                              *
     * \param   position                      Position of the mouse press                                                                           *
     *                                                                                                                                              *
     * \return  This function does not have any return value.                                                                                       *
     ************************************************************************************************************************************************/
    void pressedRightMouseButton(QPoint position);

private:

    /*!
     * \brief This is a pointer to the user interface of the class MainWindow.
     */
    Ui::MainWindow *m_userInterface;

    /*!
     * \brief This is a pointer to the action group containing the operation mode actions.
     */
    QActionGroup *m_operationModeActionGroup;

    /*!
     * \brief This is a pointer to the action group containing the wind rose orientation actions.
     */
    QActionGroup *m_windRoseOrientationActionGroup;

    /*!
     * \brief This is a pointer to the user interface of the class DialogNewBattleMap.
     */
    DialogNewBattleMap *m_dialogNewBattleMap;

    /*!
     * \brief This is a pointer to the Battle Map.
     */
    BattleMap *m_battleMap;

    /*!
     * \brief This the Battle Map scene section.
     */
    BattleMapSceneSection m_battleMapSceneSection;

    /*!
     * \brief This is the handler for displaying the Battle Map scene on the master screen.
     */
    MasterScreenHandler m_masterScreenHandler;

    /*!
     * \brief This is the handler for displaying the Battle Map scene on the player screen.
     */
    PlayerScreenHandler m_playerScreenHandler;
};
#endif // MAINWINDOW_H
