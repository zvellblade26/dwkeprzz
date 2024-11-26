/* See LICENSE file for copyright and license details. */
/* Default settings; can be overriden by command line. */

static int topbar = 1;                      /* -b  option; if 0, dmenu appears at bottom     */
static int instant = 1;                     /* -n  option; if 1, select single entry automatically */
static int centered = 1;                    /* -c option; centers dmenu on screen */
static int min_width = 650;                    /* minimum width when centered */
static const float menu_height_ratio = 3.0f;  /* This is the ratio used in the original calculation */
/* -fn option overrides fonts[0]; default X11 font or font set */
static const char *fonts[] = {
	//"SF Pro Display:style=SemiBold:pixelsize=25:antialias=true:autohint=true"
	//"SF Pro:style=SemiBold:pixelsize=25:antialias=true:autohint=true"
	"SF Pro Rounded:style=Regular:pixelsize=28:antialias=true:autohint=true"
	//"SF Pro Text:style=SemiBold:pixelsize=25:antialias=true:autohint=true"
	//"JetBrainsMonoNL NFP ExtraBold:style=Regular:pixelsize=20:antialias=true:autohint=true"
};
static const char *prompt      = NULL;      /* -p  option; prompt to the left of input field */
static const char *colors[SchemeLast][2] = {
    [SchemeNorm]   = { "#ffffff", "#1e1e1e" }, // Light text on dark background
    [SchemeSel]    = { "#ffffff", "#3e74c7" }, // Highlighted item with dark background
    [SchemeOut]    = { "#000000", "#00ffff" },  // Output color, you can customize as needed
	 [SchemeBorder] = { "#000000", NULL },
};
/* -l option; if nonzero, dmenu uses vertical list with given number of lines */
//static unsigned int lines      = 0;
static unsigned int lines      = 7;
static unsigned int border_width = 5;
/*
 * Characters not considered part of a word while deleting words
 * for example: " /?\"&[]"
 */
static const char worddelimiters[] = " ";
