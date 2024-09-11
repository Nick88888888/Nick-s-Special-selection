THRESHOLD_black = (0, 20, -128, 127, -128, 127)#first is black
THRESHOLD_yellow =(100, 0, -12, 127, 32, 127)
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
a=0
x=0
find_area=0
num=0
while( a==0):
    see=0 
    L_area=0
    R_area=0
    clock.tick()
    img = sensor.snapshot()
    for blob in img.find_blobs([THRESHOLD_yellow], area_threshold=300,pixels_threshold=300,  merge=True):
        # These values depend on the blob not being circular - otherwise they will be shaky.
        if blob.elongation() > 0.1:
            img.draw_rectangle(blob.rect())
            img.draw_cross(blob.cx(), blob.cy())
            img.draw_keypoints([(blob.cx(), blob.cy(), int(math.degrees(blob.rotation())))], size=20)
            print(blob.elongation())
            a=1
    if(a!=1):     
         line = img.get_regression([THRESHOLD_black],area_threshold=20,pixels_threshold=20)
         if (line):
             rho_err = abs(line.rho())-img.width()/2
             if line.theta()>90:
                 theta_err = line.theta()-180
             else:
                 theta_err = line.theta()
             img.draw_line(line.line(), color =[255,255,255])
             for blob in img.find_blobs([THRESHOLD_black], area_threshold=20,pixels_threshold=20,  merge=True,roi=(0,0,80,10)):
                 if blob.elongation() > 0.1:
                       img.draw_rectangle(blob.rect())
                       img.draw_cross(blob.cx(), blob.cy())
                       img.draw_keypoints([(blob.cx(), blob.cy(), int(math.degrees(blob.rotation())))], size=20,color = (0,255,255))
                       see=1
                       find_area=0
             if see==0 and num==1:
                find_area=1
                car.run_turn(50,50)
             elif see==0:
                 for blob in img.find_blobs([THRESHOLD_black], area_threshold=20,pixels_threshold=20,  merge=True):
                     if blob.elongation() > 0.1:
                          img.draw_rectangle(blob.rect())
                          img.draw_cross(blob.cx(), blob.cy())
                          img.draw_keypoints([(blob.cx(), blob.cy(), int(math.degrees(blob.rotation())))], size=20)
                          if blob.area()<700 and blob.cx()>20 and blob.cx()<50 and blob.cy()>45 and theta_err<15 and theta_err>-15:
                             find_area=1
                             num=1
             print("blob.area()=",blob.area(),"blob.cx()=",blob.cx(),"blob.cy()=",blob.cy())
             if(find_area!=1):
                 if theta_err>60 or theta_err<-60 or x==1:
                    if theta_err>5:
                        car.run_turn(50,-65)
                    elif theta_err<-5:  
                        car.run_turn(-65,50)
                    else:
                        x=0
                    
                 #print(rho_err,line.magnitude(),rho_err)
                 else:
                     if line.magnitude()>0.5:
                         #if -40<b_err<40 and -30<t_err<30:
                         rho_output = rho_pid.get_pid(rho_err,1)
                         theta_output = theta_pid.get_pid(theta_err,1)
                         output = rho_output+theta_output
                         car.run(50+output, 50-output,theta_output,output)
                         #print("rho_pid=",rho_output ,"theta_pid=",theta_output,"output=",output,"L=",45+output,"R=",45-output)
             else:
                 car.run_turn(50,50)   
                   
         #else:
             #car.run_turn(45,55)     
  


#car.run_turn(0,0) 
#print("second")

        

