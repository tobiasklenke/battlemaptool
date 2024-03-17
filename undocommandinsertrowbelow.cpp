/****************************************************************************************************************************************************
 * INCLUDES                                                                                                                                         *
 ****************************************************************************************************************************************************/

#include "undocommandinsertrowbelow.h"

/****************************************************************************************************************************************************
 * DEFINITION OF PUBLIC FUNCTIONS                                                                                                                   *
 ****************************************************************************************************************************************************/

/*!
 * \brief This function is the constructor of the class UndoCommandInsertRowBelow.
 */
UndoCommandInsertRowBelow::UndoCommandInsertRowBelow(Ui::MainWindow *userInterface, BattleMap *battleMap, BattleMapSceneSection *battleMapSceneSection, MasterScreenHandler *masterScreenHandler, PlayerScreenHandler *playerScreenHandler, QUndoCommand *parent) :
    QUndoCommand(parent),
    m_userInterface(userInterface),
    m_battleMap(battleMap),
    m_battleMapSceneSection(battleMapSceneSection),
    m_masterScreenHandler(masterScreenHandler),
    m_playerScreenHandler(playerScreenHandler)
{
}

/*!
 * \brief This function is the destructor of the class UndoCommandInsertRowBelow.
 */
UndoCommandInsertRowBelow::~UndoCommandInsertRowBelow()
{
}

/*!
 * \brief This function undos this command.
 */
void UndoCommandInsertRowBelow::undo()
{
    //TODO
}

/*!
 * \brief This function applies or redos this command.
 */
void UndoCommandInsertRowBelow::redo()
{
    /* insert new row below Battle Map */
    m_battleMap->insertRowBelow();

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

    /* insert new Battle Map square graphics items for screen handlers */
    m_masterScreenHandler->insertRowBelow();
    m_playerScreenHandler->insertRowBelow();
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
