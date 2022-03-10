SHELL := bash


export CAPNP_INCLUDE_PATH = $(abspath $(dir $(shell which capnp))/../include)

.DEFAULT: release

export CXXFLAGS+=-DCAPNP_INCLUDE_PATH=$(CAPNP_INCLUDE_PATH)
export CXXFLAGS+=--std=c++20 -rdynamic

export LIBS = \
  -lcapnpc -lcapnp-rpc -lcapnp \
  -lcapnp-json \
  -lkj-http -lkj-async -lkj \
  -lpthread \
  -lgtest_main -lgtest


NIX_BUILD_CORES ?= 4
EKAM := nice ekam
EKAM_FLAGS := -j $(NIX_BUILD_CORES) -l 200


debug debug-continuous: export CXXFLAGS+=-ggdb3 -O0 -U_FORTIFY_SOURCE
release release-continuous: export CXXFLAGS+=-O2 -DNDEBUG

debug-continuous release-continuous: export EKAM_FLAGS+=-c

debug debug-continuous release release-continuous:
	$(EKAM) $(EKAM_FLAGS)

clean:
	rm -fr bin tmp

.PHONY: clean all

.DEFAULT: release
