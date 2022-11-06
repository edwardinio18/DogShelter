cmake_minimum_required(VERSION 3.19)
project(a14-edwardinio18)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(CMAKE_PREFIX_PATH "C:\\Qt\\6.3.0\\mingw_64\\lib\\cmake")

find_package(Qt6 COMPONENTS
		Core
		Gui
		Widgets
		REQUIRED)

add_executable(a14-edwardinio18
		GUI/GUI.cpp GUI/GUI.h CustomException/customException.cpp CustomException/customException.h Dog/dog.cpp Dog/dog.h Main/main.cpp Main/main.h Repository/repository.cpp Repository/repository.h Repository/repositoryCSV.cpp Repository/repositoryCSV.h Repository/repositoryHTML.cpp Repository/repositoryHTML.h Repository/userRepository.cpp Repository/userRepository.h Service/service.cpp Service/service.h Service/userServ.cpp Service/userServ.h Validator/validator.h Validator/validator.cpp Service/undoredo.cpp Service/undoredo.h TableView/TableView.cpp TableView/TableView.h)

target_link_libraries(a14-edwardinio18
		Qt::Core
		Qt::Gui
		Qt::Widgets
		)

if (WIN32)
	set(DEBUG_SUFFIX)
	set(QT_INSTALL_PATH "${CMAKE_PREFIX_PATH}")
	if (NOT EXISTS "${QT_INSTALL_PATH}/bin")
		set(QT_INSTALL_PATH "${QT_INSTALL_PATH}/..")
		if (NOT EXISTS "${QT_INSTALL_PATH}/bin")
			set(QT_INSTALL_PATH "${QT_INSTALL_PATH}/..")
		endif ()
	endif ()
	if (EXISTS "${QT_INSTALL_PATH}/plugins/platforms/qwindows${DEBUG_SUFFIX}.dll")
		add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
				COMMAND ${CMAKE_COMMAND} -E make_directory
				"$<TARGET_FILE_DIR:${PROJECT_NAME}>/plugins/platforms/")
		add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
				COMMAND ${CMAKE_COMMAND} -E copy
				"${QT_INSTALL_PATH}/plugins/platforms/qwindows${DEBUG_SUFFIX}.dll"
				"$<TARGET_FILE_DIR:${PROJECT_NAME}>/plugins/platforms/")
	endif ()
	foreach (QT_LIB Core Gui Widgets)
		add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
				COMMAND ${CMAKE_COMMAND} -E copy
				"${QT_INSTALL_PATH}/bin/Qt6${QT_LIB}${DEBUG_SUFFIX}.dll"
				"$<TARGET_FILE_DIR:${PROJECT_NAME}>")
	endforeach (QT_LIB)
endif ()