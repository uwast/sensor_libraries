#log1 = open('~/Desktop/GPSlog.txt', 'wr')
#log2 = open('~/Desktop/REClog.txt', 'wr')
#log3 = open('~/Desktop/GYROlog.txt', 'wr')


minTime = 8000
maxTime = 1
timeCount = 0
sensorCount1 = 0
sensorCount2 = 0
sensorCount3 = 0
sensorCount4 = 0

with open('timelog.txt', 'r+b')  as f:
    for line in f:
        timeCount = timeCount + 1
	if int(line) <minTime and timeCount > 50:
		minTime = int(line)
	elif int(line) > maxTime and timeCount > 50:
		maxTime = int(line)

print ('Maximum Delay Between Data was: ')
print maxTime

print ('Minimum Delay Between Data was: ')
print minTime


with open('ANElog.txt', 'r+b') as f:
    for line in f:
    	sensorCount4 = sensorCount4 + 1

print ('Numbers of lines missing from ANE: ')
print (timeCount - sensorCount4)

with open('GYROlog.txt', 'r+b') as f:
    for line in f:
        sensorCount4 = sensorCount3 + 1

print ('Numbers of lines missing from GYRO: ')
print (timeCount - sensorCount3)

with open('GPSlog.txt', 'r+b') as f:
    for line in f:
        sensorCount2 = sensorCount2 + 1

print ('Numbers of lines missing from GPS: ')
print (timeCount - sensorCount2)

with open('REClog.txt', 'r+b') as f:
    for line in f:
        sensorCount1 = sensorCount1 + 1

print ('Numbers of lines missing from REC: ')
print (timeCount - sensorCount1)
