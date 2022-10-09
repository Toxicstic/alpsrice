/* See LICENSE file for copyright and license details. */
#include <X11/XF86keysym.h>

/* appearance */
static const unsigned int borderpx  = 2;        /* border pixel of windows */
static const unsigned int snap      = 16;       /* snap pixel */
static const int swallowfloating    = 0;        /* 1 means swallow floating windows by default */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const int user_bh            = 2;        /* 2 is the default spacing around the bar's font */
static const char *fonts[]          = { "monospace:size=12:style=Book Italic,Italic", "icons:pixelsize=14:style=Regular", "emoji:pixelsize=16" };
static const char dmenufont[]       = "monospace:size=12:style=Book";
static const char norm_bg[]       = "#373e47"; // not selected bg
static const char norm_border[]       = "#373e47"; // border not selected
static const char norm_fg[]       = "#d9e3f0"; // not selected foreground
static const char sel_fg[]       = "#373e47"; // selected foreground
static const char col_accent[]        = "#40bf40"; // selected border, bg
static const char *colors[][3]      = {
    /*               fg		bg		border   */
    [SchemeNorm] = { norm_fg,	norm_bg,	norm_border },
    [SchemeSel]  = { sel_fg,	col_accent,	col_accent  },
};

/* tagging */
//static const char *tags[] = { "🖤", "⭐", "🤥", "🫠", "🧌", "👺", "🎶" };
//static const char *tags[] = { "I","II","III","IV","V","VI","VII","IIX","IX" };
static const char *tags[] = { "1","2","3","4","5","6","7","8","🎶" };

static const Rule rules[] = {
    /* xprop(1):
     *	WM_CLASS(STRING) = instance, class
     *	WM_NAME(STRING) = title
     */
    /* class     instance  title           tags mask  isfloating  isterminal  noswallow  monitor */
    { "Gimp",    NULL,     NULL,           0,         1,          0,           0,        -1 },
    { "Firefox", NULL,     NULL,           1 << 8,    0,          0,          -1,        -1 },
    { "St",      NULL,     NULL,           0,         0,          1,           0,        -1 },
    { NULL,      NULL,     "Event Tester", 0,         0,          0,           1,        -1 }, /* xev */
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */

#include "layouts.c"
static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "t",      tile },    /* first entry is default */
	{ "f",      NULL },    /* no layout function means floating behavior */
	{ "m",      monocle },
	{ "g",      grid },
};

/* key definitions */
#define STATUSBAR "dwmblocks"
#define MODKEY Mod1Mask
#define ALTKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *browser[] = { "setsid", "chromium-browser", NULL };
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", norm_bg, "-nf", norm_fg, "-sb", col_accent, "-sf", sel_fg, NULL };
static const char *termcmd[]  = { "st", NULL };

static const char volume_step[2]		= "5";		/* in percentage */
static const char *volumemutecmd[]		= { "pamixer", "-t", NULL };
//static const char *volumeincreasecmd[]	= { "pamixer", "-i", volume_step, "&&" , "pkill", "-RTMIN+3", "dwmblocks", NULL };
//static const char *volumedecreasecmd[]	= { "pamixer", "-d", volume_step, "&&" , "pkill", "-RTMIN+3", "dwmblocks", NULL };

static Key keys[] = {
    /* modifier                     key        function        argument */

	// layouts
	{ ALTKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },
	{ ALTKEY,                       XK_f,      setlayout,      {.v = &layouts[1]} },
	{ ALTKEY,                       XK_m,      setlayout,      {.v = &layouts[2]} },
	{ ALTKEY,                       XK_g,      setlayout,      {.v = &layouts[3]} },

    // dwm controls
	{ MODKEY,                       XK_space,  setlayout,      {0} },
	{ MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
    // --visual
    { MODKEY|ShiftMask,             XK_q,      quit,           {0} },
    { MODKEY|ShiftMask,             XK_c,      killclient,     {0} },
    { MODKEY,                       XK_b,      togglebar,      {0} },

    // focus
    { MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
    { MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
    { MODKEY,                       XK_h,      setmfact,       {.f = -0.01} },
    { MODKEY,                       XK_l,      setmfact,       {.f = +0.01} },

    { MODKEY,                       XK_Return, zoom,           {0} },

    { MODKEY,                       XK_Tab,    view,           {0} },
    { MODKEY,                       XK_0,      view,           {.ui = ~0 } },
    { MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },

    // Monitors
    { MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
    { MODKEY,                       XK_period, focusmon,       {.i = +1 } },
    { MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
    { MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },

    // -- controls
    { MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
    { MODKEY,                       XK_d,      incnmaster,     {.i = -1 } },
    { MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },

    // tag controls
    TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)

	// launch
	{ ALTKEY,		XK_space,	spawn,		SHCMD("globsearch") },
	{ MODKEY,		XK_w,		spawn,          { .v = browser } },
	{ MODKEY,		XK_t,		spawn,          SHCMD("torrentsearcher") },

	{ MODKEY,		XK_e,		spawn,          SHCMD("em") },
	{ MODKEY,		XK_o,		spawn,          SHCMD("mufzf") },
	{ MODKEY,		XK_u,		spawn,          SHCMD("kpmenu -d ~/.yourkeypassdatabse.kdbx") },
	{ MODKEY,		XK_s,		spawn,          SHCMD("web-search") },
	{ MODKEY|ShiftMask,	XK_b,		spawn,          SHCMD("bookmarks") },
	{ MODKEY|ShiftMask,	XK_l,		spawn,		SHCMD("power") },
	{ MODKEY|ShiftMask,	XK_w,		spawn,          SHCMD("ap") },
	{ MODKEY|ShiftMask,	XK_t,		spawn,          SHCMD("wallpaper") },
	//{ MODKEY|ShiftMask,	XK_s,		spawn,          SHCMD("spotify") },
	{ MODKEY|ShiftMask,	XK_i,		spawn,          SHCMD("ytfzf -D") },
	//{ MODKEY|ShiftMask,	XK_p,		spawn,		SHCMD("scrot --select ~/px/scr/%Y-%m-%d_%H-%M-%S.png") },

	// -- dwm
	{ MODKEY,                       XK_p,      spawn,          {.v = dmenucmd } },
	{ MODKEY|ShiftMask,             XK_Return, spawn,          {.v = termcmd } },

	// function keys (chromebook) 
	{ 0,	XF86XK_MonBrightnessDown,	spawn,	SHCMD("doas intel_backlight -") },
	{ 0,	XF86XK_MonBrightnessUp,		spawn,	SHCMD("doas intel_backlight +") },

	{ 0,	XF86XK_AudioMute,			spawn,	{ .v = volumemutecmd } },
	{ 0,	XF86XK_AudioRaiseVolume,	spawn,	SHCMD("pamixer -i 5 && pkill -RTMIN+3 dwmblocks") },
	{ 0,	XF86XK_AudioLowerVolume,	spawn,	SHCMD("pamixer -d 5 && pkill -RTMIN+3 dwmblocks") },
	
	// TODO: doesnt work for some reason
	{ 0,	XF86XK_Tools,				spawn,	SHCMD("xscreensaver-command -lock") },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
    /* click                event mask      button          function        argument */
    { ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
    { ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
    { ClkWinTitle,          0,              Button2,        zoom,           {0} },
    { ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
    { ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
    { ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
    { ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
    { ClkTagBar,            0,              Button1,        view,           {0} },
    { ClkTagBar,            0,              Button3,        toggleview,     {0} },
    { ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
    { ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};
