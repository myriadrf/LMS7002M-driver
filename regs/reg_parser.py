########################################################################
## Parse the LMS7002M register map (text dump from pdf)
## and create usable C structures and enum definitions
########################################################################

import sys
import os
import re
import json
from Cheetah.Template import Template

def get_name(reg):
    pass

TMPL="""
///
/// \file LMS7002M/LMS7002M_regs.h
///
/// Register address and field shift constants for LMS7002M.
///
/// \copyright
/// Copyright (c) 2014-2015 Fairwaves, Inc.
/// Copyright (c) 2014-2015 Rice University
/// SPDX-License-Identifier: Apache-2.0
/// http://www.apache.org/licenses/LICENSE-2.0
///

//------ this is a generated file, do not edit --------//

#pragma once

struct LMS7002M_regs_struct;
typedef struct LMS7002M_regs_struct LMS7002M_regs_t;

//! initialize a register structure with default values
static inline void LMS7002M_regs_init(LMS7002M_regs_t *regs);

//! set the fields from the value that belong to the register specified by addr
static inline void LMS7002M_regs_set(LMS7002M_regs_t *regs, const int addr, const int value);

//! get the value of the register specified by the fields at the given address
static inline int LMS7002M_regs_get(LMS7002M_regs_t *regs, const int addr);

struct LMS7002M_regs_struct
{
    #for $reg in $regs
    
    #end for
};

static inline void LMS7002M_regs_init(LMS7002M_regs_t *regs)
{

}

static inline void LMS7002M_regs_set(LMS7002M_regs_t *regs, const int addr, const int value)
{

}

static inline int LMS7002M_regs_get(LMS7002M_regs_t *regs, const int addr)
{

}

"""

if __name__ == '__main__':
    regs = json.loads(open(sys.argv[1]).read())

    code = str(Template(TMPL, dict(
        regs=regs,
        get_name=get_name,
    )))

    print code
