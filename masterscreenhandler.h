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
#include "customgraphicsview.h"
#include "screencalc.h"

/****************************************************************************************************************************************************
 * CLASS DECLARATION                                                                                                                                *
 ****************************************************************************************************************************************************/

/*!
 * \brief This class implements the functionality needed for the handling of the master screen.
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
     * \details This function deletes the objects created in the constructor.                                                                       *
     *                                                                                                                                              *
     * \return  This function does not have any return value.                                                                                       *
     ************************************************************************************************************************************************/
    ~MasterScreenHandler();

    /*! *********************************************************************************************************************************************
     * \brief   This function sets the address of the member variable m_graphicsView.                                                               *
     *                                                                                                                                              *
     * \details This function sets the address of the member variable m_graphicsView, connects the signals and slots of the graphics view and sets  *
     *          the background color of the graphics view to the window color. Afterwards, it sets the Battle Map scene to the graphics view and    *
     *          adds a text asking the user to create a new Battle Map or open an existing Battle Map.                                              *
     *                                                                                                                                              *
     * \param   graphicsView                  Address of the graphics view to display the Battle Map scene on                                       *
     *                                                                                                                                              *
     * \return  This function does not have any return value.                                                                                       *
     ************************************************************************************************************************************************/
    void setGraphicsView(CustomGraphicsView *graphicsView);

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
     * \details This function sets the member variable m_operationMode, resets the selection area and sets the cursor according to the operation    *
     *          mode.                                                                                                                               *
     *                                                                                                                                              *
     * \param   operationMode                 Operation mode                                                                                        *
     *                                                                                                                                              *
     * \return  This function does not have any return value.                                                                                       *
     ************************************************************************************************************************************************/
    void setOperationMode(operationMode_t operationMode);

    /*! *********************************************************************************************************************************************
     * \brief   This function returns the pixmaps of the Battle Map squares from the selection area.                                                *
     *                                                                                                                                              *
     * \details -                                                                                                                                   *
     *                                                                                                                                              *
     * \return  This function returns the pixmaps of the Battle Map squares from the selection area.                                                *
     ************************************************************************************************************************************************/
    QList<QList<QPixmap>> getPixmapsFromSelectionArea();

    /*! *********************************************************************************************************************************************
     * \brief   This function returns the indexes of the first selected Battle Map square via its parameters.                                       *
     *                                                                                                                                              *
     * \details This function checks the Battle Map squares for the first selected one and sets the indexes of the first selected Battle Map square *
     *          to the values of parameters firstSelectedRowIdx and firstSelectedColumnIdx.                                                         *
     *                                                                                                                                              *
     * \param   firstSelectedRowIdx              Address of the row index of the first selected Battle Map square                                   *
     * \param   firstSelectedColumnIdx           Address of the column index of the first selected Battle Map square                                *
     *                                                                                                                                              *
     * \return  This function does not have any return value.                                                                                       *
     ************************************************************************************************************************************************/
    void getIndexesOfFirstBattleMapSquareFromSelectionArea(quint32 *firstSelectedRowIdx, quint32 *firstSelectedColumnIdx);

    /*! *********************************************************************************************************************************************
     * \brief   This function shows the Battle Map image.                                                                                           *
     *                                                                                                                                              *
     * \details This function resets and reconnects the Battle Map scene, resets the scaling of the graphics view and adds the Battle Map squares   *
     *          and the coverage rectangles to the Battle Map scene. Afterwards, it updates the Battle Map scene section and adds a frame. Finally, *
     *          as soon as the Battle Map image is shown, it stacks the Battle Map scene section rectangle on top of all other items so that the    *
     *          selection rectangle is completely visible and it enables the event processing of the graphics view.                                 *
     *                                                                                                                                              *
     * \return  This function does not have any return value.                                                                                       *
     ************************************************************************************************************************************************/
    void showBattleMapImage();

    /*! *********************************************************************************************************************************************
     * \brief   This function updates the pixmaps of the Battle Map squares according to the Battle Map.                                            *
     *                                                                                                                                              *
     * \details -                                                                                                                                   *
     *                                                                                                                                              *
     * \return  This function does not have any return value.                                                                                       *
     ************************************************************************************************************************************************/
    void updatePixmapsAccordingBattleMap();

    /*! *********************************************************************************************************************************************
     * \brief   This function inserts a new row above the Battle Map.                                                                               *
     *                                                                                                                                              *
     * \details This function inserts a new row above the Battle Map. It appends the graphics item of the Battle Map squares to the row, makes the  *
     *          Battle Map squares in the inserted row selectable, sets the graphics item of the Battle Map squares to the background layer and     *
     *          adds the Battle Map squares to the Battle Map scene. Moreover, it appends the graphics items of the coverage rectangles to the row, *
     *          sets the graphics items of the coverage rectangles to the coverage layer, adds the coverage rectangles to the Battle Map scene and  *
     *          sets the visibility state of the coverage rectangles according to the coverage state of the Battle Map squares. Finally, it         *
     *          repositions the Battle Map squares on the Battle Map scene, updates the Battle Map scene section and the frame and resets the       *
     *          selection area when the editing of the Battle Map is finished.                                                                      *
     *                                                                                                                                              *
     * \return  This function does not have any return value.                                                                                       *
     ************************************************************************************************************************************************/
    void insertRowAbove();

    /*! *********************************************************************************************************************************************
     * \brief   This function inserts a new row below the Battle Map.                                                                               *
     *                                                                                                                                              *
     * \details This function inserts a new row below the Battle Map. It appends the graphics item of the Battle Map squares to the row, makes the  *
     *          Battle Map squares in the inserted row selectable, sets the graphics item of the Battle Map squares to the background layer and     *
     *          adds the Battle Map squares to the Battle Map scene. Moreover, it appends the graphics items of the coverage rectangles to the row, *
     *          sets the graphics items of the coverage rectangles to the coverage layer, adds the coverage rectangles to the Battle Map scene and  *
     *          sets the visibility state of the coverage rectangles according to the coverage state of the Battle Map squares. Finally, it         *
     *          repositions the Battle Map squares on the Battle Map scene, updates the Battle Map scene section and the frame and resets the       *
     *          selection area when the editing of the Battle Map is finished.                                                                      *
     *                                                                                                                                              *
     * \return  This function does not have any return value.                                                                                       *
     ************************************************************************************************************************************************/
    void insertRowBelow();

    /*! *********************************************************************************************************************************************
     * \brief   This function inserts a new column to the left of the Battle Map.                                                                   *
     *                                                                                                                                              *
     * \details This function inserts a new column to the left of the Battle Map. It prepends the graphics item of the Battle Map squares to the    *
     *          rows, makes the Battle Map squares in the inserted column selectable, sets the graphics item of the Battle Map squares to the       *
     *          background layer and adds the Battle Map squares to the Battle Map scene. Moreover, it prepends the graphics items of the coverage  *
     *          rectangles to the rows, sets the graphics items of the coverage rectangles to the coverage layer, adds the coverage rectangles to   *
     *          the Battle Map scene and sets the visibility state of the coverage rectangles according to the coverage state of the Battle Map     *
     *          squares. Finally, it repositions the Battle Map squares on the Battle Map scene, updates the Battle Map scene section and the frame *
     *          and resets the selection area when the editing of the Battle Map is finished.                                                       *
     *                                                                                                                                              *
     * \return  This function does not have any return value.                                                                                       *
     ************************************************************************************************************************************************/
    void insertColumnLeft();

    /*! *********************************************************************************************************************************************
     * \brief   This function inserts a new column to the right of the Battle Map.                                                                  *
     *                                                                                                                                              *
     * \details This function inserts a new column to the right of the Battle Map. It appends the graphics item of the Battle Map squares to the    *
     *          rows, makes the Battle Map squares in the inserted column selectable, sets the graphics item of the Battle Map squares to the       *
     *          background layer and adds the Battle Map squares to the Battle Map scene. Moreover, it appends the graphics items of the coverage   *
     *          rectangles to the rows, sets the graphics items of the coverage rectangles to the coverage layer, adds the coverage rectangles to   *
     *          the Battle Map scene and sets the visibility state of the coverage rectangles according to the coverage state of the Battle Map     *
     *          squares. Finally, it repositions the Battle Map squares on the Battle Map scene, updates the Battle Map scene section and the frame *
     *          and resets the selection area when the editing of the Battle Map is finished.                                                       *
     *                                                                                                                                              *
     * \return  This function does not have any return value.                                                                                       *
     ************************************************************************************************************************************************/
    void insertColumnRight();

    /*! *********************************************************************************************************************************************
     * \brief   This function deletes a row above the Battle Map.                                                                                   *
     *                                                                                                                                              *
     * \details This function deletes a row above the Battle Map. Afterwards, it repositions the Battle Map squares and the coverage rectangles on  *
     *          the Battle Map scene, updates the Battle Map scene section and the frame and resets the selection area when the editing of the      *
     *          Battle Map is finished.                                                                                                             *
     *                                                                                                                                              *
     * \return  This function does not have any return value.                                                                                       *
     ************************************************************************************************************************************************/
    void deleteRowAbove();

    /*! *********************************************************************************************************************************************
     * \brief   This function deletes a row below the Battle Map.                                                                                   *
     *                                                                                                                                              *
     * \details This function deletes a row below the Battle Map. Afterwards, it repositions the Battle Map squares and the coverage rectangles on  *
     *          the Battle Map scene, updates the Battle Map scene section and the frame and resets the selection area when the editing of the      *
     *          Battle Map is finished.                                                                                                             *
     *                                                                                                                                              *
     * \return  This function does not have any return value.                                                                                       *
     ************************************************************************************************************************************************/
    void deleteRowBelow();

    /*! *********************************************************************************************************************************************
     * \brief   This function deletes a column to the left of the Battle Map.                                                                       *
     *                                                                                                                                              *
     * \details This function deletes a column to the left of the Battle Map. Afterwards, it repositions the Battle Map squares and the coverage    *
     *          rectangles on the Battle Map scene, updates the Battle Map scene section and the frame and resets the selection area when the       *
     *          editing of the Battle Map is finished.                                                                                              *
     *                                                                                                                                              *
     * \return  This function does not have any return value.                                                                                       *
     ************************************************************************************************************************************************/
    void deleteColumnLeft();

    /*! *********************************************************************************************************************************************
     * \brief   This function deletes a column to the right of the Battle Map.                                                                      *
     *                                                                                                                                              *
     * \details This function deletes a column to the right of the Battle Map. Afterwards, it repositions the Battle Map squares and the coverage   *
     *          rectangles on the Battle Map scene, updates the Battle Map scene section and the frame and resets the selection area when the       *
     *          editing of the Battle Map is finished.                                                                                              *
     *                                                                                                                                              *
     * \return  This function does not have any return value.                                                                                       *
     ************************************************************************************************************************************************/
    void deleteColumnRight();

    /*! *********************************************************************************************************************************************
     * \brief   This function updates the coverage state of Battle Map squares.                                                                     *
     *                                                                                                                                              *
     * \details This function gets the row and column indexes of the selected Battle Map squares and updates the coverage states of these Battle    *
     *          Map squares and the visibility states of the corresponding coverage rectangles according to the parameter covered. Finally, the     *
     *          selection area is reset.                                                                                                            *
     *                                                                                                                                              *
     * \param   covered                       Information whether Battle Map squares shall be covered or uncovered                                  *
     *                                                                                                                                              *
     * \return  This function does not have any return value.                                                                                       *
     ************************************************************************************************************************************************/
    void handleCoverBattleMap(bool covered);

protected: /* - */

signals:

    /*! *********************************************************************************************************************************************
     * \brief This signal is emitted as soon as the selection has been changed.                                                                     *
     ************************************************************************************************************************************************/
    void changedSelection(bool selectionCopyable);

private slots:

    /*! *********************************************************************************************************************************************
     * \brief   This function updates the member variable m_scaleFactor.                                                                            *
     *                                                                                                                                              *
     * \details This function updates the scale factors of the master screen handler and the Battle Map scene and redraws the Battle Map scene      *
     *          section rect.                                                                                                                       *
     *                                                                                                                                              *
     * \param   scaleFactor                   Scale factor                                                                                          *
     *                                                                                                                                              *
     * \return  This function does not have any return value.                                                                                       *
     ************************************************************************************************************************************************/
    void changedScaleFactor(qreal scaleFactor);

    /*! *********************************************************************************************************************************************
     * \brief   This function handles a key press.                                                                                                  *
     *                                                                                                                                              *
     * \details This function determines the viewport center position in scene coordinates. Afterwards, if any of the keys Key_Left, Key_Up,        *
     *          Key_Right and Key_Down has been pressed, it decrements or increments the first rows or columns of the Battle Map scene section      *
     *          accordingly and centers the graphics view on the new position of the scene center if the border of the Battle Map scene section is  *
     *          moved outside the viewport. Finally, it updates the Battle Map scene section.                                                       *
     *                                                                                                                                              *
     * \param   key                           Pressed key                                                                                           *
     *                                                                                                                                              *
     * \return  This function does not have any return value.                                                                                       *
     ************************************************************************************************************************************************/
    void pressedKey(Qt::Key key);

    /*! *********************************************************************************************************************************************
     * \brief   This function handles a press of the right mouse button.                                                                            *
     *                                                                                                                                              *
     * \details This function selects selectable graphics items that are not selected and that are positioned at the right mouse button press       *
     *          position.                                                                                                                           *
     *                                                                                                                                              *
     * \param   position                      Position of the mouse press                                                                           *
     *                                                                                                                                              *
     * \return  This function does not have any return value.                                                                                       *
     ************************************************************************************************************************************************/
    void pressedRightMouseButton(QPoint position);

    /*! *********************************************************************************************************************************************
     * \brief   This function handles the selection of some Battle Map squares.                                                                     *
     *                                                                                                                                              *
     * \details This function handles the selection of some Battle Map squares with the respective operation mode.                                  *
     *                                                                                                                                              *
     * \return  This function does not have any return value.                                                                                       *
     ************************************************************************************************************************************************/
    void selectedBattleMapSquares();

    /*! *********************************************************************************************************************************************
     * \brief   This function handles the unselection of all Battle Map squares.                                                                    *
     *                                                                                                                                              *
     * \details This function handles the unselection of all Battle Map squares by resetting the selection area.                                    *
     *                                                                                                                                              *
     * \return  This function does not have any return value.                                                                                       *
     ************************************************************************************************************************************************/
    void unselectedBattleMapSquares();

private:

    /*! *********************************************************************************************************************************************
     * \brief   This function deletes the graphics items of the Battle Map squares and coverage rectangles.                                         *
     *                                                                                                                                              *
     * \details This function deletes the graphics items of the Battle Map squares and coverage rectangles and removes all the graphics items from  *
     *          the list.                                                                                                                           *
     *                                                                                                                                              *
     * \return  This function does not have any return value.                                                                                       *
     ************************************************************************************************************************************************/
    void deleteBattleMapSquaresGraphicsItems();

    /*! *********************************************************************************************************************************************
     * \brief   This function updates the graphics items of the Battle Map squares and coverage rectangles.                                         *
     *                                                                                                                                              *
     * \details This function deletes the Battle Map squares and the coverage rectangles of the previous Battle Map. Afterwards, it appends the     *
     *          rows to the nested QList member variables m_battleMapSquaresGraphicsItems and m_coverageGraphicsItems if the rows do not already    *
     *          exist. To each row of m_battleMapSquaresGraphicsItems it appends the graphics items of the Battle Map squares, which are made       *
     *          selectable, and it sets the graphics items of the Battle Map squares to the background layer. To each row of                        *
     *          m_coverageGraphicsItems it appends the graphics items of the coverage rectangles and it sets the graphics items of the coverage     *
     *          rectangles to the coverage layer.                                                                                                   *
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
     * \details This function removes all graphics items from the Battle Map scene and deletes m_battleMapScene afterwards.                         *
     *                                                                                                                                              *
     * \return  This function does not have any return value.                                                                                       *
     ************************************************************************************************************************************************/
    void deleteBattleMapScene();

    /*! *********************************************************************************************************************************************
     * \brief   This function handles the selection of some Battle Map squares in case of operation mode Select.                                    *
     *                                                                                                                                              *
     * \details This function checks first whether the Ctrl key on the keyboard is pressed and sets the item selection operation accordingly which  *
     *          decides if the new selection will replace or extend the previous selection. If the mouse has not been moved between mouse press and *
     *          mouse release event, only a single Battle Map square is selected. Otherwise, multiple Battle Map squares are selected. Afterwards,  *
     *          the selected items and the Battle Map scene section rectangle are stacked on top of the unselected items. Finally, the function     *
     *          determines the indexes of the rows and columns limiting the selection area and checks if the selection is copyable, which is shared *
     *          with the main window by emitting the signal changedSelection().                                                                     *
     *                                                                                                                                              *
     * \param   positionPress                 Position of the mouse button press                                                                    *
     * \param   positionRelease               Position of the mouse button release                                                                  *
     *                                                                                                                                              *
     * \return  This function does not have any return value.                                                                                       *
     ************************************************************************************************************************************************/
    void handleSelect(QPointF positionPress, QPointF positionRelease);

    /*! *********************************************************************************************************************************************
     * \brief   This function resets the selection area.                                                                                            *
     *                                                                                                                                              *
     * \details This function unselects all selected graphics items and sets the unselected items to the background layer. Afterwards, it emits the *
     *          signal changedSelection() indicating that the selection is not copyable.                                                            *
     *                                                                                                                                              *
     * \return  This function does not have any return value.                                                                                       *
     ************************************************************************************************************************************************/
    void resetSelectionArea();

    /*!
     * \brief This is a pointer to the graphics view.
     */
    CustomGraphicsView *m_graphicsView;

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
    BattleMapSceneMasterScreen *m_battleMapScene;

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
     * \brief This is the variable containing the graphics items of the rectangles covering the Battle Map squares.
     */
    QList<QList<QGraphicsRectItem*>> m_coverageGraphicsItems;

    /*!
     * \brief This is the factor that is used for scaling the graphics view while scrolling.
     */
    qreal m_scaleFactor;
};

#endif // MASTERSCREENHANDLER_H
