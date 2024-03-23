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
    m_columnRight(QList<BattleMapSquare*>()),
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
    /* delete column right */
    for (quint32 columnIdx = 0U; columnIdx < m_columnRight.count(); columnIdx++)
    {
        delete m_columnRight[columnIdx];
    }
}

/*!
 * \brief This function undos this command.
 */
void UndoCommandInsertColumnRight::undo()
{
    /* delete column to the right of Battle Map */
    m_columnRight = m_battleMap->deleteColumnRight();

    /* enable or disable actions for decrement depending on current number of columns */
    if (BATTLEMAP_MINIMUMNUMBERROWSANDCOLUMNS == m_battleMap->getNumberColumns())
    {
        m_userInterface->actionDeleteColumnLeft->setEnabled(false);
        m_userInterface->actionDeleteColumnRight->setEnabled(false);
    }
    else
    {
        m_userInterface->actionDeleteColumnLeft->setEnabled(true);
        m_userInterface->actionDeleteColumnRight->setEnabled(true);
    }

    /* check whether number of columns displayable on player screen is greater than total number of columns of Battle Map */
    quint32 numberColumnsOnPlayerScreen = static_cast<quint32>(calcScreenWidthInInches(CONFIG_PLAYER_SCREEN_DIAGONAL, CONFIG_PLAYER_SCREEN_RESOLUTION.height(), CONFIG_PLAYER_SCREEN_RESOLUTION.width()));
    if (m_battleMap->getNumberColumns() < numberColumnsOnPlayerScreen)
    {
        /* decrement number of columns of Battle Map scene section */
        m_battleMapSceneSection->setNumberColumnsSceneSection(m_battleMapSceneSection->getNumberColumnsSceneSection() - 1U);
    }
    else
    {
        if (m_battleMap->getNumberColumns() < m_battleMapSceneSection->getIndexFirstColumnSceneSection() + m_battleMapSceneSection->getNumberColumnsSceneSection())
        {
            /* decrement index of first column of Battle Map scene section */
            m_battleMapSceneSection->setIndexFirstColumnSceneSection(m_battleMapSceneSection->getIndexFirstColumnSceneSection() - 1U);
        }
    }

    /* delete Battle Map square graphics items for screen handlers */
    m_masterScreenHandler->deleteColumnRight();
    m_playerScreenHandler->deleteColumnRight();
}

/*!
 * \brief This function applies or redos this command.
 */
void UndoCommandInsertColumnRight::redo()
{
    /* insert new column to the right of Battle Map */
    m_battleMap->insertColumnRight(m_columnRight);
    m_columnRight.clear();

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
