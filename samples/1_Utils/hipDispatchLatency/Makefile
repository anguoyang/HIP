HIP_PATH?= $(wildcard /opt/rocm/hip)
ifeq (,$(HIP_PATH))
	HIP_PATH=../../..
endif
HIPCC=$(HIP_PATH)/bin/hipcc -std=c++11

EXE=hipDispatchLatency

CXXFLAGS = -O3

all: test_kernel.code ${EXE}

$(EXE): hipDispatchLatency.cpp
	$(HIPCC) $(CXXFLAGS) hipDispatchLatency.cpp -o $@

test_kernel.code: test_kernel.cpp
	$(HIP_PATH)/bin/hipcc --genco  $(GENCO_FLAGS) $^ -o $@
clean:
	rm -f *.o $(EXE)
