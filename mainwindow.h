#ifndef MAINWINDOW_H
#define MAINWINDOW_H

/****************************************************************************************************************************************************
 * Includes
 ****************************************************************************************************************************************************/

#include <QMainWindow>

#include "dialog_newbattlemap.h"

/****************************************************************************************************************************************************
 * Class Declaration
 ****************************************************************************************************************************************************/

QT_BEGIN_NAMESPACE
namespace Ui
{
    class MainWindow;
}
QT_END_NAMESPACE

/*!
 * \brief This class implements the main functionality of the application.
 */
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:

    /*!
     * \brief This function is the constructor of the class MainWindow.
     */
    MainWindow(QWidget *parent = nullptr);

    /*!
     * \brief This function is the destructor of the class MainWindow.
     */
    ~MainWindow();

private slots:

    /*!
     * \brief This function opens the dialog Dialog_NewBattleMap.
     */
    void open_Dialog_NewBattleMap();

private:

    /*!
     * \brief This is a pointer to the user interface of the class MainWindow.
     */
    Ui::MainWindow *pUserInterface;

    /*!
     * \brief This is a pointer to the user interface of the class Dialog_NewBattleMap.
     */
    Dialog_NewBattleMap *pDialog_NewBattleMap;
};
#endif // MAINWINDOW_H
