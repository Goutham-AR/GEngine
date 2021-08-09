add_library(
    imGui
    STATIC

    imgui.cpp    imgui.h  
    imconfig.h
    imgui_draw.cpp    
    imgui_widgets.cpp  
    imstb_truetype.h
    imgui_internal.h  
    imstb_rectpack.h   
    imgui_demo.cpp  
    imgui_tables.cpp  
    imstb_textedit.h
)

target_include_directories(
    imGui
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)