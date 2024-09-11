THRESHOLD_black = (0, 42, 87, -113, 118, 0)#first is black
THRESHOLD_blue = (0, 43, 70, -113, -92, 0)
import sensor, image, time,pyb,math
from pyb import LED
import car
from pid import PID
rho_pid = PID(p=0.4, i=0)
theta_pid = PID(p=0.4, i=0)
threshold_index = 0

sensor.reset()
sensor.set_pixformat(sensor.RGB565)
sensor.set_framesize(sensor.QQQVGA) # 80x60 (4,800 pixels) - O(N^2) max = 2,3040,000.
#sensor.set_windowing([0,20,80,40])
sensor.skip_frames(time = 2000)     # WARNING: If you use QQVGA it may take seconds
clock = time.clock()                # to process a frame sometimes.

L_area=0
R_area=0
num=0
x=0
b=0
while(True):
    L_area=0
    R_area=0
    clock.tick()
    img = sensor.snapshot()
    if(x!=1):
        for blob in img.find_blobs([THRESHOLD_blue], area_threshold=200,pixels_threshold=200,  merge=True):
            # These values depend on the blob not being circular - otherwise they will be shaky.
            if blob.elongation() > 0.1:
                img.draw_rectangle(blob.rect())
                img.draw_cross(blob.cx(), blob.cy())
                img.draw_keypoints([(blob.cx(), blob.cy(), int(math.degrees(blob.rotation())))], size=20)
                b=1
    if(b==1):
        if(x!=1):
            car.run(50,70,-50,0)
            time.sleep_ms(1000)
        else:
            line = img.get_regression([THRESHOLD_blue],area_threshold=20,pixels_threshold=20)
            rho_err = abs(line.rho())-img.width()/2
            if line.theta()>90:
                theta_err = line.theta()-180
            else:
                theta_err = line.theta()
            img.draw_line(line.line(), color =[255,255,255])
            #print(rho_err,line.magnitude(),rho_err)
            if line.magnitude()>0.5:
                #if -40<b_err<40 and -30<t_err<30:
                rho_output = rho_pid.get_pid(rho_err,1)
                theta_output = theta_pid.get_pid(theta_err,1)
                output = rho_output+theta_output
                car.run(55+output, 55-output,theta_output,output)
                print("rho_pid=",rho_output ,"theta_pid=",theta_output,"output=",output,"L=",45+output,"R=",45-output)
        x=1
    
            
    if(b!=1): 
        line = img.get_regression([THRESHOLD_black],area_threshold=20,pixels_threshold=20)
        rho_err = abs(line.rho())-img.width()/2
        if line.theta()>90:
            theta_err = line.theta()-180
        else:
            theta_err = line.theta()
        img.draw_line(line.line(), color =[255,255,255])
        #print(rho_err,line.magnitude(),rho_err)
        if line.magnitude()>0.5:
            #if -40<b_err<40 and -30<t_err<30:
            rho_output = rho_pid.get_pid(rho_err,1)
            theta_output = theta_pid.get_pid(theta_err,1)
            output = rho_output+theta_output
            car.run(55+output, 55-output,theta_output,output)
            print("rho_pid=",rho_output ,"theta_pid=",theta_output,"output=",output,"L=",45+output,"R=",45-output)
    
        
       
        
        
 
        

        

