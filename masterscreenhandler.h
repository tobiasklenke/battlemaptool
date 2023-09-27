#ifndef MASTERSCREENHANDLER_H
#define MASTERSCREENHANDLER_H

/****************************************************************************************************************************************************
 * INCLUDES                                                                                                                                         *
 ****************************************************************************************************************************************************/

#include "battlemap.h"
#include "battlemapscenemasterscreen.h"
#include "graphicsview_battlemap.h"

/****************************************************************************************************************************************************
 * CLASS DECLARATION                                                                                                                                *
 ****************************************************************************************************************************************************/

/*!
 * \brief This class implements the functionality of the master screen handling.
 */
class MasterScreenHandler
{

public:

    /*! *********************************************************************************************************************************************
     * \brief   This function is the constructor of the class MasterScreenHandler.                                                                  *
     *                                                                                                                                              *
     * \details -                                                                                                                                   *
     *                                                                                                                                              *
     * \return  This function does not have any return value.                                                                                       *
     ************************************************************************************************************************************************/
    MasterScreenHandler();

    /*! *********************************************************************************************************************************************
     * \brief   This function is the destructor of the class MasterScreenHandler.                                                                   *
     *                                                                                                                                              *
     * \details This function deletes the objects pointed to by pBattleMapScene and contained in the nested QList member variable                   *
	 *          m_battleMapSquaresGraphicsItems.                                                                                                    *
     *                                                                                                                                              *
     * \return  This function does not have any return value.                                                                                       *
     ************************************************************************************************************************************************/
    ~MasterScreenHandler();

    /*! *********************************************************************************************************************************************
     * \brief   This function sets the address of the member variable pGraphicsView.                                                                *
     *                                                                                                                                              *
     * \details -                                                                                                                                   *
     *                                                                                                                                              *
     * \param   graphicsView                  Address of the graphics view to display the Battle Map scene on                                       *
     *                                                                                                                                              *
     * \return  This function does not have any return value.                                                                                       *
     ************************************************************************************************************************************************/
    void setGraphicsView(GraphicsView_BattleMap *graphicsView);

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
     * \brief   This function shows the Battle Map image.                                                                                           *
     *                                                                                                                                              *
     * \details This function resets the Battle Map scene and adds all the Battle Map squares from the Battle Map to the Battle Map scene.          *
     *                                                                                                                                              *
     * \return  This function does not have any return value.                                                                                       *
     ************************************************************************************************************************************************/
    void showBattleMapImage();

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

    /*!
     * \brief This is a pointer to the graphics view.
     */
    GraphicsView_BattleMap *pGraphicsView;

    /*!
     * \brief This is a pointer to the Battle Map.
     */
    BattleMap *pBattleMap;

    /*!
     * \brief This is a pointer to the Battle Map scene.
     */
    BattleMapSceneMasterScreen *pBattleMapScene;

    /*!
     * \brief This is the text to be shown in the Battle Map scene.
     */
    QGraphicsTextItem m_sceneText;

    /*!
     * \brief This is the rect to be shown in the Battle Map scene.
     */
    QGraphicsRectItem m_sceneRect;

    /*!
     * \brief This is the variable containing the graphics items of the Battle Map squares.
     */
    QList<QList<QGraphicsPixmapItem*>> m_battleMapSquaresGraphicsItems;

};

#endif // MASTERSCREENHANDLER_H
