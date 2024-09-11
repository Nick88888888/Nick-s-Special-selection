THRESHOLD = (100, 93, 12, -76, -7, 101)
import sensor, image, time
from pyb import LED
import car
from pyb import Pin
from pid import PID
from pyb import UART
uart = UART(3, 19200)
rho_pid = PID(p=0.47, i=0,d=0.112)
theta_pid = PID(p=0.1, i=0,d=0.007)
Pin1 =  Pin('P8', Pin.OUT_PP)
#LED(1).on()
#LED(2).on()
#LED(3).on()
sensor.reset()
sensor.set_vflip(True)
sensor.set_hmirror(True)
sensor.set_pixformat(sensor.RGB565)
sensor.set_framesize(sensor.QQQVGA)
sensor.skip_frames(time=2000)
clock = time.clock()
avage=[0]*5
count=0
n=0
while(True):
    clock.tick()
    speed=40
    way=103
    img = sensor.snapshot().binary([THRESHOLD])
    line = img.get_regression([(100,100)], robust=True)
    if (line):
        rho_err = abs(line.rho())-img.width()/2
        if line.theta()>90:
            theta_err = line.theta()-180
        else:
            theta_err = line.theta()
        
        print(rho_err,line.magnitude(),rho_err,theta_err,line.rho())
        img.draw_line(line.line(), color=127)
        if line.magnitude()>8 and theta_err<60 and theta_err>-60:
            
            way=100
            if(count>3):   
                count=0
            else:
                count = count+1
            value=0
            rho_output = rho_pid.get_pid(rho_err,1)
            theta_output = theta_pid.get_pid(theta_err,1)+14
            output = rho_output+theta_output
            avage[count] = output
            for i in range(4):      
                value = value+ avage[i] 
            value = value/10
            uart.write(str('+') + str(speed) + "," + str(int(way + value)) + "E\n")
            print("way+output=",way+output)
        else:   
            if(line.rho()<0): 
                way=100
                if(count>3):   
                    count=0
                else:
                    count = count+1
                value=0
                rho_output = rho_pid.get_pid(rho_err,1)
                theta_output = theta_pid.get_pid(theta_err,1)+10
                output = rho_output+theta_output
                avage[count] = output
                for i in range(4):      
                    value = value+ avage[i] 
                value = value/10
                uart.write(str('+') + str(speed) + "," + str(int(way-value)) + "E\n")
    else:
        if(n==1):
            way=99
            uart.write(str('+') + str(speed) + "," + str(int(way)) + "E\n")
            LED(1).on()
            LED(2).on()
            LED(3).on()
            Pin1.high()
            time.sleep_ms(20)
            
        else:
            uart.write(str('+') + str(speed) + "," + str(int(way)) + "E\n")
            time.sleep_ms(100)
    time.sleep_ms(25)
