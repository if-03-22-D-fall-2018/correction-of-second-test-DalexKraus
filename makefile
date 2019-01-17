CC					= g++
CCLINK			= g++
LIBS				=
CCOPTIONS		= -Wall -pedantic -g
LDOPTIONS		=
HDRS				= dictionary.h test_dictionary.h general.h shortcut.h

TEST = test_dictionary
PROGRAM =

TESTOBJECT = dictionary_test_driver.o
MAINOBJECT = dictionary_main_driver.o
OBJS = general.o shortcut.o dictionary.o test_dictionary.o

DOXY            = /Applications/Doxygen/Doxygen.app/Contents/Resources/doxygen

all: $(PROGRAM)
	./$(PROGRAM)

$(TEST): $(OBJS) $(TESTOBJECT)
	$(CCLINK) -o $@ $(LDOPTIONS) $(OBJS) $(TESTOBJECT)

$(PROGRAM): $(OBJS) $(MAINOBJECT)
	$(CCLINK) -o $@ $(LDOPTIONS) $(OBJS) $(MAINOBJECT)

.PHONY: clean cleanall doxy test setsample setassignment definesample defineassignment assignmentfolder

clean:
	rm -f $(PROGRAM) $(TEST) $(TESTOBJECT) $(MAINOBJECT) $(OBJS)

cleanall:
	rm -f $(PROGRAM) $(TEST) $(TESTOBJECT) $(MAINOBJECT) $(OBJS) index.html
	rm -R html

doxy:
	$(DOXY)
	ln -s html/index.html index.html

test: $(TEST)
	./$(TEST)

#sets project as sample solution
setsample:
	cp dictionary.cpp.sample dictionary.cpp
	cp dictionary.h.sample dictionary.h

#sets project as assignment
setassignment:
	cp dictionary.cpp.assignment dictionary.cpp
	cp dictionary.h.assignment dictionary.h

# defines current state of project as sample solution
definesample:
	cp dictionary.cpp dictionary.cpp.sample
	cp dictionary.h dictionary.h.sample

# defines current sate of project as assignment
defineassignment:
	cp dictionary.cpp dictionary.cpp.assignment
	cp dictionary.h dictionary.h.assignment

# creates a folder which can serve as a publishable assignment
assignmentfolder:
	make setsample
	make doxy
	make setassignment
	mkdir ../assignment
	cp -R * ../assignment
	rm ../assignment/*.sample
	rm ../assignment/*.assignment
	make cleanall

%.o: %.cpp $(HDRS)
	$(CC) $(CCOPTIONS) -c $<
