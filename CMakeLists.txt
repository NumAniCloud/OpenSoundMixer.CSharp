# Debug Release�Ɍ���
set(CMAKE_CONFIGURATION_TYPES Debug Release CACHE TYPE INTERNAL FORCE )

# �v���W�F�N�g��
project(OpenSoundMixer)

# CMake �o�[�W�����`�F�b�N
if (MSVC)
cmake_minimum_required(VERSION 2.8.11)
else()
cmake_minimum_required(VERSION 2.8)
endif()

# �R���p�C���ݒ�
if (MSVC)
	# ���ɉ���
else()
	set(CMAKE_CXX_FLAGS "-std=c++11 -fPIC" ${CMAKE_CXX_FLAGS})
endif()

# �\�[�X�R�[�h�ݒ�
set(common_src
	src/osm.Decorder.cpp
	src/osm.Manager_Impl.cpp
	src/osm.ReferenceObject.cpp
	src/osm.Sound_Impl.cpp
	src/Decorder/osm.OggDecorder.cpp
	src/Decorder/osm.WaveDecorder.cpp)

set(xaudio2_src
	src/Manager/osm.Manager_Impl_XAudio2.cpp)

set(pulse_audio_src
	src/Manager/osm.Manager_Impl_PulseAudio.cpp)

set(test_src
	src/main.cpp)

if(WIN32)
list(APPEND common_src
	${xaudio2_src})
else()
list(APPEND common_src
	${pulse_audio_src})
endif()

list(APPEND test_src
	${common_src})


# �C���N���[�h�̐ݒ�
include_directories(
	src/
	)

# �R���p�C�����ǉ�
add_executable( osmtest ${test_src} )
add_library( osmlib STATIC ${common_src} )

if (MSVC)

else()
	FIND_PACKAGE(PulseAudio REQUIRED)
	list(APPEND osmtest ${PulseAudio_LIBRARY})

	find_package(Threads REQUIRED)
	list(APPEND common_lib ${CMAKE_THREAD_LIBS_INIT})
endif()

# �t���O����
if (MSVC)
	if (NOT USE_MSVC_RUNTIME_LIBRARY_DLL)
		foreach (flag CMAKE_C_FLAGS
			CMAKE_C_FLAGS_DEBUG
			CMAKE_C_FLAGS_RELEASE
			CMAKE_CXX_FLAGS
			CMAKE_CXX_FLAGS_DEBUG
			CMAKE_CXX_FLAGS_RELEASE)

			if (${flag} MATCHES "/MD")
				string(REGEX REPLACE "/MD" "/MT" ${flag} "${${flag}}")
			endif()
			if (${flag} MATCHES "/MDd")
				string(REGEX REPLACE "/MDd" "/MTd" ${flag} "${${flag}}")
			endif()
		endforeach()
	endif()
endif()

# �o�͐�̐ݒ�
if (MSVC)
set_target_properties(osmlib PROPERTIES OUTPUT_NAME_DEBUG "OpenSoundMixer" )
set_target_properties(osmlib PROPERTIES OUTPUT_NAME_RELEASE "OpenSoundMixer" )
set_target_properties(osmtest PROPERTIES OUTPUT_NAME_DEBUG "OpenSoundMixerTest" )
set_target_properties(osmtest PROPERTIES OUTPUT_NAME_RELEASE "OpenSoundMixerTest" )
else()
set_target_properties(osmlib PROPERTIES OUTPUT_NAME "OpenSoundMixer" )
set_target_properties(osmtest PROPERTIES OUTPUT_NAME "OpenSoundMixerTest" )
endif()

install(
	TARGETS osmlib
	ARCHIVE DESTINATION lib
	LIBRARY DESTINATION lib)

install(
	TARGETS osmtest
	RUNTIME DESTINATION bin
	ARCHIVE DESTINATION bin
	LIBRARY DESTINATION bin)