AUTOMAKE_OPTIONS=foreign
bin_PROGRAMS=file_ipc

BOOST_PATH=/unixC/Boost/boost_1_58_0

#add source files
file_ipc_SOURCES=\
	IPC.h IPC.cpp Processor.cpp Processor.h Main.cpp

file_ipc_CXXFLAGS=\
	-I$(BOOST_PATH) -D_FILE_OFFSET_BITS=64 -ggdb -Wall -O0

file_ipc_LDADD=\
	-lpthread -lm -lboost_system -lboost_thread \
	-lboost_thread -lboost_program_options -lrt

file_ipc_LDFLAGS=\
	-fPIC -rdynamic -L$(BOOST_PATH)/stage/lib -pthread 
