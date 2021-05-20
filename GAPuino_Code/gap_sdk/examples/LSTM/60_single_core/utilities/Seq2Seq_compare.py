import h5py
import numpy as np
import matplotlib.pyplot as plt  
import math 
import Utility as uf

from pickle import load

#carico il modello
model = h5py.File('27_9EDU1LSTM_60OneYear.h5', 'r')

#carico lo scaler
scaler = load(open('scaler.pkl', 'rb'))

#Leggo i pesi della rete
dense_bias = np.array((((model['model_weights'])['dense_12'])['dense_12'])['bias:0'])
dense_kernel = np.array((((model['model_weights'])['dense_12'])['dense_12'])['kernel:0'])

Encoder_lstm_bias = np.array((((model['model_weights'])['rnn_23'])['rnn_23'])['bias:0'])
Encoder_lstm_kernel = np.array((((model['model_weights'])['rnn_23'])['rnn_23'])['kernel:0'])
Encoder_lstm_rec_ker = np.array((((model['model_weights'])['rnn_23'])['rnn_23'])['recurrent_kernel:0'])

Decoder_lstm_bias = np.array((((model['model_weights'])['rnn_24'])['rnn_24'])['bias:0'])
Decoder_lstm_kernel = np.array((((model['model_weights'])['rnn_24'])['rnn_24'])['kernel:0'])
Decoder_lstm_rec_ker = np.array((((model['model_weights'])['rnn_24'])['rnn_24'])['recurrent_kernel:0'])

'''
print(np.amin(Encoder_lstm_bias))
print(np.amax(Encoder_lstm_bias))
print(Encoder_lstm_kernel.shape, Encoder_lstm_rec_ker.shape, Encoder_lstm_bias.shape)
print(dense_kernel.shape, dense_bias.shape)
'''
layers=60
steps_in=27
steps_out=9
#scale=pow(2,14)


##Funzioni non lineari
def sigmoid(x):
    z=1/(1 + np.exp(-x))
    return z 

def hyperbolic_tangent(x):
    return (np.exp(x) - np.exp(-x))/(np.exp(x) + np.exp(-x))

# hard sigmoid function element wise
def hard_sig(x):
    # in Keras for both tensorflow and theano backend
    return np.max(np.array([0.0, np.min(np.array([1.0, x * 0.2 + 0.5]))]))

def hard_sigmoid(x, fun=hard_sig):
    return np.vectorize(fun)(x)


#preparo dataset per inferenza
#carico test sequence
input_seq_test = np.load('Input_seq_test.npy')
output_seq_test = np.load('Output_seq_test.npy')

x = input_seq_test[0:2,:]
y = output_seq_test[0:2,:]
#print(x[0,0])


Outputs = []

######################################  FLOATING POINT  ######################################

Encoder_c_0_lstm = np.zeros((1, layers))
Encoder_h_0_lstm = np.zeros((1, layers))
#for n_input in range(x.shape[0]):
for n_input in range(1):

	#Encoder LSTM
#	print(x[n_input,:])
	Encoder_c_0_lstm = np.zeros((1, layers))
	Encoder_h_0_lstm = np.zeros((1, layers))

	for n_steps in range(steps_in):
	#for n_steps in range(1):
		z_lstm = np.dot(x[n_input,n_steps], Encoder_lstm_kernel) + np.dot(Encoder_h_0_lstm, Encoder_lstm_rec_ker) + Encoder_lstm_bias
		i_lstm = hard_sigmoid(z_lstm[:, 0:layers])
		f_lstm = hard_sigmoid(z_lstm[:, layers:layers*2])
		input_to_c_lstm = z_lstm[:, layers*2:layers*3]
		o_lstm = hard_sigmoid(z_lstm[:, layers*3:layers*4])
		#print(i_lstm)
		c_lstm = np.multiply(f_lstm, Encoder_c_0_lstm) + np.multiply(i_lstm, np.tanh(input_to_c_lstm))
		h_lstm = np.multiply(o_lstm, np.tanh(c_lstm))
		Encoder_c_0_lstm=c_lstm
		Encoder_h_0_lstm=h_lstm

	#print(z_lstm[:, layers:layers*2])
#	print(Encoder_h_0_lstm)
#	print(Encoder_c_0_lstm)
	#Decoder LSTM

	Decoder_c_0_lstm = Encoder_c_0_lstm
	Decoder_h_0_lstm = Encoder_h_0_lstm


	for n_steps in range(steps_out):
	#for n_steps in range(1):
		z_lstmD = np.dot(Decoder_h_0_lstm, Decoder_lstm_rec_ker) + Decoder_lstm_bias
		i_lstmD = hard_sigmoid(z_lstmD[:, 0:layers])
		f_lstmD = hard_sigmoid(z_lstmD[:, layers:layers*2])
		input_to_c_lstmD = z_lstmD[:, layers*2:layers*3]
		o_lstmD = hard_sigmoid(z_lstmD[:, layers*3:layers*4])
		c_lstmD = np.multiply(f_lstmD, Decoder_c_0_lstm) + np.multiply(i_lstmD, np.tanh(input_to_c_lstmD))
		h_lstmD = np.multiply(o_lstmD, np.tanh(c_lstmD))
		Decoder_c_0_lstm=c_lstmD
		Decoder_h_0_lstm=h_lstmD
		##Dense Layer
		Output_dense = np.dot(Decoder_h_0_lstm, dense_kernel)+ dense_bias
		Outputs.append(Output_dense)


Outputs = np.array(Outputs)

#print('output :',Outputs)
#print('Valori attesi: ',y)
#print('output :', scaler.inverse_transform(Outputs.reshape(-1,1)))



######################################  FIXED POINT(16,12)  ######################################

##Scaling Factors
scale_shift=11  #ricorda di cambiarlo anche all'interno delle Utility function
scale=pow(2,scale_shift)
unscale=pow(2, -scale_shift)
scale2=pow(2,scale_shift*2)
unscale2=pow(2,-scale_shift*2)

##Coefficients Scaling
Encoder_lstm_bias_fix = np.int32(np.trunc(scale2*Encoder_lstm_bias)) #(32,24)
Encoder_lstm_kernel_fix = np.int32(np.trunc(scale*Encoder_lstm_kernel))#(32,12)
Encoder_lstm_rec_ker_fix = np.int32(np.trunc(scale*Encoder_lstm_rec_ker))#(32,12)

Decoder_lstm_bias_fix = np.int32(np.trunc(scale2*Decoder_lstm_bias))#(32,24)
Decoder_lstm_kernel_fix = np.int32(np.trunc(scale*Decoder_lstm_kernel))#(32,12)
Decoder_lstm_rec_ker_fix = np.int32(np.trunc(scale*Decoder_lstm_rec_ker))#(32,12)

dense_bias_fix = np.int32(np.trunc(scale2*dense_bias))#(32,24)
dense_kernel_fix = np.int32(np.trunc(scale*dense_kernel))#(32,12)

##Input Scaling

Input_seq_test_fix = np.int32(np.trunc(input_seq_test*scale))#(32,12)
x_fix = Input_seq_test_fix[0:2,:]

Outputs_fix = []

#for n_input in range(x.shape[0]):
for n_input in range(1):

	#Encoder LSTM

	Encoder_c_0_lstm_fix = np.int32(np.zeros((1, layers)))
	Encoder_h_0_lstm_fix = np.int32(np.zeros((1, layers)))

	#for n_steps in range(2):
	for n_steps in range(steps_in):
		z_lstm_fix = np.dot(x_fix[n_input,n_steps], Encoder_lstm_kernel_fix) + np.dot(Encoder_h_0_lstm_fix, Encoder_lstm_rec_ker_fix) + Encoder_lstm_bias_fix#(32,24)
		i_lstm_fix = uf.hard_sig(z_lstm_fix[:, 0:layers])#(32,12)
		f_lstm_fix = uf.hard_sig(z_lstm_fix[:, layers:layers*2])#(32,12)
		input_to_c_lstm_fix = z_lstm_fix[:, layers*2:layers*3]#(32,24)		
#		input_to_c_lstm_fix = (input_to_c_lstm_fix)>>12#(32,12)non fa troncamento ma arrotondamento		
		o_lstm_fix = uf.hard_sig(z_lstm_fix[:, layers*3:layers*4])#(32,12)
		c_lstm_fix = np.multiply(f_lstm_fix, Encoder_c_0_lstm_fix) + np.multiply(i_lstm_fix, uf.tanh(input_to_c_lstm_fix))#(32,24)
		h_lstm_fix = np.multiply(o_lstm_fix, uf.tanh(c_lstm_fix))#(32,24)
		Encoder_c_0_lstm_fix = (c_lstm_fix>>scale_shift)#(32,12)
		Encoder_h_0_lstm_fix = (h_lstm_fix>>scale_shift)#(32,12)
	
	#print("z_o",z_lstm_fix[:, layers*3:layers*4]>>11)
	#print("c", uf.tanh(input_to_c_lstm_fix))
	#print("i", i_lstm_fix)
	#print("f", f_lstm_fix)
	#print("o", o_lstm_fix)
	
	print("Enc H",Encoder_h_0_lstm_fix)
	print("Enc C",Encoder_c_0_lstm_fix)
	#print("Enc Z",z_lstm_fix>>scale_shift)
	
	#Decoder LSTM

	Decoder_c_0_lstm_fix = Encoder_c_0_lstm_fix#(32,12)
	Decoder_h_0_lstm_fix = Encoder_h_0_lstm_fix#(32,12)

	for n_steps in range(steps_out):
	#for n_steps in range(1):
		z_lstmD_fix = np.dot(Decoder_h_0_lstm_fix, Decoder_lstm_rec_ker_fix) + Decoder_lstm_bias_fix#(32,24)
		i_lstmD_fix = uf.hard_sig(z_lstmD_fix[:, 0:layers])#(32,12)
		f_lstmD_fix = uf.hard_sig(z_lstmD_fix[:, layers:layers*2])#(32,12)
		input_to_c_lstmD_fix = (z_lstmD_fix[:, layers*2:layers*3])#(32,24)
#		input_to_c_lstmD_fix = (input_to_c_lstmD_fix)>>12#(32,12)non fa troncamento ma arrotondamento		
		o_lstmD_fix = uf.hard_sig(z_lstmD_fix[:, layers*3:layers*4])#(32,12)
		c_lstmD_fix = np.multiply(f_lstmD_fix, Decoder_c_0_lstm_fix) + np.multiply(i_lstmD_fix, uf.tanh(input_to_c_lstmD_fix))#(32,24)
		h_lstmD_fix = np.multiply(o_lstmD_fix, uf.tanh(c_lstmD_fix))#(32,24)
		Decoder_c_0_lstm_fix = (c_lstmD_fix>>scale_shift)#(32,12)
		Decoder_h_0_lstm_fix = (h_lstmD_fix>>scale_shift)#(32,12)
		##Dense Layer
		Output_dense_fix = np.dot(Decoder_h_0_lstm_fix, dense_kernel_fix)+ dense_bias_fix#(32,24)
		Outputs_fix.append(Output_dense_fix)
	#print("Dec H",Decoder_h_0_lstm_fix)
	#print("Dec C",Decoder_c_0_lstm_fix)		

#print(np.max(z_lstm-z_lstm_fix*unscale2))
#print(np.max(Encoder_h_0_lstm-Encoder_h_0_lstm_fix*unscale))

Outputs_fix = np.trunc(np.array(Outputs_fix)*unscale)
print("Outputs Fixed Point:",Outputs_fix)
