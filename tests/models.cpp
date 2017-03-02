#include "catch.hpp"

#include <models/user.hpp>
#include <models/embed.hpp>

#include <iostream>
#include <fstream>

#include <cstdlib>

using namespace disccord::models;

//User model and User sub-model tests
TEST_CASE( "User model correctly instantiated" ){
    user test_user;
    if (!test_user.get_username().empty() && test_user.get_discriminator() != 0 && !test_user.get_bot())
    {
        FAIL("Default constructor for embed model not correctly instantiated");
    }
    web::json::value embed_obj;
    embed_obj["id"] = web::json::value("1"); //id's pass in as strings
    embed_obj["username"] = web::json::value("test_username");
    embed_obj["discriminator"] = web::json::value("4215");
    embed_obj["bot"] = web::json::value(true);
    test_user.decode(embed_obj);
    
    REQUIRE( test_user.get_username() == "test_username" );
    REQUIRE( test_user.get_discriminator() == 4215 );
    REQUIRE( test_user.get_bot() == true );
}


//Embed model and Embed sub-model tests
TEST_CASE( "Embed model correctly instantiated" ){
    
    //Embed Model
    embed test_embed;
    if (!test_embed.get_title().empty() && test_embed.get_type() != "rich" && test_embed.get_color() != 0)
    {
        FAIL("Default constructor for embed model not correctly instantiated");
    }
    web::json::value embed_obj;
    embed_obj["id"] = web::json::value("1"); //id's pass in as strings for now
    embed_obj["title"] = web::json::value("test_title");
    embed_obj["type"] = web::json::value("rich");
    embed_obj["color"] = web::json::value(4679);
    embed_obj["description"] = web::json::value("test_description");
    embed_obj["url"] = web::json::value("test_url");
    embed_obj["date"] = web::json::value("test_date");

    //Embed Sub-model: Author
    embed_author test_embed_author;
    //test default constructor here
    web::json::value author_obj;
    author_obj["id"] = web::json::value("2");
    author_obj["name"] = web::json::value("test_name");
    author_obj["url"] = web::json::value("test_url");
    author_obj["icon_url"] = web::json::value("test_icon_url");
    test_embed_author.decode(author_obj);
    
    REQUIRE(test_embed_author.get_name() == "test_name");
    REQUIRE(test_embed_author.get_url().get_value() == "test_url");
    REQUIRE(test_embed_author.get_icon_url().get_value() == "test_icon_url");
    
    //Embed Sub-model: Footer
    embed_footer test_embed_footer;
    //test default constructor here
    web::json::value footer_obj;
    footer_obj["id"] = web::json::value("3");
    footer_obj["text"] = web::json::value("test_text");
    footer_obj["icon_url"] = web::json::value("test_icon_url");
    test_embed_footer.decode(footer_obj);
	
	REQUIRE(test_embed_footer.get_text() == "test_text");
    REQUIRE(test_embed_footer.get_icon_url().get_value() == "test_icon_url");
    
    //Embed Sub-model: Image
    embed_image test_embed_image;
    //test default constructor here
    web::json::value image_obj;
    image_obj["id"] = web::json::value("4");
    image_obj["url"] = web::json::value("test_url");
    test_embed_image.decode(image_obj);
	
    REQUIRE(test_embed_image.get_url() == "test_url");
    
    //Embed Sub-model: Provider
    embed_provider test_embed_provider;
    //test default constructor here
    web::json::value provider_obj;
    provider_obj["id"] = web::json::value("5");
    provider_obj["name"] = web::json::value("test_name");
    provider_obj["url"] = web::json::value("test_url");
    test_embed_provider.decode(provider_obj);
	
	REQUIRE(test_embed_provider.get_name() == "test_name");
	REQUIRE(test_embed_provider.get_url().get_value() == "test_url");
    
    //Embed Sub-model: Thumbnail
    embed_thumbnail test_embed_thumbnail;
    //test default constructor here
    web::json::value thumbnail_obj;
    thumbnail_obj["id"] = web::json::value("6");
    thumbnail_obj["url"] = web::json::value("test_url");
    test_embed_thumbnail.decode(thumbnail_obj);
	
	REQUIRE(test_embed_thumbnail.get_url() == "test_url");
    
    //Embed Sub-model: Video
    embed_video test_embed_video;
    //test default constructor here
    web::json::value video_obj;
    video_obj["id"] = web::json::value("7");
    video_obj["url"] = web::json::value("test_url");
    test_embed_video.decode(video_obj);

	REQUIRE(test_embed_video.get_url() == "test_url");
    
    //Embed Sub-model: Field
    embed_field test_embed_field;
    //test default constructor here
    web::json::value field_obj;
    field_obj["id"] = web::json::value("8");
    field_obj["name"] = web::json::value("test_name");
    field_obj["value"] = web::json::value("test_value");
    test_embed_field.decode(field_obj);
	
	REQUIRE(test_embed_field.get_name() == "test_name");
    REQUIRE(test_embed_field.get_value() == "test_value");
	REQUIRE(test_embed_field.get_inline().get_value() == false);
    
    //build embed submodels..
    embed_obj["footer"] = footer_obj;
    embed_obj["image"] = image_obj;
    embed_obj["thumbnail"] = thumbnail_obj;
    embed_obj["video"] = video_obj;
    embed_obj["provider"] = provider_obj;
    embed_obj["author"] = author_obj;
    std::vector<web::json::value> field_array;
    field_array.push_back(field_obj);
    embed_obj["fields"] = web::json::value::array(field_array);
    
    test_embed.decode(embed_obj);

	//check all embed members
    REQUIRE( test_embed.get_title() == "test_title" );
    REQUIRE( test_embed.get_type() == "rich" );
    REQUIRE( test_embed.get_color() == 4679 );
	REQUIRE( test_embed.get_description().get_value() == "test_description" );
	REQUIRE( test_embed.get_url().get_value() == "test_url" );
	REQUIRE( test_embed.get_date().get_value() == "test_date" );

    REQUIRE( test_embed.get_fields().get_value().empty() == false );
    
    for (unsigned int i = 0; i < test_embed.get_fields().get_value().size(); i++)
    {
        std::string name = test_embed.get_fields().get_value()[i].get_name();
        INFO( "The name of the field is " << name);
        std::string value = test_embed.get_fields().get_value()[i].get_value();
        INFO( "The value of the field is " << value);
        bool vinline = test_embed.get_fields().get_value()[i].get_inline();
        INFO( "The inline of the field is " << vinline);
        
        REQUIRE(name == "test_name");
        REQUIRE(value == "test_value");
        REQUIRE(vinline == false);
    }
}
