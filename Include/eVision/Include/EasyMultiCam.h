// EasyMultiCam.h: EasyMutltiCam library header file for eVision 6.7.1.0
//
// Copyright ( c) 1997-2006, Euresys. All rights reserved.
//

#if !defined(__EASYMULTICAM_H__)
#define __EASYMULTICAM_H__

#ifdef __GNUC__
#define EMC_API
#else
#if defined E_STATIC
#define EMC_API
#elif defined E_DLL_EXPORT
#define EMC_API __declspec(dllexport)
#else
#define EMC_API __declspec(dllimport)
#endif
#endif

#include "../Include/EuresysException.h"
#include "../Include/MCpp.h"
#include "../Include/Easy.h"
#include "../Include/EColor.h"


// ****************************************************************************************************
// Euresys namespace
// -----------------
namespace Euresys
{
	// ************************************************************************************************
	// Euresys.eVision namespace
	// -------------------------

	namespace eVision
	{
		// ********************************************************************************************
		// Euresys.eVision.EasyMultiCam namespace
		// --------------------------------------

		namespace EasyMultiCam
		{
			// EImage config update
			EMC_API void UpdateImageConfig(const Euresys::MultiCam::Surface &s, EImageBW8 &img);
			EMC_API void UpdateImageConfig(const Euresys::MultiCam::Surface &s, EImageBW16 &img);
			EMC_API void UpdateImageConfig(const Euresys::MultiCam::Surface &s, EImageC24 &img);
			EMC_API void UpdateImageConfig(const Euresys::MultiCam::Surface &s, EImageC24A &img);
			EMC_API void UpdateImageConfig(const Euresys::MultiCam::Surface &s, EImageC15 &img);
			EMC_API void UpdateImageConfig(const Euresys::MultiCam::Surface &s, EImageC16 &img);

			// EImage creation
			EMC_API EImageBW8 *CreateImageBW8(const Euresys::MultiCam::Surface &s);
			EMC_API EImageBW16 *CreateImageBW16(const Euresys::MultiCam::Surface &s);
			EMC_API EImageC24 *CreateImageC24(const Euresys::MultiCam::Surface &s);
			EMC_API EImageC24A *CreateImageC24A(const Euresys::MultiCam::Surface &s);
			EMC_API EImageC15 *CreateImageC15(const Euresys::MultiCam::Surface &s);
			EMC_API EImageC16 *CreateImageC16(const Euresys::MultiCam::Surface &s);

			// Surface config update
			void UpdateSurfaceConfig(const EImageBW8 &img, Euresys::MultiCam::Surface &s);
			void UpdateSurfaceConfig(const EImageBW16 &img, Euresys::MultiCam::Surface &s);
			void UpdateSurfaceConfig(const EImageC24 &img, Euresys::MultiCam::Surface &s);
			void UpdateSurfaceConfig(const EImageC24A &img, Euresys::MultiCam::Surface &s);
			void UpdateSurfaceConfig(const EImageC15 &img, Euresys::MultiCam::Surface &s);
			void UpdateSurfaceConfig(const EImageC16 &img, Euresys::MultiCam::Surface &s);

			// Surface creation
			EMC_API Euresys::MultiCam::Surface *CreateSurface(const EImageBW8 &img);
			EMC_API Euresys::MultiCam::Surface *CreateSurface(const EImageBW16 &img);
			EMC_API Euresys::MultiCam::Surface *CreateSurface(const EImageC24 &img);
			EMC_API Euresys::MultiCam::Surface *CreateSurface(const EImageC24A &img);
			EMC_API Euresys::MultiCam::Surface *CreateSurface(const EImageC15 &img);
			EMC_API Euresys::MultiCam::Surface *CreateSurface(const EImageC16 &img);

			// Surface creation
			EMC_API Euresys::MultiCam::Surface *CreateSurface(const EBW8Vector &vec);
			EMC_API Euresys::MultiCam::Surface *CreateSurface(const EBW16Vector &vec);
			EMC_API Euresys::MultiCam::Surface *CreateSurface(const EBW32Vector &vec);
			EMC_API Euresys::MultiCam::Surface *CreateSurface(const EC24Vector &vec);
			EMC_API Euresys::MultiCam::Surface *CreateSurface(const EColorVector &vec);

			// EJpegHandler - Surface interface
			EMC_API void SetSurfaceForJpegHandler(const Euresys::MultiCam::Surface &s, EJpegHandler &JpegHandler);

			// ********************************************************************************************
			// Exceptions
			// ----------
			struct Exception : public Euresys::Exception
			{
			private:
				char *McDescription;

			public:
				Exception(INT32 error, const char *desc);
				Exception(Exception &e);
				Exception& operator=(Exception& other);
				~Exception();

				INT32 Error;
				EMC_API const char *What();
			};
		}
	}
}


#endif // !defined(__EASYMULTICAM_H__)
