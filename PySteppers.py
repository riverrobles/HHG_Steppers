# -*- coding: utf-8 -*-
"""
Created on Fri Oct 12 01:14:53 2018

@author: River
"""

import serial
import logging 

import numpy as np 

class Stepper_Handler:
    def __init__(self,port='COM3'):
        self.ser = serial.Serial(port,9600,timeout=None)
        self.step_interval = 1000

        self.step_position = [0,0,0] 
        self.step_maximum = [1e5,1e5,1e5]

    def step(self,steps,board):
        logging.info('Stepping')
        
        n_iterations = abs(steps / self.step_interval)
            
        i = 0 
            
        while (i < n_iterations):
            self.ser.write('{0}\n{1}\n'.format(self.step_interval,board))
            message = self.ser.read_until()
                
            i = self.interp_message(message,board,self.step_interval,steps,i)
            
            if (message == 'Normal') and (i > n_iterations):
                self.ser.write('{0}\n{1}\n'.format(steps - n_iterations*self.step_interval*np.sign(steps),board))
                message = self.ser.read_until()
                
                i = self.interp_messsage(message,board,steps - n_iterations*self.step_interval*np.sign(steps),steps,i)
            
    def interp_messsage(self,message,board,interval,steps,i):
        if message == 'Normal':
            i += 1
            self.step_position[board] += interval*np.sign(steps)
        elif message == 'Hit positive switch':
            i = 10e5
            self.step_position[board] = self.step_maximum[board]
        elif message == 'Hit negative switch':
            i = 10e5
            self.step_position[board] = 0 
        
        return i
            
    def close_ser(self):
        self.ser.close() 