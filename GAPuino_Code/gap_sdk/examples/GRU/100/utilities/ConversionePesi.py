import h5py
import numpy as np
import matplotlib.pyplot as plt  
import math 


model = h5py.File('27_9EDU1GRU_100OneYear.h5', 'r')
neuroni = 100
#print(list(model.keys())[0])

input_seq_test = np.load('Input_seq_test.npy')
output_seq_test = np.load('Output_seq_test.npy')

dense_bias = np.array((((model['model_weights'])['dense_5'])['dense_5'])['bias:0'])
dense_kernel = np.array((((model['model_weights'])['dense_5'])['dense_5'])['kernel:0'])

Encoder_lstm_bias = np.array((((model['model_weights'])['rnn_9'])['rnn_9'])['bias:0'])
Encoder_lstm_kernel = np.array((((model['model_weights'])['rnn_9'])['rnn_9'])['kernel:0'])
Encoder_lstm_rec_ker = np.array((((model['model_weights'])['rnn_9'])['rnn_9'])['recurrent_kernel:0'])

Decoder_lstm_bias = np.array((((model['model_weights'])['rnn_10'])['rnn_10'])['bias:0'])
Decoder_lstm_kernel = np.array((((model['model_weights'])['rnn_10'])['rnn_10'])['kernel:0'])
Decoder_lstm_rec_ker = np.array((((model['model_weights'])['rnn_10'])['rnn_10'])['recurrent_kernel:0'])

print("min e max Encoder lstm bias ", np.amin(Encoder_lstm_bias),":",np.amax(Encoder_lstm_bias))
print("min e max Encoder lstm kernel ", np.amin(Encoder_lstm_kernel),":",np.amax(Encoder_lstm_kernel))
print("min e max Encoder lstm recurrent ", np.amin(Encoder_lstm_rec_ker),":",np.amax(Encoder_lstm_rec_ker))

print("\nmin e max Decoder lstm bias ", np.amin(Decoder_lstm_bias),":",np.amax(Decoder_lstm_bias))
print("min e max Decoder lstm kernel ", np.amin(Decoder_lstm_kernel),":",np.amax(Decoder_lstm_kernel))
print("min e max Decoder lstm recurrent ", np.amin(Decoder_lstm_rec_ker),":",np.amax(Decoder_lstm_rec_ker))

print("\nmin e max Dense bias ", np.amin(dense_bias),":",np.amax(dense_bias))
print("min e max Dense kernel ", np.amin(dense_kernel),":",np.amax(dense_kernel))


scale=pow(2,12)
scale2=pow(2,24)


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

'''
hex_file = bytes(Enc_rec_ker)
fo = open("Enc_rec_ker.dat","wb")
fo.write(hex_file)
fo.close() 

hex_file2 = bytes(Dec_rec_ker)
fo2 = open("Dec_rec_ker.dat","wb")
fo2.write(hex_file2)
fo2.close()
'''
np.savetxt('coeffGRU/Ingressi.txt', x_fix, delimiter=',',newline=',',  fmt='%d')

np.savetxt('coeffGRU/Encoder_GRU_bias1.txt', Enc_bias[:2*neuroni], delimiter=',',newline=',', fmt='%d')
np.savetxt('coeffGRU/Encoder_GRU_kernel1.txt', Enc_kernel[:,:2*neuroni], delimiter=',',newline=',',  fmt='%d')
np.savetxt('coeffGRU/Encoder_GRU_rec_ker1.txt', Enc_rec_ker[:,:2*neuroni], delimiter=',',newline=',\n',  fmt='%d')

np.savetxt('coeffGRU/Encoder_GRU_bias2.txt', Enc_bias[2*neuroni:], delimiter=',',newline=',', fmt='%d')
np.savetxt('coeffGRU/Encoder_GRU_kernel2.txt', Enc_kernel[:,2*neuroni:], delimiter=',',newline=',',  fmt='%d')
np.savetxt('coeffGRU/Encoder_GRU_rec_ker2.txt', Enc_rec_ker[:,2*neuroni:], delimiter=',',newline=',\n',  fmt='%d')

np.savetxt('coeffGRU/Decoder_GRU_bias1.txt', Dec_bias[:2*neuroni], delimiter=',',newline=',', fmt='%d')
np.savetxt('coeffGRU/Decoder_GRU_kernel1.txt', Dec_kernel[:,:2*neuroni], delimiter=',',newline=',',  fmt='%d')
np.savetxt('coeffGRU/Decoder_GRU_rec_ker1.txt', Dec_rec_ker[:,:2*neuroni], delimiter=',',newline=',\n',  fmt='%d')

np.savetxt('coeffGRU/Decoder_GRU_bias2.txt', Dec_bias[2*neuroni:], delimiter=',',newline=',', fmt='%d')
np.savetxt('coeffGRU/Decoder_GRU_kernel2.txt', Dec_kernel[:,2*neuroni:], delimiter=',',newline=',',  fmt='%d')
np.savetxt('coeffGRU/Decoder_GRU_rec_ker2.txt', Dec_rec_ker[:,2*neuroni:], delimiter=',',newline=',\n',  fmt='%d')

np.savetxt('coeffGRU/Dense_bias.txt', Dense_bias, delimiter=',',newline=',',  fmt='%d')
np.savetxt('coeffGRU/Dense_kernel.txt', Dense_kernel, delimiter=',',newline=',',  fmt='%d')

