cmake_minimum_required(VERSION 3.10)
project(CameraCQJTU)

set(Matlab_ROOT_DIR "C:/mat")

find_package(Matlab REQUIRED COMPONENTS MAIN_PROGRAM MEX_COMPILER)

include_directories(
    ${Matlab_INCLUDE_DIRS}
    ${CMAKE_SOURCE_DIR}/SDK/include
)

file(GLOB SOURCES "${CMAKE_SOURCE_DIR}/src/source/*.cpp")

add_executable(Camera ${SOURCES})

link_directories(${CMAKE_SOURCE_DIR}/SDK/x64)
file(GLOB SDK_LIBS "${CMAKE_SOURCE_DIR}/SDK/x64/*.lib")
target_link_libraries(Camera ${SDK_LIBS} ${Matlab_LIBRARIES})

set(SDK_DLL_DIR "${CMAKE_SOURCE_DIR}/SDK/x64")
file(GLOB SDK_DLLS "${SDK_DLL_DIR}/*.dll")
foreach(DLL ${SDK_DLLS})
    add_custom_command(TARGET Camera POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
            ${DLL} $<TARGET_FILE_DIR:Camera>
    )
endforeach()

set(Matlab_DLL_DIR "${Matlab_ROOT_DIR}/bin/win64")
set(MATLAB_DLLS
    "libmwi18n.dll"
    "libmex.dll"
    "mvm.dll"
    "libmx.dll"
    "libmwservices.dll"
    "libmwfl.dll"
    "libmwmfl_permute.dll"
    "libut.dll"
    "libMatlabDataArray.dll"
    "libmwload_context.dll"
    "libmwfoundation_log.dll"
    "libmwfoundation_usm.dll"
    "libmwfoundation_matlabdata.dll"
    "libmwfoundation_matlabdata_standalone.dll"
    "libmwfoundation_matlabdata_matlab.dll"
    "libmwindexingapimethods.dll"
    "mwboost_log-vc142-mt-x64-1_78.dll"
    "icuuc69.dll"
    "tbb.dll"
    "tbbmalloc.dll"
    "zlib1.dll"
    "libmwresource_core.dll"
    "libmwfoundation_filesystem.dll"
    "libmwcpp11compat.dll"
    "mwboost_filesystem-vc142-mt-x64-1_78.dll"
    "mwboost_thread-vc142-mt-x64-1_78.dll"
    "mwboost_serialization-vc142-mt-x64-1_78.dll"
    "mwboost_atomic-vc142-mt-x64-1_78.dll"
    "mwboost_iostreams-vc142-mt-x64-1_78.dll"
    "mwboost_chrono-vc142-mt-x64-1_78.dll"
    "libexpat.dll"
    "icudt69.dll"
    "icuin69.dll"
    "icuio69.dll"
    "libmwflstrings.dll"
    "m_dispatcher.dll"
    "mlutil.dll"
    "generate_diag_message.dll"
    "mcos.dll"
    "libmwcppmicroservices.dll"
    "CppMicroServices3.dll"
    "builtin.dll"
    "libmwcapabilities.dll"
    "libmwcwf_interface.dll"
    "libmwflstorageprovider.dll"
    "libmwflstorageutility.dll"
    "libmwflstoragevfs.dll"
    "libmwfoundation_feature.dll"
    "libmwlivecode.dll"
    "libmwmatlabstoragesystem.dll"
    "libmwms.dll"
    "libmwrelease_info.dll"
    "libmwsearch_path_utilities.dll"
    "libmwsettings_in_matlab.dll"
    "opccore.dll"
    "opcmodel.dll"
    "opczippackage.dll"
    "settingscore.dll"
    "string_matrix.dll"
    "libmwmcom.dll"
    "libmwmst.dll"
    "libmwthreadpool.dll"
    "libmwnativedisplay.dll"
    "libmwstartupplugin.dll"
    "libmwstartup_plugin_initializer.dll"
    "libmvmtransportapi.dll"
    "matlab_toolbox_events_base.dll"
    "execution_events.dll"
    "libmwfoundation_tracelogger.dll"
)
foreach(DLL ${MATLAB_DLLS})
    add_custom_command(TARGET Camera POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "${Matlab_DLL_DIR}/${DLL}" $<TARGET_FILE_DIR:Camera>
    )
endforeach()
