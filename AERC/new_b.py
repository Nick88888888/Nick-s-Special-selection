THRESHOLD_black = (0, 20, -128, 127, -128, 127)#first is black
THRESHOLD_red = (48, 0, 7, 74, 16, 64)
import sensor, image, time, pyb, math, car,sensor1
from pyb import LED, UART
from pid import PID
rho_pid = PID(p=0.4, i=0)
theta_pid = PID(p=0.4, i=0)
threshold_index = 0

sensor.reset()
sensor.set_pixformat(sensor.RGB565)
sensor.set_framesize(sensor.QQQVGA) # 80x60 (4,800 pixels) - O(N^2) max = 2,3040,000.
#sensor.set_windowing([0,20,80,40])
sensor.skip_frames(time=2000)     # WARNING: If you use QQVGA it may take seconds
clock = time.clock()                # to process a frame sometimes.


num = 0
b = 0
a = None  # 初始化 a 為 None
num = 0
y = 0
find_area = 0
disconnected = 0
see=0
number=0
count=0
while a is None:  # 使用 None 作為條件part斷線
    see = 0
    L_area = 0
    R_area = 0
    x=0
    old_values = sensor1.sensor_value(return_old=True)
    new_values = sensor1.sensor_value()
    print(old_values)
    clock.tick()
    img = sensor.snapshot()
    for blob in img.find_blobs([THRESHOLD_black], area_threshold=20,pixels_threshold=20,  merge=True,roi=(0,0,80,10)):
                 if blob.elongation() > 0.1:
                       img.draw_rectangle(blob.rect())
                       img.draw_cross(blob.cx(), blob.cy())
                       img.draw_keypoints([(blob.cx(), blob.cy(), int(math.degrees(blob.rotation())))], size=20,color = (0,255,255))
                       see=1
                       
    if a != 1:
        line = img.get_regression([THRESHOLD_black], area_threshold=20, pixels_threshold=20)
        if line:
            rho_err = abs(line.rho()) - img.width() / 2
            img.draw_line(line.line(), color=[255, 255, 255])
            if line.theta() > 90:
                theta_err = line.theta() - 180
            else:
                theta_err = line.theta()
            if theta_err<10 and theta_err>-10 and see==0 :
                car.run_turn(0,0)
                a = 1      
            else:
                
                if theta_err > 60 or theta_err < -60 or num == 1:
                    if count!=2:
                        count+=1
                        while(theta_err > 5 or theta_err < -5):
                            clock.tick()
                            img = sensor.snapshot()
                            line = img.get_regression([THRESHOLD_black], area_threshold=20, pixels_threshold=20)
                            if line:
                                rho_err = abs(line.rho()) - img.width() / 2
                                img.draw_line(line.line(), color=[255, 255, 255])
                                if line.theta() > 90:
                                    theta_err = line.theta() - 180
                                else:
                                    theta_err = line.theta()
                            if theta_err > 5:
                                car.run_turn(50, -70)
                            elif theta_err < -5:
                                car.run_turn(-70, 50)
                            else:
                                num = 0
                    if count==2:
                        if see==0:
                            car.run_turn(-50,-50)
                   

                # print(rho_err,line.magnitude(),rho_err)
                else:
                    if line.magnitude() > 0.5:
                        # if -40<b_err<40 and -30<t_err<30:
                        rho_output = rho_pid.get_pid(rho_err, 1)
                        theta_output = theta_pid.get_pid(theta_err, 1)
                        output = rho_output + theta_output
                        car.run(50+output, 50-output,theta_output,output)
                        #print("rho_pid=",rho_output ,"theta_pid=",theta_output,"output=",output,"L=",45+output,"R=",45-output)
            print("count=",count)
            #print("theta_err=",theta_err)
a = None
speed=0
while a is None:  # 使用 None 作為條件part2黃線
    value=0
    cx=0
    cy=0
    see = 0
    x=0
    old_values = sensor1.sensor_value(return_old=True)
    new_values = sensor1.sensor_value()
    print(old_values)
    clock.tick()
    img = sensor.snapshot()
    #for blob in img.find_blobs([THRESHOLD_black], area_threshold=20,pixels_threshold=20,  merge=True,roi=(0,0,80,10)):
        #if blob.elongation() > 0.1:
           #img.draw_rectangle(blob.rect())
           #img.draw_cross(blob.cx(), blob.cy())
           #img.draw_keypoints([(blob.cx(), blob.cy(), int(math.degrees(blob.rotation())))], size=20,color = (0,255,255))
           #cx=blob.cx()
           #cy=blob.cy()
    for i in range(5):
        x+=new_values[i]
    if x>=2:
        a=1    
                       
    if a != 1:
    
        for i in range(5):
           value += new_values[i]*(i+1)*10
        value = value-30
        if value==-30:
            value=0
            
        if value==-20:
            speed=25
        elif value==-10:
            speed=7
        elif value==20:
            speed=-25
        elif value==30: 
             speed=-7
        else:
            speed=0
        car.run_turn(50-speed,48+speed)
        print(new_values)
car.run_turn(50,50)
time.sleep_ms(200)
car.run_turn(-50,50)
time.sleep_ms(1000)
car.run_turn(0,0)

a = None
while a is None:  # 接黃
    x=0
    old_values = sensor1.sensor_value(return_old=True)
    new_values = sensor1.sensor_value()
    print(old_values)
    clock.tick()
    img = sensor.snapshot()
    for i in range(5):
        x+=new_values[i]
    if x>=2:
        a=1                      
    if a != 1:
        line = img.get_regression([THRESHOLD_black], area_threshold=20, pixels_threshold=20)
        if line:
            rho_err = abs(line.rho()) - img.width() / 2
            img.draw_line(line.line(), color=[255, 255, 255])
            if line.theta() > 90:
                theta_err = line.theta() - 180
            else:
                theta_err = line.theta()
          
                
            if theta_err > 60 or theta_err < -60 or num == 1:
                while(theta_err > 5 or theta_err < -5):
                    clock.tick()
                    img = sensor.snapshot()
                    line = img.get_regression([THRESHOLD_black], area_threshold=20, pixels_threshold=20)
                    if line:
                        rho_err = abs(line.rho()) - img.width() / 2
                        img.draw_line(line.line(), color=[255, 255, 255])
                        if line.theta() > 90:
                            theta_err = line.theta() - 180
                        else:
                            theta_err = line.theta()
                    if theta_err > 5:
                        car.run_turn(50, -70)
                    elif theta_err < -5:
                        car.run_turn(-70, 50)
                    else:
                        num = 0
            else:
                if line.magnitude() > 0.5:
                    # if -40<b_err<40 and -30<t_err<30:
                    rho_output = rho_pid.get_pid(rho_err, 1)
                    theta_output = theta_pid.get_pid(theta_err, 1)
                    output = rho_output + theta_output
                    car.run(50+output, 50-output,theta_output,output)
car.run_turn(50,50) 
time.sleep_ms(230)
car.run_turn(-50,60) 
time.sleep_ms(900)
car.run_turn(0,0) 
a = None
while a is None:  # 接藍線
    x=0
    old_values = sensor1.sensor_value(return_old=True)
    new_values = sensor1.sensor_value()
    print(old_values)
    clock.tick()
    img = sensor.snapshot()
    for i in range(5):
        x+=new_values[i]
    if x>=2:
        a=1                      
    if a != 1:
        line = img.get_regression([THRESHOLD_black], area_threshold=20, pixels_threshold=20)
        if line:
            rho_err = abs(line.rho()) - img.width() / 2
            img.draw_line(line.line(), color=[255, 255, 255])
            if line.theta() > 90:
                theta_err = line.theta() - 180
            else:
                theta_err = line.theta()
         
            
                
            if theta_err > 60 or theta_err < -60 or num == 1:
                while(theta_err > 5 or theta_err < -5):
                    clock.tick()
                    img = sensor.snapshot()
                    line = img.get_regression([THRESHOLD_black], area_threshold=20, pixels_threshold=20)
                    if line:
                        rho_err = abs(line.rho()) - img.width() / 2
                        img.draw_line(line.line(), color=[255, 255, 255])
                        if line.theta() > 90:
                            theta_err = line.theta() - 180
                        else:
                            theta_err = line.theta()
                    if theta_err > 5:
                        car.run_turn(50, -70)
                    elif theta_err < -5:
                        car.run_turn(-70, 50)
                    else:
                        num = 0
            else:
                if line.magnitude() > 0.5:
                    # if -40<b_err<40 and -30<t_err<30:
                    rho_output = rho_pid.get_pid(rho_err, 1)
                    theta_output = theta_pid.get_pid(theta_err, 1)
                    output = rho_output + theta_output
                    car.run(50+output, 50-output,theta_output,output)
car.run_turn(50,50)
time.sleep_ms(350)
car.run_turn(50,-65) 
time.sleep_ms(900)
car.run_turn(0,0) 
a = None
count=0
while a is None:#接藍線
    clock.tick()
    img = sensor.snapshot()
    line = img.get_regression([THRESHOLD_black],area_threshold=20,pixels_threshold=20)
    if line:
        rho_err = abs(line.rho())-img.width()/2
        if line.theta()>90:
            theta_err = line.theta()-180
        else:
            theta_err = line.theta()
        img.draw_line(line.line(), color =[255,255,255])
        #print(rho_err,line.magnitude(),rho_err)
        if theta_err>50 or theta_err<-50:
            car.run_turn(65,60)
            time.sleep_ms(100)
            count+=1
            
        else: 
            if line.magnitude()>0.5:
                #if -40<b_err<40 and -30<t_err<30:
                rho_output = rho_pid.get_pid(rho_err,1)
                theta_output = theta_pid.get_pid(theta_err,1)
                output = rho_output+theta_output
                car.run(60+output, 60-output,theta_output,output)
                print("rho_pid=",rho_output ,"theta_pid=",theta_output,"output=",output,"L=",45+output,"R=",45-output)
        if count ==4:         
           a=1
a = None
while a is None:  # 使用 None 作為條件
    see = 0
    L_area = 0
    R_area = 0
    x=0
    old_values = sensor1.sensor_value(return_old=True)
    new_values = sensor1.sensor_value()
    print(old_values)
    clock.tick()
    img = sensor.snapshot()
    for blob in img.find_blobs([THRESHOLD_red], area_threshold=300, pixels_threshold=300, merge=True):#偵測有沒有紅色
        # These values depend on the blob not being circular - otherwise they will be shaky.
        if blob.elongation() > 0.1:
            img.draw_rectangle(blob.rect())
            img.draw_cross(blob.cx(), blob.cy())
            img.draw_keypoints([(blob.cx(), blob.cy(), int(math.degrees(blob.rotation())))], size=20)
            print(blob.elongation())
            a = 2
    if a != 1:
        line = img.get_regression([THRESHOLD_black], area_threshold=20, pixels_threshold=20)
        if line:
            rho_err = abs(line.rho()) - img.width() / 2
            img.draw_line(line.line(), color=[255, 255, 255])
            if line.theta() > 90:
                theta_err = line.theta() - 180
            else:
                theta_err = line.theta()
            if theta_err > 60 or theta_err < -60 or num == 1:
                for i in range(5):#遇到銳角
                    x+=old_values[i]*(i+1)/3
                if x==1:
                    value=0
                    while(value==0):
                         new_values = sensor1.sensor_value()
                         for i in range(5):
                            value += new_values[i]*(i+1)*10
                         value = value-30
                         if value==-30:
                            value=0
                         car.run_turn(-50,-50)
                    print("value=",value)
                    car.run_turn(value*1.8,-value*1.4)
                    time.sleep_ms(1000)    
                else:
                    if theta_err > 5:
                        car.run_turn(50, -70)
                    elif theta_err < -5:
                        car.run_turn(-70, 50)
                    else:
                        num = 0

            # print(rho_err,line.magnitude(),rho_err)
            else:
                if line.magnitude() > 0.5:
                    # if -40<b_err<40 and -30<t_err<30:
                    rho_output = rho_pid.get_pid(rho_err, 1)
                    theta_output = theta_pid.get_pid(theta_err, 1)
                    output = rho_output + theta_output
                    car.run(50+output, 50-output,theta_output,output)
                    # print("rho_pid=",rho_output ,"theta_pid=",theta_output,"output=",output,"L=",45+output,"R=",45-output)

#print("stop")
#if a == 1:
    #print("yellow")
#elif a == 2:
    #print("Red")#繞水瓶
    #car.run_turn(50, -60)
    #time.sleep_ms(700)
    #car.run_turn(0, 0)
    #time.sleep_ms(50)
    #car.run_turn(50, 50)
    #time.sleep_ms(1300)
    #car.run_turn(-50, 50)
    #time.sleep_ms(800)
    #car.run_turn(50, 50)
    #time.sleep_ms(1500)
    #car.run_turn(-50, 50)
    #time.sleep_ms(1300)
    #value=0
    #while(value==0):
        #clock.tick()
        #img = sensor.snapshot()
        #for blob in img.find_blobs([THRESHOLD_black], area_threshold=300, pixels_threshold=300, merge=True):#偵測有沒有黑色
        ## These values depend on the blob not being circular - otherwise they will be shaky.
            #if blob.elongation() > 0.1:
                #img.draw_rectangle(blob.rect())
                #img.draw_cross(blob.cx(), blob.cy())
                #img.draw_keypoints([(blob.cx(), blob.cy(), int(math.degrees(blob.rotation())))], size=20)
                #print(blob.elongation())
                #value = 2
        #car.run_turn(52,50)
    #print("stop2")
    #car.run_turn(50,-60)
    #time.sleep_ms(700)    
                     

