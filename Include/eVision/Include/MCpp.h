// MCPP.H - MULTICAM C++ API

#if !defined(__MCPP_H__)
#define __MCPP_H__

#ifdef __GNUC__
#define MCPP_API
#else
#if defined E_STATIC
#define MCPP_API
#elif defined MCPP_LICENSEMEDIATOR
#define MCPP_API
#elif defined E_DLL_EXPORT
#define MCPP_API __declspec(dllexport)
#else
#define MCPP_API __declspec(dllimport)
#endif
#endif

#ifndef __MCPP_ONLY
#include "Easy.h"
#endif // __MCPP_ONLY
#include "EuresysException.h"
#include "multicam.h"


// For wrapping
#ifdef __GNUC__
typedef void (*FinalizeCallback)(int handle);
#else
typedef void (__stdcall *FinalizeCallback)(int handle);
#endif


namespace Euresys
{
	namespace MultiCam
	{
		// ********************************************************************************************
		// MultiCamObject: base class for Configuration, Board, Surface and Channel classes
		// --------------------------------------------------------------------------------

		class Surface;
		class MultiCamObject
		{
		protected:
			MCHANDLE Handle;
			virtual Surface *GetSurface(MCHANDLE handle);
		public:
			MultiCamObject();

		public:
			MCPP_API void SetParam(MCPARAMID param, int value);
			MCPP_API void SetParam(MCPARAMID param, unsigned int value);
			MCPP_API void SetParam(MCPARAMID param, const char *value);
			MCPP_API void SetParam(MCPARAMID param, double value);
			MCPP_API void SetParam(MCPARAMID param, Surface &value);
			MCPP_API void SetParam(const char *param, int value);
			MCPP_API void SetParam(const char *param, unsigned int value);
			MCPP_API void SetParam(const char *param, const char *value);
			MCPP_API void SetParam(const char *param, double value);
			MCPP_API void SetParam(const char *param, Surface &value);

			MCPP_API void GetParam(MCPARAMID param, int &value);
			MCPP_API void GetParam(MCPARAMID param, unsigned int &value);
			MCPP_API void GetParam(MCPARAMID param, char *value, int maxLength);
			MCPP_API void GetParam(MCPARAMID param, double &value);
			MCPP_API void GetParam(MCPARAMID param, Surface *&value);
			MCPP_API void GetParam(const char *param, int &value);
			MCPP_API void GetParam(const char *param, unsigned int &value);
			MCPP_API void GetParam(const char *param, char *value, int maxLength);
			MCPP_API void GetParam(const char *param, double &value);
			MCPP_API void GetParam(const char *param, Surface *&value);
      
			MCPP_API void GetParamInfo(MCPARAMID param, void* pInfo);

			MCHANDLE GetHandle();
		};


		// ********************************************************************************************
		// Configuration class
		// -------------------

		class Configuration : public MultiCamObject
		{
			// Wrapping members
		public:
			int handle_;
			FinalizeCallback callback_;

		public:
			Configuration();
			~Configuration();
		};


		// ********************************************************************************************
		// Board class
		// -----------

		class Board : public MultiCamObject
		{
			// Wrapping members
		public:
			int handle_;
			FinalizeCallback callback_;

		public:
			Board(int index);
			~Board();
		};


		// ********************************************************************************************
		// BoardList class
		// ---------------

		class BoardList
		{
			// Wrapping members
		public:
			int handle_;
			FinalizeCallback callback_;

		private:
			Board **List;
			int Count;
		public:
			BoardList();
			~BoardList();
			void Init();

		public:
			inline Board *operator[] (int driverIndex) { return GetBoardByDriverIndex(driverIndex); }
			MCPP_API Board *GetBoardByDriverIndex(int driverIndex);
			MCPP_API Board *GetBoardByPciPosition(int pciPosition);
			MCPP_API Board *GetBoardByBoardName(const char *boardName);
			MCPP_API Board *GetBoardByBoardIdentifier(const char *boardIdentifier);
			MCPP_API int GetCount();
		};

    namespace Internal
    {
		// ********************************************************************************************
      // List: simple list class
      // -----------------------

      template <class T, int N> class List
		{
		protected:
        int count, allocCount;
        T *list;

		public:
        List();
        ~List();

        T operator[] (int Index) const { return list[Index]; }
        int GetCount() const { return count; }
        int Add(T &item);
		};

		template <class T, int N>
      List<T, N>::List()
		{
        count = 0;
        allocCount = 0;
        list = NULL;
		}

		template <class T, int N>
      List<T, N>::~List()
		{
        if (list != NULL)
          free(list);
		}

		template <class T, int N>
      int List<T, N>::Add(T &item)
		{
        int element = count++;

        if (count >= allocCount)
			{
          allocCount += N;
          list = (T *)realloc(list, sizeof(T) * allocCount);
			}

        list[element] = item;

			return element;
		}
    }

		// ********************************************************************************************
		// Channel class
		// -------------

		struct Exception;
		class SignalInfo;
		class Callback;
		template <class T> class UserCallback;

#ifdef __MCPP_ONLY
    class Channel : public MultiCamObject
#else
    class Channel : public MultiCamObject, public Euresys::IListener
#endif // __MCPP_ONLY
		{
			// Wrapping members
		public:
			int handle_;
			FinalizeCallback callback_;

		private:
			void GetSignalInfo(PMCSIGNALINFO mcInfo, SignalInfo *Info);
			virtual Surface *GetSurface(MCHANDLE Handle);
      Internal::List<Surface *, 16> SurfaceList;
			int EventMax;
			Callback **Callbacks;
			bool CbReg;
			MCPP_API void RegisterCallback(Callback *cb, MCSIGNAL Signal);
		public:
			void CbRoutine(PMCSIGNALINFO mcInfo);

		public:
			MCPP_API Channel(Board *board, int connector);
			MCPP_API Channel(Board *board, const char *connector);
			MCPP_API ~Channel();
            inline operator MCHANDLE() { return Handle; }

			MCPP_API void SetActive();
			MCPP_API void SetIdle();
			MCPP_API void Prepare();

			inline void WaitSignal(MCSIGNAL signal, unsigned int timeout, SignalInfo &info) { WaitForSignal(signal, timeout, info); }
			MCPP_API void WaitForSignal(MCSIGNAL signal, unsigned int timeout, SignalInfo &info);
			MCPP_API void GetSignalInfo(MCSIGNAL signal, SignalInfo &info);

			Surface *GetSurfaceByIndex(unsigned int index)
			{
				Surface *surf;
				GetParam(MC_Cluster + index, surf);
				return surf;
			}

			template <class T>
			void RegisterCallback(T *owner, void (T::*callbackMethod)(Channel &, SignalInfo &), MCSIGNAL signal)
			{
				if (owner == NULL || callbackMethod == NULL)
				{
					Euresys::MultiCam::Exception e(MC_INTERNAL_ERROR, "Invalid callback object or function");
					throw e;
				}


				Callback *cb = new UserCallback<T>(owner, callbackMethod);
				RegisterCallback(cb, signal);
			}
			MCPP_API void UnregisterCallback(MCSIGNAL signal);
			MCPP_API void RegisterCallback(void *, void *, int);

#ifndef __MCPP_ONLY
      // Implementation of IListener interface.
      MCPP_API void Listen(IBroadcaster* sender);
      // The vector containing the subscribed ROIs for the camera.
      Euresys::GenericRoiExtentBroadcastingVector CameraRois;
#endif // __MCPP_ONLY
		};


		// ********************************************************************************************
		// Surface class
		// -------------

		class Surface : public MultiCamObject
		{
			// Wrapping members
		public:
			int handle_;
			FinalizeCallback callback_;

		private:
			bool UserSurface;
		public:
			Surface(MCHANDLE aHandle);

		public:
			MCPP_API Surface();
			MCPP_API ~Surface();
			inline operator MCHANDLE() { return Handle; }

			MCPP_API void Reserve();
			MCPP_API void Free();
		};


		// ********************************************************************************************
		// SignalInfo class
		// ----------------

		class SignalInfo
		{
			// Wrapping members
		public:
			int handle_;
			FinalizeCallback callback_;
			SignalInfo() 
			{
				handle_ = 0;
				callback_ = 0;
			};
			~SignalInfo()
			{
				if ((handle_ != 0) && (callback_ != NULL))
					callback_(handle_);
			}

		public:
			MCSIGNAL Signal;
			Surface *Surf;
		};


		// ********************************************************************************************
		// Callback class
		// --------------

		class Callback
		{
		public:
			MCPP_API virtual ~Callback() = 0;
			virtual void Run(Channel &channel, SignalInfo &info) = 0;
		};

		template <class T> class UserCallback : public Callback
		{
		private:
			T *Object;
			void (T::*Function)(Channel &channel, SignalInfo &info);

		public:
			UserCallback(T *obj, void (T::*f)(Channel &channel, SignalInfo &info)) :
			  Object(obj),
			  Function(f)
			{
			}
			~UserCallback()
			{
			}

			void Run(Channel &channel, SignalInfo &info)
			{
				(Object->*Function)(channel, info);
			}
		};


		// ********************************************************************************************
		// Global objects
		// --------------

		// Configuration
		extern MCPP_API Configuration Config;

		// List of boards
		extern MCPP_API BoardList Boards;

		// ********************************************************************************************
		// Exceptions
		// ----------
		struct Exception : public Euresys::Exception
		{
		private:
			  char *McDescription;

		public:
			  MCPP_API Exception(int error, const char *desc);
			  MCPP_API Exception(Exception &e);
			  MCPP_API Exception& operator=(Exception &e);
			  MCPP_API ~Exception();

			  int Error;
			  MCPP_API const char *What();
			  MCPP_API MCSTATUS GetMcStatus() { return Error; }
		};
	}
}

#endif // !defined( __MCPP_H__)
