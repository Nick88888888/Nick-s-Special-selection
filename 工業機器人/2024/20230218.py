THRESHOLD = (90, 100, 109, -103, 96, -64)
import sensor, image, time
from pyb import LED
import car
from pyb import Pin
from pid import PID
from pyb import UART
uart = UART(3, 19200)
rho_pid = PID(p=0.4, i=0,d=0.112)
theta_pid = PID(p=0.09, i=0,d=0.007)
Pin1 =  Pin('P8', Pin.OUT_PP)
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
def square():
	for blob in img.find_blobs([(100,100)],pixels_threshold=80,area_threshold=80,merge=True,):
		img.draw_rectangle(blob.rect(),color=(100,0,0))
		img.draw_cross(blob.cx(), blob.cy())
		return(int(blob.area()))
while(True):
	clock.tick()
	speed=43
	way=99
	img = sensor.snapshot().binary([THRESHOLD])
	line = img.get_regression([(100,100)],pixel_threshold=600, area_threshold=300,robust=True,roi = (0,0,40,60))
	if (line ):
		rho_err = abs(line.rho())-img.width()/2
		if line.theta()>90:
			theta_err = line.theta()-180
		else:
			theta_err = line.theta()
		print(rho_err,line.magnitude(),rho_err,theta_err,line.rho(),"line.length=",line.length ())
		img.draw_line(line.line(), color=127)
		if line.magnitude()>8 and theta_err<60 and theta_err>-60 and line.length ()>45:
			way=99
			if(count>3):
				count=0
			else:
				count = count+1
			value=0
			rho_output = rho_pid.get_pid(rho_err,1)
			theta_output = theta_pid.get_pid(theta_err,1)+7
			output = rho_output+theta_output
			avage[count] = output
			for i in range(5):
				value = value+ avage[i]
			value = value/5
			uart.write(str('+') + str(speed) + "," + str(int(way + value)) + "E\n")

	else:
		uart.write(str('+') + str(int(speed*0.8)) + "," + str(int(way)) + "E\n")
	time.sleep_ms(25)