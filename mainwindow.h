#ifndef MAINWINDOW_H
#define MAINWINDOW_H

/****************************************************************************************************************************************************
 * INCLUDES                                                                                                                                         *
 ****************************************************************************************************************************************************/

#include <QGraphicsPixmapItem>
#include <QGraphicsView>
#include <QMainWindow>

#include "battlemap.h"
#include "battlemapscenemasterscreen.h"
#include "dialog_newbattlemap.h"

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
     * \details This function sets up the user interface of the class MainWindow and connects the signals and slots of the main window actions.     *
     *                                                                                                                                              *
     * \param   playerWindow                  Address of the QGraphicsView to display the players window                                            *
     * \param   parent                        Parent of the class MainWindow                                                                        *
     *                                                                                                                                              *
     * \return  This function does not have any return value.                                                                                       *
     ************************************************************************************************************************************************/
    MainWindow(QGraphicsView *playerWindow, QWidget *parent = nullptr);

    /*! *********************************************************************************************************************************************
     * \brief   This function is the destructor of the class MainWindow.                                                                            *
     *                                                                                                                                              *
     * \details This function deletes the object pointed to by pUserInterface.                                                                      *
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

private:

    /*! *********************************************************************************************************************************************
     * \brief   This function shows the Battle Map image on the master screen.                                                                            *
     *                                                                                                                                              *
     * \details TODO                                                                                                                                *
     *                                                                                                                                              *
     * \return  This function does not have any return value.                                                                                       *
     ************************************************************************************************************************************************/
    void showBattleMapImageOnMasterScreen();

    /*!
     * \brief This is a pointer to the user interface of the class MainWindow.
     */
    Ui::MainWindow *pUserInterface;

    /*!
     * \brief This is a pointer to the user interface of the class Dialog_NewBattleMap.
     */
    Dialog_NewBattleMap *pDialog_NewBattleMap;

    /*!
     * \brief This is a pointer to the graphics view shown on the player screen.
     */
    QGraphicsView *pPlayerScreenWindow;

    /*!
     * \brief This is a pointer to the BattleMapSceneMasterScreen object that is set to pPlayerScreenWindow.
     */
    BattleMapSceneMasterScreen *pBattleMapSceneMasterScreen;

    /*!
     * \brief This is a pointer to the Battle Map.
     */
    BattleMap * pBattleMap;
};
#endif // MAINWINDOW_H
