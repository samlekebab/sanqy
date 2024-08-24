SRC_DIR += ./ \
./lib/ \
./lib/sqlite3/ 
TARGET = sanqy

SRCS = $(wildcard $(addsuffix src/*.cpp,$(SRC_DIR)))
SRCS_C = $(wildcard $(addsuffix src/*.c,$(SRC_DIR)))
SRCS +=$(wildcard $(addsuffix *.cpp,$(SRC_DIR)))
SRCS_C +=$(wildcard $(addsuffix *.c,$(SRC_DIR)))
SRCS += $(wildcard $(addsuffix src/*.s,$(SRC_DIR)))

OBJS = $(join $(patsubst %, build/obj/%,$(dir $(SRCS))),$(patsubst %, %.o, $(notdir $(SRCS))) )
OBJS_C = $(join $(patsubst %, build/obj/%,$(dir $(SRCS_C))),$(patsubst %, %.o, $(notdir $(SRCS_C))) )

DEPS = $(patsubst %, build/dep/%.d,$(notdir $(SRCS)))
DEPS += $(patsubst %, build/dep/%.d,$(notdir $(SRCS_C)))

HEADER_DIR = $(addsuffix header/,$(SRC_DIR) ) 
HEADER_DIR += $(addsuffix include/,$(SRC_DIR) ) 
HEADER_DIR += $(SRC_DIR)
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
dyn: build/lib$(TARGET).so .ccls

build/dep \
$(addprefix build/obj/,$(SRC_DIR)) \
$(addprefix build/obj/,$(addsuffix src/, $(SRC_DIR))) : 
	mkdir -p $@

build/lib$(TARGET).so : $(OBJS_C) $(OBJS) | build/object.list
	@echo "building lib$(TARGET).so"
	g++ -o "build/lib$(TARGET).so" @"build/object.list" -fPIC -shared -Wall -Wextra -Werror -L/usr/lib -lcurses -lc -lm -lstdc++
	objdump -h -S build/lib$(TARGET).so > "build/$(TARGET).list"

build/$(TARGET) :$(OBJS_C) $(OBJS) | build/object.list
	@echo "building $(TARGET)"
	g++ -o "build/$(TARGET)" @"build/object.list"  -Wall -Wextra -Werror -L/usr/lib -lcurses -lc -lm -lstdc++
	objdump -h -S build/$(TARGET) > "build/$(TARGET).list"

src.list : Makefile
	echo -e '\
	$(addprefix \n"./,$(addsuffix ", $(SRCS) $(SRCS_C)))' > src.list

h.list : Makefile
	echo -e '\
	$(addprefix \n"./,$(addsuffix ", $(HEADER_DIR) ))' > h.list

build/object.list : Makefile
	echo -e '\
	$(addprefix \n"./,$(addsuffix ", $(OBJS) $(OBJS_C)))' > build/object.list
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

$(OBJS_C) : build/obj/%.o : $$(dir %)$$(notdir %) | build/obj/$$(dir %) build/dep
	@echo "building obj $@, requiered $^"
	gcc "$<" -g3 $(DEFS) -c $(INCLUDES) -fPIC -O0 -Wall -Wextra -Werror -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@"
	@echo "moving dependency in build/dep/$(notdir $*).d"
	-mv build/obj/$*.d build/dep/$(notdir $*).d

$(OBJS) : build/obj/%.o : $$(dir %)$$(notdir %) | build/obj/$$(dir %) build/dep
	@echo "building obj $@, requiered $^"
	g++ "$<" -g3 $(DEFS) -c $(INCLUDES) -fPIC -O0 -Wall -Wextra -Werror -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@"
	@echo "moving dependency in build/dep/$(notdir $*).d"
	-mv build/obj/$*.d build/dep/$(notdir $*).d

		
-include $(DEPS)
