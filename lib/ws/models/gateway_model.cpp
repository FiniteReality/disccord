#include <iostream>

#include <bert.hpp>

#include <cpprest/streams.h>

#include <disccord/ws/models/gateway_model.hpp>

namespace disccord
{
    namespace ws
    {
        namespace models
        {
            gateway_model::gateway_model()
            { }
            gateway_model::~gateway_model()
            { }

            void gateway_model::decode(bert::value etf)
            {

            }

            bert::value gateway_model::encode_etf()
            {
                return bert::value();
            }

            void gateway_model::encode_to(bert::value &etf)
            { }
        }
    }
}

/*
namespace Concurrency
{
    namespace streams
    {
        //TODO: is this going to work?
        template<>
        pplx::task<disccord::ws::models::gateway_model> type_parser<uint8_t, disccord::ws::models::gateway_model>::parse(Concurrency::streams::streambuf<uint8_t> buf)
        {
            const size_t size = buf.size();
            std::vector<uint8_t> buffer;
            buffer.reserve(size);
            

            return buf.getn(buffer.data(), size).then([&range,size](size_t read)
            {
                assert(read == size); //TODO: better validation for this
                return bert::parse(range);
            }).then([](std::vector<bert::value> values)
            {
                for (auto& value : values)
                {
                    std::cout << "ETF type: " << value.get_type() << std::endl;
                }

                disccord::ws::models::gateway_model model;
                model.decode(values.front());

                return model;
            });
        }
    }
}
*/
