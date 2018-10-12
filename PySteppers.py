# -*- coding: utf-8 -*-
"""
Created on Fri Oct 12 01:14:53 2018

@author: River
"""

import serial

class Stepper_Handler:
    def __init__(self,port='COM3'):
        self.ser = serial.Serial(port,9600,timeout=10)