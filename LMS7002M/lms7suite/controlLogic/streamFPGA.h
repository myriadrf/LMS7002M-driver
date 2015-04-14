/**
@file 	streamFPGA.h
@author	Lime Microsystems
@brief 	Functions for configuring Stream FPGA
*/

#pragma once
class ConnectionManager;

int ConfigurePLL(ConnectionManager *serPort, const float fOutTx_MHz, const float fOutRx_MHz, const float phaseShift_deg);