#ifndef GRAPHICSVIEW_BATTLEMAP_H
#define GRAPHICSVIEW_BATTLEMAP_H

/****************************************************************************************************************************************************
 * INCLUDES                                                                                                                                         *
 ****************************************************************************************************************************************************/

#include <QGraphicsScene>
#include <QGraphicsView>
#include <QWheelEvent>

#include "defines.h"

/****************************************************************************************************************************************************
 * CLASS DECLARATION                                                                                                                                *
 ****************************************************************************************************************************************************/

/*!
 * \brief This class implements the custom functionality of a Battle Map view.
 */
class GraphicsView_BattleMap : public QGraphicsView
{
    Q_OBJECT

public:

    /*! *********************************************************************************************************************************************
     * \brief   This function is the constructor of the class GraphicsView_BattleMap.                                                               *
     *                                                                                                                                              *
     * \details -                                                                                                                                   *
     *                                                                                                                                              *
     * \return  This function does not have any return value.                                                                                       *
     ************************************************************************************************************************************************/
    GraphicsView_BattleMap(QWidget *parent = nullptr);

    /*! *********************************************************************************************************************************************
     * \brief   This function is the destructor of the class GraphicsView_BattleMap.                                                                *
     *                                                                                                                                              *
     * \details -                                                                                                                                   *
     *                                                                                                                                              *
     * \return  This function does not have any return value.                                                                                       *
     ************************************************************************************************************************************************/
    ~GraphicsView_BattleMap();

    /*! *********************************************************************************************************************************************
     * \brief   This function resets the scaling.                                                                                                   *
     *                                                                                                                                              *
     * \details This function scales the view to the original size, resets the scale factor and emits the signal that the scale factor has been     *
     *          changed.                                                                                                                            *
     *                                                                                                                                              *
     * \return  This function does not have any return value.                                                                                       *
     ************************************************************************************************************************************************/
    void resetScaling();

protected:

    /*! *********************************************************************************************************************************************
     * \brief   This function handles a mouse wheel event on the Battle Map view.                                                                   *
     *                                                                                                                                              *
     * \details This function handles a mouse wheel event on the Battle Map view by incrementing or decrementing the scale factor by 10 percent,    *
     *          depending on the scrolling direction. The scale factor can take values in the range of 10 percent to 200 percent. Afterwards, the   *
     *          function emits the signal that the scale factor has been changed.                                                                   *
     *                                                                                                                                              *
     * \param   event                         Mouse wheel event to be handled                                                                       *
     *                                                                                                                                              *
     * \return  This function does not have any return value.                                                                                       *
     ************************************************************************************************************************************************/
    void wheelEvent(QWheelEvent *event);

signals:

    /*! *********************************************************************************************************************************************
     * \brief This signal is emitted as soon as the scale factor of the Battle Map view changes.                                                    *
     ************************************************************************************************************************************************/
    void changed_ScaleFactor(qreal m_scaleFactor);

private slots: /* - */

private:

    /*!
     * \brief This is the factor that is used for scaling the Battle Map view while scrolling.
     */
    qreal m_scaleFactor;

};

#endif // GRAPHICSVIEW_BATTLEMAP_H
