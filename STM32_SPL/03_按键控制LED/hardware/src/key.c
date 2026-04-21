#include "stm32f10x.h"

// 按键驱动头文件
#include "key.h"
// LED驱动头文件（控制LED亮灭）
#include "led.h"

/*
 * 函数名称：Key_Init
 * 函数功能：按键初始化（外部中断方式）
 * 入口参数：无
 * 返回参数：无
 * 说明：配置 PA1 为按键中断，下降沿触发，用来控制LED
*/
void Key_Init(void)
{
    // 定义三个结构体变量，用来存放配置参数
    // 标准库必须用结构体传参，这是固定写法
    GPIO_InitTypeDef gpio_initstruct;      // GPIO配置结构体
    EXTI_InitTypeDef exti_initstruct;      // 外部中断配置结构体
    NVIC_InitTypeDef nvic_initstruct;      // 中断优先级配置结构体

    /* ===================== 第一步：开时钟 ===================== */
    // STM32任何外设使用前必须开时钟，否则无法工作！
    // 使能 GPIOA 时钟（按键在PA1）
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
    
    // 使能 AFIO 时钟（外部中断必须开AFIO！）
    // 因为EXTI中断线和GPIO的映射由AFIO管理
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);

    /* ===================== 第二步：配置GPIO ===================== */
    // 按键配置：上拉输入模式（GPIO_Mode_IPU）
    // 为什么上拉？
    // 按键一端接GND，一端接PA1，松开时PA1=高电平，按下=低电平
    gpio_initstruct.GPIO_Mode = GPIO_Mode_IPU;    // 上拉输入模式
    
    gpio_initstruct.GPIO_Pin = GPIO_Pin_1;        // 配置 PA1
    
    gpio_initstruct.GPIO_Speed = GPIO_Speed_50MHz;// 输入模式下速度无效，随便写
    
    GPIO_Init(GPIOA, &gpio_initstruct);           // 把配置写入寄存器

    /* ===================== 第三步：GPIO映射到EXTI中断线 ===================== */
    // 作用：把 PA1 映射到 EXTI1 中断线
    // 规则：Px1 都对应 EXTI1，Px2对应EXTI2，以此类推
    GPIO_EXTILineConfig(GPIO_PortSourceGPIOA, GPIO_PinSource1);

    /* ===================== 第四步：配置EXTI外部中断 ===================== */
    exti_initstruct.EXTI_Line = EXTI_Line1;        // 使用中断线1（对应PA1）
    exti_initstruct.EXTI_LineCmd = ENABLE;         // 开启该中断线
    exti_initstruct.EXTI_Mode = EXTI_Mode_Interrupt; // 中断模式（不是事件模式）
    
    // 触发方式：下降沿触发
    // 为什么下降沿？
    // 按键松开：PA1=高电平
    // 按键按下：PA1=高 → 低（下降沿），触发中断
    exti_initstruct.EXTI_Trigger = EXTI_Trigger_Falling;

    EXTI_Init(&exti_initstruct);  // 写入配置

    /* ===================== 第五步：配置NVIC中断优先级 ===================== */
    nvic_initstruct.NVIC_IRQChannel = EXTI1_IRQn;    // EXTI1中断通道
    nvic_initstruct.NVIC_IRQChannelCmd = ENABLE;     // 开启中断
    
    // 抢占优先级2，子优先级2
    // 优先级数值越大，优先级越低
    // 这里只要不跟系统中断冲突即可，2/2是通用配置
    nvic_initstruct.NVIC_IRQChannelPreemptionPriority = 2;
    nvic_initstruct.NVIC_IRQChannelSubPriority = 2;

    NVIC_Init(&nvic_initstruct);
}

/*
 * 函数名称：EXTI1_IRQHandler
 * 函数功能：EXTI1中断服务函数（固定名称，不可修改）
 * 入口参数：无
 * 返回参数：无
 * 说明：按键按下时，CPU自动跳到这个函数执行
 */
void EXTI1_IRQHandler(void)
{
    // 1. 消抖：等待10ms，避开按键机械抖动
    DelayXms(10);

    // 2. 再次判断按键是否真的按下（PA1为低电平）
    if(GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_1) == 0)
    {
        // 3. 按键功能：翻转LED状态
        if(led_info.Led_Status == LED_ON)
            Led_Set(LED_OFF);   // 亮 → 灭
        else
            Led_Set(LED_ON);    // 灭 → 亮
    }

    // 4. 必须清除中断标志位！
    // 不清零，中断会一直触发，程序卡死
    EXTI_ClearITPendingBit(EXTI_Line1);
}