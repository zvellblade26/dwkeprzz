/* See LICENSE file for copyright and license details. */
#include <X11/XF86keysym.h>

/* appearance */
static const unsigned int borderpx  = 0.1;      /* border pixel of windows */
static const unsigned int snap      = 0;       /* snap pixel default = 26 */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const int focusonwheel       = 0;
static const char *fonts[]          = { "MesloLGL Nerd Font Propo:pixelsize=15:style=Bold:antialias=true:autohint=true" };
#define ICONSIZE bh       /* icon size */
#define ICONSPACING 10    /* space between icon and title */

static const char nmft[]   = "#82ffff";
static const char brdr[]   = "#000000";
static const char ttbg[]   = "#001919";

static const char *colors[][3] = {
[SchemeNorm]  = { nmft, ttbg, brdr },
[SchemeSel]   = { ttbg, nmft, brdr },
[SchemeTitle] = { NULL, ttbg, brdr },
[SchemeUrg]  = { "#ffffff", "#ff0000", "#fffe3e" },
};

static const Block blocks[] = {
	{ "#82ffff",      "sb-wifi",											        0,		      1 },
	{ "#82e8ff",      "sb-volume",										        0,		      2 },
	{ "#82bdff",      "echo \" $(date '+%a, (%d)-%m  %I:%M')\"",      60,           3 },
	{ "#8287ff",      "sb-battery",											     5,	  	      4 },
	{ "#7273ff",      "sb-cpu",											        0,	  	      0 },
};
//kill -44 $(pidof dwm)
//Just add 34 to your typical signal number.

static char delimiter[] = " ";
#define CMDLENGTH	50


/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

static const Rule rules[] = {
	/* class           instance    title       tags mask     isfloating   monitor */
	{ "alacritty",     NULL,       NULL,       0,            0,           -1 },
	{ "firefox",       NULL,       NULL,       1 << 1,       0,           -1 },
	{ "libreoffice",   NULL,       NULL,       1 << 2,       0,           -1 },
	{ "Thunar",        NULL,       NULL,       0,            1,           -1 },
	{ "pavucontrol",   NULL,       NULL,       0,			   1,           -1 },
};

/* layout(s) */
static const float mfact     = 0.6; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 0;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */

static const Layout layouts[] = {
//dwm.c Layout "symbol on bar"
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
};


/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* commands */
// APPS
static char dmenumon[2]               = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[]         = { "dmenu_run", NULL };
static const char *termcmd[]          = { "alacritty", NULL };
static const char *browser[]          = { "firefox", NULL };
static const char *thunar[]           = { "thunar", NULL };
static const char *ss[]		           = { "xfce4-screenshooter", NULL };

#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

static const Key keys[] = {
	/* modifier                     key									function        argument */
	{ MODKEY,							  XK_space,							spawn,          {.v = dmenucmd } },
	{ MODKEY|ShiftMask,             XK_Return, 						spawn,          {.v = termcmd } },
	{ MODKEY,                       XK_e,      						spawn,          {.v = thunar } },
	{ MODKEY|ShiftMask,             XK_s,  						   spawn,          {.v = ss } },
	{ MODKEY,                       XK_f,      						spawn,          {.v = browser } },


	{ Mod1Mask,							  XK_g,								spawn,			 SHCMD("www-sh") },
	{ MODKEY,							  XK_s,								spawn,			 SHCMD("dbrowse-sh") },
	{ MODKEY|ControlMask,			  XK_p,								spawn,			 SHCMD("pgtest-sh") },
	{ MODKEY,							  XK_x,      						spawn,          SHCMD("poweropt-sh") },
   { 0,									  XF86XK_AudioRaiseVolume,    spawn,          SHCMD("volume-sh up") },
	{ 0,									  XF86XK_AudioLowerVolume,    spawn,          SHCMD("volume-sh down") },
   { 0,									  XF86XK_AudioMute,				spawn,          SHCMD("volume-sh mute") },
   { ControlMask,						  XK_Prior,							spawn,          SHCMD("backlight-sh up") },
   { ControlMask,						  XK_Next,         				spawn,          SHCMD("backlight-sh down") },
 
	{ MODKEY,                       XK_b,                       togglebar,      {0} },
	{ MODKEY,                       XK_j,                       focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,                       focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_i,                       incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_d,                       incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,                       setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,                       setmfact,       {.f = +0.05} },
	{ MODKEY,                       XK_Return,                  zoom,           {0} }, //swap master
	{ MODKEY,                       XK_Tab,                     view,           {0} }, //last tag
	{ MODKEY,							  XK_q,                       killclient,     {0} },
	{ MODKEY|ShiftMask,             XK_space,						   togglefloating, {0} },
	{ MODKEY,                       XK_0,      					   view,           {.ui = ~0 } }, //view all open apps
	TAGKEYS(                        XK_1,                       0)
	TAGKEYS(                        XK_2,                       1)
	TAGKEYS(                        XK_3,                       2)
	TAGKEYS(                        XK_4,                       3)
	TAGKEYS(                        XK_5,                       4)
	TAGKEYS(                        XK_6,                       5)
	TAGKEYS(                        XK_7,                       6)
	TAGKEYS(                        XK_8,                       7)
	TAGKEYS(                        XK_9,                       8)
	{ MODKEY|ShiftMask,             XK_q,      quit,            {0} }, //exit DWM
	{ MODKEY|ControlMask,           XK_m,      setlayout,      {.v = &layouts[0]} },
	//{ MODKEY|ControlMask,           XK_f,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY|ControlMask,           XK_f,      setlayout,      {.v = &layouts[2]} },
	//{ MODKEY,                       XK_space,  setlayout,      {0} },
	//{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	//{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	//{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
	//{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	//{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static const Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,					 Button1,        spawn,          SHCMD("pid=$(pidof dwm); kill -35 $pid; kill -36 $pid; kill -37 $pid; kill -36 $pid; kill -38 $pid; dunstify 'WTF' -t 90") },
	{ ClkWinTitle,          MODKEY,         Button1,        spawn,          SHCMD("poweropt-sh") },

	{ ClkStatusText,        0,              Button1,        sendstatusbar,   {.i = 1 } },
	{ ClkStatusText,        0,              Button2,        sendstatusbar,   {.i = 2 } },
	{ ClkStatusText,        0,              Button3,        sendstatusbar,   {.i = 3 } },
	{ ClkStatusText,        0,              Button4,        sendstatusbar,   {.i = 4 } },
	{ ClkStatusText,        0,              Button5,        sendstatusbar,   {.i = 5 } },
	{ ClkStatusText,        ShiftMask,      Button1,        sendstatusbar,   {.i = 6 } },

	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
};
