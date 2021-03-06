/**
 * @file
 * Manage precompiled / predefined regular expressions
 *
 * @authors
 * Copyright (C) 2020 Pietro Cerutti <gahr@gahr.ch>
 *
 * @copyright
 * This program is free software: you can redistribute it and/or modify it under
 * the terms of the GNU General Public License as published by the Free Software
 * Foundation, either version 2 of the License, or (at your option) any later
 * version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 * FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more
 * details.
 *
 * You should have received a copy of the GNU General Public License along with
 * this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef MUTT_LIB_PREX_H
#define MUTT_LIB_PREX_H

#include <regex.h>

/**
 * enum Prex - Predefined list of regular expressions
 */
enum Prex
{
  PREX_URL,                   ///< `[imaps://user:pass@example.com/INBOX?foo=bar]`
  PREX_URL_QUERY_KEY_VAL,     ///< `https://example.com/?[q=foo]`
  PREX_RFC2047_ENCODED_WORD,  ///< `[=?utf-8?Q?=E8=81=AA=E6=98=8E=E7=9A=84?=]`
  PREX_GNUTLS_CERT_HOST_HASH, ///<\c [\#H foo.com A76D 954B EB79 1F49 5B3A 0A0E 0681 65B1]
  PREX_MAX
};

/**
 * enum PrexUrlSchemeMatch - Regex Matches for #PREX_URL
 *
 * @note The []s show the matching path of the URL
 */
enum PrexUrlSchemeMatch
{
  PREX_URL_MATCH_FULL,           ///< `[imaps://user:pass@host.comInbox?foo=bar]`
  PREX_URL_MATCH_SCHEME,         ///< `[imaps]://...`
  PREX_URL_MATCH_REST,           ///< `imaps:[//...]`
  PREX_URL_MATCH_AUTH_OR_PATH,   ///< `imaps:[somepath]|[//me@example.com/Inbox]?foo=bar`
  PREX_URL_MATCH_AUTHORITY_PATH, ///< `imaps:[//me@example.com/Inbox]?foo=bar`
  PREX_URL_MATCH_USERINFO,       ///< `...//[user:pass@]...`
  PREX_URL_MATCH_USER,           ///< `...//[user]:pass@...`
  PREX_URL_MATCH_COLONPASS,      ///< `...//user[:pass]@...`
  PREX_URL_MATCH_PASS,           ///< `...//user:[pass]@...`
  PREX_URL_MATCH_HOST,           ///< `imaps://...[host.com]...`
  PREX_URL_MATCH_HOSTNAME,       ///< `imaps://...[host.com]...`
  PREX_URL_MATCH_HOSTIPVX,       ///< `imaps://...[127.0.0.1]...`
  PREX_URL_MATCH_COLONPORT,      ///< `imaps://host.com[:993]/...`
  PREX_URL_MATCH_PORT,           ///< `imaps://host.com:[993]/...`
  PREX_URL_MATCH_SLASHPATH,      ///< `...:993[/Inbox]`
  PREX_URL_MATCH_PATH,           ///< `...:993/[Inbox]`
  PREX_URL_MATCH_PATH_ONLY,      ///< `mailto:[me@example.com]?foo=bar`
  PREX_URL_MATCH_QUESTIONQUERY,  ///< `...Inbox[?foo=bar&baz=value]`
  PREX_URL_MATCH_QUERY,          ///< `...Inbox?[foo=bar&baz=value]`
  PREX_URL_MATCH_MAX,
};

/**
 * enum PrexUrlQueryKeyValMatch - Regex Matches for #PREX_URL_QUERY_KEY_VAL
 *
 * @note The []s show the matching path of the URL Query
 */
enum PrexUrlQueryKeyValMatch
{
  PREX_URL_QUERY_KEY_VAL_MATCH_FULL, ///< `[key=val]`
  PREX_URL_QUERY_KEY_VAL_MATCH_KEY,  ///< `[key]=val`
  PREX_URL_QUERY_KEY_VAL_MATCH_VAL,  ///< `key=[val]`
  PREX_URL_QUERY_KEY_VAL_MATCH_MAX
};

/**
 * enum PrexRfc2047EncodedWordMatch - Regex Matches for #PREX_RFC2047_ENCODED_WORD
 *
 * @note The []s show the matching path of the RFC2047-encoded word
 */
enum PrexRfc2047EncodedWordMatch
{
  PREX_RFC2047_ENCODED_WORD_MATCH_FULL,     ///< `[=?utf-8?Q?=E8=81...?=]`
  PREX_RFC2047_ENCODED_WORD_MATCH_CHARSET,  ///< `=?[utf-8]?Q?=E8=81...?=`
  PREX_RFC2047_ENCODED_WORD_MATCH_ENCODING, ///< `=?utf-8?[Q]?=E8=81...?=`
  PREX_RFC2047_ENCODED_WORD_MATCH_TEXT,     ///< `=?utf-8?Q?[=E8=81...]?=`
  PREX_RFC2047_ENCODED_WORD_MATCH_MAX
};

/**
 * enum PrexGnuTlsCertHostnameMatch - Regex Matches for a TLS Certificate Hostname
 *
 * @note The []s show the matching path of the TLS Certificate Hostname
 */
enum PrexGnuTlsCertHostnameMatch
{
  PREX_GNUTLS_CERT_HOST_HASH_MATCH_FULL,      ///<\c [\#H foo.com A76D ... 65B1]
  PREX_GNUTLS_CERT_HOST_HASH_MATCH_HOST,      ///<\c \#H [foo.com] A76D ... 65B1
  PREX_GNUTLS_CERT_HOST_HASH_MATCH_HASH,      ///<\c \#H foo.com [A76D ... 65B1]
  PREX_GNUTLS_CERT_HOST_HASH_MATCH_HASH_LAST, ///<\c \#H foo.com A76D ... [65B1]
  PREX_GNUTLS_CERT_HOST_HASH_MATCH_MAX
};

regmatch_t *mutt_prex_capture(enum Prex which, const char *str);
void mutt_prex_free(void);

#endif /* MUTT_LIB_PREX_H */
