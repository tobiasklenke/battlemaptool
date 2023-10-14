/****************************************************************************************************************************************************
 * INCLUDES                                                                                                                                         *
 ****************************************************************************************************************************************************/

#include "battlemapscenesection.h"

/****************************************************************************************************************************************************
 * DEFINITION OF PUBLIC FUNCTIONS                                                                                                                   *
 ****************************************************************************************************************************************************/

/*!
 * \brief This function is the constructor of the class BattleMapSceneSection.
 */
BattleMapSceneSection::BattleMapSceneSection() :
    m_indexFirstRowSceneSection(0U),
    m_indexFirstColumnSceneSection(0U),
    m_numberRowsSceneSection(0U),
    m_numberColumnsSceneSection(0U)
{
}

/*!
 * \brief This function is the destructor of the class BattleMap.
 */
BattleMapSceneSection::~BattleMapSceneSection()
{
}

/*!
 * \brief This function returns the value of the member variable m_indexFirstRowSceneSection.
 */
quint32 BattleMapSceneSection::getIndexFirstRowSceneSection() const
{
    return m_indexFirstRowSceneSection;
}

/*!
 * \brief This function sets the value of the member variable m_indexFirstRowSceneSection.
 */
void BattleMapSceneSection::setIndexFirstRowSceneSection(quint32 indexFirstRowSceneSection)
{
    m_indexFirstRowSceneSection = indexFirstRowSceneSection;
}

/*!
 * \brief This function returns the value of the member variable m_indexFirstColumnSceneSection.
 */
quint32 BattleMapSceneSection::getIndexFirstColumnSceneSection() const
{
    return m_indexFirstColumnSceneSection;
}

/*!
 * \brief This function sets the value of the member variable m_indexFirstColumnSceneSection.
 */
void BattleMapSceneSection::setIndexFirstColumnSceneSection(quint32 indexFirstColumnSceneSection)
{
    m_indexFirstColumnSceneSection = indexFirstColumnSceneSection;
}

/*!
 * \brief This function returns the value of the member variable m_numberRowsSceneSection.
 */
quint32 BattleMapSceneSection::getNumberRowsSceneSection() const
{
    return m_numberRowsSceneSection;
}

/*!
 * \brief This function sets the value of the member variable m_numberRowsSceneSection.
 */
void BattleMapSceneSection::setNumberRowsSceneSection(quint32 numberRowsSceneSection)
{
    m_numberRowsSceneSection = numberRowsSceneSection;
}

/*!
 * \brief This function returns the value of the member variable m_numberColumnsSceneSection.
 */
quint32 BattleMapSceneSection::getNumberColumnsSceneSection() const
{
    return m_numberColumnsSceneSection;
}

/*!
 * \brief This function sets the value of the member variable m_numberColumnsSceneSection.
 */
void BattleMapSceneSection::setNumberColumnsSceneSection(quint32 numberColumnsSceneSection)
{
    m_numberColumnsSceneSection = numberColumnsSceneSection;
}

/****************************************************************************************************************************************************
 * DEFINITION OF PROTECTED FUNCTIONS                                                                                                                *
 ****************************************************************************************************************************************************/

/* - */

/****************************************************************************************************************************************************
 * DEFINITION OF PRIVATE FUNCTIONS                                                                                                                  *
 ****************************************************************************************************************************************************/

/* - */
