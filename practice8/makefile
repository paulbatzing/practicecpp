# "all" is name of the default target, running "make" without params would use it
all: use namespaces calculator10

# for C++, replace CC (c compiler) with CXX (c++ compiler) which is used as default linker
CC=$(CXX)

# tell which files should be used, .cpp -> .o make would do automatically
use: my.o use.o
namespaces: namespaces.o
calculator10: calculator10.o

