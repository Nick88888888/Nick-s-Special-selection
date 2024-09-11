THRESHOLD_black = (0, 20, -128, 127, -128, 127)#first is black
THRESHOLD_yellow = (100, 0, -12, 127, 32, 127)
THRESHOLD_red = (48, 0, 7, 74, 16, 64)
THRESHOLD_blue=(14, 0, -101, 111, -118, 21)
import sensor, image, time, pyb, math, car,sensor1,A
from pyb import LED, UART
from pid import PID
rho_pid = PID(p=0.4, i=0)
theta_pid = PID(p=0.4, i=0)
threshold_index = 0

sensor.reset()
sensor.set_pixformat(sensor.RGB565)#//////////////////////////////A圖ㄋ
sensor.set_framesize(sensor.QQQVGA) # 80x60 (4,800 pixels) - O(N^2) max = 2,3040,000.
#sensor.set_windowing([0,20,80,40])
sensor.skip_frames(time=2000)     # WARNING: If you use QQVGA it may take seconds
clock = time.clock()                # to process a frame sometimes.

L_area = 0
R_area = 0
num = 0
b = 0
a = None  # 初始化 a 為 None
num = 0
y = 0
find_area = 0
disconnected = 0
count=0
uart = UART(3, 19200)
q=1
while(q==1):
    uart.write("w")
    while not uart.any():
        pass
    char = int(uart.readchar())
    print(char)
    if char>0:
        uart.write("a")
        q=0
if char == 16:#AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA
    print("A")
elif char == 8:#BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBB
    print("B")
elif char == 4:
    print("C")
elif char == 2:
    print("D")