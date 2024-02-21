//---------------------------------------------------------------------------

#pragma hdrstop

#include "UUIDGenerator.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)

boost::uuids::random_generator UUIDGenerator::generator;

boost::uuids::uuid UUIDGenerator::generateUUID()  {

	boost::uuids::uuid uuid = generator();

   	return uuid;
}

UnicodeString UUIDGenerator::generateUUIDasString()  {

	boost::uuids::uuid uuid = generator();
    std::string uuidString = boost::uuids::to_string(uuid);

   	return UnicodeString(uuidString.c_str());
}
