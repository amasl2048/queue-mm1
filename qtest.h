/*qtest.h*/

int qsize = 0; // текущая длина очереди
int qm    = 0; // макс. длина очереди
int busy  = 0; // сервер свободен
double c_time = 1E12; // время обслуживания (макс.)
float htime  = 1000; // время теста
double atime  = 1E-9; // начальное время поступления требования
double u, r;          // переменные для хранения случайных величин
//int maxtime = 1000 * 1000 * 1000;

long int mbase = 4294967296; // pow(2, 23)
long int xi; // random value

int in    = 0; // счетчик поступления требований в систему
int out   = 0; // счетчик требований поступающих на сервер
int q_in  = 0; // счетчик поступления требований в очередь
int q0    = 0; // счетчик пустой очереди
int s_in  = 0;
int s_out = 0; // счетчик обслуженных требований

double qqq    = 0.0; //средняя длина очереди
double ltime  = 0.0; // время прихода последнего требования
float lambda1 = 0.9; // значение интенсивности потока требований 
float lambda2 = 1.0; // значение интенсивности обслуживания

int qmax       = 15; // макс. возможная очередь
int pdrop      = 0;  // счетчик сброшенных пакетов

double tbusy    = 0.0;
double tfree    = 0.0;
double tbusy_1  = 0.0; // время предыдущего события
double tfree_1  = 0.0;
double qtbusy   = 0.0;
double qtfree   = 0.0;
double qtbusy_1 = 0.0; // время предыдущего события
double qtfree_1 = 0.0;
double qtave    = 0.0; // время проведенное в очереди

ofstream queue("queue.txt");
ofstream drop("drop.txt");
ofstream mean1("mean1.txt");
ofstream mean2("mean2.txt");

void new_order();
void server_in();
void packet_drop();
void queue_in();
void new_atime();
void service();
void server_free();
void queue_out();
void stop_test();

void out_data();

// log files
ofstream new_order_log ("new_order.log");
ofstream atime_log ("atime.log");
ofstream c_time_log ("c_time.log");


