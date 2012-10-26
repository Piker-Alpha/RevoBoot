/*
 * Copyright (c) 2009 Master Chief.
 *
 * Updates:
 *
 *			- Read settings file based on given model identifier (PikerAlpha, October 2012).
 */

#define TO_STRING_DO(a)		#a
#define STRING(a)			TO_STRING_DO(a)
#define INCLUDE_FILE		STRING(SETTINGS_FILE)

#include INCLUDE_FILE
