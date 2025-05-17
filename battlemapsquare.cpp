/****************************************************************************************************************************************************
 * INCLUDES                                                                                                                                         *
 ****************************************************************************************************************************************************/

#include "battlemapsquare.h"

/****************************************************************************************************************************************************
 * DEFINITION OF PUBLIC FUNCTIONS                                                                                                                   *
 ****************************************************************************************************************************************************/

/*!
 * \brief This function is the constructor of the class BattleMapSquare.
 */
BattleMapSquare::BattleMapSquare(qreal orientation) :
    m_covered(false),
    m_disguised(false),
    m_disguisable(false)
{
    /* initialize original pixmap of Battle Map square with image of empty Battle Map square rotated according to Battle Map orientation */
    m_battleMapSquareOriginalPixmap = QPixmap::fromImage(QImage((EMPTYBATTLEMAPSQUAREIMAGE_SOURCE))).transformed(QTransform().rotate(orientation));
    m_battleMapSquareOriginalPixmap = m_battleMapSquareOriginalPixmap.scaled(QSize(BATTLEMAPSQUARE_SIZE, BATTLEMAPSQUARE_SIZE));

    /* draw Battle Map grid around Battle Map square */
    QPainter *painter = new QPainter(&m_battleMapSquareOriginalPixmap);
    painter->setPen(QPen(BATTLEMAPGRID_COLOR, BATTLEMAPGRID_LINEWIDTH, Qt::SolidLine));
    painter->drawRect(m_battleMapSquareOriginalPixmap.rect());
    delete painter;
}

/*!
 * \brief This function is the destructor of the class BattleMapSquare.
 */
BattleMapSquare::~BattleMapSquare()
{
}

/*!
 * \brief This function returns the pixmap of the member variable m_battleMapSquareOriginalPixmap.
 */
QPixmap BattleMapSquare::getBattleMapSquareOriginalPixmap() const
{
    return m_battleMapSquareOriginalPixmap;
}

/*!
 * \brief This function sets the pixmap of the member variable m_battleMapSquareOriginalPixmap and ascertains whether the Battle Map square is disguisable.
 */
void BattleMapSquare::setBattleMapSquareOriginalPixmap(QPixmap battleMapSquarePixMap)
{
    m_battleMapSquareOriginalPixmap = battleMapSquarePixMap;

    ascertainDisguisable();
}

/*!
 * \brief This function returns the pixmap of the member variable m_battleMapSquareDisguisePixmap.
 */
QPixmap BattleMapSquare::getBattleMapSquareDisguisePixmap() const
{
    return m_battleMapSquareDisguisePixmap;
}

/*!
 * \brief This function sets the pixmap of the member variable m_battleMapSquareDisguisePixmap and ascertains whether the Battle Map square is disguisable.
 */
void BattleMapSquare::setBattleMapSquareDisguisePixmap(QPixmap battleMapSquarePixMap)
{
    m_battleMapSquareDisguisePixmap = battleMapSquarePixMap;

    ascertainDisguisable();
}

/*!
 * \brief This function returns the value of the member variable m_covered.
 */
bool BattleMapSquare::getCovered() const
{
    return m_covered;
}

/*!
 * \brief This function sets the value of the member variable m_covered.
 */
void BattleMapSquare::setCovered(bool covered)
{
    m_covered = covered;
}

/*!
 * \brief This function returns the value of the member variable m_disguised.
 */
bool BattleMapSquare::getDisguised() const
{
    return m_disguised;
}

/*!
 * \brief This function sets the value of the member variable m_disguised.
 */
void BattleMapSquare::setDisguised(bool disguised)
{
    m_disguised = disguised;
}

/*!
 * \brief This function returns the value of the member variable m_disguisable.
 */
bool BattleMapSquare::getDisguisable() const
{
    return m_disguisable;
}

/****************************************************************************************************************************************************
 * DEFINITION OF PROTECTED FUNCTIONS                                                                                                                *
 ****************************************************************************************************************************************************/

/* - */

/****************************************************************************************************************************************************
 * DEFINITION OF PRIVATE SLOT FUNCTIONS                                                                                                             *
 ****************************************************************************************************************************************************/

/* - */

/****************************************************************************************************************************************************
 * DEFINITION OF PRIVATE FUNCTIONS                                                                                                                  *
 ****************************************************************************************************************************************************/

/*!
 * \brief This function ascertains whether the Battle Map square is disguisable and sets the value of the member variable m_disguisable accordingly.
 */
void BattleMapSquare::ascertainDisguisable()
{
    if (m_battleMapSquareDisguisePixmap.isNull())
    {
        /* if disguise pixmap is not available, Battle Map square is not disguisable */
        m_disguisable = false;
    }
    else
    {
        QImage battleMapSquareOriginalImage = m_battleMapSquareOriginalPixmap.toImage();
        QImage battleMapSquareDisguiseImage = m_battleMapSquareDisguisePixmap.toImage();

        QCryptographicHash hashOriginalImage(QCryptographicHash::Sha256);
        QCryptographicHash hashDisguiseImage(QCryptographicHash::Sha256);

        hashOriginalImage.addData(reinterpret_cast<const char*>(battleMapSquareOriginalImage.bits()), battleMapSquareOriginalImage.sizeInBytes());
        hashDisguiseImage.addData(reinterpret_cast<const char*>(battleMapSquareDisguiseImage.bits()), battleMapSquareDisguiseImage.sizeInBytes());

        /* if checksums of original and disguise pixmap differ, Battle Map square is disguisable */
        m_disguisable = (hashOriginalImage.result() != hashDisguiseImage.result());
    }
}
