#ifndef WIZARDPAGENEWBATTLEMAPDISGUISE_H
#define WIZARDPAGENEWBATTLEMAPDISGUISE_H

/****************************************************************************************************************************************************
 * INCLUDES                                                                                                                                         *
 ****************************************************************************************************************************************************/

#include <QFileDialog>
#include <QGraphicsItem>
#include <QMessageBox>
#include <QTimer>
#include <QWizardPage>

#include "battlemap.h"
#include "battlemapscene.h"


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
     * \brief   This function determines whether the Finish button should be shown for this page or not.                                            *
     *                                                                                                                                              *
     * \details -                                                                                                                                   *
     *                                                                                                                                              *
     * \return  This function returns true, if the Finish button of the wizard should be shown. Otherwise, it returns false.                        *
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
     * \brief   This function handles the editing of lineEditSource.                                                                                *
     *                                                                                                                                              *
     * \return  This function does not have any return value.                                                                                       *
     ************************************************************************************************************************************************/
    void editingFinishedLineEditSource();

    /*! *********************************************************************************************************************************************
     * \brief   This function handles a click on pushButtonSelectSource.                                                                            *
     *                                                                                                                                              *
     * \details This function selects a source via a file dialog, synchronises the file path of the selected source with the text string of         *
     *          lineEditSource and handles the editing of lineEditSource afterwards.                                                                *
     *                                                                                                                                              *
     * \return  This function does not have any return value.                                                                                       *
     ************************************************************************************************************************************************/
    void releasedPushButtonSelectSource();

    /*! *********************************************************************************************************************************************
     * \brief   This function toggles the original and the disguise pixmaps.                                                                        *
     *                                                                                                                                              *
     * \return  This function does not have any return value.                                                                                       *
     ************************************************************************************************************************************************/
    void togglePixmaps();

private:

    /*! *********************************************************************************************************************************************
     * \brief   This function changes the member variable m_completePage and emits the signal completeChanged().                                    *
     *                                                                                                                                              *
     * \details -                                                                                                                                   *
     *                                                                                                                                              *
     * \param   completePage                  Information whether page ist complete                                                                 *
     *                                                                                                                                              *
     * \return  This function does not have any return value.                                                                                       *
     ************************************************************************************************************************************************/
    void setCompletePage(bool completePage);

    /*! *********************************************************************************************************************************************
     * \brief   This function deletes the graphics items of the Battle Map squares.                                                                 *
     *                                                                                                                                              *
     * \details This function deletes the graphics items of the Battle Map squares and removes all the graphics items from the list.                *
     *                                                                                                                                              *
     * \return  This function does not have any return value.                                                                                       *
     ************************************************************************************************************************************************/
    void deleteBattleMapSquareGraphicsItems();

    /*! *********************************************************************************************************************************************
     * \brief   This function updates the graphics items of the Battle Map squares.                                                                 *
     *                                                                                                                                              *
     * \return  This function does not have any return value.                                                                                       *
     ************************************************************************************************************************************************/
    void updateBattleMapSquareGraphicsItems();

    /*! *********************************************************************************************************************************************
     * \brief   This function deletes the Battle Map scene.                                                                                         *
     *                                                                                                                                              *
     * \details This function removes all remaining graphics items from the Battle Map scene and deletes m_battleMapScene afterwards.               *
     *                                                                                                                                              *
     * \return  This function does not have any return value.                                                                                       *
     ************************************************************************************************************************************************/
    void deleteBattleMapScene();

    /*! *********************************************************************************************************************************************
     * \brief   This function extracts the Battle Map from the Battle Map image.                                                                    *
     *                                                                                                                                              *
     * \return  This function does not have any return value.                                                                                       *
     ************************************************************************************************************************************************/
    void extractBattleMap();

    /*! *********************************************************************************************************************************************
     * \brief   This function shows the original and the disguise Battle Map images.                                                                *
     *                                                                                                                                              *
     * \return  This function does not have any return value.                                                                                       *
     ************************************************************************************************************************************************/
    void showBattleMapImages();

    /*! *********************************************************************************************************************************************
     * \brief   This function checks whether the Battle Map is disguisable.                                                                         *
     *                                                                                                                                              *
     * \return  This function returns true if the Battle Map is disguisable. Otherwise, it returns false.                                           *
     ************************************************************************************************************************************************/
    bool checkForDisguise();

    /*!
     * \brief This is a pointer to the user interface of the class WizardPageNewBattleMapDisguise.
     */
    Ui::WizardPageNewBattleMapDisguise *m_userInterface;

    /*!
     * \brief This is the information whether the page is completed.
     */
    bool m_completePage;

    /*!
     * \brief This is a pointer to the Battle Map scene that is set to GraphicsViewBattleMap.
     */
    BattleMapScene *m_battleMapScene;

    /*!
     * \brief This is the text to be shown in the Battle Map scene.
     */
    QGraphicsTextItem m_sceneText;

    /*!
     * \brief This is the pixmap of the Battle Map image.
     */
    QGraphicsPixmapItem m_battleMapImagePixmap;

    /*!
     * \brief This is a list of Battle Map lines building the Battle Map grid to be drawn for control purposes.
     */
    QList<QGraphicsLineItem*> m_battleMapLinesToDraw;

    /*!
     * \brief This is the variable containing the graphics items of the Battle Map squares.
     */
    QList<QList<QGraphicsPixmapItem*>> m_battleMapSquareGraphicsItems;

    /*!
     * \brief This is the timer variable for the toggle of the original and the disguise pixmaps.
     */
    QTimer m_pixmapToggleTimer;

    /*!
     * \brief This is the factor that is used for scaling the graphics view while scrolling.
     */
    qreal m_scaleFactor;

    /*!
     * \brief This is a pointer to the newly created Battle Map.
     */
    BattleMap *m_battleMap;
};

#endif // WIZARDPAGENEWBATTLEMAPDISGUISE_H
