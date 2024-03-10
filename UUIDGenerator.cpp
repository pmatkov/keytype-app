
#pragma hdrstop

#include "UUIDGenerator.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)


namespace UUIDGenerator {

    boost::uuids::random_generator generator;

    boost::uuids::uuid generateUUID()  {

        boost::uuids::uuid uuid = generator();

        return uuid;
    }

    UnicodeString generateUUIDasString()  {

        boost::uuids::uuid uuid = generator();
        std::string uuidString = boost::uuids::to_string(uuid);

        return UnicodeString(uuidString.c_str());
    }
}
