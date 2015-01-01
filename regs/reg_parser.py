########################################################################
## Parse the LMS7002M register map (text dump from pdf)
## and create usable C structures and enum definitions
########################################################################

import sys
import os
import re
import json
from Cheetah.Template import Template

def get_name(reg, field_name):
    #TODO optional reg[name]
    reg_name = reg['addr'].lower()
    field = reg['fields'][field_name]
    return 'reg_' + reg_name + '_' + field_name.lower()

def get_default(reg):
    if 'default' in reg:
        return hex(eval('0b'+reg['default'].replace(' ', '')))
    return 0

def get_options(reg, field_name):
    field = reg['fields'][field_name]
    if 'options' in field:
        return [(('%s_%s'%(get_name(reg, field_name), k)).upper(), v) for k,v in field['options'].iteritems()]
    return None

def get_shift_mask(reg, field_name):
    field = reg['fields'][field_name]
    bits = field['bits']
    if ':' in bits:
        low, high = sorted(map(int, bits.split(':')))
        mask = hex(eval('0b'+('1'*(high-low+1))))
        return low, mask
    return int(bits), "0x1"

TMPL="""
///
/// \\file LMS7002M/LMS7002M_regs.h
///
/// Register address and field shift constants for LMS7002M.
///
/// \\copyright
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

//! enumerated values for some registers
#for $reg in $regs
#for $field_name in sorted($reg.fields.keys()):
#if $get_options($reg, $field_name)
#for $k,$v in $get_options($reg, $field_name)
\#define $k $v
#end for;
#end if
#end for
#end for

struct LMS7002M_regs_struct
{
    #for $reg in $regs
    #for $field_name in sorted($reg.fields.keys()):
    int $get_name($reg, $field_name);
    #end for
    #end for
};

/***********************************************************************
 * Implementation details below
 **********************************************************************/

static inline void LMS7002M_regs_init(LMS7002M_regs_t *regs)
{
    #for $reg in $regs
    LMS7002M_regs_set(regs, $reg.addr, $get_default($reg));
    #end for
}

static inline void LMS7002M_regs_set(LMS7002M_regs_t *regs, const int addr, const int value)
{
    #for $reg in $regs
    if (addr == $reg.addr)
    {
        #for $field_name in sorted($reg.fields.keys())
        #set $shift, $mask = $get_shift_mask($reg, $field_name)
        regs->$get_name($reg, $field_name) = (value >> $shift) & $mask;
        #end for
        return;
    }
    #end for
}

static inline int LMS7002M_regs_get(LMS7002M_regs_t *regs, const int addr)
{
    int value = 0;
    #for $reg in $regs
    if (addr == $reg.addr)
    {
        #for $field_name in sorted($reg.fields.keys())
        #set $shift, $mask = $get_shift_mask($reg, $field_name)
        value |= (regs->$get_name($reg, $field_name) & $mask) << $shift;
        #end for
    }
    #end for
    return value;
}

"""

if __name__ == '__main__':
    regs = list()
    for arg in sys.argv[1:]:
        regs.extend(json.loads(open(arg).read()))
    regs = sorted(regs, key=lambda x: eval(x['addr']))

    code = str(Template(TMPL, dict(
        regs=regs,
        get_name=get_name,
        get_default=get_default,
        get_options=get_options,
        get_shift_mask=get_shift_mask,
    )))

    print code
