// BVCam version 3.03.00 API Header File
// Copyright (C) 2020-2020 BlueVision Ltd., Japan
#pragma once


#pragma pack( push, 4 )

#ifdef __cplusplus
extern "C" {
#endif

#define BVCAM_LIBRARY_STRUCT_VERSION 30300

#undef	Dllport
#ifdef	_BV_CREATEDLL_
#define	Dllport	__declspec( dllexport ) __cdecl
#else
#define	Dllport	__declspec( dllimport ) __cdecl
#pragma comment( lib, "BVCam" )
#endif

#define	HCAMERA				PVOID
#define	HCTBL				PVOID
#define HNodeMap			PVOID
#define	HFEATURE			PVOID


typedef	enum BVCAM_GIGESTREAMTYPE
{
	BVCAM_GIGEIMAGEDATA		= 1,
	BVCAM_GIGERAWDATA,
	BVCAM_GIGEFILEDATA,
	BVCAM_GIGECHUNKDATA,
	BVCAM_GIGEEXTCHUNKDATA,
	BVCAM_GIGEV2EXTCHUNKDATA = 0x4000,
	BVCAM_GIGEVENDORDATA	= 0x8000,
} BVCAM_GIGESTREAMTYPE;


typedef	enum BVCAM_USBSTREAMTYPE
{
	BVCAM_USBIMAGEDATA		= 1,
	BVCAM_USBCHUNKDATA		= 0x4000,
	BVCAM_USBEXTCHUNKDATA,
} BVCAM_USBSTREAMTYPE;


typedef enum BVCAM_TRANSMITSPEED
{
	BVCAM_S100M				= 0,			//	100M
	BVCAM_S1000M,							//	1G
	BVCAM_SUSB2				= 100,			//	USB 2.0
	BVCAM_SUSB3,							//	USB 3.0
} BVCAM_TRANSMITSPEED;


typedef enum BVCAM_SHIFTID
{
											//	15 14 13 12 ..... 2 1 0
											//
	BVCAM_SFT0				= 0,			//	7-0 bit
	BVCAM_SFT1,								//	8-1 bit
	BVCAM_SFT2,								//	9-2 bit
	BVCAM_SFT3,								//	10-3 bit
	BVCAM_SFT4,								//	11-4 bit
	BVCAM_SFT5,								//	12-5 bit
	BVCAM_SFT6,								//	13-6 bit
	BVCAM_SFT7,								//	14-7 bit
	BVCAM_SFT8,								//	15-8 bit
	BVCAM_SFTAUTO			= -1
} BVCAM_SHIFTID;


typedef enum BVCAM_DIBMODE
{
	BVCAM_DIB32				= 0,			//
	BVCAM_DIB24,							//
} BVCAM_DIBMODE;


typedef enum BVCAM_STOREMODE
{
	BVCAM_MEMmode			= 0,			//	MEMORY mode
	BVCAM_MEMmodeLR,						//	MEMORY mode (Flip horizontal)
	BVCAM_BMPmode,							//	BMP file mode
	BVCAM_BMPmodeLR,						//	BMP file mode (Flip horizontal)
} BVCAM_STOREMODE;


typedef	enum BVCAM_ENDIAN
{
	BVCAM_BIGENDIAN			= 0,			//	Big Endian
	BVCAM_LITTLEENDIAN						//	Little Endian
} BVCAM_ENDIAN;


typedef	enum BVCAM_DEVICETYPE
{
	BVCAM_UNKNOWNDEV		= -1,
	BVCAM_ANYDEV			= 0,
	BVCAM_GIGECAMERA,
	BVCAM_USBCAMERA,
} BVCAM_DEVICETYPE;


typedef enum BVCAM_OPENMODE
{
	BVCAM_AUTO_ACCESS		= 0,
	BVCAM_READONLY_ACCESS,
	BVCAM_CONTROL_ACCESS,
	BVCAM_EXCLUSIVE_ACCESS,
} BVCAM_OPENMODE;


typedef enum BVCAM_FEATURETYPE
{
	BVCAM_INTEGERTYPE		= 0,
	BVCAM_BOOLEANTYPE,
	BVCAM_FLOATTYPE,
	BVCAM_STRINGTYPE,
	BVCAM_COMMANDTYPE,
	BVCAM_ENUMERATIONTYPE,
	BVCAM_CATEGORYTYPE,
	BVCAM_REGISTERTYPE
} BVCAM_FEATURETYPE;


typedef enum BVCAM_VISIBILITYTYPE
{
	BVCAM_BEGINNER = 0,
	BVCAM_EXPERT,
	BVCAM_GURU,
	BVCAM_INVISIBLE,
	BVCAM_UNDEFVISIBILITY = 99
} BVCAM_VISIBILITYTYPE;


//ステータスコード
typedef enum STATUS_SYSTEMCODE
{
	STATUSBVCAM_POWERUP		= 1,			//	Return from sleep of system
	STATUSBVCAM_DEVICECHANGE,				//	A numerical change in a device is detected
} STATUS_SYSTEMCODE;


typedef enum STATUS_IMAGE
{
	STATUSIMAGE_COMPLETE	= 0,			//	Success Return
	STATUSIMAGE_REQUEST_PENDING,			//	requested is pending completion
	STATUSIMAGE_REQUEST_ERROR,				//	requested is Failure
	STATUSIMAGE_REQUEST_RESTART,			//	requested is Failure
} STATUS_IMAGE;


#pragma warning( push )
#pragma warning( disable : 4200 )


typedef struct BVCAM_GIGEDEVINFO
{
	WORD					Spec_Major;
	WORD					Spec_Minor;
	DWORD					Dev_Mode;
	DWORD					IPConfig;
	DWORD					IPConfigOption;
	BYTE					MACAddr[ 6 ];
	BYTE					IPAddr[ 4 ];
	BYTE					SubMask[ 4 ];
	BYTE					GateWay[ 4 ];
	char					VendorName[ 32 ];
	char					Rsvd;
	char					ModelName[ 32 ];
	char					Rsvd1;
	char					Dev_Ver[ 32 ];
	char					Rsvd2;
	char					Vendor_Info[ 48 ];
	char					Rsvd3;
	char					SerialNumber[ 16 ];
	char					Rsvd4;
	char					UserName[ 16 ];
	DWORD					Rsvd5;
} BVCAM_GIGEDEVINFO, *pBVCAM_GIGEDEVINFO;


typedef struct BVCAM_USBDEVINFO
{
	UINT64					Dev_Capability;
	DWORD					GenCP_Version;
	char					VendorName[ 64 ];
	char					Rsvd;
	char					ModelName[ 64 ];
	char					Rsvd1;
	char					FamilyName[ 64 ];
	char					Rsvd2;
	char					Dev_Version[ 64 ];
	char					Rsvd3;
	char					Vendor_Info[ 64 ];
	char					Rsvd4;
	char					SerialNumber[ 64 ];
	char					Rsvd5;
	char					UserName[ 64 ];
	DWORD					Rsvd6;
} BVCAM_USBDEVINFO, *pBVCAM_USBDEVINFO;


//	BVCAM_CameraInfo
typedef struct BVCAM_DEVINFO
{
	UINT64					UID;
	DWORD					BusNumber;
	BVCAM_DEVICETYPE		DeviceType;
	BVCAM_TRANSMITSPEED		Speed;
	union U
	{
		BVCAM_GIGEDEVINFO		GigEDev;
		BVCAM_USBDEVINFO		UsbDev;
	} u;
} BVCAM_DEVINFO, *pBVCAM_DEVINFO;


//	BVCAM_GetList
typedef struct BVCAM_LIST
{
	DWORD					Count;				//	Number of connected cameras or numbers of Info arrays
	BVCAM_DEVINFO			Info[ 1 ];
} BVCAM_LIST, *pBVCAM_LIST;


//	BVCAM_Open
typedef struct BVCAM_OPENPARAM
{
	BVCAM_DEVICETYPE		DeviceType;
	UINT64					UID;				// Not Zero is AccMode Used
	BYTE					IPAddr[ 4 ];
	char					UserName[ 64 ];
	ULONG					Rsvd;
	BVCAM_OPENMODE			AccMode;
	BOOL					XML_DiskFlag;
} BVCAM_OPENPARAM, *pBVCAM_OPENPARAM;


typedef struct BVCAM_IMAGE
{
	DWORD					Width;
	DWORD					Height;
	BYTE					*pBuffer;
	DWORD					Length;
	DWORD					PixelFormatID;
	BVCAM_ENDIAN			EndianMode;
	STATUS_IMAGE			Status;
} BVCAM_IMAGE, *pBVCAM_IMAGE;


//	BVCAM_StreamComplete
typedef	struct BVCAM_GIGESTREAMINFO
{
	DWORD					Stream_Type;
	UINT64					Fream_ID;
	UINT64					TimeStamp;

	union U
	{
		struct IMAGE
		{
			DWORD				Pixel_Type;
			DWORD				Width;
			DWORD				Height;
			DWORD				Offset_X;
			DWORD				Offset_Y;
			WORD				Padding_X;
			WORD				Padding_Y;
			DWORD				Size_Y;
		} Image;

		struct RAW
		{
			UINT64				DataSize;
		} Raw;

		struct FILE
		{
			UINT64				DataSize;
			BYTE				FileName[ 512 ];
		} File;

		struct CHUNK
		{
			DWORD				DataSize;
		} Chunk;

		struct EXT_CHUNK
		{
			DWORD				Pixel_Type;
			DWORD				Width;
			DWORD				Height;
			DWORD				Offset_X;
			DWORD				Offset_Y;
			WORD				Padding_X;
			WORD				Padding_Y;
			DWORD				DataSize;
			DWORD				Size_Y;
			DWORD				Chunk_ID;
		} Ext_Chunk;

		struct VENDOR
		{
			BYTE				VendorData[ 512 ];
		} Vendor;
	} u;
} BVCAM_GIGESTREAMINFO, *pBVCAM_GIGESTREAMINFO;


//	BVCAM_StreamComplete
typedef	struct BVCAM_USBSTREAMINFO
{
	DWORD					Stream_Type;
	UINT64					Fream_ID;
	UINT64					TimeStamp;
	UINT64					DataSize;

	union U
	{
		struct IMAGE
		{
			DWORD				Pixel_Type;
			DWORD				Width;
			DWORD				Height;
			DWORD				Offset_X;
			DWORD				Offset_Y;
			WORD				Padding_X;
			WORD				Padding_Y;
			DWORD				Size_Y;
		} Image;

		struct CHUNK
		{
			DWORD				Chunk_ID;
		} Chunk;

		struct EXT_CHUNK
		{
			DWORD				Pixel_Type;
			DWORD				Width;
			DWORD				Height;
			DWORD				Offset_X;
			DWORD				Offset_Y;
			WORD				Padding_X;
			WORD				Padding_Y;
			DWORD				Size_Y;
			DWORD				Chunk_ID;
		} Ext_Chunk;
	} u;
} BVCAM_USBSTREAMINFO, *pBVCAM_USBSTREAMINFO;


typedef	struct BVCAM_IMAGEDATAINFO
{
	BVCAM_DEVICETYPE		DeviceType;
	union U
	{
		struct CGIGE
		{
			BOOL					Payload_Flag;
			BVCAM_GIGESTREAMINFO	StreamInfo;
		} CGigE;

		struct CUSB
		{
			BOOL					Payload_Flag;
			BVCAM_USBSTREAMINFO		StreamInfo;
		} CUsb;

	} u;
} BVCAM_IMAGEDATAINFO, *pBVCAM_IMAGEDATAINFO;


//	BVCAM_GigEGetPktLog
typedef	struct BVCAM_PKTLOG
{
	UINT64					ToTalPktCount;
	UINT64					ErrorPktCount;
	UINT64					RSendCount;
} BVCAM_PKTLOG, *pBVCAM_PKTLOG;


typedef	struct BVCAM_COLORVALUE
{
	double					R_Value;
	double					G1_Value;
	double					G2_Value;
	double					B_Value;
} BVCAM_COLORVALUE, *pBVCAM_COLORVALUE;


typedef	struct BVCAM_COLORCONVMODE
{
	BVCAM_STOREMODE			StoreMode;
	BVCAM_SHIFTID			ShiftID;
	BVCAM_DIBMODE			DIBMode;
	DWORD					Parallel_Thread;
	BOOL					BayerRevision_G;
} BVCAM_COLORCONVMODE, *pBVCAM_COLORCONVMODE;


//	Event Info
typedef	struct BVCAM_EVENTINFO
{
	USHORT					EventID;
	union U
	{
		struct CGIGE
		{
			WORD					StreamIndex;
			UINT64					BlockID;
			UINT64					TimeStamp;
			DWORD					Length;
			BYTE					Data[ 4 ];
		} CGigE;

		struct CUSB
		{
			UINT64					TimeStamp;
			DWORD					Length;
			BYTE					Data[ 4 ];
		} CUsb;

	} u;
} BVCAM_EVENTINFO, *pBVCAM_EVENTINFO;


//	BVCAM_GetChunkInfoBuffer
//	BVCAM_GetChunkInfoImage
typedef struct BVCAM_CHUNKINFO
{
	DWORD					Count;
	struct INFO
	{
		DWORD					ChunkID;
		DWORD					Length;
		PVOID					pChunkData;
	} Info[1];
} BVCAM_CHUNKINFO, *pBVCAM_CHUNKINFO;


//	BVCAM_FeatureInfo
typedef	struct BVCAM_FEATUREINFO
{
	BVCAM_FEATURETYPE		FType;
	BVCAM_VISIBILITYTYPE	VType;
	UINT64					PollingTime;
	union U
	{
		struct INTREG
		{
			INT64				MinValue;
			INT64				MaxValue;
			INT64				IncValue;
		} IntReg;

		struct FLOATREG
		{
			double				MinValue;
			double				MaxValue;
			double				IncValue;
			BOOL				HasInc;
		} FloatReg;

		struct STRINGREG
		{
			UINT64				MaxLength;
		} StringReg;

		struct REG
		{
			INT64				Addr;
			UINT64				Length;
		} Reg;
	} u;
} BVCAM_FEATUREINFO, *pBVCAM_FEATUREINFO;


typedef	VOID(CALLBACK* SYSTEMFUNC)(STATUS_SYSTEMCODE Statsu, PVOID Context);
typedef	VOID(CALLBACK* IMAGEFUNC)(HCAMERA hCamera, BVCAM_IMAGE* Image, BVCAM_IMAGEDATAINFO* Info, PVOID Context);
typedef	VOID(CALLBACK* EVENTFUNC)(HCAMERA hCamera, BVCAM_EVENTINFO* EventInfo, PVOID Context);
typedef	VOID(CALLBACK* ACTIONACKFUNC)(UINT64 UID, PVOID Context);


//API------------------------------------------------------------------------------------------------------------
/*	C API Interface Functions	*/
VOID	Dllport BVCAM_SetCallBack(PVOID Context, SYSTEMFUNC SysTemFunc);
BOOL	Dllport BVCAM_SetStructVersion(DWORD Version);
VOID	Dllport BVCAM_GetErrorMsg(char* Buffer, DWORD Length);
BOOL	Dllport BVCAM_GetList(BVCAM_LIST* List);
BOOL	Dllport BVCAM_Open(BVCAM_OPENPARAM* OpenParam, HCAMERA* hCamera);
BOOL	Dllport BVCAM_Close(HCAMERA hCamera);
VOID	Dllport BVCAM_CloseAll(VOID);
BOOL	Dllport BVCAM_Camera(HCAMERA hCamera, BOOL* Connect);
BOOL	Dllport BVCAM_CameraInfo(HCAMERA hCamera, BVCAM_DEVINFO* CInfo);
BOOL	Dllport BVCAM_GetNodeMap(HCAMERA hCamera, HNodeMap* pNodeMap);
BOOL	Dllport BVCAM_GetFeatureHandle(HCAMERA hCamera, HFEATURE* hFeature);
BOOL	Dllport BVCAM_ResourceAlloc(HCAMERA hCamera);
BOOL	Dllport BVCAM_ResourceRelease(HCAMERA hCamera);
BOOL	Dllport BVCAM_SetConvMode(HCAMERA hCamera, BVCAM_COLORCONVMODE* Mode, BVCAM_COLORVALUE* ColorValue);
BOOL	Dllport BVCAM_GetBMPINFO(HCAMERA hCamera, BITMAPINFO* Info, DWORD* Lengeh, BOOL Priority_MONO);
BOOL	Dllport BVCAM_ConvExec(HCAMERA hCamera, BVCAM_IMAGE* Image, BYTE* OutBuf);
BOOL	Dllport BVCAM_GetChunkInfo(HCAMERA hCamera, BVCAM_IMAGE* Image, BVCAM_CHUNKINFO* Info);
BOOL	Dllport BVCAM_ImageStart(HCAMERA hCamera);
BOOL	Dllport BVCAM_ImageStop(HCAMERA hCamera);
BOOL	Dllport BVCAM_ImageAlloc(HCAMERA hCamera, BVCAM_IMAGE** Image);
BOOL	Dllport BVCAM_ImageFree(HCAMERA hCamera, BVCAM_IMAGE* Image);
BOOL	Dllport BVCAM_ImageFreeAll(HCAMERA hCamera);
BOOL	Dllport BVCAM_ImageReq(HCAMERA hCamera, BVCAM_IMAGE* Image);
BOOL	Dllport BVCAM_ImageComplete(HCAMERA hCamera, BVCAM_IMAGE* Image, DWORD TimeOut, BVCAM_IMAGEDATAINFO* Info);
BOOL	Dllport BVCAM_ImageReqAbortAll(HCAMERA hCamera);
BOOL	Dllport BVCAM_VSyncReq(HCAMERA hCamera, PVOID* Hd);
BOOL	Dllport BVCAM_VSyncComplete(HCAMERA hCamera, PVOID Hd, DWORD TimeOut);
BOOL	Dllport BVCAM_SetImageCallBack(HCAMERA hCamera, PVOID Context, IMAGEFUNC ImageFunc, DWORD BufferCount, BOOL InfoSet_Flag);
BOOL	Dllport BVCAM_SetEventCallBack(HCAMERA hCamera, PVOID Context, EVENTFUNC EventFunc);
BOOL	Dllport BVCAM_SetCmdTimeOut(HCAMERA hCamera, DWORD TimeOut);
DWORD	Dllport BVCAM_GetLibraryRevision(VOID);
VOID	Dllport BVCAM_ReDetection(VOID);


/************************************************/
/*	Chunk Access API							*/
/************************************************/
BOOL	Dllport BVCAM_ChunkAttachBuffer(HCAMERA hCamera, BVCAM_IMAGE* Image);
BOOL	Dllport BVCAM_ChunkGetType(HCAMERA hCamera, char* ChunkName, BVCAM_FEATURETYPE* Type, DWORD* Length);
BOOL	Dllport BVCAM_ChunkGetInteger(HCAMERA hCamera, char* ChunkName, INT64* Value);
BOOL	Dllport BVCAM_ChunkGetFloat(HCAMERA hCamera, char* ChunkName, double* Value);
BOOL	Dllport BVCAM_ChunkGetRegister(HCAMERA hCamera, char* ChunkName, BYTE* OutBuf, DWORD Length);
BOOL	Dllport BVCAM_ChunkGetEnumeration(HCAMERA hCamera, char* ChunkName, char* OutBuf, DWORD Length);
BOOL	Dllport BVCAM_ChunkGetString(HCAMERA hCamera, char* ChunkName, char* OutBuf, DWORD Length);
BOOL	Dllport BVCAM_ChunkGetBoolean(HCAMERA hCamera, char* ChunkName, BOOL* Value);


/************************************************/
/*	GigE Only API								*/
/************************************************/
BOOL	Dllport BVCAM_ControlCamera(HCAMERA hCamera, BOOL* Yes);
BOOL	Dllport BVCAM_GetGigEPktLog(HCAMERA hCamera, BVCAM_PKTLOG* Log);
BOOL	Dllport BVCAM_TestStream(HCAMERA hCamera, DWORD TimeOut);
BOOL	Dllport BVCAM_ResourceAllocGigE(HCAMERA hCamera, BYTE* IPAddr, BOOL Recover);
BOOL	Dllport BVCAM_HeartbeatMode(HCAMERA hCamera, DWORD TimeOut);
BOOL	Dllport BVCAM_BandAdjust(HCAMERA hCamera, DWORD BandSize);
BOOL	Dllport BVCAM_LostPktMode(HCAMERA hCamera, BOOL LostFlag, BYTE ClearData);
BOOL	Dllport BVCAM_ActionCommand(HCAMERA hCamera, BOOL Unicast, DWORD device_key, DWORD group_key, DWORD group_mask);
BOOL	Dllport BVCAM_ActionCommandAll(DWORD device_key, DWORD group_key, DWORD group_mask);
BOOL	Dllport BVCAM_ActionCommandTime(HCAMERA hCamera, BOOL Unicast, DWORD device_key, DWORD group_key, DWORD group_mask, UINT64 TimeValue);
BOOL	Dllport BVCAM_ActionCommandAllTime(DWORD device_key, DWORD group_key, DWORD group_mask, UINT64 TimeValue);
BOOL	Dllport BVCAM_SetActionAckCallBack(PVOID Context, ACTIONACKFUNC ActionAckFunc);


/************************************************/
/*	USB Only API								*/
/************************************************/
BOOL	Dllport BVCAM_SetPacketSizeUSB(HCAMERA hCamera, ULONG Length);
BOOL	Dllport BVCAM_StreamResetUSB(HCAMERA hCamera);


/************************************************/
/*	Color Conversion API						*/
/************************************************/
BOOL	Dllport BVCAM_CreateConvHandle(HCTBL* hTbl, BVCAM_COLORCONVMODE* CMode, BVCAM_COLORVALUE* CValue);
VOID	Dllport BVCAM_CloseConvHandle(HCTBL hTbl);
VOID	Dllport BVCAM_CloseAllConvHandle(VOID);
BOOL	Dllport BVCAM_ColorConvExec(HCTBL hTbl, BVCAM_IMAGE* Image, BYTE* OutBuf);
BOOL	Dllport BVCAM_ColorConvGetBMPINFO(HCTBL hTbl, BVCAM_IMAGE* Image, BITMAPINFO* Info);
BOOL	Dllport BVCAM_GetMonoBMPINFO(BVCAM_IMAGE* Image, BITMAPINFO* BmpInfo);


/************************************************/
/*	Feature API									*/
/************************************************/
BOOL	Dllport BVCAM_CategoryName(HFEATURE hFeature, DWORD Index, char* Buffer, DWORD Length);
BOOL	Dllport BVCAM_FeatureName(HFEATURE hFeature, char* Category, DWORD Index, char* Buffer, DWORD Length);
BOOL	Dllport BVCAM_FeatureType(HFEATURE hFeature, char* FeatureName, BVCAM_FEATURETYPE* Type);
BOOL	Dllport BVCAM_FeatureInfo(HFEATURE hFeature, char* FeatureName, BVCAM_FEATUREINFO* Info);
BOOL	Dllport BVCAM_FeatureDisplayName(HFEATURE hFeature, char* FeatureName, char* Buffer, DWORD Length);
BOOL	Dllport BVCAM_FeatureDescription(HFEATURE hFeature, char* FeatureName, char* Buffer, DWORD Length);
BOOL	Dllport BVCAM_FeatureToolTip(HFEATURE hFeature, char* FeatureName, char* Buffer, DWORD Length);
BOOL	Dllport BVCAM_FeatureUnit(HFEATURE hFeature, char* FeatureName, char* Buffer, DWORD Length);
BOOL	Dllport BVCAM_EnumerationEntryName(HFEATURE hFeature, char* FeatureName, DWORD Index, char* Buffer, DWORD Length);
BOOL	Dllport BVCAM_EnumerationEntryDisplayName(HFEATURE hFeature, char* FeatureName, char* EntryName, char* Buffer, DWORD Length);
BOOL	Dllport BVCAM_EnumerationEntryDescription(HFEATURE hFeature, char* FeatureName, char* EntryName, char* Buffer, DWORD Length);
BOOL	Dllport BVCAM_EnumerationEntryToolTip(HFEATURE hFeature, char* FeatureName, char* EntryName, char* Buffer, DWORD Length);
BOOL	Dllport BVCAM_EnumerationEntryValue(HFEATURE hFeature, char* FeatureName, char* EntryName, INT64* Value);
BOOL	Dllport BVCAM_EnumerationEntryIsAvailable(HFEATURE hFeature, char* FeatureName, char* EntryName, BOOL* IsAnser);
BOOL	Dllport BVCAM_GetFeatureInteger(HFEATURE hFeature, char* FeatureName, INT64* Value, BOOL CacheClear);
BOOL	Dllport BVCAM_SetFeatureInteger(HFEATURE hFeature, char* FeatureName, INT64 Value);
BOOL	Dllport BVCAM_GetFeatureFloat(HFEATURE hFeature, char* FeatureName, double* Value, BOOL CacheClear);
BOOL	Dllport BVCAM_SetFeatureFloat(HFEATURE hFeature, char* FeatureName, double Value);
BOOL	Dllport BVCAM_GetFeatureString(HFEATURE hFeature, char* FeatureName, char* Value, DWORD Length, BOOL CacheClear);
BOOL	Dllport BVCAM_SetFeatureString(HFEATURE hFeature, char* FeatureName, char* Value);
BOOL	Dllport BVCAM_GetFeatureBoolean(HFEATURE hFeature, char* FeatureName, BOOL* Value, BOOL CacheClear);
BOOL	Dllport BVCAM_SetFeatureBoolean(HFEATURE hFeature, char* FeatureName, BOOL Value);
BOOL	Dllport BVCAM_GetFeatureEnumeration(HFEATURE hFeature, char* FeatureName, char* Buffer, DWORD Length, BOOL CacheClear);
BOOL	Dllport BVCAM_SetFeatureEnumeration(HFEATURE hFeature, char* FeatureName, char* Buffer);
BOOL	Dllport BVCAM_GetFeatureRegister(HFEATURE hFeature, char* FeatureName, BYTE* Buffer, DWORD Length, BOOL CacheClear);
BOOL	Dllport BVCAM_SetFeatureRegister(HFEATURE hFeature, char* FeatureName, BYTE* Buffer, DWORD Length);
BOOL	Dllport BVCAM_FeatureCommand(HFEATURE hFeature, char* FeatureName);
BOOL	Dllport BVCAM_FeatureIsAvailable(HFEATURE hFeature, char* FeatureName, BOOL* IsAnser);
BOOL	Dllport BVCAM_FeatureIsWritable(HFEATURE hFeature, char* FeatureName, BOOL* IsAnser);
BOOL	Dllport BVCAM_FeatureIsReadable(HFEATURE hFeature, char* FeatureName, BOOL* IsAnser);


/************************************************/
/*	Register API								*/
/************************************************/
BOOL	Dllport BVCAM_ReadReg(HCAMERA hCamera, UINT64 Addr, DWORD* Value);
BOOL	Dllport BVCAM_ReadMem(HCAMERA hCamera, UINT64 Addr, PVOID pBuffer, DWORD* Length);
BOOL	Dllport BVCAM_WriteReg(HCAMERA hCamera, UINT64 Addr, DWORD Value);
BOOL	Dllport BVCAM_WriteMem(HCAMERA hCamera, UINT64 Addr, PVOID pBuffer, DWORD* Length);
BOOL	Dllport BVCAM_WriteRegAll(DWORD Addr, DWORD Value);

#ifdef __cplusplus
}
#endif

#pragma warning( pop )
#pragma pack( pop )
