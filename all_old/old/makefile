# These directories specify where source code files are located.
# Edit these variables if more directories are needed.  
# Separate each entry by spaces.
#SHARED_SRC_DIRS:=$(CURDIR) src gen_src
SHARED_SRC_DIRS:=src src/liborangepower_src gen_src
CXX_DIRS:=$(SHARED_SRC_DIRS)
C_DIRS:=$(SHARED_SRC_DIRS)
S_DIRS:=$(SHARED_SRC_DIRS)
# NASM Source Directories
# Note:  NS is a prefix for NASM in all cases
NS_DIRS:=$(SHARED_SRC_DIRS)

# End of source directories


# Comment out or un-comment out the next line to enable debugging stuff to
# be generated
#DEBUG:=yeah do debug

DEBUG_OPTIMIZATION_LEVEL:=-O0
REGULAR_OPTIMIZATION_LEVEL:=-O2

NUM_JOBS:=8

ALWAYS_DEBUG_SUFFIX:=_debug
ifdef DEBUG
	DEBUG_SUFFIX:=$(ALWAYS_DEBUG_SUFFIX)
endif

# This is the name of the output file.  Change this if needed!
PROJ:=$(shell basename $(CURDIR))$(DEBUG_SUFFIX)


# This is used for do_asmouts
#VERBOSE_ASM_FLAG:=-fverbose-asm


# Compilers and initial compiler flags
CXX:=$(PREFIX)g++
CXX_FLAGS:=$(CXX_FLAGS) -std=c++17 -Wall \
	$(shell pkg-config --cflags jsoncpp)

CC:=$(PREFIX)gcc
C_FLAGS:=$(C_FLAGS) -std=c11 -Wall

AS:=$(PREFIX)as
S_FLAGS:=$(S_FLAGS) -mnaked-reg #-msyntax=intel

NS:=nasm
NS_FLAGS:=$(NS_FLAGS) -f elf64

OBJDUMP:=$(PREFIX)objdump
LD:=$(CXX)

# Initial linker flags
LD_FLAGS:=$(LD_FLAGS) -lm -ljsoncpp



ifdef DEBUG
	EXTRA_DEBUG_FLAGS:=-g
	DEBUG_FLAGS:=-gdwarf-3 $(EXTRA_DEBUG_FLAGS)
	EXTRA_LD_FLAGS:=$(DEBUG_FLAGS)
	OPTIMIZATION_LEVEL:=$(DEBUG_OPTIMIZATION_LEVEL)
else
	OPTIMIZATION_LEVEL:=$(REGULAR_OPTIMIZATION_LEVEL)
endif






FINAL_BASE_FLAGS:=$(OPTIMIZATION_LEVEL) \
	$(EXTRA_BASE_FLAGS) $(EXTRA_DEBUG_FLAGS)

# Final compiler and linker flags
CXX_FLAGS:=$(CXX_FLAGS) $(FINAL_BASE_FLAGS)
C_FLAGS:=$(C_FLAGS) $(FINAL_BASE_FLAGS)
LD_FLAGS:=$(LD_FLAGS) $(EXTRA_LD_FLAGS) $(COMMON_LD_FLAGS)




# Generated directories
OBJDIR:=objs$(DEBUG_SUFFIX)
ASMOUTDIR:=asmouts$(DEBUG_SUFFIX)
DEPDIR:=deps$(DEBUG_SUFFIX)
PREPROCDIR:=preprocs$(DEBUG_SUFFIX)

# Directories to search, specified at the top of this file
export VPATH	:=	\
	$(foreach DIR,$(CXX_DIRS),$(CURDIR)/$(DIR)) \
	$(foreach DIR,$(C_DIRS),$(CURDIR)/$(DIR)) \
	$(foreach DIR,$(S_DIRS),$(CURDIR)/$(DIR)) \
	$(foreach DIR,$(NS_DIRS),$(CURDIR)/$(DIR)) \


CXX_SOURCES:=$(foreach DIR,$(CXX_DIRS),$(notdir $(wildcard $(DIR)/*.cpp)))
CXX_OFILES:=$(CXX_SOURCES:%.cpp=$(OBJDIR)/%.o) 
CXX_PFILES:=$(CXX_SOURCES:%.cpp=$(DEPDIR)/%.P) 
 
# Assembly source code generated by gcc/g++
CXX_ASMOUTS:=$(CXX_SOURCES:%.cpp=$(ASMOUTDIR)/%.s)


C_SOURCES:=$(foreach DIR,$(C_DIRS),$(notdir $(wildcard $(DIR)/*.c)))
C_OFILES:=$(C_SOURCES:%.c=$(OBJDIR)/%.o) 
C_PFILES:=$(C_SOURCES:%.c=$(DEPDIR)/%.P) 
 
# Assembly source code generated by gcc/g++
C_ASMOUTS:=$(C_SOURCES:%.c=$(ASMOUTDIR)/%.s)


S_SOURCES:=$(foreach DIR,$(S_DIRS),$(notdir $(wildcard $(DIR)/*.s)))
S_OFILES:=$(S_SOURCES:%.s=$(OBJDIR)/%.o) 
S_PFILES:=$(S_SOURCES:%.s=$(DEPDIR)/%.P) 
 

NS_SOURCES:=$(foreach DIR,$(S_DIRS),$(notdir $(wildcard $(DIR)/*.nasm)))
NS_OFILES:=$(NS_SOURCES:%.nasm=$(OBJDIR)/%.o) 
NS_PFILES:=$(NS_SOURCES:%.nasm=$(DEPDIR)/%.P) 
 

# Compiler-generated files
# OFILES are object code files (extension .o)
OFILES:=$(CXX_OFILES) $(C_OFILES) $(S_OFILES) $(NS_OFILES) 
# PFILES are used for automatic dependency generation
PFILES:=$(CXX_PFILES) $(C_PFILES) $(S_PFILES) $(NS_PFILES) 
ASMOUTS:=$(CXX_ASMOUTS) $(C_ASMOUTS)

# Preprocessed output of only C++ files
CXX_EFILES:=$(CXX_SOURCES:%.cpp=$(PREPROCDIR)/%.E)
EFILES:=$(CXX_EFILES)


MODIFED_GENERATED_SOURCES:=gen_src/grammar.tab.cpp
FINAL_GENERATED_SOURCES:=gen_src/lex.yy.c gen_src/grammar.tab.hh
GENERATED_SOURCES:=$(MODIFED_GENERATED_SOURCES) \
	$(FINAL_GENERATED_SOURCES)

all : all_pre $(MODIFED_GENERATED_SOURCES)
	@make -j$(NUM_JOBS) final_generated

final_generated : all_pre $(FINAL_GENERATED_SOURCES)
	@make -j$(NUM_JOBS) non_generated

non_generated : all_pre $(OFILES)
	$(LD) $(OBJDIR)/*.o -o $(PROJ) $(LD_FLAGS)

# all_objs is ENTIRELY optional.
all_objs : all_pre $(OFILES)
	@#

do_asmouts : all_pre all_pre_asmout $(ASMOUTS)
	@#

all_pre :
	mkdir -p $(OBJDIR) $(DEPDIR) gen_src

all_pre_asmout :
	mkdir -p $(ASMOUTDIR)




gen_src/lex.yy.c : src/lexicals.l
	cd src && flex lexicals.l && mv lex.yy.c ../gen_src/lex.yy.c

gen_src/grammar.tab.cpp : src/grammar.yy src/misc_bison_stuff.hpp
	cd src && bison -d grammar.yy \
	&& find . -type f -iname "grammar.tab.cc" -print0 \
	| xargs -0 sed -i 's/grammar\.tab\.cc/grammar.tab.cpp/g' \
	&& mv grammar.tab.cc ../gen_src/grammar.tab.cpp
gen_src/grammar.tab.hh : src/grammar.yy src/misc_bison_stuff.hpp
	mv src/grammar.tab.hh gen_src/grammar.tab.hh

# Here's where things get really messy.
$(CXX_OFILES) : $(OBJDIR)/%.o : %.cpp 
	@#echo "Generating dependency information for "$@"...." 
	@echo $@" was updated or has no object file.  (Re)Compiling...." 
	$(CXX) $(CXX_FLAGS) -MMD -c $< -o $@ 
	@cp $(OBJDIR)/$*.d $(DEPDIR)/$*.P 
	@#$(sed_script) < $(OBJDIR)/$*.d >> $(DEPDIR)/$*.P 
	@rm -f $(OBJDIR)/$*.d


$(C_OFILES) : $(OBJDIR)/%.o : %.c 
	@#echo "Generating dependency information for "$@"...." 
	@echo $@" was updated or has no object file.  (Re)Compiling...." 
	$(CC) $(C_FLAGS) -MMD -c $< -o $@ 
	@cp $(OBJDIR)/$*.d $(DEPDIR)/$*.P 
	@#$(sed_script) < $(OBJDIR)/$*.d >> $(DEPDIR)/$*.P 
	@rm -f $(OBJDIR)/$*.d

# For NASM sources, the dependency generation is somewhat different from
# that of C/C++ sources.
$(NS_OFILES) : $(OBJDIR)/%.o : %.nasm
	@#echo "Generating dependency information for "$@"...."
	@echo $@" was updated or has no object file.  (Re)Assembling...."
	$(NS) $(NS_FLAGS) $< -o $@ -MD $(DEPDIR)/$*.P

$(S_OFILES) : $(OBJDIR)/%.o : %.s
	@#echo "Generating dependency information for "$@"...."
	@echo $@" was updated or has no object file.  (Re)Assembling...."
	$(AS) $(S_FLAGS) -MD $(OBJDIR)/$*.d -c $< -o $@
	@cp $(OBJDIR)/$*.d $(DEPDIR)/$*.P
	@#$(sed_script) < $(OBJDIR)/$*.d >> $(DEPDIR)/$*.P
	@rm -f $(OBJDIR)/$*.d


# Here we have stuff for outputting assembly source code instead of an object file.

$(CXX_ASMOUTS) : $(ASMOUTDIR)/%.s : %.cpp 
	@#$(CXX) $(CXX_FLAGS) -MMD -S -fverbose-asm $< -o $@ 
	@#$(CXX) $(CXX_FLAGS) -MMD -S $< -o $@ 
	$(CXX) $(CXX_FLAGS) -MMD -S $(VERBOSE_ASM_FLAG) $< -o $@ 
	@cp $(ASMOUTDIR)/$*.d $(DEPDIR)/$*.P 
	@#$(sed_script) < $(ASMOUTDIR)/$*.d >> $(DEPDIR)/$*.P 
	@rm -f $(ASMOUTDIR)/$*.d


$(C_ASMOUTS) : $(ASMOUTDIR)/%.s : %.c 
	@#$(CC) $(C_FLAGS) -MMD -S -fverbose-asm $< -o $@ 
	@#$(CC) $(C_FLAGS) -MMD -S $< -o $@ 
	$(CC) $(C_FLAGS) -MMD -S $(VERBOSE_ASM_FLAG) $< -o $@ 
	@cp $(ASMOUTDIR)/$*.d $(DEPDIR)/$*.P 
	@#$(sed_script) < $(ASMOUTDIR)/$*.d >> $(DEPDIR)/$*.P 
	@rm -f $(ASMOUTDIR)/$*.d

-include $(PFILES)


only_preprocess : only_preprocess_pre $(EFILES)
	@#

only_preprocess_pre : 
	mkdir -p $(DEPDIR) $(PREPROCDIR)


#$(CXX_EFILES) : $(PREPROCDIR)/%.E : %.cpp
$(CXX_EFILES) : $(PREPROCDIR)/%.E : %.cpp
	$(CXX) $(CXX_FLAGS) -MMD -E $< -o $@
	@cp $(PREPROCDIR)/$*.d $(DEPDIR)/$*.P
	@#$(sed_script) < $(PREPROCDIR)/$*.d >> $(DEPDIR)/$*.P
	@rm -f $(PREPROCDIR)/$*.d


#¯\(°_o)/¯

.PHONY : clean
clean :
	rm -rfv $(OBJDIR) $(DEPDIR) $(ASMOUTDIR) $(PREPROCDIR) $(PROJ) tags *.taghl gmon.out $(GENERATED_SOURCES)

# Flags for make disassemble*
DISASSEMBLE_FLAGS:=$(DISASSEMBLE_BASE_FLAGS) -C -d 
DISASSEMBLE_ALL_FLAGS:=$(DISASSEMBLE_BASE_FLAGS) -C -D 

DISASSEMBLE_2_FLAGS:=$(DISASSEMBLE_BASE_FLAGS) -C -S -l -d 
DISASSEMBLE_ALL_2_FLAGS:=$(DISASSEMBLE_BASE_FLAGS) -C -S -l -D 

.PHONY : disassemble
disassemble :
	$(OBJDUMP) $(DISASSEMBLE_FLAGS) $(PROJ)

.PHONY : disassemble_all
disassemble_all :
	$(OBJDUMP) $(DISASSEMBLE_ALL_FLAGS) $(PROJ)


.PHONY : disassemble_2
disassemble_2 :
	$(OBJDUMP) $(DISASSEMBLE_2_FLAGS) $(PROJ)

.PHONY : disassemble_all_2
disassemble_all_2 :
	$(OBJDUMP) $(DISASSEMBLE_ALL_2_FLAGS) $(PROJ)
