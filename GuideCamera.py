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
    def __init__(self, deviceID):
        dllPath = os.path.join(os.getcwd(), "dll/win64")
        os.add_dll_directory(dllPath)
        self.camera = cdll.LoadLibrary("./dll/win64/GuideSDK.dll")

        thermalImagePath = os.path.join(os.getcwd(), 'img')
        deviceCount = self.camera.GetDeviceNum()
        if deviceCount >= deviceID:
            self.deviceID = deviceID
            self.camera.SetPixelFormatEx(deviceID, 1)
            self.camera.OpenStream(deviceID, rgbCallback, y16Callback,
                           stateCallback, None, 2, 0)
            self.camera.SetPalette(deviceID, 2)
            self.camera.ShowPalette(deviceID, 0)
        else:
            raise Exception('No Guide device found.')

    def takeScreenShot(self):
        self.camera.TakeScreenshot(self.deviceID, b'./img', 3)

    # TODO:retrun a image
    def retrieve():
        print("Retrieve");

    def autoFocus(self):
        self.camera.FocusControl(self.deviceID, 4, 0)

    def release(self):
        self.camera.CloseStream(self.deviceID)

if __name__ == "__main__":
    thermalCam = GuideCamera(1)
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
    thermalCam.release()
