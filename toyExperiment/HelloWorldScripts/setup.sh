#! /bin/bash
#
# 1) Make a symlink to the directory that holds the input files.
# 2) Make an output directory. There are two options:
#    a) Make it in ${ART_WORKBOOK_OUTPUT_BASE} and sym link to it.
#    b) Make it is a real subdirectory of cwd.
#

if [ -z "$TOYEXPERIMENT_DIR" ]; then
  echo "You cannot run this script until the toyExperiment ups product has been setup."
  return 1
fi

inputLink="inputFiles"
inputDir=${TOYEXPERIMENT_DIR}/inputFiles
if [ -e ${inputDir} ]; then
  if [ -e ${inputLink} ]; then
    if [ ! -l ${inputLink} ]; then
      echo "${inputLink} exists but is not a link."
      echo "Please rename/remove it and rerun this script"
      exit 1
    fi
  fi
  ln -s ${inputDir} ${inputLink}
fi

# The name of the output directory; either a real directory or a symlink to one.
outputName="output"

# Ensure that the the output directory or symlink exists.
if [ -n "${ART_WORKBOOK_OUTPUT_BASE}" ]; then

  # Case 1: make output directory in ART_WORKBOOK_OUTPUT_BASE and symlink to it.
  export ART_WORKBOOK_OUTPUT=${ART_WORKBOOK_OUTPUT_BASE}/$(whoami)/art_workbook_output
  if [ ! -e $ART_WORKBOOK_OUTPUT ]; then
    mkdir -p ${ART_WORKBOOK_OUTPUT}
  fi
  if [ ! -d ${ART_WORKBOOK_OUTPUT} ]; then
    echo "Error making the output directory " ${ART_WORKBOOK_OUTPUT}
    echo "There is already a file with that name and it is not a directory."
    echo "Please rename/remove this file and rerun this script"
    exit 1
  fi
  ln -s ${ART_WORKBOOK_OUTPUT} ${outputName}

else

  # Case 2: make the directory in cwd.
  if [ ! -e ${outputName} ]; then
    mkdir ${outputName}
  fi
  if [ ! -d  ${outputName} ]; then
    echo "Error making the output directory " ${outputName}
    echo "There is already a file with that name and it is not a directory."
    echo "Please rename/remove this file and rerun this script"
    exit 1
  fi

fi
