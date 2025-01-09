# == DO NOT EDIT THE FOLLOWING LINES for the Raspberry Pi Pico VS Code Extension to work ==
if(WIN32)
    set(USERHOME $ENV{USERPROFILE})
else()
    set(USERHOME $ENV{HOME})
endif()
set(sdkVersion 2.1.0)
set(toolchainVersion 13_3_Rel1)
set(picotoolVersion 2.1.0)
set(picoVscode ${USERHOME}/.pico-sdk/cmake/pico-vscode.cmake)
if (EXISTS ${picoVscode})
    include(${picoVscode})
endif()
# ====================================================================================
set(PICO_BOARD pico CACHE STRING "Board type")

# garante a versao correta do CMake
cmake_minimum_required(VERSION 3.21)

#inclusao do caminho do SDK do Raspberry Pi Pico
include($ENV{PICO_SDK_PATH}/external/pico_sdk_import.cmake)

#Define o nome do projeto "btncont" e as linguagens que usara "C, C++, e Assembly"
project(btncont C CXX ASM)

#Inicia o SDK
pico_sdk_init()

#Adiciona o executavel
add_executable(btncont
    btncont.c
)

#linka as bibliotecas necessarias
target_link_libraries(btncont pico_stdlib)

#faz a adicao dos arquivos UF2 e BIN para poder executar o programa
pico_add_extra_outputs(btncont)

# Faz com que a porta COM apareca, necessita do stdio_init_all();
pico_enable_stdio_usb(btncont 1)
pico_enable_stdio_uart(btncont 0)




