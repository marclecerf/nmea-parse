LDFLAGS += -L/usr/local/lib
LDLIBS += -dynamiclib -flat_namespace -lprotobuf

PBCXX  := protoc
PBMETA := $(wildcard *.proto)
PBSRCS := $(PBMETA:.proto=.pb.cc)
PBHDRS := $(PBMETA:.proto=.pb.h)

SRCS   := $(sort $(PBSRCS) $(wildcard *.cc))
OBJS   := $(SRCS:.cc=.o)
HDRS   := $(wildcard *.h)

LIBSO  := libcommon.so

all: $(LIBSO)

$(LIBSO): $(OBJS)
	$(CXX) -o $@ $^ $(LDFLAGS) $(LDLIBS)

%.o: %.cc
	$(CXX) $(CXXFLAGS) -c -o $@ $<

$(PBSRCS): $(PBMETA)
	$(PBCXX) --proto_path=. --cpp_out=. $(PBMETA)

clean:
	rm -f *.so $(PBSRCS) $(PBHDRS) $(OBJS)
