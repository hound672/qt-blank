#!/bin/bash 

LOGFILE="report.log"

valgrind --tool=memcheck --leak-check=full -v --log-file=$LOGFILE --suppressions=val_suppression.dbg ./DUMMY

echo "--------------------------------------------------------------------"
tail -2 $LOGFILE