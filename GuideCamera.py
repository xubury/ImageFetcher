from ctypes import *
import os
import cv2

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


@CFUNCTYPE(None, GD_Y16_INFO, c_void_p)
def y16Callback(y16, params):
    y16

@CFUNCTYPE(None, GD_STATE_INFO, c_void_p)
def stateCallback(stateinfo, params):
    stateinfo

class GuideCamera():
    def __init__(self):
        dllPath = os.path.join(os.getcwd(), "dll/win64")
        os.add_dll_directory(dllPath)
        self.dll = cdll.LoadLibrary("./dll/win64/GuideSDK.dll")

        thermalImagePath = os.path.join(os.getcwd(), 'img')
        deviceCount = self.dll.GetDeviceNum()
        if deviceCount > 0:
            self.deviceID = deviceID
            self.dll.SetPixelFormatEx(deviceID, 1)
            self.dll.OpenStream(deviceID, rgbCallback, y16Callback,
                           stateCallback, None, 2, 0)
            self.dll.SetPalette(deviceID, 2)
            self.dll.ShowPalette(deviceID, 0)
        else:
            raise Exception('No Guide device found.')

    def takeScreenShot(self):
        self.dll.TakeScreenshot(self.deviceID, b'./img', 3)

    def autoFocus(self):
        self.dll.FocusControl(self.deviceID, 4, 0)

if __name__ == "__main__":
    thermalCam = GuideCamera()
    cv2.namedWindow("test")
    while True:
        k = cv2.waitKey(0)
        if k == 27:
            cv2.destroyAllWindows()
            break
        elif k == ord('r'):
            thermalCam.takeScreenShot()
        elif k == ord('a'):
            thermalCam.autoFocus()
