import sensor, image, time, math,array
from pyb import UART
from pyb import LED
uart = UART(3, 19200)
threshold_index = 0
thresholds = [(100, 92, 66, -37, 86, -48),(4, 20, 71, -96, 92, -48)]#第一個抓白線，二是黑

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
    (0, 60, 320, 240),
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
k=0

white_limit=50





   
 
def run(n):     
    speed=50
    way=100 
    P_degrees=60#角度要除的數字       
    P_area=1400
    L_area=-1
    L_degrees=0.0000000001
    MAXY_L=0
    MAXX_L=0            
    for blob in img.find_blobs([thresholds[n]], pixels_threshold=150,#左邊
        area_threshold=250, merge=True,roi = ROIS[1]):
        if MAXY_L < blob.cy():
            MAXY_L = blob.cy()
            MAXX_L = blob.cx()
            LX = blob.cx()
            LY = blob.cy()
            L_area = blob.area()/P_area
            L_degrees = (math.degrees(blob.rotation()))/P_degrees
            print("blob_degrees=",math.degrees(blob.rotation())-90)
    if(MAXY_L!=0):
        img.draw_rectangle(blob.rect(),color =(255,55,0))
        img.draw_cross(MAXX_L , MAXY_L)
        img.draw_keypoints([(MAXX_L , MAXY_L, int(math.degrees(blob.rotation())))], size=20)
        img.draw_keypoints([(MAXX_L , MAXY_L, int(math.degrees(blob.rotation())))], size=20) 
        
    MAXY_R = 0
    MAXX_R = 320
    R_degrees=0.0000000001 
    R_area=-1
    for blob in img.find_blobs([thresholds[n]], pixels_threshold=150,
        area_threshold=250, merge=True,roi = ROIS[2]):
        if MAXY_R < blob.cy():
            MAXY_R = blob.cy()
            MAXX_R = blob.cx()
            RX = blob.cx()
            RY = blob.cy()
            R_area = blob.area()/P_area
            R_degrees = (math.degrees(blob.rotation()))/P_degrees
    if(MAXY_R != 0):
        img.draw_rectangle(blob.rect(),color =(0,55,255))
        img.draw_cross(MAXX_R , MAXY_R)
        img.draw_keypoints([(MAXX_R , MAXY_R, int(math.degrees(blob.rotation())))], size=20)
        img.draw_keypoints([(MAXX_R , MAXY_R, int(math.degrees(blob.rotation())))], size=20)
        
    way = way - int(R_area+R_degrees - L_area-L_degrees)
    print("way=",way,"k=",k,"R_area=",R_area,"R_degrees=",R_degrees,"L_area=",L_area,"L_degrees=",L_degrees)
    uart.write(str('+') + str(int(speed-abs(way*0.07))) + "," + str(int(way)) + "E\n")
    time.sleep_ms(30)       
    
    
    
#===============================================================================================    
while(True):
    
    sensor.reset()#抓白線
    sensor.set_vflip(True)
    sensor.set_hmirror(True)
    sensor.set_pixformat(sensor.RGB565)
    sensor.set_framesize(sensor.QVGA)
    sensor.skip_frames(time = 100)    
    clock = time.clock()
   
    while(k%2==0):         
        clock.tick()
        img = sensor.snapshot()
        img.draw_rectangle(ROIS[0],color=(0,100,200))  
        white = img.get_statistics ( roi = ROIS[0])  
        print("white",white)    
        if(white[0]>white_limit):    
            k=k+1 
        run(k%2)  
    uart.write(str('+') + str(0) + "," + str(95)+ "E\n")
    time.sleep_ms(30)     
  
    sensor.reset()#抓白線
    sensor.set_vflip(True)
    sensor.set_hmirror(True)
    sensor.set_pixformat(sensor.RGB565)
    sensor.set_framesize(sensor.QVGA)
    sensor.skip_frames(time = 200)    
    clock = time.clock()    
    while(k%2==1):         
        clock.tick()
        img = sensor.snapshot()
        img.draw_rectangle(ROIS[0],color=(0,100,200))
        white = img.get_statistics ( roi = ROIS[0])  
        print("white",white)    
        if(white[0]<white_limit):    
            k=k+1         
        run(k%2)    
    uart.write(str('+') + str(0) + "," + str(100 )+ "E\n")
    time.sleep_ms(30)       
        
        
