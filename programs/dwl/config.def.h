/* appearance */
static const int sloppyfocus               = 1;  /* focus follows mouse */
static const int bypass_surface_visibility = 0;  /* 1 means idle inhibitors will disable idle tracking even if it's surface isn't visible  */
static const int smartgaps                 = 0;  /* 1 means no outer gap when there is only one window */
static const unsigned int borderpx         = 2;  /* border pixel of windows */
static const unsigned int gappx            = 10; /* horiz inner gap between windows */
static const float bordercolor[]           = {0.902, 0.596, 0.459, 1.0}; // #e69875
static const float focuscolor[]            = {0.655, 0.753, 0.502, 1.0}; // #a7c080
static const float urgentcolor[]           = {0.902, 0.494, 0.502, 1.0};
static const float floatcolor[]						 = {0.859, 0.737, 0.498, 1.0};
/* To conform the xdg-protocol, set the alpha to zero to restore the old behavior */
static const float fullscreen_bg[]         = {0.118,0.137,0.149, 1.0}; // #1e2326
static const char cursortheme[]            = "$HOME/.local/share/themes/Everforest-Dark/"; /* theme from /usr/share/cursors/xorg-x11 */
static const unsigned int cursorsize       = 14;
// static const int center_relative_to_monitor = 0; /* 0 means center floating relative to the window area */

/* tagging */
// static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9"};

static const char *const autostart[] = {
	"someblocks", NULL,
	"pipewire", "&", "wireplumber", NULL,
	"swaybg", "-i", "/home/capim/images/wallpapers/everforest/guts.png", NULL, // CHANGE THIS TO MATCH YOUR USER NAME!
	"gsettings", "set", "org.gnome.desktop.interface", "gtk-theme", "'Everforest-Dark'", NULL,
	"gsettings", "set", "org.gnome.desktop.interface", "icon-theme", "'Everforest-Dark-Icons'", NULL,
	"gsettings", "set", "org.gnome.desktop.interface", "cursor-size", "14", NULL,
	"gsettings", "set", "org.gnome.desktop.interface", "cursor-theme", "Everforest-Cursor", NULL,
	"gsettings", "set", "org.gnome.desktop.interface", "font-name", "scientifica 9", NULL,
	"gsettings", "set", "org.gnome.desktop.interface", "document-font-name", "scientifica 9", NULL,
	"gsettings", "set", "org.gnome.desktop.interface", "monospace-font-name", "scientifica 9", NULL,
	"dbus-update-activation-environment", "--all", NULL,
};

/* tagging - TAGCOUNT must be no greater than 31 */
#define TAGCOUNT (9)

/* logging */
static int log_level = WLR_ERROR;

static const Rule rules[] = {
	/* app_id     title       tags mask     isfloating   monitor */
 	/* examples:
	{ "gimp",     null,       0,            1,           -1 },
 	*/
	{ "thall",  NULL,       1 << 8,       0,           -1 },
};

/* layout(s) */
static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
};

/* monitors */
static const MonitorRule monrules[] = {
	/* name       mfact nmaster scale layout       rotate/reflect                x    y */
	/* example of a HiDPI laptop monitor:
	{ "eDP-1",    0.5,  1,      2,    &layouts[0], WL_OUTPUT_TRANSFORM_NORMAL,   -1,  -1 },
	*/
	/* defaults */
	{ NULL,       0.55, 1,      1,    &layouts[0], WL_OUTPUT_TRANSFORM_NORMAL,   -1,  -1 },
};

/* keyboard */
static const struct xkb_rule_names xkb_rules = {
	/* can specify fields: rules, model, layout, variant, options */
	/* example:
	.options = "ctrl:nocaps",
	*/
	.layout = "br",
};

static const int repeat_rate = 40;
static const int repeat_delay = 300;

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
static const enum libinput_config_accel_profile accel_profile = LIBINPUT_CONFIG_ACCEL_PROFILE_ADAPTIVE;
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
static const char *termcmd[] = { "foot", NULL };
static const char *togglebar[] = { "somebar", "-c", "toggle", "all", NULL };

// PRINTING

// grim -g "$(slurp)" - | swappy  -f -
static const char *grabscreen[] =    { "grim", "-g", "\"$(slurp)\"", "-", "|", "swappy",  "-f", "-", NULL };
// grim - | swappy -f -
static const char *printscreen[] =   { "grim", "-", "|", "swappy", "-f", "-", NULL };

// WEB
static const char *browser[] =    { "librewolf", NULL };

// EDITING
// static const char *inkscape[] =   { "inkscape", NULL };
// static const char *gimp[] =       { "gimp", NULL };

// BRIGHTNESS
static const char *raise_brightness[] = { "getbrightness", "raise", "1", NULL};
static const char *lower_brightness[] = { "getbrightness", "lower", "1", NULL};

// AUDIO
static const char *raise_volume[] =       { "getvolume", "raise", NULL };
static const char *lower_volume[] =       { "getvolume", "lower", NULL };
static const char *mute_volume[]  =       { "getvolume", "mute", NULL };
    // MICROPHONE	
	static const char *raise_mic_volume[] =       { "getvolume", "raise_mic", NULL };
	static const char *lower_mic_volume[] =       { "getvolume", "lower_mic", NULL };
	static const char *mute_mic_volume[] =        { "getvolume", "mute_mic", NULL };
	    // PROGRAMS
		static const char *pulsemixer[] =		{ "foot", "-e", "pulsemixer", NULL };

// MUSIC
static const char *nextsong[] =   { "mpc", "next", NULL };
static const char *prevsong[] =   { "mpc", "prev", NULL };
static const char *togglesong[] = { "mpc", "toggle", NULL };
static const char *clearsong[] =  { "mpc", "clear", NULL };
static const char *ncmpcpp[] =    { "foot", "-e", "ncmpcpp", NULL };


static const Key keys[] = {
	/* Note that Shift changes certain key codes: c -> C, 2 -> at, etc. */
	/* modifier                  key                 function        argument */
	{ MODKEY,                    XKB_KEY_d,          spawn,           SHCMD("tofi-run | dash")  },
	{ MODKEY|WLR_MODIFIER_SHIFT, XKB_KEY_T,          spawn,           SHCMD("notify-send \"$(date)\" ")  },
	{ MODKEY,		    						 XKB_KEY_Return,     spawn,          {.v = termcmd} },

	// WEB
	    { MODKEY,                    XKB_KEY_b,          spawn,          {.v = browser} },

	// BRIGHTNESS
	    { MODKEY,                    XKB_KEY_F9,          spawn,          {.v = raise_brightness} },
	    { MODKEY,                    XKB_KEY_F8,          spawn,          {.v = lower_brightness} },

	// AUDIO
	    { MODKEY,                    XKB_KEY_s,            spawn,          {.v = pulsemixer} },
	    { MODKEY,                    XKB_KEY_F12,          spawn,          {.v = raise_volume} },
	    { MODKEY,                    XKB_KEY_F11,          spawn,          {.v = lower_volume} },
	    { MODKEY,                    XKB_KEY_F10,          spawn,          {.v = mute_volume} },
	    /// MICROPHONE
		{ MODKEY|WLR_MODIFIER_SHIFT,                    XKB_KEY_F12,          spawn,          {.v = raise_mic_volume} },
		{ MODKEY|WLR_MODIFIER_SHIFT,                    XKB_KEY_F11,          spawn,          {.v = lower_mic_volume} },
		{ MODKEY|WLR_MODIFIER_SHIFT,                    XKB_KEY_F10,          spawn,          {.v = mute_mic_volume} },

	// MUSIC
	     { MODKEY,                    XKB_KEY_n,           spawn,           {.v = ncmpcpp} },
	     { MODKEY,                    XKB_KEY_c,           spawn,           {.v = clearsong} },
	     { MODKEY,                    XKB_KEY_F3,          spawn,          {.v = nextsong} },
	     { MODKEY,                    XKB_KEY_F2,          spawn,          {.v = togglesong} },
	     { MODKEY,                    XKB_KEY_F1,          spawn,          {.v = prevsong} },

	// IMAGE MANIPULATION
	    // { MODKEY|WLR_MODIFIER_SHIFT, XKB_KEY_I,          spawn,          {.v = inkscape} },
	    // { MODKEY|WLR_MODIFIER_SHIFT, XKB_KEY_G,          spawn,          {.v = gimp} },

	// PRINTING
	    { MODKEY,                    XKB_KEY_p,          spawn,          {.v = grabscreen} },
	    { MODKEY|WLR_MODIFIER_SHIFT, XKB_KEY_P,          spawn,          {.v = printscreen} },

	// SYSTEM
	{ MODKEY,                    XKB_KEY_g,          togglegaps,     {0} },
	{ MODKEY|WLR_MODIFIER_SHIFT, XKB_KEY_G,          spawn,          {.v = togglebar } },
	{ MODKEY,										 XKB_KEY_q,          killclient,     {0} },
	{ MODKEY|WLR_MODIFIER_SHIFT, XKB_KEY_Q,          quit,           {0} },

	{ MODKEY,                    XKB_KEY_j,          focusstack,     {.i = +1} },
	{ MODKEY,                    XKB_KEY_k,          focusstack,     {.i = -1} },
	{ MODKEY,                    XKB_KEY_i,          incnmaster,     {.i = +1} },
	{ MODKEY,                    XKB_KEY_u,          incnmaster,     {.i = -1} },
	{ MODKEY,                    XKB_KEY_h,          setmfact,       {.f = -0.05} },
	{ MODKEY,                    XKB_KEY_l,          setmfact,       {.f = +0.05} },
	{ MODKEY|WLR_MODIFIER_SHIFT, XKB_KEY_Return,     zoom,           {0} },
	{ MODKEY,                    XKB_KEY_Tab,        view,           {0} },
	{ MODKEY,                    XKB_KEY_t,          setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                    XKB_KEY_f,          setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                    XKB_KEY_m,          setlayout,      {.v = &layouts[2]} },
	{ MODKEY,                    XKB_KEY_space,      setlayout,      {0} },
	{ MODKEY|WLR_MODIFIER_SHIFT, XKB_KEY_space,      togglefloating, {0} },
	{ MODKEY,                    XKB_KEY_e,         togglefullscreen, {0} },
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

	/* Ctrl-Alt-Backspace and Ctrl-Alt-Fx used to be handled by X server */
	{ WLR_MODIFIER_CTRL|WLR_MODIFIER_ALT,XKB_KEY_Terminate_Server, quit, {0} },
#define CHVT(n) { WLR_MODIFIER_CTRL|WLR_MODIFIER_ALT,XKB_KEY_XF86Switch_VT_##n, chvt, {.ui = (n)} }
	CHVT(1), CHVT(2), CHVT(3), CHVT(4), CHVT(5), CHVT(6),
	CHVT(7), CHVT(8), CHVT(9), CHVT(10), CHVT(11), CHVT(12),
};

static const Button buttons[] = {
	{ MODKEY, BTN_LEFT,   moveresize,     {.ui = CurMove} },
	{ MODKEY, BTN_MIDDLE, togglefloating, {0} },
	{ MODKEY, BTN_RIGHT,  moveresize,     {.ui = CurResize} },
};
