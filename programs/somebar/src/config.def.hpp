// somebar - dwl bar
// see license file for copyright and license details.

#pragma once
#include "common.hpp"
#include <linux/input-event-codes.h>

constexpr bool topbar = true;

constexpr int paddingx = 10;
constexpr int paddingy = 3;

// see https://docs.gtk.org/pango/type_func.fontdescription.from_string.html
constexpr const char* font = "scientifica bold 10";

//					                               	#9da9a0          		 #1e2326
constexpr colorscheme colorinactive = {color(0x9d, 0xa9, 0xa0), color(0x1e, 0x23, 0x26)};
//			                               			#a7c080		          	#a132326
constexpr colorscheme coloractive = {color(0xa7, 0xc0, 0x80), color(0x1e, 0x23, 0x26)};

static std::vector<std::string> tagnames = {
	"1", "2", "3",
	"4", "5", "6",
	"7", "8", "9",
};

constexpr const char* termcmd[] = {"foot", nullptr};
constexpr const char* editconfig[] = {"foot", "-e", "hx", "~/.local/src/dwl/config.h", nullptr};
constexpr button buttons[] = {
	{ clkstatustext,   btn_left,  spawn,      {.v = termcmd} },
	{ clkstatustext,   btn_right,  spawn,      {.v = editconfig} },
};
