/* Taken from https://github.com/djpohly/dwl/issues/466 */
#define COLOR(hex)    { ((hex >> 24) & 0xFF) / 255.0f, \
                        ((hex >> 16) & 0xFF) / 255.0f, \
                        ((hex >> 8) & 0xFF) / 255.0f, \
                        (hex & 0xFF) / 255.0f }
/* appearance */
static const int sloppyfocus               = 1;  /* focus follows mouse */
static const int bypass_surface_visibility = 0;  /* 1 means idle inhibitors will disable idle tracking even if it's surface isn't visible  */
static const int smartgaps                 = 0;  /* 1 means no outer gap when there is only one window */
static const int monoclegaps               = 0;  /* 1 means outer gaps in monocle layout */
static const unsigned int borderpx         = 3;  /* border pixel of windows */
static const unsigned int gappih           = 10; /* horiz inner gap between windows */
static const unsigned int gappiv           = 10; /* vert inner gap between windows */
static const unsigned int gappoh           = 10; /* horiz outer gap between windows and screen edge */
static const unsigned int gappov           = 10; /* vert outer gap between windows and screen edge */
static const float rootcolor[]             = COLOR(0x222222ff);
static const float bordercolor[]           = COLOR(0x444444ff);
static const float focuscolor[]            = COLOR(0xff3584ff);
static const float urgentcolor[]           = COLOR(0xff0000ff);
/* This conforms to the xdg-protocol. Set the alpha to zero to restore the old behavior */
static const float fullscreen_bg[]         = {0.1f, 0.1f, 0.1f, 1.0f}; /* You can also use glsl colors */
static const char cursortheme[]            = "Adwaita"; /* theme from /usr/share/cursors/xorg-x11 */
static const unsigned int cursorsize       = 32;

/* bar */
static const int showbar        = 1; /* 0 means no bar */
static const int topbar         = 1; /* 0 means bottom bar */
static const char *fonts[]      = {"inter:style=Medium:size=16","Font Awesome 6 Free Solid,:size=16:weight=medium"};
static const char *fontattrs    = "dpi=108";
static pixman_color_t normbarfg = { 0xbbbb, 0xbbbb, 0xbbbb, 0xffff };
static pixman_color_t normbarbg = { 0x2222, 0x2222, 0x2222, 0xffff };
static pixman_color_t selbarfg  = { 0xeeee, 0xeeee, 0xeeee, 0xffff };
static pixman_color_t selbarbg  = { 0x3500, 0x8400, 0xe400, 0xffff };

/* tagging - TAGCOUNT must be no greater than 31 */
static char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

/* logging */
static int log_level = WLR_ERROR;

/* Autostart */
static const char *const autostart[] = {
        "setbg", NULL,
        "dunst", NULL,
        "mpris_listen", NULL,
        "systemctl", "--user", "import-environment", "WAYLAND_DISPLAY", "XDG_CURRENT_DESKTOP", NULL,
        "foot", "-s", NULL,
        "cherrytree",  NULL,
        "rnote", "Documents/japanese/kanj/kanji-practice.rnote", NULL,
        "foliate", "Documents/books/kanji_1.epub", NULL,
        NULL /* terminate */
};


static const Rule rules[] = {
	/* app_id                title      tags mask     isfloating   monitor */
	{ "foot",                NULL,      0,            0,          -1 },
	{ "lf",                  NULL,      0,            0,          -1 },
	{ "page.kramo.Cartridges", NULL,      0,            1,          -1 },
	{ "music",               NULL,      ~0,           0,           0 },
	{ "com.github.johnfactotum.Foliate", NULL, 0,     0,           0 },
};

/* layout(s) */
static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
	{ "@|@",      snail },
};

/* monitors */
/* NOTE: ALWAYS add a fallback rule, even if you are completely sure it won't be used */
static const MonitorRule monrules[] = {
	/* name       mfact nmaster scale layout       rotate/reflect              x  y  resx resy rate mode adaptive*/
	/* example of a HiDPI laptop monitor at 120Hz:
	{ "eDP-1",    0.5f,  1,      2,    &layouts[0], WL_OUTPUT_TRANSFORM_NORMAL, 0, 0, 0, 0, 120.000f, 1, 1},
	*/
	/* defaults */
	// { "DP-1",     0.5f, 1,      1,    &layouts[0], WL_OUTPUT_TRANSFORM_NORMAL, 1440,  750, 2560, 1440, 240.000f,  0, 0},
	{ "DP-1",     0.5f, 1,      1,    &layouts[0], WL_OUTPUT_TRANSFORM_NORMAL,-1,    -1,   2560, 1440, 240.000f,  0, 0},
	{ "DP-3",     0.5f, 0,      1,    &layouts[0], WL_OUTPUT_TRANSFORM_90,    -1,    -1,   1440, 2560, 144.000f,  1, 0},
	{ NULL,       0.5f, 1,      1,    &layouts[0], WL_OUTPUT_TRANSFORM_NORMAL, 0,     0,   0,    0,    0.0f,      0, 1},
	// mode let's the user decide on how dwl should implement the modes:
	// -1 Sets a custom mode following the users choice
	// All other number's set the mode at the index n, 0 is the standard mode; see wlr-randr
};

/* keyboard */
static const struct xkb_rule_names xkb_rules = {
	/* can specify fields: rules, model, layout, variant, options */
	/* example:
	.options = "ctrl:nocaps",
	*/
	.options = NULL,
};

static const int repeat_rate = 25;
static const int repeat_delay = 600;

/* Trackpad */
static const int tap_to_click = 1;
static const int tap_and_drag = 1;
static const int drag_lock = 1;
static const int natural_scrolling = 0;
static const int disable_while_typing = 1;
static const int left_handed = 0;
static const int middle_button_emulation = 0;
/* You can choose between:
LIBINPUT_CONFIG_SCROLL_NO_SCROLL
LIBINPUT_CONFIG_SCROLL_2FG
LIBINPUT_CONFIG_SCROLL_EDGE
LIBINPUT_CONFIG_SCROLL_ON_BUTTON_DOWN
*/
static const enum libinput_config_scroll_method scroll_method = LIBINPUT_CONFIG_SCROLL_2FG;

/* You can choose between:
LIBINPUT_CONFIG_CLICK_METHOD_NONE
LIBINPUT_CONFIG_CLICK_METHOD_BUTTON_AREAS
LIBINPUT_CONFIG_CLICK_METHOD_CLICKFINGER
*/
static const enum libinput_config_click_method click_method = LIBINPUT_CONFIG_CLICK_METHOD_BUTTON_AREAS;

/* You can choose between:
LIBINPUT_CONFIG_SEND_EVENTS_ENABLED
LIBINPUT_CONFIG_SEND_EVENTS_DISABLED
LIBINPUT_CONFIG_SEND_EVENTS_DISABLED_ON_EXTERNAL_MOUSE
*/
static const uint32_t send_events_mode = LIBINPUT_CONFIG_SEND_EVENTS_ENABLED;

/* You can choose between:
LIBINPUT_CONFIG_ACCEL_PROFILE_FLAT
LIBINPUT_CONFIG_ACCEL_PROFILE_ADAPTIVE
*/
static const enum libinput_config_accel_profile accel_profile = LIBINPUT_CONFIG_ACCEL_PROFILE_FLAT;
static const double accel_speed = 0.0;

/* You can choose between:
LIBINPUT_CONFIG_TAP_MAP_LRM -- 1/2/3 finger tap maps to left/right/middle
LIBINPUT_CONFIG_TAP_MAP_LMR -- 1/2/3 finger tap maps to left/middle/right
*/
static const enum libinput_config_tap_button_map button_map = LIBINPUT_CONFIG_TAP_MAP_LRM;

/* If you want to use the windows key for MODKEY, use WLR_MODIFIER_LOGO */
#define MODKEY WLR_MODIFIER_LOGO

#define TAGKEYS(KEY,SKEY,TAG) \
	{ MODKEY,                    KEY,            view,            {.ui = 1 << TAG} }, \
	{ MODKEY|WLR_MODIFIER_CTRL,  KEY,            toggleview,      {.ui = 1 << TAG} }, \
	{ MODKEY|WLR_MODIFIER_SHIFT, SKEY,           tag,             {.ui = 1 << TAG} }, \
	{ MODKEY|WLR_MODIFIER_CTRL|WLR_MODIFIER_SHIFT,SKEY,toggletag, {.ui = 1 << TAG} }

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static const char *leftBtn[] = { "toggle_mpv", NULL };
static const char *rightBtn[] = { "toggle_volume", NULL };
static const char *termcmd[] = { "foot", NULL };
static const char *menucmd[] = { "mymenu", NULL };
static const char *printcmd[]  = { "screenshot", NULL };
//static const char *passcmd[]  = { "passmenu", "-i", "--hb", "#98FB98", "--hf", "#222222",  NULL };
static const char *passcmd[]  = { "keepmenu", "-C", NULL };
static const char *plaympvcmd[]  = { "play", NULL };
static const char *playcmd[]  = { "playselect", NULL };
static const char *filescmd[]  = { "foot", "-e", "yazi", NULL };
static const char *powercmd[]  = { "power-menu", NULL };
static const char *musiccmd[]  = { "musicbox", NULL };
static const char *textcmd[]  = { "foot", "-e", "text-editor", NULL };
static const char *steamcmd[]  = { "cartridges", NULL };
static const char *guitext[]  = { "neovide", "--multigrid", NULL };
static const char *volcmd[]  = { "toggle_volume", NULL };
static const char *mpvcmd[]  = { "toggle_mpv", NULL };
static const char *raisecmd[]  = { "mpv_volume", ".05+", NULL };
static const char *lowercmd[]  = { "mpv_volume", ".05-", NULL };
static const char *mpv_next[]  = { "mpv_playlist", "+1", NULL };
static const char *mpv_prev[]  = { "mpv_playlist", "-1", NULL };
static const char *fuzzel[]  = { "fuzzel", NULL };
static const char *browser[]  = { "qutebrowser", NULL };
static const char *mpv[] = {"mpv",
                            "--force-window",
                            "--idle",
                            "--wayland-app-id=\"music\"",
                            "--ytdl-raw-options-append=cookies-from-browser=firefox:xvmub5tl.mxy-1700932099723",
                            "--script=/home/mxy/.local/share/git-repos/mpv-mpris/mpris.so",
                            "--script=/home/mxy/.local/share/git-repos/mpvSockets/mpvSockets.lua",
                            "--script-opts=dmenu-playlist-music_osc=true",
                            "--loop-file=no",
                            NULL};

static const Key keys[] = {
	/* Note that Shift changes certain key codes: c -> C, 2 -> at, etc. */
	/* modifier                  key                 function        argument */
	{ 0,           		           XKB_KEY_Scroll_Lock, spawn,         {.v = playcmd } },
	// { 0,                         XKB_KEY_Print,      spawn,          {.v = printcmd } },
	{ 0,           		           XKB_KEY_Pause,      spawn,          {.v = volcmd } },
	{ 0,           		           XKB_KEY_XF86AudioMute,spawn,        {.v = volcmd } },
	{ 0,           		           XKB_KEY_XF86AudioPlay,spawn,        {.v = mpvcmd } },
	{ 0,           		           XKB_KEY_XF86AudioLowerVolume,spawn, {.v = lowercmd } },
	{ 0,           		           XKB_KEY_XF86AudioRaiseVolume,spawn, {.v = raisecmd } },
	{ 0,           		           XKB_KEY_XF86AudioPrev,spawn,        {.v = mpv_prev } },
	{ 0,           		           XKB_KEY_XF86AudioNext,spawn,        {.v = mpv_next } },
	{ MODKEY,      		           0,                  spawn,          {.v = plaympvcmd } },
	{ MODKEY,      		           XKB_KEY_z,          spawn,          {.v = browser} },
	{ MODKEY,      		           XKB_KEY_x,          spawn,          {.v = mpv} },
	{ MODKEY,      		           XKB_KEY_Pause,      spawn,          {.v = plaympvcmd } },
	{ MODKEY|WLR_MODIFIER_SHIFT, XKB_KEY_Delete,     spawn,          {.v = powercmd } },
	{ MODKEY|WLR_MODIFIER_SHIFT, XKB_KEY_M,          spawn,          {.v = musiccmd } },
	{ MODKEY|WLR_MODIFIER_SHIFT, XKB_KEY_P,          spawn,          {.v = passcmd } },
	{ MODKEY,                    XKB_KEY_e,          spawn,          {.v = filescmd } },
	{ MODKEY,                    XKB_KEY_v,          spawn,          {.v = textcmd } },
	{ MODKEY|WLR_MODIFIER_SHIFT, XKB_KEY_V,          spawn,          {.v = guitext } },
	{ MODKEY,                    XKB_KEY_s,          spawn,          {.v = steamcmd } },
	{ MODKEY,                    XKB_KEY_p,          spawn,          {.v = fuzzel } },
	{ WLR_MODIFIER_ALT,          XKB_KEY_p,          spawn,          {.v = menucmd} },
	{ MODKEY|WLR_MODIFIER_SHIFT, XKB_KEY_Return,     spawn,          {.v = termcmd} },
	{ 0,                         XKB_KEY_Print,      regions,        SHCMD("screenshot") },
	{ MODKEY,                    XKB_KEY_b,          togglebar,      {0} },
	{ MODKEY,                    XKB_KEY_j,          focusstack,     {.i = +1} },
	{ MODKEY,                    XKB_KEY_k,          focusstack,     {.i = -1} },
	{ MODKEY|WLR_MODIFIER_SHIFT, XKB_KEY_J,          pushdown,       {0} },
	{ MODKEY|WLR_MODIFIER_SHIFT, XKB_KEY_K,          pushup,         {0} },
	{ MODKEY,                    XKB_KEY_i,          incnmaster,     {.i = +1} },
	{ MODKEY,                    XKB_KEY_d,          incnmaster,     {.i = -1} },
	{ MODKEY,                    XKB_KEY_h,          setmfact,       {.f = -0.05f} },
	{ MODKEY,                    XKB_KEY_l,          setmfact,       {.f = +0.05f} },
	{ MODKEY,                    XKB_KEY_equal,      incgaps,        {.i = +5 } },
	{ MODKEY,                    XKB_KEY_minus,      incgaps,        {.i = -5 } },
	{ MODKEY|WLR_MODIFIER_SHIFT, XKB_KEY_plus,       togglegaps,     {0} },
	{ MODKEY,                    XKB_KEY_Return,     zoom,           {0} },
	{ MODKEY,                    XKB_KEY_Tab,        view,           {0} },
	{ MODKEY|WLR_MODIFIER_SHIFT, XKB_KEY_C,          killclient,     {0} },
	{ MODKEY,                    XKB_KEY_t,          setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                    XKB_KEY_f,          setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                    XKB_KEY_m,          setlayout,      {.v = &layouts[2]} },
	{ MODKEY,                    XKB_KEY_r,          setlayout,      {.v = &layouts[3]} },
	{ MODKEY,                    XKB_KEY_space,      setlayout,      {0} },
	{ MODKEY|WLR_MODIFIER_SHIFT, XKB_KEY_space,      togglefloating, {0} },
	{ MODKEY|WLR_MODIFIER_SHIFT, XKB_KEY_F,          togglefullscreen, {0} },
	{ MODKEY,                    XKB_KEY_0,          view,           {.ui = ~0} },
	{ MODKEY|WLR_MODIFIER_SHIFT, XKB_KEY_parenright, tag,            {.ui = ~0} },
	{ MODKEY,                    XKB_KEY_comma,      focusmon,       {.i = WLR_DIRECTION_LEFT} },
	{ MODKEY,                    XKB_KEY_period,     focusmon,       {.i = WLR_DIRECTION_RIGHT} },
	{ MODKEY|WLR_MODIFIER_SHIFT, XKB_KEY_less,       tagmon,         {.i = WLR_DIRECTION_LEFT} },
	{ MODKEY|WLR_MODIFIER_SHIFT, XKB_KEY_greater,    tagmon,         {.i = WLR_DIRECTION_RIGHT} },
	TAGKEYS(          XKB_KEY_1, XKB_KEY_exclam,                     0),
	TAGKEYS(          XKB_KEY_2, XKB_KEY_at,                         1),
	TAGKEYS(          XKB_KEY_3, XKB_KEY_numbersign,                 2),
	TAGKEYS(          XKB_KEY_4, XKB_KEY_dollar,                     3),
	TAGKEYS(          XKB_KEY_5, XKB_KEY_percent,                    4),
	TAGKEYS(          XKB_KEY_6, XKB_KEY_asciicircum,                5),
	TAGKEYS(          XKB_KEY_7, XKB_KEY_ampersand,                  6),
	TAGKEYS(          XKB_KEY_8, XKB_KEY_asterisk,                   7),
	TAGKEYS(          XKB_KEY_9, XKB_KEY_parenleft,                  8),
	{ MODKEY|WLR_MODIFIER_SHIFT, XKB_KEY_Q,          quit,           {0} },

	/* Ctrl-Alt-Backspace and Ctrl-Alt-Fx used to be handled by X server */
	{ WLR_MODIFIER_CTRL|WLR_MODIFIER_ALT,XKB_KEY_Terminate_Server, quit, {0} },
	/* Ctrl-Alt-Fx is used to switch to another VT, if you don't know what a VT is
	 * do not remove them.
	 */
#define CHVT(n) { WLR_MODIFIER_CTRL|WLR_MODIFIER_ALT,XKB_KEY_XF86Switch_VT_##n, chvt, {.ui = (n)} }
	CHVT(1), CHVT(2), CHVT(3), CHVT(4), CHVT(5), CHVT(6),
	CHVT(7), CHVT(8), CHVT(9), CHVT(10), CHVT(11), CHVT(12),
};

static const Button buttons[] = {
	{ ClkLtSymbol, 0,      BTN_LEFT,   setlayout,      {.v = &layouts[0]} },
	{ ClkLtSymbol, 0,      BTN_RIGHT,  setlayout,      {.v = &layouts[2]} },
	{ ClkTitle,    0,      BTN_MIDDLE, zoom,           {0} },
	{ ClkStatus,   0,      BTN_MIDDLE, spawn,          {.v = termcmd} },
	{ ClkStatus,   0,      BTN_LEFT,   spawn,          {.v = leftBtn} },
	{ ClkStatus,   0,      BTN_RIGHT,  spawn,          {.v = rightBtn} },
	{ ClkClient,   MODKEY, BTN_LEFT,   moveresize,     {.ui = CurMove} },
	{ ClkClient,   MODKEY, BTN_MIDDLE, togglefloating, {0} },
	{ ClkClient,   MODKEY, BTN_RIGHT,  moveresize,     {.ui = CurResize} },
	{ ClkTagBar,   0,      BTN_LEFT,   view,           {0} },
	{ ClkTagBar,   0,      BTN_RIGHT,  toggleview,     {0} },
	{ ClkTagBar,   MODKEY, BTN_LEFT,   tag,            {0} },
	{ ClkTagBar,   MODKEY, BTN_RIGHT,  toggletag,      {0} },
};
