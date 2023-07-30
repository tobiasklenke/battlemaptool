#ifndef DIALOG_NEWBATTLEMAP_H
#define DIALOG_NEWBATTLEMAP_H

/****************************************************************************************************************************************************
 * Includes
 ****************************************************************************************************************************************************/

#include <QDialog>
#include <QFileDialog>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QMessageBox>

#include "battlemap.h"
#include "battlemapscene.h"
#include "screencalc.h"

#include "defines.h"

/****************************************************************************************************************************************************
 * Class Declaration
 ****************************************************************************************************************************************************/

namespace Ui
{
    class Dialog_NewBattleMap;
}

/*!
 * \brief This class implements the functionality needed for the creation of a new Battle Map.
 */
class Dialog_NewBattleMap : public QDialog
{
    Q_OBJECT

public:

    /*!
     * \brief This function is the constructor of the class Dialog_NewBattleMap.
     */
    Dialog_NewBattleMap(QWidget *parent = nullptr);

    /*!
     * \brief This function is the destructor of the class Dialog_NewBattleMap.
     */
    ~Dialog_NewBattleMap();

    /*!
     * \brief This function returns the value of the member variable m_battleMapImageSelectedFromSource.
     */
    bool getBattleMapImageSelectedFromSource() const;

    /*!
     * \brief This function returns the pixmap of the member variable pBattleMapImagePixMap.
     */
    QPixmap getBattleMapPixmap() const;

    /*!
     * \brief This function returns the address of the newly created Battle Map.
     */
    BattleMap * getBattleMap() const;

private slots:

    /*!
     * \brief This function handles a toggle of RadioButton_ImageBattleMap.
     */
    void toggled_RadioButton_ImageBattleMap(bool checked);

    /*!
     * \brief This function handles a toggle of RadioButton_EmptyBattleMap.
     */
    void toggled_RadioButton_EmptyBattleMap(bool checked);

    /*!
     * \brief This function handles the editing of LineEdit_Source.
     */
    void editingFinished_LineEdit_Source();

    /*!
     * \brief This function handles a click on PushButton_SelectSource.
     */
    void released_PushButton_SelectSource();

    /*!
     * \brief This function handles the editing of LineEdit_NumberRows.
     */
    void editingFinished_LineEdit_NumberRows();

    /*!
     * \brief This function handles the editing of LineEdit_NumberColumns.
     */
    void editingFinished_LineEdit_NumberColumns();

    /*!
     * \brief This function handles a click on PushButton_DecrementNumberRows.
     */
    void released_PushButton_DecrementNumberRows();

    /*!
     * \brief This function handles a click on PushButton_IncrementNumberRows.
     */
    void released_PushButton_IncrementNumberRows();

    /*!
     * \brief This function handles a click on PushButton_DecrementNumberColumns.
     */
    void released_PushButton_DecrementNumberColumns();

    /*!
     * \brief This function handles a click on PushButton_IncrementNumberColumns.
     */
    void released_PushButton_IncrementNumberColumns();

    /*!
     * \brief This function handles the selection of a Battle Map square.
     */
    void selected_BattleMapSquare();

    /*!
     * \brief This function handles a state change of CheckBox_DrawBattleMapGrid.
     */
    void stateChanged_CheckBox_DrawBattleMapGrid(int state);

    /*!
     * \brief This function handles a click on the push button with AcceptRole.
     */
    void accepted_DialogButtonBox();

private:

    /*!
     * \brief This function shows the empty Battle Map image.
     */
    void showEmptyBattleMapImage();

    /*!
     * \brief This function shows the Battle Map image from selected source.
     */
    void showSourceBattleMapImage();

    /*!
     * \brief This function corrects the number of rowsconsidering the Battle Map squares aspect ratio.
     */
    void correctNumberRows();

    /*!
     * \brief This function corrects the number of columns considering the Battle Map squares aspect ratio.
     */
    void correctNumberColumns();

    /*!
     * \brief This function controls the number of rows and columns.
     */
    void controlNumberRowsAndColumns();

    /*!
     * \brief This function draws the Battle Map grid.
     */
    void drawBattleMapGrid();

    /*!
     * \brief This is a pointer to the user interface of the class Dialog_NewBattleMap.
     */
    Ui::Dialog_NewBattleMap *pUserInterface;

    /*!
     * \brief This is a pointer to the BattleMapScene object that is set to GraphicsView_BattleMap.
     */
    BattleMapScene *pBattleMapScene;

    /*!
     * \brief This is the information whether the Battle Map image has been selected from source.
     */
    bool m_battleMapImageSelectedFromSource;

    /*!
     * \brief This is the pixmap of the Battle Map image.
     */
    QGraphicsPixmapItem *pBattleMapImagePixMap;

    /*!
     * \brief This is a pointer to the newly created Battle Map.
     */
    BattleMap * pBattleMap;
};

#endif // DIALOG_NEWBATTLEMAP_H
