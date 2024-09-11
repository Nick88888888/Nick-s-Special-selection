import sensor, image, time, math,array
from pyb import UART
from pyb import LED
uart = UART(3, 19200)
threshold_index = 0
thresholds = [(100, 88, 56, -71, 70, -48),(4, 45, 56, -71, 70, -48)]

LED(1).on()
LED(2).on()
LED(3).on()
sensor.reset()
sensor.set_vflip(True)
sensor.set_hmirror(True)
sensor.set_pixformat(sensor.RGB565)
sensor.set_framesize(sensor.QVGA)
sensor.skip_frames(time = 2000)
sensor.set_auto_gain(False)
sensor.set_auto_whitebal(False)
clock = time.clock()
ROIS = [
    (100, 60, 120, 240),
    (0, 60, 160, 240),
    (160, 60, 160, 240)
]
r=0
middle_line = 0
middle_y = 0
LX=0
RX=0
LY=0
RY=0
p=0
p2=0
p3=0
middle_area = 0
R_area=0
L_area=0
sumLR=0
c=0
L=[0,0,0,0,0,0,0,0,0,0]
R=[0,0,0,0,0,0,0,0,0,0]
powerL = 0
powerR = 0
t=0
MAXY_R=0
MAXY_L=0
MAXY_M=0
m_area=0
while(True):
    k=0
    
    speed=38
    way=100
    LX=-1
    RX=-1
    LY=-1
    RY=-1
    R_area=-1
    L_area=-1
    L=0
    R=0
    sumLR=0
    powerL = 0
    powerR = 0
    clock.tick()
    img = sensor.snapshot()
    MAXY_L=0
    MAXX_L=0
    MAXY_M=0
    m_area=0
    white = img.get_statistics ( roi = ROIS[0])
    print("white",white[0])    
    if(white[0]>40):    
        k=1
#    for blob in img.find_blobs([thresholds[0]], pixels_threshold=150,
#        area_threshold=250, merge=True,roi = ROIS[0]):
#        if MAXY_M < blob.cy():
#            MAXY_M = blob.cy()
#            m_area = blob.pixels()
#            img.draw_rectangle(blob.rect(),color =(0,55,0))
   
    
    for blob in img.find_blobs([thresholds[k]], pixels_threshold=150,
        area_threshold=250, merge=True,roi = ROIS[1]):
        if MAXY_L < blob.cy():
            MAXY_L = blob.cy()
            MAXX_L = blob.cx()
            LX = blob.cx()
            LY = blob.cy()
            L_area = blob.area()
    if(MAXY_L!=0):
        img.draw_rectangle(blob.rect(),color =(255,55,0))
        img.draw_cross(MAXX_L , MAXY_L)
        img.draw_keypoints([(MAXX_L , MAXY_L, int(math.degrees(blob.rotation())))], size=20)
        img.draw_keypoints([(MAXX_L , MAXY_L, int(math.degrees(blob.rotation())))], size=20)        
   
   
    
    MAXY_R = 0
    MAXX_R = 320
    for blob in img.find_blobs([thresholds[k]], pixels_threshold=150,
        area_threshold=250, merge=True,roi = ROIS[2]):
        if MAXY_R < blob.cy():
            MAXY_R = blob.cy()
            MAXX_R = blob.cx()
            RX = blob.cx()
            RY = blob.cy()
            R_area = blob.area()
            
    if(MAXY_R != 0):
        img.draw_rectangle(blob.rect(),color =(0,55,255))
        img.draw_cross(MAXX_R , MAXY_R)
        img.draw_keypoints([(MAXX_R , MAXY_R, int(math.degrees(blob.rotation())))], size=20)
        img.draw_keypoints([(MAXX_R , MAXY_R, int(math.degrees(blob.rotation())))], size=20)
        
    way = way - int((R_area - L_area) / 1200)
    print("way=",way,"k=",k)
    uart.write(str('+') + str(speed) + "," + str(int(way)) + "E\n")
    time.sleep_ms(30)
