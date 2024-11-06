/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 1;      /* border pixel of windows */
static const unsigned int snap      = 26;       /* snap pixel */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
//static const char *fonts[]          = { "NBP Informa FiveSix:size=14:style=Regular", "NotoColorEmoji:pixelsize=16:antialias=true:autohint=true" };
//static const char *fonts[]          = { "JetBrains Mono NL:size=10:style=Bold", "NotoColorEmoji:pixelsize=16:antialias=true:autohint=true" };
static const char *fonts[]          = { "JetBrainsMonoNL NFM SemiBold:size=10:style=SemiBold,Regular", "NotoColorEmoji:pixelsize=16:antialias=true:autohint=true" };
//static const char dmenufont[]       = { "JetBrains Mono NL:size=16:style=Bold:pixelsize=16:antialias=true:autohint=true" };
static const char dmenufont[]       = { "NBP Informa FiveSix:size=25:style=Regular:pixelsize=25:antialias=true:autohint=true" };

static const char normbordercolor[]           = "#000000"; /*black*/
static const char selbordercolor[]            = "#ededed"; /*white*/
static const char normbgcolor[]               = "#b6b6b6"; /*grey*/
static const char normfgcolor[]               = "#000000"; /*black*/
static const char selbgcolor[]                = "#ededed"; /*white*/
static const char selfgcolor[]                = "#000000"; /*black*/

//static const char normbordercolor[]           = "#11ee06"; /*green*/
//static const char normbgcolor[]               = "#0861f9"; /*blue*/
//static const char normfgcolor[]               = "#f9f808"; /*yellow*/
//static const char selbordercolor[]            = "#ededed"; /*white*/
//static const char selbgcolor[]                = "#ededed"; /*white*/
//static const char selfgcolor[]                = "#e61b1b"; /*red*/

//static const char normbordercolor[]           = "#3B4252";
//static const char normbgcolor[]               = "#2E3440";
//static const char normfgcolor[]               = "#D8DEE9";
//static const char selbordercolor[]            = "#434C5E";
//static const char selbgcolor[]                = "#434C5E";
//static const char selfgcolor[]                = "#ECEFF4";

static const char *colors[][3] = {
    /*               fg           bg           border   */
    [SchemeNorm] = { normfgcolor, normbgcolor, normbordercolor },
    [SchemeSel]  = { selfgcolor,  selbgcolor,  selbordercolor },
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5" };
//static const char *tags[] = { "一", "二", "三", "四", "五" };
//static const char *tags[] = { "", "", "", "", "󰊖" };

static const Rule rules[] = {
	/* class           instance    title       tags mask     isfloating   monitor */
	{ "alacritty",     NULL,       NULL,       0,            0,           -1 },
	{ "firefox",       NULL,       NULL,       1 << 1,       0,           -1 },
	{ "libreoffice",   NULL,       NULL,       1 << 2,       0,           -1 },
	{ "Thunar",        NULL,       NULL,       0,            1,           -1 },
	{ "pavucontrol",   NULL,       NULL,       0,			 1,           -1 },
};

/* layout(s) */
static const float mfact     = 0.6; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 0;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */

static const Layout layouts[] = {
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
static char dmenumon[2]       = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", normbgcolor, "-nf", normfgcolor, "-sb", selbgcolor, "-sf", selfgcolor, NULL };
static const char *termcmd[]  = { "alacritty", NULL };
static const char *browser[]  = { "firefox", NULL };
static const char *thunar[]   = { "thunar", NULL };
static const char *ping[]     = { "pgtest-sh", NULL };
static const char *power[]    = { "poweropt-sh", NULL };

static const Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY,                       XK_s,      spawn,          {.v = dmenucmd } },
	{ MODKEY|ControlMask,           XK_p,      spawn,          {.v = ping } },
	{ MODKEY,						XK_x,      spawn,          {.v = power} },
	{ MODKEY|ShiftMask,             XK_Return, spawn,          {.v = termcmd } },
	{ MODKEY,                       XK_e,      spawn,          {.v = thunar } },
    { MODKEY,                       XK_f,      spawn,          {.v = browser } },
	{ MODKEY,                       XK_b,      togglebar,      {0} },
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_d,      incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
	{ MODKEY,                       XK_Return, zoom,           {0} },
	{ MODKEY,                       XK_Tab,    view,           {0} },
	{ MODKEY|ShiftMask,             XK_c,      killclient,     {0} },
	//{ MODKEY|ControlMask,           XK_t,      setlayout,      {.v = &layouts[0]} },
	//{ MODKEY|ControlMask,           XK_f,      setlayout,      {.v = &layouts[1]} },
	//{ MODKEY|ControlMask,           XK_m,      setlayout,      {.v = &layouts[2]} },
	//{ MODKEY,                       XK_space,  setlayout,      {0} },
	{ MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	//{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	//{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	//{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
	//{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	//{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	{ MODKEY|ShiftMask,             XK_q,      quit,           {0} },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static const Button buttons[] = {
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

