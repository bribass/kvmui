cmake_minimum_required(VERSION 3.20)
project(kvmui)

# Required versioning
set(QT_MIN_VERSION "6.8.0")
set(KF_MIN_VERSION "6.0.0")

# Load extra-cmake-modules
find_package(ECM ${KF_MIN_VERSION} REQUIRED NO_MODULE)
set(CMAKE_MODULE_PATH ${ECM_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

# Load KDE CMake modules
include(KDEInstallDirs)
include(KDECMakeSettings)
include(KDECompilerSettings NO_POLICY_SCOPE)
include(ECMInstallIcons)
include(FeatureSummary)

# Find the required libraries
find_package(Qt6 ${QT_MIN_VERSION} CONFIG REQUIRED COMPONENTS
        Core
        Widgets
)
find_package(KF6 ${KF_MIN_VERSION} REQUIRED COMPONENTS
        CoreAddons
        I18n
        WidgetsAddons
        XmlGui
)

# Build the executables
add_executable(kvmui)
target_sources(kvmui PRIVATE
        src/main.cpp
        src/mainwindow.cpp
        src/vminfo.cpp
        src/vmprovider.cpp
        src/vmprovideraddwizard.cpp
        src/providers/quickemu.cpp
)
target_include_directories(kvmui PRIVATE src)
target_link_libraries(kvmui
        Qt6::Widgets
        KF6::CoreAddons
        KF6::I18n
        KF6::WidgetsAddons
        KF6::XmlGui
)

# Install the executables
install(TARGETS kvmui ${KDE_INSTALL_TARGETS_DEFAULT_ARGS})
install(FILES src/kvmuiui.rc DESTINATION ${KDE_INSTALL_KXMLGUIDIR}/kvmui)
ecm_install_icons(DESTINATION share/icons ICONS
        icons/sc-apps-kvmui-hv-quickemu.svg
)

# And summarize
feature_summary(WHAT ALL INCLUDE_QUIET_PACKAGES FATAL_ON_MISSING_REQUIRED_PACKAGES)
