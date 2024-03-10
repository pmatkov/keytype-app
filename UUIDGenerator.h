//---------------------------------------------------------------------------

#ifndef UUIDGeneratorH
#define UUIDGeneratorH
//---------------------------------------------------------------------------
#include <vcl.h>
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_generators.hpp>
#include <boost/uuid/uuid_io.hpp>

namespace UUIDGenerator {

    boost::uuids::uuid generateUUID();
    UnicodeString generateUUIDasString();

};

#endif
