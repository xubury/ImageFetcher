from datetime import datetime, date
import cv2
import os

def getTime():
    now = datetime.now()
    current_time = now.strftime("%H-%M-%S")
    return current_time

def getDate():
    return str(date.today())

def hconcatResizeMin(im_list, interpolation=cv2.INTER_CUBIC):
    h_min = min(im.shape[0] for im in im_list)
    im_list_resize = [cv2.resize(im, (int(im.shape[1] * h_min / im.shape[0]), h_min), interpolation=interpolation)
                      for im in im_list]
    return cv2.hconcat(im_list_resize)

def saveImage(img, type):
    # save image to img/Y-M-D/[type]/Y-M-D-H-M-S.jpg
    date = getDate()
    path = os.path.join("img", date, type)
    name = date + '-' +getTime() + '.jpg'
    # if output path not exists, create one
    if not os.path.exists(path):
        os.makedirs(path)
    fileName = os.path.join(path, name)
    cv2.imwrite(fileName, img)
    print("Save", type, "image to", fileName)

if __name__ == "__main__":
    print("Current Time =", getTime())
    print("Current Date =", getDate())
    img1 = cv2.imread("img/test.jpg")
    img2 = cv2.imread("img/temp.jpg")
    saveImage(img1, "visible")
    while True:
        cv2.imshow("test", hconcatResizeMin([img1, img2]))
        k = cv2.waitKey(1)
        if k == 27:
            break
