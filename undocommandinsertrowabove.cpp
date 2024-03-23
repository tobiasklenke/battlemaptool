/****************************************************************************************************************************************************
 * INCLUDES                                                                                                                                         *
 ****************************************************************************************************************************************************/

#include "undocommandinsertrowabove.h"

/****************************************************************************************************************************************************
 * DEFINITION OF PUBLIC FUNCTIONS                                                                                                                   *
 ****************************************************************************************************************************************************/

/*!
 * \brief This function is the constructor of the class UndoCommandInsertRowAbove.
 */
UndoCommandInsertRowAbove::UndoCommandInsertRowAbove(Ui::MainWindow *userInterface, BattleMap *battleMap, BattleMapSceneSection *battleMapSceneSection, MasterScreenHandler *masterScreenHandler, PlayerScreenHandler *playerScreenHandler, QUndoCommand *parent) :
    QUndoCommand(parent),
    m_rowAbove(QList<BattleMapSquare*>()),
    m_userInterface(userInterface),
    m_battleMap(battleMap),
    m_battleMapSceneSection(battleMapSceneSection),
    m_masterScreenHandler(masterScreenHandler),
    m_playerScreenHandler(playerScreenHandler)
{
}

/*!
 * \brief This function is the destructor of the class UndoCommandInsertRowAbove.
 */
UndoCommandInsertRowAbove::~UndoCommandInsertRowAbove()
{
    /* delete row above */
    for (quint32 columnIdx = 0U; columnIdx < m_rowAbove.count(); columnIdx++)
    {
        delete m_rowAbove[columnIdx];
    }
}

/*!
 * \brief This function undos this command.
 */
void UndoCommandInsertRowAbove::undo()
{
    /* delete row above Battle Map */
    m_rowAbove = m_battleMap->deleteRowAbove();

    /* enable or disable actions for decrement depending on current number of rows */
    if (BATTLEMAP_MINIMUMNUMBERROWSANDCOLUMNS == m_battleMap->getNumberRows())
    {
        m_userInterface->actionDeleteRowAbove->setEnabled(false);
        m_userInterface->actionDeleteRowBelow->setEnabled(false);
    }
    else
    {
        m_userInterface->actionDeleteRowAbove->setEnabled(true);
        m_userInterface->actionDeleteRowBelow->setEnabled(true);
    }

    /* check whether number of rows displayable on player screen is greater than total number of rows of Battle Map */
    quint32 numberRowsOnPlayerScreen = static_cast<quint32>(calcScreenHeightInInches(CONFIG_PLAYER_SCREEN_DIAGONAL, CONFIG_PLAYER_SCREEN_RESOLUTION.height(), CONFIG_PLAYER_SCREEN_RESOLUTION.width()));
    if (m_battleMap->getNumberRows() < numberRowsOnPlayerScreen)
    {
        /* decrement number of rows of Battle Map scene section */
        m_battleMapSceneSection->setNumberRowsSceneSection(m_battleMapSceneSection->getNumberRowsSceneSection() - 1U);
    }
    else
    {
        if (0U < m_battleMapSceneSection->getIndexFirstRowSceneSection())
        {
            /* decrement index of first row of Battle Map scene section */
            m_battleMapSceneSection->setIndexFirstRowSceneSection(m_battleMapSceneSection->getIndexFirstRowSceneSection() - 1U);
       }
    }

    /* delete Battle Map square graphics items for screen handlers */
    m_masterScreenHandler->deleteRowAbove();
    m_playerScreenHandler->deleteRowAbove();
}

/*!
 * \brief This function applies or redos this command.
 */
void UndoCommandInsertRowAbove::redo()
{
    /* insert new row above Battle Map */
    m_battleMap->insertRowAbove(m_rowAbove);
    m_rowAbove.clear();

    /* enable actions for decrement depending on current number of rows */
    if (BATTLEMAP_MINIMUMNUMBERROWSANDCOLUMNS < m_battleMap->getNumberRows())
    {
        m_userInterface->actionDeleteRowAbove->setEnabled(true);
        m_userInterface->actionDeleteRowBelow->setEnabled(true);
    }

    /* check whether number of rows displayable on player screen is greater than or equal to total number of rows of Battle Map */
    quint32 numberRowsOnPlayerScreen = static_cast<quint32>(calcScreenHeightInInches(CONFIG_PLAYER_SCREEN_DIAGONAL, CONFIG_PLAYER_SCREEN_RESOLUTION.height(), CONFIG_PLAYER_SCREEN_RESOLUTION.width()));
    if (m_battleMap->getNumberRows() <= numberRowsOnPlayerScreen)
    {
        /* increment number of rows of Battle Map scene section */
        m_battleMapSceneSection->setNumberRowsSceneSection(m_battleMapSceneSection->getNumberRowsSceneSection() + 1U);
    }
    else
    {
        /* increment index of first row of Battle Map scene section */
        m_battleMapSceneSection->setIndexFirstRowSceneSection(m_battleMapSceneSection->getIndexFirstRowSceneSection() + 1U);
    }

    /* insert new Battle Map square graphics items for screen handlers */
    m_masterScreenHandler->insertRowAbove();
    m_playerScreenHandler->insertRowAbove();
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
