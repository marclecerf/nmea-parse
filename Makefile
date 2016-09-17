PROJECT_ROOT   := $(shell pwd)

CXXFLAGS  := -std=c++11 -I$(PROJECT_ROOT)
LFLAGS    := -L$(PROJECT_ROOT)/common

export

SUBDIRS := plugins bin common

.PHONY: subdirs $(SUBDIRS)

subdirs: $(SUBDIRS)

all: subdirs

plugins: common

bin: plugins common

$(SUBDIRS):
	$(MAKE) -C $@

clean:
	for dir in $(SUBDIRS); do \
		$(MAKE) -C $$dir $@; \
	done
