//Modify this file to change what commands output to your statusbar, and recompile using the make command.
static const Block blocks[] = {
	/*Icon*/	/*Command*/	 			/*Update Interval*/		/*Update Signal*/
	{"vol %", "wpctl get-volume @DEFAULT_AUDIO_SINK@ | cut -d \".\" -f 2" ,							1,		0},

	{"mem ", "free -h | awk '/^Mem/ { print $3\"/\"$2 }' | sed s/i//g",	1,		0},

	{"date ", "date '+%b %d (%a) %I:%M%p'",					5,		0},
};

//sets delimeter between status commands. NULL character ('\0') means no delimeter.
static char delim[] = " | ";
static unsigned int delimLen = 5;
