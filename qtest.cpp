/* qtest.cpp		 			*/
/* System M/M/1:15 				*/
/* version v0.3 (15.06.2010)			*/
#include <iostream>
#include <sstream>
#include <fstream>
#include <math.h>
#include <cstdlib>

using namespace std;

#include "arg.h"
#include "qtest.h"

int main(int argc, char **argv) {

// ввод данных из командной строки
if (argc == 1 | argc > 4) {
  cout << "Usage: qtest [htime] [qmax] [lambda1]\n";
  cout << "Default htime = " << htime << "\n";
  cout << "Default qmax = " << qmax << "\n";
  cout << "Default lambda1 = " << lambda1 << "\n";
}
if (argc == 2) {
  cout << "Usage: qtest [htime] [qmax] [lambda1]\n";
  cout << "Default qmax = " << qmax << "\n";
  cout << "Default lambda1 = " << lambda1 << "\n";
  istringstream(argv[1]) >> htime;
}
if (argc == 3) {
  cout << "Usage: qtest [htime] [qmax] [lambda1]\n";
  cout << "Default lambda1 = " << lambda1 << "\n";
  istringstream(argv[1]) >> htime;
  istringstream(argv[2]) >> qmax;
}
if (argc == 4) {
  cout << "Usage: qtest [htime] [qmax] [lambda1]\n";
  istringstream(argv[1]) >> htime;
  istringstream(argv[2]) >> qmax;
  istringstream(argv[3]) >> lambda1;
}

srand ( time(NULL) );
//srand (1);
xi = rand() % mbase + 1;

while (atime <= htime | c_time <= htime) {// пока момент времени прихода нового требования или обслуживания меньше времени теста
	
    if (atime <= htime & atime <= c_time) { // и момент времени прихода нового требования меньше окончания обслуживания
		
		new_order(); // новое требование
		if (busy == 0)	{ // если сервер свободен
				server_in();
		}
		else { // иначе если сервер занят - далее 2 варианта
            if (qsize >= qmax) {
				packet_drop(); // если очередь заполнена, то сброс пакета
			}
			else {
				queue_in(); // иначе помещение В ОЧЕРЕДЬ
			}
	    }
		new_atime(); // время следующего требования
	}
    else { // иначе обслуживание
		
		service(); //далее 2 варианта
		if (qsize == 0)	{ // очередь пуста
          server_free(); // ОСВОБОЖДЕНИЕ СЕРВЕРА 
		}
		else {
          queue_out(); // обслуживание ИЗ ОЧЕРЕДИ
		}
		s_out++;
    }
}
stop_test();
out_data();
return 0;
}

void new_order() {
  in++;
  //new_order_log.precision(16); 
  //new_order_log << atime << " " << c_time << "\n";
}

void server_in() {
  
  busy    = 1; // ЗАНЯТИЕ СЕРВЕРА
  s_in++;
  tfree   = tfree + atime - tfree_1;  // счетчик свободного времеи сервера
  tbusy_1 = atime;
  xi      = urn13(xi);
  u       = double(xi) / double(mbase);
  r       = func1(lambda2, u);

  //mean2.precision(16); 
  //mean2 << xi << "\t" << u << "\t" << r << endl;

  c_time  = atime + r; // время окончания обслуживания
  
  //c_time_log.precision(16); 
  //c_time_log << c_time << "\n";

}

void packet_drop() {
  
  pdrop++; // счетчик сброшенных пакетов
  //drop.precision(16); 
  //drop << atime << " " << qsize << "\n"; // запись момента сброса
  
}

void queue_in() {
  q_in++;

  if (qsize == 0) {
      q0++; // счетчик пустой очереди
      qtfree   = qtfree + atime - qtfree_1; // счетчик свободного времени очереди
      qtbusy_1 = atime;
  }

  qqq   = (qqq * ltime + qsize * (atime - ltime)) / atime; //средняя длина очереди
  qtave = qtave + qsize * (atime - ltime);           // время проведенное в очереди
  ltime = atime;                                     // время прихода последнего требования
  qsize++;                                           // текущее кол-во требований в очереди

  if (qsize > qm) {
    qm = qsize;                                      // макс. длина
  }
  
  //queue.precision(16); 
  //queue << atime << " " << qsize << " " << "in\n";   // запись момента буферизации
}

void new_atime() {

  xi      = urn13(xi);
  u       = double(xi) / double(mbase);
  r       = func1(lambda1, u);
  
  //mean1.precision(16); 
  //mean1 << xi << "\t" << u << "\t" << r << endl;
  
  atime = atime + r; // new arrival time
  
  //atime_log.precision(16); 
  //atime_log << atime << "\n";

}

void service() {
  out++;
}

void server_free() {
  busy    = 0; 
  tbusy   = tbusy + c_time - tbusy_1; // счетчик времени занятия сервера
  tfree_1 = c_time;
  c_time  = 1E12; 
}

void queue_out() {
  s_in++;
  qqq   = ( qqq * ltime + qsize * (c_time - ltime) ) / c_time; 
  qtave = qtave + qsize * (c_time - ltime); // время проведенное в очереди
  ltime = c_time;
  qsize--;

  if (qsize==0) {
    qtbusy   = qtbusy + c_time - qtbusy_1; // счетчик свободного времени очереди
    qtfree_1 = c_time;
  }
  
  //queue.precision(16); 
  //queue << c_time << " " << qsize << " " << "out\n"; //запись ухода пакета
  
  xi      = urn13(xi);
  u       = double(xi) / double(mbase);
  r       = func1(lambda2, u);

  //mean2.precision(16); 
  //mean2 << xi << "\t" << u << "\t" << r << endl;
  
  c_time = c_time + r; // новое время окончания обслуживания
  
}

void stop_test()
{
  if (qsize == 0) {
    qtfree = qtfree + htime - qtfree_1;
  }
  else {
    qtbusy = qtbusy + htime - qtbusy_1;
  }

  if (busy == 0) {
    tfree = tfree + htime - tfree_1;
  }
  else {
    tbusy = tbusy + htime - tbusy_1;
  }

  qtave = (qtave + ( (htime - ltime) * qsize) ) / q_in; // ср. время в очереди
}

void out_data () {
  
  float roh, in1, out1;

  roh = (float)s_out / (float)in;
  cout << "\n--System--\n";
  cout << "Mes.In" << "\t" << "Mes.Out" << "\t" << "Ratio%" << "\n";
  cout << in << "\t" << s_out << "\t" << (1 - roh) * 100 << "\n";

  // Расчетные интенсивности
  in1  = (float)in    / (float)htime;
  out1 = (float)s_out / (float)tbusy;
  cout << "\nIn" << "\t" << "Out" << "\t" << "Roh" << "\n";
  cout << in1 << "\t" << out1 << "\t" << in1/out1 << "\n";

  cout << "\n--Queue--\n";
  cout << "T free = " << qtfree << "\t" << "T busy = " << qtbusy << "\t"<< "Totaly = " << qtbusy+qtfree << "\n";
  cout << "Max" << "\t" << "Qsize" << "\t" << "Entries"  << "\t" << "Entry(0)"<< "\t" << "Ave.size" << "\t" << "Ave.time" << "\n";
  cout << qm << "\t" << qsize << "\t" << q_in << "\t" << q0 << "\t\t" << qqq << "\t\t" << qtave << "\n";
  cout << "W system = " << qqq/in1+1/lambda2 << " min\n";
  cout << "Drops = " << pdrop << "\t" << (float)pdrop/(float)in*100 << "%\n";

  cout << "\n--Server--\n";
  cout << "T free = " << tfree << "\t" << "T busy = " << tbusy << "\t" << "Totaly = " << tbusy+tfree << "\n";
  cout << "Busy" << "\t" << "Entries"  << "\t" << "Util." << "\t\t" << "Ave.time" << "\n";
  cout << busy << "\t" << s_in << "\t" << tbusy/(tbusy+tfree) << "\t\t" << tbusy/(float)s_in << "\n\n";

}
