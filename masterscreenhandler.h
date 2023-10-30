#ifndef MASTERSCREENHANDLER_H
#define MASTERSCREENHANDLER_H

/****************************************************************************************************************************************************
 * INCLUDES                                                                                                                                         *
 ****************************************************************************************************************************************************/

#include <QGuiApplication>
#include <QImage>
#include <QObject>

#include "battlemap.h"
#include "battlemapscenemasterscreen.h"
#include "battlemapscenesection.h"
#include "graphicsview_battlemap.h"
#include "screencalc.h"

/****************************************************************************************************************************************************
 * CLASS DECLARATION                                                                                                                                *
 ****************************************************************************************************************************************************/

/*!
 * \brief This class implements the functionality of the master screen handling.
 */
class MasterScreenHandler : public QObject
{
    Q_OBJECT

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
     * \details This function sets the address of the member variable pGraphicsView, connects the signals and slots and sets the Battle Map scene.  *
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
     * \brief   This function shows the Battle Map image.                                                                                           *
     *                                                                                                                                              *
     * \details This function resets the Battle Map scene and adds all the Battle Map squares from the Battle Map to the Battle Map scene.          *
     *                                                                                                                                              *
     * \return  This function does not have any return value.                                                                                       *
     ************************************************************************************************************************************************/
    void showBattleMapImage();

protected: /* - */

signals: /* - */

private slots:

    /*! *********************************************************************************************************************************************
     * \brief   This function updates the member variable m_scaleFactor and redraws the Battle Map section rect.                                    *
     *                                                                                                                                              *
     * \details -                                                                                                                                   *
     *                                                                                                                                              *
     * \return  This function does not have any return value.                                                                                       *
     ************************************************************************************************************************************************/
    void changed_ScaleFactor(qreal scaleFactor);

    /*! *********************************************************************************************************************************************
     * \brief   This function updates the member variables of the Battle Map scene section in case of an appropriate key press.                     *
     *                                                                                                                                              *
     * \details This function updates the member variables of the Battle Map scene section in case of an appropriate key press and centers the      *
     *          graphics view on the new position of the scene center if the border of the Battle Map scene section is moved outside the viewport.  *
     *                                                                                                                                              *
     * \return  This function does not have any return value.                                                                                       *
     ************************************************************************************************************************************************/
    void pressed_Key(Qt::Key key);

    /*! *********************************************************************************************************************************************
     * \brief   This function handles the selection of some Battle Map squares.                                                                     *
     *                                                                                                                                              *
     * \details -                                                                                                                                   *
     *                                                                                                                                              *
     * \return  This function does not have any return value.                                                                                       *
     ************************************************************************************************************************************************/
    void selected_BattleMapSquares();

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
     * \brief   This function updates the Battle Map scene section.                                                                                 *
     *                                                                                                                                              *
     * \details This function updates the rect that frames the Battle Map scene section to be displayed on the player screen and the opacity of the *
     *          Battle Map squares depending on whether they are displayed on the player screen.                                                    *
     *                                                                                                                                              *
     * \return  This function does not have any return value.                                                                                       *
     ************************************************************************************************************************************************/
    void updateBattleMapSceneSection();

    /*! *********************************************************************************************************************************************
     * \brief   This function deletes the Battle Map scene.                                                                                         *
     *                                                                                                                                              *
     * \details -                                                                                                                                   *
     *                                                                                                                                              *
     * \return  This function does not have any return value.                                                                                       *
     ************************************************************************************************************************************************/
    void deleteBattleMapScene();

    /*! *********************************************************************************************************************************************
     * \brief   This function handles the selection of some Battle Map squares in case of operation mode Select.                                    *
     *                                                                                                                                              *
     * \details This function checks first if the Ctrl key on the keyboard is pressed and sets the item selection operation accordingly which       *
	 *          decides if the new selection will replace or extend the previous selection. If the mouse has not been moved between mouse press and *
	 *          mouse release event, only a single Battle Map square is selected. Otherwise, multiple Battle Map squares are selected. Finally, the *
	 *          selected items are stacked on top of the unselected items so that the selection rectangle is completely visible.                    *
     *                                                                                                                                              *
     * \return  This function does not have any return value.                                                                                       *
     ************************************************************************************************************************************************/
    void handleSelect();

    /*! *********************************************************************************************************************************************
     * \brief   This function handles the selection of some Battle Map squares in case of operation modes CoverBattleMap or UncoverBattleMap.       *
     *                                                                                                                                              *
     * \details This function gets the selected Battle Map squares and determines the row and column indexes of them. Afterwards, the function      *
	 *          updates the coverage states and pixmaps of Battle Map squares according to the parameter covered. If the Battle Map squares are     *
	 *          covered, its pixmap is converted to grayscale and a transparent black layer is added to it in order to darken it. Otherwise, the    *
	 *          original pixmap is used. Finally, the selection area is reset.                                                                      *
     *                                                                                                                                              *
     * \return  This function does not have any return value.                                                                                       *
     ************************************************************************************************************************************************/
    void handleCoverBattleMap(bool covered);

    /*!
     * \brief This is a pointer to the graphics view.
     */
    GraphicsView_BattleMap *pGraphicsView;

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
    BattleMapSceneMasterScreen *pBattleMapScene;

    /*!
     * \brief This is the operation mode.
     */
    operationMode_t m_operationMode;

    /*!
     * \brief This is the text to be shown in the Battle Map scene.
     */
    QGraphicsTextItem m_sceneText;

    /*!
     * \brief This is the graphics item of the rect to be shown in the Battle Map scene, that frames the Battle Map scene section to be displayed on the player screen.
     */
    QGraphicsRectItem m_sceneSectionRect;

    /*!
     * \brief This is the variable containing the graphics items of the Battle Map squares.
     */
    QList<QList<QGraphicsPixmapItem*>> m_battleMapSquaresGraphicsItems;

    /*!
     * \brief This is the factor that is used for scaling the Battle Map view while scrolling.
     */
    qreal m_scaleFactor;
};

#endif // MASTERSCREENHANDLER_H
