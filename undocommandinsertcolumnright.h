#ifndef UNDOCOMMANDINSERTCOLUMNRIGHT_H
#define UNDOCOMMANDINSERTCOLUMNRIGHT_H

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
 * \brief This class implements the functionality needed for the insertion of a column to the right of the Battle Map and its undo mechanism.
 */
class UndoCommandInsertColumnRight : public QUndoCommand
{

public:

    /*! *********************************************************************************************************************************************
     * \brief   This function is the constructor of the class UndoCommandInsertColumnRight.                                                         *
     *                                                                                                                                              *
     * \details -                                                                                                                                   *
     *                                                                                                                                              *
     * \param   userInterface                 Address of the user interface of class MainWindow.                                                    *
     * \param   battleMap                     Address of the Battle Map                                                                             *
     * \param   battleMapSceneSection         Address of the Battle Map scene section                                                               *
     * \param   masterScreenHandler           Address of the master screen handler                                                                  *
     * \param   playerScreenHandler           Address of the player screen handler                                                                  *
     * \param   parent                        Parent of the class UndoCommandInsertColumnRight                                                      *
     *                                                                                                                                              *
     * \return  This function does not have any return value.                                                                                       *
     ************************************************************************************************************************************************/
    UndoCommandInsertColumnRight(Ui::MainWindow *userInterface, BattleMap *battleMap, BattleMapSceneSection *battleMapSceneSection, MasterScreenHandler *masterScreenHandler, PlayerScreenHandler *playerScreenHandler, QUndoCommand *parent = nullptr);

    /*! *********************************************************************************************************************************************
     * \brief   This function is the destructor of the class UndoCommandInsertColumnRight.                                                          *
     *                                                                                                                                              *
     * \details This function deletes the Battle Map squares contained in member variable m_columnRight.                                            *                                                                                                             
     *                                                                                                                                              *
     * \return  This function does not have any return value.                                                                                       *
     ************************************************************************************************************************************************/
    ~UndoCommandInsertColumnRight();

    /*! *********************************************************************************************************************************************
     * \brief   This function undos this command.                                                                                                   *
     *                                                                                                                                              *
     * \details This function deletes a column to the right of the Battle Map and stores it in the member variable m_columnRight for redoing the    *
     *          command. Afterwards, it enables or disables the actions for decrement depending on the current number of columns and it checks      *
     *          whether the number of columns displayable on the player screen is greater than the total number of columns of the Battle Map. If    *
     *          so, it decrements the number of columns of the Battle Map scene section. Otherwise, and if the index of the last column of the      *
     *          Battle Map scene section is greater than the total number of columns of the Battle Map, it decrements the index of the first column *
     *          of the Battle Map scene section. Finally, it calls the respective functions of the screen handlers for deleting Battle Map square   *
     *          graphics items.                                                                                                                     *                                                                                                                                *
     *                                                                                                                                              *
     * \return  This function does not have any return value.                                                                                       *
     ************************************************************************************************************************************************/
    void undo() override;

    /*! *********************************************************************************************************************************************
     * \brief   This function applies or redos this command.                                                                                        *
     *                                                                                                                                              *
     * \details This function inserts a new column to the right of the Battle Map, using the member variable m_columnRight which is empty when the  *
     *          command is initially applied, or otherwise contains the inserted column to the right which has previously been undone. Afterwards,  *
     *          it enables the actions for decrement depending on the current number of columns and it checks whether the number of columns         *
     *          displayable on the player screen is greater than or equal to the total number of columns of the Battle Map. If so, it increments    *
     *          the number of columns of the Battle Map scene section. Finally, it calls the respective functions of the screen handlers for        *
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
     * \brief This is the variable containing the Battle Map squares building the inserted Battle Map column.
     */
    QList<BattleMapSquare*> m_columnRight;

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

#endif // UNDOCOMMANDINSERTCOLUMNRIGHT_H
