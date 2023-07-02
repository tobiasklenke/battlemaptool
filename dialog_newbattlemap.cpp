/****************************************************************************************************************************************************
 * Includes
 ****************************************************************************************************************************************************/

#include "dialog_newbattlemap.h"
#include "ui_dialog_newbattlemap.h"

/****************************************************************************************************************************************************
 * Member Function Definition
 ****************************************************************************************************************************************************/

/*!
 * \brief This function is the constructor of the class Dialog_NewBattleMap.
 */
Dialog_NewBattleMap::Dialog_NewBattleMap(QWidget *parent) : QDialog(parent), pUserInterface(new Ui::Dialog_NewBattleMap)
{
    qDebug() << "..." << __func__;

    pUserInterface->setupUi(this);

    /* Set initial state */
    pUserInterface->RadioButton_ImageBattleMap->setChecked(false);
    pUserInterface->RadioButton_EmptyBattleMap->setChecked(true);
    pUserInterface->LineEdit_Source->setEnabled(false);
    pUserInterface->PushButton_SelectSource->setEnabled(false);
    pUserInterface->LineEdit_NumberRows->setText("0");
    pUserInterface->LineEdit_NumberColumns->setText("0");
    pBattleMapScene = new BattleMapScene();
    showEmptyBattleMapImage();

    /* Set connections */
    connect(pUserInterface->RadioButton_ImageBattleMap, SIGNAL(toggled(bool)), this, SLOT(toggled_RadioButton_ImageBattleMap(bool)));
    connect(pUserInterface->RadioButton_EmptyBattleMap, SIGNAL(toggled(bool)), this, SLOT(toggled_RadioButton_EmptyBattleMap(bool)));
    connect(pUserInterface->LineEdit_Source, SIGNAL(editingFinished()), this, SLOT(editingFinished_LineEdit_Source()));
    connect(pUserInterface->PushButton_SelectSource, SIGNAL(released()), this, SLOT(released_PushButton_SelectSource()));
    connect(pUserInterface->LineEdit_NumberRows, SIGNAL(editingFinished()), this, SLOT(editingFinished_LineEdit_NumberRows()));
    connect(pUserInterface->LineEdit_NumberColumns, SIGNAL(editingFinished()), this, SLOT(editingFinished_LineEdit_NumberColumns()));
    connect(pUserInterface->PushButton_DecrementNumberRows, SIGNAL(released()), this, SLOT(released_PushButton_DecrementNumberRows()));
    connect(pUserInterface->PushButton_IncrementNumberRows, SIGNAL(released()), this, SLOT(released_PushButton_IncrementNumberRows()));
    connect(pUserInterface->PushButton_DecrementNumberColumns, SIGNAL(released()), this, SLOT(released_PushButton_DecrementNumberColumns()));
    connect(pUserInterface->PushButton_IncrementNumberColumns, SIGNAL(released()), this, SLOT(released_PushButton_IncrementNumberColumns()));
    connect(pBattleMapScene, SIGNAL(selected_BattleMapSquare()), this, SLOT(selected_BattleMapSquare()));
    connect(pUserInterface->DialogButtonBox, SIGNAL(accepted()), this, SLOT(accepted_DialogButtonBox()));
    connect(pUserInterface->DialogButtonBox, SIGNAL(rejected()), this, SLOT(rejected_DialogButtonBox()));
}

/*!
 * \brief This function is the destructor of the class Dialog_NewBattleMap.
 */
Dialog_NewBattleMap::~Dialog_NewBattleMap()
{
    qDebug() << "..." << __func__;

    delete pUserInterface;
    delete pBattleMapScene;
}

/*!
 * \brief This function handles a toggle of RadioButton_ImageBattleMap.
 */
void Dialog_NewBattleMap::toggled_RadioButton_ImageBattleMap(bool checked)
{
    qDebug() << "..." << __func__;

    if (checked)
    {
        /* Enable widgets for source selection */
        pUserInterface->LineEdit_Source->setEnabled(true);
        pUserInterface->PushButton_SelectSource->setEnabled(true);

        /* Disable widgets for numbers of rows and columns */
        pUserInterface->LineEdit_NumberRows->setEnabled(false);
        pUserInterface->LineEdit_NumberColumns->setEnabled(false);
        pUserInterface->PushButton_DecrementNumberRows->setEnabled(false);
        pUserInterface->PushButton_IncrementNumberRows->setEnabled(false);
        pUserInterface->PushButton_DecrementNumberColumns->setEnabled(false);
        pUserInterface->PushButton_IncrementNumberColumns->setEnabled(false);

        /* Reset source file path, number of rows and columns */
        pUserInterface->LineEdit_Source->setText("");
        pUserInterface->LineEdit_NumberRows->setText("0");
        pUserInterface->LineEdit_NumberColumns->setText("0");
    }
}


/*!
 * \brief This function handles a toggle of RadioButton_EmptyBattleMap.
 */
void Dialog_NewBattleMap::toggled_RadioButton_EmptyBattleMap(bool checked)
{
    qDebug() << "..." << __func__;

    if (checked)
    {
        /* Disable widgets for source selection */
        pUserInterface->LineEdit_Source->setEnabled(false);
        pUserInterface->PushButton_SelectSource->setEnabled(false);

        /* Enable widgets for numbers of rows and columns */
        pUserInterface->LineEdit_NumberRows->setEnabled(true);
        pUserInterface->LineEdit_NumberColumns->setEnabled(true);
        pUserInterface->PushButton_DecrementNumberRows->setEnabled(true);
        pUserInterface->PushButton_IncrementNumberRows->setEnabled(true);
        pUserInterface->PushButton_DecrementNumberColumns->setEnabled(true);
        pUserInterface->PushButton_IncrementNumberColumns->setEnabled(true);

        /* Reset source file path, number of rows and columns */
        pUserInterface->LineEdit_Source->setText("");
        pUserInterface->LineEdit_NumberRows->setText("0");
        pUserInterface->LineEdit_NumberColumns->setText("0");

        /* Show empty battle map image */
        showEmptyBattleMapImage();
    }
}

/*!
 * \brief This function handles the editing of LineEdit_Source.
 */
void Dialog_NewBattleMap::editingFinished_LineEdit_Source()
{
    qDebug() << "..." << __func__;

    if (!pUserInterface->LineEdit_Source->text().isEmpty())
    {
        /* Show battle map image from selected source */
        showSourceBattleMapImage();
    }
}

/*!
 * \brief This function handles a click on PushButton_SelectSource.
 */
void Dialog_NewBattleMap::released_PushButton_SelectSource()
{
    qDebug() << "..." << __func__;

    /* Select source for battle map */
    QString selectedSource = QFileDialog::getOpenFileName(this, tr("Select Source"), ".", tr("Image Files (*.png *.jpg *.bmp)"));
    pUserInterface->LineEdit_Source->setText(selectedSource);

    /* LineEdit_Source has been edited, call slot function */
    editingFinished_LineEdit_Source();
}

/*!
 * \brief This function handles the editing of LineEdit_NumberRows.
 */
void Dialog_NewBattleMap::editingFinished_LineEdit_NumberRows()
{
    qDebug() << "..." << __func__;

}

/*!
 * \brief This function handles the editing of LineEdit_NumberColumns.
 */
void Dialog_NewBattleMap::editingFinished_LineEdit_NumberColumns()
{
    qDebug() << "..." << __func__;
}

/*!
 * \brief This function handles a click on PushButton_DecrementNumberRows.
 */
void Dialog_NewBattleMap::released_PushButton_DecrementNumberRows()
{
    qDebug() << "..." << __func__;

    if (0 <= pUserInterface->LineEdit_NumberRows->text().toInt() - 1)
    {
        pUserInterface->LineEdit_NumberRows->setText(QString::number(pUserInterface->LineEdit_NumberRows->text().toInt() - 1));
    }
}

/*!
 * \brief This function handles a click on PushButton_IncrementNumberRows.
 */
void Dialog_NewBattleMap::released_PushButton_IncrementNumberRows()
{
    qDebug() << "..." << __func__;

    pUserInterface->LineEdit_NumberRows->setText(QString::number(pUserInterface->LineEdit_NumberRows->text().toInt() + 1));
}

/*!
 * \brief This function handles a click on PushButton_DecrementNumberColumns.
 */
void Dialog_NewBattleMap::released_PushButton_DecrementNumberColumns()
{
    qDebug() << "..." << __func__;

    if (0 <= pUserInterface->LineEdit_NumberColumns->text().toInt() - 1)
    {
        pUserInterface->LineEdit_NumberColumns->setText(QString::number(pUserInterface->LineEdit_NumberColumns->text().toInt() - 1));
    }
}

/*!
 * \brief This function handles a click on PushButton_IncrementNumberColumns.
 */
void Dialog_NewBattleMap::released_PushButton_IncrementNumberColumns()
{
    qDebug() << "..." << __func__;

    pUserInterface->LineEdit_NumberColumns->setText(QString::number(pUserInterface->LineEdit_NumberColumns->text().toInt() + 1));
}

/*!
 * \brief This function handles the selection of a Battle Map square.
 */
void Dialog_NewBattleMap::selected_BattleMapSquare()
{
    qDebug() << "..." << __func__;

    QPointF selectedSquareEdges =  pBattleMapScene->getScenePosRelease() - pBattleMapScene->getScenePosPress();
    qreal averageEdgeLength = (selectedSquareEdges.rx() + selectedSquareEdges.ry()) / 2;

    qint8 numRows = abs(m_battleMapImage.size().height() / averageEdgeLength);
    qint8 numCols = abs(m_battleMapImage.size().width() / averageEdgeLength);

    /* Enable widgets for numbers of rows and columns */
    pUserInterface->LineEdit_NumberRows->setEnabled(true);
    pUserInterface->LineEdit_NumberColumns->setEnabled(true);
    pUserInterface->PushButton_DecrementNumberRows->setEnabled(true);
    pUserInterface->PushButton_IncrementNumberRows->setEnabled(true);
    pUserInterface->PushButton_DecrementNumberColumns->setEnabled(true);
    pUserInterface->PushButton_IncrementNumberColumns->setEnabled(true);

    pUserInterface->LineEdit_NumberRows->setText(QString::number(numRows));
    pUserInterface->LineEdit_NumberColumns->setText(QString::number(numCols));

    //TODO Berechneten Square wieder in Scene einzeichnen zur Kontrolle
}

/*!
 * \brief This function handles a click on the push button with AcceptRole.
 */
void Dialog_NewBattleMap::accepted_DialogButtonBox()
{
    qDebug() << "..." << __func__;

    //TODO: Implement storation of selected battle map image and number of rows and columns

    delete this;
}

/*!
 * \brief This function handles a click on the push button with RejectRole.
 */
void Dialog_NewBattleMap::rejected_DialogButtonBox()
{
    qDebug() << "..." << __func__;

    delete this;
}

/*!
 * \brief This function handles a click on the X title bar button.
 */
void Dialog_NewBattleMap::reject()
{
    qDebug() << "..." << __func__;

    delete this;
}

/*!
 * \brief This function shows the empty battle map image.
 */
void Dialog_NewBattleMap::showEmptyBattleMapImage()
{
    qDebug() << "..." << __func__;

    pUserInterface->GraphicsView_BattleMap->setScene(pBattleMapScene);
    pUserInterface->GraphicsView_BattleMap->setInteractive(false);
    pUserInterface->GraphicsView_BattleMap->viewport()->setCursor(Qt::ArrowCursor);
    pUserInterface->GraphicsView_BattleMap->setToolTip("");

    //TODO load from configuration data
    m_battleMapImage.load(EMPTY_BATTLEMAP_SOURCE);

    if (m_battleMapImage.isNull())
    {
        pBattleMapScene->clear();
        pBattleMapScene->setSceneRect(0, 0, 0, 0);
        pBattleMapScene->addText("Selected Battle Map Source is no image file!");
    }
    else
    {
        QGraphicsPixmapItem* item = new QGraphicsPixmapItem(QPixmap::fromImage(m_battleMapImage));
        pBattleMapScene->addItem(item);
        pBattleMapScene->setSceneRect(0, 0, m_battleMapImage.width(), m_battleMapImage.height());

        pUserInterface->GraphicsView_BattleMap->show();
    }
}

/*!
 * \brief This function shows the battle map image from selected source.
 */
void Dialog_NewBattleMap::showSourceBattleMapImage()
{
    qDebug() << "..." << __func__;

    QMessageBox msgBox(this);

    pUserInterface->GraphicsView_BattleMap->setScene(pBattleMapScene);
    pUserInterface->GraphicsView_BattleMap->setInteractive(false);
    pUserInterface->GraphicsView_BattleMap->viewport()->setCursor(Qt::ArrowCursor);
    pUserInterface->GraphicsView_BattleMap->setToolTip("");

    m_battleMapImage.load(pUserInterface->LineEdit_Source->text());

    if (m_battleMapImage.isNull())
    {
        pBattleMapScene->clear();
        pBattleMapScene->setSceneRect(0, 0, 0, 0);
        pBattleMapScene->addText("Selected Battle Map Source is no image file!");
    }
    else
    {
        pUserInterface->GraphicsView_BattleMap->setInteractive(true);
        pUserInterface->GraphicsView_BattleMap->viewport()->setCursor(Qt::CrossCursor);
        pUserInterface->GraphicsView_BattleMap->setToolTip("Select Battle Map square");

        QGraphicsPixmapItem* item = new QGraphicsPixmapItem(QPixmap::fromImage(m_battleMapImage));
        pBattleMapScene->addItem(item);
        pBattleMapScene->setSceneRect(0, 0, m_battleMapImage.width(), m_battleMapImage.height());

        pUserInterface->GraphicsView_BattleMap->show();

        msgBox.setWindowTitle("Select Battle Map square");
        msgBox.setText("Please select a Battle Map square in order to determine the number of rows and columns of the Battle Map.");
        msgBox.exec();
    }
}
