import time
import serial

con1 = raw_input('Enter GPS connection')
con2 = raw_input('Enter Receiver connection')
con3 = raw_input('Enter Gyro connection')
con4 = raw_input('Enter faked anenometer connection')


ser1 = serial.Serial(con1, 9600, timeout=1)
ser2 = serial.Serial(con2, 9600, timeout=1)
ser3 = serial.Serial(con3, 9600, timeout=1)
ser4 = serial.Serial(con4, 9600, timeout=1)

log1 = open('GPSlog.txt', 'wr')
log2 = open('REClog.txt', 'wr')
log3 = open('GYROlog.txt', 'wr')
log4 = open('ANElog.txt', 'wr')
timelog = open('timelog.txt', 'wr')


print('Beginning test...')
try:

    while 1:
        startTime = int(round(time.time() * 1000))

        response1 = ser1.readline()
        response2 = ser2.readline()
        response3 = ser3.readline()
        response4 = ser4.readline()

        # Write sensor data to log files

        log1.write(reponse1)
        log2.write(response2)
        log3.write(response3)
        log4.write(response4)
        

        # Write timing to log file

        endTime = int(round(time.time() * 1000))
        totalTime = endTime - startTime
        timelog.write(str(totalTime) + '\n')
     
except KeyboardInterrupt:
    ser1.close()
    ser2.close()
    ser3.close()
    ser4.close()

    log1.close()
    log2.close()
    log3.close()
    log4.close()
    timelog.close()

