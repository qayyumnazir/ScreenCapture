import pyautogui,keyboard,cv2,win32api,os,wx,threading,imagezmq,sys,time
from os.path import isfile, join
from PIL import Image
import numpy as np

def Sender():
    while True:
        if keyboard.is_pressed('a') == True:
            break

    sender = imagezmq.ImageSender(connect_to='tcp://192.168.1.13:5555', REQ_REP=False)
    pathIn = r'C:\Users\qayyu\OneDrive\Desktop\Screenshooter\\'

    image_window_name = 'From Sender'
    i = 0
    time.sleep(2)
    finish = False
    while not finish:
        if keyboard.is_pressed('s') == True:
            finish=True
        i = i + 1
        print('Sending ' + str(i))

        for filename in os.listdir(pathIn):
            if filename.endswith(".png"):
                image = cv2.imread(os.path.join(pathIn, filename))
                sender.send_image(image_window_name, image)
                time.sleep(1)


        # Send an image to the queue
        sender.send_image(image_window_name, image)
        time.sleep(1)



def toAVI():
    pathIn = r'C:\Users\qayyu\OneDrive\Desktop\Screenshooter\\'
    pathOut = r'C:\Users\qayyu\OneDrive\Desktop\Video.avi'
    fps = 2
    frame_array = []
    files = [f for f in os.listdir(pathIn) if isfile(join(pathIn, f))]
    # for sorting the file names properly
    files.sort(key=lambda x: x[5:-4])
    files.sort()
    frame_array = []
    files = [f for f in os.listdir(pathIn) if isfile(join(pathIn, f))]
    # for sorting the file names properly
    files.sort(key=lambda x: x[5:-4])
    for i in range(len(files)):
        filename = pathIn + files[i]
        # reading each files
        img = cv2.imread(filename)
        height, width, layers = img.shape
        size = (width, height)

        # inserting the frames into an image array
        frame_array.append(img)
    out = cv2.VideoWriter(pathOut, cv2.VideoWriter_fourcc(*'DIVX'), fps, size)
    for i in range(len(frame_array)):
        # writing to a image array
        out.write(frame_array[i])
    out.release()

def screenshooterPositivePositive(coor1,coor2):


    flag=True
    while flag:
        if keyboard.is_pressed('a') == True:
            print("Start Record")
            flag= True
            q=1000
            while flag:
                if keyboard.is_pressed('s') == True:
                    print("Stop Record")
                    flag = False
                myScreenshot = pyautogui.screenshot(region=(coor1.x, coor1.y, coor2.x-coor1.x, coor2.y-coor1.y,))
                myScreenshot.save(r'C:\Userws\qayyu\OneDrive\Desktop\Screenshooter\image' + str(q) + '.png')
                q+=1

def screenshooterPositiveNegative(coor1,coor2):
    flag=True
    while flag:
        if keyboard.is_pressed('a') == True:
            print("Start Record")
            flag= True
            q=1000
            while flag:
                if keyboard.is_pressed('s') == True:
                    print("Stop Record")
                    flag = False
                myScreenshot = pyautogui.screenshot(region=(coor1.x, coor2.y, coor2.x-coor1.x, coor1.y-coor2.y,))
                myScreenshot.save(r'C:\Users\qayyu\OneDrive\Desktop\Screenshooter\image' + str(q) + '.png')
                q+=1

def screenshooterNegativeNegative(coor1,coor2):
    flag=True
    while flag:
        if keyboard.is_pressed('a') == True:
            print("Start Record")
            flag= True
            q=1000
            while flag:
                if keyboard.is_pressed('s') == True:
                    print("Stop Record")
                    flag = False
                myScreenshot = pyautogui.screenshot(region=(coor2.x, coor2.y, coor1.x-coor2.x, coor1.y-coor2.y,))
                myScreenshot.save(r'C:\Users\qayyu\OneDrive\Desktop\Screenshooter\image' + str(q) + '.png')
                q+=1

def screenshooterNegativePositive(coor1,coor2):
    flag=True
    while flag:
        if keyboard.is_pressed('a') == True:
            print("Start Record")
            flag= True
            q=1000
            while flag:
                if keyboard.is_pressed('s') == True:
                    print("Stop Record")
                    flag = False
                myScreenshot = pyautogui.screenshot(region=(coor2.x, coor1.y, coor1.x-coor2.x, coor2.y-coor1.y,))
                myScreenshot.save(r'C:\Users\qayyu\OneDrive\Desktop\Screenshooter\image' + str(q) + '.png')
                q+=1

def rctngle(x,y,w,h,dc,app):
    finish=False
    while not finish:
        if keyboard.is_pressed('s') == True:
            finish=True
        dc.DrawRectangle(x,y,w,h)


def chooseOrientation(coor1,coor2):

    app = wx.PySimpleApp()
    dc = wx.ScreenDC()
    dc.StartDrawingOnTop(None)
    dc.SetPen(wx.Pen('red', 2))
    dc.SetBrush(wx.TRANSPARENT_BRUSH)



    if coor2.x>=coor1.x and coor2.y>=coor1.y:
        t1 = threading.Thread(target=rctngle, args=(coor1.x, coor1.y, coor2.x - coor1.x, coor2.y - coor1.y,dc,app))
        t2 = threading.Thread(target=screenshooterPositivePositive, args=(coor1,coor2))


        t1.start()
        t2.start()


        t1.join()
        t2.join()



    elif coor1.x>coor2.x and coor2.y>coor1.y:
        t1 = threading.Thread(target=rctngle, args=(coor2.x, coor1.y, coor1.x -coor2.x, coor2.y - coor1.y,dc,app))
        t2 = threading.Thread(target=screenshooterNegativePositive, args=(coor1, coor2))

        t1.start()
        t2.start()

        t1.join()
        t2.join()



    elif coor1.x>coor2.x and coor1.y>coor2.y:
        t1 = threading.Thread(target=rctngle, args=(coor2.x, coor2.y, coor1.x-coor2.x, coor1.y-coor2.y,dc,app))
        t2 = threading.Thread(target=screenshooterNegativeNegative(), args=(coor1, coor2))

        t1.start()
        t2.start()

        t1.join()
        t2.join()

    else:
        t1 = threading.Thread(target=rctngle, args=(coor1.x, coor2.y, coor2.x-coor1.x, coor1.y-coor2.y,dc,app))
        t2 = threading.Thread(target=screenshooterPositiveNegative, args=(coor1, coor2))

        t1.start()
        t2.start()

        t1.join()
        t2.join()



def ScreenCapture():
    outerloop = True
    first = True
    while outerloop:

        if keyboard.is_pressed('W') == True:
            print("Ready to record")

            while outerloop:


                if win32api.GetKeyState(0x01) < 0:

                    if first:
                        first = False
                        coor1 = pyautogui.position()
                else:
                    if not first:
                        coor2 = pyautogui.position()
                        chooseOrientation(coor1,coor2)
                        finish = True
                        print("D if you want to change it to avi, F to skip")
                        while True:
                            if keyboard.is_pressed('d'):
                                toAVI()
                                break
                            elif keyboard.is_pressed('f'):
                                break


                        outerloop = False

ScreenCapture()
#Sender()
