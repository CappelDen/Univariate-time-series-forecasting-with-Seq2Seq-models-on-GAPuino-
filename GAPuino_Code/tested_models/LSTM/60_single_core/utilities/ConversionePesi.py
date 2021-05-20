import h5py
import numpy as np
import matplotlib.pyplot as plt  
import math 


model = h5py.File('27_9EDU1LSTM_60OneYear.h5', 'r')
input_seq_test = np.load('Input_seq_test.npy')
output_seq_test = np.load('Output_seq_test.npy')

dense_bias = np.array((((model['model_weights'])['dense_12'])['dense_12'])['bias:0'])
dense_kernel = np.array((((model['model_weights'])['dense_12'])['dense_12'])['kernel:0'])

Encoder_lstm_bias = np.array((((model['model_weights'])['rnn_23'])['rnn_23'])['bias:0'])
Encoder_lstm_kernel = np.array((((model['model_weights'])['rnn_23'])['rnn_23'])['kernel:0'])
Encoder_lstm_rec_ker = np.array((((model['model_weights'])['rnn_23'])['rnn_23'])['recurrent_kernel:0'])

Decoder_lstm_bias = np.array((((model['model_weights'])['rnn_24'])['rnn_24'])['bias:0'])
Decoder_lstm_kernel = np.array((((model['model_weights'])['rnn_24'])['rnn_24'])['kernel:0'])
Decoder_lstm_rec_ker = np.array((((model['model_weights'])['rnn_24'])['rnn_24'])['recurrent_kernel:0'])

print("min e max Encoder lstm bias ", np.amin(Encoder_lstm_bias),":",np.amax(Encoder_lstm_bias))
print("min e max Encoder lstm kernel ", np.amin(Encoder_lstm_kernel),":",np.amax(Encoder_lstm_kernel))
print("min e max Encoder lstm recurrent ", np.amin(Encoder_lstm_rec_ker),":",np.amax(Encoder_lstm_rec_ker))

print("\nmin e max Decoder lstm bias ", np.amin(Decoder_lstm_bias),":",np.amax(Decoder_lstm_bias))
print("min e max Decoder lstm kernel ", np.amin(Decoder_lstm_kernel),":",np.amax(Decoder_lstm_kernel))
print("min e max Decoder lstm recurrent ", np.amin(Decoder_lstm_rec_ker),":",np.amax(Decoder_lstm_rec_ker))

print("\nmin e max Dense bias ", np.amin(dense_bias),":",np.amax(dense_bias))
print("min e max Dense kernel ", np.amin(dense_kernel),":",np.amax(dense_kernel))


scale=pow(2,11)
scale2=pow(2,22)


Enc_bias=np.int32(np.trunc(scale2*Encoder_lstm_bias))
Enc_kernel=np.int16(np.trunc(scale*Encoder_lstm_kernel))	
Enc_rec_ker=np.int16(np.trunc(scale*Encoder_lstm_rec_ker))

Dec_bias=np.int32(np.trunc(scale2*Decoder_lstm_bias))
Dec_kernel=np.int16(np.trunc(scale*Decoder_lstm_kernel))	
Dec_rec_ker=np.int16(np.trunc(scale*Decoder_lstm_rec_ker))

Dense_bias=np.int32(np.trunc(scale2*dense_bias))
Dense_kernel=np.int16(np.trunc(scale*dense_kernel))

Input_seq_test_fix = np.int32(np.trunc(input_seq_test*scale))#(32,12)
x_fix = np.reshape(Input_seq_test_fix[0:2,:],(-1,27))

np.savetxt('coeff/Encoder_lstm_bias.txt', Enc_bias, delimiter=',',newline=',', fmt='%d')
np.savetxt('coeff/Encoder_lstm_kernel.txt', Enc_kernel, delimiter=',',newline=',',  fmt='%d')
np.savetxt('coeff/Encoder_lstm_rec_ker.txt', Enc_rec_ker, delimiter=',',newline=',\n',  fmt='%d')

np.savetxt('coeff/Decoder_lstm_bias.txt', Dec_bias, delimiter=',',newline=',',  fmt='%d')
np.savetxt('coeff/Decoder_lstm_kernel.txt', Dec_kernel, delimiter=',',newline=',',  fmt='%d')
np.savetxt('coeff/Decoder_lstm_rec_ker.txt', Dec_rec_ker, delimiter=',',newline=',\n',  fmt='%d')


np.savetxt('coeff/Dense_bias.txt', Dense_bias, delimiter=',',newline=',',  fmt='%d')
np.savetxt('coeff/Dense_kernel.txt', Dense_kernel, delimiter=',',newline=',',  fmt='%d')


np.savetxt('coeff/Ingressi.txt', x_fix, delimiter=',',newline=',',  fmt='%d')

