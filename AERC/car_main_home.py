THRESHOLD = (0, 23, -72, 88, 104, -88)# Grayscale threshold for dark things...
import sensor, image, time,pyb
from pyb import LED
import car
from pid import PID
rho_pid = PID(p=0.4, i=0)
theta_pid = PID(p=0.001, i=0)
thresholds =[(81, 100, -72, 88, 104, -88)]
#

sensor.reset()
sensor.set_pixformat(sensor.RGB565)
sensor.set_framesize(sensor.QQQVGA) # 80x60 (4,800 pixels) - O(N^2) max = 2,3040,000.
#sensor.set_windowing([0,20,80,40])
sensor.skip_frames(time = 2000)     # WARNING: If you use QQVGA it may take seconds
clock = time.clock()                # to process a frame sometimes.

L_area=0
R_area=0
while(True):
    L_area=0
    R_area=0
    clock.tick()
    img = sensor.snapshot().binary([THRESHOLD])
    line = img.get_regression([(100,100)],area_threshold=250,robust = True)
    if (line):
        rho_err = abs(line.rho())-img.width()/2
        if line.theta()>90:
            theta_err = line.theta()-180
        else:
            theta_err = line.theta()
        img.draw_line(line.line(), color = 127)
        #print(rho_err,line.magnitude(),rho_err)
        if line.magnitude()>8:
            #if -40<b_err<40 and -30<t_err<30:
            rho_output = rho_pid.get_pid(rho_err,1)
            theta_output = theta_pid.get_pid(theta_err,1)
            output = rho_output+theta_output
            car.run(20+output*2.3, 20-output*2.3)
            print(30+output*1.5)
        else:
            for blob in img.find_blobs([thresholds[0]], pixels_threshold=50, area_threshold=50, merge=True,roi = (0,0,40,240)):
                img.draw_rectangle(blob.rect(),color =(255,0,0)) 
                L_area = blob.area()
        #左邊紅色
            for blob in img.find_blobs([thresholds[0]], pixels_threshold=50, area_threshold=50, merge=True,roi = (40,0,70,240)):
                    img.draw_rectangle(blob.rect(),color =(0,255,0))    
                    R_area = blob.area()
            if(L_area+10> R_area):                          
                  car.run(-20,20)
            else:
                   car.run(20,-20) 
            print("L_area=",L_area,"R_area=",R_area)    
    else:
        car.run(-20,-20)
        pass
    
    #print(clock.fps())
