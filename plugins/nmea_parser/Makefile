LFLAGS+= -dynamiclib -flat_namespace

CC_FILES := $(wildcard *.cc)
SO_FILES := $(CC_FILES:.cc=.so)

all: $(SO_FILES)

%.so: %.cc
	$(CXX) $(CXXFLAGS) $(LFLAGS) -o $@ $<

clean:
	rm -f *.so
