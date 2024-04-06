#ifndef UNDOCOMMANDPASTE_H
#define UNDOCOMMANDPASTE_H

/****************************************************************************************************************************************************
 * INCLUDES                                                                                                                                         *
 ****************************************************************************************************************************************************/

#include "battlemap.h"
#include "masterscreenhandler.h"

#include <QUndoCommand>

/****************************************************************************************************************************************************
 * CLASS DECLARATION                                                                                                                                *
 ****************************************************************************************************************************************************/

/*!
 * \brief This class implements the functionality needed for the pasting of the previously copied clipboard to the Battle Map and its undo mechanism.
 */
class UndoCommandPaste : public QUndoCommand
{

public:

    /*! *********************************************************************************************************************************************
     * \brief   This function is the constructor of the class UndoCommandPaste.                                                                     *
     *                                                                                                                                              *
     * \details -                                                                                                                                   *
     *                                                                                                                                              *
     * \param   copiedPixmaps                 Pixmaps of the copied Battle Map squares                                                              *
     * \param   battleMap                     Address of the Battle Map                                                                             *
     * \param   masterScreenHandler           Address of the master screen handler                                                                  *
     * \param   parent                        Parent of the class UndoCommandPaste                                                                  *
     *                                                                                                                                              *
     * \return  This function does not have any return value.                                                                                       *
     ************************************************************************************************************************************************/
    UndoCommandPaste(QList<QList<QPixmap>> copiedPixmaps, BattleMap *battleMap, MasterScreenHandler *masterScreenHandler, QUndoCommand *parent = nullptr);

    /*! *********************************************************************************************************************************************
     * \brief   This function is the destructor of the class UndoCommandPaste.                                                                      *
     *                                                                                                                                              *
     * \details -                                                                                                                                   *
     *                                                                                                                                              *
     * \return  This function does not have any return value.                                                                                       *
     ************************************************************************************************************************************************/
    ~UndoCommandPaste();

    /*! *********************************************************************************************************************************************
     * \brief   This function undos this command.                                                                                                   *
     *                                                                                                                                              *
     * \details This function pastes the pixmaps of the overwritten Battle Map squares to the Battle Map and updates the pixmaps of the overwritten *
     *          Battle Map squares considering the coverage states.                                                                                 *
     *                                                                                                                                              *
     * \return  This function does not have any return value.                                                                                       *
     ************************************************************************************************************************************************/
    void undo() override;

    /*! *********************************************************************************************************************************************
     * \brief   This function applies or redos this command.                                                                                        *
     *                                                                                                                                              *
     * \details This function determines the indexes of the row and the column of the first Battle Map Square from the selection area and stores    *
     *          the pixmaps of the Battle Map squares to be overwritten only if it applies this command. Finally, it pastes the pixmaps of the      *
     *          copied Battle Map squares to the Battle Map and updates the pixmaps of the copied Battle Map squares considering the coverage       *
     *          states.                                                                                                                             *
     *                                                                                                                                              *
     * \return  This function does not have any return value.                                                                                       *
     ************************************************************************************************************************************************/
    void redo() override;

protected: /* - */

signals: /* - */

private slots: /* - */

private:

    /*!
     * \brief This is the variable containing the index of the first row where the paste action takes place.
     */
    quint32 m_firstRowIdx;

    /*!
     * \brief This is the variable containing the index of the first column where the paste action takes place.
     */
    quint32 m_firstColumnIdx;

    /*!
     * \brief This is the variable containing the pixmaps of the overwritten Battle Map squares.
     */
    QList<QList<QPixmap>> m_overwrittenPixmaps;

    /*!
     * \brief This is the variable containing the pixmaps of the copied Battle Map squares.
     */
    QList<QList<QPixmap>> m_copiedPixmaps;

    /*!
     * \brief This is a pointer to the Battle Map.
     */
    BattleMap *m_battleMap;

    /*!
     * \brief This is a pointer to the handler for displaying the Battle Map scene on the master screen.
     */
    MasterScreenHandler *m_masterScreenHandler;
};

#endif // UNDOCOMMANDPASTE_H
