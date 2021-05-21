import h5py
import numpy as np
import matplotlib.pyplot as plt
import math
import UtilityPar as uf
from sklearn.metrics import mean_squared_error
from sklearn.metrics import mean_absolute_error
from sklearn.metrics import r2_score
from pickle import load

#carico il modello
model = h5py.File('27_9EDU1GRU_100OneYear.h5', 'r')

layers=100
steps_in=27
steps_out=9
vett_in=2924

#carico lo scaler
scaler = load(open('scaler.pkl', 'rb'))

#Leggo i pesi della rete
dense_bias = np.array((((model['model_weights'])['dense_5'])['dense_5'])['bias:0'])
dense_kernel = np.array((((model['model_weights'])['dense_5'])['dense_5'])['kernel:0'])

Encoder_gru_bias = np.array((((model['model_weights'])['rnn_9'])['rnn_9'])['bias:0'])
Encoder_gru_kernel = np.array((((model['model_weights'])['rnn_9'])['rnn_9'])['kernel:0'])
Encoder_gru_rec_ker = np.array((((model['model_weights'])['rnn_9'])['rnn_9'])['recurrent_kernel:0'])

Decoder_gru_bias = np.array((((model['model_weights'])['rnn_10'])['rnn_10'])['bias:0'])
Decoder_gru_kernel = np.array((((model['model_weights'])['rnn_10'])['rnn_10'])['kernel:0'])
Decoder_gru_rec_ker = np.array((((model['model_weights'])['rnn_10'])['rnn_10'])['recurrent_kernel:0'])

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
input_seq_test = np.load('input_test_complete.npy')
output_seq_test = np.load('output_test_complete.npy')
print(output_seq_test.shape)

x = input_seq_test[0:vett_in,:]
#print(x)
y = output_seq_test[0:vett_in,:]

######################################  FLOATING POINT  ######################################
Outputs_array= np.zeros(shape=(vett_in,steps_out))

#for n_input in range(x.shape[0]):
for n_input in range(vett_in):
	Outputs = []
	#Encoder LSTM
	Encoder_h_0_gru = np.zeros((1, layers))
	for n_steps in range(steps_in):
#	for n_steps in range(1):
		Encoder_z_r_gru = x[n_input,n_steps]*Encoder_gru_kernel[:,:layers*2] + np.dot(Encoder_h_0_gru, Encoder_gru_rec_ker[:,:layers*2]) + Encoder_gru_bias[:layers*2]
		Encoder_z_gru = hard_sigmoid(Encoder_z_r_gru[:, :layers])
		Encoder_r_gru = hard_sigmoid(Encoder_z_r_gru[:,layers:layers*2])

		prod = Encoder_r_gru*Encoder_h_0_gru
		Encoder_h0_tilde_gru = x[n_input,n_steps]*Encoder_gru_kernel[:,layers*2:] + np.dot(prod,Encoder_gru_rec_ker[:,layers*2:]) + Encoder_gru_bias[layers*2:]

		Encoder_h_tilde_gru = np.tanh(Encoder_h0_tilde_gru)

		Encoder_h_gru = (1-Encoder_z_gru)*Encoder_h_tilde_gru + Encoder_z_gru*Encoder_h_0_gru

		Encoder_h_0_gru = Encoder_h_gru

#print(Encoder_h_0_gru)
	#Decoder GRU

	Decoder_h_0_gru = Encoder_h_0_gru


	for n_steps in range(steps_out):
#	for n_steps in range(1):

		Decoder_z_r_gru = np.dot(Decoder_h_0_gru, Decoder_gru_rec_ker[:,:layers*2]) + Decoder_gru_bias[:layers*2]
		Decoder_z_gru = hard_sigmoid(Decoder_z_r_gru[:, :layers])
		Decoder_r_gru = hard_sigmoid(Decoder_z_r_gru[:,layers:layers*2])
		prod = Decoder_r_gru*Decoder_h_0_gru
		Decoder_h0_tilde_gru = np.dot(prod,Decoder_gru_rec_ker[:,layers*2:]) + Decoder_gru_bias[layers*2:]
		Decoder_h_tilde_gru = np.tanh(Decoder_h0_tilde_gru)

		Decoder_h_gru = (1-Decoder_z_gru)*Decoder_h_tilde_gru + Decoder_z_gru*Decoder_h_0_gru

		Decoder_h_0_gru = Decoder_h_gru
		##Dense Layer
		Output_dense = np.dot(Decoder_h_0_gru, dense_kernel)+ dense_bias
		Outputs.append(Output_dense)

	Outputs_array[n_input] = np.squeeze(np.array(Outputs))


######################################  FIXED POINT(16,12)  ######################################

##Scaling Factors
scale_shift=12  #ricorda di cambiarlo anche all'interno delle Utility function
scale=pow(2,scale_shift)
unscale=pow(2, -scale_shift)
scale2=pow(2,scale_shift*2)
unscale2=pow(2,-scale_shift*2)

##Coefficients Scaling
Encoder_gru_bias_fix = np.int32(np.trunc(scale2*Encoder_gru_bias)) #(32,24)
Encoder_gru_kernel_fix = np.int32(np.trunc(scale*Encoder_gru_kernel))#(32,12)
Encoder_gru_rec_ker_fix = np.int32(np.trunc(scale*Encoder_gru_rec_ker))#(32,12)

Decoder_gru_bias_fix = np.int32(np.trunc(scale2*Decoder_gru_bias))#(32,24)
Decoder_gru_kernel_fix = np.int32(np.trunc(scale*Decoder_gru_kernel))#(32,12)
Decoder_gru_rec_ker_fix = np.int32(np.trunc(scale*Decoder_gru_rec_ker))#(32,12)

dense_bias_fix = np.int32(np.trunc(scale2*dense_bias))#(32,24)
dense_kernel_fix = np.int32(np.trunc(scale*dense_kernel))#(32,12)

##Input Scaling

Input_seq_test_fix = np.int32(np.trunc(input_seq_test*scale))#(32,12)
x_fix = Input_seq_test_fix[0:vett_in,:]
#print("input",x_fix.shape)
One_scaled =np.int32(1<<scale_shift)

Outputs_fix_array=np.zeros(shape=(vett_in,steps_out))

#for n_input in range(x.shape[0]):
for n_input in range(vett_in):

	#Encoder LSTM
	Outputs_fix = []
	Encoder_h_0_gru_fix = np.int32(np.zeros((1, layers)))

	for n_steps in range(steps_in):
#	for n_steps in range(2):

		z_r_gru_fix = x_fix[n_input, n_steps]*Encoder_gru_kernel_fix[:,:layers*2] + np.dot(Encoder_h_0_gru_fix, Encoder_gru_rec_ker_fix[:,:layers*2]) + Encoder_gru_bias_fix[:layers*2]#(32,24)
		#print("z_r_gru_fix",z_r_gru_fix)
		z_gru_fix = uf.hard_sig(z_r_gru_fix[:,:layers])#(32,12)
		r_gru_fix = uf.hard_sig(z_r_gru_fix[:, layers:layers*2])#(32,12)
		#print("z_gru_fix",z_gru_fix)
		#print("r_gru_fix",r_gru_fix)
		prod_fix = (r_gru_fix*Encoder_h_0_gru_fix)>>scale_shift#(32,12)
		#print("prod_fix",prod_fix)

		h0_tilde_gru_fix = x_fix[n_input, n_steps]*Encoder_gru_kernel_fix[:,layers*2:] + np.dot(prod_fix,Encoder_gru_rec_ker_fix[:,layers*2:]) + Encoder_gru_bias_fix[layers*2:]#(32,24)
		#print("h0_tilde_gru_fix",h0_tilde_gru_fix>>scale_shift)
		h_tilde_gru_fix = uf.tanh(h0_tilde_gru_fix)#(32,12)

		h_gru_fix = (One_scaled-z_gru_fix)*h_tilde_gru_fix + z_gru_fix*Encoder_h_0_gru_fix
		#print("h_e_gru_fix",h_gru_fix)

		Encoder_h_0_gru_fix = (h_gru_fix>>scale_shift)#(32,12)
		#print("Encoder_h_0_gru_fix",Encoder_h_0_gru_fix)

	#print("Enc H_fix",Encoder_h_0_gru_fix)

	#Decoder LSTM

	Decoder_h_0_gru_fix = Encoder_h_0_gru_fix#(32,12)

	for n_steps in range(steps_out):
#	for n_steps in range(2):
		z_r_gruD_fix = np.dot(Decoder_h_0_gru_fix, Decoder_gru_rec_ker_fix[:,:layers*2]) + Decoder_gru_bias_fix[:layers*2]#(32,24)
		z_gruD_fix = uf.hard_sig(z_r_gruD_fix[:,:layers])#(32,12)
		r_gruD_fix = uf.hard_sig(z_r_gruD_fix[:, layers:layers*2])#(32,12)
		prodD_fix = (r_gruD_fix*Decoder_h_0_gru_fix)>>scale_shift#(32,12)
		#print("z_r_gru",z_r_gru_fix)
		#print("z_gru",z_gruD_fix)
		#print("r_gru",r_gruD_fix)
		#print("prod_fix",prodD_fix)

		h0_tilde_gruD_fix = np.dot(prodD_fix,Decoder_gru_rec_ker_fix[:,layers*2:]) + Decoder_gru_bias_fix[layers*2:]#(32,24)
		h_tilde_gruD_fix = uf.tanh(h0_tilde_gruD_fix)

		h_gruD_fix = (One_scaled-z_gruD_fix)*h_tilde_gruD_fix + z_gruD_fix*Decoder_h_0_gru_fix

		Decoder_h_0_gru_fix = (h_gruD_fix>>scale_shift)#(32,12)

		##Dense Layer
		Output_dense_fix = np.dot(Decoder_h_0_gru_fix, dense_kernel_fix)+ dense_bias_fix#(32,24)
		Outputs_fix.append(Output_dense_fix)

		#print("Dec H",Decoder_h_0_gru_fix)
	Outputs_fix_array[n_input] = np.squeeze(np.array(Outputs_fix))


Outputs_fix_array = Outputs_fix_array*unscale2


pred_values = scaler.inverse_transform(Outputs_array.reshape(-1,1))

pred_values_fix = scaler.inverse_transform(Outputs_fix_array.reshape(-1,1))

Output_seq_test = scaler.inverse_transform(y.reshape(-1,1))

print('Train Mean Absolute Error:', mean_absolute_error(Output_seq_test, pred_values))
print('Train Root Mean Squared Error:',np.sqrt(mean_squared_error(Output_seq_test, pred_values)))
print('Train R2 score:',r2_score(Output_seq_test, pred_values))

print('\nTest Mean Absolute Error:', mean_absolute_error(Output_seq_test, pred_values_fix))
print('Test Root Mean Squared Error:',np.sqrt(mean_squared_error(Output_seq_test, pred_values_fix)))
print('Test R2 score:',r2_score(Output_seq_test,pred_values_fix))
