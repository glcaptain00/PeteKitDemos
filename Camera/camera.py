from digitalio import DigitalInOut, Direction, Pull
import cv2
import board

# Button A
btnA = DigitalInOut(board.D5)
btnA.direction = Direction.INPUT
btnA.pull = Pull.UP

# Button B
btnB = DigitalInOut(board.D6)
btnB.direction = Direction.INPUT
btnB.pull = Pull.UP

cam = cv2.VideoCapture(0)

while True:
    if (btnA.value == False):
        ret, image = cam.read()
        cv2.imwrite('/home/pi/testimage.jpg', image)
    if (btnB.value == False):
        cam.release()
        break