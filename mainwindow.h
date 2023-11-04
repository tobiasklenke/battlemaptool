#ifndef MAINWINDOW_H
#define MAINWINDOW_H

/****************************************************************************************************************************************************
 * INCLUDES                                                                                                                                         *
 ****************************************************************************************************************************************************/

#include <QActionGroup>
#include <QMainWindow>

#include "battlemap.h"
#include "battlemapscenesection.h"
#include "dialog_newbattlemap.h"
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
     * \details This function sets up the user interface of the class MainWindow, sets the respective graphics views to the master and player       *
     *          screen handlers and connects the signals and slots of the main window actions.                                                      *
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
     * \details This function deletes the objects pointed to by pUserInterface, pBattleMap and pBattleMapSceneSection.                              *
     *                                                                                                                                              *
     * \return  This function does not have any return value.                                                                                       *
     ************************************************************************************************************************************************/
    ~MainWindow();

protected: /* - */

signals: /* - */

private slots:

    /*! *********************************************************************************************************************************************
     * \brief   This function handles the action Action_NewBattleMap and opens the dialog Dialog_NewBattleMap.                                      *
     *                                                                                                                                              *
     * \details This function creates a dialog Dialog_NewBattleMap and connects the signals and slots of the dialog button box actions of the       *
     *          dialog Dialog_NewBattleMap. Afterwards, the function opens the dialog Dialog_NewBattleMap.                                          *
     *                                                                                                                                              *
     * \return  This function does not have any return value.                                                                                       *
     ************************************************************************************************************************************************/
    void triggered_Action_NewBattleMap();

    /*! *********************************************************************************************************************************************
     * \brief   This function handles the acceptance of the dialog Dialog_NewBattleMap.                                                             *
     *                                                                                                                                              *
     * \details This function stores the Battle Map object created via the dialog Dialog_NewBattleMap. Afterwards, the function deletes the object  *
     *          pointed to by pDialog_NewBattleMap, sets the parameters of the Battle Map scene section, shares the Battle Map with the screen      *
     *          handlers, shows the Battle Map image on the master screen and initializes the Battle Map image on the player screen.                *
     *                                                                                                                                              *
     * \return  This function does not have any return value.                                                                                       *
     ************************************************************************************************************************************************/
    void accepted_Dialog_NewBattleMap();

    /*! *********************************************************************************************************************************************
     * \brief   This function handles the rejection of the dialog Dialog_NewBattleMap.                                                              *
     *                                                                                                                                              *
     * \details This function deletes the object pointed to by pDialog_NewBattleMap.                                                                *
     *                                                                                                                                              *
     * \return  This function does not have any return value.                                                                                       *
     ************************************************************************************************************************************************/
    void rejected_Dialog_NewBattleMap();

    /*! *********************************************************************************************************************************************
     * \brief   This function handles the action Action_UpdatePlayerScreen and updates the player screen.                                           *
     *                                                                                                                                              *
     * \details -                                                                                                                                   *
     *                                                                                                                                              *
     * \return  This function does not have any return value.                                                                                       *
     ************************************************************************************************************************************************/
    void triggered_Action_UpdatePlayerScreen();

    /*! *********************************************************************************************************************************************
     * \brief   This function handles a toggle of Mode_Select.                                                                                      *
     *                                                                                                                                              *
     * \details This function sets the operation mode of the master and the player screen handlers to Select.                                       *
     *                                                                                                                                              *
     * \return  This function does not have any return value.                                                                                       *
     ************************************************************************************************************************************************/
    void toggled_Mode_Select(bool checked);

    /*! *********************************************************************************************************************************************
     * \brief   This function handles a toggle of Mode_CoverBattleMap.                                                                              *
     *                                                                                                                                              *
     * \details This function sets the operation mode of the master and the player screen handlers to CoverBattleMap.                               *
     *                                                                                                                                              *
     * \return  This function does not have any return value.                                                                                       *
     ************************************************************************************************************************************************/
    void toggled_Mode_CoverBattleMap(bool checked);

    /*! *********************************************************************************************************************************************
     * \brief   This function handles the action Action_CoverBattleMap and covers the selected Battle Map squares on the master screen.             *
     *                                                                                                                                              *
     * \details -                                                                                                                                   *
     *                                                                                                                                              *
     * \return  This function does not have any return value.                                                                                       *
     ************************************************************************************************************************************************/
    void triggered_Action_CoverBattleMap();

    /*! *********************************************************************************************************************************************
     * \brief   This function handles a toggle of Mode_UncoverBattleMap.                                                                            *
     *                                                                                                                                              *
     * \details This function sets the operation mode of the master and the player screen handlers to UncoverBattleMap.                             *
     *                                                                                                                                              *
     * \return  This function does not have any return value.                                                                                       *
     ************************************************************************************************************************************************/
    void toggled_Mode_UncoverBattleMap(bool checked);

    /*! *********************************************************************************************************************************************
     * \brief   This function handles the action Action_UncoverBattleMap and uncovers the selected Battle Map squares on the master screen.         *
     *                                                                                                                                              *
     * \details -                                                                                                                                   *
     *                                                                                                                                              *
     * \return  This function does not have any return value.                                                                                       *
     ************************************************************************************************************************************************/
    void triggered_Action_UncoverBattleMap();

    /*! *********************************************************************************************************************************************
     * \brief   This function updates the label that shows the value of the scale factor.                                                           *
     *                                                                                                                                              *
     * \details -                                                                                                                                   *
     *                                                                                                                                              *
     * \return  This function does not have any return value.                                                                                       *
     ************************************************************************************************************************************************/
    void changed_ScaleFactor(qreal scaleFactor);

    /*! *********************************************************************************************************************************************
     * \brief   This function handles a click of the right mouse button.                                                                            *
     *                                                                                                                                              *
     * \details This function checks whether the mouse button click was positioned at the Battle Map scene and if so, opens a context menu.         *
     *                                                                                                                                              *
     * \param   position                      Position of the mouse click                                                                           *
     *                                                                                                                                              *
     * \return  This function does not have any return value.                                                                                       *
     ************************************************************************************************************************************************/
    void clicked_RightMouseButton(QPoint position);

private:

    /*!
     * \brief This is a pointer to the user interface of the class MainWindow.
     */
    Ui::MainWindow *pUserInterface;

    /*!
     * \brief This is a pointer to the action group containing the operation mode actions.
     */
    QActionGroup *pOperationModeActionGroup;

    /*!
     * \brief This is a pointer to the user interface of the class Dialog_NewBattleMap.
     */
    Dialog_NewBattleMap *pDialog_NewBattleMap;

    /*!
     * \brief This is a pointer to the Battle Map.
     */
    BattleMap *pBattleMap;

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
