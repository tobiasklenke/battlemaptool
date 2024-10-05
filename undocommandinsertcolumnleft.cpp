/****************************************************************************************************************************************************
 * INCLUDES                                                                                                                                         *
 ****************************************************************************************************************************************************/

#include "undocommandinsertcolumnleft.h"

/****************************************************************************************************************************************************
 * DEFINITION OF PUBLIC FUNCTIONS                                                                                                                   *
 ****************************************************************************************************************************************************/

/*!
 * \brief This function is the constructor of the class UndoCommandInsertColumnLeft.
 */
UndoCommandInsertColumnLeft::UndoCommandInsertColumnLeft(Ui::MainWindow *userInterface, BattleMap *battleMap, BattleMapSceneSection *battleMapSceneSection, MasterScreenHandler *masterScreenHandler, PlayerScreenHandler *playerScreenHandler, QUndoCommand *parent) :
    QUndoCommand(parent),
    m_columnLeft(QList<BattleMapSquare*>()),
    m_userInterface(userInterface),
    m_battleMap(battleMap),
    m_battleMapSceneSection(battleMapSceneSection),
    m_masterScreenHandler(masterScreenHandler),
    m_playerScreenHandler(playerScreenHandler)
{
}

/*!
 * \brief This function is the destructor of the class UndoCommandInsertColumnLeft.
 */
UndoCommandInsertColumnLeft::~UndoCommandInsertColumnLeft()
{
    /* delete column left */
    for (quint32 columnIdx = 0U; columnIdx < m_columnLeft.count(); columnIdx++)
    {
        delete m_columnLeft[columnIdx];
    }
}

/*!
 * \brief This function undos this command.
 */
void UndoCommandInsertColumnLeft::undo()
{
    QSettings settings;

    /* delete column to the left of Battle Map */
    m_columnLeft = m_battleMap->deleteColumnLeft();

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
    quint32 numberColumnsOnPlayerScreen = static_cast<quint32>(calcScreenWidthInInches(settings.value(CONFIGKEY_PLAYERSCREEN_DIAGONAL).toReal(), settings.value(CONFIGKEY_PLAYERSCREEN_RESOLUTION_HEIGHT).toUInt(), settings.value(CONFIGKEY_PLAYERSCREEN_RESOLUTION_WIDTH).toUInt()));
    if (m_battleMap->getNumberColumns() < numberColumnsOnPlayerScreen)
    {
        /* decrement number of columns of Battle Map scene section */
        m_battleMapSceneSection->setNumberColumnsSceneSection(m_battleMapSceneSection->getNumberColumnsSceneSection() - 1U);
    }
    else
    {
        if (0U < m_battleMapSceneSection->getIndexFirstColumnSceneSection())
        {
            /* decrement index of first column of Battle Map scene section */
            m_battleMapSceneSection->setIndexFirstColumnSceneSection(m_battleMapSceneSection->getIndexFirstColumnSceneSection() - 1U);
        }
    }

    /* delete Battle Map square graphics items for screen handlers */
    m_masterScreenHandler->deleteColumnLeft();
    m_playerScreenHandler->deleteColumnLeft();
}

/*!
 * \brief This function applies or redos this command.
 */
void UndoCommandInsertColumnLeft::redo()
{
    QSettings settings;

    /* insert new column to the left of Battle Map */
    m_battleMap->insertColumnLeft(m_columnLeft);
    m_columnLeft.clear();

    /* enable actions for decrement depending on current number of columns */
    if (BATTLEMAP_MINIMUMNUMBERROWSANDCOLUMNS < m_battleMap->getNumberColumns())
    {
        m_userInterface->actionDeleteColumnLeft->setEnabled(true);
        m_userInterface->actionDeleteColumnRight->setEnabled(true);
    }

    /* check whether number of columns displayable on player screen is greater than or equal to total number of columns of Battle Map */
    quint32 numberColumnsOnPlayerScreen = static_cast<quint32>(calcScreenWidthInInches(settings.value(CONFIGKEY_PLAYERSCREEN_DIAGONAL).toReal(), settings.value(CONFIGKEY_PLAYERSCREEN_RESOLUTION_HEIGHT).toUInt(), settings.value(CONFIGKEY_PLAYERSCREEN_RESOLUTION_WIDTH).toUInt()));
    if (m_battleMap->getNumberColumns() <= numberColumnsOnPlayerScreen)
    {
        /* increment number of columns of Battle Map scene section */
        m_battleMapSceneSection->setNumberColumnsSceneSection(m_battleMapSceneSection->getNumberColumnsSceneSection() + 1U);
    }
    else
    {
        /* increment index of first column of Battle Map scene section */
        m_battleMapSceneSection->setIndexFirstColumnSceneSection(m_battleMapSceneSection->getIndexFirstColumnSceneSection() + 1U);
    }

    /* insert new Battle Map square graphics items for screen handlers */
    m_masterScreenHandler->insertColumnLeft();
    m_playerScreenHandler->insertColumnLeft();
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
