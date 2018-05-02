# -*- coding: utf-8 -*-
"""
Created on Mon Apr 30 09:21:20 2018

@author: gokul
"""

import numpy as np
import matplotlib.pyplot as plt


f,ax = plt.subplots(1)


D_list = [1]
F_list=[3]
for D in D_list:
    for F in F_list:
        #tau=1.0
        #filename = "2018-04-29.22:15:46-entropy-production-D=1.000000_Dr=1.000000_Fa=1.000000_N=1000000_tau=5.000000.csv"
        filename = "entropy-production-D=%d.000000_Dr=1.000000_Fa=%d.000000_N=1000000_tau=5.000000.csv"%(D,F)
        #filename = "2018-04-30.00:23:29-entropy-production-D=1.000000_Dr=1.000000_Fa=5.000000_N=1000000_tau=5.000000.csv"
        #filename = "2018-04-30.00:23:13-entropy-production-D=3.000000_Dr=1.000000_Fa=1.000000_N=1000000_tau=5.000000.csv"
        #filename = "2018-04-30.01:17:47-entropy-production-D=5.000000_Dr=1.000000_Fa=1.000000_N=1000000_tau=5.000000.csv"
        g = open("Figures/"+filename,"r")
        data = []
        for item in g:
            row=item.rstrip('\n')
            row_as_array = row.split(',')
            row_as_array = np.asarray(row_as_array[:-1])
            row_as_array = row_as_array.astype(float)
            data.append(row_as_array)
        data = np.asarray(data)
        g.close()
        
        tau_list = data[0]
        work_data = data[1:]
        del data
        
        #plt.grid()
        ax.set_xlabel("$W_\\tau$",fontsize=30)
        ax.set_ylabel("$J(W_\\tau)$",fontsize=30)
        #tau_list=[1.0]
        for i in xrange(0,len(tau_list)):
            tau = tau_list[i]    
            work_list = work_data[:,i]
            Prob_W = np.histogram(work_list,bins=49,density = True)
            A_tau = max(Prob_W[0])
            LDF_W = -(1/tau)*np.log(Prob_W[0]/float(A_tau))        
            
            
            #legend = axis.legend()
            #ax.plot(Prob_W[1][:-1],LDF_W,linewidth=4,label="$\\tau=$%.1f"%tau)
            #ax.plot(Prob_W[1][:-1],LDF_W,linewidth=4,label="$D=%.1f$"%D)
            ax.plot(Prob_W[1][:-1],LDF_W,linewidth=4,label="$F_a=%.1f$"%F)            
            #ax.scatter(Prob_W[1][:-1],LDF_W,s=30,label="$\\tau=$%.1f"%tau)    
            
            g = open("Output/LDF/tau=%f-LDF-"%tau+filename,"w")
            for i in xrange(0,len(LDF_W)):
                g.write(str(Prob_W[1][i])+","+str(LDF_W[i])+"\n")
            g.close()  
        #plt.hist(work_list,normed=True)    
ax.legend(fontsize=25,loc=3)
#ax.set_xlim([-20,20])
ax.set_xticks(range(-20,25,5)+[1])
ax.tick_params(labelsize=20)
ax.grid()