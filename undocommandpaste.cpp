/****************************************************************************************************************************************************
 * INCLUDES                                                                                                                                         *
 ****************************************************************************************************************************************************/

#include "undocommandpaste.h"

/****************************************************************************************************************************************************
 * DEFINITION OF PUBLIC FUNCTIONS                                                                                                                   *
 ****************************************************************************************************************************************************/

/*!
 * \brief This function is the constructor of the class UndoCommandPaste.
 */
UndoCommandPaste::UndoCommandPaste(QList<QList<QPixmap>> copiedPixmaps, BattleMap *battleMap, MasterScreenHandler *masterScreenHandler, QUndoCommand *parent) :
    QUndoCommand(parent),
    m_copiedPixmaps(copiedPixmaps),
    m_battleMap(battleMap),
    m_masterScreenHandler(masterScreenHandler)
{
}

/*!
 * \brief This function is the destructor of the class UndoCommandPaste.
 */
UndoCommandPaste::~UndoCommandPaste()
{
}

/*!
 * \brief This function undos this command.
 */
void UndoCommandPaste::undo()
{
    /* paste pixmaps of overwritten Battle Map squares to Battle Map */
    m_battleMap->changeBattleMapSquarePixmaps(m_firstRowIdx, m_firstColumnIdx, m_overwrittenPixmaps);

    /* update pixmaps of overwritten Battle Map squares according to Battle Map */
    m_masterScreenHandler->updatePixmapsAccordingBattleMap();
}

/*!
 * \brief This function applies or redos this command.
 */
void UndoCommandPaste::redo()
{
    if (m_overwrittenPixmaps.isEmpty())
    {
        /* determine indexes of row and column of the first Battle Map Square from selection area */
        m_masterScreenHandler->getIndexesOfFirstBattleMapSquareFromSelectionArea(&m_firstRowIdx, &m_firstColumnIdx);

        /* store pixmaps of Battle Map squares to be overwritten */
        for (quint32 rowIdx = 0U; rowIdx < m_copiedPixmaps.count(); rowIdx++)
        {
            /* append new row of pixmaps */
            m_overwrittenPixmaps.append(QList<QPixmap>());

            for (quint32 columnIdx = 0U; columnIdx < m_copiedPixmaps.first().count(); columnIdx++)
            {
                /* append new pixmap to row */
                if ((m_firstRowIdx + rowIdx < m_battleMap->getNumberRows()) && (m_firstColumnIdx + columnIdx < m_battleMap->getNumberColumns()))
                {
                    m_overwrittenPixmaps.last().append(m_battleMap->getBattleMapSquarePixmap(m_firstRowIdx + rowIdx, m_firstColumnIdx + columnIdx));
                }
            }

            /* remove row of pixmaps if no pixmaps have been appended */
            if (0U == m_overwrittenPixmaps.last().count())
            {
                m_overwrittenPixmaps.removeLast();
            }
        }
    }

    /* paste pixmaps of copied Battle Map squares to Battle Map */
    m_battleMap->changeBattleMapSquarePixmaps(m_firstRowIdx, m_firstColumnIdx, m_copiedPixmaps);

    /* update pixmaps of copied Battle Map squares according to Battle Map */
    m_masterScreenHandler->updatePixmapsAccordingBattleMap();
}

/****************************************************************************************************************************************************
 * DEFINITION OF PROTECTED FUNCTIONS                                                                                                                *
 ****************************************************************************************************************************************************/

/* - */

/****************************************************************************************************************************************************
 * DEFINITION OF PRIVATE SLOT FUNCTIONS                                                                                                             *
 ****************************************************************************************************************************************************/

/* - */

/****************************************************************************************************************************************************
 * DEFINITION OF PRIVATE FUNCTIONS                                                                                                                  *
 ****************************************************************************************************************************************************/

/* - */
