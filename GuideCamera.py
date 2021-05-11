from ctypes import *
import os
import cv2
import numpy as np
import matplotlib.pyplot as plt


class GD_RGB_INFO(Structure):
    _fields_ = [("rgbData", POINTER(c_ubyte)),
                ("imgWidth", c_int32),
                ("imgHeight", c_int32),
                ("devID", c_int32)]


class GD_Y16_INFO(Structure):
    _fields_ = [("y16Data", POINTER(c_int16)),
                ("imgWidth", c_int32),
                ("imgHeight", c_int32),
                ("devID", c_int32)]


class GD_STATE_INFO(Structure):
    _fields_ = [("CONNECT_STATE", c_int32),
                ("devID", c_int32)]


@CFUNCTYPE(None, GD_RGB_INFO, c_void_p)
def rgbCallback(rgbInfo, params):
    rgbInfo
    #  content = cast(params,POINTER(py_object)).contents
    #  if content == None:
    #      return
    #  cam = content.value
    #  dataSize = rgbInfo.imgWidth * rgbInfo.imgHeight * 3
    #  array = cast(rgbInfo.rgbData, POINTER(c_ubyte * dataSize)).contents
    #  cam.image = np.frombuffer(array, dtype=np.uint8).reshape(480, 640, 3)


@CFUNCTYPE(None, GD_Y16_INFO, c_void_p)
def y16Callback(y16, params):
    y16


@CFUNCTYPE(None, GD_STATE_INFO, c_void_p)
def stateCallback(stateinfo, params):
    print("state callback")


class GuideCamera():
    def __init__(self, deviceID):
        dllPath = os.path.join(os.getcwd(), "dll/win64")
        os.add_dll_directory(dllPath)
        self.camera = cdll.LoadLibrary("./dll/win64/GuideSDK.dll")

        deviceCount = self.camera.GetDeviceNum()
        if deviceCount >= deviceID:
            self.deviceID = deviceID
            self.camera.SetPixelFormatEx(deviceID, 2)
            self.camera.OpenStream(deviceID, rgbCallback, y16Callback,
                                   stateCallback, cast(pointer(py_object(self)), c_void_p), 2, 0)
            self.camera.SetPalette(deviceID, 2)
            self.camera.ShowPalette(deviceID, 0)
            self.image = np.zeros((480, 640, 3), dtype=np.uint8)
            self.gray = np.zeros((480, 640), dtype=np.float32)
            self.tempMatrix = np.zeros((480, 640), dtype=np.float32)
        else:
            raise Exception('No Guide device found.')

    def takeScreenShot(self):
        self.camera.TakeScreenshot(self.deviceID, b'./img', 3)

    # retrieve temperature and RGB image,
    # the RGB value are mapped according to (tempuratue - minTemp) / (maxTemp - minTemp)
    def retrieve(self, minTemp, maxTemp):
        self.camera.GetTempMatrix(
            self.deviceID, self.tempMatrix.ctypes.data_as(POINTER(c_float)), 640, 480)
        self.gray = (self.tempMatrix - minTemp) / (maxTemp - minTemp)
        self.gray[self.gray > 1] = 1
        self.gray[self.gray < 0] = 0
        self.gray *= 255
        self.gray = np.round(self.gray)
        self.image = cv2.applyColorMap(
            self.gray.astype(np.uint8), cv2.COLORMAP_HOT)
        return self.tempMatrix, self.image

    def autoFocus(self):
        self.camera.FocusControl(self.deviceID, 4, 0)

    def release(self):
        self.camera.CloseStream(self.deviceID)


if __name__ == "__main__":
    thermalCam = GuideCamera(1)
    cv2.namedWindow("test")
    while True:
        k = cv2.waitKey(1)
        temp, color = thermalCam.retrieve(10, 60)
        cv2.imshow("test", color)
        if k == 27:
            cv2.destroyAllWindows()
            break
        elif k == ord('r'):
            cv2.imwrite("img/temp.jpg", temp)
            cv2.imwrite("img/test.jpg", color)
        elif k == ord('a'):
            thermalCam.autoFocus()
    thermalCam.release()
