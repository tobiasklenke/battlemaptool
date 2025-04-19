#ifndef WIZARDNEWBATTLEMAP_H
#define WIZARDNEWBATTLEMAP_H

#include <QWizard>

#include "battlemap.h"
#include "wizardpagenewbattlemapdisguise.h"
#include "wizardpagenewbattlemaporiginal.h"

/****************************************************************************************************************************************************
 * CLASS DECLARATION                                                                                                                                *
 ****************************************************************************************************************************************************/

namespace Ui
{
    class WizardNewBattleMap;
}

/*!
 * \brief This class implements the functionality needed for the creation of a new Battle Map.
 */
class WizardNewBattleMap : public QWizard
{
    Q_OBJECT

public:

    /*! *********************************************************************************************************************************************
     * \brief   This function is the constructor of the class WizardNewBattleMap.                                                                   *
     *                                                                                                                                              *
     * \details This function sets up the user interface and shares the Battle Map with the wizard pages.                                           *
     *                                                                                                                                              *
     * \param   parent                        Parent of the class WizardNewBattleMap                                                                *
     *                                                                                                                                              *
     * \return  This function does not have any return value.                                                                                       *
     ************************************************************************************************************************************************/
    WizardNewBattleMap(QWidget *parent = nullptr);

    /*! *********************************************************************************************************************************************
     * \brief   This function is the destructor of the class WizardNewBattleMap.                                                                    *
     *                                                                                                                                              *
     * \details This function deletes the objects created in the constructor.                                                                       *
     *                                                                                                                                              *
     * \return  This function does not have any return value.                                                                                       *
     ************************************************************************************************************************************************/
    ~WizardNewBattleMap();

    /*! *********************************************************************************************************************************************
     * \brief   This function returns the address of the newly created Battle Map object.                                                           *
     *                                                                                                                                              *
     * \details -                                                                                                                                   *
     *                                                                                                                                              *
     * \return  This function returns the address of the newly created Battle Map object.                                                           *
     ************************************************************************************************************************************************/
    BattleMap * getBattleMap() const;

protected: /* - */

signals: /* - */

private slots: /* - */

private:

    /*!
     * \brief This is a pointer to the user interface of the class WizardNewBattleMap.
     */
    Ui::WizardNewBattleMap *m_userInterface;

    /*!
     * \brief This is a pointer to the newly created Battle Map.
     */
    BattleMap *m_battleMap;
};

#endif // WIZARDNEWBATTLEMAP_H
