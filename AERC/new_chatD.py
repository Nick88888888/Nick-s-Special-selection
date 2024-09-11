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
while a is None:  # 使用 None 作為條件黑線D圖
    see = 0
    L_area = 0
    R_area = 0
    x=0
    old_values = sensor1.sensor_value(return_old=True)
    new_values = sensor1.sensor_value()
    print(old_values)
    clock.tick()
    print(count)
    img = sensor.snapshot()
    for i in range(5):
       x+=new_values[i]
    if a!=1:
        if  new_values [4]==1 and count==0:
            car.run_turn(50,50)
            time.sleep_ms(80)
            car.run_turn(50,-55)
            time.sleep_ms(1100)
            c= None
            while(None):
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
                    c=1
            count+=1
        elif new_values [0]==1 and count==1:
            car.run_turn(50,50)
            time.sleep_ms(250)
            car.run_turn(0,0)
            time.sleep_ms(500)
            count+=1
        elif x>2 and count==2:
            car.run_turn(50,50)
            time.sleep_ms(200)
            car.run_turn(50,-60)
            time.sleep_ms(1100)
            car.run_turn(50,50)
            time.sleep_ms(200)
            count+=1
        elif x>3 and count==3:
            a=1
        else:
            line = img.get_regression([THRESHOLD_black], area_threshold=20, pixels_threshold=20)
            if line:
                rho_err = abs(line.rho()) - img.width() / 2
                img.draw_line(line.line(), color=[255, 255, 255])
                if line.theta() > 90:
                    theta_err = line.theta() - 180
                else:
                    theta_err = line.theta()
                if theta_err > 60 or theta_err < -60 or num == 1:
             
                    if theta_err > 5:
                        car.run_turn(45, -65)
                    elif theta_err < -5:
                        car.run_turn(-65,45)
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
car.run_turn(0,0)
time.sleep_ms(500)              
car.run_turn(50,50)
time.sleep_ms(200) 
car.run_turn(50,-50) 
time.sleep_ms(500)  
car.run_turn(0,0)   
a = None
count=0
while a is None:#跟藍線
    x=0
    old_values = sensor1.sensor_value(return_old=True)
    new_values = sensor1.sensor_value()
    clock.tick()
    print(count)
    img = sensor.snapshot()
    line = img.get_regression([THRESHOLD_black],area_threshold=20,pixels_threshold=20)
    for i in range(5):
        x+=new_values[i]
 
    if line:
        rho_err = abs(line.rho())-img.width()/2
        if line.theta()>90:
            theta_err = line.theta()-180
        else:
            theta_err = line.theta()
        img.draw_line(line.line(), color =[255,255,255])
        #print(rho_err,line.magnitude(),rho_err)
        if theta_err>50 or theta_err<-50:
            car.run_turn(65,65)
            time.sleep_ms(200)
            count+=1
        else: 
            if line.magnitude()>0.5:
                #if -40<b_err<40 and -30<t_err<30:
                rho_output = rho_pid.get_pid(rho_err,1)
                theta_output = theta_pid.get_pid(theta_err,1)
                output = rho_output+theta_output
                car.run(50+output, 50-output,theta_output,output)
                print("rho_pid=",rho_output ,"theta_pid=",theta_output,"output=",output,"L=",45+output,"R=",45-output)
    if x>=2 and count>=1 :
            a=1
                
                    
car.run_turn(0,0)
time.sleep_ms(500)  
car.run_turn(50,50)
time.sleep_ms(250) 
car.run_turn(-50,50) 
time.sleep_ms(500)
a = None
count=0
while a is None:#跟藍線
    x=0
    old_values = sensor1.sensor_value(return_old=True)
    new_values = sensor1.sensor_value()
    clock.tick()
    print(count)
    img = sensor.snapshot()
    line = img.get_regression([THRESHOLD_black],area_threshold=20,pixels_threshold=20)
    for i in range(5):
        x+=new_values[i]
    if new_values[0]==1:
        car.run_turn(50,50)
        time.sleep_ms(80)
        car.run_turn(-50,50)
        time.sleep_ms(1100)
        c= None
        while(None):
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
                c=1
    elif  new_values[0]==1:
        car.run_turn(50,50)
        time.sleep_ms(80)
        car.run_turn(50,-50)
        time.sleep_ms(1100)
        c= None
        while(None):
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
                c=1
    elif line:
        rho_err = abs(line.rho())-img.width()/2
        if line.theta()>90:
            theta_err = line.theta()-180
        else:
            theta_err = line.theta()
        img.draw_line(line.line(), color =[255,255,255])
        #print(rho_err,line.magnitude(),rho_err)
        if theta_err>50 or theta_err<-50:
            car.run_turn(65,65)
            time.sleep_ms(200)
            count+=1
        else: 
            if line.magnitude()>0.5:
                #if -40<b_err<40 and -30<t_err<30:
                rho_output = rho_pid.get_pid(rho_err,1)
                theta_output = theta_pid.get_pid(theta_err,1)
                output = rho_output+theta_output
                car.run(50+output, 50-output,theta_output,output)
                print("rho_pid=",rho_output ,"theta_pid=",theta_output,"output=",output,"L=",45+output,"R=",45-output)
    
