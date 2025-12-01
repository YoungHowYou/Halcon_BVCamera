// Halcon_BVCamera.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
// #include <SDKDDKVer.h>
#define WIN32_LEAN_AND_MEAN // Exclude rarely-used stuff from Windows headers
#include <windows.h>
#include "HalconCpp.h"
#include "HDevThread.h"
#include "BVCamAPI.h"

#include "Halcon_BVCamera.h"
// HCAMERA hCamera[32];
// HFEATURE hFeature[32];

using namespace HalconCpp;
#define H_BVCamera_TAG 0xC0FFEE60
#define H_BVCamera_SEM_TYPE "BVCamera"
extern "C"
{
	typedef struct
	{
		HCAMERA BV相机句柄;
		HFEATURE BV相机参数句柄;

	} HUserHandleData;

	static Herror HUserHandleDestructor(Hproc_handle ph, HUserHandleData *data)
	{
		if (data->BV相机句柄)
		{

			data->BV相机句柄 = NULL;
		}
		else
		{
		}
		return HFree(ph, data);
	}
	// 句柄类型描述符
	const HHandleInfo HandleTypeUser = HANDLE_INFO_INITIALIZER_NOSER(H_BVCamera_TAG, H_BVCamera_SEM_TYPE, HUserHandleDestructor, NULL, NULL);
}

struct MyContext
{
	int 分时频闪数;
	char 相机用户名[64];
	HTuple 相机采集队列; // 直接放对象

	MyContext(int flash, const char *name, const HTuple &queue)
		: 分时频闪数(flash), 相机采集队列(queue)
	{
		strcpy_s(相机用户名, name);
	}
};

#define Max_Buffer 5

VOID CALLBACK ImageDataRcv(HCAMERA hCamera, BVCAM_IMAGE *pImage, pBVCAM_IMAGEDATAINFO pImageInfo, PVOID Context)
{
	MyContext *ctx = static_cast<MyContext *>(Context);
	HObject ho_Image;
	HTuple hv_MessageHandle;
	// MyContext *ctx = (MyContext *)用户自定义数据容器;
	// MyContext *ctx = static_cast<MyContext *>(用户自定义数据容器);
	// int *用户自定义数据 = reinterpret_cast<int *>(用户自定义数据容器);
	if (	pImage->PixelFormatID == 17301505)
	{
		GenImage1(&ho_Image, "byte", (long)(pImage->Width) * (ctx->分时频闪数),  (long)(pImage->Height) / (ctx->分时频闪数), (__int64)pImage->pBuffer);
	}
	else
	{
		GenImage1(&ho_Image, "uint2",  (long)(pImage->Width) * (ctx->分时频闪数),  (long)(pImage->Height) / (ctx->分时频闪数), (__int64)pImage->pBuffer);
	}
	CreateMessage(&hv_MessageHandle);
	SetMessageObj(ho_Image, hv_MessageHandle, "image");
	//SetMessageTuple(hv_MessageHandle, "nFrameNum", pImage->EndianMode);
	// SetMessageTuple(hv_MessageHandle, "nFrameCounter", (__int64)(帧信息->nFrameCounter));
	// SetMessageTuple(hv_MessageHandle, "nTriggerIndex", (__int64)(帧信息->nTriggerIndex));
	// SetMessageTuple(hv_MessageHandle, "nFirstLineEncoderCount", (__int64)(帧信息->nFirstLineEncoderCount));
	// SetMessageTuple(hv_MessageHandle, "nLastLineEncoderCount", (__int64)(帧信息->nLastLineEncoderCount));
	// SetMessageTuple(hv_MessageHandle, "nHostTimeStamp", (__int64)(帧信息->nHostTimeStamp));
	// SetMessageTuple(hv_MessageHandle, "fGain", (DOUBLE)(帧信息->fGain));
	// SetMessageTuple(hv_MessageHandle, "fExposureTime", (DOUBLE)(帧信息->fExposureTime));

	SetMessageTuple(hv_MessageHandle, "nDeviceID", ctx->相机用户名);

	EnqueueMessage((ctx->相机采集队列), hv_MessageHandle, HTuple(), HTuple());
	ClearMessage(hv_MessageHandle);
}

Herror HBVCamOpenByUID(Hproc_handle proc_handle)
{
	Hcpar nDeviceIndex, 相机用户名, 分时频闪数;
	Hcpar *相机采集队列容器;
	INT4_8 参数个数; // 参数个数

	HAllocStringMem(proc_handle, 32);
	HGetSPar(proc_handle, 1, STRING_PAR, &相机用户名, 1);
	HGetSPar(proc_handle, 2, LONG_PAR, &分时频闪数, 1);
	HGetPPar(proc_handle, 3, &相机采集队列容器, &参数个数);
	HTuple 相机采集队列(相机采集队列容器, 1);

	// list acquired

	BVCAM_SetStructVersion(BVCAM_LIBRARY_STRUCT_VERSION);
	BVCAM_LIST *pList;
	DWORD Count;
	Count = 0;
	BVCAM_GetList((pBVCAM_LIST)&Count);
	pList = (pBVCAM_LIST) new BYTE[sizeof(DWORD) + sizeof(pList->Info[0]) * Count];
	pList->Count = Count;
	BVCAM_GetList(pList);

	INT UserIndex = 0;
	for (int i = 0; i < pList->Count; ++i)
	{
		if (strcmp(pList->Info[i].u.GigEDev.UserName, 相机用户名.par.s) == 0)
		{
			// std::cout << "Found UID 'AA' at index: " << i << std::endl;
			UserIndex = i;
		}
	}
	HCAMERA hCamera;
	HFEATURE hFeature;
	BVCAM_OPENPARAM OpenParam = {};
	OpenParam.UID = pList->Info[UserIndex].UID;

	if (!BVCAM_Open(&OpenParam, &hCamera))
	{
		return 10000 * H__LINE__;
	}
	if (!BVCAM_ResourceAlloc(hCamera))
	{
		return 10000 * H__LINE__;
	}
	if (!BVCAM_GetFeatureHandle(hCamera, &hFeature))
	{
		return 10000 * H__LINE__;
	}
	MyContext *ctx = new MyContext(分时频闪数.par.l, 相机用户名.par.s, 相机采集队列);

	if (!BVCAM_SetImageCallBack(hCamera, ctx, ImageDataRcv, Max_Buffer, FALSE))
	{
		return 10000 * H__LINE__;
	}

	HUserHandleData **handle_data;
	// 分配输出句柄
	HCkP(HAllocOutputHandle(proc_handle, 1, &handle_data, &HandleTypeUser));
	// 分配并初始化用户数据
	HCkP(HAlloc(proc_handle, sizeof(HUserHandleData), (void **)handle_data));
	(*handle_data)->BV相机句柄 = hCamera;
	(*handle_data)->BV相机参数句柄 = hFeature;
	return H_MSG_TRUE;
}

Herror HBVCamStartGrab(Hproc_handle proc_handle)
{
	HUserHandleData *handle_data;
	HGetCElemH1(proc_handle, 1, &HandleTypeUser, &handle_data);

	if (!BVCAM_ImageStart(handle_data->BV相机句柄))
	{
		return 10000 * H__LINE__;
	}

	return H_MSG_TRUE;
}

Herror HBVCamStopGrab(Hproc_handle proc_handle)
{
	HUserHandleData *handle_data;
	HGetCElemH1(proc_handle, 1, &HandleTypeUser, &handle_data);
	if (!BVCAM_ImageStop(handle_data->BV相机句柄))
	{
		return 10000 * H__LINE__;
	}
	return H_MSG_TRUE;
}

Herror HBVCAM_FeatureCommand(Hproc_handle proc_handle)
{
	Hcpar FeatureName;
	HUserHandleData *handle_data;
	HAllocStringMem(proc_handle, 32);
	HGetCElemH1(proc_handle, 1, &HandleTypeUser, &handle_data);
	HGetSPar(proc_handle, 2, STRING_PAR, &FeatureName, 1);
	BOOL opes = FALSE;
	opes = BVCAM_FeatureCommand(handle_data->BV相机参数句柄, FeatureName.par.s);
	if (opes == FALSE)
	{
		return 10000 * H__LINE__;
	}

	return H_MSG_TRUE;
}

Herror HBVCAM_SetFeatureFloat(Hproc_handle proc_handle)
{
	Hcpar FeatureName, Value;
	HAllocStringMem(proc_handle, 32);
	HUserHandleData *handle_data;
	HGetCElemH1(proc_handle, 1, &HandleTypeUser, &handle_data);
	HGetSPar(proc_handle, 2, STRING_PAR, &FeatureName, 1);
	HGetSPar(proc_handle, 3, DOUBLE_PAR, &Value, 1);
	BOOL opes = FALSE;
	opes = BVCAM_SetFeatureFloat(handle_data->BV相机参数句柄, FeatureName.par.s, Value.par.d);
	if (opes == FALSE)
	{
		return 10000 * H__LINE__;
	}

	return H_MSG_TRUE;
}
// BOOL	Dllport BVCAM_SetFeatureInteger(HFEATURE hFeature, char* FeatureName, INT64 Value);
Herror HBVCAM_SetFeatureInteger(Hproc_handle proc_handle)
{
	Hcpar FeatureName, Value;
	//"TriggerSoftware"
	HAllocStringMem(proc_handle, 32);
	HUserHandleData *handle_data;
	HGetCElemH1(proc_handle, 1, &HandleTypeUser, &handle_data);
	HGetSPar(proc_handle, 2, STRING_PAR, &FeatureName, 1);
	HGetSPar(proc_handle, 3, LONG_PAR, &Value, 1);
	BOOL opes = FALSE;
	opes = BVCAM_SetFeatureInteger(handle_data->BV相机参数句柄, FeatureName.par.s, Value.par.l);
	if (opes == FALSE)
	{
		return 10000 * H__LINE__;
	}

	return H_MSG_TRUE;
}
