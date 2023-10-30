#ifndef DEFINES_H
#define DEFINES_H

/****************************************************************************************************************************************************
 * INCLUDES                                                                                                                                         *
 ****************************************************************************************************************************************************/

/****************************************************************************************************************************************************
 * DEFINES                                                                                                                                          *
 ****************************************************************************************************************************************************/

/* CONFIGURATION PARAMETERS, TODO REMOVE */
#define CONFIG_MASTER_SCREEN_DIAGONAL                      23.8
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
 * \brief This is the line color of the Battle Map selection square.
 */
#define BATTLEMAPSELECTIONSQUARE_COLOR                     Qt::black

/*!
 * \brief This is the line width of the Battle Map selection square.
 */
#define BATTLEMAPSELECTIONSQUARE_LINEWIDTH                 3

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

/* Icon resource paths */

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
