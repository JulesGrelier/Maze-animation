#ifndef CONSTANTS
#define CONSTANTS

/* -------- SHOULDN'T TOUCH -------- */
#define WIDTH 1080
#define HEIGHT 720
/* --------------------------------- */


#define SIZE_SQUARE 4
#define THICKNESS 1

/* ---------- DON'T TOUCH ---------- */
#define NB_H_SQUARE WIDTH/SIZE_SQUARE
#define NB_V_SQUARE HEIGHT/SIZE_SQUARE
#define NB_SQUARES NB_H_SQUARE * NB_V_SQUARE
/* --------------------------------- */

#define SHOW_CONSTRUCTION true
#define STEP_FOR_COLOR_ANIMATION 2

#define RED_VALUE_1 255
#define GREEN_VALUE_1 230
#define BLUE_VALUE_1 70

#define RED_VALUE_2 200
#define GREEN_VALUE_2 0
#define BLUE_VALUE_2 90

/* ---------- DON'T TOUCH ---------- */
#define RED_GRADIENT_1 (RED_VALUE_2 - RED_VALUE_1) / 60.f
#define RED_GRADIENT_2 -RED_VALUE_2 / 40.f

#define GREEN_GRADIENT_1 (GREEN_VALUE_2 - GREEN_VALUE_1) / 60.f
#define GREEN_GRADIENT_2 -GREEN_VALUE_2 / 40.f

#define BLUE_GRADIENT_1 (BLUE_VALUE_2 - BLUE_VALUE_1) / 60.f
#define BLUE_GRADIENT_2 -BLUE_VALUE_2 / 40.f
/* --------------------------------- */

#endif