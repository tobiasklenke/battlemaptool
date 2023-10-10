#ifndef MAINWINDOW_H
#define MAINWINDOW_H

/****************************************************************************************************************************************************
 * INCLUDES                                                                                                                                         *
 ****************************************************************************************************************************************************/

#include <QMainWindow>

#include "battlemap.h"
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
     * \details This function deletes the objects pointed to by pUserInterface and pBattleMap.                                                      *
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
    void open_Dialog_NewBattleMap();

    /*! *********************************************************************************************************************************************
     * \brief   This function handles the acceptance of the dialog Dialog_NewBattleMap.                                                             *
     *                                                                                                                                              *
     * \details This function stores the Battle Map object created via the dialog Dialog_NewBattleMap. Afterwards, the function deletes the object  *
     *          pointed to by pDialog_NewBattleMap.                                                                                                 *
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
     * \brief   This function updates the label that shows the value of the scale factor.                                                           *
     *                                                                                                                                              *
     * \details -                                                                                                                                   *
     *                                                                                                                                              *
     * \return  This function does not have any return value.                                                                                       *
     ************************************************************************************************************************************************/
    void changed_ScaleFactor(qreal scaleFactor);

private:

    /*!
     * \brief This is a pointer to the user interface of the class MainWindow.
     */
    Ui::MainWindow *pUserInterface;

    /*!
     * \brief This is a pointer to the user interface of the class Dialog_NewBattleMap.
     */
    Dialog_NewBattleMap *pDialog_NewBattleMap;

    /*!
     * \brief This is a pointer to the Battle Map.
     */
    BattleMap *pBattleMap;

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
