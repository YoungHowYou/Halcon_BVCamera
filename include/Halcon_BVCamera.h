#pragma once
#ifndef __APPLE__
#  include "Halcon.h"
#else
#  ifndef HC_LARGE_IMAGES
#    include <HALCON/Halcon.h>
#  else
#    include <HALCONxl/Halcon.h>
#  endif
#endif
#define Test_EXPORTS_API __declspec(dllexport)
#ifdef __cplusplus
extern "C" {
#endif
	extern Test_EXPORTS_API Herror HBVCamOpen(Hproc_handle proc_handle);
	extern Test_EXPORTS_API Herror HBVCamStartGrab(Hproc_handle proc_handle);
	extern Test_EXPORTS_API Herror HBVCamStopGrab(Hproc_handle proc_handle);
	extern Test_EXPORTS_API Herror HBVCamGrabImage(Hproc_handle proc_handle);
	extern Test_EXPORTS_API Herror HBVCAM_FeatureCommand(Hproc_handle proc_handle);
	extern Test_EXPORTS_API Herror HBVCAM_SetFeatureFloat(Hproc_handle proc_handle);
	extern Test_EXPORTS_API Herror HBVCAM_SetFeatureInteger(Hproc_handle proc_handle);
	extern Test_EXPORTS_API Herror HBVCamOpenByUID(Hproc_handle proc_handle);

#ifdef __cplusplus
}
#endif 
