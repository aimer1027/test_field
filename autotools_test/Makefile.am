AUTOMAKE_OPTIONS=foreign
bin_PROGRAMS=BitTorrent
BitTorrent_SOURCES=\
   Main.cpp \
   core.hpp  \
   /unixC/Bson/bson/src/bsonobj.cpp /unixC/Bson/bson/src/util/json.cpp \
   /unixC/Bson/bson/src/oid.cpp /unixC/Bson/bson/src/lib/base64.cpp  \
   /unixC/Bson/bson/src/lib/md5.cpp /unixC/Bson/bson/src/lib/nonce.cpp

BitTorrent_CXXFLAGS=-I/unixC/Boost/boost_1_58_0 -I/unixC/Bson/bson/src -D_FILE_OFFSET_BITS=64 \
	-ggdb -Wall -O0
BitTorrent_LDADD=-lpthread -lm -lboost_system -lboost_thread \
	-lboost_thread -lboost_program_options -lrt
BitTorrent_LDFLAGS=-fPIC -rdynamic -L/unixC/Boost/boost_1_58_0/stage/lib -pthread
  
