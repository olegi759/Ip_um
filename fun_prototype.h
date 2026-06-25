/**************************************
программа контроля звуковых линий IP усилителя
*********************************************/

void init_ipCL(void);
//задержка
void delay_ipCL(BYTE v);
//загрузка tpic1
void set_tpic1(void);
//загрузка tpic2
void set_tpic2(void);
//обработка команды
void work_PC(void);
void delayed_response_PC(void);
//проверка входов с внешн компаратора
void test_in_comp(void);
//запуск тестирования
void set_test_L1(void);
void set_test_L2(void);
void set_test_L3(void);
void set_test_L4(void);
//выплонение шага тестирования
void step_test_L(void);
//инсталяция звуковых линий
void install_SL(void);
//выбор оптимального значения
BYTE optimal_value_selection(BYTE chNumber);

void set_f_start_test_Lx(void);
void Ulog(char *txt);
void UlogParam(char *txt, int val);

#ifdef DEBUG
    #define Ulog(txt) Ulog(txt)
    #define UlogParam(txt, val) UlogParam(txt, val)
#else
    #define Ulog(txt) do { } while(0)
    #define UlogParam(txt, val) do { } while(0)
#endif