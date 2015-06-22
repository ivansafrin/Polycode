#/bin/sh -f
 
# things to do for travis-ci in the before_install section
 
if ( test "`uname -s`" = "Darwin" )
then
  #cmake v2.8.12 is installed on the Mac workers now
  #brew update
  #brew install cmake
  echo
else
  #install a newer cmake since at this time Travis only has version 2.8.7
  echo "yes" | sudo add-apt-repository ppa:kalakris/cmake
  sudo apt-get update -qq
  sudo apt-get install cmake libsdl1.2-dev python-ply
fi
