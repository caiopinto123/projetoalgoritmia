/*
 *  CUnit - A Unit testing framework library for C.
 *  Copyright (C) 2001  Anil Kumar
 *  Copyright (C) 2004  Anil Kumar, Jerry St.Clair
 *
 *  This library is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU Library General Public
 *  License as published by the Free Software Foundation; either
 *  version 2 of the License, or (at your option) any later version.
 *
 *  This library is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *  Library General Public License for more details.
 *
 *  You should have received a copy of the GNU Library General Public
 *  License along with this library; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

/*
 *  Contains Type Definitions for some generic functions used across
 *  CUnit project files.
 *
 *  Created By     : Anil Kumar on 13/Oct/2001
 *  Last Modified  : 13/Oct/2001
 *  Comment        : Moved some of the generic functions declarations
 *                   from other files to this one so as to use the
 *                   functions consitently. This file is not included
 *                   in the distribution headers because it is used
 *                   internally by CUnit.
 *  EMail          : aksaharan@yahoo.com
 *
 *  Last Modified  : 20-Jul-2004 (JDS)
 *  Comment        : New interface, support for deprecated version 1 names.
 *  EMail          : jds2@users.sourceforge.net
 *
 *  Modified       : 5-Sep-2004 (JDS)
 *  Comment        : Added internal test interface.
 *  EMail          : jds2@users.sourceforge.net
 */

#ifndef _CUNIT_UTIL_H
#define _CUNIT_UTIL_H

#ifdef __cplusplus
extern "C" {
#endif

#define CUNIT_MAX_STRING_LENGTH 1024

#define CUNIT_MAX_ENTITY_LEN 5

int CU_translate_special_characters(const char* szSrc, char* szDest, int maxlen);
int CU_compare_strings(const char* szSrc, const char* szDest);

void CU_trim_left(char* szString);
void CU_trim_right(char* szString);
void CU_trim(char* szString);

#ifdef CUNIT_BUILD_TESTS
void test_cunit_Util(void);
#endif

#ifdef __cplusplus
}
#endif

#ifdef USE_DEPRECATED_CUNIT_NAMES

#define translate_special_characters(src, dest, len) CU_translate_special_characters(src, dest, len)

#define compare_strings(src, dest) CU_compare_strings(src, dest)

#define trim_left(str) CU_trim_left(str)

#define trim_right(str) CU_trim_right(str)

#define trim(str) CU_trim(str)

#endif  /* USE_DEPRECATED_CUNIT_NAMES */

#endif /* _CUNIT_UTIL_H */
