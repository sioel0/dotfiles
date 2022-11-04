//Modify this file to change what commands output to your statusbar, and recompile using the make command.
static const Block blocks[] = {
	/*Icon*/	/*Command*/		/*Update Interval*/	/*Update Signal*/
  {"", "/home/sioel0/.scripts/info_not/network",     25,  0},
  {"", "/home/sioel0/.scripts/info_not/battery",     10,  0},
  {"", "/home/sioel0/.scripts/info_not/caldate",     60,  0},
  {"", "/home/sioel0/.scripts/info_not/hour",         5,  0},
};

//sets delimeter between status commands. NULL character ('\0') means no delimeter.
static char delim[] = " | ";
static unsigned int delimLen = 5;
