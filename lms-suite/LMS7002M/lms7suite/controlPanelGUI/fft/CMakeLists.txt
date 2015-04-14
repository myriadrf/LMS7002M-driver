set(fftviewer_src_files
	dlgExtraControls.cpp
	FFTcalculator.cpp
	PlotUpdateThread.cpp
	pnlFFTviewer.cpp
	SamplesCollector.cpp
	UnitsButton.cpp
	kiss_fft.c
)

add_subdirectory(oglGraph)
include_directories(../.)

set(USE_FFTW OFF CACHE BOOL "Use libFFTW3 for calculations")
if(USE_FFTW)
	find_package(FFTW3 REQUIRED)
	include_directories(${FFTW3_INCLUDE_DIRS})
	LINK_DIRECTORIES(${FFTW3_LIBRARIES})
endif()

add_library(fftviewer STATIC ${fftviewer_src_files})
target_include_directories(fftviewer PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(fftviewer controlLogic oglGraph)
if(USE_FFTW)
	target_link_libraries(fftviewer ${FFTW3_LIBRARIES})
endif()
