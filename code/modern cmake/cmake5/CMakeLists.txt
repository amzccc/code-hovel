cmake_minimum_required(VERSION 3.20.0)

project(InstallExport CXX)

include(GNUInstallDirs)

add_library(Calc STATIC calc.cpp)

set_target_properties(Calc PROPERTIES PUBLIC_HEADER calc.h)

set(CMAKE_INSTALL_PREFIX ${CMAKE_BINARY_DIR}/install)

install(TARGETS Calc EXPORT CalcTargets 
    ARCHIVE PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/calc    
)

install(EXPORT CalcTargets
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/calc/cmake
    NAMESPACE Calc::    
)

