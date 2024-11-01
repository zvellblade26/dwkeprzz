/* See LICENSE file for copyright and license details. */
/* Default settings; can be overriden by command line. */

static int topbar = 1;                      /* -b  option; if 0, dmenu appears at bottom     */
/* -fn option overrides fonts[0]; default X11 font or font set */
static const char *fonts[] = {
	/*"SF Pro Text:size=13:style=Bold:pixelsize=13:antialias=true:autohint=true"*/
	/*"JetBrains Mono NL:size=16:style=Bold:pixelsize=16:antialias=true:autohint=true"*/
	"NBP Informa FiveSix:size=23:style=Bold:pixelsize=23:antialias=true:autohint=true"

};
static const char *prompt      = NULL;      /* -p  option; prompt to the left of input field */
static const char *colors[SchemeLast][2] = {
	/*     fg         bg       */
	[SchemeNorm] = { "#000000", "#b6b6b6" },
	[SchemeSel] = { "#000000", "#ededed" },
	[SchemeOut] = { "#000000", "#00ffff" },
};
/* -l option; if nonzero, dmenu uses vertical list with given number of lines */
static unsigned int lines      = 0;

/*
 * Characters not considered part of a word while deleting words
 * for example: " /?\"&[]"
 */
static const char worddelimiters[] = " ";
