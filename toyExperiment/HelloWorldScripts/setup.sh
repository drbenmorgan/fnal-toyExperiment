#! /bin/bash

# Find input files here.
ln -s $TOYEXPERIMENT_DIR/inputFiles .

# Put output files here
export ART_WORKBOOK_OUTPUT=${ART_WORKBOOK_OUTPUT_BASE}/$(whoami)/art_workbook_output
mkdir -p ${ART_WORKBOOK_OUTPUT}
ln -s ${ART_WORKBOOK_OUTPUT} output

