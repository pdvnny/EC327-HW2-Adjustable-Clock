# This Makefile
# gives instructions to the command
# make
# about how and whether to build programs
#
# The syntax is

# thingtobuld:  what-it-needs-or-depends-on
#    instructions on how to build it
#

# make uses the modification dates to determine
# is the programs need to be re-built

all: ac ac_debug

ac: adjustableclock.cpp
	g++ adjustableclock.cpp -o ac -lsfml-graphics -lsfml-window -lsfml-system


ac_debug: adjustableclock.cpp
	g++ adjustableclock.cpp -g -o ac_debug -lsfml-graphics -lsfml-window -lsfml-system