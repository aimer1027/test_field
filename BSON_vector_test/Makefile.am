AUTOMAKE_OPTIONS=foreign
bin_PROGRAMS=Bson_Vector_test
BSON_SRC_PATH=/unixC/Bson/bson/src
BOOST_LIB_PATH=/unixC/Boost/boost_1_58_0

#what source files  Bson_Vector_test needs ?
Bson_Vector_test_SOURCES=\
   bson_vector_test.cpp \
   $(BSON_SRC_PATH)/bsonobj.cpp $(BSON_SRC_PATH)/util/json.cpp \
   $(BSON_SRC_PATH)/oid.cpp $(BSON_SRC_PATH)/lib/base64.cpp \
   $(BSON_SRC_PATH)/lib/md5.cpp $(BSON_SRC_PATH)/lib/nonce.cpp 


Bson_Vector_test_CXXFLAGS=\
       -I$(BOOST_LIB_PATH) -I$(BSON_SRC_PATH) -D_FILE_OFFSET_BITS=64 \
       -ggdb -Wall -O0


Bson_Vector_test_LDADD=\
       -lpthread -lm -lboost_system -lboost_thread \
       -lboost_thread -lboost_program_options -lrt

Bson_Vector_test_LDFLAGS=\
        -fPIC -rdynamic -L$(BOOST_LIB_PATH)/stage/lib -pthread    
