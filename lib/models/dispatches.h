/* ANSI-C code produced by gperf version 3.0.4 */
/* Command-line: gperf -CGD -LANSI-C -K dispatch_name -t lib/models/dispatches.gperf  */
/* Computed positions: -k'1,9,14' */

#if !((' ' == 32) && ('!' == 33) && ('"' == 34) && ('#' == 35) \
      && ('%' == 37) && ('&' == 38) && ('\'' == 39) && ('(' == 40) \
      && (')' == 41) && ('*' == 42) && ('+' == 43) && (',' == 44) \
      && ('-' == 45) && ('.' == 46) && ('/' == 47) && ('0' == 48) \
      && ('1' == 49) && ('2' == 50) && ('3' == 51) && ('4' == 52) \
      && ('5' == 53) && ('6' == 54) && ('7' == 55) && ('8' == 56) \
      && ('9' == 57) && (':' == 58) && (';' == 59) && ('<' == 60) \
      && ('=' == 61) && ('>' == 62) && ('?' == 63) && ('A' == 65) \
      && ('B' == 66) && ('C' == 67) && ('D' == 68) && ('E' == 69) \
      && ('F' == 70) && ('G' == 71) && ('H' == 72) && ('I' == 73) \
      && ('J' == 74) && ('K' == 75) && ('L' == 76) && ('M' == 77) \
      && ('N' == 78) && ('O' == 79) && ('P' == 80) && ('Q' == 81) \
      && ('R' == 82) && ('S' == 83) && ('T' == 84) && ('U' == 85) \
      && ('V' == 86) && ('W' == 87) && ('X' == 88) && ('Y' == 89) \
      && ('Z' == 90) && ('[' == 91) && ('\\' == 92) && (']' == 93) \
      && ('^' == 94) && ('_' == 95) && ('a' == 97) && ('b' == 98) \
      && ('c' == 99) && ('d' == 100) && ('e' == 101) && ('f' == 102) \
      && ('g' == 103) && ('h' == 104) && ('i' == 105) && ('j' == 106) \
      && ('k' == 107) && ('l' == 108) && ('m' == 109) && ('n' == 110) \
      && ('o' == 111) && ('p' == 112) && ('q' == 113) && ('r' == 114) \
      && ('s' == 115) && ('t' == 116) && ('u' == 117) && ('v' == 118) \
      && ('w' == 119) && ('x' == 120) && ('y' == 121) && ('z' == 122) \
      && ('{' == 123) && ('|' == 124) && ('}' == 125) && ('~' == 126))
/* The character set is not based on ISO-646.  */
#error "gperf generated tables don't work with this execution character set. Please report a bug to <bug-gnu-gperf@gnu.org>."
#endif

#line 1 "lib/models/dispatches.gperf"

#include "gateway.h"
#line 4 "lib/models/dispatches.gperf"
struct DISPATCH_HASH {
	const char* dispatch_name;
	const enum DISPATCH_TYPE value;
};

#define TOTAL_KEYWORDS 35
#define MIN_WORD_LENGTH 5
#define MAX_WORD_LENGTH 25
#define MIN_HASH_VALUE 5
#define MAX_HASH_VALUE 94
/* maximum key range = 90, duplicates = 0 */

#ifdef __GNUC__
__inline
#else
#ifdef __cplusplus
inline
#endif
#endif
static unsigned int
hash (register const char *str, register unsigned int len)
{
  static const unsigned char asso_values[] =
    {
      95, 95, 95, 95, 95, 95, 95, 95, 95, 95,
      95, 95, 95, 95, 95, 95, 95, 95, 95, 95,
      95, 95, 95, 95, 95, 95, 95, 95, 95, 95,
      95, 95, 95, 95, 95, 95, 95, 95, 95, 95,
      95, 95, 95, 95, 95, 95, 95, 95, 95, 95,
      95, 95, 95, 95, 95, 95, 95, 95, 95, 95,
      95, 95, 95, 95, 95,  0, 95, 15, 20, 10,
      95,  0, 95, 55, 95, 95,  0,  0,  0, 25,
       0, 95,  0, 95, 15, 45, 10, 95, 95, 95,
      95, 95, 95, 95, 95,  5, 95, 95, 95, 95,
      95, 95, 95, 95, 95, 95, 95, 95, 95, 95,
      95, 95, 95, 95, 95, 95, 95, 95, 95, 95,
      95, 95, 95, 95, 95, 95, 95, 95, 95, 95,
      95, 95, 95, 95, 95, 95, 95, 95, 95, 95,
      95, 95, 95, 95, 95, 95, 95, 95, 95, 95,
      95, 95, 95, 95, 95, 95, 95, 95, 95, 95,
      95, 95, 95, 95, 95, 95, 95, 95, 95, 95,
      95, 95, 95, 95, 95, 95, 95, 95, 95, 95,
      95, 95, 95, 95, 95, 95, 95, 95, 95, 95,
      95, 95, 95, 95, 95, 95, 95, 95, 95, 95,
      95, 95, 95, 95, 95, 95, 95, 95, 95, 95,
      95, 95, 95, 95, 95, 95, 95, 95, 95, 95,
      95, 95, 95, 95, 95, 95, 95, 95, 95, 95,
      95, 95, 95, 95, 95, 95, 95, 95, 95, 95,
      95, 95, 95, 95, 95, 95, 95, 95, 95, 95,
      95, 95, 95, 95, 95, 95
    };
  register int hval = len;

  switch (hval)
    {
      default:
        hval += asso_values[(unsigned char)str[13]];
      /*FALLTHROUGH*/
      case 13:
      case 12:
      case 11:
      case 10:
      case 9:
        hval += asso_values[(unsigned char)str[8]];
      /*FALLTHROUGH*/
      case 8:
      case 7:
      case 6:
      case 5:
      case 4:
      case 3:
      case 2:
      case 1:
        hval += asso_values[(unsigned char)str[0]];
        break;
    }
  return hval;
}

static const struct DISPATCH_HASH wordlist[] =
  {
#line 9 "lib/models/dispatches.gperf"
    {"READY", DISPATCH_READY},
#line 10 "lib/models/dispatches.gperf"
    {"RESUMED", DISPATCH_RESUMED},
#line 15 "lib/models/dispatches.gperf"
    {"GUILD_SYNC", DISPATCH_GUILD_SYNC},
#line 37 "lib/models/dispatches.gperf"
    {"MESSAGE_ACK", DISPATCH_MESSAGE_ACK},
#line 16 "lib/models/dispatches.gperf"
    {"GUILD_DELETE", DISPATCH_GUILD_DELETE},
#line 24 "lib/models/dispatches.gperf"
    {"GUILD_BAN_ADD", DISPATCH_GUILD_BAN_ADD},
#line 17 "lib/models/dispatches.gperf"
    {"GUILD_MEMBER_ADD", DISPATCH_GUILD_MEMBER_ADD},
#line 23 "lib/models/dispatches.gperf"
    {"GUILD_ROLE_DELETE", DISPATCH_GUILD_ROLE_DELETE},
#line 19 "lib/models/dispatches.gperf"
    {"GUILD_MEMBER_REMOVE", DISPATCH_GUILD_MEMBER_REMOVE},
#line 11 "lib/models/dispatches.gperf"
    {"GUILD_CREATE", DISPATCH_GUILD_CREATE},
#line 20 "lib/models/dispatches.gperf"
    {"GUILD_MEMBERS_CHUNK", DISPATCH_GUILD_MEMBERS_CHUNK},
#line 21 "lib/models/dispatches.gperf"
    {"GUILD_ROLE_CREATE", DISPATCH_GUILD_ROLE_CREATE},
#line 42 "lib/models/dispatches.gperf"
    {"VOICE_STATE_UPDATE", DISPATCH_VOICE_STATE_UPDATE},
#line 29 "lib/models/dispatches.gperf"
    {"CHANNEL_PINS_ACK", DISPATCH_CHANNEL_PINS_ACK},
#line 12 "lib/models/dispatches.gperf"
    {"GUILD_UPDATE", DISPATCH_GUILD_UPDATE},
#line 38 "lib/models/dispatches.gperf"
    {"PRESENCE_UPDATE", DISPATCH_PRESENCE_UPDATE},
#line 22 "lib/models/dispatches.gperf"
    {"GUILD_ROLE_UPDATE", DISPATCH_GUILD_ROLE_UPDATE},
#line 33 "lib/models/dispatches.gperf"
    {"MESSAGE_CREATE", DISPATCH_MESSAGE_CREATE},
#line 25 "lib/models/dispatches.gperf"
    {"GUILD_BAN_REMOVE", DISPATCH_GUILD_BAN_REMOVE},
#line 39 "lib/models/dispatches.gperf"
    {"TYPING_START", DISPATCH_TYPING_START},
#line 35 "lib/models/dispatches.gperf"
    {"MESSAGE_DELETE", DISPATCH_MESSAGE_DELETE},
#line 36 "lib/models/dispatches.gperf"
    {"MESSAGE_DELETE_BULK", DISPATCH_MESSAGE_DELETE_BULK},
#line 26 "lib/models/dispatches.gperf"
    {"CHANNEL_CREATE", DISPATCH_CHANNEL_CREATE},
#line 14 "lib/models/dispatches.gperf"
    {"GUILD_INTEGRATIONS_UPDATE", DISPATCH_GUILD_INTEGRATIONS_UPDATE},
#line 40 "lib/models/dispatches.gperf"
    {"USER_UPDATE", DISPATCH_USER_UPDATE},
#line 28 "lib/models/dispatches.gperf"
    {"CHANNEL_DELETE", DISPATCH_CHANNEL_DELETE},
#line 18 "lib/models/dispatches.gperf"
    {"GUILD_MEMBER_UPDATE", DISPATCH_GUILD_MEMBER_UPDATE},
#line 34 "lib/models/dispatches.gperf"
    {"MESSAGE_UPDATE", DISPATCH_MESSAGE_UPDATE},
#line 43 "lib/models/dispatches.gperf"
    {"VOICE_SERVER_UPDATE", DISPATCH_VOICE_SERVER_UPDATE},
#line 30 "lib/models/dispatches.gperf"
    {"CHANNEL_PINS_UPDATE", DISPATCH_CHANNEL_PINS_UPDATE},
#line 27 "lib/models/dispatches.gperf"
    {"CHANNEL_UPDATE", DISPATCH_CHANNEL_UPDATE},
#line 41 "lib/models/dispatches.gperf"
    {"USER_SETTINGS_UPDATE", DISPATCH_USER_SETTINGS_UPDATE},
#line 13 "lib/models/dispatches.gperf"
    {"GUILD_EMOJIS_UPDATE", DISPATCH_GUILD_EMOJIS_UPDATE},
#line 31 "lib/models/dispatches.gperf"
    {"CHANNEL_RECIPIENT_ADD", DISPATCH_CHANNEL_RECIPIENT_ADD},
#line 32 "lib/models/dispatches.gperf"
    {"CHANNEL_RECIPIENT_REMOVE", DISPATCH_CHANNEL_RECIPIENT_REMOVE}
  };

static const signed char lookup[] =
  {
    -1, -1, -1, -1, -1,  0, -1,  1, -1, -1,  2,  3,  4,  5,
    -1, -1,  6,  7, -1,  8, -1, -1,  9, -1, 10, -1, -1, 11,
    12, -1, -1, 13, 14, -1, -1, 15, -1, 16, -1, 17, -1, 18,
    19, -1, 20, -1, -1, -1, -1, 21, -1, -1, -1, -1, 22, 23,
    24, -1, -1, 25, -1, -1, -1, -1, 26, -1, -1, -1, -1, 27,
    -1, -1, -1, -1, 28, -1, -1, -1, -1, 29, -1, -1, -1, -1,
    30, 31, -1, -1, -1, 32, -1, 33, -1, -1, 34
  };

#ifdef __GNUC__
__inline
#if defined __GNUC_STDC_INLINE__ || defined __GNUC_GNU_INLINE__
__attribute__ ((__gnu_inline__))
#endif
#endif
const struct DISPATCH_HASH *
in_word_set (register const char *str, register unsigned int len)
{
  if (len <= MAX_WORD_LENGTH && len >= MIN_WORD_LENGTH)
    {
      register int key = hash (str, len);

      if (key <= MAX_HASH_VALUE && key >= 0)
        {
          register int index = lookup[key];

          if (index >= 0)
            {
              register const char *s = wordlist[index].dispatch_name;

              if (*str == *s && !strcmp (str + 1, s + 1))
                return &wordlist[index];
            }
        }
    }
  return 0;
}
