// ****************************************************************************
// Surface Description
//
#ifndef __EC_SURFACE
#define	__EC_SURFACE

enum t_Surface_Type {
	EC_SURFACE_TYPE_UNKNOWN,
	EC_SURFACE_TYPE_PC,			
	EC_SURFACE_TYPE_DIRECT_DRAW,
	EC_SURFACE_TYPE_BOARD,		
	EC_SURFACE_TYPE_IEEE1394,	
	EC_SURFACE_TYPE_DSP,		
	EC_SURFACE_TYPE_PRESTO
};

enum t_Surface_State {
	SURFACE_STATE_FREE,		// 0
	SURFACE_STATE_CAPTURED,	// 1
	SURFACE_STATE_FILLING,	// 2
	SURFACE_STATE_FILLED,	// 3
	SURFACE_STATE_PROCESSING// 4
};

#define EC_MAX_SURFACE	16384

#define EC_PAUSE_INITPAUSE		0x01
#define EC_PAUSE_REPEATPAUSE	0x02
#define EC_PAUSE_LAST			0x10

#define EC_PAUSE_LIVE			0x20

#define EC_TRIGGER_INIT			0x01
#define EC_TRIGGER_REPEAT		0x02
#define EC_TRIGGER_LAST			0x10

#define EC_STATUS_PARITY_UP		0x0080
#define EC_ERROR_DELAY			0x0100
#define EC_ERROR_FIFO_RESYNC	0x0200
#define EC_ERROR_MISMATCH		0x0400
#define EC_ERROR_RESTART		0x0800
#define	EC_ERROR_FIFO			0x1000
#define	EC_ERROR_SKIP			0x2000
#define	EC_ERROR_NOSIG			0x4000
#define	EC_ERROR_DMA			0x8000
#define	EC_ERROR_FLUSH			0xFF00


typedef struct t_SurfaceInfo {
	UINT32 StructSize ;
	UINT32 Type ;
	PVOID Address ;
	UINT32 Size ;
	UINT32 Pitch ;
	UINT32 UserAllocatedMemory;
} ECSURFACEINFO, *PECSURFACEINFO;


#endif //__EC_SURFACE
