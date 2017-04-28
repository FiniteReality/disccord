#include "catch.hpp"

#include <disccord/models/user.hpp>
#include <disccord/models/embed.hpp>
#include <disccord/models/invite.hpp>
#include <disccord/models/invite_metadata.hpp>
#include <disccord/models/message.hpp>
#include <disccord/models/channel.hpp>
#include <disccord/models/connection.hpp>
#include <disccord/models/guild.hpp>
#include <disccord/models/guild_embed.hpp>
#include <disccord/models/guild_member.hpp>
#include <disccord/models/read_state.hpp>
#include <disccord/models/relationship.hpp>
#include <disccord/models/ban.hpp>
#include <disccord/models/application.hpp>
#include <disccord/models/voice_region.hpp>
#include <disccord/models/voice_state.hpp>
#include <disccord/models/webhook.hpp>
#include <disccord/util/optional.hpp>

#include <iostream>
#include <fstream>

#include <cstdlib>

using namespace disccord;
using namespace disccord::models;

TEST_CASE( "User model correctly instantiated" ){
    user test_user;
    if (!test_user.get_username().empty() && test_user.get_discriminator() != 0 && !test_user.get_bot())
    {
        FAIL("Default constructor for embed model not correctly instantiated");
    }
    std::string json = R"({
    "id": "1234567890",
    "username": "FiniteReality",
    "discriminator": "5734",
    "bot": false
})";

    REQUIRE_NOTHROW(test_user.decode(web::json::value::parse(json)));

    REQUIRE(test_user.get_id() == 1234567890);
    REQUIRE(test_user.get_username() == "FiniteReality");
    REQUIRE(test_user.get_discriminator() == 5734);
    REQUIRE(test_user.get_bot() == false);
}


TEST_CASE( "Embed model correctly instantiated" ){
    //Embed Model
    embed test_embed;
    if (!test_embed.get_title().empty() && test_embed.get_type() != "rich" && test_embed.get_color() != 0)
    {
        FAIL("Default constructor for embed model not correctly instantiated");
    }

    std::string json = R"({
    "title": "Hello World",
    "type": "rich",
    "description": "This is a description",
    "url": "http://example.com/",
    "color": 123,
    "timestamp": "0000-00-00T00:00:00.000Z",
    "footer": {
        "icon_url": "http://example.com/",
        "text": "This is a footer"
    },
    "thumbnail": {
        "url": "http://example.com/"
    },
    "image": {
        "url": "http://example.com/"
    },
    "author": {
        "name": "Embed Author",
        "url": "http://example.com/",
        "icon_url": "http://example.com/"
    },
    "fields": [
        {
            "name": "Embed Field",
            "value": "Field Content",
            "inline": true
        },
        {
            "name": "Embed Field",
            "value": "Field Content",
            "inline": false
        },
        {
            "name": "Embed Field",
            "value": "Field Content"
        }
    ]
})";

    REQUIRE_NOTHROW(test_embed.decode(web::json::value::parse(json)));

    // TODO: put some requires here!!
}

TEST_CASE( "Invite model correctly instantiated" ){
    invite test_invite;
    if (!test_invite.get_code().empty())
    {
        FAIL("Default constructor for invite model not correctly instantiated");
    }
    std::string json = R"({
    "code": "asdfh487yed",
    "guild": {
        "id" : "165176875973476352",
        "name" : "CS:GO Fraggers Only",
        "splash" : null,
        "icon" : null
    },
    "channel": {
        "id" : "165176875973476352",
        "name" : "illuminati",
        "type" : 0
    }
})";

    REQUIRE_NOTHROW(test_invite.decode(web::json::value::parse(json)));

    // When splash/icon are null
    REQUIRE(test_invite.get_code() == "asdfh487yed");
    REQUIRE(test_invite.get_channel().get_value().get_id() == 165176875973476352);
    REQUIRE(test_invite.get_channel().get_value().get_name() == "illuminati");
    REQUIRE(test_invite.get_channel().get_value().get_type() == 0);
    REQUIRE(test_invite.get_guild().get_value().get_id() == 165176875973476352);
    REQUIRE(test_invite.get_guild().get_value().get_name() == "CS:GO Fraggers Only");

    std::string json2 = R"({
    "code": "asdfh487yed",
    "guild": {
        "id" : "165176875973476352",
        "name" : "CS:GO Fraggers Only",
        "splash" : "9de5c5675676fdabbc54c52ca03860a1",
        "icon" : "197d87a0caa9ea666b14e0938606aa2d"
    },
    "channel": {
        "id" : "165176875973476352",
        "name" : "illuminati",
        "type" : 0
    }
})";

    REQUIRE_NOTHROW(test_invite.decode(web::json::value::parse(json2)));

    // When splash/icon have values
    REQUIRE(test_invite.get_guild().get_value().get_splash().get_value() == "9de5c5675676fdabbc54c52ca03860a1");
    REQUIRE(test_invite.get_guild().get_value().get_icon().get_value() == "197d87a0caa9ea666b14e0938606aa2d");
}

TEST_CASE( "Invite Metadata model correctly instantiated" ){
    invite_metadata test_invite_md;
    if (!test_invite_md.get_created_at().empty() && test_invite_md.get_uses() != 0 && 
        !test_invite_md.get_max_uses() != 0 && !test_invite_md.get_max_age() != 0 && 
        test_invite_md.get_temporary() && test_invite_md.get_revoked())
    {
        FAIL("Default constructor for invite metadata model not correctly instantiated");
    }
    std::string json = R"({
    "inviter": {
        "id": "1234567890",
        "username": "FiniteReality",
        "discriminator": "5734",
        "bot": false
    },
    "created_at": "2016-03-31T19:15:39.954000+00:00",
    "uses" : 42,
    "max_uses" : 345000,
    "max_age" : 7200,
    "temporary" : true,
    "revoked" : false
})";

    REQUIRE_NOTHROW(test_invite_md.decode(web::json::value::parse(json)));

    REQUIRE(test_invite_md.get_inviter().get_value().get_id() == 1234567890);
    REQUIRE(test_invite_md.get_inviter().get_value().get_username() == "FiniteReality");
    REQUIRE(test_invite_md.get_inviter().get_value().get_discriminator() == 5734);
    REQUIRE(test_invite_md.get_inviter().get_value().get_bot() == false);
    REQUIRE(test_invite_md.get_created_at() == "2016-03-31T19:15:39.954000+00:00");
    REQUIRE(test_invite_md.get_uses() == 42);
    REQUIRE(test_invite_md.get_max_uses() == 345000);
    REQUIRE(test_invite_md.get_max_age() == 7200);
    REQUIRE(test_invite_md.get_temporary() == true);
    REQUIRE(test_invite_md.get_revoked() == false);
}

TEST_CASE( "Message model correctly instantiated" ){
    message test_message;
    if (test_message.get_id() != 0 && test_message.get_channel_id() != 0 && 
        !test_message.get_content().empty() && !test_message.get_timestamp().empty() && 
        test_message.get_tts() && test_message.get_mention_everyone() && test_message.get_pinned())
    {
        FAIL("Default constructor for message model not correctly instantiated");
    }

    std::string json = R"({
    "id" : "1266567890",
    "channel_id" : "9999999999",
    "author": {
        "id": "1234567890",
        "username": "FiniteReality",
        "discriminator": "5734",
        "bot": false
    },
    "content" : "this is message content",
    "timestamp": "2016-03-31T19:15:39.954000+00:00",
    "tts" : false,
    "mention_everyone" : true,
    "mentions" : [
    {
        "id": "6789012345",
        "username": "FiniteReality123",
        "discriminator": "6676",
        "bot": false
    },
    {
        "id": "1234567890",
        "username": "FiniteReality456",
        "discriminator": "9979",
        "bot": true
    }
    ],
    "mention_roles" : [
    {
        "id" : "1234567890",
        "name" : "DISCCORD_ROLE",
        "color" : 123456,
        "permissions" : 0,
        "position" : 3,
        "managed" : false,
        "mentionable" : true,
        "hoist" : false
    },
    {
        "id" : "3456789012",
        "name" : "DISCCORD_PLEB",
        "color" : 777777,
        "permissions" : 10,
        "position" : 4,
        "managed" : true,
        "mentionable" : false,
        "hoist" : false
    }
    ],
    "pinned" : false
})";

    REQUIRE_NOTHROW(test_message.decode(web::json::value::parse(json)));

    REQUIRE(test_message.get_author().get_value().get_id() == 1234567890);
    REQUIRE(test_message.get_author().get_value().get_username() == "FiniteReality");
    REQUIRE(test_message.get_author().get_value().get_discriminator() == 5734);
    REQUIRE(test_message.get_author().get_value().get_bot() == false);
    REQUIRE(test_message.get_id() == 1266567890);
    REQUIRE(test_message.get_channel_id() == 9999999999);
    REQUIRE(test_message.get_content() == "this is message content");
    REQUIRE(test_message.get_timestamp() == "2016-03-31T19:15:39.954000+00:00");
    REQUIRE(test_message.get_tts() == false);
    REQUIRE(test_message.get_mention_everyone() == true);
    REQUIRE(test_message.get_pinned() == false);

    //mentions array
    auto m1 = test_message.get_mentions().get_value()[0];
    auto m2 = test_message.get_mentions().get_value()[1];
    REQUIRE(m1.get_id() == 6789012345);
    REQUIRE(m1.get_username() == "FiniteReality123");
    REQUIRE(m1.get_discriminator() == 6676);
    REQUIRE(m1.get_bot() == false);

    REQUIRE(m2.get_id() == 1234567890);
    REQUIRE(m2.get_username() == "FiniteReality456");
    REQUIRE(m2.get_discriminator() == 9979);
    REQUIRE(m2.get_bot() == true);

    //mention_roles array
    auto mr1 = test_message.get_mention_roles().get_value()[0];
    auto mr2 = test_message.get_mention_roles().get_value()[1];
    REQUIRE(mr1.get_id() == 1234567890);
    REQUIRE(mr1.get_name() == "DISCCORD_ROLE");
    REQUIRE(mr1.get_color() == 123456);
    REQUIRE(mr1.get_permissions() == 0);
    REQUIRE(mr1.get_position() == 3);
    REQUIRE(mr1.get_managed() == false);
    REQUIRE(mr1.get_mentionable() == true);
    REQUIRE(mr1.get_hoist() == false);

    //TODO: check a few more of these
}

TEST_CASE( "Channel model correctly instantiated" ){
    channel test_channel;
    channel test_channel2;
    channel test_channel3;
    if (test_channel.get_id() != 0 && test_channel.get_last_message_id() != 0 && 
        test_channel.get_guild_id() != 0 && !test_channel.get_is_private())
    {
        FAIL("Default constructor for channel model not correctly instantiated");
    }

    //Build a DM Channel
    std::string dm_json = R"({
    "recipient": {
        "id": "1234567890",
        "username": "FiniteReality",
        "discriminator": "5734",
        "bot": false
    },
    "id": "134552934997426176",
    "is_private" : true,
    "last_message_id" : "153642275539255296"
})";

    REQUIRE_NOTHROW(test_channel.decode(web::json::value::parse(dm_json)));

    REQUIRE(test_channel.get_id() == 134552934997426176);
    REQUIRE(test_channel.get_is_private().get_value() == true);
    REQUIRE(test_channel.get_last_message_id().get_value() == 153642275539255296);

    auto recip = test_channel.get_recipient().get_value();
    REQUIRE(recip.get_id() == 1234567890);
    REQUIRE(recip.get_username() == "FiniteReality");
    REQUIRE(recip.get_discriminator() == 5734);
    REQUIRE(recip.get_bot() == false);

    //Build a Guild Channel
    //Text
    std::string textguild_json = R"({
    "id": "41771983423143937",
    "guild_id": "41771983423143937",
    "name": "general",
    "type": 0,
    "position": 6,
    "is_private": false,
    "permission_overwrites": [
    {
        "id" : "1234567890",
        "type" : "role",
        "allow" : 123456,
        "deny" : 0
    },
    {
        "id" : "3456789012",
        "type" : "member",
        "allow" : 777777,
        "deny" : 10
    }
    ],
    "topic": "24/7 chat about how to gank Mike #2",
    "last_message_id": "155117677105512449"
})";

    REQUIRE_NOTHROW(test_channel2.decode(web::json::value::parse(textguild_json)));

    REQUIRE(test_channel2.get_id() == 41771983423143937);
    REQUIRE(test_channel2.get_is_private().get_value() == false);
    REQUIRE(test_channel2.get_last_message_id().get_value() == 155117677105512449);
    REQUIRE(test_channel2.get_topic().get_value() == "24/7 chat about how to gank Mike #2");
    REQUIRE(test_channel2.get_position().get_value() == 6);
    REQUIRE(test_channel2.get_type().get_value() == 0);
    REQUIRE(test_channel2.get_name().get_value() == "general");
    REQUIRE(test_channel2.get_guild_id().get_value() == 41771983423143937);

    //permission_overwrites array
    auto po1 = test_channel2.get_permission_overwrites().get_value()[0];
    auto po2 = test_channel2.get_permission_overwrites().get_value()[1];
    REQUIRE(po1.get_id() == 1234567890);
    REQUIRE(po1.get_type() == "role");
    REQUIRE(po1.get_allow() == 123456);
    REQUIRE(po1.get_deny() == 0);
    REQUIRE(po2.get_id() == 3456789012);
    REQUIRE(po2.get_type() == "member");
    REQUIRE(po2.get_allow() == 777777);
    REQUIRE(po2.get_deny() == 10);

    //Voice
    std::string voiceguild_json = R"({
    "id": "155101607195836416",
    "guild_id": "41771983423143937",
    "name": "ROCKET CHEESE",
    "type": 1,
    "position": 5,
    "is_private": false,
    "permission_overwrites": [],
    "bitrate": 64000,
    "user_limit": 0
})";

    REQUIRE_NOTHROW(test_channel3.decode(web::json::value::parse(voiceguild_json)));

    REQUIRE(test_channel3.get_id() == 155101607195836416);
    REQUIRE(test_channel3.get_is_private().get_value() == false);
    REQUIRE(test_channel3.get_bitrate().get_value() == 64000);
    REQUIRE(test_channel3.get_user_limit().get_value() == 0);
    REQUIRE(test_channel3.get_position().get_value() == 5);
    REQUIRE(test_channel3.get_type().get_value() == 1);
    REQUIRE(test_channel3.get_name().get_value() == "ROCKET CHEESE");
    REQUIRE(test_channel3.get_guild_id().get_value() == 41771983423143937);
}

TEST_CASE( "Connection model correctly instantiated" ){
    connection test_connection;
    if (!test_connection.get_id().empty() && !test_connection.get_name().empty() && 
        !test_connection.get_type().empty() && !test_connection.get_revoked())
    {
        FAIL("Default constructor for connection model not correctly instantiated");
    }

    std::string json = R"({
    "integrations": [
    {
        "id" : "155101607195836416",
        "name" : "IntegrateMeBoi",
        "type" : "twitch",
        "enabled" : true,
        "syncing" : false,
        "role_id" : "958364161551016071",
        "expire_behavior" : 12345,
        "expire_grace_period" : 98345,
        "user" : {
            "id": "1234567890",
            "username": "FiniteReality",
            "discriminator": "5734",
            "bot": false
        },
        "account" : {
            "id" : "9998",
            "name" : "IamAccount"
        },
        "synced_at" : "2016-03-31T19:15:39.954000+00:00"
    },
    {
        "id" : "195836416155101607",
        "name" : "IntegrateMeOtherBoi",
        "type" : "youtube",
        "enabled" : false,
        "syncing" : true,
        "role_id" : "958615510160713641",
        "expire_behavior" : 45123,
        "expire_grace_period" : 34985,
        "user" : {
            "id": "8901234567",
            "username": "RealityFinite",
            "discriminator": "3457",
            "bot": false
        },
        "account" : {
            "id" : "8889",
            "name" : "IamNotAccount"
        },
        "synced_at" : "2017-03-31T19:35:49.954000+00:00"
    }
    ],
    "id": "13455293",
    "name" : "FiniteReality",
    "type" : "twitch",
    "revoked" : true
})";

    REQUIRE_NOTHROW(test_connection.decode(web::json::value::parse(json)));

    //integrations array
    auto ig1 = test_connection.get_integrations().get_value()[0];
    auto ig2 = test_connection.get_integrations().get_value()[1];
    REQUIRE(ig1.get_id() == 155101607195836416);
    REQUIRE(ig1.get_name() == "IntegrateMeBoi");
    REQUIRE(ig1.get_type() == "twitch");
    REQUIRE(ig1.get_enabled() == true);
    REQUIRE(ig1.get_syncing() == false);
    REQUIRE(ig1.get_role_id() == 958364161551016071);
    REQUIRE(ig1.get_expire_behavior() == 12345);
    REQUIRE(ig1.get_expire_grace_period() == 98345);
    auto usr = ig1.get_user().get_value();
    REQUIRE(usr.get_id() == 1234567890);
    REQUIRE(usr.get_username() == "FiniteReality");
    REQUIRE(usr.get_discriminator() == 5734);
    REQUIRE(usr.get_bot() == false);
    auto accnt = ig1.get_account().get_value();
    REQUIRE(accnt.get_id() == 9998);
    REQUIRE(accnt.get_name() == "IamAccount");
    REQUIRE(ig1.get_synced_at() == "2016-03-31T19:15:39.954000+00:00");

    REQUIRE(ig2.get_id() == 195836416155101607);
    REQUIRE(ig2.get_name() == "IntegrateMeOtherBoi");
    REQUIRE(ig2.get_type() == "youtube");
    REQUIRE(ig2.get_enabled() == false);
    REQUIRE(ig2.get_syncing() == true);
    REQUIRE(ig2.get_role_id() == 958615510160713641);
    REQUIRE(ig2.get_expire_behavior() == 45123);
    REQUIRE(ig2.get_expire_grace_period() == 34985);
    auto usr2 = ig2.get_user().get_value();
    REQUIRE(usr2.get_id() == 8901234567);
    REQUIRE(usr2.get_username() == "RealityFinite");
    REQUIRE(usr2.get_discriminator() == 3457);
    REQUIRE(usr2.get_bot() == false);
    auto accnt2 = ig2.get_account().get_value();
    REQUIRE(accnt2.get_id() == 8889);
    REQUIRE(accnt2.get_name() == "IamNotAccount");
    REQUIRE(ig2.get_synced_at() == "2017-03-31T19:35:49.954000+00:00");

    REQUIRE(test_connection.get_id() == "13455293");
    REQUIRE(test_connection.get_name() == "FiniteReality");
    REQUIRE(test_connection.get_type() == "twitch");
    REQUIRE(test_connection.get_revoked() == true);
}

TEST_CASE( "Guild model correctly instantiated" ){
    guild test_guild;
    if (test_guild.get_owner_id() != 0 && test_guild.get_afk_timeout() != 0 && 
        !test_guild.get_region().empty() && !test_guild.get_name().empty() && 
        test_guild.get_embed_enabled() && test_guild.get_verification_level() != 0
        && test_guild.get_mfa_level() != 0 && test_guild.get_default_message_notifications() != 0)
    {
        FAIL("Default constructor for guild model not correctly instantiated");
    }

    //testing a GUILD_CREATE scenario
    std::string json = R"({
        "id": "41771983423143937",
        "name": "Discord Developers",
        "icon": "SEkgTU9NIElUUyBBTkRSRUkhISEhISEh",
        "splash": null,
        "owner_id": "80351110224678912",
        "region": "us-east",
        "afk_channel_id": "42072017402331136",
        "afk_timeout": 300,
        "embed_enabled": true,
        "embed_channel_id": "41771983444115456",
        "verification_level": 1,
        "default_message_notifications": 3,
        "mfa_level": 1,
        "roles": [
            {
                "id": "41771983423143936",
                "name": "WE DEM BOYZZ!!!!!!",
                "color": 3447003,
                "hoist": true,
                "position": 1,
                "permissions": 66321471,
                "managed": false,
                "mentionable": false
            },
            {
                "id": "23143936417719834",
                "name": "WE DEM GURLZZ!!!!!!",
                "color": 7003344,
                "hoist": true,
                "position": 5,
                "permissions": 0,
                "managed": true,
                "mentionable": true
            }
        ],
        "emojis": [
            {
                "id": "23143936417719834",
                "name": "testemoj"
            },
            {
                "id": "17719834231439364",
                "name": "2testemoji2"
            }
        ],
        "members": [
            {
                "user": {
                    "id": "1234567890",
                    "username": "FiniteReality",
                    "discriminator": "5734",
                    "bot": false
                },
                "nick": "NOT API SUPPORT",
                "roles": [
                    "23143936417719834",
                    "23143936834417719"
                ],
                "joined_at": "2015-04-26T06:26:56.936000+00:00",
                "deaf": false,
                "mute": false
            },
            {
                "user": {
                    "id": "1234567890",
                    "username": "FiniteReality",
                    "discriminator": "5734",
                    "bot": false
                },
                "nick": "DISCCORD IS BEST LIB",
                "roles": [
                    "23143936417719834",
                    "23143936834417719"
                ],
                "joined_at": "2017-02-26T06:26:69.936000+00:00",
                "deaf": true,
                "mute": false
            }
        ],
        "presences": [
            {
                "user": {
                    "id": "1234567890",
                    "username": "FiniteReality",
                    "discriminator": "5734",
                    "bot": false
                },
                "roles": ["34231771981439364","17719834393642314"],
                "game": {
                    "name": "Rocket League",
                    "type": 1,
                    "url": "https://www.twitch.tv/123"
                },
                "guild_id": "34177198143936423",
                "status": "offline"
            },
            {
                "user": {
                    "id": "1234567890",
                    "username": "FiniteReality",
                    "discriminator": "5734",
                    "bot": false
                },
                "roles": ["34231771981439364","17719834393642314"],
                "game": {
                    "name": "DisccordDev",
                    "type": 0,
                    "url": null
                },
                "guild_id": "19341778143936423",
                "status": "online"
            }
        ],
        "features": ["INVITE_SPLASH"],
        "channels": [
            {
                "id": "41771983423143937",
                "guild_id": "41771983423143937",
                "name": "general",
                "type": 0,
                "position": 6,
                "is_private": false,
                "permission_overwrites": [],
                "topic": "24/7 chat about how to gank Mike #2",
                "last_message_id": "155117677105512449"
            },
            {
                "id": "41771983423143937",
                "guild_id": "41771983423143937",
                "name": "general",
                "type": 0,
                "position": 6,
                "is_private": false,
                "permission_overwrites": [],
                "topic": "24/7 chat about how to gank Mike #2",
                "last_message_id": "155117677105512449"
            }
        ],
        "unavailable": false
})";

    REQUIRE_NOTHROW(test_guild.decode(web::json::value::parse(json)));
    auto null_string = util::optional<std::string>::no_value();
    REQUIRE(test_guild.get_id() == 41771983423143937);
    REQUIRE(test_guild.get_name() == "Discord Developers");
    REQUIRE(test_guild.get_region() == "us-east");
    REQUIRE(test_guild.get_icon().get_value() == "SEkgTU9NIElUUyBBTkRSRUkhISEhISEh");
    CAPTURE(test_guild.get_splash().get_value());
    REQUIRE(test_guild.get_owner_id() == 80351110224678912);
    REQUIRE(test_guild.get_afk_channel_id().get_value()  == 42072017402331136);
    REQUIRE(test_guild.get_embed_channel_id().get_value()  == 41771983444115456);
    REQUIRE(test_guild.get_afk_timeout() == 300);
    REQUIRE(test_guild.get_mfa_level() == 1);
    REQUIRE(test_guild.get_verification_level() == 1);
    REQUIRE(test_guild.get_default_message_notifications() == 3);
    REQUIRE(test_guild.get_embed_enabled() == true);

    auto gfeats = test_guild.get_features()[0];
    REQUIRE(gfeats == "INVITE_SPLASH");

    //only testing the composites/fields that still need code coverage
    auto gpresc = test_guild.get_presences().get_value()[0]; //just going to test one value in vector for now
    REQUIRE(gpresc.get_game().get_value().get_name() == "Rocket League");
    REQUIRE(gpresc.get_game().get_value().get_url().get_value() == "https://www.twitch.tv/123");
    REQUIRE(gpresc.get_game().get_value().get_type().get_value() == 1);
    REQUIRE(gpresc.get_guild_id() == 34177198143936423);
    REQUIRE(gpresc.get_status() == "offline");
    auto gmembs = test_guild.get_members().get_value()[0]; //just going to test one value in vector for now
    REQUIRE(gmembs.get_nick().get_value() == "NOT API SUPPORT");
    REQUIRE(gmembs.get_joined_at() == "2015-04-26T06:26:56.936000+00:00");
    REQUIRE(gmembs.get_deaf() == false);
    REQUIRE(gmembs.get_mute() == false);
}

TEST_CASE( "Guild Embed model correctly instantiated" ){
    guild_embed test_guild_embed;
    if (test_guild_embed.get_channel_id() != 0 && test_guild_embed.get_enabled())
    {
        FAIL("Default constructor for guild embed model not correctly instantiated");
    }

    std::string json = R"({
    "channel_id": "38143936423417719",
    "enabled": true
})";

    REQUIRE_NOTHROW(test_guild_embed.decode(web::json::value::parse(json)));

    REQUIRE(test_guild_embed.get_channel_id() == 38143936423417719);
    REQUIRE(test_guild_embed.get_enabled() == true);
}

TEST_CASE( "Read State model correctly instantiated" ){
    read_state test_read_state;
    if (test_read_state.get_id() != 0 && test_read_state.get_mention_count() != 0)
    {
        FAIL("Default constructor for read state model not correctly instantiated");
    }

    std::string json = R"({
    "id": "64234381439317719",
    "mention_count": 13,
    "last_message_id": "64281439334317719"
})";

    REQUIRE_NOTHROW(test_read_state.decode(web::json::value::parse(json)));

    REQUIRE(test_read_state.get_id() == 64234381439317719);
    REQUIRE(test_read_state.get_mention_count() == 13);
    REQUIRE(test_read_state.get_last_message_id().get_value() == 64281439334317719);
}

TEST_CASE( "Relationship model correctly instantiated" ){
    relationship test_relationship;
    if (test_relationship.get_id() != 0)
    {
        FAIL("Default constructor for relationship model not correctly instantiated");
    }

    std::string json = R"({
    "id": "64234381431771993",
    "user": {
        "id": "1234567890",
        "username": "FiniteReality",
        "discriminator": "5734",
        "bot": false
    },
    "type": 4
})";

    REQUIRE_NOTHROW(test_relationship.decode(web::json::value::parse(json)));

    REQUIRE(test_relationship.get_id() == 64234381431771993);
    REQUIRE(test_relationship.get_type().get_value() == 4);
}

TEST_CASE( "Ban model correctly instantiated" ){
    ban test_ban;
    if (!test_ban.get_reason().empty())
    {
        FAIL("Default constructor for ban model not correctly instantiated");
    }

    std::string json = R"({
    "reason": "low quality jokes",
    "user": {
        "id": "1234567890",
        "username": "FiniteReality",
        "discriminator": "5734",
        "bot": false
    }
})";

    REQUIRE_NOTHROW(test_ban.decode(web::json::value::parse(json)));

    REQUIRE(test_ban.get_reason() == "low quality jokes");
}

TEST_CASE( "Guild Member model correctly instantiated" ){
    guild_member test_guild_memb;

    std::string json = R"({
      "deaf": false,
      "joined_at": "2016-12-11T19:10:41.288000+00:00",
      "user": {
        "username": "Disccord test bot",
        "discriminator": "3071",
        "bot": true,
        "id": "257584807716978688",
        "avatar": null
      },
      "roles": [
        "230773182120984577",
        "257584964726423554"
      ],
      "mute": false
})";

    REQUIRE_NOTHROW(test_guild_memb.decode(web::json::value::parse(json)));
    
    auto gmemb = test_guild_memb.get_member().get_value();
    auto roles = test_guild_memb.get_roles().get_value();
    REQUIRE(test_guild_memb.get_deaf() == false);
    REQUIRE(test_guild_memb.get_joined_at() == "2016-12-11T19:10:41.288000+00:00");
    REQUIRE(gmemb.get_username() == "Disccord test bot");
    REQUIRE(gmemb.get_discriminator() == 3071);
    REQUIRE(gmemb.get_bot() == true);
    REQUIRE(gmemb.get_id() == 257584807716978688);
    REQUIRE(roles[0] == 230773182120984577);
    REQUIRE(roles[1] == 257584964726423554);
    REQUIRE(test_guild_memb.get_mute() == false);
}

TEST_CASE( "Application model correctly instantiated" ){
    application test_app;
    if (test_app.get_id() != 0  && !test_app.get_name().empty() &&
        test_app.get_bot_public() && test_app.get_bot_requires_code_grant())
    {
        FAIL("Default constructor for application model not correctly instantiated");
    }

    std::string json = R"({
    "description": "Test",
    "icon": null,
    "id": "172150183260323840",
    "name": "Baba O-Riley",
    "bot_public": true,
    "bot_requires_code_grant": false,
    "owner": {
        "id": "1234567890",
        "username": "FiniteReality",
        "discriminator": "5734",
        "bot": false
    },
    "rpc_origins": [
    "WHAT","THIS","APPLICATION"
    ]
})";

    REQUIRE_NOTHROW(test_app.decode(web::json::value::parse(json)));

    REQUIRE(test_app.get_id() == 172150183260323840);
    REQUIRE(test_app.get_name() == "Baba O-Riley");
    REQUIRE(test_app.get_bot_public() == true);
    REQUIRE(test_app.get_bot_requires_code_grant() == false);
    REQUIRE(test_app.get_description().get_value() == "Test");
    REQUIRE(test_app.get_rpc_origins().get_value()[0] == "WHAT");
    REQUIRE(test_app.get_rpc_origins().get_value()[1] == "THIS");
    REQUIRE(test_app.get_rpc_origins().get_value()[2] == "APPLICATION");
}

TEST_CASE( "Voice region model correctly instantiated" ){
    voice_region test_vr;
    if (!test_vr.get_id().empty()  && !test_vr.get_name().empty() &&
        test_vr.get_vip() && test_vr.get_optimal() &&
        test_vr.get_deprecated() && test_vr.get_custom())
    {
        FAIL("Default constructor for Voice region model not correctly instantiated");
    }

    std::string json = R"({
    "name": "London",
    "deprecated": true,
    "custom": false,
    "vip": false,
    "optimal": true,
    "id": "london"
})";

    REQUIRE_NOTHROW(test_vr.decode(web::json::value::parse(json)));

    REQUIRE(test_vr.get_id() == "london");
    REQUIRE(test_vr.get_name() == "London");
    REQUIRE(test_vr.get_vip() == false);
    REQUIRE(test_vr.get_optimal() == true);
    REQUIRE(test_vr.get_deprecated() == true);
    REQUIRE(test_vr.get_custom() == false);
}

TEST_CASE( "Voice state model correctly instantiated" ){
    voice_state test_vs;
    if (test_vs.get_channel_id() != 0 && test_vs.get_user_id() != 0 &&
        !test_vs.get_session_id().empty()  && test_vs.get_deaf() &&
        test_vs.get_mute() && test_vs.get_self_deaf() &&
        test_vs.get_self_mute() && test_vs.get_suppress())
    {
        FAIL("Default constructor for Voice state model not correctly instantiated");
    }

    std::string json = R"({
    "channel_id": "157733188964188161",
    "user_id": "80351110224678912",
    "session_id": "90326bd25d71d39b9ef95b299e3872ff",
    "deaf": false,
    "mute": false,
    "self_deaf": false,
    "self_mute": true,
    "suppress": false
})";

    REQUIRE_NOTHROW(test_vs.decode(web::json::value::parse(json)));

    REQUIRE(test_vs.get_channel_id() == 157733188964188161);
    REQUIRE(test_vs.get_user_id() == 80351110224678912);
    REQUIRE(test_vs.get_session_id() == "90326bd25d71d39b9ef95b299e3872ff");
    REQUIRE(test_vs.get_deaf() == false);
    REQUIRE(test_vs.get_mute() == false);
    REQUIRE(test_vs.get_self_deaf() == false);
    REQUIRE(test_vs.get_self_mute() == true);
    REQUIRE(test_vs.get_suppress() == false);
}

TEST_CASE( "Webhook model correctly instantiated" ){
    webhook test_wh;
    if (test_wh.get_channel_id() != 0 && !test_wh.get_token().empty())
    {
        FAIL("Default constructor for Webhook model not correctly instantiated");
    }
    
    std::string json = R"({
    "name": "test webhook",
    "channel_id": "199737254929760256",
    "token": "3d89bb7572e0fb30d8128367b3b1b44fecd1726de135cbe28a41f8b2f777c372ba2939e72279b94526ff5d1bd4358d65cf11",
    "avatar": null,
    "guild_id": "199737254929760256",
    "id": "223704706495545344",
    "user": {
        "username": "test",
        "discriminator": "7479",
        "id": "190320984123768832",
        "avatar": "b004ec1740a63ca06ae2e14c5cee11f3"
    }
})";

    REQUIRE_NOTHROW(test_wh.decode(web::json::value::parse(json)));
    
    REQUIRE(test_wh.get_channel_id() == 199737254929760256);
    REQUIRE(test_wh.get_guild_id().get_value() == 199737254929760256);
    REQUIRE(test_wh.get_id() == 223704706495545344);
    REQUIRE(test_wh.get_token() == "3d89bb7572e0fb30d8128367b3b1b44fecd1726de135cbe28a41f8b2f777c372ba2939e72279b94526ff5d1bd4358d65cf11");
    REQUIRE(test_wh.get_name().get_value() == "test webhook");
}
