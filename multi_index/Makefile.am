AUTOMAKE_OPTIONS=foreign
bin_PROGRAMS=multi_index_demo
BOOST_LIB_PATH=/unixC/Boost/boost_1_58_0

#what source files multi_index_demo need ?

multi_index_demo_SOURCES=\
	multi_index_demo.cpp 

multi_index_demo_CXXFLAGS=\
	-I$(BOOST_LIB_PATH) -D_FILE_OFFSET_BITS=64 \
	-ggdb -Wall -O0

multi_index_demo_LDADD=\
	-lpthread -lm -lboost_system -lboost_thread \
	-lboost_program_options -lrt

multi_index_demo_LDFLAGS=\
	-fPIC -rdynamic -L$(BOOST_LIB_PATH)/stage/lib -pthread
