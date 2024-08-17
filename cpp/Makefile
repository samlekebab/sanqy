SRC_DIR += ./ \
./lib/
TARGET = sanqy

SRCS = $(wildcard $(addsuffix src/*.cpp,$(SRC_DIR)))
SRCS += $(wildcard $(addsuffix src/*.s,$(SRC_DIR)))
OBJS = $(join $(patsubst %src/, build/obj/%,$(dir $(SRCS))),$(patsubst %, %.o, $(notdir $(SRCS))) )
DEPS = $(patsubst %, build/dep/%.d,$(notdir $(SRCS)))
HEADER_DIR = $(addsuffix header/,$(SRC_DIR) ) 
HEADER_DIR += $(addsuffix include/,$(SRC_DIR) ) 
HEADER_DIR += usr/include/
HEADER_DIR += ./lib/include/SQLiteCpp

INCLUDES = $(addprefix -I,$(HEADER_DIR) )
CCLS_INCLUDES = $(INCLUDES)
space := ${null} ${null}
${space} := ${space}
DEFS += -DDEBUG


cclsClean :
	rm -r ./.ccls-cache/

all: build/$(TARGET) .ccls

$(addprefix build/obj/,$(SRC_DIR)) : 
	mkdir -p $@

build/dep:
	mkdir -p $@

build/$(TARGET) : $(OBJS) | build/object.list
	@echo "building $(TARGET)"
	g++ -o "build/$(TARGET)" @"build/object.list"  -Wall -Wextra -Werror -L/usr/lib -lsqlite3 -lc -lm -lstdc++
	objdump -h -S build/$(TARGET) > "build/$(TARGET).list"

build/object.list : Makefile
	echo -e '\
	$(addprefix \n"./,$(addsuffix ", $(OBJS)))' > build/object.list
	mv build/object.list build/.tmp
	tail -n +3 build/.tmp > build/object.list
	rm build/.tmp
clean:
	rm -r build

.ccls : Makefile
	echo -e "\
%h -x c++-header\n\
-I\n\
$(subst ${ },\n,$(strip $(CCLS_INCLUDES)))\n\
-Wall\n\
-Wextra\n\
-Werror\n\
\n\
-DDEBUG\n\
-DUSE_HAL_DRIVER\n\
-DSTM32F407xx\n\
-DCCLS_PARSER\n\
\n\
-O0\
" > .ccls
	cp .ccls build/.tmp
#	tail -n +2 build/.tmp > .ccls
	rm build/.tmp

.SECONDEXPANSION:

$(OBJS) : build/obj/%.o : $$(dir %)src/$$(notdir %) | build/obj/$$(dir %) build/dep
	@echo "building obj $@, requiered $^"
	g++ "$<" -g3 $(DEFS) -c $(INCLUDES) -O0 -Wall -Wextra -Werror -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@"
	@echo "moving dependency in build/dep/$(notdir $*).d"
	-mv build/obj/$*.d build/dep/$(notdir $*).d

		
-include $(DEPS)
