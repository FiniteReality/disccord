/* C++ code produced by gperf version 3.1 */
/* Command-line: gperf -CGIP -LC++ -t -m 5000 dispatches.gperf  */
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
#error "gperf generated tables don't work with this execution character set. Please report a bug to <bug-gperf@gnu.org>."
#endif

#line 1 "dispatches.gperf"

#include <disccord/ws/dispatch.hpp>
#line 4 "dispatches.gperf"
struct dispatch_mapping {
    int name;
	const disccord::ws::dispatch dispatch;
};
#include <string.h>

#define TOTAL_KEYWORDS 35
#define MIN_WORD_LENGTH 5
#define MAX_WORD_LENGTH 25
#define MIN_HASH_VALUE 9
#define MAX_HASH_VALUE 54
/* maximum key range = 46, duplicates = 0 */

class Perfect_Hash
{
private:
  static inline unsigned int hash (const char *str, size_t len);
public:
  static const struct dispatch_mapping *in_word_set (const char *str, size_t len);
};

inline unsigned int
Perfect_Hash::hash (const char *str, size_t len)
{
  static const unsigned char asso_values[] =
    {
      55, 55, 55, 55, 55, 55, 55, 55, 55, 55,
      55, 55, 55, 55, 55, 55, 55, 55, 55, 55,
      55, 55, 55, 55, 55, 55, 55, 55, 55, 55,
      55, 55, 55, 55, 55, 55, 55, 55, 55, 55,
      55, 55, 55, 55, 55, 55, 55, 55, 55, 55,
      55, 55, 55, 55, 55, 55, 55, 55, 55, 55,
      55, 55, 55, 55, 55, 10, 55,  4,  2,  1,
      55,  0, 55, 13, 55, 55,  0,  3, 25, 13,
       2, 55,  4, 55, 12,  9,  7, 55, 55, 55,
      55, 55, 55, 55, 55, 11, 55, 55, 55, 55,
      55, 55, 55, 55, 55, 55, 55, 55, 55, 55,
      55, 55, 55, 55, 55, 55, 55, 55, 55, 55,
      55, 55, 55, 55, 55, 55, 55, 55, 55, 55,
      55, 55, 55, 55, 55, 55, 55, 55, 55, 55,
      55, 55, 55, 55, 55, 55, 55, 55, 55, 55,
      55, 55, 55, 55, 55, 55, 55, 55, 55, 55,
      55, 55, 55, 55, 55, 55, 55, 55, 55, 55,
      55, 55, 55, 55, 55, 55, 55, 55, 55, 55,
      55, 55, 55, 55, 55, 55, 55, 55, 55, 55,
      55, 55, 55, 55, 55, 55, 55, 55, 55, 55,
      55, 55, 55, 55, 55, 55, 55, 55, 55, 55,
      55, 55, 55, 55, 55, 55, 55, 55, 55, 55,
      55, 55, 55, 55, 55, 55, 55, 55, 55, 55,
      55, 55, 55, 55, 55, 55, 55, 55, 55, 55,
      55, 55, 55, 55, 55, 55, 55, 55, 55, 55,
      55, 55, 55, 55, 55, 55
    };
  unsigned int hval = len;

  switch (hval)
    {
      default:
        hval += asso_values[static_cast<unsigned char>(str[13])];
      /*FALLTHROUGH*/
      case 13:
      case 12:
      case 11:
      case 10:
      case 9:
        hval += asso_values[static_cast<unsigned char>(str[8])];
      /*FALLTHROUGH*/
      case 8:
      case 7:
      case 6:
      case 5:
      case 4:
      case 3:
      case 2:
      case 1:
        hval += asso_values[static_cast<unsigned char>(str[0])];
        break;
    }
  return hval;
}

struct stringpool_t
  {
    char stringpool_str9[sizeof("READY")];
    char stringpool_str11[sizeof("RESUMED")];
    char stringpool_str12[sizeof("GUILD_DELETE")];
    char stringpool_str13[sizeof("GUILD_CREATE")];
    char stringpool_str14[sizeof("GUILD_UPDATE")];
    char stringpool_str17[sizeof("GUILD_ROLE_DELETE")];
    char stringpool_str18[sizeof("GUILD_ROLE_CREATE")];
    char stringpool_str19[sizeof("GUILD_ROLE_UPDATE")];
    char stringpool_str20[sizeof("MESSAGE_DELETE")];
    char stringpool_str21[sizeof("CHANNEL_DELETE")];
    char stringpool_str22[sizeof("MESSAGE_CREATE")];
    char stringpool_str23[sizeof("CHANNEL_CREATE")];
    char stringpool_str24[sizeof("MESSAGE_ACK")];
    char stringpool_str25[sizeof("MESSAGE_DELETE_BULK")];
    char stringpool_str26[sizeof("GUILD_MEMBER_REMOVE")];
    char stringpool_str27[sizeof("MESSAGE_UPDATE")];
    char stringpool_str28[sizeof("CHANNEL_UPDATE")];
    char stringpool_str29[sizeof("GUILD_MEMBER_ADD")];
    char stringpool_str30[sizeof("USER_UPDATE")];
    char stringpool_str31[sizeof("GUILD_MEMBER_UPDATE")];
    char stringpool_str32[sizeof("CHANNEL_PINS_ACK")];
    char stringpool_str33[sizeof("GUILD_MEMBERS_CHUNK")];
    char stringpool_str34[sizeof("CHANNEL_PINS_UPDATE")];
    char stringpool_str35[sizeof("GUILD_SYNC")];
    char stringpool_str36[sizeof("TYPING_START")];
    char stringpool_str37[sizeof("VOICE_STATE_UPDATE")];
    char stringpool_str38[sizeof("GUILD_BAN_ADD")];
    char stringpool_str39[sizeof("VOICE_SERVER_UPDATE")];
    char stringpool_str40[sizeof("PRESENCE_UPDATE")];
    char stringpool_str41[sizeof("GUILD_EMOJIS_UPDATE")];
    char stringpool_str42[sizeof("CHANNEL_RECIPIENT_ADD")];
    char stringpool_str45[sizeof("CHANNEL_RECIPIENT_REMOVE")];
    char stringpool_str49[sizeof("GUILD_INTEGRATIONS_UPDATE")];
    char stringpool_str52[sizeof("USER_SETTINGS_UPDATE")];
    char stringpool_str54[sizeof("GUILD_BAN_REMOVE")];
  };
static const struct stringpool_t stringpool_contents =
  {
    "READY",
    "RESUMED",
    "GUILD_DELETE",
    "GUILD_CREATE",
    "GUILD_UPDATE",
    "GUILD_ROLE_DELETE",
    "GUILD_ROLE_CREATE",
    "GUILD_ROLE_UPDATE",
    "MESSAGE_DELETE",
    "CHANNEL_DELETE",
    "MESSAGE_CREATE",
    "CHANNEL_CREATE",
    "MESSAGE_ACK",
    "MESSAGE_DELETE_BULK",
    "GUILD_MEMBER_REMOVE",
    "MESSAGE_UPDATE",
    "CHANNEL_UPDATE",
    "GUILD_MEMBER_ADD",
    "USER_UPDATE",
    "GUILD_MEMBER_UPDATE",
    "CHANNEL_PINS_ACK",
    "GUILD_MEMBERS_CHUNK",
    "CHANNEL_PINS_UPDATE",
    "GUILD_SYNC",
    "TYPING_START",
    "VOICE_STATE_UPDATE",
    "GUILD_BAN_ADD",
    "VOICE_SERVER_UPDATE",
    "PRESENCE_UPDATE",
    "GUILD_EMOJIS_UPDATE",
    "CHANNEL_RECIPIENT_ADD",
    "CHANNEL_RECIPIENT_REMOVE",
    "GUILD_INTEGRATIONS_UPDATE",
    "USER_SETTINGS_UPDATE",
    "GUILD_BAN_REMOVE"
  };
#define stringpool ((const char *) &stringpool_contents)

static const struct dispatch_mapping wordlist[] =
  {
    {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1},
#line 9 "dispatches.gperf"
    {(int)(size_t)&((struct stringpool_t *)0)->stringpool_str9,disccord::ws::dispatch::READY},
    {-1},
#line 10 "dispatches.gperf"
    {(int)(size_t)&((struct stringpool_t *)0)->stringpool_str11,disccord::ws::dispatch::RESUMED},
#line 16 "dispatches.gperf"
    {(int)(size_t)&((struct stringpool_t *)0)->stringpool_str12,disccord::ws::dispatch::GUILD_DELETE},
#line 11 "dispatches.gperf"
    {(int)(size_t)&((struct stringpool_t *)0)->stringpool_str13,disccord::ws::dispatch::GUILD_CREATE},
#line 12 "dispatches.gperf"
    {(int)(size_t)&((struct stringpool_t *)0)->stringpool_str14,disccord::ws::dispatch::GUILD_UPDATE},
    {-1}, {-1},
#line 23 "dispatches.gperf"
    {(int)(size_t)&((struct stringpool_t *)0)->stringpool_str17,disccord::ws::dispatch::GUILD_ROLE_DELETE},
#line 21 "dispatches.gperf"
    {(int)(size_t)&((struct stringpool_t *)0)->stringpool_str18,disccord::ws::dispatch::GUILD_ROLE_CREATE},
#line 22 "dispatches.gperf"
    {(int)(size_t)&((struct stringpool_t *)0)->stringpool_str19,disccord::ws::dispatch::GUILD_ROLE_UPDATE},
#line 35 "dispatches.gperf"
    {(int)(size_t)&((struct stringpool_t *)0)->stringpool_str20,disccord::ws::dispatch::MESSAGE_DELETE},
#line 28 "dispatches.gperf"
    {(int)(size_t)&((struct stringpool_t *)0)->stringpool_str21,disccord::ws::dispatch::CHANNEL_DELETE},
#line 33 "dispatches.gperf"
    {(int)(size_t)&((struct stringpool_t *)0)->stringpool_str22,disccord::ws::dispatch::MESSAGE_CREATE},
#line 26 "dispatches.gperf"
    {(int)(size_t)&((struct stringpool_t *)0)->stringpool_str23,disccord::ws::dispatch::CHANNEL_CREATE},
#line 37 "dispatches.gperf"
    {(int)(size_t)&((struct stringpool_t *)0)->stringpool_str24,disccord::ws::dispatch::MESSAGE_ACK},
#line 36 "dispatches.gperf"
    {(int)(size_t)&((struct stringpool_t *)0)->stringpool_str25,disccord::ws::dispatch::MESSAGE_DELETE_BULK},
#line 19 "dispatches.gperf"
    {(int)(size_t)&((struct stringpool_t *)0)->stringpool_str26,disccord::ws::dispatch::GUILD_MEMBER_REMOVE},
#line 34 "dispatches.gperf"
    {(int)(size_t)&((struct stringpool_t *)0)->stringpool_str27,disccord::ws::dispatch::MESSAGE_UPDATE},
#line 27 "dispatches.gperf"
    {(int)(size_t)&((struct stringpool_t *)0)->stringpool_str28,disccord::ws::dispatch::CHANNEL_UPDATE},
#line 17 "dispatches.gperf"
    {(int)(size_t)&((struct stringpool_t *)0)->stringpool_str29,disccord::ws::dispatch::GUILD_MEMBER_ADD},
#line 40 "dispatches.gperf"
    {(int)(size_t)&((struct stringpool_t *)0)->stringpool_str30,disccord::ws::dispatch::USER_UPDATE},
#line 18 "dispatches.gperf"
    {(int)(size_t)&((struct stringpool_t *)0)->stringpool_str31,disccord::ws::dispatch::GUILD_MEMBER_UPDATE},
#line 29 "dispatches.gperf"
    {(int)(size_t)&((struct stringpool_t *)0)->stringpool_str32,disccord::ws::dispatch::CHANNEL_PINS_ACK},
#line 20 "dispatches.gperf"
    {(int)(size_t)&((struct stringpool_t *)0)->stringpool_str33,disccord::ws::dispatch::GUILD_MEMBERS_CHUNK},
#line 30 "dispatches.gperf"
    {(int)(size_t)&((struct stringpool_t *)0)->stringpool_str34,disccord::ws::dispatch::CHANNEL_PINS_UPDATE},
#line 15 "dispatches.gperf"
    {(int)(size_t)&((struct stringpool_t *)0)->stringpool_str35,disccord::ws::dispatch::GUILD_SYNC},
#line 39 "dispatches.gperf"
    {(int)(size_t)&((struct stringpool_t *)0)->stringpool_str36,disccord::ws::dispatch::TYPING_START},
#line 42 "dispatches.gperf"
    {(int)(size_t)&((struct stringpool_t *)0)->stringpool_str37,disccord::ws::dispatch::VOICE_STATE_UPDATE},
#line 24 "dispatches.gperf"
    {(int)(size_t)&((struct stringpool_t *)0)->stringpool_str38,disccord::ws::dispatch::GUILD_BAN_ADD},
#line 43 "dispatches.gperf"
    {(int)(size_t)&((struct stringpool_t *)0)->stringpool_str39,disccord::ws::dispatch::VOICE_SERVER_UPDATE},
#line 38 "dispatches.gperf"
    {(int)(size_t)&((struct stringpool_t *)0)->stringpool_str40,disccord::ws::dispatch::PRESENCE_UPDATE},
#line 13 "dispatches.gperf"
    {(int)(size_t)&((struct stringpool_t *)0)->stringpool_str41,disccord::ws::dispatch::GUILD_EMOJIS_UPDATE},
#line 31 "dispatches.gperf"
    {(int)(size_t)&((struct stringpool_t *)0)->stringpool_str42,disccord::ws::dispatch::CHANNEL_RECIPIENT_ADD},
    {-1}, {-1},
#line 32 "dispatches.gperf"
    {(int)(size_t)&((struct stringpool_t *)0)->stringpool_str45,disccord::ws::dispatch::CHANNEL_RECIPIENT_REMOVE},
    {-1}, {-1}, {-1},
#line 14 "dispatches.gperf"
    {(int)(size_t)&((struct stringpool_t *)0)->stringpool_str49,disccord::ws::dispatch::GUILD_INTEGRATIONS_UPDATE},
    {-1}, {-1},
#line 41 "dispatches.gperf"
    {(int)(size_t)&((struct stringpool_t *)0)->stringpool_str52,disccord::ws::dispatch::USER_SETTINGS_UPDATE},
    {-1},
#line 25 "dispatches.gperf"
    {(int)(size_t)&((struct stringpool_t *)0)->stringpool_str54,disccord::ws::dispatch::GUILD_BAN_REMOVE}
  };

const struct dispatch_mapping *
Perfect_Hash::in_word_set (const char *str, size_t len)
{
  if (len <= MAX_WORD_LENGTH && len >= MIN_WORD_LENGTH)
    {
      unsigned int key = hash (str, len);

      if (key <= MAX_HASH_VALUE)
        {
          int o = wordlist[key].name;
          if (o >= 0)
            {
              const char *s = o + stringpool;

              if (*str == *s && !strcmp (str + 1, s + 1))
                return &wordlist[key];
            }
        }
    }
  return 0;
}
#line 44 "dispatches.gperf"

