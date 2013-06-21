objects:=*.o
cc=gcc
source=*.cpp

compile:$(objects)
	$(cc) -o compile $(objects)

%.d:%.cpp
	@set -e; rm -f $@; \
	$(cc) -M $< >; $@.$$$$; \
	sed 's,\($*\)\.o[ :]*,\1.o $@ : ,g' < $@.$$$$ >; $@; \
	rm -f $@.$$$$

include $(sources:.cpp=.d)

.PHONY:clean
clean:
	rm compile $(objects)
