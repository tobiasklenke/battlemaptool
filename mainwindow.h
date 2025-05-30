#ifndef MAINWINDOW_H
#define MAINWINDOW_H

/****************************************************************************************************************************************************
 * INCLUDES                                                                                                                                         *
 ****************************************************************************************************************************************************/

#include <QActionGroup>
#include <QMainWindow>
#include <QSettings>
#include <QUndoStack>

#include "battlemap.h"
#include "battlemapscenesection.h"
#include "dialogsettings.h"
#include "playerscreenhandler.h"
#include "masterscreenhandler.h"
#include "undocommanddeletecolumnleft.h"
#include "undocommanddeletecolumnright.h"
#include "undocommanddeleterowabove.h"
#include "undocommanddeleterowbelow.h"
#include "undocommandinsertcolumnleft.h"
#include "undocommandinsertcolumnright.h"
#include "undocommandinsertrowabove.h"
#include "undocommandinsertrowbelow.h"
#include "undocommandpaste.h"
#include "undocommandrotatebattlemapleft.h"
#include "undocommandrotatebattlemapright.h"
#include "wizardnewbattlemap.h"

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
     * \details This function sets up the user interface, adds the undo stack actions to the menu, passes the graphics views and Battle Map scene   *
     *          sections to the master and player screen handlers and creates the action groups for the operation mode and the wind rose            *
     *          orientation. Afterwards, it connects several signals and slots and it makes the labels invisible so that they are not shown         *
     *          initially when there is no Battle Map and also makes the labels transparent for mouse events so that they do not process them       *
     *          instead of the graphics view. Finally, it is checked whether the application is initially configured. If this is not the case, the  *
     *          settings of the player screen or the default settings are applied, depending on a player screen being available.                    *
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
     * \details This function deletes the objects created in the constructor except m_wizardNewBattleMap.                                           *
     *                                                                                                                                              *
     * \return  This function does not have any return value.                                                                                       *
     ************************************************************************************************************************************************/
    ~MainWindow();

protected: /* - */

signals: /* - */

private slots:

    /*! *********************************************************************************************************************************************
     * \brief   This function handles the addition of a screen.                                                                                     *
     *                                                                                                                                              *
     * \details This function moves the player window to the respective screen. Afterwards, it determines the resolution and size values of the     *
     *          screen associated with the windowing system the application is connected to and it checks whether the settings of the added screen  *
     *          differ from the current player screen settings. If this is the case, it shows a message box informing the user that the settings of *
     *          the added screen differ from the current player screen settings and asking the user whether the settings of the added screen shall  *
     *          be applied. If the user confirms, it applies the settings of the player screen, updates the Battle Map scene section, shows the     *
     *          Battle Map image on the master screen, initializes the Battle Map image on the player screen and updates the wind rose image        *
     *          position on the player screen. Finally, it enables or disables the action actionUpdatePlayerScreen, depending on whether the Battle *
     *          Map is initialized and a player screen is available.                                                                                *
     *                                                                                                                                              *
     * \return  This function does not have any return value.                                                                                       *
     ************************************************************************************************************************************************/
    void screenAdded(QScreen *screen);

    /*! *********************************************************************************************************************************************
     * \brief   This function handles the removal of a screen.                                                                                      *
     *                                                                                                                                              *
     * \details This function enables or disables the action actionUpdatePlayerScreen, depending on whether the Battle Map is initialized and a     *
     *          player screen is available.                                                                                                         *
     *                                                                                                                                              *
     * \return  This function does not have any return value.                                                                                       *
     ************************************************************************************************************************************************/
    void screenRemoved(QScreen *screen);

    /*! *********************************************************************************************************************************************
     * \brief   This function handles the action actionNewBattleMap.                                                                                *
     *                                                                                                                                              *
     * \details This function creates the wizard WizardNewBattleMap and connects the signals and slots of the wizard WizardNewBattleMap.            *
     *          Afterwards, it opens the wizard WizardNewBattleMap.                                                                                 *
     *                                                                                                                                              *
     * \return  This function does not have any return value.                                                                                       *
     ************************************************************************************************************************************************/
    void triggeredActionNewBattleMap();

    /*! *********************************************************************************************************************************************
     * \brief   This function handles the acceptance of the wizard WizardNewBattleMap.                                                              *
     *                                                                                                                                              *
     * \details This function first sets the wait cursor as the following process may take some time, stores the Battle Map from the accepted       *
     *          wizard WizardNewBattleMap and deletes the wizard afterwards. Then, it updates the Battle Map scene section. It shares the Battle    *
     *          Map with the screen handlers, shows the Battle Map image on the master screen and initializes the Battle Map image on the player    *
     *          screen. Afterwards, it enables the actions that shall only be available when the Battle Map is initialized and it also makes the    *
     *          label labelScaleFactor visible so that it is shown when the Battle Map is initialized. Finally, it resets the arrow cursor as the   *
     *          process which takes some time is completed.                                                                                         *
     *                                                                                                                                              *
     * \return  This function does not have any return value.                                                                                       *
     ************************************************************************************************************************************************/
    void acceptedWizardNewBattleMap();

    /*! *********************************************************************************************************************************************
     * \brief   This function handles the rejection of the wizard WizardNewBattleMap.                                                               *
     *                                                                                                                                              *
     * \details This function deletes the wizard m_wizardNewBattleMap.                                                                              *
     *                                                                                                                                              *
     * \return  This function does not have any return value.                                                                                       *
     ************************************************************************************************************************************************/
    void rejectedWizardNewBattleMap();

    /*! *********************************************************************************************************************************************
     * \brief   This function handles the action actionOpenBattleMap.                                                                               *
     *                                                                                                                                              *
     * \details TODO                                                                                                                                *
     *                                                                                                                                              *
     * \return  This function does not have any return value.                                                                                       *
     ************************************************************************************************************************************************/
    void triggeredActionOpenBattleMap();

    /*! *********************************************************************************************************************************************
     * \brief   This function handles the acceptance of the wizard WizardOpenBattleMap.                                                             *
     *                                                                                                                                              *
     * \details TODO                                                                                                                                *
     *                                                                                                                                              *
     * \return  This function does not have any return value.                                                                                       *
     ************************************************************************************************************************************************/
    void acceptedWizardOpenBattleMap();

    /*! *********************************************************************************************************************************************
     * \brief   This function handles the rejection of the wizard WizardOpenBattleMap.                                                              *
     *                                                                                                                                              *
     * \details This function deletes the wizard m_wizardOpenBattleMap.                                                                             *
     *                                                                                                                                              *
     * \return  This function does not have any return value.                                                                                       *
     ************************************************************************************************************************************************/
    void rejectedWizardOpenBattleMap();

    /*! *********************************************************************************************************************************************
     * \brief   This function handles the action actionCopy.                                                                                        *
     *                                                                                                                                              *
     * \details This function gets the pixmaps of the Battle Map squares from the selection area of the master screen handler and enables the       *
     *          action actionPaste since the pixmaps of the Battle Map squares from the selection area have been copied.                            *
     *                                                                                                                                              *
     * \return  This function does not have any return value.                                                                                       *
     ************************************************************************************************************************************************/
    void triggeredActionCopy();

    /*! *********************************************************************************************************************************************
     * \brief   This function handles the action actionPaste.                                                                                       *
     *                                                                                                                                              *
     * \details This function pushes the command UndoCommandPaste to the undo stack and applies it by calling its function redo().                  *
     *                                                                                                                                              *
     * \return  This function does not have any return value.                                                                                       *
     ************************************************************************************************************************************************/
    void triggeredActionPaste();

    /*! *********************************************************************************************************************************************
     * \brief   This function handles the action actionInsertRowAbove.                                                                              *
     *                                                                                                                                              *
     * \details This function pushes the command UndoCommandInsertRowAbove to the undo stack and applies it by calling its function redo().         *
     *                                                                                                                                              *
     * \return  This function does not have any return value.                                                                                       *
     ************************************************************************************************************************************************/
    void triggeredActionInsertRowAbove();

    /*! *********************************************************************************************************************************************
     * \brief   This function handles the action actionInsertRowBelow.                                                                              *
     *                                                                                                                                              *
     * \details This function pushes the command UndoCommandInsertRowBelow to the undo stack and applies it by calling its function redo().         *
     *                                                                                                                                              *
     * \return  This function does not have any return value.                                                                                       *
     ************************************************************************************************************************************************/
    void triggeredActionInsertRowBelow();

    /*! *********************************************************************************************************************************************
     * \brief   This function handles the action actionInsertColumnLeft.                                                                            *
     *                                                                                                                                              *
     * \details This function pushes the command UndoCommandInsertColumnLeft to the undo stack and applies it by calling its function redo().       *
     *                                                                                                                                              *
     * \return  This function does not have any return value.                                                                                       *
     ************************************************************************************************************************************************/
    void triggeredActionInsertColumnLeft();

    /*! *********************************************************************************************************************************************
     * \brief   This function handles the action actionInsertColumnRight.                                                                           *
     *                                                                                                                                              *
     * \details This function pushes the command UndoCommandInsertColumnRight to the undo stack and applies it by calling its function redo().      *
     *                                                                                                                                              *
     * \return  This function does not have any return value.                                                                                       *
     ************************************************************************************************************************************************/
    void triggeredActionInsertColumnRight();

    /*! *********************************************************************************************************************************************
     * \brief   This function handles the action actionDeleteRowAbove.                                                                              *
     *                                                                                                                                              *
     * \details This function pushes the command UndoCommandDeleteRowAbove to the undo stack and applies it by calling its function redo().         *
     *                                                                                                                                              *
     * \return  This function does not have any return value.                                                                                       *
     ************************************************************************************************************************************************/
    void triggeredActionDeleteRowAbove();

    /*! *********************************************************************************************************************************************
     * \brief   This function handles the action actionDeleteRowBelow.                                                                              *
     *                                                                                                                                              *
     * \details This function pushes the command UndoCommandDeleteRowBelow to the undo stack and applies it by calling its function redo().         *
     *                                                                                                                                              *
     * \return  This function does not have any return value.                                                                                       *
     ************************************************************************************************************************************************/
    void triggeredActionDeleteRowBelow();

    /*! *********************************************************************************************************************************************
     * \brief   This function handles the action actionDeleteColumnLeft.                                                                            *
     *                                                                                                                                              *
     * \details This function pushes the command UndoCommandDeleteColumnLeft to the undo stack and applies it by calling its function redo().       *
     *                                                                                                                                              *
     * \return  This function does not have any return value.                                                                                       *
     ************************************************************************************************************************************************/
    void triggeredActionDeleteColumnLeft();

    /*! *********************************************************************************************************************************************
     * \brief   This function handles the action actionDeleteColumnRight.                                                                           *
     *                                                                                                                                              *
     * \details This function pushes the command UndoCommandDeleteColumnRight to the undo stack and applies it by calling its function redo().      *
     *                                                                                                                                              *
     * \return  This function does not have any return value.                                                                                       *
     ************************************************************************************************************************************************/
    void triggeredActionDeleteColumnRight();

    /*! *********************************************************************************************************************************************
     * \brief   This function handles the action actionRotateBattleMapLeft.                                                                         *
     *                                                                                                                                              *
     * \details This function pushes the command UndoCommandRotateBattleMapLeft to the undo stack and applies it by calling its function redo().    *
     *                                                                                                                                              *
     * \return  This function does not have any return value.                                                                                       *
     ************************************************************************************************************************************************/
    void triggeredActionRotateBattleMapLeft();

    /*! *********************************************************************************************************************************************
     * \brief   This function handles the action actionRotateBattleMapRight.                                                                        *
     *                                                                                                                                              *
     * \details This function pushes the command UndoCommandRotateBattleMapRight to the undo stack and applies it by calling its function redo().   *
     *                                                                                                                                              *
     * \return  This function does not have any return value.                                                                                       *
     ************************************************************************************************************************************************/
    void triggeredActionRotateBattleMapRight();

    /*! *********************************************************************************************************************************************
     * \brief   This function handles the action actionUpdatePlayerScreen.                                                                          *
     *                                                                                                                                              *
     * \details This function updates the Battle Map image on the player screen and clears the undo stack afterwards.                               *
     *                                                                                                                                              *
     * \return  This function does not have any return value.                                                                                       *
     ************************************************************************************************************************************************/
    void triggeredActionUpdatePlayerScreen();

    /*! *********************************************************************************************************************************************
     * \brief   This function handles the action actionResetPlayerScreen.                                                                           *
     *                                                                                                                                              *
     * \details -                                                                                                                                   *
     *                                                                                                                                              *
     * \return  This function does not have any return value.                                                                                       *
     ************************************************************************************************************************************************/
    void triggeredActionResetPlayerScreen();

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
     * \brief   This function handles the action actionOpenSettings.                                                                                *
     *                                                                                                                                              *
     * \details This function creates the dialog DialogSettings and connects the signals and slots of the dialog button box actions of the dialog   *
     *          DialogSettings. Afterwards, it opens the dialog DialogSettings.                                                                     *
     *                                                                                                                                              *
     * \return  This function does not have any return value.                                                                                       *
     ************************************************************************************************************************************************/
    void triggeredActionOpenSettings();

    /*! *********************************************************************************************************************************************
     * \brief   This function handles the acceptance of the dialog DialogSettings.                                                                  *
     *                                                                                                                                              *
     * \details This function first checks whether the settings have been changed and, if this is the case, updates the Battle Map scene section,   *
     *          shows the Battle Map image on the master screen and initializes the Battle Map image on the player screen and updates the wind rose *
     *          image position on the player screen. Finally, it deletes the dialog DialogSettings.                                                 *
     *                                                                                                                                              *
     * \return  This function does not have any return value.                                                                                       *
     ************************************************************************************************************************************************/
    void acceptedDialogSettings();

    /*! *********************************************************************************************************************************************
     * \brief   This function handles the rejection of the dialog DialogSettings.                                                                   *
     *                                                                                                                                              *
     * \details This function deletes the dialog DialogSettings.                                                                                    *
     *                                                                                                                                              *
     * \return  This function does not have any return value.                                                                                       *
     ************************************************************************************************************************************************/
    void rejectedDialogSettings();

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

    /*! *********************************************************************************************************************************************
     * \brief   This function enables or disables the actions actionCopy and actionPaste.                                                           *
     *                                                                                                                                              *
     * \details This function enables the action actionCopy if the pixmaps of the selected Battle Map squares are copyable and it enables the       *
     *          action actionPaste if the pixmaps of the selected Battle Map squares are copyable and if the pixmaps of the Battle Map squares have *
     *          already been copied.                                                                                                                *
     *                                                                                                                                              *
     * \param   selectionCopyable             Information whether pixmaps of selected Battle Map squares are copyable                               *
     *                                                                                                                                              *
     * \return  This function does not have any return value.                                                                                       *
     ************************************************************************************************************************************************/
    void changedSelection(bool selectionCopyable);

private:

    /*! *********************************************************************************************************************************************
     * \brief   This function updates the Battle Map scene section.                                                                                 *
     *                                                                                                                                              *
     * \details This function resets the indexes of the first row and column of the Battle Map scene section, checks whether the number of rows     *
     *          respectively columns displayable on the player screen is less than the total number of rows respectively columns of the Battle Map  *
     *          and sets the number of rows respectively columns of the Battle Map scene section to the less number.                                *
     *                                                                                                                                              *
     * \return  This function does not have any return value.                                                                                       *
     ************************************************************************************************************************************************/
    void updateBattleMapSceneSection();

    /*! *********************************************************************************************************************************************
     * \brief   This function applies the settings of the screen associated with the windowing system the application is connected to.              *
     *                                                                                                                                              *
     * \details This function determines the resolution and size values of the screen associated with the windowing system the application is       *
     *          connected to and applies the settings of the player screen.                                                                         *
     *                                                                                                                                              *
     * \return  This function does not have any return value.                                                                                       *
     ************************************************************************************************************************************************/
    void applyPlayerScreenSettings();

    /*!
     * \brief This is a pointer to the user interface of the class MainWindow.
     */
    Ui::MainWindow *m_userInterface;

    /*!
     * \brief This is a pointer to the graphics view of the player window.
     */
    QGraphicsView *m_playerWindow;

    /*!
     * \brief This is a pointer to the undo stack that maintains a stack of commands that have been applied to the Battle Map.
     */
    QUndoStack *m_undoStack;

    /*!
     * \brief This is a pointer to the undo action that accesses the undo stack.
     */
    QAction *m_undoAction;

    /*!
     * \brief This is a pointer to the redo action that accesses the undo stack.
     */
    QAction *m_redoAction;

    /*!
     * \brief This is a pointer to the action group containing the operation mode actions.
     */
    QActionGroup *m_operationModeActionGroup;

    /*!
     * \brief This is a pointer to the action group containing the wind rose orientation actions.
     */
    QActionGroup *m_windRoseOrientationActionGroup;

    /*!
     * \brief This is a pointer to the user interface of the class WizardOpenBattleMap.
     */
    WizardNewBattleMap *m_wizardNewBattleMap;

    /*!
     * \brief This is a pointer to the user interface of the class DialogSettings.
     */
    DialogSettings *m_dialogSettings;

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

    /*!
     * \brief This is the variable containing the pixmaps of the copied Battle Map squares.
     */
    QList<QList<QPixmap>> m_copiedPixmaps;
};
#endif // MAINWINDOW_H
