//
// Created by star on 2023/12/7.
//

//#include "delay.h"
//#include <stdio.h>
//
//static uint32_t usTicks ;
//volatile uint32_t SysTickUptime  = 0  ; //systick 每1ms 中断一次
//
//void Delay_Init(void)
//{
//    SysTick_Config(SystemCoreClock/1000 ) ;
//    /*
//        这里的系统时钟是100mhz，一个时钟周期有 1 / 100 000 000 s   也就是一个时钟周期有 10ns
//        我们需要计数到1ms，也就是100 000个周期，也就是100 000个10ns
//        所以 SystemCoreClock/1000
//        1ms 开启systick中断一次
//    */
//    usTicks = SystemCoreClock/1000000 ; //1us的滴答数 usTicks = 100
//    //usTicks = SystemCoreClock/10000000 ; // 100ns 7个0
//}
//
///* 毫秒级运行定时器 ， 返回的是毫秒
//SysTickUptime 溢出时间大概49天 */
//uint32_t millis(void)
//{
//    return SysTickUptime ;
//}
//
///* 毫秒级延时函数  */
//void delay_ms(uint32_t ms)
//{
//    uint32_t now_time = millis();
//    while(millis() - now_time  < ms) { }
//}
//
///* 微秒级计数函数  */
//uint32_t  micros ( void )
//{
////    printf("---\n");
//    uint32_t  ms ,  cycle_cnt ;
//		//		printf("@@\n");
//    do{
//        ms = SysTickUptime ;
//        cycle_cnt = SysTick->VAL ;
//    }while(ms != SysTickUptime ) ;
//    return (ms * 1000 ) + ( ( (SystemCoreClock/1000)   - cycle_cnt )  / usTicks ) ;
//
//}
//
///* 微秒级延时函数  */
//void delay_us(uint32_t us)
//{
//    uint32_t now_time = micros();
//    while(1){
//        uint32_t t=micros();
//        if(t-now_time>=us)
//            break;
//    }
//    // while(micros() - now_time  < us) { }
//		printf("end\n");
//}
//
///*举个简单的例子理解一下 假如 我们这里选择 100mhz
//        此时SysTickUptime = 100 表示自系统启动以来已经过了100ms
//        在某一时刻，我们调用micros函数，SysTick->VAL当前的值是50000
//        （表示自上次SysTick中断以来已经过了50000个周期）
//
//        那么此时是多少毫秒呢
//也就是计算 SysTickUptime * 1000 + （1000000 - SysTick->VAL） / usTicks
//（1000000 - SysTick->VAL） / usTicks 表示走过的50000个周期 有少个usTicks 1个usTicks 也就是1us
//
//*/
