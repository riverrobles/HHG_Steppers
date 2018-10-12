# -*- coding: utf-8 -*-
"""
Created on Fri Oct 12 09:34:06 2018

@author: river
"""

import logging
import tkinter as tk 

from PySteppers import Stepper_Handler 

class App:
    def __init__(self,controller):
        self.controller = Stepper_Handler() 
        
if __name__ == "__main__":
    app = App()
    