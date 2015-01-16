# LMS7002M register definitions generator

This directory contains a set of JSON files, each describing a register section in the LMS7002M.
These JSON files are used with the reg_parser.py python script to generate the LMS7002M_regs.h C wrapper.

## Motivation

Encoding the correct shift and masks over 100s of registers can be error prone.
The generated register structure creates an unpacked view of the register space.
Each individual register field can be read/written as a normal integer in C.
When accessing a particular address, the wrapper takes care of the packing
and unpacking the various register fields with the correct bit shifting and masking.
Also, this approach provides a generic way to shadow register fields in the host,
which can be used to avoid unnecessary SPI traffic and read/modify/write paradigm.

## Making changes

Please dont modify LMS7002M_regs.h directly!

* Missing a register section? create a new JSON register file.
* Missing a register in a section? add it to the existing JSON file.
* Missing a field in a register? add it to the existing JSON file.
* Missing field's enumerated options? add it to the existing JSON file.

After making changes to the JSON files, simply run the regen.sh script.

