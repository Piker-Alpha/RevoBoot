/*
 * Copyright (c) 2009 Master Chief.
 *
 * Updates:
 *
 *  		- Read settings file based on given model identifier (PikerAlpha, October 2012).
 *			- COMMA_STRIPPED_MODEL_ID added (PikerAlpha, November 2012).
 */

#define TO_STRING_DO(a)						#a
#define STRING(a)							TO_STRING_DO(a)

#include STRING(SETTINGS_FILE)

/*
 * gPlatform.ModelID is a char * initialized by a call to strdup(SMB_PRODUCT_NAME) in
 * platform.c and we use strdup once more here so that gPlatform.ModelID is untouched.
 */
#define COMMA_STRIPPED_MODEL_ID	removeChar(strdup(gPlatform.ModelID), ',')
