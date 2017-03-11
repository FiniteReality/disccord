#include "catch.hpp"

#include <models/user.hpp>
#include <models/embed.hpp>
#include <models/invite.hpp>
#include <models/invite_metadata.hpp>

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
        FAIL("Default constructor for invite model not correctly instantiated");
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
