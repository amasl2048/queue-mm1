#Queuing system M/M/1

Running simulation for 10,000,000 time intervals:
```
$ ./qtest 10000000
Usage: qtest [htime] [qmax] [lambda1]
Default qmax = 15
Default lambda1 = 0.9
```
where:

- `qmax    = 15    //queue size`

- `lambda1 = 0.9   //new order arriving intensity`

- `lambda2 = 1     //serving intensity`

Output:
```
--System--
Mes.In      Mes.Out     Ratio%
90001960	88004026	2.21988

In	     Out	      Roh
0.90002	 1.00014	  0.899897

--Queue--
T free = 2.28124e+07	T busy = 7.71876e+07	Totaly = 1e+08
Max	Qsize	Entries	    Entry(0)	Ave.size	Ave.time
15	13	    77195660	9724323		4.71512		6.10802
W system = 6.23891 min
Drops = 1997920	2.21986%

--Server--
T free = 1.20079e+07	T busy = 8.79921e+07	Totaly = 1e+08
Busy	Entries	        Util.		Ave.time
1	    88004027	    0.879921	0.999864
```

Formula calculation:
```
$ ./mm1.py
pb   = 0.0222    # block probability
navg = 5.5974    # average orders in a system
tavg = 6.2194    # average time in a system
u    = 0.8800    # throughput

```
