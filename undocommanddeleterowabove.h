#ifndef UNDOCOMMANDDELETEROWABOVE_H
#define UNDOCOMMANDDELETEROWABOVE_H

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
 * \brief This class implements the functionality needed for the deletion of a row above the Battle Map and its undo mechanism.
 */
class UndoCommandDeleteRowAbove : public QUndoCommand
{

public:

    /*! *********************************************************************************************************************************************
     * \brief   This function is the constructor of the class UndoCommandDeleteRowAbove.                                                            *
     *                                                                                                                                              *
     * \details -                                                                                                                                   *
     *                                                                                                                                              *
     * \param   userInterface                 Address of the user interface of class MainWindow.                                                    *
     * \param   battleMap                     Address of the Battle Map                                                                             *
     * \param   battleMapSceneSection         Address of the Battle Map scene section                                                               *
     * \param   masterScreenHandler           Address of the master screen handler                                                                  *
     * \param   playerScreenHandler           Address of the player screen handler                                                                  *
     * \param   parent                        Parent of the class UndoCommandDeleteRowAbove                                                         *
     *                                                                                                                                              *
     * \return  This function does not have any return value.                                                                                       *
     ************************************************************************************************************************************************/
    UndoCommandDeleteRowAbove(Ui::MainWindow *userInterface, BattleMap *battleMap, BattleMapSceneSection *battleMapSceneSection, MasterScreenHandler *masterScreenHandler, PlayerScreenHandler *playerScreenHandler, QUndoCommand *parent = nullptr);

    /*! *********************************************************************************************************************************************
     * \brief   This function is the destructor of the class UndoCommandDeleteRowAbove.                                                             *
     *                                                                                                                                              *
     * \details This function deletes the Battle Map squares contained in member variable m_rowAbove.                                               *
     *                                                                                                                                              *
     * \return  This function does not have any return value.                                                                                       *
     ************************************************************************************************************************************************/
    ~UndoCommandDeleteRowAbove();

    /*! *********************************************************************************************************************************************
     * \brief   This function undos this command.                                                                                                   *
     *                                                                                                                                              *
     * \details This function inserts a new row above the Battle Map, using the member variable m_rowAbove which contains the row that has          *
     *          previously been deleted. Afterwards, it enables the actions for decrement depending on the current number of rows and it checks     *
     *          whether the number of rows displayable on the player screen is greater than or equal to the total number of rows of the Battle Map. *
     *          If so, it increments the number of rows of the Battle Map scene section. Otherwise, it increments the index of the first row of the *
     *          Battle Map scene section. Finally, it calls the respective functions of the screen handlers for inserting new Battle Map square     *
     *          graphics items.                                                                                                                     *
     *                                                                                                                                              *
     * \return  This function does not have any return value.                                                                                       *
     ************************************************************************************************************************************************/
    void undo() override;

    /*! *********************************************************************************************************************************************
     * \brief   This function applies or redos this command.                                                                                        *
     *                                                                                                                                              *
     * \details This function deletes a row above the Battle Map and stores it in the member variable m_rowAbove for undoing the command.           *
     *          Afterwards, it enables or disables the actions for decrement depending on the current number of rows and it checks whether the      *
     *          number of rows displayable on the player screen is greater than the total number of rows of the Battle Map. If so, it decrements    *
     *          the number of rows of the Battle Map scene section. Otherwise, and if the index of the first row of the Battle Map scene section is *
     *          greater than 0, it decrements the index of the first row of the Battle Map scene section. Finally, it calls the respective          *
     *          functions of the screen handlers for deleting Battle Map square graphics items.                                                     *
     *                                                                                                                                              *
     * \return  This function does not have any return value.                                                                                       *
     ************************************************************************************************************************************************/
    void redo() override;

protected: /* - */

signals: /* - */

private slots: /* - */

private:

    /*!
     * \brief This is the variable containing the Battle Map squares building the deleted Battle Map row.
     */
    QList<BattleMapSquare*> m_rowAbove;

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

#endif // UNDOCOMMANDDELETEROWABOVE_H
