/* See LICENSE file for copyright and license details. */
/* Default settings; can be overriden by command line. */

static int topbar = 1;                      /* -b  option; if 0, dmenu appears at bottom     */
/* -fn option overrides fonts[0]; default X11 font or font set */
static const char *fonts[2] = {
	//"monoscape:size=38",
	"monoscape:size=12:Style=Book Italic",
	//"emoji:pixelsize=40:style=Regular"
	"emoji:pixelsize=14:style=Regular"
};
static const char *prompt      = NULL;      /* -p  option; prompt to the left of input field */
static const char *colors[SchemeLast][2] = {
	/*     fg         bg       */
	[SchemeNorm] = { "#d9e3f0", "#373e47" }, //col_gray3,col_gray1
	[SchemeSel] = { "#373e47", "#40bf40" }, //col_gray4,col_cyan
	[SchemeOut] = { "#000000", "#00ffff" },
};
/* -l option; if nonzero, dmenu uses vertical list with given number of lines */
static unsigned int lines      = 15;
/* -h option; minimum height of a menu line */
static unsigned int lineheight = 20;
static unsigned int min_lineheight = 20;

/*
 * Characters not considered part of a word while deleting words
 * for example: " /?\"&[]"
 */
static const char worddelimiters[] = " ";
