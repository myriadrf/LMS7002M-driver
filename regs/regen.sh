#!/bin/bash
DIR="$( cd "$( dirname "$0" )" && pwd )"
set -x #echo on
python ${DIR}/reg_parser.py ${DIR}/raw_regs.json  > ${DIR}/../include/LMS7002M/LMS7002M_regs.h
