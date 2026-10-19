cmake_minimum_required(VERSION 3.19)
project(41132226_1019_contact_book LANGUAGES CXX)

find_package(Qt6 6.5 REQUIRED COMPONENTS Core Widgets LinguistTools)

qt_standard_project_setup()

qt_add_executable(41132226_1019_contact_book
    WIN32 MACOSX_BUNDLE
    main.cpp
    mywidget.cpp
    mywidget.h
    mywidget.ui
)

qt_add_translations(
    TARGETS 41132226_1019_contact_book
    TS_FILES 41132226_1019_contact_book_zh_TW.ts
)

target_link_libraries(41132226_1019_contact_book
    PRIVATE
        Qt::Core
        Qt::Widgets
)

install(TARGETS 41132226_1019_contact_book
    BUNDLE  DESTINATION .
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

qt_generate_deploy_app_script(
    TARGET 41132226_1019_contact_book
    OUTPUT_SCRIPT deploy_script
    NO_UNSUPPORTED_PLATFORM_ERROR
)
install(SCRIPT ${deploy_script})
