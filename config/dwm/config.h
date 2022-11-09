/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 1;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const unsigned int systraypinning = 0;   /* 0: sloppy systray follows selected monitor, >0: pin systray to monitor X */
static const unsigned int systrayonleft = 0;   	/* 0: systray in the right corner, >0: systray on left of status text */
static const unsigned int systrayspacing = 2;   /* systray spacing */
static const int systraypinningfailfirst = 1;   /* 1: if pinning fails, display systray on the first monitor, False: display systray on the last monitor*/
static const int showsystray        = 1;     /* 0 means no systray */
static const int showbar            = 1;     /* 0 means no bar */
static const int topbar             = 1;     /* 0 means bottom bar */
static const int focusonwheel       = 0;
static const char *fonts[]          = { "JetbrainsMono NF:size=10" };
static const char dmenufont[]       = "JetbrainsMono NF:size=10";
static const char col_gray1[]       = "#222222";
static const char col_gray2[]       = "#444444";
static const char col_gray3[]       = "#bbbbbb";
static const char col_gray4[]       = "#eeeeee";
static const char col_cyan[]        = "#75289e";
static const char col_sel[]         = "#dfeb36";
static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_gray3, col_gray1, col_gray2 },
	[SchemeSel]  = { col_gray4, col_cyan,  col_sel   },
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      	     instance    title    tags mask     isfloating   CenterThisWindow?     monitor    scratchkey*/
	{ "st",              NULL,       NULL,    0,            0,     	     1,		                 -1,     0  },
	{ "alacritty",       NULL,       NULL,    0,            0,     	     1,		                 -1,     0  },
	{ "Gimp",            NULL,       NULL,    0,            1,           0,                    -1,     0  },
	{ "Firefox",         NULL,       NULL,    1 << 8,       0,           0,                    -1,     0  },
	{ NULL,              NULL,  "scratchpad", 0,            1,           1,                    -1,    's' },
};

/* layout(s) */
static const float mfact     = 0.52; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */

#include "layouts.c"
static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[D]",      deck },
	{ "[M]",      monocle },
	{ "[]=",      tile },    /* first entry is default */
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "HHH",      grid },
};

/* key definitions */
#define MODKEY Mod1Mask
#define SUPKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_gray1, "-nf", col_gray3, "-sb", col_cyan, "-sf", col_gray4, NULL };
static const char *termcmd[]  = { "alacritty", NULL };
// monitor brightness
static const char *brinc[] = { "sudo", "light", "-A", "5", NULL };
static const char *brdec[] = { "sudo", "light", "-U", "5", NULL };
// volume control
static const char *vlinc[] = { "pactl", "set-sink-volume", "@DEFAULT_SINK@", "+5%", NULL };
static const char *vldec[] = { "pactl", "set-sink-volume", "@DEFAULT_SINK@", "-5%", NULL };
static const char *mute[] = { "pactl", "set-sink-mute", "@DEFAULT_SINK@", "toggle", NULL };
// applications
static const char *firefox[] = { "firefox", NULL };
static const char *chromium[] = { "chromium", NULL };
static const char *telegram[] = { "telegram-desktop", NULL };
static const char *editor[] = { "alacritty", "-e", "nvim", NULL };
static const char *kdocker[] = { "kdocker", NULL };
static const char *pcmanfm[] = { "pcmanfm", NULL };
static const char *lock[] = { "i3lock", "-c", "000000", NULL };
// screen setup
static const char *over[] = { "xrandr", "--output", "eDP-1", "--mode", "1920x1080", "--pos", "0x1080", "--rotate", "normal", "--output", "HDMI-1", "--primary", "--mode", "1920x1080", "--pos", "0x0", "--rotate", "normal", NULL };
static const char *left[] = { "xrandr", "--output", "eDP-1", "--mode", "1920x1080", "--pos", "1920x0", "--rotate", "normal", "--output", "HDMI-1", "--primary", "--mode", "1920x1080", "--pos", "0x0", "--rotate", "normal", NULL };
static const char *right[] = { "xrandr", "--output", "eDP-1", "--mode", "1920x1080", "--pos", "0x0", "--rotate", "normal", "--output", "HDMI-1", "--primary", "--mode", "1920x1080", "--pos", "1920x0", "--rotate", "normal", NULL }; 
static const char *duplicate[] = { "xrandr", "--output", "eDP-1", "--mode", "1920x1080", "--pos", "0x0", "--rotate", "normal", "--output", "HDMI-1", "--primary", "--mode", "1920x1080", "--pos", "0x0", "--rotate", "normal", NULL }; 
static const char *desktop[] = { "xrandr", "--output", "eDP-1", "--mode", "1920x1080", "--pos", "0x0", "--rotate", "normal", "--output", "HDMI-1", "--off", NULL }; 
static const char *monitor[] = { "xrandr", "--output", "eDP-1", "--off", "--output", "HDMI-1", "--primary", "--mode", "1920x1080", "--pos", "0x0", "--rotate", "normal", NULL }; 

#include <X11/XF86keysym.h>
static const Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY,                       XK_d,      spawn,          {.v = dmenucmd } },
	{ MODKEY,                       XK_Return, spawn,          {.v = termcmd } },
	{ MODKEY,                       XK_b,      togglebar,      {0} },
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.02} },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.02} },
	{ MODKEY|ShiftMask,             XK_Return, zoom,           {0} },
	{ MODKEY,                       XK_q,      killclient,     {0} },
	{ MODKEY|ShiftMask,             XK_q,      killclient,     {0} },
	{ MODKEY,                       XK_r,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       XK_m,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[2]} },
	{ MODKEY,                       XK_f,      setlayout,      {.v = &layouts[3]} },
	{ MODKEY,                       XK_g,      setlayout,      {.v = &layouts[4]} },
	{ MODKEY,                       XK_space,  setlayout,      {0} },
	{ MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	{ MODKEY|ShiftMask,             XK_e,      quit,           {0} },
  { 0,             XF86XK_AudioLowerVolume,  spawn,          {.v = vldec } },
  { 0,             XF86XK_AudioRaiseVolume,   spawn,          {.v = vlinc } },
  { 0,             XF86XK_AudioMute,         spawn,          {.v = mute } },
  { 0,             XF86XK_MonBrightnessDown, spawn,          {.v = brdec } },
  { 0,             XF86XK_MonBrightnessUp,   spawn,          {.v = brinc } },
  { MODKEY,                       XK_c,      spawn,          {.v = chromium } },
  { MODKEY,                       XK_w,      spawn,          {.v = firefox } },
  { MODKEY|ShiftMask,             XK_f,      spawn,          {.v = pcmanfm } },
  { SUPKEY,                       XK_d,      spawn,          {.v = kdocker } },
  { MODKEY|ShiftMask,             XK_t,      spawn,          {.v = telegram } },
  { MODKEY,                       XK_v,      spawn,          {.v = editor } },
  { SUPKEY,                       XK_o,      spawn,          {.v = over } },
  { SUPKEY,                       XK_l,      spawn,          {.v = right } },
  { SUPKEY,                       XK_h,      spawn,          {.v = left } },
  { SUPKEY,                       XK_s,      spawn,          {.v = duplicate } },
  { SUPKEY,                       XK_p,      spawn,          {.v = desktop } },
  { SUPKEY,                       XK_m,      spawn,          {.v = monitor } },
  { MODKEY|ShiftMask,             XK_x,      spawn,          {.v = lock } },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static const Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
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

