
#pragma once

#include <stdio.h>
#include <stdint.h>
#include <memory>
#include <atomic>

#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif

namespace osm
{
	struct Sample
	{
		int16_t	Left;
		int16_t	Right;
	};

	/**
	@brief	�Q�ƃJ�E���^�̃C���^�[�t�F�[�X
	*/
	class IReference
	{
	public:
		/**
		@brief	�Q�ƃJ�E���^�����Z����B
		@return	���Z��̎Q�ƃJ�E���^
		*/
		virtual int AddRef() = 0;

		/**
		@brief	�Q�ƃJ�E���^���擾����B
		@return	�Q�ƃJ�E���^
		*/
		virtual int GetRef() = 0;

		/**
		@brief	�Q�ƃJ�E���^�����Z����B0�ɂȂ������A�C���X�^���X���폜����B
		@return	���Z��̎Q�ƃJ�E���^
		*/
		virtual int Release() = 0;
	};

	class Sound
		: public IReference
	{
	protected:
		Sound() {}
		virtual ~Sound() {}
	public:
	};

	class Manager
	{
	protected:
		Manager(){}
		~Manager(){}
	public:

	};

	template <class T>
	void SafeAddRef(T& t)
	{
		if (t != NULL)
		{
			t->AddRef();
		}
	}

	template <class T>
	void SafeRelease(T& t)
	{
		if (t != NULL)
		{
			t->Release();
			t = NULL;
		}
	}

	template <class T>
	void SafeSubstitute(T& target, T& value)
	{
		SafeAddRef(value);
		SafeRelease(target);
		target = value;
	}

	template <typename T>
	inline void SafeDelete(T*& p)
	{
		if (p != NULL)
		{
			delete (p);
			(p) = NULL;
		}
	}

	template <typename T>
	inline void SafeDeleteArray(T*& p)
	{
		if (p != NULL)
		{
			delete[](p);
			(p) = NULL;
		}
	}

	/**
	@brief	�ő�l�擾
	*/
	template <typename T, typename U>
	T Max(T t, U u)
	{
		if (t > (T) u)
		{
			return t;
		}
		return u;
	}

	/**
	@brief	�ŏ��l�擾
	*/
	template <typename T, typename U>
	T Min(T t, U u)
	{
		if (t < (T) u)
		{
			return t;
		}
		return u;
	}

	/**
	@brief	�͈͓��l�擾
	*/
	template <typename T, typename U, typename V>
	T Clamp(T t, U max_, V min_)
	{
		if (t > (T) max_)
		{
			t = (T) max_;
		}

		if (t < (T) min_)
		{
			t = (T) min_;
		}

		return t;
	}

#ifdef _WIN32
	inline void Sleep(int32_t ms)
	{
		::Sleep(ms);
	}
#else
	inline void Sleep(int32_t ms)
	{
		usleep(1000 * ms);
	}
#endif
}