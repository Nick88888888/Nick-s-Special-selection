import sensor, image, time, math,array
from pyb import UART
from pyb import LED

uart = UART(3, 19200)
threshold_index = 0
thresholds = [(100, 66, 84, -71, 70, -48)]
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
    (100, 0, 120, 240),
    (0, 60, 160, 240),
    (160, 60, 160, 240)
]

avage=[0]*5
count=0
MAXY_R=0
MAXY_L=0
MAXY_M=0
past=0
while(True):
    if(count>3):
        count=0
    else:
        count = count+1

    value=0
    speed=35
    way=100
    R_area=-1
    L_area=-1
    past = value
    clock.tick()
    img = sensor.snapshot()

    MAXY_L=0
    MAXX_L=0

    for blob in img.find_blobs([thresholds[threshold_index]], pixels_threshold=150,
                                area_threshold=250, merge=True,roi = ROIS[1] ):
        if MAXY_L< blob.cy():
            MAXY_L =  blob.cy()
            MAXX_L =  blob.cx()      
            L_area = blob.area()

    if(MAXY_L!=0):
        img.draw_rectangle(blob.rect(),color =(255,55,0))
        img.draw_cross(MAXX_L , MAXY_L)
        img.draw_keypoints([(MAXX_L , MAXY_L, int(math.degrees(blob.rotation())))], size=20)
        img.draw_keypoints([(MAXX_L , MAXY_L, int(math.degrees(blob.rotation())))], size=20)
        #print(" MAXY_L=", MAXY_L)

    MAXY_R =0
    MAXX_R =320

    for blob in img.find_blobs([thresholds[threshold_index]], pixels_threshold=150,
                                area_threshold=250, merge=True,roi = ROIS[2] ):
        if MAXY_R< blob.cy():
            MAXY_R= blob.cy()
            MAXX_R=  blob.cx()
            R_area = blob.area()

    if(MAXY_R!=0):
        img.draw_rectangle(blob.rect(),color =(0,55,255))
        img.draw_cross(MAXX_R , MAXY_R)
        img.draw_keypoints([(MAXX_R , MAXY_R, int(math.degrees(blob.rotation())))], size=20)
        img.draw_keypoints([(MAXX_R , MAXY_R, int(math.degrees(blob.rotation())))], size=20)

    avage[count] = int(( R_area - L_area )/1880)

    for i in range(5):
         value = value+ avage[i]
    value = value/5
    way = way-value + (value-past)*0
    print("way=",way)
    uart.write(str('+') + str(speed) + "," + str(int(way)) + "E\n")
    time.sleep_ms(30)
