import Utils
import GuideCamera
import BalserCamera
import cv2
import os

if __name__ == "__main__":
    visibleCam = BalserCamera(1920, 1080)
    thermalCam = GuideCamera(1)
    cv2.namedWindow("Image fetcher")
    while True:
        temperature, thermalImg = thermalCam.retrieve(10, 60)
        visibleImg = visibleCam.retrieve()
        # concate two images horizontally
        concatImg = Utils.hconcatResizeMin([visibleImg, thermalImg])
        cv2.imshow("Image fetcher", concatImg)
        k = cv2.waitKey(1)
        if k == 27:
            # esc
            break
        elif k == ord('a'):
            # make thermal camera auto focus
            thermalCam.autoFocus()
        elif k == ord('r'):
            Utils.saveImage(visibleImg, "visible")
            Utils.saveImage(thermalImg, "thermal")
    # release cameras
    visibleCam.release()
    thermalCam.release()

