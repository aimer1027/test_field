AUTOMAKE_OPTIONS=foreign
bin_PROGRAMS=message_sender_server

BSON_PATH=/unixC/Bson/bson/src
BOOST_PATH=/unixC/Boost/boost_1_58_0

message_sender_server_SOURCES=\
      server.cpp \
      $(BSON_PATH)/bsonobj.cpp $(BSON_PATH)/util/json.cpp \
      $(BSON_PATH)/oid.cpp $(BSON_PATH)/lib/base64.cpp \
      $(BSON_PATH)/lib/md5.cpp $(BSON_PATH)/lib/nonce.cpp

message_sender_server_CXXFLAGS=\
      -I$(BOOST_PATH) -I$(BSON_PATH) -D_FILE_OFFSET_BITS=64 \
      -ggdb -Wall -O0

message_sender_server_LDADD=\
       -lpthread -lm -lboost_system -lboost_thread \
       -lboost_thread -lboost_program_options -lrt 
       
message_sender_server_LDFLAGS=\
       -fPIC -rdynamic -L$(BOOST_PATH)/stage/lib -pthread
