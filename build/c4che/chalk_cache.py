AR = 'arm-none-eabi-ar'
ARFLAGS = 'rcs'
AS = 'arm-none-eabi-gcc'
BINDIR = '/usr/local/bin'
BLOCK_MESSAGE_KEYS = []
BUILD_DIR = 'chalk'
BUILD_TYPE = 'app'
BUNDLE_BIN_DIR = 'chalk'
BUNDLE_NAME = 'pebble_bus.pbw'
CC = ['arm-none-eabi-gcc']
CCLNK_SRC_F = []
CCLNK_TGT_F = ['-o']
CC_NAME = 'gcc'
CC_SRC_F = []
CC_TGT_F = ['-c', '-o']
CC_VERSION = ('4', '7', '2')
CFLAGS = ['-std=c99', '-mcpu=cortex-m3', '-mthumb', '-ffunction-sections', '-fdata-sections', '-g', '-fPIE', '-Os', '-D_TIME_H_', '-Wall', '-Wextra', '-Werror', '-Wno-unused-parameter', '-Wno-error=unused-function', '-Wno-error=unused-variable']
CFLAGS_MACBUNDLE = ['-fPIC']
CFLAGS_cshlib = ['-fPIC']
CPPPATH_ST = '-I%s'
DEFINES = ['RELEASE', 'PBL_PLATFORM_CHALK', 'PBL_COLOR', 'PBL_ROUND', 'PBL_MICROPHONE', 'PBL_SMARTSTRAP', 'PBL_HEALTH', 'PBL_COMPASS', 'PBL_SMARTSTRAP_POWER', 'PBL_DISPLAY_WIDTH=180', 'PBL_DISPLAY_HEIGHT=180', 'PBL_SDK_3']
DEFINES_ST = '-D%s'
DEST_BINFMT = 'elf'
DEST_CPU = 'arm'
DEST_OS = 'darwin'
INCLUDES = ['chalk']
LD = 'arm-none-eabi-ld'
LIBDIR = '/usr/local/lib'
LIBPATH_ST = '-L%s'
LIB_DIR = 'node_modules'
LIB_JSON = []
LIB_ST = '-l%s'
LINKFLAGS = ['-mcpu=cortex-m3', '-mthumb', '-Wl,--gc-sections', '-Wl,--warn-common', '-fPIE', '-Os']
LINKFLAGS_MACBUNDLE = ['-bundle', '-undefined', 'dynamic_lookup']
LINKFLAGS_cshlib = ['-shared']
LINKFLAGS_cstlib = ['-Wl,-Bstatic']
LINK_CC = ['arm-none-eabi-gcc']
MESSAGE_KEYS = {u'temperature': 10001, u'get_upcoming_busses': 10003, u'getWeather': 10002, u'cityname': 10007, u'cityid': 10006, u'color_picker': 10009, u'stop_id': 10005, u'boolean_box': 10008, u'stop_name': 10004, u'icon': 10000}
MESSAGE_KEYS_DEFINITION = '/Users/sebastiengouin-davis/Dropbox/code-drawer/pebble_bus/build/src/message_keys.auto.c'
MESSAGE_KEYS_HEADER = '/Users/sebastiengouin-davis/Dropbox/code-drawer/pebble_bus/build/include/message_keys.auto.h'
MESSAGE_KEYS_JSON = '/Users/sebastiengouin-davis/Dropbox/code-drawer/pebble_bus/build/js/message_keys.json'
NODE_PATH = '/Users/sebastiengouin-davis/Library/Application Support/Pebble SDK/SDKs/current/node_modules'
PEBBLE_SDK_COMMON = '/Users/sebastiengouin-davis/Library/Application Support/Pebble SDK/SDKs/current/sdk-core/pebble/common'
PEBBLE_SDK_PLATFORM = '/Users/sebastiengouin-davis/Library/Application Support/Pebble SDK/SDKs/current/sdk-core/pebble/chalk'
PEBBLE_SDK_ROOT = '/Users/sebastiengouin-davis/Library/Application Support/Pebble SDK/SDKs/current/sdk-core/pebble'
PLATFORM = {'TAGS': ['chalk', 'color', 'round', 'mic', 'strap', 'strappower', 'compass', 'health', '180w', '180h'], 'MAX_FONT_GLYPH_SIZE': 256, 'ADDITIONAL_TEXT_LINES_FOR_PEBBLE_H': [], 'MAX_APP_BINARY_SIZE': 65536, 'MAX_RESOURCES_SIZE': 1048576, 'MAX_APP_MEMORY_SIZE': 65536, 'MAX_WORKER_MEMORY_SIZE': 10240, 'NAME': 'chalk', 'BUNDLE_BIN_DIR': 'chalk', 'BUILD_DIR': 'chalk', 'MAX_RESOURCES_SIZE_APPSTORE': 262144, 'DEFINES': ['PBL_PLATFORM_CHALK', 'PBL_COLOR', 'PBL_ROUND', 'PBL_MICROPHONE', 'PBL_SMARTSTRAP', 'PBL_HEALTH', 'PBL_COMPASS', 'PBL_SMARTSTRAP_POWER', 'PBL_DISPLAY_WIDTH=180', 'PBL_DISPLAY_HEIGHT=180']}
PLATFORM_NAME = 'chalk'
PREFIX = '/usr/local'
PROJECT_INFO = {'appKeys': {u'temperature': 10001, u'get_upcoming_busses': 10003, u'getWeather': 10002, u'cityname': 10007, u'cityid': 10006, u'color_picker': 10009, u'stop_id': 10005, u'boolean_box': 10008, u'stop_name': 10004, u'icon': 10000}, u'sdkVersion': u'3', u'projectType': u'native', u'uuid': u'77b40a84-30ad-4ca5-8106-8d80f38f2fa5', u'messageKeys': {u'temperature': 10001, u'get_upcoming_busses': 10003, u'getWeather': 10002, u'cityname': 10007, u'cityid': 10006, u'color_picker': 10009, u'stop_id': 10005, u'boolean_box': 10008, u'stop_name': 10004, u'icon': 10000}, 'companyName': u'sebgd@icloud.com', u'enableMultiJS': True, u'targetPlatforms': [u'chalk'], u'capabilities': [u'location', u'configurable'], 'versionLabel': u'1.0', 'longName': u'RFTA', u'displayName': u'RFTA', 'shortName': u'RFTA', u'watchapp': {u'watchface': False}, u'resources': {u'media': [{u'targetPlatforms': None, u'type': u'bitmap', u'name': u'IMAGE_SPLASH', u'file': u'images/weather_icon.png'}]}, 'name': u'RFTA'}
REQUESTED_PLATFORMS = [u'chalk']
RESOURCES_JSON = [{u'targetPlatforms': None, u'type': u'bitmap', u'name': u'IMAGE_SPLASH', u'file': u'images/weather_icon.png'}]
RPATH_ST = '-Wl,-rpath,%s'
SANDBOX = False
SDK_VERSION_MAJOR = 5
SDK_VERSION_MINOR = 84
SHLIB_MARKER = None
SIZE = 'arm-none-eabi-size'
SONAME_ST = '-Wl,-h,%s'
STLIBPATH_ST = '-L%s'
STLIB_MARKER = None
STLIB_ST = '-l%s'
SUPPORTED_PLATFORMS = ['aplite', 'basalt', 'chalk', 'diorite', 'emery']
TARGET_PLATFORMS = ['chalk']
TIMESTAMP = 1479610221
USE_GROUPS = True
VERBOSE = 0
WEBPACK = '/Users/sebastiengouin-davis/Library/Application Support/Pebble SDK/SDKs/current/node_modules/.bin/webpack'
cprogram_PATTERN = '%s'
cshlib_PATTERN = 'lib%s.so'
cstlib_PATTERN = 'lib%s.a'
macbundle_PATTERN = '%s.bundle'
