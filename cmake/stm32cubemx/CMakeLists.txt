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
    ../../App/EngFOC
    ../../App/EngIFSvc
    ../../App/EngTimer

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
    ../../HAL/EngHAL/STM32F4xx

    ../../HAL/EngChip/Drivers/CMSIS/DSP/Include
)

target_sources(stm32cubemx INTERFACE
    ../../App/EngSM_IF.c
    ../../App/EngSM_Main.c
    ../../App/EngFOC/EngFOC_IF.c
    ../../App/EngFOC/EngFOC_Main.c
    ../../App/EngIFSvc/EngIFSvc_IF.c
    ../../App/EngIFSvc/EngIFSvc_Main.c
    ../../App/EngTimer/EngTimerSvc_IF.c
    ../../App/EngTimer/EngTimerSvc_Main.c

    ../../Drv/EngDrv_IF.c
    ../../Drv/EngDrv_ADC.c
    ../../Drv/EngDrv_CAN.c
    ../../Drv/EngDrv_Encoder.c
    ../../Drv/EngDrv_Flash.c
    ../../Drv/EngDrv_Sensor.c
    ../../Drv/EngDrv_SPI.c
    ../../Drv/EngDrv_UART.c

    ../../Infra/EngLib/EngLib_IF.c
    ../../Infra/EngLib/EngLib_Main.c
    ../../Infra/EngLib/EngLog_IF.c
    ../../Infra/EngLib/EngLog_Lib.c
    ../../Infra/EngLib/EngOS_Lib.c

    ../../Infra/EngCM/EngCM_IF.c
    
    ../../HAL/EngChip/Core/Src/main.c
    ../../HAL/EngChip/Core/Src/freertos.c
    ../../HAL/EngChip/Core/Src/stm32f4xx_it.c
    ../../HAL/EngChip/Core/Src/stm32f4xx_hal_msp.c
    ../../HAL/EngChip/Core/Src/system_stm32f4xx.c

    ../../HAL/EngHAL/EngHal_Lib.c
    ../../HAL/EngHAL/STM32F4xx/EngHAL_Base_STM32F4xx.c
    ../../HAL/EngHAL/STM32F4xx/EngHAL_Core_STM32F4xx.c
    ../../HAL/EngHAL/STM32F4xx/EngHAL_ADC_STM32F4xx.c
    ../../HAL/EngHAL/STM32F4xx/EngHAL_PWM_STM32F4xx.c
    ../../HAL/EngHAL/STM32F4xx/EngHAL_CAN_STM32F4xx.c
    ../../HAL/EngHAL/STM32F4xx/EngHAL_GPIO_STM32F4xx.c
    ../../HAL/EngHAL/STM32F4xx/EngHAL_I2C_STM32F4xx.c
    ../../HAL/EngHAL/STM32F4xx/EngHAL_UART_STM32F4xx.c
    ../../HAL/EngHAL/STM32F4xx/EngHAL_PWR_STM32F4xx.c
    ../../HAL/EngHAL/STM32F4xx/EngHAL_RTC_STM32F4xx.c
    ../../HAL/EngHAL/STM32F4xx/EngHAL_SRAM_STM32F4xx.c
    ../../HAL/EngHAL/STM32F4xx/EngHAL_SPI_STM32F4xx.c

    ../../HAL/EngChip/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_adc.c
    ../../HAL/EngChip/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_adc_ex.c
    ../../HAL/EngChip/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_i2c.c
    ../../HAL/EngChip/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_i2c_ex.c
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
    ../../HAL/EngChip/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_rtc.c
    ../../HAL/EngChip/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_rtc_ex.c

    ../../HAL/EngChip/Drivers/CMSIS/DSP/Source/FastMathFunctions/arm_cos_f32.c
    ../../HAL/EngChip/Drivers/CMSIS/DSP/Source/FastMathFunctions/arm_sin_f32.c
    ../../HAL/EngChip/Drivers/CMSIS/DSP/Source/CommonTables/arm_common_tables.c

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


