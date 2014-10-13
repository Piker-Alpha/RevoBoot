clear
#
# Check argument for Mac model.
#
if [[ "$1" =~ [iMac|Mac] ]];
  then
    #
    # Use specified MacModelNN from argument.
    #
    make MODEL=$1
  else
    #
    # Check RevoBoot/MODEL for default model.
    #
    if [ -f MODEL ];
      then
        #
        # Get MacModelNN from MODEL (assuming it to be correct).
        #
        make MODEL=`cat MODEL`
      else
        #
        # No default model found. Create MODEL file for future use.
        #
        echo "Macmini62" > MODEL
        #
        # Use Macmini62 as our default (matches settings-template.h)
        #
        make MODEL=Macmini62
  fi;
fi

