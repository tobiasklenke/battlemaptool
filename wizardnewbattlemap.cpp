/****************************************************************************************************************************************************
 * INCLUDES                                                                                                                                         *
 ****************************************************************************************************************************************************/

#include "wizardnewbattlemap.h"
#include "ui_wizardnewbattlemap.h"

/****************************************************************************************************************************************************
 * DEFINITION OF PUBLIC FUNCTIONS                                                                                                                   *
 ****************************************************************************************************************************************************/

/*!
 * \brief This function is the constructor of the class WizardNewBattleMap.
 */
WizardNewBattleMap::WizardNewBattleMap(QWidget *parent) :
    QWizard(parent),
    m_userInterface(new Ui::WizardNewBattleMap),
    m_battleMap(new BattleMap())
{
    /* set up the user interface */
    m_userInterface->setupUi(this);
    setButtonText(BackButton, "Original");
    setButtonText(NextButton, "Disguise");
    setButtonText(FinishButton, "OK");

    /* create wizard pages */
    WizardPageNewBattleMapOriginal* wizardPageNewBattleMapOriginal= new WizardPageNewBattleMapOriginal(m_battleMap, this);
    WizardPageNewBattleMapDisguise* wizardPageNewBattleMapDisguise= new WizardPageNewBattleMapDisguise(m_battleMap, this);
    addPage(wizardPageNewBattleMapOriginal);
    addPage(wizardPageNewBattleMapDisguise);
}

/*!
 * \brief This function is the destructor of the class WizardNewBattleMap.
 */
WizardNewBattleMap::~WizardNewBattleMap()
{
    /* delete objects created in the constructor */
    delete m_userInterface;
    delete m_battleMap;
}

/*!
 * \brief This function returns the address of the newly created Battle Map object.
 */
BattleMap * WizardNewBattleMap::getBattleMap() const
{
    return m_battleMap;
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
