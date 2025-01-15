# garante a versao correta do CMake
cmake_minimum_required(VERSION 3.21)

#inclusao do caminho do SDK do Raspberry Pi Pico
include($ENV{PICO_SDK_PATH}/external/pico_sdk_import.cmake)

#Define o nome do projeto "modelDefault" e as linguagens que usara "C, C++, e Assembly"
project(modelDefault C CXX ASM)

#Inicia o SDK
pico_sdk_init()

#Adiciona o executavel
add_executable(modelDefault
    modelDefault.c
)

#linka as bibliotecas necessarias
target_link_libraries(modelDefault pico_stdlib)

#faz a adicao dos arquivos UF2 e BIN para poder executar o programa
pico_add_extra_outputs(modelDefault)

# Faz com que a porta COM apareca, necessita do stdio_init_all();
pico_enable_stdio_usb(modelDefault 1)