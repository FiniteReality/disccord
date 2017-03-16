#include "catch.hpp"

#include <models/user.hpp>
#include <models/embed.hpp>
#include <models/invite.hpp>
#include <models/invite_metadata.hpp>
#include <models/message.hpp>
#include <models/channel.hpp>
#include <models/connection.hpp>

#include <iostream>
#include <fstream>

#include <cstdlib>

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

    test_user.decode(web::json::value::parse(json));
    
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

    test_embed.decode(web::json::value::parse(json));

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
        "type" : "text"
    }
})";

    test_invite.decode(web::json::value::parse(json));
    
    // When splash/icon are null
    REQUIRE(test_invite.get_code() == "asdfh487yed");
    REQUIRE(test_invite.get_channel().get_value().get_id() == "165176875973476352");
    REQUIRE(test_invite.get_channel().get_value().get_name() == "illuminati");
    REQUIRE(test_invite.get_channel().get_value().get_type() == "text");
    REQUIRE(test_invite.get_guild().get_value().get_id() == "165176875973476352");
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
        "type" : "text"
    }
})";

    test_invite.decode(web::json::value::parse(json2));
    
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
    
    test_invite_md.decode(web::json::value::parse(json));
    
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
    if (!test_message.get_id().empty() && !test_message.get_channel_id().empty() && 
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

    test_message.decode(web::json::value::parse(json));
    
    REQUIRE(test_message.get_author().get_value().get_id() == 1234567890);
    REQUIRE(test_message.get_author().get_value().get_username() == "FiniteReality");
    REQUIRE(test_message.get_author().get_value().get_discriminator() == 5734);
    REQUIRE(test_message.get_author().get_value().get_bot() == false);
    REQUIRE(test_message.get_id() == "1266567890");
    REQUIRE(test_message.get_channel_id() == "9999999999");
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
    REQUIRE(mr1.get_id() == "1234567890");
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

    test_channel.decode(web::json::value::parse(dm_json));
    
    REQUIRE(test_channel.get_id() == 134552934997426176);
    REQUIRE(test_channel.get_is_private() == true);
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
    "type": "text",
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
    
    test_channel2.decode(web::json::value::parse(textguild_json));
    
    REQUIRE(test_channel2.get_id() == 41771983423143937);
    REQUIRE(test_channel2.get_is_private() == false);
    REQUIRE(test_channel2.get_last_message_id().get_value() == 155117677105512449);
    REQUIRE(test_channel2.get_topic().get_value() == "24/7 chat about how to gank Mike #2");
    REQUIRE(test_channel2.get_position().get_value() == 6);
    REQUIRE(test_channel2.get_type().get_value() == "text");
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
    "type": "voice",
    "position": 5,
    "is_private": false,
    "permission_overwrites": [],
    "bitrate": 64000,
    "user_limit": 0
})";

    test_channel3.decode(web::json::value::parse(voiceguild_json));
    
    REQUIRE(test_channel3.get_id() == 155101607195836416);
    REQUIRE(test_channel3.get_is_private() == false);
    REQUIRE(test_channel3.get_bitrate().get_value() == 64000);
    REQUIRE(test_channel3.get_user_limit().get_value() == 0);
    REQUIRE(test_channel3.get_position().get_value() == 5);
    REQUIRE(test_channel3.get_type().get_value() == "voice");
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

    test_connection.decode(web::json::value::parse(json));
    
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
    REQUIRE(accnt.get_id() == "9998");
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
    REQUIRE(accnt2.get_id() == "8889");
    REQUIRE(accnt2.get_name() == "IamNotAccount");
    REQUIRE(ig2.get_synced_at() == "2017-03-31T19:35:49.954000+00:00");

    REQUIRE(test_connection.get_id() == "13455293");
    REQUIRE(test_connection.get_name() == "FiniteReality");
    REQUIRE(test_connection.get_type() == "twitch");
    REQUIRE(test_connection.get_revoked() == true);
}
