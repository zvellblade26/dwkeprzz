/* user and group to drop privileges to */
static const char *user  = "nobody";
static const char *group = "nobody";

static const char *colorname[NUMCOLS] = {
	[INIT] =   "black",     /* after initialization */
	[INPUT] =  "#005577",   /* during input */
	[INPUT_ALT] = "black", /* during input, second color */
	[FAILED] = "#870000",   /* wrong password */
};

/* treat a cleared input like a wrong password (color) */
static const int failonclear = 1;

/* enable or disable (1 means enable, 0 disable) bell sound when password is incorrect */
static const int xbell = 0;
