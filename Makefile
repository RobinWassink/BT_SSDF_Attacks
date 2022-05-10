# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.7

# Default target executed when no arguments are given to make.
default_target: all

.PHONY : default_target

# Allow only one "make -f Makefile2" at a time, but pass parallelism.
.NOTPARALLEL:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /root/sensor-robin

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /root/sensor-robin

#=============================================================================
# Targets provided globally by CMake.

# Special rule for the target install/local
install/local: preinstall
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Installing only the local directory..."
	/usr/bin/cmake -DCMAKE_INSTALL_LOCAL_ONLY=1 -P cmake_install.cmake
.PHONY : install/local

# Special rule for the target install/local
install/local/fast: install/local

.PHONY : install/local/fast

# Special rule for the target install
install: preinstall
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Install the project..."
	/usr/bin/cmake -P cmake_install.cmake
.PHONY : install

# Special rule for the target install
install/fast: preinstall/fast
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Install the project..."
	/usr/bin/cmake -P cmake_install.cmake
.PHONY : install/fast

# Special rule for the target list_install_components
list_install_components:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Available install components are: \"Unspecified\""
.PHONY : list_install_components

# Special rule for the target list_install_components
list_install_components/fast: list_install_components

.PHONY : list_install_components/fast

# Special rule for the target rebuild_cache
rebuild_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Running CMake to regenerate build system..."
	/usr/bin/cmake -H$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR)
.PHONY : rebuild_cache

# Special rule for the target rebuild_cache
rebuild_cache/fast: rebuild_cache

.PHONY : rebuild_cache/fast

# Special rule for the target package
package: preinstall
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Run CPack packaging tool..."
	/usr/bin/cpack --config ./CPackConfig.cmake
.PHONY : package

# Special rule for the target package
package/fast: package

.PHONY : package/fast

# Special rule for the target package_source
package_source:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Run CPack packaging tool for source..."
	/usr/bin/cpack --config ./CPackSourceConfig.cmake /root/sensor-robin/CPackSourceConfig.cmake
.PHONY : package_source

# Special rule for the target package_source
package_source/fast: package_source

.PHONY : package_source/fast

# Special rule for the target edit_cache
edit_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "No interactive CMake dialog available..."
	/usr/bin/cmake -E echo No\ interactive\ CMake\ dialog\ available.
.PHONY : edit_cache

# Special rule for the target edit_cache
edit_cache/fast: edit_cache

.PHONY : edit_cache/fast

# The main all target
all: cmake_check_build_system
	$(CMAKE_COMMAND) -E cmake_progress_start /root/sensor-robin/CMakeFiles /root/sensor-robin/CMakeFiles/progress.marks
	$(MAKE) -f CMakeFiles/Makefile2 all
	$(CMAKE_COMMAND) -E cmake_progress_start /root/sensor-robin/CMakeFiles 0
.PHONY : all

# The main clean target
clean:
	$(MAKE) -f CMakeFiles/Makefile2 clean
.PHONY : clean

# The main clean target
clean/fast: clean

.PHONY : clean/fast

# Prepare targets for installation.
preinstall: all
	$(MAKE) -f CMakeFiles/Makefile2 preinstall
.PHONY : preinstall

# Prepare targets for installation.
preinstall/fast:
	$(MAKE) -f CMakeFiles/Makefile2 preinstall
.PHONY : preinstall/fast

# clear depends
depend:
	$(CMAKE_COMMAND) -H$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 1
.PHONY : depend

#=============================================================================
# Target rules for targets named es_sensor

# Build rule for target.
es_sensor: cmake_check_build_system
	$(MAKE) -f CMakeFiles/Makefile2 es_sensor
.PHONY : es_sensor

# fast build rule for target.
es_sensor/fast:
	$(MAKE) -f CMakeFiles/es_sensor.dir/build.make CMakeFiles/es_sensor.dir/build
.PHONY : es_sensor/fast

MiscBlocks/AvroSerialization.o: MiscBlocks/AvroSerialization.cpp.o

.PHONY : MiscBlocks/AvroSerialization.o

# target to build an object file
MiscBlocks/AvroSerialization.cpp.o:
	$(MAKE) -f CMakeFiles/es_sensor.dir/build.make CMakeFiles/es_sensor.dir/MiscBlocks/AvroSerialization.cpp.o
.PHONY : MiscBlocks/AvroSerialization.cpp.o

MiscBlocks/AvroSerialization.i: MiscBlocks/AvroSerialization.cpp.i

.PHONY : MiscBlocks/AvroSerialization.i

# target to preprocess a source file
MiscBlocks/AvroSerialization.cpp.i:
	$(MAKE) -f CMakeFiles/es_sensor.dir/build.make CMakeFiles/es_sensor.dir/MiscBlocks/AvroSerialization.cpp.i
.PHONY : MiscBlocks/AvroSerialization.cpp.i

MiscBlocks/AvroSerialization.s: MiscBlocks/AvroSerialization.cpp.s

.PHONY : MiscBlocks/AvroSerialization.s

# target to generate assembly for a file
MiscBlocks/AvroSerialization.cpp.s:
	$(MAKE) -f CMakeFiles/es_sensor.dir/build.make CMakeFiles/es_sensor.dir/MiscBlocks/AvroSerialization.cpp.s
.PHONY : MiscBlocks/AvroSerialization.cpp.s

MiscBlocks/FileSink.o: MiscBlocks/FileSink.cpp.o

.PHONY : MiscBlocks/FileSink.o

# target to build an object file
MiscBlocks/FileSink.cpp.o:
	$(MAKE) -f CMakeFiles/es_sensor.dir/build.make CMakeFiles/es_sensor.dir/MiscBlocks/FileSink.cpp.o
.PHONY : MiscBlocks/FileSink.cpp.o

MiscBlocks/FileSink.i: MiscBlocks/FileSink.cpp.i

.PHONY : MiscBlocks/FileSink.i

# target to preprocess a source file
MiscBlocks/FileSink.cpp.i:
	$(MAKE) -f CMakeFiles/es_sensor.dir/build.make CMakeFiles/es_sensor.dir/MiscBlocks/FileSink.cpp.i
.PHONY : MiscBlocks/FileSink.cpp.i

MiscBlocks/FileSink.s: MiscBlocks/FileSink.cpp.s

.PHONY : MiscBlocks/FileSink.s

# target to generate assembly for a file
MiscBlocks/FileSink.cpp.s:
	$(MAKE) -f CMakeFiles/es_sensor.dir/build.make CMakeFiles/es_sensor.dir/MiscBlocks/FileSink.cpp.s
.PHONY : MiscBlocks/FileSink.cpp.s

MiscBlocks/Filter/FIR/FIRDesign.o: MiscBlocks/Filter/FIR/FIRDesign.cpp.o

.PHONY : MiscBlocks/Filter/FIR/FIRDesign.o

# target to build an object file
MiscBlocks/Filter/FIR/FIRDesign.cpp.o:
	$(MAKE) -f CMakeFiles/es_sensor.dir/build.make CMakeFiles/es_sensor.dir/MiscBlocks/Filter/FIR/FIRDesign.cpp.o
.PHONY : MiscBlocks/Filter/FIR/FIRDesign.cpp.o

MiscBlocks/Filter/FIR/FIRDesign.i: MiscBlocks/Filter/FIR/FIRDesign.cpp.i

.PHONY : MiscBlocks/Filter/FIR/FIRDesign.i

# target to preprocess a source file
MiscBlocks/Filter/FIR/FIRDesign.cpp.i:
	$(MAKE) -f CMakeFiles/es_sensor.dir/build.make CMakeFiles/es_sensor.dir/MiscBlocks/Filter/FIR/FIRDesign.cpp.i
.PHONY : MiscBlocks/Filter/FIR/FIRDesign.cpp.i

MiscBlocks/Filter/FIR/FIRDesign.s: MiscBlocks/Filter/FIR/FIRDesign.cpp.s

.PHONY : MiscBlocks/Filter/FIR/FIRDesign.s

# target to generate assembly for a file
MiscBlocks/Filter/FIR/FIRDesign.cpp.s:
	$(MAKE) -f CMakeFiles/es_sensor.dir/build.make CMakeFiles/es_sensor.dir/MiscBlocks/Filter/FIR/FIRDesign.cpp.s
.PHONY : MiscBlocks/Filter/FIR/FIRDesign.cpp.s

MiscBlocks/Filter/Resampler/Downsampler.o: MiscBlocks/Filter/Resampler/Downsampler.cpp.o

.PHONY : MiscBlocks/Filter/Resampler/Downsampler.o

# target to build an object file
MiscBlocks/Filter/Resampler/Downsampler.cpp.o:
	$(MAKE) -f CMakeFiles/es_sensor.dir/build.make CMakeFiles/es_sensor.dir/MiscBlocks/Filter/Resampler/Downsampler.cpp.o
.PHONY : MiscBlocks/Filter/Resampler/Downsampler.cpp.o

MiscBlocks/Filter/Resampler/Downsampler.i: MiscBlocks/Filter/Resampler/Downsampler.cpp.i

.PHONY : MiscBlocks/Filter/Resampler/Downsampler.i

# target to preprocess a source file
MiscBlocks/Filter/Resampler/Downsampler.cpp.i:
	$(MAKE) -f CMakeFiles/es_sensor.dir/build.make CMakeFiles/es_sensor.dir/MiscBlocks/Filter/Resampler/Downsampler.cpp.i
.PHONY : MiscBlocks/Filter/Resampler/Downsampler.cpp.i

MiscBlocks/Filter/Resampler/Downsampler.s: MiscBlocks/Filter/Resampler/Downsampler.cpp.s

.PHONY : MiscBlocks/Filter/Resampler/Downsampler.s

# target to generate assembly for a file
MiscBlocks/Filter/Resampler/Downsampler.cpp.s:
	$(MAKE) -f CMakeFiles/es_sensor.dir/build.make CMakeFiles/es_sensor.dir/MiscBlocks/Filter/Resampler/Downsampler.cpp.s
.PHONY : MiscBlocks/Filter/Resampler/Downsampler.cpp.s

MiscBlocks/IQSink.o: MiscBlocks/IQSink.cpp.o

.PHONY : MiscBlocks/IQSink.o

# target to build an object file
MiscBlocks/IQSink.cpp.o:
	$(MAKE) -f CMakeFiles/es_sensor.dir/build.make CMakeFiles/es_sensor.dir/MiscBlocks/IQSink.cpp.o
.PHONY : MiscBlocks/IQSink.cpp.o

MiscBlocks/IQSink.i: MiscBlocks/IQSink.cpp.i

.PHONY : MiscBlocks/IQSink.i

# target to preprocess a source file
MiscBlocks/IQSink.cpp.i:
	$(MAKE) -f CMakeFiles/es_sensor.dir/build.make CMakeFiles/es_sensor.dir/MiscBlocks/IQSink.cpp.i
.PHONY : MiscBlocks/IQSink.cpp.i

MiscBlocks/IQSink.s: MiscBlocks/IQSink.cpp.s

.PHONY : MiscBlocks/IQSink.s

# target to generate assembly for a file
MiscBlocks/IQSink.cpp.s:
	$(MAKE) -f CMakeFiles/es_sensor.dir/build.make CMakeFiles/es_sensor.dir/MiscBlocks/IQSink.cpp.s
.PHONY : MiscBlocks/IQSink.cpp.s

MiscBlocks/IQStream.o: MiscBlocks/IQStream.cpp.o

.PHONY : MiscBlocks/IQStream.o

# target to build an object file
MiscBlocks/IQStream.cpp.o:
	$(MAKE) -f CMakeFiles/es_sensor.dir/build.make CMakeFiles/es_sensor.dir/MiscBlocks/IQStream.cpp.o
.PHONY : MiscBlocks/IQStream.cpp.o

MiscBlocks/IQStream.i: MiscBlocks/IQStream.cpp.i

.PHONY : MiscBlocks/IQStream.i

# target to preprocess a source file
MiscBlocks/IQStream.cpp.i:
	$(MAKE) -f CMakeFiles/es_sensor.dir/build.make CMakeFiles/es_sensor.dir/MiscBlocks/IQStream.cpp.i
.PHONY : MiscBlocks/IQStream.cpp.i

MiscBlocks/IQStream.s: MiscBlocks/IQStream.cpp.s

.PHONY : MiscBlocks/IQStream.s

# target to generate assembly for a file
MiscBlocks/IQStream.cpp.s:
	$(MAKE) -f CMakeFiles/es_sensor.dir/build.make CMakeFiles/es_sensor.dir/MiscBlocks/IQStream.cpp.s
.PHONY : MiscBlocks/IQStream.cpp.s

MiscBlocks/Transmission.o: MiscBlocks/Transmission.cpp.o

.PHONY : MiscBlocks/Transmission.o

# target to build an object file
MiscBlocks/Transmission.cpp.o:
	$(MAKE) -f CMakeFiles/es_sensor.dir/build.make CMakeFiles/es_sensor.dir/MiscBlocks/Transmission.cpp.o
.PHONY : MiscBlocks/Transmission.cpp.o

MiscBlocks/Transmission.i: MiscBlocks/Transmission.cpp.i

.PHONY : MiscBlocks/Transmission.i

# target to preprocess a source file
MiscBlocks/Transmission.cpp.i:
	$(MAKE) -f CMakeFiles/es_sensor.dir/build.make CMakeFiles/es_sensor.dir/MiscBlocks/Transmission.cpp.i
.PHONY : MiscBlocks/Transmission.cpp.i

MiscBlocks/Transmission.s: MiscBlocks/Transmission.cpp.s

.PHONY : MiscBlocks/Transmission.s

# target to generate assembly for a file
MiscBlocks/Transmission.cpp.s:
	$(MAKE) -f CMakeFiles/es_sensor.dir/build.make CMakeFiles/es_sensor.dir/MiscBlocks/Transmission.cpp.s
.PHONY : MiscBlocks/Transmission.cpp.s

ProcessingBlocks/Averaging.o: ProcessingBlocks/Averaging.cpp.o

.PHONY : ProcessingBlocks/Averaging.o

# target to build an object file
ProcessingBlocks/Averaging.cpp.o:
	$(MAKE) -f CMakeFiles/es_sensor.dir/build.make CMakeFiles/es_sensor.dir/ProcessingBlocks/Averaging.cpp.o
.PHONY : ProcessingBlocks/Averaging.cpp.o

ProcessingBlocks/Averaging.i: ProcessingBlocks/Averaging.cpp.i

.PHONY : ProcessingBlocks/Averaging.i

# target to preprocess a source file
ProcessingBlocks/Averaging.cpp.i:
	$(MAKE) -f CMakeFiles/es_sensor.dir/build.make CMakeFiles/es_sensor.dir/ProcessingBlocks/Averaging.cpp.i
.PHONY : ProcessingBlocks/Averaging.cpp.i

ProcessingBlocks/Averaging.s: ProcessingBlocks/Averaging.cpp.s

.PHONY : ProcessingBlocks/Averaging.s

# target to generate assembly for a file
ProcessingBlocks/Averaging.cpp.s:
	$(MAKE) -f CMakeFiles/es_sensor.dir/build.make CMakeFiles/es_sensor.dir/ProcessingBlocks/Averaging.cpp.s
.PHONY : ProcessingBlocks/Averaging.cpp.s

ProcessingBlocks/FFT.o: ProcessingBlocks/FFT.cpp.o

.PHONY : ProcessingBlocks/FFT.o

# target to build an object file
ProcessingBlocks/FFT.cpp.o:
	$(MAKE) -f CMakeFiles/es_sensor.dir/build.make CMakeFiles/es_sensor.dir/ProcessingBlocks/FFT.cpp.o
.PHONY : ProcessingBlocks/FFT.cpp.o

ProcessingBlocks/FFT.i: ProcessingBlocks/FFT.cpp.i

.PHONY : ProcessingBlocks/FFT.i

# target to preprocess a source file
ProcessingBlocks/FFT.cpp.i:
	$(MAKE) -f CMakeFiles/es_sensor.dir/build.make CMakeFiles/es_sensor.dir/ProcessingBlocks/FFT.cpp.i
.PHONY : ProcessingBlocks/FFT.cpp.i

ProcessingBlocks/FFT.s: ProcessingBlocks/FFT.cpp.s

.PHONY : ProcessingBlocks/FFT.s

# target to generate assembly for a file
ProcessingBlocks/FFT.cpp.s:
	$(MAKE) -f CMakeFiles/es_sensor.dir/build.make CMakeFiles/es_sensor.dir/ProcessingBlocks/FFT.cpp.s
.PHONY : ProcessingBlocks/FFT.cpp.s

ProcessingBlocks/PSDFast.o: ProcessingBlocks/PSDFast.cpp.o

.PHONY : ProcessingBlocks/PSDFast.o

# target to build an object file
ProcessingBlocks/PSDFast.cpp.o:
	$(MAKE) -f CMakeFiles/es_sensor.dir/build.make CMakeFiles/es_sensor.dir/ProcessingBlocks/PSDFast.cpp.o
.PHONY : ProcessingBlocks/PSDFast.cpp.o

ProcessingBlocks/PSDFast.i: ProcessingBlocks/PSDFast.cpp.i

.PHONY : ProcessingBlocks/PSDFast.i

# target to preprocess a source file
ProcessingBlocks/PSDFast.cpp.i:
	$(MAKE) -f CMakeFiles/es_sensor.dir/build.make CMakeFiles/es_sensor.dir/ProcessingBlocks/PSDFast.cpp.i
.PHONY : ProcessingBlocks/PSDFast.cpp.i

ProcessingBlocks/PSDFast.s: ProcessingBlocks/PSDFast.cpp.s

.PHONY : ProcessingBlocks/PSDFast.s

# target to generate assembly for a file
ProcessingBlocks/PSDFast.cpp.s:
	$(MAKE) -f CMakeFiles/es_sensor.dir/build.make CMakeFiles/es_sensor.dir/ProcessingBlocks/PSDFast.cpp.s
.PHONY : ProcessingBlocks/PSDFast.cpp.s

ProcessingBlocks/RemoveDC.o: ProcessingBlocks/RemoveDC.cpp.o

.PHONY : ProcessingBlocks/RemoveDC.o

# target to build an object file
ProcessingBlocks/RemoveDC.cpp.o:
	$(MAKE) -f CMakeFiles/es_sensor.dir/build.make CMakeFiles/es_sensor.dir/ProcessingBlocks/RemoveDC.cpp.o
.PHONY : ProcessingBlocks/RemoveDC.cpp.o

ProcessingBlocks/RemoveDC.i: ProcessingBlocks/RemoveDC.cpp.i

.PHONY : ProcessingBlocks/RemoveDC.i

# target to preprocess a source file
ProcessingBlocks/RemoveDC.cpp.i:
	$(MAKE) -f CMakeFiles/es_sensor.dir/build.make CMakeFiles/es_sensor.dir/ProcessingBlocks/RemoveDC.cpp.i
.PHONY : ProcessingBlocks/RemoveDC.cpp.i

ProcessingBlocks/RemoveDC.s: ProcessingBlocks/RemoveDC.cpp.s

.PHONY : ProcessingBlocks/RemoveDC.s

# target to generate assembly for a file
ProcessingBlocks/RemoveDC.cpp.s:
	$(MAKE) -f CMakeFiles/es_sensor.dir/build.make CMakeFiles/es_sensor.dir/ProcessingBlocks/RemoveDC.cpp.s
.PHONY : ProcessingBlocks/RemoveDC.cpp.s

ProcessingBlocks/RemoveDCRTL.o: ProcessingBlocks/RemoveDCRTL.cpp.o

.PHONY : ProcessingBlocks/RemoveDCRTL.o

# target to build an object file
ProcessingBlocks/RemoveDCRTL.cpp.o:
	$(MAKE) -f CMakeFiles/es_sensor.dir/build.make CMakeFiles/es_sensor.dir/ProcessingBlocks/RemoveDCRTL.cpp.o
.PHONY : ProcessingBlocks/RemoveDCRTL.cpp.o

ProcessingBlocks/RemoveDCRTL.i: ProcessingBlocks/RemoveDCRTL.cpp.i

.PHONY : ProcessingBlocks/RemoveDCRTL.i

# target to preprocess a source file
ProcessingBlocks/RemoveDCRTL.cpp.i:
	$(MAKE) -f CMakeFiles/es_sensor.dir/build.make CMakeFiles/es_sensor.dir/ProcessingBlocks/RemoveDCRTL.cpp.i
.PHONY : ProcessingBlocks/RemoveDCRTL.cpp.i

ProcessingBlocks/RemoveDCRTL.s: ProcessingBlocks/RemoveDCRTL.cpp.s

.PHONY : ProcessingBlocks/RemoveDCRTL.s

# target to generate assembly for a file
ProcessingBlocks/RemoveDCRTL.cpp.s:
	$(MAKE) -f CMakeFiles/es_sensor.dir/build.make CMakeFiles/es_sensor.dir/ProcessingBlocks/RemoveDCRTL.cpp.s
.PHONY : ProcessingBlocks/RemoveDCRTL.cpp.s

ProcessingBlocks/Windowing.o: ProcessingBlocks/Windowing.cpp.o

.PHONY : ProcessingBlocks/Windowing.o

# target to build an object file
ProcessingBlocks/Windowing.cpp.o:
	$(MAKE) -f CMakeFiles/es_sensor.dir/build.make CMakeFiles/es_sensor.dir/ProcessingBlocks/Windowing.cpp.o
.PHONY : ProcessingBlocks/Windowing.cpp.o

ProcessingBlocks/Windowing.i: ProcessingBlocks/Windowing.cpp.i

.PHONY : ProcessingBlocks/Windowing.i

# target to preprocess a source file
ProcessingBlocks/Windowing.cpp.i:
	$(MAKE) -f CMakeFiles/es_sensor.dir/build.make CMakeFiles/es_sensor.dir/ProcessingBlocks/Windowing.cpp.i
.PHONY : ProcessingBlocks/Windowing.cpp.i

ProcessingBlocks/Windowing.s: ProcessingBlocks/Windowing.cpp.s

.PHONY : ProcessingBlocks/Windowing.s

# target to generate assembly for a file
ProcessingBlocks/Windowing.cpp.s:
	$(MAKE) -f CMakeFiles/es_sensor.dir/build.make CMakeFiles/es_sensor.dir/ProcessingBlocks/Windowing.cpp.s
.PHONY : ProcessingBlocks/Windowing.cpp.s

context/ElectrosenseContext.o: context/ElectrosenseContext.cpp.o

.PHONY : context/ElectrosenseContext.o

# target to build an object file
context/ElectrosenseContext.cpp.o:
	$(MAKE) -f CMakeFiles/es_sensor.dir/build.make CMakeFiles/es_sensor.dir/context/ElectrosenseContext.cpp.o
.PHONY : context/ElectrosenseContext.cpp.o

context/ElectrosenseContext.i: context/ElectrosenseContext.cpp.i

.PHONY : context/ElectrosenseContext.i

# target to preprocess a source file
context/ElectrosenseContext.cpp.i:
	$(MAKE) -f CMakeFiles/es_sensor.dir/build.make CMakeFiles/es_sensor.dir/context/ElectrosenseContext.cpp.i
.PHONY : context/ElectrosenseContext.cpp.i

context/ElectrosenseContext.s: context/ElectrosenseContext.cpp.s

.PHONY : context/ElectrosenseContext.s

# target to generate assembly for a file
context/ElectrosenseContext.cpp.s:
	$(MAKE) -f CMakeFiles/es_sensor.dir/build.make CMakeFiles/es_sensor.dir/context/ElectrosenseContext.cpp.s
.PHONY : context/ElectrosenseContext.cpp.s

drivers/common/SequentialHopping.o: drivers/common/SequentialHopping.cpp.o

.PHONY : drivers/common/SequentialHopping.o

# target to build an object file
drivers/common/SequentialHopping.cpp.o:
	$(MAKE) -f CMakeFiles/es_sensor.dir/build.make CMakeFiles/es_sensor.dir/drivers/common/SequentialHopping.cpp.o
.PHONY : drivers/common/SequentialHopping.cpp.o

drivers/common/SequentialHopping.i: drivers/common/SequentialHopping.cpp.i

.PHONY : drivers/common/SequentialHopping.i

# target to preprocess a source file
drivers/common/SequentialHopping.cpp.i:
	$(MAKE) -f CMakeFiles/es_sensor.dir/build.make CMakeFiles/es_sensor.dir/drivers/common/SequentialHopping.cpp.i
.PHONY : drivers/common/SequentialHopping.cpp.i

drivers/common/SequentialHopping.s: drivers/common/SequentialHopping.cpp.s

.PHONY : drivers/common/SequentialHopping.s

# target to generate assembly for a file
drivers/common/SequentialHopping.cpp.s:
	$(MAKE) -f CMakeFiles/es_sensor.dir/build.make CMakeFiles/es_sensor.dir/drivers/common/SequentialHopping.cpp.s
.PHONY : drivers/common/SequentialHopping.cpp.s

drivers/rtlsdr/converter/converter.o: drivers/rtlsdr/converter/converter.c.o

.PHONY : drivers/rtlsdr/converter/converter.o

# target to build an object file
drivers/rtlsdr/converter/converter.c.o:
	$(MAKE) -f CMakeFiles/es_sensor.dir/build.make CMakeFiles/es_sensor.dir/drivers/rtlsdr/converter/converter.c.o
.PHONY : drivers/rtlsdr/converter/converter.c.o

drivers/rtlsdr/converter/converter.i: drivers/rtlsdr/converter/converter.c.i

.PHONY : drivers/rtlsdr/converter/converter.i

# target to preprocess a source file
drivers/rtlsdr/converter/converter.c.i:
	$(MAKE) -f CMakeFiles/es_sensor.dir/build.make CMakeFiles/es_sensor.dir/drivers/rtlsdr/converter/converter.c.i
.PHONY : drivers/rtlsdr/converter/converter.c.i

drivers/rtlsdr/converter/converter.s: drivers/rtlsdr/converter/converter.c.s

.PHONY : drivers/rtlsdr/converter/converter.s

# target to generate assembly for a file
drivers/rtlsdr/converter/converter.c.s:
	$(MAKE) -f CMakeFiles/es_sensor.dir/build.make CMakeFiles/es_sensor.dir/drivers/rtlsdr/converter/converter.c.s
.PHONY : drivers/rtlsdr/converter/converter.c.s

drivers/rtlsdr/rtlsdrDriver.o: drivers/rtlsdr/rtlsdrDriver.cpp.o

.PHONY : drivers/rtlsdr/rtlsdrDriver.o

# target to build an object file
drivers/rtlsdr/rtlsdrDriver.cpp.o:
	$(MAKE) -f CMakeFiles/es_sensor.dir/build.make CMakeFiles/es_sensor.dir/drivers/rtlsdr/rtlsdrDriver.cpp.o
.PHONY : drivers/rtlsdr/rtlsdrDriver.cpp.o

drivers/rtlsdr/rtlsdrDriver.i: drivers/rtlsdr/rtlsdrDriver.cpp.i

.PHONY : drivers/rtlsdr/rtlsdrDriver.i

# target to preprocess a source file
drivers/rtlsdr/rtlsdrDriver.cpp.i:
	$(MAKE) -f CMakeFiles/es_sensor.dir/build.make CMakeFiles/es_sensor.dir/drivers/rtlsdr/rtlsdrDriver.cpp.i
.PHONY : drivers/rtlsdr/rtlsdrDriver.cpp.i

drivers/rtlsdr/rtlsdrDriver.s: drivers/rtlsdr/rtlsdrDriver.cpp.s

.PHONY : drivers/rtlsdr/rtlsdrDriver.s

# target to generate assembly for a file
drivers/rtlsdr/rtlsdrDriver.cpp.s:
	$(MAKE) -f CMakeFiles/es_sensor.dir/build.make CMakeFiles/es_sensor.dir/drivers/rtlsdr/rtlsdrDriver.cpp.s
.PHONY : drivers/rtlsdr/rtlsdrDriver.cpp.s

main.o: main.cpp.o

.PHONY : main.o

# target to build an object file
main.cpp.o:
	$(MAKE) -f CMakeFiles/es_sensor.dir/build.make CMakeFiles/es_sensor.dir/main.cpp.o
.PHONY : main.cpp.o

main.i: main.cpp.i

.PHONY : main.i

# target to preprocess a source file
main.cpp.i:
	$(MAKE) -f CMakeFiles/es_sensor.dir/build.make CMakeFiles/es_sensor.dir/main.cpp.i
.PHONY : main.cpp.i

main.s: main.cpp.s

.PHONY : main.s

# target to generate assembly for a file
main.cpp.s:
	$(MAKE) -f CMakeFiles/es_sensor.dir/build.make CMakeFiles/es_sensor.dir/main.cpp.s
.PHONY : main.cpp.s

misc/TCP.o: misc/TCP.cpp.o

.PHONY : misc/TCP.o

# target to build an object file
misc/TCP.cpp.o:
	$(MAKE) -f CMakeFiles/es_sensor.dir/build.make CMakeFiles/es_sensor.dir/misc/TCP.cpp.o
.PHONY : misc/TCP.cpp.o

misc/TCP.i: misc/TCP.cpp.i

.PHONY : misc/TCP.i

# target to preprocess a source file
misc/TCP.cpp.i:
	$(MAKE) -f CMakeFiles/es_sensor.dir/build.make CMakeFiles/es_sensor.dir/misc/TCP.cpp.i
.PHONY : misc/TCP.cpp.i

misc/TCP.s: misc/TCP.cpp.s

.PHONY : misc/TCP.s

# target to generate assembly for a file
misc/TCP.cpp.s:
	$(MAKE) -f CMakeFiles/es_sensor.dir/build.make CMakeFiles/es_sensor.dir/misc/TCP.cpp.s
.PHONY : misc/TCP.cpp.s

misc/TLS.o: misc/TLS.cpp.o

.PHONY : misc/TLS.o

# target to build an object file
misc/TLS.cpp.o:
	$(MAKE) -f CMakeFiles/es_sensor.dir/build.make CMakeFiles/es_sensor.dir/misc/TLS.cpp.o
.PHONY : misc/TLS.cpp.o

misc/TLS.i: misc/TLS.cpp.i

.PHONY : misc/TLS.i

# target to preprocess a source file
misc/TLS.cpp.i:
	$(MAKE) -f CMakeFiles/es_sensor.dir/build.make CMakeFiles/es_sensor.dir/misc/TLS.cpp.i
.PHONY : misc/TLS.cpp.i

misc/TLS.s: misc/TLS.cpp.s

.PHONY : misc/TLS.s

# target to generate assembly for a file
misc/TLS.cpp.s:
	$(MAKE) -f CMakeFiles/es_sensor.dir/build.make CMakeFiles/es_sensor.dir/misc/TLS.cpp.s
.PHONY : misc/TLS.cpp.s

types/SpectrumSegment.o: types/SpectrumSegment.cpp.o

.PHONY : types/SpectrumSegment.o

# target to build an object file
types/SpectrumSegment.cpp.o:
	$(MAKE) -f CMakeFiles/es_sensor.dir/build.make CMakeFiles/es_sensor.dir/types/SpectrumSegment.cpp.o
.PHONY : types/SpectrumSegment.cpp.o

types/SpectrumSegment.i: types/SpectrumSegment.cpp.i

.PHONY : types/SpectrumSegment.i

# target to preprocess a source file
types/SpectrumSegment.cpp.i:
	$(MAKE) -f CMakeFiles/es_sensor.dir/build.make CMakeFiles/es_sensor.dir/types/SpectrumSegment.cpp.i
.PHONY : types/SpectrumSegment.cpp.i

types/SpectrumSegment.s: types/SpectrumSegment.cpp.s

.PHONY : types/SpectrumSegment.s

# target to generate assembly for a file
types/SpectrumSegment.cpp.s:
	$(MAKE) -f CMakeFiles/es_sensor.dir/build.make CMakeFiles/es_sensor.dir/types/SpectrumSegment.cpp.s
.PHONY : types/SpectrumSegment.cpp.s

# Help Target
help:
	@echo "The following are some of the valid targets for this Makefile:"
	@echo "... all (the default if no target is provided)"
	@echo "... clean"
	@echo "... depend"
	@echo "... install/local"
	@echo "... install"
	@echo "... list_install_components"
	@echo "... rebuild_cache"
	@echo "... es_sensor"
	@echo "... package"
	@echo "... package_source"
	@echo "... edit_cache"
	@echo "... MiscBlocks/AvroSerialization.o"
	@echo "... MiscBlocks/AvroSerialization.i"
	@echo "... MiscBlocks/AvroSerialization.s"
	@echo "... MiscBlocks/FileSink.o"
	@echo "... MiscBlocks/FileSink.i"
	@echo "... MiscBlocks/FileSink.s"
	@echo "... MiscBlocks/Filter/FIR/FIRDesign.o"
	@echo "... MiscBlocks/Filter/FIR/FIRDesign.i"
	@echo "... MiscBlocks/Filter/FIR/FIRDesign.s"
	@echo "... MiscBlocks/Filter/Resampler/Downsampler.o"
	@echo "... MiscBlocks/Filter/Resampler/Downsampler.i"
	@echo "... MiscBlocks/Filter/Resampler/Downsampler.s"
	@echo "... MiscBlocks/IQSink.o"
	@echo "... MiscBlocks/IQSink.i"
	@echo "... MiscBlocks/IQSink.s"
	@echo "... MiscBlocks/IQStream.o"
	@echo "... MiscBlocks/IQStream.i"
	@echo "... MiscBlocks/IQStream.s"
	@echo "... MiscBlocks/Transmission.o"
	@echo "... MiscBlocks/Transmission.i"
	@echo "... MiscBlocks/Transmission.s"
	@echo "... ProcessingBlocks/Averaging.o"
	@echo "... ProcessingBlocks/Averaging.i"
	@echo "... ProcessingBlocks/Averaging.s"
	@echo "... ProcessingBlocks/FFT.o"
	@echo "... ProcessingBlocks/FFT.i"
	@echo "... ProcessingBlocks/FFT.s"
	@echo "... ProcessingBlocks/PSDFast.o"
	@echo "... ProcessingBlocks/PSDFast.i"
	@echo "... ProcessingBlocks/PSDFast.s"
	@echo "... ProcessingBlocks/RemoveDC.o"
	@echo "... ProcessingBlocks/RemoveDC.i"
	@echo "... ProcessingBlocks/RemoveDC.s"
	@echo "... ProcessingBlocks/RemoveDCRTL.o"
	@echo "... ProcessingBlocks/RemoveDCRTL.i"
	@echo "... ProcessingBlocks/RemoveDCRTL.s"
	@echo "... ProcessingBlocks/Windowing.o"
	@echo "... ProcessingBlocks/Windowing.i"
	@echo "... ProcessingBlocks/Windowing.s"
	@echo "... context/ElectrosenseContext.o"
	@echo "... context/ElectrosenseContext.i"
	@echo "... context/ElectrosenseContext.s"
	@echo "... drivers/common/SequentialHopping.o"
	@echo "... drivers/common/SequentialHopping.i"
	@echo "... drivers/common/SequentialHopping.s"
	@echo "... drivers/rtlsdr/converter/converter.o"
	@echo "... drivers/rtlsdr/converter/converter.i"
	@echo "... drivers/rtlsdr/converter/converter.s"
	@echo "... drivers/rtlsdr/rtlsdrDriver.o"
	@echo "... drivers/rtlsdr/rtlsdrDriver.i"
	@echo "... drivers/rtlsdr/rtlsdrDriver.s"
	@echo "... main.o"
	@echo "... main.i"
	@echo "... main.s"
	@echo "... misc/TCP.o"
	@echo "... misc/TCP.i"
	@echo "... misc/TCP.s"
	@echo "... misc/TLS.o"
	@echo "... misc/TLS.i"
	@echo "... misc/TLS.s"
	@echo "... types/SpectrumSegment.o"
	@echo "... types/SpectrumSegment.i"
	@echo "... types/SpectrumSegment.s"
.PHONY : help



#=============================================================================
# Special targets to cleanup operation of make.

# Special rule to run CMake to check the build system integrity.
# No rule that depends on this can have commands that come from listfiles
# because they might be regenerated.
cmake_check_build_system:
	$(CMAKE_COMMAND) -H$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 0
.PHONY : cmake_check_build_system

