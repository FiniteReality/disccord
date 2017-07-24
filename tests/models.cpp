#include "catch.hpp"

#include <disccord/models/user.hpp>
//#include <disccord/models/embed.hpp>
#include <disccord/models/invite.hpp>
//#include <disccord/models/invite_metadata.hpp>
#include <disccord/models/message.hpp>
#include <disccord/models/channel.hpp>
#include <disccord/models/connection.hpp>
#include <disccord/models/guild.hpp>
#include <disccord/models/guild_embed.hpp>
#include <disccord/models/guild_member.hpp>
//#include <disccord/models/read_state.hpp>
//#include <disccord/models/relationship.hpp>
//#include <disccord/models/ban.hpp>
//#include <disccord/models/application.hpp>
#include <disccord/models/voice_region.hpp>
//#include <disccord/models/voice_state.hpp>
#include <disccord/util/optional.hpp>

#include <iostream>
#include <fstream>

#include <cstdlib>

using namespace disccord;
using namespace disccord::models;

TEST_CASE( "User model correctly instantiated" ){
    user test_user;

    std::string json = R"({
    "id": "1234567890",
    "username": "FiniteReality",
    "discriminator": "5734",
    "bot": false
})";

    REQUIRE_NOTHROW(test_user.decode(web::json::value::parse(json)));

    REQUIRE(test_user.id == 1234567890);
    REQUIRE(test_user.username == "FiniteReality");
    REQUIRE(test_user.discriminator == 5734);
    REQUIRE(test_user.bot == false);
}


/*TEST_CASE( "Embed model correctly instantiated" ){
    //Embed Model
    embed test_embed;
    if (!test_embed.title.empty() && test_embed.type != "rich" && test_embed.color != 0)
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
}*/

TEST_CASE( "Invite model correctly instantiated" ){
    invite test_invite;

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
    REQUIRE(test_invite.code == "asdfh487yed");
    /*REQUIRE(test_invite.channel.get_value().id == 165176875973476352);
    REQUIRE(test_invite.channel.get_value().name == "illuminati");
    REQUIRE(test_invite.channel.get_value().type == 0);
    REQUIRE(test_invite.guild.get_value().id == 165176875973476352);
    REQUIRE(test_invite.guild.get_value().name == "CS:GO Fraggers Only");*/

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

    /*// When splash/icon have values
    REQUIRE(test_invite.guild.get_value().splash.get_value() == "9de5c5675676fdabbc54c52ca03860a1");
    REQUIRE(test_invite.guild.get_value().icon.get_value() == "197d87a0caa9ea666b14e0938606aa2d");*/
}

/*TEST_CASE( "Invite Metadata model correctly instantiated" ){
    invite_metadata test_invite_md;
    if (!test_invite_md.created_at.empty() && test_invite_md.uses != 0 && 
        !test_invite_md.max_uses != 0 && !test_invite_md.max_age != 0 && 
        test_invite_md.temporary && test_invite_md.revoked)
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

    REQUIRE(test_invite_md.inviter.get_value().id == 1234567890);
    REQUIRE(test_invite_md.inviter.get_value().username == "FiniteReality");
    REQUIRE(test_invite_md.inviter.get_value().discriminator == 5734);
    REQUIRE(test_invite_md.inviter.get_value().bot == false);
    REQUIRE(test_invite_md.created_at == "2016-03-31T19:15:39.954000+00:00");
    REQUIRE(test_invite_md.uses == 42);
    REQUIRE(test_invite_md.max_uses == 345000);
    REQUIRE(test_invite_md.max_age == 7200);
    REQUIRE(test_invite_md.temporary == true);
    REQUIRE(test_invite_md.revoked == false);
}*/

TEST_CASE( "Message model correctly instantiated" ){
    message test_message;

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
    "pinned" : false,
    "type": 0
})";

    REQUIRE_NOTHROW(test_message.decode(web::json::value::parse(json)));

    REQUIRE(test_message.author.get_value().id == 1234567890);
    REQUIRE(test_message.author.get_value().username == "FiniteReality");
    REQUIRE(test_message.author.get_value().discriminator == 5734);
    REQUIRE(test_message.author.get_value().bot == false);
    REQUIRE(test_message.id == 1266567890);
    REQUIRE(test_message.type == disccord::message_type::DEFAULT);
    REQUIRE(test_message.channel_id == 9999999999);
    REQUIRE(test_message.content == std::string{"this is message content"});
    //REQUIRE(test_message.timestamp == "2016-03-31T19:15:39.954000+00:00");
    REQUIRE(test_message.tts == false);
    REQUIRE(test_message.mention_everyone == true);
    REQUIRE(test_message.pinned == false);

    //mentions array
    auto m1 = test_message.mentions[0];
    auto m2 = test_message.mentions[1];
    REQUIRE(m1.id == 6789012345);
    REQUIRE(m1.username == "FiniteReality123");
    REQUIRE(m1.discriminator == 6676);
    REQUIRE(m1.bot == false);

    REQUIRE(m2.id == 1234567890);
    REQUIRE(m2.username == "FiniteReality456");
    REQUIRE(m2.discriminator == 9979);
    REQUIRE(m2.bot == true);

    //mention_roles array
    auto mr1 = test_message.mention_roles[0];
    auto mr2 = test_message.mention_roles[1];
    REQUIRE(mr1.id == 1234567890);
    REQUIRE(mr1.name == "DISCCORD_ROLE");
    REQUIRE(mr1.color == 123456);
    REQUIRE(mr1.permissions == disccord::permissions::NONE);
    REQUIRE(mr1.position == 3);
    REQUIRE(mr1.managed == false);
    REQUIRE(mr1.mentionable == true);
    REQUIRE(mr1.hoist == false);

    //TODO: check a few more of these
}

TEST_CASE( "Channel model correctly instantiated" ){
    channel test_channel;
    channel test_channel2;
    channel test_channel3;

    //Build a DM Channel
    std::string dm_json = R"({
    "recipients": {
        "id": "1234567890",
        "username": "FiniteReality",
        "discriminator": "5734",
        "bot": false
    },
    "id": "134552934997426176",
    "last_message_id" : "153642275539255296",
    "type": 1
})";

    REQUIRE_NOTHROW(test_channel.decode(web::json::value::parse(dm_json)));

    REQUIRE(test_channel.id == 134552934997426176);
    REQUIRE(test_channel.last_message_id.get_value() == 153642275539255296);
    REQUIRE(test_channel.type == disccord::channel_type::DM);

    /*auto recip = test_channel.recipient.get_value();
    REQUIRE(recip.id == 1234567890);
    REQUIRE(recip.username == "FiniteReality");
    REQUIRE(recip.discriminator == 5734);
    REQUIRE(recip.bot == false);*/

    //Build a Guild Channel
    //Text
    std::string textguild_json = R"({
    "id": "41771983423143937",
    "guild_id": "41771983423143937",
    "name": "general",
    "type": 0,
    "position": 6,
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

    REQUIRE(test_channel2.id == 41771983423143937);
    REQUIRE(test_channel2.last_message_id.get_value() == 155117677105512449);
    REQUIRE(test_channel2.topic.get_value() == "24/7 chat about how to gank Mike #2");
    REQUIRE(test_channel2.position.get_value() == 6);
    REQUIRE(test_channel2.type == disccord::channel_type::GUILD_TEXT);
    REQUIRE(test_channel2.name.get_value() == "general");
    REQUIRE(test_channel2.guild_id.get_value() == 41771983423143937);

    /*//permission_overwrites array
    auto po1 = test_channel2.permission_overwrites.get_value()[0];
    auto po2 = test_channel2.permission_overwrites.get_value()[1];
    REQUIRE(po1.id == 1234567890);
    REQUIRE(po1.type == "role");
    REQUIRE(po1.allow == 123456);
    REQUIRE(po1.deny == 0);
    REQUIRE(po2.id == 3456789012);
    REQUIRE(po2.type == "member");
    REQUIRE(po2.allow == 777777);
    REQUIRE(po2.deny == 10);*/

    //Voice
    std::string voiceguild_json = R"({
    "id": "155101607195836416",
    "guild_id": "41771983423143937",
    "name": "ROCKET CHEESE",
    "type": 1,
    "position": 5,
    "permission_overwrites": [],
    "bitrate": 64000,
    "user_limit": 0
})";

    REQUIRE_NOTHROW(test_channel3.decode(web::json::value::parse(voiceguild_json)));

    REQUIRE(test_channel3.id == 155101607195836416);
    REQUIRE(test_channel3.bitrate.get_value() == 64000);
    REQUIRE(test_channel3.user_limit.get_value() == 0);
    REQUIRE(test_channel3.position.get_value() == 5);
    REQUIRE(test_channel3.type == disccord::channel_type::DM);
    REQUIRE(test_channel3.name.get_value() == "ROCKET CHEESE");
    REQUIRE(test_channel3.guild_id.get_value() == 41771983423143937);
}

TEST_CASE( "Connection model correctly instantiated" ){
    connection test_connection;

    std::string json = R"({
    "integrations": [1234567890,0987654321],
    "id": "13455293",
    "name" : "FiniteReality",
    "type" : "twitch",
    "revoked" : true
})";

    REQUIRE_NOTHROW(test_connection.decode(web::json::value::parse(json)));

    //integrations array
    REQUIRE(test_connection.integrations[0] == 1234567890);
    REQUIRE(test_connection.integrations[1] ==  987654321);

    REQUIRE(test_connection.id == "13455293");
    REQUIRE(test_connection.name == "FiniteReality");
    REQUIRE(test_connection.type == "twitch");
    REQUIRE(test_connection.revoked == true);
}

TEST_CASE( "Guild model correctly instantiated" ){
    guild test_guild;

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
        "default_message_notifications": 1,
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
                "permission_overwrites": [],
                "topic": "24/7 chat about how to gank Mike #2",
                "last_message_id": "155117677105512449"
            }
        ],
        "unavailable": false
})";

    REQUIRE_NOTHROW(test_guild.decode(web::json::value::parse(json)));
    auto null_string = util::optional<std::string>::no_value();
    REQUIRE(test_guild.id == 41771983423143937);
    REQUIRE(test_guild.name == "Discord Developers");
    REQUIRE(test_guild.region == "us-east");
    REQUIRE(test_guild.icon.get_value() == "SEkgTU9NIElUUyBBTkRSRUkhISEhISEh");
    CAPTURE(test_guild.splash.get_value());
    REQUIRE(test_guild.owner_id == 80351110224678912);
    REQUIRE(test_guild.afk_channel_id.get_value()  == 42072017402331136);
    REQUIRE(test_guild.embed_channel_id.get_value()  == 41771983444115456);
    REQUIRE(test_guild.afk_timeout == 300U);
    REQUIRE(test_guild.mfa_level == disccord::mfa_level::ENABLED);
    REQUIRE(test_guild.verification_level == disccord::verification_level::LOW);
    REQUIRE(test_guild.default_message_notifications == disccord::notification_level::MENTIONS);
    REQUIRE(test_guild.embed_enabled == true);

    REQUIRE(test_guild.features[0] == "INVITE_SPLASH");

    //only testing the composites/fields that still need code coverage
    /*auto gpresc = test_guild.presences.get_value()[0]; //just going to test one value in vector for now
    REQUIRE(gpresc.game.get_value().name == "Rocket League");
    REQUIRE(gpresc.game.get_value().url.get_value() == "https://www.twitch.tv/123");
    REQUIRE(gpresc.game.get_value().type.get_value() == 1);
    REQUIRE(gpresc.guild_id == 34177198143936423);
    REQUIRE(gpresc.status == "offline");
    auto gmembs = test_guild.members.get_value()[0]; //just going to test one value in vector for now
    REQUIRE(gmembs.nick.get_value() == "NOT API SUPPORT");
    //REQUIRE(gmembs.joined_at == "2015-04-26T06:26:56.936000+00:00");
    REQUIRE(gmembs.deaf == false);
    REQUIRE(gmembs.mute == false);*/
}

TEST_CASE( "Guild Embed model correctly instantiated" ){
    guild_embed test_guild_embed;

    std::string json = R"({
    "channel_id": "38143936423417719",
    "enabled": true
})";

    REQUIRE_NOTHROW(test_guild_embed.decode(web::json::value::parse(json)));

    REQUIRE(test_guild_embed.channel_id == 38143936423417719);
    REQUIRE(test_guild_embed.enabled == true);
}

/*TEST_CASE( "Read State model correctly instantiated" ){
    read_state test_read_state;
    if (test_read_state.id != 0 && test_read_state.mention_count != 0)
    {
        FAIL("Default constructor for read state model not correctly instantiated");
    }

    std::string json = R"({
    "id": "64234381439317719",
    "mention_count": 13,
    "last_message_id": "64281439334317719"
})";

    REQUIRE_NOTHROW(test_read_state.decode(web::json::value::parse(json)));

    REQUIRE(test_read_state.id == 64234381439317719);
    REQUIRE(test_read_state.mention_count == 13);
    REQUIRE(test_read_state.last_message_id.get_value() == 64281439334317719);
}

TEST_CASE( "Relationship model correctly instantiated" ){
    relationship test_relationship;
    if (test_relationship.id != 0)
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

    REQUIRE(test_relationship.id == 64234381431771993);
    REQUIRE(test_relationship.type.get_value() == 4);
}

TEST_CASE( "Ban model correctly instantiated" ){
    ban test_ban;
    if (!test_ban.reason.empty())
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

    REQUIRE(test_ban.reason == "low quality jokes");
}*/

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
    
    auto gmemb = test_guild_memb.user.get_value();
    auto roles = test_guild_memb.roles;
    REQUIRE(test_guild_memb.deaf == false);
    //REQUIRE(test_guild_memb.joined_at == "2016-12-11T19:10:41.288000+00:00");
    REQUIRE(gmemb.username == "Disccord test bot");
    REQUIRE(gmemb.discriminator == 3071);
    REQUIRE(gmemb.bot == true);
    REQUIRE(gmemb.id == 257584807716978688);
    REQUIRE(roles[0] == 230773182120984577);
    REQUIRE(roles[1] == 257584964726423554);
    REQUIRE(test_guild_memb.mute == false);
}

/*TEST_CASE( "Application model correctly instantiated" ){
    application test_app;
    if (test_app.id != 0  && !test_app.name.empty() &&
        test_app.bot_public && test_app.bot_requires_code_grant)
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

    REQUIRE(test_app.id == 172150183260323840);
    REQUIRE(test_app.name == "Baba O-Riley");
    REQUIRE(test_app.bot_public == true);
    REQUIRE(test_app.bot_requires_code_grant == false);
    REQUIRE(test_app.description.get_value() == "Test");
    REQUIRE(test_app.rpc_origins.get_value()[0] == "WHAT");
    REQUIRE(test_app.rpc_origins.get_value()[1] == "THIS");
    REQUIRE(test_app.rpc_origins.get_value()[2] == "APPLICATION");
}*/

TEST_CASE( "Voice region model correctly instantiated" ){
    voice_region test_vr;

    std::string json = R"({
    "id": "london-1",
    "name": "London",
    "vip": true,
    "optimal": false,
    "sample_hostname": "london-1.discord-meme.com",
    "sample_port": 6969
})";

    REQUIRE_NOTHROW(test_vr.decode(web::json::value::parse(json)));

    REQUIRE(test_vr.id == "london-1");
    REQUIRE(test_vr.name == "London");
    REQUIRE(test_vr.vip == true);
    REQUIRE(test_vr.optimal == false);
    REQUIRE(test_vr.sample_hostname == "london-1.discord-meme.com");
    REQUIRE(test_vr.sample_port == 6969);
}

/*TEST_CASE( "Voice state model correctly instantiated" ){
    voice_state test_vs;
    if (test_vs.channel_id != 0 && test_vs.user_id != 0 &&
        !test_vs.session_id.empty()  && test_vs.deaf &&
        test_vs.mute && test_vs.self_deaf &&
        test_vs.self_mute && test_vs.suppress)
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

    REQUIRE(test_vs.channel_id == 157733188964188161);
    REQUIRE(test_vs.user_id == 80351110224678912);
    REQUIRE(test_vs.session_id == "90326bd25d71d39b9ef95b299e3872ff");
    REQUIRE(test_vs.deaf == false);
    REQUIRE(test_vs.mute == false);
    REQUIRE(test_vs.self_deaf == false);
    REQUIRE(test_vs.self_mute == true);
    REQUIRE(test_vs.suppress == false);
}*/
