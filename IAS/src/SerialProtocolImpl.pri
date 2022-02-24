#INCLUDEPATH += D:\opencv3-2\build\install\include
INCLUDEPATH += /home/tesis/opencv-4.0.1/include
INCLUDEPATH += $$PWD/Action/
INCLUDEPATH += $$PWD/Command/
INCLUDEPATH += $$PWD/Protocol/
INCLUDEPATH += $$PWD/Image/
INCLUDEPATH += $$PWD/Utils/
INCLUDEPATH += $$PWD/Screen/
INCLUDEPATH += $$PWD/Screen/Components/
INCLUDEPATH += $$PWD/Computer/
INCLUDEPATH += $$PWD/Error/

#LIBS += D:\opencv3-2\build\bin\libopencv_core320.dll
#LIBS += D:\opencv3-2\build\bin\libopencv_highgui320.dll
#LIBS += D:\opencv3-2\build\bin\libopencv_imgcodecs320.dll
#LIBS += D:\opencv3-2\build\bin\libopencv_imgproc320.dll
#LIBS += D:\opencv3-2\build\bin\libopencv_features2d320.dll
#LIBS += D:\opencv3-2\build\bin\libopencv_calib3d320.dll
#LIBS += D:\opencv3-2\build\bin\libopencv_tracking320.dll

#LIBS += -L$$(OPENCV_SDK_DIR)/x86/mingw/lib \

# OpenCV
INCLUDEPATH += /usr/local/include/opencv2
LIBS += $(shell pkg-config opencv --libs)

#LIBS += -lopencv_core320        \
#        -lopencv_highgui320     \
#        -lopencv_imgcodecs320   \
#        -lopencv_imgproc320     \
#        -lopencv_features2d320  \
#        -lopencv_calib3d320

HEADERS += \
    $$PWD/Action/Action.h \
    $$PWD/Action/ActionFactory.h \
    $$PWD/Action/ActionFactoryES.h \
    $$PWD/Action/ActionFactoryIAS.h \
    $$PWD/Action/ActionFactoryOBC.h \
    $$PWD/Action/ActionManager.h \
    $$PWD/Action/ActionsQueue.h \
    $$PWD/Action/CaptureReqAction.h \
    $$PWD/Action/CatalogReqAction.h \
    $$PWD/Action/CatalogResAction.h \
    $$PWD/Action/CropReqAction.h \
    $$PWD/Action/DeleteReqAction.h \
    $$PWD/Action/ImageHQReqAction.h \
    $$PWD/Action/ImageHQResAction.h \
    $$PWD/Action/ImageLQReqAction.h \
    $$PWD/Action/ImageLQResAction.h \
    $$PWD/Action/KeepaliveReqAction.h \
    $$PWD/Action/KeepaliveResAction.h \
    $$PWD/Action/LedIASGetReqAction.h \
    $$PWD/Action/LedIASGetResAction.h \
    $$PWD/Action/LedIASSetReqAction.h \
    $$PWD/Action/LedOBCGetReqAction.h \
    $$PWD/Action/LedOBCGetResAction.h \
    $$PWD/Action/LedOBCSetReqAction.h \
    $$PWD/CommLinkMonitor.h \
    $$PWD/Command/CaptureCommandReq.h \
    $$PWD/Command/CatalogCommandReq.h \
    $$PWD/Command/CatalogCommandRes.h \
    $$PWD/Command/CropCommandReq.h \
    $$PWD/Command/DeleteCommandReq.h \
    $$PWD/Command/ImageHQCommandReq.h \
    $$PWD/Command/ImageHQCommandRes.h \
    $$PWD/Command/ImageLQCommandReq.h \
    $$PWD/Command/ImageLQCommandRes.h \
    $$PWD/Command/KeepaliveCommandReq.h \
    $$PWD/Command/KeepaliveCommandRes.h \
    $$PWD/Command/LedIASGetCommandReq.h \
    $$PWD/Command/LedIASGetCommandRes.h \
    $$PWD/Command/LedIASSetCommandReq.h \
    $$PWD/Command/LedOBCGetCommandReq.h \
    $$PWD/Command/LedOBCGetCommandRes.h \
    $$PWD/Command/LedOBCSetCommandReq.h \
    $$PWD/Computer/PortId.h \
    $$PWD/Error/ErrorId.h \
    $$PWD/Error/ErrorManager.h \
    $$PWD/Image/CameraManager.h \
    $$PWD/Image/ImageManagerIAS.h \
    $$PWD/Protocol/PacketBuilder.h \
    $$PWD/Protocol/PacketValidator.h \
    $$PWD/Protocol/SPIPortManager.h \
    $$PWD/Screen/Components/ButtonViewModel.h \
    $$PWD/Screen/Components/ImagePropertiesViewModel.h \
    $$PWD/Screen/Components/InfoTextViewModel.h \
    $$PWD/Screen/Components/TextFieldViewModel.h \
    $$PWD/Computer/Computer.h \
    $$PWD/Computer/EarthStation.h \
    $$PWD/Computer/ImageAcquisitionSystem.h \
    $$PWD/Computer/OnBoardComputer.h \
    $$PWD/Image/ImageDataBase.h \
    $$PWD/Image/ImageProperties.h \
    $$PWD/Image/ImageManager.h \
    $$PWD/Image/ROI.h \
    $$PWD/Protocol/CommManager.h \
    $$PWD/Command/Command.h \
    $$PWD/Command/CommandCode.h \
    $$PWD/Image/ImageEditor.h \
    $$PWD/Protocol/PacketReader.h \
    $$PWD/Protocol/SerialPortManager.h \
    $$PWD/Command/TransmissionQueue.h \
    $$PWD/Screen/AbstractScreenViewModel.h \
    $$PWD/Screen/MainScreenViewModel.h \
    $$PWD/Screen/ScreenProperties.h \
    $$PWD/Utils/Defines.h \
    $$PWD/Utils/Defines.h \
    $$PWD/Utils/Files.h \
    $$PWD/Utils/ImageFileInfo.h \
    $$PWD/Utils/Operators.h \
    $$PWD/ViewModel.h \
    $$PWD/ViewModelManager.h

SOURCES += \
    $$PWD/Action/Action.cpp \
    $$PWD/Action/ActionFactory.cpp \
    $$PWD/Action/ActionFactoryES.cpp \
    $$PWD/Action/ActionFactoryIAS.cpp \
    $$PWD/Action/ActionFactoryOBC.cpp \
    $$PWD/Action/ActionManager.cpp \
    $$PWD/Action/ActionsQueue.cpp \
    $$PWD/Action/CaptureReqAction.cpp \
    $$PWD/Action/CatalogReqAction.cpp \
    $$PWD/Action/CatalogResAction.cpp \
    $$PWD/Action/CropReqAction.cpp \
    $$PWD/Action/DeleteReqAction.cpp \
    $$PWD/Action/ImageHQReqAction.cpp \
    $$PWD/Action/ImageHQResAction.cpp \
    $$PWD/Action/ImageLQReqAction.cpp \
    $$PWD/Action/ImageLQResAction.cpp \
    $$PWD/Action/KeepaliveReqAction.cpp \
    $$PWD/Action/KeepaliveResAction.cpp \
    $$PWD/Action/LedIASGetReqAction.cpp \
    $$PWD/Action/LedIASGetResAction.cpp \
    $$PWD/Action/LedIASSetReqAction.cpp \
    $$PWD/Action/LedOBCGetReqAction.cpp \
    $$PWD/Action/LedOBCGetResAction.cpp \
    $$PWD/Action/LedOBCSetReqAction.cpp \
    $$PWD/CommLinkMonitor.cpp \
    $$PWD/Command/CaptureCommandReq.cpp \
    $$PWD/Command/CatalogCommandReq.cpp \
    $$PWD/Command/CatalogCommandRes.cpp \
    $$PWD/Command/CropCommandReq.cpp \
    $$PWD/Command/DeleteCommandReq.cpp \
    $$PWD/Command/ImageHQCommandReq.cpp \
    $$PWD/Command/ImageHQCommandRes.cpp \
    $$PWD/Command/ImageLQCommandReq.cpp \
    $$PWD/Command/ImageLQCommandRes.cpp \
    $$PWD/Command/KeepaliveCommandReq.cpp \
    $$PWD/Command/KeepaliveCommandRes.cpp \
    $$PWD/Command/LedIASGetCommandReq.cpp \
    $$PWD/Command/LedIASGetCommandRes.cpp \
    $$PWD/Command/LedIASSetCommandReq.cpp \
    $$PWD/Command/LedOBCGetCommandReq.cpp \
    $$PWD/Command/LedOBCGetCommandRes.cpp \
    $$PWD/Command/LedOBCSetCommandReq.cpp \
    $$PWD/Error/ErrorManager.cpp \
    $$PWD/Image/CameraManager.cpp \
    $$PWD/Image/ImageManagerIAS.cpp \
    $$PWD/Protocol/PacketBuilder.cpp \
    $$PWD/Protocol/PacketValidator.cpp \
    $$PWD/Protocol/SPIPortManager.cpp \
    $$PWD/Screen/Components/ButtonViewModel.cpp \
    $$PWD/Screen/Components/ImagePropertiesViewModel.cpp \
    $$PWD/Screen/Components/InfoTextViewModel.cpp \
    $$PWD/Screen/Components/TextFieldViewModel.cpp \
    $$PWD/Computer/Computer.cpp \
    $$PWD/Computer/EarthStation.cpp \
    $$PWD/Computer/ImageAcquisitionSystem.cpp \
    $$PWD/Computer/OnBoardComputer.cpp \
    $$PWD/Image/ImageDataBase.cpp \
    $$PWD/Image/ImageProperties.cpp \
    $$PWD/Image/ImageManager.cpp \
    $$PWD/Protocol/CommManager.cpp \
    $$PWD/Command/Command.cpp \
    $$PWD/Image/ImageEditor.cpp \
    $$PWD/Protocol/PacketReader.cpp \
    $$PWD/Protocol/SerialPortManager.cpp \
    $$PWD/Command/TransmissionQueue.cpp \
    $$PWD/Screen/AbstractScreenViewModel.cpp \
    $$PWD/Screen/MainScreenViewModel.cpp \
    $$PWD/Screen/ScreenProperties.cpp \
    $$PWD/Utils/Files.cpp \
    $$PWD/Utils/ImageFileInfo.cpp \
    $$PWD/Utils/Operators.cpp \
    $$PWD/ViewModel.cpp \
    $$PWD/ViewModelManager.cpp

DISTFILES +=
