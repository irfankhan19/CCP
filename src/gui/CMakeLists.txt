

include_directories(${QT_INCLUDES} ${CMAKE_CURRENT_BINARY_DIR} ../model ../io)

set(SRC_view FileBatch.cpp HistoryChanger.cpp viewcluster.cpp MainWindow.cpp RunData.cpp RunBatch.cpp SolutionPool.cpp)
set(SRC_view_H  FileBatch.h viewcluster.h MainWindow.h RunData.h RunBatch.h SolutionPool.h HistoryChanger.h)
set (SRC_View_UIS MainWindow.ui RunData.ui RunBatch.ui)

qt4_automoc(${SRC_view})
QT4_WRAP_CPP(MOC_CPP ${SRC_view_H})
QT4_WRAP_UI(SRC_View_UIS_H ${SRC_View_UIS})

add_library(CCPClusterView SHARED ${SRC_view} ${MOC_CPP} ${SRC_View_UIS_H})

target_link_libraries(CCPClusterView ${QT_QTCORE_LIBRARY} ${QT_QTGUI_LIBRARY} ${QT_QTSCRIPT_LIBRARY} CCPModelLib)
