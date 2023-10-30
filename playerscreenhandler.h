#ifndef PLAYERSCREENHANDLER_H
#define PLAYERSCREENHANDLER_H

/****************************************************************************************************************************************************
 * INCLUDES                                                                                                                                         *
 ****************************************************************************************************************************************************/

#include <QGraphicsView>
#include <QParallelAnimationGroup>
#include <QPropertyAnimation>

#include "battlemap.h"
#include "battlemapsceneplayerscreen.h"
#include "battlemapscenesection.h"
#include "customgraphicspixmapitem.h"
#include "screencalc.h"

/****************************************************************************************************************************************************
 * CLASS DECLARATION                                                                                                                                *
 ****************************************************************************************************************************************************/

/*!
 * \brief This class implements the functionality of the player screen handling.
 */
class PlayerScreenHandler
{

public:

    /*! *********************************************************************************************************************************************
     * \brief   This function is the constructor of the class PlayerScreenHandler.                                                                  *
     *                                                                                                                                              *
     * \details -                                                                                                                                   *
     *                                                                                                                                              *
     * \return  This function does not have any return value.                                                                                       *
     ************************************************************************************************************************************************/
    PlayerScreenHandler();

    /*! *********************************************************************************************************************************************
     * \brief   This function is the destructor of the class PlayerScreenHandler.                                                                   *
     *                                                                                                                                              *
     * \details This function deletes the objects pointed to by pBattleMapScene and contained in the nested QList member variable                   *
	 *          m_battleMapSquaresGraphicsItems.                                                                                                    *
     *                                                                                                                                              *
     * \return  This function does not have any return value.                                                                                       *
     ************************************************************************************************************************************************/
    ~PlayerScreenHandler();

    /*! *********************************************************************************************************************************************
     * \brief   This function sets the address of the member variable pGraphicsView.                                                                *
     *                                                                                                                                              *
     * \details This function sets the address of the member variable pGraphicsView and sets the Battle Map scene.                                  *
     *                                                                                                                                              *
     * \param   graphicsView                  Address of the graphics view to display the Battle Map scene on                                       *
     *                                                                                                                                              *
     * \return  This function does not have any return value.                                                                                       *
     ************************************************************************************************************************************************/
    void setGraphicsView(QGraphicsView *graphicsView);

    /*! *********************************************************************************************************************************************
     * \brief   This function sets the address of the member variable pBattleMap.                                                                   *
     *                                                                                                                                              *
     * \details This function sets the address of the member variable pBattleMap and updates the graphics items of the Battle Map squares.          *
     *                                                                                                                                              *
     * \param   battleMap                     Address of the Battle Map                                                                             *
     *                                                                                                                                              *
     * \return  This function does not have any return value.                                                                                       *
     ************************************************************************************************************************************************/
    void setBattleMap(BattleMap *battleMap);

    /*! *********************************************************************************************************************************************
     * \brief   This function sets the address of the member variable pBattleMapSceneSection.                                                       *
     *                                                                                                                                              *
     * \details -                                                                                                                                   *
     *                                                                                                                                              *
     * \param   battleMapSceneSection         Address of the Battle Map scene section                                                               *
     *                                                                                                                                              *
     * \return  This function does not have any return value.                                                                                       *
     ************************************************************************************************************************************************/
    void setBattleMapSceneSection(BattleMapSceneSection *battleMapSceneSection);

    /*! *********************************************************************************************************************************************
     * \brief   This function sets the operation mode.                                                                                              *
     *                                                                                                                                              *
     * \details This function sets the operation mode and the cursor according to the operation mode.                                               *
     *                                                                                                                                              *
     * \param   operationMode                 Operation mode                                                                                        *
     *                                                                                                                                              *
     * \return  This function does not have any return value.                                                                                       *
     ************************************************************************************************************************************************/
    void setOperationMode(operationMode_t operationMode);

    /*! *********************************************************************************************************************************************
     * \brief   This function initializes the Battle Map image without showing it.                                                                  *
     *                                                                                                                                              *
     * \details This function resets the Battle Map scene and adds all the Battle Map squares from the Battle Map to the Battle Map scene without   *
     *          showing them.                                                                                                                       *
     *                                                                                                                                              *
     * \return  This function does not have any return value.                                                                                       *
     ************************************************************************************************************************************************/
    void initBattleMapImage();

    /*! *********************************************************************************************************************************************
     * \brief   This function updates the Battle Map image                   .                                                                      *
     *                                                                                                                                              *
     * \details This function updates the visibility of the Battle Map squares depending on whether they are displayed on the player screen.        *
     *                                                                                                                                              *
     * \return  This function does not have any return value.                                                                                       *
     ************************************************************************************************************************************************/
    void updateBattleMapImage();

protected: /* - */

signals: /* - */

private slots: /* - */

private:

    /*! *********************************************************************************************************************************************
     * \brief   This function deletes the graphics items of the Battle Map squares.                                                                 *
     *                                                                                                                                              *
     * \details -                                                                                                                                   *
     *                                                                                                                                              *
     * \return  This function does not have any return value.                                                                                       *
     ************************************************************************************************************************************************/
    void deleteBattleMapSquaresGraphicsItems();

    /*! *********************************************************************************************************************************************
     * \brief   This function updates the graphics items of the Battle Map squares.                                                                 *
     *                                                                                                                                              *
     * \details -                                                                                                                                   *
     *                                                                                                                                              *
     * \return  This function does not have any return value.                                                                                       *
     ************************************************************************************************************************************************/
    void updateBattleMapSquaresGraphicsItems();

    /*! *********************************************************************************************************************************************
     * \brief   This function deletes the Battle Map scene.                                                                                         *
     *                                                                                                                                              *
     * \details -                                                                                                                                   *
     *                                                                                                                                              *
     * \return  This function does not have any return value.                                                                                       *
     ************************************************************************************************************************************************/
    void deleteBattleMapScene();

    /*! *********************************************************************************************************************************************
     * \brief   This function updates the visibility of the Battle Map squares depending on whether they are displayed on the player screen.        *
     *                                                                                                                                              *
     * \details This function updates the visibility of the Battle Map squares depending on whether they are displayed on the player screen and     *
	 *          sets the rect of the Battle Map scene according to the visible Battle Map squares.                                                  *
	 *                                                                                                                                              *
     * \return  This function does not have any return value.                                                                                       *
     ************************************************************************************************************************************************/
    void updateBattleMapSquaresVisibility();

    /*! *********************************************************************************************************************************************
     * \brief   This function updates the opacity of the Battle Map squares depending on whether they are covered.                                  *
     *                                                                                                                                              *
     * \details This function updates the opacity of the Battle Map squares depending on whether they are covered. In case that a Battle Map square *
	 *          is visible and therefore located within the displayed Battle Map scene section, it is checked if the Battle Map square shall be     *
	 *          covered. If so, the opacity is set to the minimum value. Otherwise and if the opacity has currently the minimum value, an opacity   *
	 *          animation is added that changes the opacity gradually from minimum to maximum value. In case that a Battle Map square is invisible  *
	 *          and therefore located outside the displayed Battle Map scene section, it is checked if the Battle Map square shall be covered. If   *
	 *          so, the opacity is set to the minimum value. Otherwise, the opacity is set immediateöy to the maximum value.                        *
     *                                                                                                                                              *
     * \return  This function does not have any return value.                                                                                       *
     ************************************************************************************************************************************************/
    void updateBattleMapSquaresOpacity();

    /*!
     * \brief This is a pointer to the graphics view.
     */
    QGraphicsView *pGraphicsView;

    /*!
     * \brief This is a pointer to the Battle Map.
     */
    BattleMap *pBattleMap;

    /*!
     * \brief This is a pointer to the Battle Map scene section.
     */
    BattleMapSceneSection *pBattleMapSceneSection;

    /*!
     * \brief This is a pointer to the Battle Map scene.
     */
    BattleMapScenePlayerScreen *pBattleMapScene;

    /*!
     * \brief This is the operation mode.
     */
    operationMode_t m_operationMode;

    /*!
     * \brief This is the variable containing the graphics items of the Battle Map squares.
     */
    QList<QList<CustomGraphicsPixmapItem*>> m_battleMapSquaresGraphicsItems;

    /*!
     * \brief This is the number of pixels per Battle Map square.
     */
    quint32 m_pixelsPerBattleMapSquare;
};

#endif // PLAYERSCREENHANDLER_H
