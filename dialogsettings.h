#ifndef DIALOGSETTINGS_H
#define DIALOGSETTINGS_H

/****************************************************************************************************************************************************
 * INCLUDES                                                                                                                                         *
 ****************************************************************************************************************************************************/

#include <QDialog>
#include <QMessageBox>
#include <QSettings>

#include "defines.h"
#include "screencalc.h"

/****************************************************************************************************************************************************
 * CLASS DECLARATION                                                                                                                                *
 ****************************************************************************************************************************************************/

namespace Ui
{
    class DialogSettings;
}

/*!
 * \brief This class implements the functionality needed for the change of settings.
 */
class DialogSettings : public QDialog
{
    Q_OBJECT

public:

    /*! *********************************************************************************************************************************************
     * \brief   This function is the constructor of the class DialogSettings.                                                                       *
     *                                                                                                                                              *
     * \details This function sets up the user interface, connects the signals and slots of the user interface widgets and initializes the edit     *
     *          fields and member variables with the current settings.                                                                              *
     *                                                                                                                                              *
     * \param   parent                        Parent of the class DialogSettings                                                                    *
     *                                                                                                                                              *
     * \return  This function does not have any return value.                                                                                       *
     ************************************************************************************************************************************************/
    DialogSettings(QWidget *parent = nullptr);

    /*! *********************************************************************************************************************************************
     * \brief   This function is the destructor of the class DialogSettings.                                                                        *
     *                                                                                                                                              *
     * \details This function deletes the objects created in the constructor.                                                                       *
     *                                                                                                                                              *
     * \return  This function does not have any return value.                                                                                       *
     ************************************************************************************************************************************************/
    ~DialogSettings();

    /*! *********************************************************************************************************************************************
     * \brief   This function returns the value of the member variable m_settingsChanged.                                                           *
     *                                                                                                                                              *
     * \details -                                                                                                                                   *
     *                                                                                                                                              *
     * \return  This function returns the value of the member variable m_settingsChanged.                                                           *
     ************************************************************************************************************************************************/
    bool getSettingsChanged() const;

protected: /* - */

signals: /* - */

private slots:

    /*! *********************************************************************************************************************************************
     * \brief   This function handles the editing of lineEditDiagonal.                                                                              *
     *                                                                                                                                              *
     * \details This function checks the text string of lineEditDiagonal for a valid format and updates the respective setting value to be applied  *
     *          according to the input value if the text string is interpretable as positive number. In case of an invalid format or a not possible *
     *          number, it shows a message box.                                                                                                     *
     *                                                                                                                                              *
     * \return  This function does not have any return value.                                                                                       *
     ************************************************************************************************************************************************/
    void editingFinishedLineEditDiagonal();

    /*! *********************************************************************************************************************************************
     * \brief   This function handles the editing of lineEditResolutionWidth.                                                                       *
     *                                                                                                                                              *
     * \details This function checks the text string of lineEditResolutionWidth for a valid format and updates the respective setting value to be   *
     *          applied according to the input value if the text string is interpretable as positive number. In case of an invalid format or a not  *
     *          possible number, it shows a message box.                                                                                            *
     *                                                                                                                                              *
     * \return  This function does not have any return value.                                                                                       *
     ************************************************************************************************************************************************/
    void editingFinishedLineEditResolutionWidth();

    /*! *********************************************************************************************************************************************
     * \brief   This function handles the editing of lineEditResolutionHeight.                                                                      *
     *                                                                                                                                              *
     * \details This function checks the text string of lineEditResolutionHeight for a valid format and updates the respective setting value to be  *
     *          applied according to the input value if the text string is interpretable as positive number. In case of an invalid format or a not  *
     *          possible number, it shows a message box.                                                                                            *
     *                                                                                                                                              *
     * \return  This function does not have any return value.                                                                                       *
     ************************************************************************************************************************************************/
    void editingFinishedLineEditResolutionHeight();

    /*! *********************************************************************************************************************************************
     * \brief   This function handles a click on the push button from dialogButtonBox with AcceptRole.                                              *
     *                                                                                                                                              *
     * \details This function first checks whether the settings have been changed and sets the member variable m_settingsChanged accordingly.       *
     *          Afterwards, it updates the settings. Finally, the function emits the signal accepted().                                             *
     *                                                                                                                                              *
     * \return  This function does not have any return value.                                                                                       *
     ************************************************************************************************************************************************/
    void acceptedDialogButtonBox();

    /*! *********************************************************************************************************************************************
     * \brief   This function handles a click on the push button from dialogButtonBox with RejectRole.                                              *
     *                                                                                                                                              *
     * \details This function emits the signal rejected().                                                                                          *
     *                                                                                                                                              *
     * \return  This function does not have any return value.                                                                                       *
     ************************************************************************************************************************************************/
    void rejectedDialogButtonBox();

    /*! *********************************************************************************************************************************************
     * \brief   This function handles a click on the close button.                                                                                  *
     *                                                                                                                                              *
     * \details This function handles a click on the close button as a click on the push button from dialogButtonBox with RejectRole.               *
     *                                                                                                                                              *
     * \return  This function does not have any return value.                                                                                       *
     ************************************************************************************************************************************************/
    void reject();

private:

    /*!
     * \brief This is a pointer to the user interface of the class DialogSettings.
     */
    Ui::DialogSettings *m_userInterface;

    /*!
     * \brief This is the information whether the settings have been changed.
     */
    bool m_settingsChanged;

    /*!
     * \brief This is the setting value to be applied for the Player Screen diagonal in inches.
     */
    qreal m_diagonalToBeApplied;

    /*!
     * \brief This is the setting value to be applied for the Player Screen width in pixels.
     */
    quint32 m_resolutionWidthToBeApplied;

    /*!
     * \brief This is the setting value to be applied for the Player Screen height in pixels.
     */
    quint32 m_resolutionHeightToBeApplied;
};

#endif // DIALOGSETTINGS_H
