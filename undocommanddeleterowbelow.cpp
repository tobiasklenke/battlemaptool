/****************************************************************************************************************************************************
 * INCLUDES                                                                                                                                         *
 ****************************************************************************************************************************************************/

#include "undocommanddeleterowbelow.h"

/****************************************************************************************************************************************************
 * DEFINITION OF PUBLIC FUNCTIONS                                                                                                                   *
 ****************************************************************************************************************************************************/

/*!
 * \brief This function is the constructor of the class UndoCommandDeleteRowBelow.
 */
UndoCommandDeleteRowBelow::UndoCommandDeleteRowBelow(Ui::MainWindow *userInterface, BattleMap *battleMap, BattleMapSceneSection *battleMapSceneSection, MasterScreenHandler *masterScreenHandler, PlayerScreenHandler *playerScreenHandler, QUndoCommand *parent) :
    QUndoCommand(parent),
    m_userInterface(userInterface),
    m_battleMap(battleMap),
    m_battleMapSceneSection(battleMapSceneSection),
    m_masterScreenHandler(masterScreenHandler),
    m_playerScreenHandler(playerScreenHandler)
{
}

/*!
 * \brief This function is the destructor of the class UndoCommandDeleteRowBelow.
 */
UndoCommandDeleteRowBelow::~UndoCommandDeleteRowBelow()
{
}

/*!
 * \brief This function undos this command.
 */
void UndoCommandDeleteRowBelow::undo()
{
    //TODO
}

/*!
 * \brief This function applies or redos this command.
 */
void UndoCommandDeleteRowBelow::redo()
{
    /* delete row below Battle Map */
    m_battleMap->deleteRowBelow();

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
        if (m_battleMap->getNumberRows() < m_battleMapSceneSection->getIndexFirstRowSceneSection() + m_battleMapSceneSection->getNumberRowsSceneSection())
        {
            /* decrement index of first row of Battle Map scene section */
            m_battleMapSceneSection->setIndexFirstRowSceneSection(m_battleMapSceneSection->getIndexFirstRowSceneSection() - 1U);
        }
    }

    /* delete Battle Map square graphics items for screen handlers */
    m_masterScreenHandler->deleteRowBelow();
    m_playerScreenHandler->deleteRowBelow();
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
