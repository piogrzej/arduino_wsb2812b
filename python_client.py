import serial
import time

LED_COUNT = 60
SHORT_DELAY_TIME = 0.008
LONG_DELAY_TIME = 0.03
SERIAL = '/dev/ttyUSB0'
BAUDRATE = 115200
byteArray = bytearray(4)

def setSingleLedToColor(led,R,G,B):
    
    s = serial.Serial(SERIAL, BAUDRATE, timeout=1)
    byteArray = bytearray(4)

    byteArray[0] = led
    byteArray[1] = R
    byteArray[2] = G
    byteArray[3] = B
    s.write(byteArray)
    # delay to give arduino some time to proces request
    time.sleep(SHORT_DELAY_TIME)

    s.close()

def applyChanges():
    s = serial.Serial(SERIAL, BAUDRATE, timeout=1)
    byteArray = bytearray(4)

    byteArray[0] = 255
    byteArray[1] = 0
    byteArray[2] = 0
    byteArray[3] = 0

    s.write(byteArray)
    # delay to give arduino some time to proces request
    time.sleep(SHORT_DELAY_TIME)

    s.close()

def setAllLedsToColor(R,G,B):

    s = serial.Serial(SERIAL, BAUDRATE, timeout=1)

    byteArray[0] = 254
    byteArray[1] = R
    byteArray[2] = G
    byteArray[3] = B

    s.write(byteArray)
    # delay to give arduino some time to proces request
    time.sleep(LONG_DELAY_TIME)

    s.close()

def endlessRainbow():

    while True:
        setAllLedsToColor(248, 12, 18)
        applyChanges()
        setAllLedsToColor(238, 17, 0)
        applyChanges()
        setAllLedsToColor(255, 51, 17)
        applyChanges()
        setAllLedsToColor(255, 68, 34)
        applyChanges()
        setAllLedsToColor(255, 102, 68)
        applyChanges()
        setAllLedsToColor(255, 153, 51)
        applyChanges()
        setAllLedsToColor(254, 174, 45)
        applyChanges()
        setAllLedsToColor(204, 187, 51)
        applyChanges()
        setAllLedsToColor(208, 195, 16)
        applyChanges()
        setAllLedsToColor(170, 204, 34)
        applyChanges()
        setAllLedsToColor(105, 208, 37)
        applyChanges()
        setAllLedsToColor(34, 204, 170)
        applyChanges()
        setAllLedsToColor(18, 189, 185)
        applyChanges()
        setAllLedsToColor(17, 170, 187)
        applyChanges()
        setAllLedsToColor(68, 68, 221)
        applyChanges()
        setAllLedsToColor(51, 17, 187)
        applyChanges()
        setAllLedsToColor(59, 12, 189)
        applyChanges()
        setAllLedsToColor(68, 34, 153)
        applyChanges()

endlessRainbow()
