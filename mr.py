#!/usr/bin/python3.6

##########################################################################
# This program is used to run other programs a number of times. The name 
# of the program to run is the argumnet to this program. Assuming that 
# this file is named mr.py you need to make sure that it is executable
# with:
#   chmod a+x mr.py

# You can use it to run a.out 10 times:
#   ./mr.py ./passwordCrack

# If you want it to run a different number of times, just change the loop.
# This program would benefit from checking that the correct number of 
# command line arguments have been passed in and a a second argument for
# defining the number of times to run. The alterations are left as an 
# exercise.
##########################################################################

import sys 
from subprocess import call

for i in range(0, 10):
  call(sys.argv[1])






























