set(controlPanelGUI_src_files
	ComboBoxMap.cpp
	controlPanel_LMS7002.cpp
	dlgAbout.cpp
	dlgConnectionManager.cpp
	dlgFloatInput.cpp
	dlgGFIR_Coefficients.cpp
	dlgMessageLog.cpp
	dlgNCOSweepTest.cpp
	dlgRegisterMap.cpp
	dlgRegisterTest.cpp
	dlgVCO_SX.cpp
	dlgVCOSweepTest.cpp
	dlgViewIRAM.cpp
	dlgViewSFR.cpp
	pnlADF.cpp
	pnlAFE.cpp
	pnlBIAS.cpp
	pnlBIST.cpp
	pnlBoard.cpp
	pnlBuffersEVB7v2.cpp
	pnlCDS.cpp
	pnlCLKGEN.cpp
	pnlFPGAControls.cpp
	pnlFreqTable.cpp
	pnlLDO.cpp
	pnlLimeLightPAD.cpp
	pnlLMS7002.cpp
	pnlMCU_BD.cpp	
	pnlMyriad7.cpp
	pnlProgramming.cpp
	pnlRBB.cpp
	pnlRFE.cpp
	pnlRxTSP.cpp
	pnlSi5351.cpp
	pnlSocketBoard.cpp
	pnlSPI.cpp
	pnlSXT.cpp
	pnlTBB.cpp
	pnlTesting.cpp
	pnlTRF.cpp
	pnlTxTSP.cpp
	pnlWFMLoader.cpp
	pnlXBUF.cpp
	pnlAlgorithms.cpp
	ResourceImagesLoader.cpp
)

add_library(controlPanelGUI STATIC ${controlPanelGUI_src_files})
target_include_directories(controlPanelGUI PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(controlPanelGUI controlLogic ${wxWidgets_LIBRARIES})

add_subdirectory(fft)
include_directories(fft)
include_directories(../controlLogic)
