/*
 * Copyright (c) 1999-2003 Apple Computer, Inc. All rights reserved.
 *
 * @APPLE_LICENSE_HEADER_START@
 * 
 * Portions Copyright (c) 1999-2003 Apple Computer, Inc.  All Rights
 * Reserved.  This file contains Original Code and/or Modifications of
 * Original Code as defined in and that are subject to the Apple Public
 * Source License Version 2.0 (the "License").  You may not use this file
 * except in compliance with the License.  Please obtain a copy of the
 * License at http://www.apple.com/publicsource and read it before using
 * this file.
 * 
 * The Original Code and all software distributed under the License are
 * distributed on an "AS IS" basis, WITHOUT WARRANTY OF ANY KIND, EITHER
 * EXPRESS OR IMPLIED, AND APPLE HEREBY DISCLAIMS ALL SUCH WARRANTIES,
 * INCLUDING WITHOUT LIMITATION, ANY WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE OR NON- INFRINGEMENT.  Please see the
 * License for the specific language governing rights and limitations
 * under the License.
 * 
 * @APPLE_LICENSE_HEADER_END@
 *
 * Copyright 1993 NeXT, Inc. All rights reserved.
 */

#include "bootstruct.h"
#include "libsaio.h"
#include "xml.h"
#include "stdbool.h"

extern char *Language;
extern char *LoadableFamilies;

int sysConfigValid;


//==============================================================================

static inline int isspace(char c)
{
    return (c == ' ' || c == '\t');
}


//==============================================================================

bool getValueForConfigTableKey(config_file_t *config, const char *key, const char **val, int *size)
{
    if (config->dictionary != 0)
    {
        // Look up key in XML dictionary
        TagPtr value;
        value = XMLGetProperty(config->dictionary, key);

        if (value != 0)
        {
            if (value->type != kTagTypeString)
            {
                error("Non-string tag '%s' found in config file\n", key);
                return false;
            }
            *val = value->string;
            *size = strlen(value->string);
            return true;
        }
    }
    // else {} for legacy plist-style table, which is not implemented!

	return false;
}


//==============================================================================

char * newStringForKey(char *key, config_file_t *config)
{
    const char *val;
    char *newstr;
    int size;
    
    if (getValueForKey(key, &val, &size, config) && size)
    {
        newstr = (char *)malloc(size + 1);
        strlcpy(newstr, val, size + 1);
        return newstr;
    }

    return 0;
}


//==============================================================================
/* parse a command line
 * in the form: [<argument> ...]  [<option>=<value> ...]
 * both <option> and <value> must be either composed of
 * non-whitespace characters, or enclosed in quotes.
 */

static const char *getToken(const char *line, const char **begin, int *len)
{
	if (*line == '\"')
	{
		*begin = ++line;

		while (*line && *line != '\"')
		{
			line++;
		}

		*len = line++ - *begin;
	}
	else
	{
		*begin = line;

		while (*line && !isspace(*line) && *line != '=')
		{
			line++;
		}

		*len = line - *begin;
	}

	return line;
}


//==============================================================================

bool getValueForBootKey(const char *line, const char *target, const char **match, int *len)
{
	const char *key, *value;

	int key_len, value_len;
	int targetLength = strlen(target);

    
	while (*line)
	{
		// Check for keyword or argument.
		while (isspace(*line))
		{
			line++;
		}

		// Check for '=' or whitespace.
		line = getToken(line, &key, &key_len);

		// line now points to '=' or space.
		if (*line && !isspace(*line))
		{
			line = getToken(++line, &value, &value_len);
		}
		else
		{
			value = line;
			value_len = 0;
		}

		// Do we have a match?
		if ((targetLength == key_len) && strncmp(target, key, key_len) == 0)
		{
			// Yes, set the matching value (match) and its length (len).
			*match = value;
			*len = value_len;

			// Bail out early (don't keep on searching to the end of the line).
			return true;
		}
	}

	return false;
}


//==============================================================================

bool getBoolForKey(const char *key, bool *result_val, config_file_t *config)
{
    const char *key_val;
    int size;
    
    if (getValueForKey(key, &key_val, &size, config))
    {
        if ((size >= 1) && (key_val[0] == 'Y' || key_val[0] == 'y'))
		{
            *result_val = true;
		}
        else
		{
            *result_val = false;
		}

        return true; // Key found.
    }

    return false; // Key not found.
}


//==============================================================================

bool getIntForKey(const char *key, int *value, config_file_t *config)
{
    const char *val;
    int size, sum;
    bool negative = false;
    
    if (getValueForKey(key, &val, &size, config))
	{
		if (size)
		{
			if (*val == '-')
			{
				negative = true;
				val++;
				size--;
			}
			
			for (sum = 0; size > 0; size--)
			{
				if (*val < '0' || *val > '9')
				{
					return false;
				}
				
				sum = (sum * 10) + (*val++ - '0');
			}
			
			if (negative)
			{
				sum = -sum;
			}
			
			*value = sum;

			return true; // Key found
		}
	}

    return false; // Key not found
}


//==============================================================================

bool getValueForKey(const char *key, const char **val, int *size, config_file_t *config)
{  
    if (getValueForBootKey(bootArgs->CommandLine, key, val, size))
	{
        return true;
	}

    bool ret = getValueForConfigTableKey(config, key, val, size);

    return ret;
}


//==============================================================================
// ParseXMLFile modifies the input buffer and expects one dictionary in the 
// XML file. Puts the first dictionary it finds in the tag pointer and 
// returns 0, or -1 if not found (and does not modify the dict pointer).
// Prints an error message if there is a parsing error.

long ParseXMLFile(char * buffer, TagPtr * dict)
{
    long	length;
	long	pos = 0;
    TagPtr	tag;
    char	*configBuffer;
  
    configBuffer = malloc(strlen(buffer)+1);
    strcpy(configBuffer, buffer);

    while (1)
    {
        length = XMLParseNextTag(configBuffer + pos, &tag);

        if (length == -1)
            break;
    
        pos += length;
    
        if (tag == 0)
		{
            continue;
		}

        if (tag->type == kTagTypeDict)
		{
            break;
		}
    
        XMLFreeTag(tag);
    }

    free(configBuffer);

    if (length < 0)
    {
        error ("Error parsing plist file\n");
        return -1;
    }

    *dict = tag;

    return 0;
}



//==============================================================================
// Returns 0 on success and -1 when it is fails to locate / open the file.

int loadSystemConfig(config_file_t *config)
{
	char *path = malloc(80); // Long enough for the longest (default) path.
	static char * dirspec[] = {
        
#if LION_RECOVERY_SUPPORT
		"com.apple.recovery.boot",
#endif
        
#if LION_INSTALL_SUPPORT
		".IABootFiles",
		"OS X Install Data",
		"Mac OS X Install Data",
#endif
		"Library/Preferences/SystemConfiguration" // The default.
        
#if APPLE_RAID_SUPPORT
		/*
		 * This is a temporarily change to test RAID support, but it
		 * will be rewritten right after Bryan confirms that it works.
		 */
		,
		"com.apple.boot.P/Library/Preferences/SystemConfiguration",
		"com.apple.boot.R/Library/Preferences/SystemConfiguration",
		"com.apple.boot.S/Library/Preferences/SystemConfiguration"
#endif
	};
    
	int i, fd;
    
	for (i = 0; i < sizeof(dirspec) / sizeof(dirspec[0]); i++)
	{
		sprintf(path, "/%s/%s", dirspec[i], "com.apple.Boot.plist");
        
		if ((fd = open(path, 0)) >= 0)
		{
			// IO_CONFIG_DATA_SIZE is defined as 4096 in bios.h and which should
			// be sufficient enough for RevoBoot (size was 4K for years already).
			read(fd, config->plist, IO_CONFIG_DATA_SIZE);
			close(fd);
            
			// Build XML dictionary.
			ParseXMLFile(config->plist, &config->dictionary);
            
			return 0;
		}
	}
    
	return -1;
}


//==============================================================================

char * newString(const char * oldString)
{
	if (oldString)
	{
		return strcpy(malloc(strlen(oldString) + 1), oldString);
	}

	return NULL;
}

