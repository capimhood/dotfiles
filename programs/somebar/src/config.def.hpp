// somebar - dwl bar
// See LICENSE file for copyright and license details.

#pragma once
#include "common.hpp"
#include <linux/input-event-codes.h>

constexpr bool topbar = true;

constexpr int paddingX = 10;
constexpr int paddingY = 3;

// See https://docs.gtk.org/Pango/type_func.FontDescription.from_string.html
constexpr const char* font = "scientifica 10";

//						#9da9a0 		 #1e2326
constexpr ColorScheme colorInactive = {Color(0x9d, 0xa9, 0xa0), Color(0x1e, 0x23, 0x26)};
//						#1e2326			#a7c080
constexpr ColorScheme colorActive = {Color(0x1e, 0x23, 0x26), Color(0xa7, 0xc0, 0x80)};

static std::vector<std::string> tagNames = {
	"1", "2", "3",
	"4", "5", "6",
	"7", "8", "9",
};

constexpr const char* termcmd[] = {"foot", nullptr};
constexpr const char* editconfig[] = {"foot", "-e", "hx", "~/.local/src/dwl/config.h", nullptr};
constexpr Button buttons[] = {
	{ ClkStatusText,   BTN_LEFT,  spawn,      {.v = termcmd} },
	{ ClkStatusText,   BTN_RIGHT,  spawn,      {.v = editconfig} },
};
