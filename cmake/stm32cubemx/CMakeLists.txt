cmake_minimum_required(VERSION 3.22)

project(stm32cubemx)
add_library(stm32cubemx INTERFACE)

# Enable CMake support for ASM and C languages
enable_language(C ASM)

target_compile_definitions(stm32cubemx INTERFACE 
	USE_HAL_DRIVER 
	STM32F446xx
    $<$<CONFIG:Debug>:DEBUG>
)

target_include_directories(stm32cubemx INTERFACE
    ../../App
    ../../Drv

    ../../Include
    ../../Infra
    ../../Infra/EngCM
    ../../Infra/EngLib

    ../../OS/FreeRTOS/Source/include
    ../../OS/FreeRTOS/Source/CMSIS_RTOS_V2
    ../../OS/FreeRTOS/Source/portable/GCC/ARM_CM4F

    ../../HAL/BSP
    ../../HAL/EngChip
    ../../HAL/EngChip/Core/Inc
    ../../HAL/EngChip/Drivers/STM32F4xx_HAL_Driver/Inc
    ../../HAL/EngChip/Drivers/STM32F4xx_HAL_Driver/Inc/Legacy
    ../../HAL/EngChip/Drivers/CMSIS/Device/ST/STM32F4xx/Include
    ../../HAL/EngChip/Drivers/CMSIS/Include
    ../../HAL/EngHAL
)

target_sources(stm32cubemx INTERFACE
    ../../App/EngSM_Main.c
    ../../App/FOC/EngFOC_Main.c
    ../../Drv/EngDrv_ADC.c
    ../../Drv/EngDrv_CAN.c
    ../../Drv/EngDrv_Encoder.c
    ../../Drv/EngDrv_Flash.c
    ../../Drv/EngDrv_IF.c
    ../../Drv/EngDrv_Sensor.c
    ../../Drv/EngDrv_SPI.c
    ../../Drv/EngDrv_UART.c
    ../../Drv/EngHAL_Interrupt.c
    ../../HAL/EngChip/Core/Src/main.c
    ../../HAL/EngChip/Core/Src/freertos.c
    ../../HAL/EngChip/Core/Src/stm32f4xx_it.c
    ../../HAL/EngChip/Core/Src/stm32f4xx_hal_msp.c
    ../../HAL/EngChip/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_adc.c
    ../../HAL/EngChip/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_adc_ex.c
    ../../HAL/EngChip/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_ll_adc.c
    ../../HAL/EngChip/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_rcc.c
    ../../HAL/EngChip/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_rcc_ex.c
    ../../HAL/EngChip/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_flash.c
    ../../HAL/EngChip/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_flash_ex.c
    ../../HAL/EngChip/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_flash_ramfunc.c
    ../../HAL/EngChip/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_gpio.c
    ../../HAL/EngChip/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_dma_ex.c
    ../../HAL/EngChip/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_dma.c
    ../../HAL/EngChip/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_pwr.c
    ../../HAL/EngChip/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_pwr_ex.c
    ../../HAL/EngChip/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_cortex.c
    ../../HAL/EngChip/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal.c
    ../../HAL/EngChip/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_exti.c
    ../../HAL/EngChip/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_can.c
    ../../HAL/EngChip/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_spi.c
    ../../HAL/EngChip/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_tim.c
    ../../HAL/EngChip/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_tim_ex.c
    ../../HAL/EngChip/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_uart.c
    ../../HAL/EngChip/Core/Src/system_stm32f4xx.c
    ../../OS/FreeRTOS/Source/croutine.c
    ../../OS/FreeRTOS/Source/event_groups.c
    ../../OS/FreeRTOS/Source/list.c
    ../../OS/FreeRTOS/Source/queue.c
    ../../OS/FreeRTOS/Source/stream_buffer.c
    ../../OS/FreeRTOS/Source/tasks.c
    ../../OS/FreeRTOS/Source/timers.c
    ../../OS/FreeRTOS/Source/CMSIS_RTOS_V2/cmsis_os2.c
    ../../OS/FreeRTOS/Source/portable/MemMang/heap_4.c
    ../../OS/FreeRTOS/Source/portable/GCC/ARM_CM4F/port.c
    ../../HAL/EngChip/Core/Src/sysmem.c
    ../../HAL/EngChip/Core/Src/syscalls.c
    ../../HAL/EngChip/startup_stm32f446xx.s
)

target_link_directories(stm32cubemx INTERFACE
)

target_link_libraries(stm32cubemx INTERFACE
)

# Validate that STM32CubeMX code is compatible with C standard
if(CMAKE_C_STANDARD LESS 11)
    message(ERROR "Generated code requires C11 or higher")
endif()


