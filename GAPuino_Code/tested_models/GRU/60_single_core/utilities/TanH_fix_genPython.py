import h5py
import numpy as np
import matplotlib.pyplot as plt  
import math 
'''
def sigmoid(x):
    z=1/(1 + np.exp(-x))
    return z 
'''

asse_x= np.arange(-2.5,-0.24,0.01)
#print(np.amax(asse_x))
asse_x= np.concatenate((asse_x, [0]))
#print(np.amax(asse_x))
#asse_x=np.array([-2.5, -2.4, -2.3, -2.2, -2.1, -2, -1.9, -1.8, -1.7, -1.6, -1.5, -1.4, -1.3, -1.2, -1.1, -1.0, -0.9, -0.8, -0.7, -0.6, -0.5, -0.4, -0.3, -0.2, -0.1, 0])
asse_y= np.tanh(asse_x)


scale=pow(2,13)
scale2=pow(2,13)
asse_x=np.int32(np.trunc(scale*asse_x))
asse_y=np.int32(np.trunc(scale2*asse_y))
'''
plt.plot(asse_x, asse_y)
plt.show()
print(asse_y)
'''

mylist=[]


for n_steps in range(len(asse_x)):
	mylist.append((asse_y[n_steps], asse_x[n_steps]))

def produce_c_code(numbers_list, idxs, idxe, level):
    if idxs >= idxe:
        raise RuntimeError("idxs=%d idxe=%d")

    indent= " "*level

    if idxs + 1 == idxe: # end of recursion
        yield indent*4 + "r= (%d>>scale_out)" % numbers_list[idxs][0]
    else:
        idxm= (idxe+idxs)//2
        yield indent*4 + "if i>= (%d>>scale_in) :" % numbers_list[idxm][1]
        yield from produce_c_code(numbers_list, idxm, idxe, level+1)
        yield indent*4 + "else :"
        yield from produce_c_code(numbers_list, idxs, idxm, level+1)

gen_obj = produce_c_code(mylist, 0, len(asse_x), 0)
for el in gen_obj:print(el)
