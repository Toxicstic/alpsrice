//Modify this file to change what commands output to your statusbar, and recompile using the make command.
static const Block blocks[] = {
//  icon,	command,	time,	signal
	{"",	"sb-music",		5,		0},
	{"",	"sb-disk",		3600,	0},
	{"",	"sb-mem",		5,		0},
	{"",	"sb-vol",		5,		3},
	{"",	"sb-bat",		5,		0},
	{"",	"sb-wifi",		5,		0},
	{"",	"sb-updates",	1800,	0},
	{"",	"sb-date",		3600,	0},
	{"",	"sb-time",		1,		0},
	{"🏔️","",0,0},
};

//sets delimeter between status commands. NULL character ('\0') means no delimeter.
static char delim[] = " ";
static unsigned int delimLen = 5;
