#!/usr/bin/python3
'''
M/M/1:n system calculation
'''

n  = 16     # max orders in a system (incl. server)
la = 0.9    # arrival intensity
mu = 1      # serving intensity
roh = la / mu

rn = pow(roh, n + 1)
p0 = (1 - roh) / (1 - rn)         # free queue probability
pb = p0 * rn / roh                

navg = roh / (1-roh) - (n+1) * rn/(1-rn)  
tavg = navg / la                    
u    = mu * (1 - p0)                

out = '''
pb   = %.4f    # block probability
navg = %.4f    # average orders in a system
tavg = %.4f    # average time in a system
u    = %.4f    # throughput
'''
print(out % (pb, navg, tavg, u))
