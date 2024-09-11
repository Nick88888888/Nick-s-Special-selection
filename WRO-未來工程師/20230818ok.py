# Single Color RGB565 Blob Tracking Example
#
# This example shows off single color RGB565 tracking using the OpenMV Cam.

import sensor, image, time, math
from pyb import UART
from pyb import LED
uart = UART(3, 19200)
threshold_index = 0 # 0 for red, 1 for green, 2 for blue


thresholds_black = [(0, 33, 1, -10, -35, 18)]
thresholds_green = [(25, 8, -56, -10, -35, 18)] #綠色的值
thresholds_orange = [(55, 26, 17, 114, -23, 121)]#橘色的值
thresholds_red = [(86, 46, 92, 8, -54, 80)]#紅色的值
LED(1).on()
LED(1).on()
LED(2).on()
LED(3).on()
sensor.reset()
sensor.set_vflip(True)
sensor.set_hmirror(True)
sensor.set_pixformat(sensor.RGB565)
sensor.set_framesize(sensor.QVGA)#320x240 
sensor.skip_frames(time = 2000)
sensor.set_auto_gain(False) # must be turned off for color tracking
sensor.set_auto_whitebal(False) # must be turned off for color tracking
clock = time.clock()
black_arrary_m= [0] * 3
count=0#移動平均要用的
b=0
x=0
turn =0
while(True):
    y=0
    right_distance=0
    left_distance=0
    a=0#if see orange line a==1
   
    angle=0
    left_area=0
    black_m_average=0#移動平均值
    sum1=0
    right_area=0
    x_left_black_value=0
    y_left_black_value=0
    x_right_black_value=0
    y_right_black_value=0
    g=0
    black_wall_m=0#黑色牆壁的斜率
    clock.tick()
    img = sensor.snapshot()
    for blob in img.find_blobs([thresholds_green[0]], pixels_threshold=200, area_threshold=200, merge=True):#找綠色線 
        if blob.elongation() > 0.5:
            img.draw_edges(blob.min_corners(), color=(255,0,0))
            img.draw_line(blob.major_axis_line(), color=(0,255,0))
            img.draw_line(blob.minor_axis_line(), color=(0,0,255))
   
        img.draw_rectangle(blob.rect())
        img.draw_cross(blob.cx(), blob.cy()) 
        img.draw_keypoints([(blob.cx(), blob.cy(), int(math.degrees(blob.rotation())))], size=20)
        if(blob.cx()-120<0):
            g=blob.cx()-120
        
    if(turn==0):
        
        for blob in img.find_blobs([thresholds_orange[0]], pixels_threshold=200, area_threshold=200, merge=True):#找橘色線 
            if blob.elongation() > 0.5:
                img.draw_edges(blob.min_corners(), color=(255,0,0))
                img.draw_line(blob.major_axis_line(), color=(0,255,0))
                img.draw_line(blob.minor_axis_line(), color=(0,0,255))
       
            img.draw_rectangle(blob.rect())
            img.draw_cross(blob.cx(), blob.cy()) 
            img.draw_keypoints([(blob.cx(), blob.cy(), int(math.degrees(blob.rotation())))], size=20)
            distance=int(210000/blob.area())
            angle = blob.rotation_deg()
            if blob.area()>300:
                if(angle>90):
                    angle = angle-180
                else:
                    angle-4
                print("angle=",angle-4)
                if(blob.cy()>200):
                    a=1
                    b=1
        if(angle>5):
            turn=1
        elif(angle<-5):
            turn=2
    threemax_x = 0
    threemax_y = 0
    for blob in img.find_blobs([thresholds_black[0]], pixels_threshold=400, area_threshold=400,roi=(50,0,80,240),merge=True):#找左黑色牆壁底下的線
        
        if(blob.corners()[2][1]>=200):
            y=1
        left_distance = int(74052/blob.area())
        if blob.cy() > threemax_y:
            threemax_x = blob.cx()
            threemax_y = blob.cy()
    img.draw_rectangle(blob.rect())
    img.draw_cross(threemax_x, threemax_y)
    x_left_black_value  = threemax_x
    y_left_black_value = threemax_y    
        #print( x_left_black_value ,y_left_black_value)
        
    fourmax_x = 0
    fourmax_y = 0    
    for blob in img.find_blobs([thresholds_black[0]], pixels_threshold=300, area_threshold=300,roi=(190,0,80,240),merge=True):#找右黑色牆壁底下的線
       
        if(blob.corners()[2][1]>=220):
            y=1
        right_distance = int(74052/blob.area())
        print("right_distance=", right_distance)
        if blob.cy() > fourmax_y:
            fourmax_x = blob.cx()
            fourmax_y = blob.cy()
    img.draw_rectangle(blob.rect())
    img.draw_cross(blob.cx(), blob.cy())
    x_right_black_value  = fourmax_x
    y_right_black_value = fourmax_y          
            
        
    if(x_left_black_value!=0 and  x_right_black_value!=0 ):   
        img.draw_line((x_left_black_value,y_left_black_value,x_right_black_value,y_right_black_value),color=(0,255,0))
        print(y_left_black_value ,y_right_black_value,x_left_black_value ,x_right_black_value)
        
        black_wall_m = (y_left_black_value - y_right_black_value) /(x_left_black_value - x_right_black_value)*-100
#        print("sum1=",sum1)
#        print("斜率=",int(black_wall_m*sum1))

     
    black_arrary_m[count]=black_wall_m
    if count==2:
        count=0
    else:
        count+=1
    for i in range(3):
        black_m_average=black_m_average+black_arrary_m[i]
    black_m_average = black_m_average/3
#    print("black_arrary_m=",black_arrary_m)
    print("black_m_average",black_m_average)
    #print("left_area+right_area=",(left_area+right_area)/1000)  
    #print("x_left_black_value=",x_left_black_value,"x_right_black_value=",x_right_black_value)
    if(g!=0):    
        uart.write(str('+')+str(60)+","+ str(80)+"E\n")
    if(y_right_black_value>200  and turn==1):
        uart.write(str('-')+str(60)+","+ str(80)+"E\n")
        print('1')
        time.sleep_ms(1200)
    elif(y_right_black_value>200 and y_left_black_value >200 and turn==2):
        uart.write(str('-')+str(70)+","+ str(120)+"E\n")
        print('2')
        time.sleep_ms(1200)
    elif(black_m_average<-7):
        print('3')
        uart.write(str('+')+str(70)+","+ str(85)+"E\n")
    elif(black_m_average>7): 
        print('4')
        uart.write(str('+')+str(60)+","+ str(110)+"E\n")
    else:
        print('5')
        uart.write(str('+')+str(60)+","+ str(97)+"E\n")   
    print("right_distance=", right_distance)
    time.sleep_ms(20)