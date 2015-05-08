AUTOMAKE_OPTIONS=foreign
bin_PROGRAMS=ptr_test

#define short names for bson path and boost path
BSON_PATH=/unixC/Bson/bson/src
BOOST_PATH=/unixC/Boost/boost_1_58_0

ptr_test_SOURCES=\
                   Main.cpp scoped_ptr.hpp NodeManager.cpp NodeManager.hpp  \
		   $(BSON_PATH)/bsonobj.cpp $(BSON_PATH)/util/json.cpp \
		   $(BSON_PATH)/oid.cpp $(BSON_PATH)/lib/base64.cpp \
                   $(BSON_PATH)/lib/md5.cpp $(BSON_PATH)/lib/nonce.cpp
                 

ptr_test_CXXFLAGS=\
                   -I$(BOOST_PATH) -I$(BSON_PATH) \
                   -D_FILE_OFFSET_BITS=64 -ggdb -Wall -O0

ptr_test_LDADD=\
                   -lpthread -lm -lboost_system -lboost_thread \
                    -lboost_thread -lboost_program_options -lrt

ptr_test_LDFLAGS=\
                   -fPIC -rdynamic -L$(BOOST_PATH)/stage/lib -pthread
