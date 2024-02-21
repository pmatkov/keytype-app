//---------------------------------------------------------------------------

#ifndef UUIDGeneratorH
#define UUIDGeneratorH
//---------------------------------------------------------------------------

#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_generators.hpp>
#include <boost/uuid/uuid_io.hpp>

class UUIDGenerator {

    private:
        static boost::uuids::random_generator generator;

    public:
    	static boost::uuids::uuid generateUUID();
        static UnicodeString generateUUIDasString();

};

#endif
