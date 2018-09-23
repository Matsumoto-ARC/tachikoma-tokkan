#!/usr/bin/python3
import struct, serial, time, os

def creat_format():
  global ds3_type 
  global ds3_num 
  global ds3_val
  if ds3_type == 1:
    if ds3_num < 10:
      ds3_num = '0' + str(ds3_num)
  elif ds3_type == 2:
    if ds3_num < 10:
      ds3_num = '0' + str(ds3_num)

    if ds3_val < -9999:
      ds3_val = str(ds3_val)
    elif ds3_val < -999:   # -9999 =< ds3_val < -999
      ds3_val = '-' + str(ds3_val)
    elif ds3_val < -99:   # -999 =< ds3_val < -99
      ds3_val = '--' + str(ds3_val)
    elif ds3_val < -9:    # -99 =< ds3_val < -9
      ds3_val = '---' + str(ds3_val)
    elif ds3_val < 0:     # -9 =< ds3_val < 0
      ds3_val = '----' + str(ds3_val)
    elif ds3_val < 10:    # 0 =< ds3_val < 10
      ds3_val = '00000' + str(ds3_val)     
    elif ds3_val < 100:   # 10 =< ds3_val < 100
      ds3_val = '0000' + str(ds3_val)      
    elif ds3_val < 1000:  # 100 =< ds3_val < 1000
      ds3_val = '000' + str(ds3_val)      
    elif ds3_val < 10000: # 1000 =< ds3_val < 10000
      ds3_val = '00' + str(ds3_val)
    elif ds3_val < 100000:  # 10000 =< ds3_val < 100000
      ds3_val = '0' + str(ds3_val)

""" device_path = os.path.relpath("/dev/input/js0")
connect_wait = True
while connect_wait:
  if os.path.isfile(device_path):
    connect_wait = False
  else:
    time.sleep(1) """

device_path = "/dev/input/js0"
port = "/dev/ttyS0"
serialArduino = serial.Serial(port, 9600)
serialArduino.flushInput()

# unsigned long, short, unsigned char, unsigned char
EVENT_FORMAT = "LhBB";
EVENT_SIZE = struct.calcsize(EVENT_FORMAT)

""" read_data = 0
while read_data == 0:
  read_data = int.from_bytes(serialArduino.read(1), 'big')
  if (read_data == 1):
    serialArduino.write(bytes(read_data)) """

with open(device_path, "rb") as device:
  event = device.read(EVENT_SIZE)
  while event:
    (ds3_time, ds3_val, ds3_type, ds3_num) = struct.unpack(EVENT_FORMAT, event)
    #print( "{0}, {1}, {2}, {3}".format( ds3_time, ds3_val, ds3_type, ds3_num ) )

    if (ds3_type == 1 or (ds3_type == 2 and ds3_num < 4)):
      creat_format()

      serial_send_data = str(ds3_type) + str(ds3_num) + str(ds3_val) + '\n'
      serialArduino.write(bytes(serial_send_data.encode('utf-8')))
      print( "{0}, {1}, {2}".format( ds3_type, ds3_num, ds3_val ) )
      
    event = device.read(EVENT_SIZE)