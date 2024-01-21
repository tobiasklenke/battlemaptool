#ifndef CUSTOMGRAPHICSPIXMAPITEM_H
#define CUSTOMGRAPHICSPIXMAPITEM_H

/****************************************************************************************************************************************************
 * INCLUDES                                                                                                                                         *
 ****************************************************************************************************************************************************/

#include <QObject>
#include <QGraphicsPixmapItem>

/****************************************************************************************************************************************************
 * CLASS DECLARATION                                                                                                                                *
 ****************************************************************************************************************************************************/

/*!
 * \brief This class implements the functionality of a custom graphics pixmap item.
 */
class CustomGraphicsPixmapItem : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
    Q_PROPERTY(qreal opacity READ opacity WRITE setOpacity)

public:

    /*! *********************************************************************************************************************************************
     * \brief   This function is the constructor of the class CustomGraphicsPixmapItem.                                                             *
     *                                                                                                                                              *
     * \details -                                                                                                                                   *
     *                                                                                                                                              *
     * \return  This function does not have any return value.                                                                                       *
     ************************************************************************************************************************************************/
    CustomGraphicsPixmapItem();

    /*! *********************************************************************************************************************************************
     * \brief   This function is the constructor of the class CustomGraphicsPixmapItem, using pixmap as the default pixmap.                         *
     *                                                                                                                                              *
     * \details -                                                                                                                                   *
     *                                                                                                                                              *
     * \param   pixmap                        Pixmap of the graphics pixmap item                                                                    *
     *                                                                                                                                              *
     * \return  This function does not have any return value.                                                                                       *
     ************************************************************************************************************************************************/
    CustomGraphicsPixmapItem(QPixmap pixmap);

    /*! *********************************************************************************************************************************************
     * \brief   This function is the destructor of the class CustomGraphicsPixmapItem.                                                              *
     *                                                                                                                                              *
     * \details -                                                                                                                                   *
     *                                                                                                                                              *
     * \return  This function does not have any return value.                                                                                       *
     ************************************************************************************************************************************************/
    ~CustomGraphicsPixmapItem();

protected: /* - */

signals: /* - */

private slots: /* - */

private: /* - */

};

#endif // CUSTOMGRAPHICSPIXMAPITEM_H
