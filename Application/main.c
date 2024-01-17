//#include <stdio.h>
//#include "gd32f4xx.h"
////-----------debug----------//
//typedef struct print_buffer
//{
//    char buf[4096];
//    int idx;
//} print_buffer;
//print_buffer stdio_print_buf;
//void print_buf_putchar(struct print_buffer *buffer, char ch)
//{
//    if (buffer == NULL)
//    {
//        buffer = &stdio_print_buf;
//    }
//    if (buffer->idx >= sizeof(buffer->buf))
//    {
//        buffer->idx = 0;
//    }
//    buffer->buf[buffer->idx++] = ch;
//}
//int fputc(int ch, FILE *f)
//{
//    print_buf_putchar(NULL, ch);
//    return ch;
//    /* USART2 for printf */
//    // usart_data_transmit(EVAL_COM0, (uint8_t) ch);
//    // while (RESET == usart_flag_get(EVAL_COM0, USART_FLAG_TBE));
//    // return ch;
//}
////-----------SysTick Delay----------//
//uint32_t volatile msTicks; // Counter for millisecond Interval
//void SysTick_Handler(void)
//{ // SysTick Interrupt Handler
//    msTicks++; // Increment Counter
//}
//int get_ticks()
//{
//    return msTicks;
//}
//void delay_1tick(void)
//{
//    uint32_t curTicks;
//    curTicks = msTicks; // Save Current SysTick Value
//    while (msTicks == curTicks)
//    { // Wait for next SysTick Interrupt
//        __WFE(); // Power-Down until next Event/Interrupt
//    }
//}
//void delay_ms(int ms)
//{
//    int i;
//    for (i = 0; i < ms; i++)
//    {
//        delay_1tick();
//    }
//}
//void systick_config(void)
//{
//    /* setup systick timer for 1000Hz interrupts */
//    if (SysTick_Config(SystemCoreClock / 1000U))
//    {
//        /* capture error */
//        while (1)
//        {
//        }
//    }
//    /* configure the systick handler priority */
//    NVIC_SetPriority(SysTick_IRQn, 0x00U);
//}
////-----------GPIO LED----------//
//void U1_led_init()
//{
//    /* enable the LEDs GPIO clock */
//    rcu_periph_clock_enable(RCU_GPIOF);
//    gpio_mode_set(GPIOF, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, GPIO_PIN_4);
//    //gpio_output_options_set(GPIOF, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ,
//    //GPIO_PIN_4);
//    //gpio_bit_reset(GPIOF, GPIO_PIN_4);
//}
//void U1_led_flash(int ms)
//{
//    //gpio_bit_toggle(GPIOF, GPIO_PIN_4);
//    gpio_bit_set(GPIOF, GPIO_PIN_4);
//    delay_ms(ms);
//    gpio_bit_reset(GPIOF, GPIO_PIN_4);
//    delay_ms(ms);
//}
////-----------main----------//
//int main()
//{
//    systick_config();
//    U1_led_init();
//    while (1)
//    {
//        printf("time=%d\n", get_ticks());
//        U1_led_flash(1000);
//    }
//}



//
//#include <stdio.h>
//#include "gd32f4xx.h"
//#include "delay.h"
//
////-----------debug----------//
//typedef struct print_buffer {
//    char buf[4096];
//    int idx;
//} print_buffer;
//print_buffer stdio_print_buf;
//
//void print_buf_putchar(struct print_buffer *buffer, char ch) {
//    if (buffer == NULL) {
//        buffer = &stdio_print_buf;
//    }
//    if (buffer->idx >= sizeof(buffer->buf)) {
//        buffer->idx = 0;
//    }
//    buffer->buf[buffer->idx++] = ch;
//}
//
//int fputc(int ch, FILE *f) {
//    print_buf_putchar(NULL, ch);
//    return ch;
//    /* USART2 for printf */
//    // usart_data_transmit(EVAL_COM0, (uint8_t) ch);
//    // while (RESET == usart_flag_get(EVAL_COM0, USART_FLAG_TBE));
//    // return ch;
//}
//
//////-----------SysTick Delay----------//
////uint32_t volatile msTicks; // Counter for millisecond Interval
////void SysTick_Handler(void) { // SysTick Interrupt Handler
////    msTicks++; // Increment Counter
////}
////
////int get_ticks() {
////    return msTicks;
////}
////
////void delay_1tick(void) {
////    uint32_t curTicks;
////    curTicks = msTicks; // Save Current SysTick Value
////    while (msTicks == curTicks) { // Wait for next SysTick Interrupt
////        __WFE(); // Power-Down until next Event/Interrupt
////    }
////}
////
////void delay_ms(int ms) {
////    int i;
////    for (i = 0; i < ms; i++) {
////        delay_1tick();
////    }
////}
////
////void systick_config(void) {
////    /* setup systick timer for 1000Hz interrupts */
////	printf("entry...\n");
////    if (SysTick_Config(SystemCoreClock / 10000000U)) {
////        /* capture error */
////        while (1) {
////            printf("---\n");
////      }
////    }
////	printf("success...\n");
////    /* configure the systick handler priority */
////    NVIC_SetPriority(SysTick_IRQn, 0x00U);
////}
////
//////-----------GPIO LED----------//
////void U1_led_init()
////{
////    /* enable the LEDs GPIO clock */
////    rcu_periph_clock_enable(RCU_GPIOF);
////    gpio_mode_set(GPIOF, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, GPIO_PIN_4);
////    //gpio_output_options_set(GPIOF, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ,
////    //GPIO_PIN_4);
////    //gpio_bit_reset(GPIOF, GPIO_PIN_4);
////}
////void U1_led_flash(int ms)
////{
////    //gpio_bit_toggle(GPIOF, GPIO_PIN_4);
////    gpio_bit_set(GPIOF, GPIO_PIN_4);
////    delay_ms(ms);
////    gpio_bit_reset(GPIOF, GPIO_PIN_4);
////    delay_ms(ms);
////}
//
//
//void U1_led_init() {
//    /* enable the LEDs GPIO clock */
//    rcu_periph_clock_enable(RCU_GPIOF);
//    rcu_periph_clock_enable(RCU_GPIOC);
//
//    gpio_mode_set(GPIOC, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, GPIO_PIN_10);
//    gpio_mode_set(GPIOF, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, GPIO_PIN_4);
//
//    gpio_output_options_set(GPIOF, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ, GPIO_PIN_4);
//    gpio_output_options_set(GPIOC, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ, GPIO_PIN_10);
//
//
//    //gpio_output_options_set(GPIOF, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ,
//    //GPIO_PIN_4);
//    //gpio_bit_reset(GPIOF, GPIO_PIN_4);
//}
//
//void U1_led_flash(int us) {
//    //gpio_bit_toggle(GPIOF, GPIO_PIN_4);
//    gpio_bit_set(GPIOC, GPIO_PIN_10);
//    gpio_bit_set(GPIOF, GPIO_PIN_4);
//	printf("---");
//    delay_us(us);
//	  printf("!!!");
//    gpio_bit_reset(GPIOC, GPIO_PIN_10);
//    gpio_bit_reset(GPIOF, GPIO_PIN_4);
//		printf("---");
//    delay_us(us);
//		  printf("!!!");
//
//}
//
//
////-----------main----------//
//int main() {
//    Delay_Init();
//    U1_led_init();
//    while (1) {
//        printf("time=%d\n", micros());
//        U1_led_flash(10);
//        //test();
//    }
//}