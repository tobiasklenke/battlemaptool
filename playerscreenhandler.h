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
 * \brief This class implements the functionality needed for the handling of the player screen.
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
     * \details This function deletes the objects created in the constructor.                                                                       *
     *                                                                                                                                              *
     * \return  This function does not have any return value.                                                                                       *
     ************************************************************************************************************************************************/
    ~PlayerScreenHandler();

    /*! *********************************************************************************************************************************************
     * \brief   This function sets the address of the member variable m_graphicsView.                                                               *
     *                                                                                                                                              *
     * \details This function sets the address of the member variable m_graphicsView, sets the background color of the graphics view to black and   *
     *          removes the frame. Afterwards, it removes the scroll bars from the graphics view and sets the Battle Map scene to the graphics      *
     *          view.                                                                                                                               *
     *                                                                                                                                              *
     * \param   graphicsView                  Address of the graphics view to display the Battle Map scene on                                       *
     *                                                                                                                                              *
     * \return  This function does not have any return value.                                                                                       *
     ************************************************************************************************************************************************/
    void setGraphicsView(QGraphicsView *graphicsView);

    /*! *********************************************************************************************************************************************
     * \brief   This function sets the address of the member variable m_battleMap.                                                                  *
     *                                                                                                                                              *
     * \details This function sets the address of the member variable m_battleMap and updates the Battle Map square graphics items according to the *
     *          set Battle Map.                                                                                                                     *
     *                                                                                                                                              *
     * \param   battleMap                     Address of the Battle Map                                                                             *
     *                                                                                                                                              *
     * \return  This function does not have any return value.                                                                                       *
     ************************************************************************************************************************************************/
    void setBattleMap(BattleMap *battleMap);

    /*! *********************************************************************************************************************************************
     * \brief   This function sets the address of the member variable m_battleMapSceneSection.                                                      *
     *                                                                                                                                              *
     * \details -                                                                                                                                   *
     *                                                                                                                                              *
     * \param   battleMapSceneSection         Address of the Battle Map scene section                                                               *
     *                                                                                                                                              *
     * \return  This function does not have any return value.                                                                                       *
     ************************************************************************************************************************************************/
    void setBattleMapSceneSection(BattleMapSceneSection *battleMapSceneSection);

    /*! *********************************************************************************************************************************************
     * \brief   This function sets the member variable m_operationMode.                                                                             *
     *                                                                                                                                              *
     * \details This function sets the member variable m_operationMode and sets the cursor according to the operation mode.                         *
     *                                                                                                                                              *
     * \param   operationMode                 Operation mode                                                                                        *
     *                                                                                                                                              *
     * \return  This function does not have any return value.                                                                                       *
     ************************************************************************************************************************************************/
    void setOperationMode(operationMode_t operationMode);

    /*! *********************************************************************************************************************************************
     * \brief   This function initializes the Battle Map image without showing it.                                                                  *
     *                                                                                                                                              *
     * \details This function resets the Battle Map scene and adds all the Battle Map squares from the Battle Map to the Battle Map scene.          *
     *          Afterwards, it initializes the Battle Map scene rect according to the Battle Map scene section and adds and positions the wind rose *
     *          graphics item.                                                                                                                      *
     * \return  This function does not have any return value.                                                                                       *
     ************************************************************************************************************************************************/
    void initBattleMapImage();

    /*! *********************************************************************************************************************************************
     * \brief   This function updates the Battle Map image.                                                                                         *
     *                                                                                                                                              *
     * \details This function updates the visibility and opacity of the Battle Map squares. Afterwards, it updates the Battle Map scene rect        *
     *          according to the Battle Map scene section and the position of the wind rose graphics item.                                          *
     *                                                                                                                                              *
     * \return  This function does not have any return value.                                                                                       *
     ************************************************************************************************************************************************/
    void updateBattleMapImage();

    /*! *********************************************************************************************************************************************
     * \brief   This function sets the visibility state of the wind rose graphics item.                                                             *
     *                                                                                                                                              *
     * \details -                                                                                                                                   *
     *                                                                                                                                              *
     * \param   visibile                      Visibility state                                                                                      *
     *                                                                                                                                              *
     * \return  This function does not have any return value.                                                                                       *
     ************************************************************************************************************************************************/
    void setWindRoseGraphicsItemVisibility(bool visibile);

    /*! *********************************************************************************************************************************************
     * \brief   This function sets the pixmap of the wind rose graphics item.                                                                       *
     *                                                                                                                                              *
     * \details -                                                                                                                                   *
     *                                                                                                                                              *
     * \param   pixmap                         Pixmap                                                                                               *
     *                                                                                                                                              *
     * \return  This function does not have any return value.                                                                                       *
     ************************************************************************************************************************************************/
    void setWindRoseGraphicsItemPixmap(QPixmap pixmap);

protected: /* - */

signals: /* - */

private slots: /* - */

private:

    /*! *********************************************************************************************************************************************
     * \brief   This function deletes the graphics items of the Battle Map squares.                                                                 *
     *                                                                                                                                              *
     * \details This function deletes the graphics items of the Battle Map squares and removes all the graphics items from the list.                *
     *                                                                                                                                              *
     * \return  This function does not have any return value.                                                                                       *
     ************************************************************************************************************************************************/
    void deleteBattleMapSquaresGraphicsItems();

    /*! *********************************************************************************************************************************************
     * \brief   This function updates the graphics items of the Battle Map squares.                                                                 *
     *                                                                                                                                              *
     * \details This function deletes the Battle Map squares of the previous Battle Map. Afterwards, it appends all the rows of the new Battle Map  *
     *          to the nested QList member variable m_battleMapSquaresGraphicsItems if the respective rows do not already exist. To each row it     *
     *          appends the graphics items of the Battle Map squares.                                                                               *
     *                                                                                                                                              *
     * \return  This function does not have any return value.                                                                                       *
     ************************************************************************************************************************************************/
    void updateBattleMapSquaresGraphicsItems();

    /*! *********************************************************************************************************************************************
     * \brief   This function deletes the Battle Map scene.                                                                                         *
     *                                                                                                                                              *
     * \details This function removes all graphics items from the Battle Map scene and deletes m_battleMapScene afterwards.                         *
     *                                                                                                                                              *
     * \return  This function does not have any return value.                                                                                       *
     ************************************************************************************************************************************************/
    void deleteBattleMapScene();

    /*! *********************************************************************************************************************************************
     * \brief   This function updates the visibility of the Battle Map squares depending on whether they are displayed on the player screen.        *
     *                                                                                                                                              *
     * \details -                                                                                                                                   *
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
     *          so, the opacity is set to the minimum value. Otherwise, the opacity is set immediately to the maximum value. Finally, it starts the *
     *          opacity animation which is deleted when it has been stopped.                                                                        *
     *                                                                                                                                              *
     * \return  This function does not have any return value.                                                                                       *
     ************************************************************************************************************************************************/
    void updateBattleMapSquaresOpacity();

    /*!
     * \brief This is a pointer to the graphics view.
     */
    QGraphicsView *m_graphicsView;

    /*!
     * \brief This is a pointer to the Battle Map.
     */
    BattleMap *m_battleMap;

    /*!
     * \brief This is a pointer to the Battle Map scene section.
     */
    BattleMapSceneSection *m_battleMapSceneSection;

    /*!
     * \brief This is a pointer to the Battle Map scene.
     */
    BattleMapScenePlayerScreen *m_battleMapScene;

    /*!
     * \brief This is the operation mode.
     */
    operationMode_t m_operationMode;

    /*!
     * \brief This is the variable containing the graphics items of the Battle Map squares.
     */
    QList<QList<CustomGraphicsPixmapItem*>> m_battleMapSquaresGraphicsItems;

    /*!
     * \brief This is the variable contaiting the graphics item of the wind rose.
     */
    QGraphicsPixmapItem m_windRoseGraphicsItem;

    /*!
     * \brief This is the edge length of a Battle Map square in pixels.
     */
    quint32 m_edgeLengthInPixels;
};

#endif // PLAYERSCREENHANDLER_H
