/*
  regerror.c - POSIX regerror() implementation for TRE.

  Copyright (C) 2001-2004 Ville Laurikari <vl@iki.fi>.

  This program is free software; you can redistribute it and/or modify
  it under the terms of the GNU General Public License version 2 (June
  1991) as published by the Free Software Foundation.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program; if not, write to the Free Software
  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA

*/

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif /* HAVE_CONFIG_H */

#include <string.h>
#ifdef HAVE_WCHAR_H
#include <wchar.h>
#endif /* HAVE_WCHAR_H */
#ifdef HAVE_WCTYPE_H
#include <wctype.h>
#endif /* HAVE_WCTYPE_H */

#include "tre-internal.h"
#include "regex.h"
#include "gettext.h"
#define _(String) dgettext(PACKAGE, String)
#define gettext_noop(String) String

/* Error message strings for error codes listed in `regex.h'.  This list
   needs to be in sync with the codes listed there, naturally. */
static const char *tre_error_messages[] =
  { gettext_noop("No error"),			   /* REG_OK */
    gettext_noop("No match"),			   /* REG_NOMATCH */
    gettext_noop("Invalid regexp"),		   /* REG_BADPAT */
    gettext_noop("Unknown collating element"),	   /* REG_ECOLLATE */
    gettext_noop("Unknown character class name"),  /* REG_ECTYPE */
    gettext_noop("Trailing backslash"),		   /* REG_EESCAPE */
    gettext_noop("Invalid back reference"),	   /* REG_ESUBREG */
    gettext_noop("Missing ']'"),		   /* REG_EBRACK */
    gettext_noop("Missing ')'"),		   /* REG_EPAREN */
    gettext_noop("Missing '}'"),		   /* REG_EBRACE */
    gettext_noop("Invalid contents of {}"),	   /* REG_BADBR */
    gettext_noop("Invalid character range"),	   /* REG_ERANGE */
    gettext_noop("Out of memory"),		   /* REG_ESPACE */
    gettext_noop("XXX")				   /* REG_BADRPT */
  };

size_t
regerror(int errcode, const regex_t *preg, char *errbuf, size_t errbuf_size)
{
  const char *err;
  size_t err_len;

  if (errcode >= 0
      && errcode < (sizeof(tre_error_messages) / sizeof(*tre_error_messages)))
    err = gettext(tre_error_messages[errcode]);
  else
    err = gettext("Unknown error");

  err_len = strlen(err) + 1;
  if (errbuf_size > 0 && errbuf != NULL)
    {
      if (err_len > errbuf_size)
	{
	  strncpy(errbuf, err, errbuf_size - 1);
	  errbuf[errbuf_size - 1] = '\0';
	}
      else
	{
	  strcpy(errbuf, err);
	}
    }
  return err_len;
}

/* EOF */
