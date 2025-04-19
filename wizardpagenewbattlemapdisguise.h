#ifndef WIZARDPAGENEWBATTLEMAPDISGUISE_H
#define WIZARDPAGENEWBATTLEMAPDISGUISE_H

/****************************************************************************************************************************************************
 * INCLUDES                                                                                                                                         *
 ****************************************************************************************************************************************************/

#include <QMessageBox>
#include <QFileDialog>
#include <QWizardPage>

#include "battlemap.h"

/****************************************************************************************************************************************************
 * CLASS DECLARATION                                                                                                                                *
 ****************************************************************************************************************************************************/

namespace Ui
{
    class WizardPageNewBattleMapDisguise;
}

/*!
 * \brief This class implements the functionality needed for the selection of a disguise of a new Battle Map.
 */
class WizardPageNewBattleMapDisguise : public QWizardPage
{
    Q_OBJECT

public:

    /*! *********************************************************************************************************************************************
     * \brief   This function is the constructor of the class WizardPageNewBattleMapDisguise.                                                       *
     *                                                                                                                                              *
     * \details This function sets up the user interface.                                                                                           *
     *                                                                                                                                              *
     * \param   battleMap                     Battle Map                                                                                            *
     * \param   parent                        Parent of the class WizardPageNewBattleMapDisguise                                                    *
     *                                                                                                                                              *
     * \return  This function does not have any return value.                                                                                       *
     ************************************************************************************************************************************************/
    WizardPageNewBattleMapDisguise(BattleMap * battleMap, QWidget *parent = nullptr);

    /*! *********************************************************************************************************************************************
     * \brief   This function is the destructor of the class WizardPageNewBattleMapDisguise.                                                        *
     *                                                                                                                                              *
     * \details This function deletes the objects created in the constructor.                                                                       *
     *                                                                                                                                              *
     * \return  This function does not have any return value.                                                                                       *
     ************************************************************************************************************************************************/
    ~WizardPageNewBattleMapDisguise();

    /*! *********************************************************************************************************************************************
     * \brief   This function prepares the page just before it is shown.                                                                            *
     *                                                                                                                                              *
     * \details This function connects the signals and slots of the push buttons of the wizard.                                                     *
     *                                                                                                                                              *
     * \return  This function does not have any return value.                                                                                       *
     ************************************************************************************************************************************************/
    void initializePage() override;

    /*! *********************************************************************************************************************************************
     * \brief   TODO                                                                                                                                *
     *                                                                                                                                              *
     * \details -                                                                                                                                   *
     *                                                                                                                                              *
     * \return  This function does not have any return value.                                                                                       *
     ************************************************************************************************************************************************/
    bool isComplete() const override;

protected: /* - */

signals: /* - */

private slots:

    /*! *********************************************************************************************************************************************
     * \brief   This function handles a click on the Back button of the wizard.                                                                     *
     *                                                                                                                                              *
     * \details This function checks whether the page is currently shown and, if so, resets the Battle Map.                                         *
     *                                                                                                                                              *
     * \return  This function does not have any return value.                                                                                       *
     ************************************************************************************************************************************************/
    void releasedWizardPushButtonBack();

    /*! *********************************************************************************************************************************************
     * \brief   This function handles a click on the Finish button of the wizard.                                                                   *
     *                                                                                                                                              *
     * \details TODO                                                                                                                                *
     *                                                                                                                                              *
     * \return  This function does not have any return value.                                                                                       *
     ************************************************************************************************************************************************/
    void releasedWizardPushButtonFinish();

private:

    /*!
     * \brief This is a pointer to the user interface of the class WizardPageNewBattleMapDisguise.
     */
    Ui::WizardPageNewBattleMapDisguise *m_userInterface;

    /*!
     * \brief This is a pointer to the newly created Battle Map.
     */
    BattleMap *m_battleMap;
};

#endif // WIZARDPAGENEWBATTLEMAPDISGUISE_H
