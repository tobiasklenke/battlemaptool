#ifndef UNDOCOMMANDINSERTROWABOVE_H
#define UNDOCOMMANDINSERTROWABOVE_H

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
 * \brief This class implements the functionality needed for the insertion of a row above the Battle Map and its undo mechanism.
 */
class UndoCommandInsertRowAbove : public QUndoCommand
{

public:

    /*! *********************************************************************************************************************************************
     * \brief   This function is the constructor of the class UndoCommandInsertRowAbove.                                                            *
     *                                                                                                                                              *
     * \details -                                                                                                                                   *
     *                                                                                                                                              *
     * \param   userInterface                 Address of the user interface of class MainWindow.                                                    *
     * \param   battleMap                     Address of the Battle Map                                                                             *
     * \param   battleMapSceneSection         Address of the Battle Map scene section                                                               *
     * \param   masterScreenHandler           Address of the master screen handler                                                                  *
     * \param   playerScreenHandler           Address of the player screen handler                                                                  *
     * \param   parent                        Parent of the class UndoCommandInsertRowAbove                                                         *
     *                                                                                                                                              *
     * \return  This function does not have any return value.                                                                                       *
     ************************************************************************************************************************************************/
    UndoCommandInsertRowAbove(Ui::MainWindow *userInterface, BattleMap *battleMap, BattleMapSceneSection *battleMapSceneSection, MasterScreenHandler *masterScreenHandler, PlayerScreenHandler *playerScreenHandler, QUndoCommand *parent = nullptr);

    /*! *********************************************************************************************************************************************
     * \brief   This function is the destructor of the class UndoCommandInsertRowAbove.                                                             *
     *                                                                                                                                              *
     * \details -                                                                                                                                   *
     *                                                                                                                                              *
     * \return  This function does not have any return value.                                                                                       *
     ************************************************************************************************************************************************/
    ~UndoCommandInsertRowAbove();

    /*! *********************************************************************************************************************************************
     * \brief   This function undos this command.                                                                                                   *
     *                                                                                                                                              *
     * \details TODO                                                                                                                                *
     *                                                                                                                                              *
     * \return  This function does not have any return value.                                                                                       *
     ************************************************************************************************************************************************/
    void undo() override;

    /*! *********************************************************************************************************************************************
     * \brief   This function applies or redos this command.                                                                                        *
     *                                                                                                                                              *
     * \details This function inserts a new row above the Battle Map. Afterwards, it enables the actions for decrement depending on the current     *
     *          number of rows and it checks whether the number of rows displayable on the player screen is greater than or equal to the total      *
     *          number of rows of the Battle Map. If so, it increments the number of rows of the Battle Map scene section. Otherwise, it increments *
     *          the index of the first row of the Battle Map scene section. Finally, it calls the respective functions of the screen handlers for   *
     *          inserting new Battle Map square graphics items.                                                                                     *
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

#endif // UNDOCOMMANDINSERTROWABOVE_H
