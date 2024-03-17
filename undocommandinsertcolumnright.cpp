/****************************************************************************************************************************************************
 * INCLUDES                                                                                                                                         *
 ****************************************************************************************************************************************************/

#include "undocommandinsertcolumnright.h"

/****************************************************************************************************************************************************
 * DEFINITION OF PUBLIC FUNCTIONS                                                                                                                   *
 ****************************************************************************************************************************************************/

/*!
 * \brief This function is the constructor of the class UndoCommandInsertColumnRight.
 */
UndoCommandInsertColumnRight::UndoCommandInsertColumnRight(Ui::MainWindow *userInterface, BattleMap *battleMap, BattleMapSceneSection *battleMapSceneSection, MasterScreenHandler *masterScreenHandler, PlayerScreenHandler *playerScreenHandler, QUndoCommand *parent) :
    QUndoCommand(parent),
    m_userInterface(userInterface),
    m_battleMap(battleMap),
    m_battleMapSceneSection(battleMapSceneSection),
    m_masterScreenHandler(masterScreenHandler),
    m_playerScreenHandler(playerScreenHandler)
{
}

/*!
 * \brief This function is the destructor of the class UndoCommandInsertColumnRight.
 */
UndoCommandInsertColumnRight::~UndoCommandInsertColumnRight()
{
}

/*!
 * \brief This function undos this command.
 */
void UndoCommandInsertColumnRight::undo()
{
    //TODO
}

/*!
 * \brief This function applies or redos this command.
 */
void UndoCommandInsertColumnRight::redo()
{
    /* insert new column to the right of Battle Map */
    m_battleMap->insertColumnRight();

    /* enable actions for decrement depending on current number of columns */
    if (BATTLEMAP_MINIMUMNUMBERROWSANDCOLUMNS < m_battleMap->getNumberColumns())
    {
        m_userInterface->actionDeleteColumnLeft->setEnabled(true);
        m_userInterface->actionDeleteColumnRight->setEnabled(true);
    }

    /* check whether number of columns displayable on player screen is greater than or equal to total number of columns of Battle Map */
    quint32 numberColumnsOnPlayerScreen = static_cast<quint32>(calcScreenWidthInInches(CONFIG_PLAYER_SCREEN_DIAGONAL, CONFIG_PLAYER_SCREEN_RESOLUTION.height(), CONFIG_PLAYER_SCREEN_RESOLUTION.width()));
    if (m_battleMap->getNumberColumns() <= numberColumnsOnPlayerScreen)
    {
        /* increment number of columns of Battle Map scene section */
        m_battleMapSceneSection->setNumberColumnsSceneSection(m_battleMapSceneSection->getNumberColumnsSceneSection() + 1U);
    }

    /* insert new Battle Map square graphics items for screen handlers */
    m_masterScreenHandler->insertColumnRight();
    m_playerScreenHandler->insertColumnRight();
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
