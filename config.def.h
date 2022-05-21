/* See LICENSE file for copyright and license details. */

#include <X11/XF86keysym.h>

/* appearance */
static const char kblayouts[3][3]   = {"it", "dk", "us"}; /* configured keyboard layouts */
static const unsigned int borderpx  = 1;        /* border pixel of windows */
static const unsigned int gappx     = 5;        /* gaps between windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const unsigned int systraypinning = 0;   /* 0: sloppy systray follows selected monitor, >0: pin systray to monitor X */
static const unsigned int systrayspacing = 2;   /* systray spacing */
static const int systraypinningfailfirst = 1;   /* 1: if pinning fails, display systray on the first monitor, False: display systray on the last monitor*/
static const int showsystray        = 1;     /* 0 means no systray */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const char *fonts[]          = { "monospace:size=10" };
static const char dmenufont[]       = "monospace:size=10";
static const char col_gray1[]       = "#222222";
static const char col_gray2[]       = "#444444";
static const char col_gray3[]       = "#bbbbbb";
static const char col_gray4[]       = "#eeeeee";
static const char col_cyan[]        = "#005577";
static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_gray3, col_gray1, col_gray2 },
	[SchemeInv]  = { col_gray1, col_gray3, col_gray2 },
	[SchemeSel]  = { col_gray4, col_cyan,  col_cyan  },
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title       tags mask     isfloating   monitor */
	{ "Gimp",     NULL,       NULL,       0,            1,           -1 },
	{ "Calculator",     NULL,       NULL,       0,            1,           -1 },
	/* { "Firefox",  NULL,       NULL,       1 << 8,       0,           -1 }, */
};

/* layout(s) */
static const float mfact     = 0.50; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
};

/*
 * --- TAG KEYS ---
 *  Mod + n => view windows with tag n (aka view workspace n)
 *  Mod + Shift + n => apply n tag to focused window (move window to workspace n)
 *  Mod + Ctrl + n => add/remove all windows with tag n from/to view (show tag n on current tag)
 *  Mod + Ctrl + Shift + n => add remove n tag to/from focused window (tag current vindow with a secondary tag n)
 *  Mod + Alt + n => move focused window on tag n on the next monitor
 *  Mod + Alt + Shift +n => move focused window on tag n on the previous monitor 
 */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} }, \
	{ MODKEY|Mod1Mask,              KEY,      tagnextmon,     {.ui = 1 << TAG} }, \
	{ MODKEY|Mod1Mask|ShiftMask,    KEY,      tagprevmon,     {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_gray1, "-nf", col_gray3, "-sb", col_cyan, "-sf", col_gray4, NULL };
static const char *termcmd[]  = { "st", NULL };
static const char *browsercmd[]  = { "firefox", NULL };
static const char *passcmd[]  = { "keepass", NULL };
static const char *emailcmd[]  = { "thunderbird", NULL };
/* static const char *filemanagercmd[]  = { "st", "-e", "ranger", NULL }; */
static const char *filemanagercmd[]  = { "thunar", NULL };
static const char *musicplayercmd[]  = { "st", "-e", "cmus", NULL };
static const char *calendarcmd[]  = { "st", "-e", "calcurse", NULL };
static const char *calccmd[]  = { "gnome-calculator", NULL };
static const char *guiappmenucmd[]  = { "xfce4-appfinder", NULL };

// System Scripts/Commands
static const char *sessmngrscript[]  = { "/home/elendil/bin/dmenu_session_manager", NULL };
static const char *lockscript[]  = { "/home/elendil/bin/lock_screen.sh", NULL };
static const char *screenshotscript[]  = { "/home/elendil/bin/screenshot.sh", NULL };
static const char *screenshotareascript[]  = { "/home/elendil/bin/screenshot_select.sh", NULL };
static const char *mutecmd[] = { "amixer", "-q", "set", "Master", "toggle", NULL };
static const char *volupcmd[] = { "amixer", "-q", "set", "Master", "5%+", "unmute", NULL };
static const char *voldowncmd[] = { "amixer", "-q", "set", "Master", "5%-", "unmute", NULL };
/* static const char *miccmd[] = { "amixer", "set", "Capture", "toggle", NULL }; */
static const char *brightupcmd[] = { "st", "-e", "light", "-A", "10", NULL };
static const char *brightdowncmd[] = { "st", "-e", "light", "-U", "10", NULL };


static Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY,                       XK_r,      spawn,          {.v = dmenucmd } },  // Open dmenu
	{ MODKEY,                       XK_Return, spawn,          {.v = termcmd } },   // Open terminal
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },        // Focus window down in the stack
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },        // Focus window up in the stack
	{ MODKEY|ShiftMask,             XK_j,      rotatestack,    {.i = +1 } },        // Move window down in the stack
	{ MODKEY|ShiftMask,             XK_k,      rotatestack,    {.i = -1 } },        // Move window up in the stack
	{ MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },        // Increase nr of windows in master area
	{ MODKEY,                       XK_d,      incnmaster,     {.i = -1 } },        // Ddecrease number of windows in master area
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },      // Make Master smaller
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },      // Make Master bigger
	{ MODKEY|ShiftMask,             XK_space,  zoom,           {0} },               // Set focused window as Master
	{ MODKEY|ShiftMask,             XK_Tab,    view,           {0} },               // Toggle to the previously focused tag
	{ MODKEY,                       XK_w,      killclient,     {0} },               // Close focused window
	{ MODKEY,                       XK_Tab,    setlayout,      {0} },               // Cycle layouts
    	{ MODKEY|ShiftMask,             XK_t,      togglefloating, {0} },                   // Toggle floating for the focused window
 	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },       // view all windows with any tag (view all windows on all tags at once)
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },       // apply all tags to focused window (so that it shows on any tag)
	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },        // Focus previous monitor
	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },        // Focus next monitor
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },        // Send focused window to previous monitor
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },        // Send focused window to next monitor
	{ MODKEY,                       XK_F5,     xrdb,           {.v = NULL } },
	{ MODKEY|ControlMask,           XK_minus,  setgaps,        {.i = -1 } },        // Make gaps smaller
	{ MODKEY|ControlMask,           XK_plus,   setgaps,        {.i = +1 } },        // Make gaps bigger
	{ MODKEY|ControlMask,           XK_equal,  setgaps,        {.i = 0  } },        // Reset gaps
	{ MODKEY|ControlMask,           XK_q,      quit,           {0} },               // Quit DWM
    	{ MODKEY|ControlMask,           XK_r,      self_restart,   {0} },               // Restart DWM
    	{ MODKEY|ControlMask,           XK_space,  change_layout,  {0} },               // Change keyboard layout
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	{ MODKEY,             XK_b, spawn,          {.v = browsercmd } },
	{ MODKEY,             XK_p, spawn,          {.v = passcmd } },
	{ MODKEY,             XK_e, spawn,          {.v = emailcmd } },
	{ MODKEY,             XK_f, spawn,          {.v = filemanagercmd } },
	{ MODKEY,             XK_m, spawn,          {.v = musicplayercmd } },
	{ MODKEY,             XK_c, spawn,          {.v = calendarcmd } },
	{ MODKEY|ShiftMask,             XK_c, spawn,          {.v = calccmd } },
	{ MODKEY|ShiftMask,             XK_r, spawn,          {.v = guiappmenucmd } },
	{ MODKEY|ControlMask, XK_x, spawn,           {.v = sessmngrscript } },
	{ MODKEY|ControlMask, XK_l, spawn,           {.v = lockscript } },
	{ 0,                  XK_Print, spawn,           {.v = screenshotscript } },
	{ MODKEY,             XK_Print, spawn,           {.v = screenshotareascript } },
    { 0,    XF86XK_AudioMute, spawn, {.v = mutecmd } },
    { 0, XF86XK_AudioLowerVolume, spawn, {.v = voldowncmd } },
    { 0, XF86XK_AudioRaiseVolume, spawn, {.v = volupcmd } },
    { 0, XF86XK_MonBrightnessUp, spawn, {.v = brightupcmd} },
    { 0, XF86XK_MonBrightnessDown, spawn, {.v = brightdowncmd} },
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

