#ifndef PLAYERSCREENHANDLER_H
#define PLAYERSCREENHANDLER_H

/****************************************************************************************************************************************************
 * INCLUDES                                                                                                                                         *
 ****************************************************************************************************************************************************/

#include <QGraphicsView>
#include <QParallelAnimationGroup>
#include <QPropertyAnimation>
#include <QSettings>

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
     * \details This function resets the Battle Map scene and adds all the Battle Map squares from the Battle Map to the Battle Map scene after it  *
     *          positions the Battle Map squares on theBattle Map scene, makes the Battle Map squares invisible and puts the Battle Map squares     *
     *          graphics items to the background so that the wind rose graphics item is completely visible. Afterwards, it initializes the Battle   *
     *          Map scene rect according to the Battle Map scene section. Finally, it initializes the member variables m_deleteRowsOnUpdate and     *
     *          m_deleteColumnsOnUpdate, adds and positions the wind rose graphics item and puts it to the foreground.                              *
     *                                                                                                                                              *
     * \return  This function does not have any return value.                                                                                       *
     ************************************************************************************************************************************************/
    void initBattleMapImage();

    /*! *********************************************************************************************************************************************
     * \brief   This function updates the Battle Map image.                                                                                         *
     *                                                                                                                                              *
     * \details This function updates the Battle Map image by deleting and repositioning the Battle Map squares on the Battle Map scene if          *
     *          required. Afterwards, it updates the pixmaps, the visibility and the opacity of the Battle Map squares. Finally, it updates the     *
     *          Battle Map scene rect according to the Battle Map scene section and it updates the position of the wind rose graphics item.         *
     *                                                                                                                                              *
     * \return  This function does not have any return value.                                                                                       *
     ************************************************************************************************************************************************/
    void updateBattleMapImage();

    /*! *********************************************************************************************************************************************
     * \brief   This function inserts a new row above the Battle Map.                                                                               *
     *                                                                                                                                              *
     * \details This function inserts a new row above the Battle Map. It puts the Battle Map square graphics items to the background so that the    *
     *          wind rose graphics item is completely visible and adds the Battle Map squares to the Battle Map scene. Afterwards, it adds the      *
     *          newly inserted row that shall not be deleted on update to the member variable m_deleteRowsOnUpdate. Finally, it sets the member     *
     *          variable m_repositioningRequired to true so that the reposition of the Battle Map squares on Battle Map scene takes place on the    *
     *          next update of the Battle Map image.                                                                                                *
     *                                                                                                                                              *
     * \return  This function does not have any return value.                                                                                       *
     ************************************************************************************************************************************************/
    void insertRowAbove();

    /*! *********************************************************************************************************************************************
     * \brief   This function inserts a new row below the Battle Map.                                                                               *
     *                                                                                                                                              *
     * \details This function inserts a new row below the Battle Map. It puts the Battle Map square graphics items to the background so that the    *
     *          wind rose graphics item is completely visible and adds the Battle Map squares to the Battle Map scene. Afterwards, it adds the      *
     *          newly inserted row that shall not be deleted on update to the member variable m_deleteRowsOnUpdate. Finally, it sets the member     *
     *          variable m_repositioningRequired to true so that the reposition of the Battle Map squares on Battle Map scene takes place on the    *
     *          next update of the Battle Map image.                                                                                                *
     *                                                                                                                                              *
     * \return  This function does not have any return value.                                                                                       *
     ************************************************************************************************************************************************/
    void insertRowBelow();

    /*! *********************************************************************************************************************************************
     * \brief   This function inserts a new column to the left of the Battle Map.                                                                   *
     *                                                                                                                                              *
     * \details This function inserts a new column to the left of the Battle Map. It puts the Battle Map square graphics items to the background so *
     *          that the wind rose graphics item is completely visible and adds the Battle Map squares to the Battle Map scene. Afterwards, it adds *
     *          the newly inserted column that shall not be deleted on update to the member variable m_deleteColumnsOnUpdate. Finally, it sets the  *
     *          member variable m_repositioningRequired to true so that the reposition of the Battle Map squares on Battle Map scene takes place on *
     *          the next update of the Battle Map image.                                                                                            *
     *                                                                                                                                              *
     * \return  This function does not have any return value.                                                                                       *
     ************************************************************************************************************************************************/
    void insertColumnLeft();

    /*! *********************************************************************************************************************************************
     * \brief   This function inserts a new column to the right of the Battle Map.                                                                  *
     *                                                                                                                                              *
     * \details This function inserts a new column to the right of the Battle Map. It puts the Battle Map square graphics items to the background   *
     *          so that the wind rose graphics item is completely visible and adds the Battle Map squares to the Battle Map scene. Afterwards, it   *
     *          adds the newly inserted column that shall not be deleted on update to the member variable m_deleteColumnsOnUpdate. Finally, it sets *
     *          the member variable m_repositioningRequired to true so that the reposition of the Battle Map squares on Battle Map scene takes      *
     *          place on the next update of the Battle Map image.                                                                                   *
     *                                                                                                                                              *
     * \return  This function does not have any return value.                                                                                       *
     ************************************************************************************************************************************************/
    void insertColumnRight();

    /*! *********************************************************************************************************************************************
     * \brief   This function prepares the deletion of a row above the Battle Map.                                                                  *
     *                                                                                                                                              *
     * \details This function prepares the deletion of a row above the Battle Map by setting the row from m_deleteRowsOnUpdate that shall be        *
     *          deleted on update. Finally, it sets the member variables m_deletionRequired and m_repositioningRequired to true so that the         *
     *          deletion and the repositioning of the Battle Map squares on the Battle Map scene takes place on the next update of the Battle Map   *
     *          image.                                                                                                                              *
     *                                                                                                                                              *
     * \return  This function does not have any return value.                                                                                       *
     ************************************************************************************************************************************************/
    void deleteRowAbove();

    /*! *********************************************************************************************************************************************
     * \brief   This function prepares the deletion of a row below the Battle Map.                                                                  *
     *                                                                                                                                              *
     * \details This function prepares the deletion of a row below the Battle Map by setting the row from m_deleteRowsOnUpdate that shall be        *
     *          deleted on update. Finally, it sets the member variables m_deletionRequired and m_repositioningRequired to true so that the         *
     *          deletion and the repositioning of the Battle Map squares on the Battle Map scene takes place on the next update of the Battle Map   *
     *          image.                                                                                                                              *
     *                                                                                                                                              *
     * \return  This function does not have any return value.                                                                                       *
     ************************************************************************************************************************************************/
    void deleteRowBelow();

    /*! *********************************************************************************************************************************************
     * \brief   This function prepares the deletion of a column to the left of the Battle Map.                                                      *
     *                                                                                                                                              *
     * \details This function prepares the deletion of a column to the left of the Battle Map by setting the column from m_deleteColumnsOnUpdate    *
     *          that shall be deleted on update. Finally, it sets the member variables m_deletionRequired and m_repositioningRequired to true so    *
     *          that the deletion and the repositioning of the Battle Map squares on the Battle Map scene takes place on the next update of the     *
     *          Battle Map image.                                                                                                                   *
     *                                                                                                                                              *
     * \return  This function does not have any return value.                                                                                       *
     ************************************************************************************************************************************************/
    void deleteColumnLeft();

    /*! *********************************************************************************************************************************************
     * \brief   This function prepares the deletion of a column to the right of the Battle Map.                                                     *
     *                                                                                                                                              *
     * \details This function prepares the deletion of a column to the right of the Battle Map by setting the column from m_deleteColumnsOnUpdate   *
     *          that shall be deleted on update. Finally, it sets the member variables m_deletionRequired and m_repositioningRequired to true so    *
     *          that the deletion and the repositioning of the Battle Map squares on the Battle Map scene takes place on the next update of the     *
     *          Battle Map image.                                                                                                                   *
     *                                                                                                                                              *
     * \return  This function does not have any return value.                                                                                       *
     ************************************************************************************************************************************************/
    void deleteColumnRight();

    /*! *********************************************************************************************************************************************
     * \brief   This function prepares the left rotation of the Battle Map.                                                                         *
     *                                                                                                                                              *
     * \details This function gets the new lists of rows and columns to be deleted and resorts the Battle Map squares according to the left         *
     *          rotation. Finally, it updates the variables for the lists of rows and columns to be deleted and for the Battle Map squares and it   *
     *          sets the member variable m_repositioningRequired to true so that the repositioning of the Battle Map squares on the Battle Map      *
     *          scene takes place on the next update of the Battle Map image.                                                                       *
     *                                                                                                                                              *
     * \return  This function does not have any return value.                                                                                       *
     ************************************************************************************************************************************************/
    void rotateBattleMapLeft();

    /*! *********************************************************************************************************************************************
     * \brief   This function prepares the right rotation of the Battle Map.                                                                        *
     *                                                                                                                                              *
     * \details This function gets the new lists of rows and columns to be deleted and resorts the Battle Map squares according to the right        *
     *          rotation. Finally, it updates the variables for the lists of rows and columns to be deleted and for the Battle Map squares and it   *
     *          sets the member variable m_repositioningRequired to true so that the repositioning of the Battle Map squares on the Battle Map      *
     *          scene takes place on the next update of the Battle Map image.                                                                       *
     *                                                                                                                                              *
     * \return  This function does not have any return value.                                                                                       *
     ************************************************************************************************************************************************/
    void rotateBattleMapRight();

    /*! *********************************************************************************************************************************************
     * \brief   This function deletes the Battle Map squares to be deleted from the Battle Map scene.                                               *
     *                                                                                                                                              *
     * \details This function determines the numbers of rows and columns in the lists m_deleteRowsOnUpdate and m_deleteColumnsOnUpdate since the    *
     *          numbers can alter in case of deletion. Afterwards, it deletes the Battle Map rows and columns from the Battle Map scene and updates *
     *          the number of rows and columns accordingly.                                                                                         *
     *                                                                                                                                              *
     * \return  This function does not have any return value.                                                                                       *
     ************************************************************************************************************************************************/
    void deleteGraphicsItemsFromBattleMapScene();

    /*! *********************************************************************************************************************************************
     * \brief   This function repositions the Battle Map squares on the Battle Map scene.                                                           *
     *                                                                                                                                              *
     * \details -                                                                                                                                   *
     *                                                                                                                                              *
     * \return  This function does not have any return value.                                                                                       *
     ************************************************************************************************************************************************/
    void repositionGraphicsItemsOnBattleMapScene();

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
    void deleteBattleMapSquareGraphicsItems();

    /*! *********************************************************************************************************************************************
     * \brief   This function updates the graphics items of the Battle Map squares.                                                                 *
     *                                                                                                                                              *
     * \details This function deletes the Battle Map squares of the previous Battle Map. Afterwards, it appends all the rows of the new Battle Map  *
     *          to the nested QList member variable m_battleMapSquaresGraphicsItems if the respective rows do not already exist. To each row it     *
     *          appends the graphics items of the Battle Map squares.                                                                               *
     *                                                                                                                                              *
     * \return  This function does not have any return value.                                                                                       *
     ************************************************************************************************************************************************/
    void updateBattleMapSquareGraphicsItems();

    /*! *********************************************************************************************************************************************
     * \brief   This function deletes the Battle Map scene.                                                                                         *
     *                                                                                                                                              *
     * \details This function removes all graphics items from the Battle Map scene and deletes m_battleMapScene afterwards.                         *
     *                                                                                                                                              *
     * \return  This function does not have any return value.                                                                                       *
     ************************************************************************************************************************************************/
    void deleteBattleMapScene();

    /*! *********************************************************************************************************************************************
     * \brief   This function updates the pixmaps of the Battle Map squares.                                                                        *
     *                                                                                                                                              *
     * \details -                                                                                                                                   *
     *                                                                                                                                              *
     * \return  This function does not have any return value.                                                                                       *
     ************************************************************************************************************************************************/
    void updateBattleMapSquaresPixmaps();

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
    QList<QList<CustomGraphicsPixmapItem*>> m_battleMapSquareGraphicsItems;

    /*!
     * \brief This is the information whether the graphics items of the Battle Map squares in the rows shall be deleted on the next update.
     */
    QList<bool> m_deleteRowsOnUpdate;

    /*!
     * \brief This is the information whether the graphics items of the Battle Map squares in the columns shall be deleted on the next update.
     */
    QList<bool> m_deleteColumnsOnUpdate;

    /*!
     * \brief This is the variable contaiting the graphics item of the wind rose.
     */
    QGraphicsPixmapItem m_windRoseGraphicsItem;

    /*!
     * \brief This is the edge length of a Battle Map square in pixels.
     */
    quint32 m_edgeLengthInPixels;

    /*!
     * \brief This is the information whether the deletion of some Battle Map squares is required due to newly deleted Battle Map squares.
     */
    bool m_deletionRequired;

    /*!
     * \brief This is the information whether the repositioning of the Battle Map squares is required due to newly inserted or deleted Battle Map squares.
     */
    bool m_repositioningRequired;
};

#endif // PLAYERSCREENHANDLER_H
