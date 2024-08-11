#ifndef UNDOCOMMANDROTATEBATTLEMAPRIGHT_H
#define UNDOCOMMANDROTATEBATTLEMAPRIGHT_H

/****************************************************************************************************************************************************
 * INCLUDES                                                                                                                                         *
 ****************************************************************************************************************************************************/

#include "battlemap.h"
#include "battlemapscenesection.h"
#include "playerscreenhandler.h"
#include "masterscreenhandler.h"
#include "ui_mainwindow.h"

#include <QUndoCommand>

/****************************************************************************************************************************************************
 * CLASS DECLARATION                                                                                                                                *
 ****************************************************************************************************************************************************/

/*!
 * \brief This class implements the functionality needed for the right rotation of the Battle Map and its undo mechanism.
 */
class UndoCommandRotateBattleMapRight : public QUndoCommand
{

public:

    /*! *********************************************************************************************************************************************
     * \brief   This function is the constructor of the class UndoCommandRotateBattleMapRight.                                                      *
     *                                                                                                                                              *
     * \details -                                                                                                                                   *
     *                                                                                                                                              *
     * \param   userInterface                 Address of the user interface of class MainWindow.                                                    *
     * \param   battleMap                     Address of the Battle Map                                                                             *
     * \param   battleMapSceneSection         Address of the Battle Map scene section                                                               *
     * \param   masterScreenHandler           Address of the master screen handler                                                                  *
     * \param   playerScreenHandler           Address of the player screen handler                                                                  *
     * \param   parent                        Parent of the class UndoCommandRotateBattleMapLeft                                                    *
     *                                                                                                                                              *
     * \return  This function does not have any return value.                                                                                       *
     ************************************************************************************************************************************************/
    UndoCommandRotateBattleMapRight(Ui::MainWindow *userInterface, BattleMap *battleMap, BattleMapSceneSection *battleMapSceneSection, MasterScreenHandler *masterScreenHandler, PlayerScreenHandler *playerScreenHandler, QUndoCommand *parent = nullptr);

    /*! *********************************************************************************************************************************************
     * \brief   This function is the destructor of the class UndoCommandRotateBattleMapRight.                                                       *
     *                                                                                                                                              *
     * \details -                                                                                                                                   *
     *                                                                                                                                              *
     * \return  This function does not have any return value.                                                                                       *
     ************************************************************************************************************************************************/
    ~UndoCommandRotateBattleMapRight();

    /*! *********************************************************************************************************************************************
     * \brief   This function undos this command.                                                                                                   *
     *                                                                                                                                              *
     * \details This function rotates the Battle Map left and checks whether the number of rows respectively columns displayable on the player      *
     *          screen is less than the total number of rows respectively columns of the Battle Map and sets the number of rows respectively        *
     *          columns of the Battle Map scene section to the less number. Finally, it rotates the Battle Map left on the master screen handler.   *
     *                                                                                                                                              *
     * \return  This function does not have any return value.                                                                                       *
     ************************************************************************************************************************************************/
    void undo() override;

    /*! *********************************************************************************************************************************************
     * \brief   This function applies or redos this command.                                                                                        *
     *                                                                                                                                              *
     * \details This function rotates the Battle Map right and checks whether the number of rows respectively columns displayable on the player     *
     *          screen is less than the total number of rows respectively columns of the Battle Map and sets the number of rows respectively        *
     *          columns of the Battle Map scene section to the less number. Finally, it rotates the Battle Map right on the master screen handler.  *
     *                                                                                                                                              *
     * \return  This function does not have any return value.                                                                                       *
     ************************************************************************************************************************************************/
    void redo() override;

protected: /* - */

signals: /* - */

private slots: /* - */

private:

    /*!
     * \brief This is a pointer to the user interface of the class MainWindow.
     */
    Ui::MainWindow *m_userInterface;

    /*!
     * \brief This is a pointer to the Battle Map.
     */
    BattleMap *m_battleMap;

    /*!
     * \brief This is a pointer to the Battle Map scene section.
     */
    BattleMapSceneSection *m_battleMapSceneSection;

    /*!
     * \brief This is a pointer to the handler for displaying the Battle Map scene on the master screen.
     */
    MasterScreenHandler *m_masterScreenHandler;

    /*!
     * \brief This is a pointer to the handler for displaying the Battle Map scene on the player screen.
     */
    PlayerScreenHandler *m_playerScreenHandler;
};

#endif // UNDOCOMMANDROTATEBATTLEMAPRIGHT_H
