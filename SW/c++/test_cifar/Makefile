CC = g++
CPPFLAGS = $(INCLUDES)
CXXFLAGS = -Wall -lpng -Wno-deprecated -O0 

LD = $(CC)
LDFLAGS = 


SRCS = $(wildcard *.cpp)
DEPS = $(SRCS:%.cpp=%.d)
OBJS = $(SRCS:%.cpp=%.o)

PROGRAM = run.x

all: $(PROGRAM)

clean: 
	-rm -f *.d *.o *.out core $(PROGRAM) trace.vcd

$(PROGRAM):	$(DEPS) $(OBJS)
		$(LD) $(LDFLAGS) $(OBJS) $(LDLIBS) -o $(PROGRAM) 2>&1 | c++filt

%.d: %.cpp
	@ echo Making dependencies for $<
	@ $(CC) -MM $(INCLUDES) $< | sed 's#: # $*.d : #1' > $@

%.o: %.cpp %.d
	$(CC) $(CPPFLAGS) $(CXXFLAGS) -c $< -o $@

# Include dependency files
ifneq ($(strip $(DEPS)),)
-include $(DEPS)
endif
