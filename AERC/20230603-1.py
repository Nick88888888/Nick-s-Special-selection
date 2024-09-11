THRESHOLD_black = [(5, 20, -33, -11, 45, -128),(0, 27, 126, -128, -3, 126),(0, 100, 127, -128, -10, -128)]#first is green second is black
import sensor, image, time,pyb,math
from pyb import LED
import car
from pid import PID
rho_pid = PID(p=0.4, i=0)
theta_pid = PID(p=0.4, i=0)
thresholds_green =[(5, 20, -33, -11, 45, -128)]
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
while(True):
    L_area=0
    R_area=0
    clock.tick()
    img = sensor.snapshot()
    line = img.get_regression([THRESHOLD_black[1]],area_threshold=20,pixels_threshold=20,robust = True)
    if (line):
        if num==1:
            car.run(0, 0,0,0)
        else:
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
                car.run(55+output, 55-output,theta_output,output)
                print("rho_pid=",rho_output ,"theta_pid=",theta_output,"output=",output,"L=",45+output,"R=",45-output)
            
    img = sensor.snapshot()
    line = img.get_regression([THRESHOLD_black[2]],area_threshold=20,pixels_threshold=20,robust = True)
    if (line):
        if num==1:
            car.run(0, 0,0,0)
        else:
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
                car.run(55+output, 55-output,theta_output,output)
                print("rho_pid=",rho_output ,"theta_pid=",theta_output,"output=",output,"L=",45+output,"R=",45-output)
            
                                
                
                
    #for blob in img.find_blobs([THRESHOLD_black[0]], pixels_threshold=200, area_threshold=200, merge=True):
        ## These values depend on the blob not being circular - otherwise they will be shaky.
        #if blob.elongation() > 0.5:
            #line = img.get_regression([THRESHOLD_black[0]],area_threshold=20,pixels_threshold=20,robust = True)
           
            #print('ok')
            #rho_err = abs(line.rho())-img.width()/2
            #if line.theta()>90:
                #theta_err = line.theta()-180
            #else:
                #theta_err = line.theta()
            #img.draw_line(line.line(), color = 127)
            ##print(rho_err,line.magnitude(),rho_err)
            #if line.magnitude()>8:
                ##if -40<b_err<40 and -30<t_err<30:
                #rho_output = rho_pid.get_pid(rho_err,1)
                #theta_output = theta_pid.get_pid(theta_err,1)
                #output = rho_output+theta_output
                #car.run(50+output, 50-output,theta_output,output)      
            #num=1
        #else:
            #num=0 
      