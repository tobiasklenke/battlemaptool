/****************************************************************************************************************************************************
 * INCLUDES                                                                                                                                         *
 ****************************************************************************************************************************************************/

#include "wizardpagenewbattlemapdisguise.h"
#include "ui_wizardpagenewbattlemapdisguise.h"

/****************************************************************************************************************************************************
 * DEFINITION OF PUBLIC FUNCTIONS                                                                                                                   *
 ****************************************************************************************************************************************************/

/*!
 * \brief This function is the constructor of the class WizardPageNewBattleMapDisguise.
 */
WizardPageNewBattleMapDisguise::WizardPageNewBattleMapDisguise(BattleMap *battleMap, QWidget *parent) :
    QWizardPage(parent),
    m_userInterface(new Ui::WizardPageNewBattleMapDisguise),
    m_battleMap(battleMap)
{
    /* set up the user interface */
    m_userInterface->setupUi(this);
}

/*!
 * \brief This function is the destructor of the class WizardPageNewBattleMapDisguise.
 */
WizardPageNewBattleMapDisguise::~WizardPageNewBattleMapDisguise()
{
    /* delete objects created in the constructor */
    delete m_userInterface;
}

/*!
 * \brief TODO
 */
void WizardPageNewBattleMapDisguise::initializePage()
{
    /* connect signals and slots of push buttons of wizard */
    connect(wizard()->button(QWizard::BackButton), SIGNAL(released()), this, SLOT(releasedWizardPushButtonBack()));
    connect(wizard()->button(QWizard::FinishButton), SIGNAL(released()), this, SLOT(releasedWizardPushButtonFinish()));
}

/*!
 * \brief TODO
 */
bool WizardPageNewBattleMapDisguise::isComplete() const
{
    qDebug() << __func__ << "Disguise";

    //TODO
    return true;
}

/****************************************************************************************************************************************************
 * DEFINITION OF PROTECTED FUNCTIONS                                                                                                                *
 ****************************************************************************************************************************************************/

/* - */

/****************************************************************************************************************************************************
 * DEFINITION OF PRIVATE SLOT FUNCTIONS                                                                                                             *
 ****************************************************************************************************************************************************/

/*!
 * \brief This function handles a click on the Back button of the wizard.
 */
void WizardPageNewBattleMapDisguise::releasedWizardPushButtonBack()
{
    /* check whether page is currently shown */
    if (wizard()->page(wizard()->currentId()) == this)
    {
        m_battleMap->deleteBattleMapSquares();
    }
}

/*!
 * \brief This function handles a click on the Finish button of the wizard.
 */
void WizardPageNewBattleMapDisguise::releasedWizardPushButtonFinish()
{
    /* check whether page is currently shown */
    if (wizard()->page(wizard()->currentId()) == this)
    {
        //TODO
    }
}

/****************************************************************************************************************************************************
 * DEFINITION OF PRIVATE FUNCTIONS                                                                                                                  *
 ****************************************************************************************************************************************************/

/* - */
