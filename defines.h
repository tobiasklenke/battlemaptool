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
#define CONFIG_PLAYER_SCREEN_DIAGONAL                      32
#define CONFIG_PLAYER_SCREEN_RESOLUTION                    QSize(1920, 1080)
#define CONFIG_BATTLEMAPSQUARE_SIZE                        200
#define CONFIG_BATTLEMAPGRID_COLOR                         Qt::black
#define CONFIG_BATTLEMAPGRID_LINEWIDTH                     3

/* Scaling parameters */

/*!
 * \This is the value representing hundred percentage.
 */
#define HUNDRED_PERCENTAGE                                 100

/*!
 * \This is the maximum value in percentage that is allowed for the scale factor of a Battle Map view.
 */
#define BATTLEMAPVIEW_SCALEFACTOR_MAXVALUE_PERCENTAGE      200

/*!
 * \This is the minimum value in percentage that is allowed for the scale factor of a Battle Map view.
 */
#define BATTLEMAPVIEW_SCALEFACTOR_MINVALUE_PERCENTAGE      10

/*!
 * \This is the step size of the scale factor of a Battle Map view while scrolling.
 */
#define BATTLEMAPVIEW_SCALEFACTOR_STEPSIZE                 0.1

/* Battle Map grid parameters */

/*!
 * \brief This is the line width of the Battle Map grid.
 */
#define BATTLEMAPGRID_COLOR                                Qt::black

/*!
 * \brief This is the line width of the Battle Map grid.
 */
#define BATTLEMAPGRID_LINEWIDTH                            3

/* Image resource paths */

/*!
 * \brief This is the resource file path of the QSplashScreen image.
 */
#define SPLASHSCREENIMAGE_SOURCE                           ":/images/images/splashscreenimage.png"

/*!
 * \brief This is the resource file path of the empty Battle Map square image.
 */
#define EMPTYBATTLEMAPSQUAREIMAGE_SOURCE                   ":/images/images/emptybattlemapsquareimage.png"

/****************************************************************************************************************************************************
 * MACROS                                                                                                                                           *
 ****************************************************************************************************************************************************/

/****************************************************************************************************************************************************
 * GLOBAL TYPE DEFINITIONS                                                                                                                          *
 ****************************************************************************************************************************************************/

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
