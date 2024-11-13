#!/usr/bin/env python3

yellow = 0XFFE0
cyan = 0x7FFF
red = 0xF800
green = 0x07E0
brown = 0XBC40
pink = 0xF81F
purple = 0x780F
black = 0x0000

class GenTetrisPiece:
    def _init_(self, name, shape):
        self.name = name
        self.shape = shape
        self.block_size = 20
        self.width = self.block_size * 4
        self.height = self.block_size * 4
    
    '''
        go through grid in shape in Shapes
            if 1, assign color, if 0, assign black for each shape
        
    '''
    def piece_to_pixel_data(self):
        pixel_data = [[0 for x in range(0,height)] for y in range(0, width)] #change potentially
        for y in range(4):
            for curr_block in range(self.block_size):
                row = []
                for x in range(len(self.shape)):
                    color = black in self.shape[x][y]



class Shapes:
    def _init_(self):
        self.o = [
            [1,1,0,0],
            [1,1,0,0],
            [0,0,0,0],
            [0,0,0,0]
        ]
        self.i = [
            [1,0,0,0],
            [1,0,0,0],
            [1,0,0,0],
            [1,0,0,0]
        ]
        self.s = [
            [0,1,1,0],
            [1,1,0,0],
            [0,0,0,0],
            [0,0,0,0]
        ]
        self.z = [
            [1,1,0,0],
            [0,1,1,0],
            [0,0,0,0],
            [0,0,0,0]
        ]
        self.l = [
            [1,0,0,0],
            [1,0,0,0],
            [1,1,0,0],
            [0,0,0,0]
        ]
        self.j = [
            [0,1,0,0],
            [0,1,0,0],
            [1,1,0,0],
            [0,0,0,0]
        ]
        self.t = [
            [1,1,1,0],
            [0,1,0,0],
            [0,0,0,0],
            [0,0,0,0]
        ]

    