set(DIRS
    usdrecord
    usdview
    testusdview
)

foreach(d ${DIRS})
    add_subdirectory(${d})
endforeach()

if (${PXR_ENABLE_MATERIALX_SUPPORT})
    add_subdirectory(usdBakeMtlx)
endif()

if (${PXR_ENABLE_WEBGPU_SUPPORT} AND EMSCRIPTEN)
    # usdviewweb fails to build, and CloudZeta doesn't need it.
    #add_subdirectory(usdviewweb)
endif()
