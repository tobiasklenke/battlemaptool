/****************************************************************************************************************************************************
 * INCLUDES                                                                                                                                         *
 ****************************************************************************************************************************************************/

#include "dialogsettings.h"
#include "ui_dialogsettings.h"

/****************************************************************************************************************************************************
 * DEFINITION OF PUBLIC FUNCTIONS                                                                                                                   *
 ****************************************************************************************************************************************************/

/*!
 * \brief This function is the constructor of the class DialogSettings.
 */
DialogSettings::DialogSettings(QWidget *parent) :
    QDialog(parent),
    m_userInterface(new Ui::DialogSettings),
    m_settingsChanged(false)
{
    QSettings settings;

    /* set up the user interface */
    m_userInterface->setupUi(this);

    /* connect signals and slots of user interface widgets */
    connect(m_userInterface->lineEditDiagonal, SIGNAL(editingFinished()), this, SLOT(editingFinishedLineEditDiagonal()));
    connect(m_userInterface->lineEditResolutionWidth, SIGNAL(editingFinished()), this, SLOT(editingFinishedLineEditResolutionWidth()));
    connect(m_userInterface->lineEditResolutionHeight, SIGNAL(editingFinished()), this, SLOT(editingFinishedLineEditResolutionHeight()));
    connect(m_userInterface->dialogButtonBox, SIGNAL(accepted()), this, SLOT(acceptedDialogButtonBox()));
    connect(m_userInterface->dialogButtonBox, SIGNAL(rejected()), this, SLOT(rejectedDialogButtonBox()));

    /* initialize edit fields and member variables with current settings */
    m_userInterface->lineEditDiagonal->setText(QString::number(settings.value(CONFIGKEY_PLAYERSCREEN_DIAGONAL).toReal()));
    m_userInterface->lineEditResolutionWidth->setText(QString::number(settings.value(CONFIGKEY_PLAYERSCREEN_RESOLUTION_WIDTH).toUInt()));
    m_userInterface->lineEditResolutionHeight->setText(QString::number(settings.value(CONFIGKEY_PLAYERSCREEN_RESOLUTION_HEIGHT).toUInt()));
    m_diagonalToBeApplied = settings.value(CONFIGKEY_PLAYERSCREEN_DIAGONAL).toReal();
    m_resolutionWidthToBeApplied = settings.value(CONFIGKEY_PLAYERSCREEN_RESOLUTION_WIDTH).toUInt();
    m_resolutionHeightToBeApplied = settings.value(CONFIGKEY_PLAYERSCREEN_RESOLUTION_HEIGHT).toUInt();
}

/*!
 * \brief This function is the destructor of the class DialogSettings.
 */
DialogSettings::~DialogSettings()
{
    /* delete objects created in the constructor */
    delete m_userInterface;
}

/*!
 * \brief This function returns the value of the member variable m_settingsChanged.
 */
bool DialogSettings::getSettingsChanged() const
{
    return m_settingsChanged;
}

/****************************************************************************************************************************************************
 * DEFINITION OF PROTECTED FUNCTIONS                                                                                                                *
 ****************************************************************************************************************************************************/

/* - */

/****************************************************************************************************************************************************
 * DEFINITION OF PRIVATE SLOT FUNCTIONS                                                                                                             *
 ****************************************************************************************************************************************************/

/*!
 * \brief This function handles the editing of lineEditDiagonal.
 */
void DialogSettings::editingFinishedLineEditDiagonal()
{
    /* check text string for valid format (float number) */
    bool validNumber;
    qreal inputValue = m_userInterface->lineEditDiagonal->text().toFloat(&validNumber);

    if (!validNumber || PLAYERSCREEN_MINIMUMDIAGONAL > inputValue)
    {
        /* show message box in case of invalid format or not positive number */
        QMessageBox msgBox(this);
        msgBox.setWindowTitle("Invalid input");
        msgBox.setText("Input '" + m_userInterface->lineEditDiagonal->text() + "' is invalid.");
        msgBox.setIcon(QMessageBox::Warning);
        msgBox.exec();

        /* reset text to last valid number of pixels */
        m_userInterface->lineEditDiagonal->setText(QString::number(m_diagonalToBeApplied));
    }
    else
    {
        /* round float number to first decimal place */
        inputValue = roundToDecimalPlaces(inputValue, PLAYERSCREEN_DIAGONAL_DECIMAL_PLACES);

        /* update text in case that number has been rounded */
        m_userInterface->lineEditDiagonal->setText(QString::number(inputValue));

        /* update setting value to be applied according to input value */
        m_diagonalToBeApplied = inputValue;
    }
}

/*!
 * \brief This function handles the editing of lineEditResolutionWidth.
 */
void DialogSettings::editingFinishedLineEditResolutionWidth()
{
    /* check text string for valid format (integer number) */
    bool validNumber;
    qint32 inputValue = m_userInterface->lineEditResolutionWidth->text().toInt(&validNumber, 10);

    if (!validNumber || PLAYERSCREEN_MINIMUMNUMBERPIXELS > inputValue)
    {
        /* show message box in case of invalid format or not positive number */
        QMessageBox msgBox(this);
        msgBox.setWindowTitle("Invalid input");
        msgBox.setText("Input '" + m_userInterface->lineEditResolutionWidth->text() + "' is invalid.");
        msgBox.setIcon(QMessageBox::Warning);
        msgBox.exec();

        /* reset text to last valid number of pixels */
        m_userInterface->lineEditResolutionWidth->setText(QString::number(m_resolutionWidthToBeApplied));
    }
    else
    {
        /* update setting value to be applied according to input value */
        m_resolutionWidthToBeApplied = inputValue;
    }
}

/*!
 * \brief This function handles the editing of lineEditResolutionHeight.
 */
void DialogSettings::editingFinishedLineEditResolutionHeight()
{
    /* check text string for valid format (integer number) */
    bool validNumber;
    qint32 inputValue = m_userInterface->lineEditResolutionHeight->text().toInt(&validNumber, 10);

    if (!validNumber || PLAYERSCREEN_MINIMUMNUMBERPIXELS > inputValue)
    {
        /* show message box in case of invalid format or not positive number */
        QMessageBox msgBox(this);
        msgBox.setWindowTitle("Invalid input");
        msgBox.setText("Input '" + m_userInterface->lineEditResolutionHeight->text() + "' is invalid.");
        msgBox.setIcon(QMessageBox::Warning);
        msgBox.exec();

        /* reset text to last valid number of pixels */
        m_userInterface->lineEditResolutionHeight->setText(QString::number(m_resolutionHeightToBeApplied));
    }
    else
    {
        /* update setting value to be applied according to input value */
        m_resolutionHeightToBeApplied = inputValue;
    }
}

/*!
 * \brief This function handles a click on the push button from dialogButtonBox with AcceptRole.
 */
void DialogSettings::acceptedDialogButtonBox()
{
    QSettings settings;

    /* check settings for change */
    if ((m_userInterface->lineEditDiagonal->text() != settings.value(CONFIGKEY_PLAYERSCREEN_DIAGONAL)) ||
        (m_userInterface->lineEditResolutionWidth->text() != settings.value(CONFIGKEY_PLAYERSCREEN_RESOLUTION_WIDTH)) ||
        (m_userInterface->lineEditResolutionHeight->text() != settings.value(CONFIGKEY_PLAYERSCREEN_RESOLUTION_HEIGHT)))
    {
        m_settingsChanged = true;
    }

    /* update settings */
    settings.setValue(CONFIGKEY_PLAYERSCREEN_DIAGONAL, m_userInterface->lineEditDiagonal->text());
    settings.setValue(CONFIGKEY_PLAYERSCREEN_RESOLUTION_WIDTH, m_userInterface->lineEditResolutionWidth->text());
    settings.setValue(CONFIGKEY_PLAYERSCREEN_RESOLUTION_HEIGHT, m_userInterface->lineEditResolutionHeight->text());

    emit accepted();
}

/*!
 * \brief This function handles a click on the push button from dialogButtonBox with RejectRole.
 */
void DialogSettings::rejectedDialogButtonBox()
{
    emit rejected();
}

/*!
 * \brief This function handles a click on the close button.
 */
void DialogSettings::reject()
{
    /* handle click on close button as click on the push button from dialogButtonBox with RejectRole */
    rejectedDialogButtonBox();
}

/****************************************************************************************************************************************************
 * DEFINITION OF PRIVATE FUNCTIONS                                                                                                                  *
 ****************************************************************************************************************************************************/

/* - */
