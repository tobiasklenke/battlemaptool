#ifndef BATTLEMAPSCENESECTION_H
#define BATTLEMAPSCENESECTION_H

/****************************************************************************************************************************************************
 * INCLUDES                                                                                                                                         *
 ****************************************************************************************************************************************************/

#include <QtGlobal>

/****************************************************************************************************************************************************
 * CLASS DECLARATION                                                                                                                                *
 ****************************************************************************************************************************************************/

/*!
 * \brief This class implements the functionality needed for the Battle Map scene section to be displayed on the player screen.
 */
class BattleMapSceneSection
{

public:

    /*! *********************************************************************************************************************************************
     * \brief   This function is the constructor of the class BattleMapSceneSection                                                                 *
     *                                                                                                                                              *
     * \details -                                                                                                                                   *
     *                                                                                                                                              *
     * \return  This function does not have any return value.                                                                                       *
     ************************************************************************************************************************************************/
    BattleMapSceneSection();

    /*! *********************************************************************************************************************************************
     * \brief   This function is the destructor of the class BattleMapSceneSection                                                                  *
     *                                                                                                                                              *
     * \details -                                                                                                                                   *
     *                                                                                                                                              *
     * \return  This function does not have any return value.                                                                                       *
     ************************************************************************************************************************************************/
    ~BattleMapSceneSection();

    /*! *********************************************************************************************************************************************
     * \brief   This function returns the value of the member variable m_indexFirstRowSceneSection.                                                 *
     *                                                                                                                                              *
     * \details -                                                                                                                                   *
     *                                                                                                                                              *
     * \return  This function returns the value of the member variable m_indexFirstRowSceneSection.                                                 *
     ************************************************************************************************************************************************/
    quint32 getIndexFirstRowSceneSection() const;

    /*! *********************************************************************************************************************************************
     * \brief   This function sets the value of the member variable m_indexFirstRowSceneSection.                                                    *
     *                                                                                                                                              *
     * \details -                                                                                                                                   *
     *                                                                                                                                              *
     * \param   indexFirstRowSceneSection     Index of the first row of the Battle Map scene section                                                *
     *                                                                                                                                              *
     * \return  This function does not have any return value.                                                                                       *
     ************************************************************************************************************************************************/
    void setIndexFirstRowSceneSection(quint32 indexFirstRowSceneSection);

    /*! *********************************************************************************************************************************************
     * \brief   This function returns the value of the member variable m_indexFirstColumnSceneSection.                                              *
     *                                                                                                                                              *
     * \details -                                                                                                                                   *
     *                                                                                                                                              *
     * \return  This function returns the value of the member variable m_indexFirstColumnSceneSection.                                              *
     ************************************************************************************************************************************************/
    quint32 getIndexFirstColumnSceneSection() const;

    /*! *********************************************************************************************************************************************
     * \brief   This function sets the value of the member variable m_indexFirstColumnSceneSection.                                                 *
     *                                                                                                                                              *
     * \details -                                                                                                                                   *
     *                                                                                                                                              *
     * \param   indexFirstColumnSceneSection  Index of the first column of the Battle Map scene section                                             *
     *                                                                                                                                              *
     * \return  This function does not have any return value.                                                                                       *
     ************************************************************************************************************************************************/
    void setIndexFirstColumnSceneSection(quint32 indexFirstColumnSceneSection);

    /*! *********************************************************************************************************************************************
     * \brief   This function returns the value of the member variable m_numberRowsSceneSection.                                                    *
     *                                                                                                                                              *
     * \details -                                                                                                                                   *
     *                                                                                                                                              *
     * \return  This function returns the value of the member variable m_numberRowsSceneSection.                                                    *
     ************************************************************************************************************************************************/
    quint32 getNumberRowsSceneSection() const;

    /*! *********************************************************************************************************************************************
     * \brief   This function sets the value of the member variable m_numberRowsSceneSection.                                                       *
     *                                                                                                                                              *
     * \details -                                                                                                                                   *
     *                                                                                                                                              *
     * \param   numberRowsSceneSection        Number of rows of the Battle Map scene section                                                        *
     *                                                                                                                                              *
     * \return  This function does not have any return value.                                                                                       *
     ************************************************************************************************************************************************/
    void setNumberRowsSceneSection(quint32 numberRowsSceneSection);

    /*! *********************************************************************************************************************************************
     * \brief   This function returns the value of the member variable m_numberColumnsSceneSection.                                                 *
     *                                                                                                                                              *
     * \details -                                                                                                                                   *
     *                                                                                                                                              *
     * \return  This function returns the value of the member variable m_numberColumnsSceneSection.                                                 *
     ************************************************************************************************************************************************/
    quint32 getNumberColumnsSceneSection() const;

    /*! *********************************************************************************************************************************************
     * \brief   This function sets the value of the member variable m_numberColumnsSceneSection.                                                    *
     *                                                                                                                                              *
     * \details -                                                                                                                                   *
     *                                                                                                                                              *
     * \param   numberColumnsSceneSection     Number of columns of the Battle Map scene section                                                     *
     *                                                                                                                                              *
     * \return  This function does not have any return value.                                                                                       *
     ************************************************************************************************************************************************/
    void setNumberColumnsSceneSection(quint32 numberColumnsSceneSection);

protected: /* - */

private:

    /*!
     * \brief This is the index of the first row to be displayed on the player screen.
     */
    quint32 m_indexFirstRowSceneSection;

    /*!
     * \brief This is the index of the first column to be displayed on the player screen.
     */
    quint32 m_indexFirstColumnSceneSection;

    /*!
     * \brief This is the number of rows to be displayed on the player screen.
     */
    quint32 m_numberRowsSceneSection;

    /*!
     * \brief This is the number of columns to be displayed on the player screen.
     */
    quint32 m_numberColumnsSceneSection;
};

#endif // BATTLEMAPSCENESECTION_H
