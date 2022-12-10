
set(source_files raygui.h)

add_library(raygui ${source_files})

set_target_properties(raygui PROPERTIES LINKER_LANGUAGE C)
