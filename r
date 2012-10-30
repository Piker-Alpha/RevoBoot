clear
make clean
#
# Check argument for Mac model.
#
if [[ "$1" =~ [iMac|Mac] ]];
  then
    #
    # Use specified MacModelNN from argument.
    #
    make MODEL=$1 > out.log
  else
    #
    # Check RevoBoot/MODEL for default model.
    #
    if [ -f MODEL ]; then
      #
      # Get MacModelNN from MODEL (assuming it to be correct).
      #
      make MODEL=`cat MODEL` > out.log
    else
      #
      # No default model found.
      #
      make > out.log
    fi;
fi

