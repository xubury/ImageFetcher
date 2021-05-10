from pypylon import pylon
import cv2

class BalserCamera:
    def __init__(self, width, height):
        self.camera = pylon.InstantCamera(pylon.TlFactory.GetInstance().CreateFirstDevice())
        self.camera.Open()
        self.camera.Width.SetValue(width)
        self.camera.Height.SetValue(height)
        self.camera.GainAuto.SetValue("Continuous")
        self.camera.BalanceWhiteAuto.SetValue("Continuous")
        self.camera.ExposureAuto.SetValue("Continuous")

        self.converter = pylon.ImageFormatConverter()
        # converting to opencv bgr format
        self.converter.OutputPixelFormat = pylon.PixelType_BGR8packed
        self.converter.OtputBitAlignment = pylon.OutputBitAlignment_MsbAligned
        # Grabing Continusely (video) with minimal delay
        self.camera.StartGrabbing(pylon.GrabStrategy_LatestImageOnly)

    def retrieve(self):
        grabResult = self.camera.RetrieveResult(5000, pylon.TimeoutHandling_ThrowException)
        if grabResult.GrabSucceeded():
            image = self.converter.Convert(grabResult).GetArray()
        grabResult.Release()
        return image

    def release(self):
        self.camera.StopGrabbing()

if __name__ == "__main__":
    visibleCam = BalserCamera(1920, 1080)
    cv2.namedWindow("test")
    while True:
        visibleImg = visibleCam.retrieve()
        cv2.imshow("test", visibleImg)
        k = cv2.waitKey(1)
        if k == 27:
            break
        elif k == ord('r'):
            cv2.imwrite("img/test.jpg", visibleImg)
    visibleCam.release()

