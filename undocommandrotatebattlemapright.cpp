/****************************************************************************************************************************************************
 * INCLUDES                                                                                                                                         *
 ****************************************************************************************************************************************************/

#include "undocommandrotatebattlemapright.h"

/****************************************************************************************************************************************************
 * DEFINITION OF PUBLIC FUNCTIONS                                                                                                                   *
 ****************************************************************************************************************************************************/

/*!
 * \brief This function is the constructor of the class UndoCommandRotateBattleMapRight.
 */
UndoCommandRotateBattleMapRight::UndoCommandRotateBattleMapRight(Ui::MainWindow *userInterface, BattleMap *battleMap, BattleMapSceneSection *battleMapSceneSection, MasterScreenHandler *masterScreenHandler, PlayerScreenHandler *playerScreenHandler, QUndoCommand *parent) :
    QUndoCommand(parent),
    m_userInterface(userInterface),
    m_battleMap(battleMap),
    m_battleMapSceneSection(battleMapSceneSection),
    m_masterScreenHandler(masterScreenHandler),
    m_playerScreenHandler(playerScreenHandler)
{
}

/*!
 * \brief This function is the destructor of the class UndoCommandRotateBattleMapRight.
 */
UndoCommandRotateBattleMapRight::~UndoCommandRotateBattleMapRight()
{
}

/*!
 * \brief This function undos this command.
 */
void UndoCommandRotateBattleMapRight::undo()
{
    QSettings settings;

    /* rotate Battle Map left */
    m_battleMap->rotateLeft();

    /* reset indexes of first row and column of Battle Map scene section */
    m_battleMapSceneSection->setIndexFirstRowSceneSection(0U);
    m_battleMapSceneSection->setIndexFirstColumnSceneSection(0U);

    /* check whether number of rows displayable on player screen is less than total number of rows of Battle Map and set number of rows of Battle Map scene section to less number */
    quint32 numberRowsOnPlayerScreen = static_cast<quint32>(calcScreenHeightInInches(settings.value(CONFIGKEY_PLAYERSCREEN_DIAGONAL).toReal(), settings.value(CONFIGKEY_PLAYERSCREEN_RESOLUTION_HEIGHT).toUInt(), settings.value(CONFIGKEY_PLAYERSCREEN_RESOLUTION_WIDTH).toUInt()));
    if (numberRowsOnPlayerScreen < m_battleMap->getNumberRows())
    {
        m_battleMapSceneSection->setNumberRowsSceneSection(numberRowsOnPlayerScreen);
    }
    else
    {
        m_battleMapSceneSection->setNumberRowsSceneSection(m_battleMap->getNumberRows());
    }

    /* check whether number of columns displayable on player screen is less than total number of columns of Battle Map and set number of columns of Battle Map scene section to less number */
    quint32 numberColumnsOnPlayerScreen = static_cast<quint32>(calcScreenWidthInInches(settings.value(CONFIGKEY_PLAYERSCREEN_DIAGONAL).toReal(), settings.value(CONFIGKEY_PLAYERSCREEN_RESOLUTION_HEIGHT).toUInt(), settings.value(CONFIGKEY_PLAYERSCREEN_RESOLUTION_WIDTH).toUInt()));
    if (numberColumnsOnPlayerScreen < m_battleMap->getNumberColumns())
    {
        m_battleMapSceneSection->setNumberColumnsSceneSection(numberColumnsOnPlayerScreen);
    }
    else
    {
        m_battleMapSceneSection->setNumberColumnsSceneSection(m_battleMap->getNumberColumns());
    }

    /* rotate Battle Map left on the screen handlers */
    m_masterScreenHandler->rotateBattleMapLeft();
    m_playerScreenHandler->rotateBattleMapLeft();
}

/*!
 * \brief This function applies or redos this command.
 */
void UndoCommandRotateBattleMapRight::redo()
{
    QSettings settings;

    /* rotate Battle Map right */
    m_battleMap->rotateRight();

    /* reset indexes of first row and column of Battle Map scene section */
    m_battleMapSceneSection->setIndexFirstRowSceneSection(0U);
    m_battleMapSceneSection->setIndexFirstColumnSceneSection(0U);

    /* check whether number of rows displayable on player screen is less than total number of rows of Battle Map and set number of rows of Battle Map scene section to less number */
    quint32 numberRowsOnPlayerScreen = static_cast<quint32>(calcScreenHeightInInches(settings.value(CONFIGKEY_PLAYERSCREEN_DIAGONAL).toReal(), settings.value(CONFIGKEY_PLAYERSCREEN_RESOLUTION_HEIGHT).toUInt(), settings.value(CONFIGKEY_PLAYERSCREEN_RESOLUTION_WIDTH).toUInt()));
    if (numberRowsOnPlayerScreen < m_battleMap->getNumberRows())
    {
        m_battleMapSceneSection->setNumberRowsSceneSection(numberRowsOnPlayerScreen);
    }
    else
    {
        m_battleMapSceneSection->setNumberRowsSceneSection(m_battleMap->getNumberRows());
    }

    /* check whether number of columns displayable on player screen is less than total number of columns of Battle Map and set number of columns of Battle Map scene section to less number */
    quint32 numberColumnsOnPlayerScreen = static_cast<quint32>(calcScreenWidthInInches(settings.value(CONFIGKEY_PLAYERSCREEN_DIAGONAL).toReal(), settings.value(CONFIGKEY_PLAYERSCREEN_RESOLUTION_HEIGHT).toUInt(), settings.value(CONFIGKEY_PLAYERSCREEN_RESOLUTION_WIDTH).toUInt()));
    if (numberColumnsOnPlayerScreen < m_battleMap->getNumberColumns())
    {
        m_battleMapSceneSection->setNumberColumnsSceneSection(numberColumnsOnPlayerScreen);
    }
    else
    {
        m_battleMapSceneSection->setNumberColumnsSceneSection(m_battleMap->getNumberColumns());
    }

    /* rotate Battle Map right on the screen handlers */
    m_masterScreenHandler->rotateBattleMapRight();
    m_playerScreenHandler->rotateBattleMapRight();
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
