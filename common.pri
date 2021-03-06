PROJECT_ROOT_PATH = $${PWD}/

CONFIG(debug, debug|release) {
    BUILD_FLAG = debug
    DEFINES += _DEBUG_
} else {
    BUILD_FLAG = release
}

BIN_PATH = $${PROJECT_ROOT_PATH}/bin/$${BUILD_FLAG}/
BUILD_PATH = $${PROJECT_ROOT_PATH}/build/$${BUILD_FLAG}/
IMPORT_PATH = $${PROJECT_ROOT_PATH}/import/
DESTDIR = $${BIN_PATH}
UI_DIR = $${BUILD_PATH}/ui/
RCC_DIR = $${BUILD_PATH}/rcc/
MOC_DIR = $${BUILD_PATH}/moc/
OBJECTS_DIR = $${BUILD_PATH}/obj/

INCLUDEPATH += $${IMPORT_PATH}/
