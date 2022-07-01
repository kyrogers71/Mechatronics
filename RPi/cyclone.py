#lab 2, raspberry pi diode bar testing
#Kyle, Jamie, Jennifer, Praneeth, Shrya


import RPi.GPIO as GPIO
import time

# run a cleanup to clear last time it ran
GPIO.cleanup()

#setup GPIO using Board numbering
GPIO.setmode(GPIO.BOARD)

#tell the Rpi these are outputs
GPIO.setup(3, GPIO.IN)
GPIO.setup(7, GPIO.IN) #GPIO.PUD_UP has state 0 as pressed
GPIO.setup(11, GPIO.OUT)
GPIO.setup(13, GPIO.OUT)
GPIO.setup(15, GPIO.OUT)
GPIO.setup(32, GPIO.OUT)
GPIO.setup(19, GPIO.OUT)
GPIO.setup(21, GPIO.OUT)
GPIO.setup(33, GPIO.OUT)

#delay = .2

win = 0
cheater = 0
cycleCount = 0
lightTime = 10*1000

while True:
    #light 1st light from t=0 up to lightTime-1, then turn it off at
    #lightTime to prepare for the next light
    if (cycleCount >=0 and cycleCount<lightTime):
        GPIO.output(11,True)    
    if cycleCount==lightTime:
        GPIO.output(11, False)
        
    # Light 2:
    if (cycleCount>(lightTime) and cycleCount<(lightTime*2)):
        GPIO.output(13,True)    
    if cycleCount==(lightTime*2):
        GPIO.output(13, False)
        
    # Light 3:
    if (cycleCount>(lightTime*2) and cycleCount<(lightTime*3)):
        GPIO.output(15,True)    
    if cycleCount==(lightTime*3):
        GPIO.output(15, False)
        if GPIO.input(3): # if the button is on right before WIN light
            cheater = 1   # then they were holding it/ cheating
            #print("CHEATER!!!")
            #time.sleep(1)
        
    # Light 4: THE WIN LIGHT
    if (cycleCount>(lightTime*3) and cycleCount<(lightTime*4)):
        GPIO.output(32,True)
        if (GPIO.input(3)and cheater==0):
            win = 1
    
    if cycleCount==(lightTime*4):
        GPIO.output(32, False)
        
    # Light 5:
    if (cycleCount>(lightTime*4) and cycleCount<(lightTime*5)):
        GPIO.output(19,True)    
    if cycleCount==(lightTime*5):
        GPIO.output(19, False)
        
    # Light 6:
    if (cycleCount>(lightTime*5) and cycleCount<(lightTime*6)):
        GPIO.output(21,True)    
    if cycleCount==(lightTime*6):
        GPIO.output(21, False)
        
    # Light 7:
    if (cycleCount>(lightTime*6) and cycleCount<(lightTime*7)):
        GPIO.output(33,True)    
    if cycleCount==(lightTime*7):
        GPIO.output(33, False)
    
    
    # after running through the loop
    if (cycleCount < (lightTime*7)):
        cycleCount = cycleCount+1
        #print(cycleCount)
    else:
        cycleCount = 0
        cheater = 0
    if win == 1 :
        GPIO.output(32, True)
        print("YOU WIN!!!!")
        
        #time.sleep(5)
        #win = 0
        break
    
#code for when you win
winPin = GPIO.PWM(32, 10)
winPin.start(50)
time.sleep(3)
GPIO.output(32, False)
GPIO.cleanup()
