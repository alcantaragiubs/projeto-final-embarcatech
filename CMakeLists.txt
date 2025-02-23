# Generated Cmake Pico project file

cmake_minimum_required(VERSION 3.13)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Initialise pico_sdk from installed location
# (note this can come from environment, CMake cache etc)

# == DO NOT EDIT THE FOLLOWING LINES for the Raspberry Pi Pico VS Code Extension to work ==
if(WIN32)
    set(USERHOME $ENV{USERPROFILE})
else()
    set(USERHOME $ENV{HOME})
endif()
set(sdkVersion 1.5.1)
set(toolchainVersion 13_3_Rel1)
set(picotoolVersion 2.0.0)
set(picoVscode ${USERHOME}/.pico-sdk/cmake/pico-vscode.cmake)
if (EXISTS ${picoVscode})
    include(${picoVscode})
endif()
# ====================================================================================
set(PICO_BOARD pico_w CACHE STRING "Board type")

# Pull in Raspberry Pi Pico SDK (must be before project)
include(pico_sdk_import.cmake)

project(placar_eletronico C CXX ASM)

# Initialise the Raspberry Pi Pico SDK
pico_sdk_init()

# Adiciona os arquivos fonte do projeto
add_executable(placar_eletronico 
    src/main.c 
    src/configuracao.c
    src/apresentacao.c
    src/joystick.c 
    src/botao.c 
    src/buzzer.c
    src/partida.c
    inc/ssd1306_i2c.c
)

# Definições de nome e versão do programa
pico_set_program_name(placar_eletronico "placar_eletronico")
pico_set_program_version(placar_eletronico "0.1")

# Habilita saída via USB e desabilita UART
pico_enable_stdio_uart(placar_eletronico 0)
pico_enable_stdio_usb(placar_eletronico 1)

# Diretórios de cabeçalhos
target_include_directories(placar_eletronico PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}  # Inclui o diretório raiz
    ${CMAKE_CURRENT_LIST_DIR}/inc  # Inclui diretório de headers adicionais
)

# Adiciona bibliotecas padrão e do hardware
target_link_libraries(placar_eletronico
    pico_stdlib
    hardware_adc
    hardware_i2c
    hardware_pwm
)

# Gera arquivos extras (UF2, bin, hex)
pico_add_extra_outputs(placar_eletronico)
