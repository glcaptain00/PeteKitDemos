from digitalio import DigitalInOut, Direction, Pull
import cv2
import board
import boto3
import datetime

client = boto3.client('dynamodb')
dynamodb = boto3.resource('dynamodb')
region_name='us-west-2'
table = dynamodb.table("TestTable")

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
        f = open('/home/pi/testimage.jpg', 'rb')
        table.put_item({'TestPartitionKey': 'Doorbell1', 'Time': datetime.now.ctime(), 'ImageData': f.read()})
        f.close()
    if (btnB.value == False):
        cam.release()
        break