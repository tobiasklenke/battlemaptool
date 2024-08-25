#ifndef DEFINES_H
#define DEFINES_H

/****************************************************************************************************************************************************
 * INCLUDES                                                                                                                                         *
 ****************************************************************************************************************************************************/

/****************************************************************************************************************************************************
 * DEFINES                                                                                                                                          *
 ****************************************************************************************************************************************************/

/* CONFIGURATION PARAMETERS, TODO REMOVE */
#define CONFIG_MASTER_SCREEN_RESOLUTION                    QSize(1920, 1080)
#define CONFIG_PLAYER_SCREEN_DIAGONAL                      23.8
#define CONFIG_PLAYER_SCREEN_RESOLUTION                    QSize(1920, 1080)
#define CONFIG_BATTLEMAPSQUARE_SIZE                        200
#define CONFIG_BATTLEMAPGRID_COLOR                         Qt::black
#define CONFIG_BATTLEMAPGRID_LINEWIDTH                     3

/* Scaling parameters */

/*!
 * \brief This is the value representing hundred percentage.
 */
#define HUNDRED_PERCENTAGE                                 100

/*!
 * \brief This is the minimum value in percentage that is allowed for the scale factor of a Battle Map view.
 */
#define BATTLEMAPVIEW_SCALEFACTOR_MINVALUE_PERCENTAGE      10

/*!
 * \brief This is the maximum value in percentage that is allowed for the scale factor of a Battle Map view.
 */
#define BATTLEMAPVIEW_SCALEFACTOR_MAXVALUE_PERCENTAGE      200

/*!
 * \brief This is the step size of the scale factor of a Battle Map view while scrolling.
 */
#define BATTLEMAPVIEW_SCALEFACTOR_STEPSIZE                 0.1

/* Battle Map parameters */

/*!
 * \brief This is the minimum number of rows and columns of the Battle Map.
 */
#define BATTLEMAP_MINIMUMNUMBERROWSANDCOLUMNS              1

/*!
 * \brief This is the line color of the Battle Map grid.
 */
#define BATTLEMAPGRID_COLOR                                Qt::black

/*!
 * \brief This is the line width of the Battle Map grid.
 */
#define BATTLEMAPGRID_LINEWIDTH                            3

/*!
 * \brief This is the line width of the Battle Map section frame.
 */
#define BATTLEMAPSECTIONFRAME_LINEWIDTH                    6

/*!
 * \brief This is the line color of the Battle Map selection rectangle.
 */
#define BATTLEMAPSELECTIONRECT_COLOR                       Qt::black

/*!
 * \brief This is the line width of the Battle Map selection rectangle.
 */
#define BATTLEMAPSELECTIONRECT_LINEWIDTH                   3

/*!
 * \brief This is the maximum expected number of rows to be calculated after Battle Map square selection.
 */
#define BATTLEMAPSELECTION_MAXIMUMNUMBERROWS               250U

/*!
 * \brief This is the maximum expected number of columns to be calculated after Battle Map square selection.
 */
#define BATTLEMAPSELECTION_MAXIMUMNUMBERCOLUMNS            250U

/*!
 * \brief This is the opacity of Battle Map squares within the Battle Map section frame on the master screen.
 */
#define BATTLEMAPSQUAREWITHINSECTIONFRAME_OPACITY          1.0

/*!
 * \brief This is the opacity of Battle Map squares outside the Battle Map section frame on the master screen.
 */
#define BATTLEMAPSQUAREOUTSIDESECTIONFRAME_OPACITY         0.5

/*!
 * \brief This is the opacity of uncovered Battle Map squares on the player screen.
 */
#define BATTLEMAPSQUAREUNCOVERED_OPACITY                   1.0

/*!
 * \brief This is the opacity of covered Battle Map squares on the player screen.
 */
#define BATTLEMAPSQUARECOVERED_OPACITY                     0.0

/*!
 * \brief This is the duration of the opacity animation of covered Battle Map squares on the player screen in miliseconds.
 */
#define BATTLEMAPSQUAREOPACITYANIMATION_DURATION           3000

/*!
 * \brief This is the color of covered Battle Map squares on the master screen.
 */
#define BATTLEMAPSQUARECOVERED_COLOR                       QColor(0, 0, 0, 150)

/* Image resource paths */

/*!
 * \brief This is the resource file path of the QSplashScreen image.
 */
#define SPLASHSCREENIMAGE_SOURCE                           ":/images/images/splashscreenimage.png"

/*!
 * \brief This is the resource file path of the empty Battle Map square image.
 */
#define EMPTYBATTLEMAPSQUAREIMAGE_SOURCE                   ":/images/images/emptybattlemapsquareimage.png"

/*!
 * \brief This is the resource file path of the wind rose image.
 */
#define WINDROSEIMAGE_SOURCE                               ":/images/images/windroseimage.png"

/* Icon resource paths */

/*!
 * \brief This is the resource file path of the Undo icon.
 */
#define UNDOICON_SOURCE                                    ":/icons/icons/undo.png"

/*!
 * \brief This is the resource file path of the Redo icon.
 */
#define REDOICON_SOURCE                                    ":/icons/icons/redo.png"

/*!
 * \brief This is the resource file path of the CoverBattleMap icon.
 */
#define COVERBATTLEMAPICON_SOURCE                          ":/icons/icons/coverbattlemap.png"

/*!
 * \brief This is the resource file path of the UncoverBattleMap icon.
 */
#define UNCOVERBATTLEMAPICON_SOURCE                        ":/icons/icons/uncoverbattlemap.png"

/* Miscellaneous */

/*!
 * \brief This is the size of custom pixmap cursors.
 */
#define CUSTOMPIXMAPCURSOR_SIZE                            32

/*!
 * \brief This is the orientation value for 0 degrees.
 */
#define ORIENTATION_0_DEGREES                              0.0

/*!
 * \brief This is the orientation value for 90 degrees.
 */
#define ORIENTATION_90_DEGREES                             90.0

/*!
 * \brief This is the orientation value for 180 degrees.
 */
#define ORIENTATION_180_DEGREES                            180.0

/*!
 * \brief This is the orientation value for 270 degrees.
 */
#define ORIENTATION_270_DEGREES                            270.0

/*!
 * \brief This is the orientation value for 360 degrees.
 */
#define ORIENTATION_360_DEGREES                            360.0

/*!
 * \brief This is the wind rose size in Battle Map squares.
 */
#define WINDROSESIZE_BATTLEMAPSQUARES                      3

/****************************************************************************************************************************************************
 * MACROS                                                                                                                                           *
 ****************************************************************************************************************************************************/

/****************************************************************************************************************************************************
 * GLOBAL TYPE DEFINITIONS                                                                                                                          *
 ****************************************************************************************************************************************************/

/*!
 * \brief This enum lists the toolbar operation modes used from the screen handlers.
 */
typedef enum
{
    /*!
     * \brief This is the default operation mode for selection.
     */
    Select,

    /*!
     * \brief This is the operation mode for covering parts of the Battle Map. (Only supported on master screen.)
     */
    CoverBattleMap,

    /*!
     * \brief This is the operation mode for uncovering parts of the Battle Map. (Only supported on master screen.)
     */
    UncoverBattleMap
} operationMode_t;

/*!
 * \brief This enum lists the z values of graphics items.
 */
typedef enum
{
    /*!
     * \brief This is the z value of backgrounded graphics items.
     */
    ZValueBackgroundedGraphicsItem,

    /*!
     * \brief This is the z value of not selected graphics items of Battle Map squares.
     */
    ZValueNotSelectedBattleMapSquareGraphicsItem,

    /*!
     * \brief This is the z value of not selected graphics items of coverage squares.
     */
    ZValueNotSelectedCoverageSquareGraphicsItem,

    /*!
     * \brief This is the z value of selected graphics items of Battle Map squares.
     */
    ZValueSelectedBattleMapSquareGraphicsItem,

    /*!
     * \brief This is the z value of selected graphics items of coverage squares.
     */
    ZValueSelectedCoverageSquareGraphicsItem,

    /*!
     * \brief This is the z value of foregrounded graphics items.
     */
    ZValueForegroundedGraphicsItem
} zValue_t;

/****************************************************************************************************************************************************
 * GLOBAL DECLARATIONS                                                                                                                              *
 ****************************************************************************************************************************************************/

/****************************************************************************************************************************************************
 * GLOBAL FUNCTION DECLARATIONS                                                                                                                     *
 ****************************************************************************************************************************************************/

/****************************************************************************************************************************************************
 * LOCAL FUNCTION DECLARATIONS                                                                                                                      *
 ****************************************************************************************************************************************************/

#endif // DEFINES_H
