#ifndef _DOLPHIN_THP_H_
#define _DOLPHIN_THP_H_

typedef unsigned char u8;
typedef signed char s8;
typedef unsigned short u16;
typedef signed short s16;
typedef unsigned long u32;
typedef signed long s32;
typedef signed long long s64;
typedef float f32;
typedef double f64;
typedef int BOOL;
#define TRUE 1
#define FALSE 0
#define NULL 0
#ifndef _DOLPHIN_OSFASTCAST_H_
#define _DOLPHIN_OSFASTCAST_H_

#ifdef __cplusplus
extern "C" {
#endif

#define OS_GQR_F32 0x0000
#define OS_GQR_U8  0x0004
#define OS_GQR_U16 0x0005
#define OS_GQR_S8  0x0006
#define OS_GQR_S16 0x0007

#define OS_FASTCAST_U8  2
#define OS_FASTCAST_U16 3
#define OS_FASTCAST_S8  4
#define OS_FASTCAST_S16 5
// clang-format off
static inline void OSInitFastCast(void) {
#ifdef __MWERKS__
  asm
  {
        li      r3, OS_GQR_U8
        oris    r3, r3, OS_GQR_U8
        mtspr   GQR2, r3

        li      r3, OS_GQR_U16
        oris    r3, r3, OS_GQR_U16
        mtspr   GQR3, r3

        li      r3, OS_GQR_S8
        oris    r3, r3, OS_GQR_S8
        mtspr   GQR4, r3

        li      r3, OS_GQR_S16
        oris    r3, r3, OS_GQR_S16
        mtspr   GQR5, r3
  }
#else

#endif
}
// clang-format off

#ifdef __cplusplus
}
#endif

#endif // _DOLPHIN_OSFASTCAST

#ifdef __cplusplus
extern "C" {
#endif

typedef u8 THPSample;
typedef s16 THPCoeff;
typedef float THPQuantTab[64];

typedef struct _THPHuffmanTab {
	u8 quick[32];
	u8 increment[32];
	u8* Vij;
	s32 maxCode[18];
	s32 valPtr[18];
	u8 Vij1;
	u8 pad[11];
} THPHuffmanTab;

typedef struct _THPComponent {
	u8 quantizationTableSelector;
	u8 DCTableSelector;
	u8 ACTableSelector;
	THPCoeff predDC;
} THPComponent;

typedef struct _THPFileInfo {
	THPQuantTab quantTabs[3];
	THPHuffmanTab huffmanTabs[4];
	THPComponent components[3];
	u16 xPixelSize;
	u16 yPixelSize;
	u16 MCUsPerRow;
	u16 decompressedY;
	u8* c;
	u32 currByte;
	u32 cnt;
	u8 validHuffmanTabs;
	u8 RST;
	u16 nMCU;
	u16 currMCU;
	u8* dLC[3];
} THPFileInfo;

typedef struct {
	u32 offsetNextChannel;
	u32 sampleSize;
	s16 lCoef[8][2];
	s16 rCoef[8][2];
	s16 lYn1;
	s16 lYn2;
	s16 rYn1;
	s16 rYn2;
} THPAudioRecordHeader;

typedef struct {
	u8* encodeData;
	u32 offsetNibbles;
	u8 predictor;
	u8 scale;
	s16 yn1;
	s16 yn2;
} THPAudioDecodeInfo;

BOOL THPInit();
s32 THPVideoDecode(void* file, void* tileY, void* tileU, void* tileV,
                   void* work);
u32 THPAudioDecode(s16* audioBuffer, u8* audioFrame, s32 flag);

static s32 __THPAudioGetNewSample(THPAudioDecodeInfo*);
static void __THPAudioInitialize(THPAudioDecodeInfo*, u8*);

static void __THPSetupBuffers(void);
static u8 __THPReadFrameHeader(void);
static u8 __THPReadScaneHeader(void);
static u8 __THPReadQuantizationTable(void);
static u8 __THPReadHuffmanTableSpecification(void);
static void __THPHuffGenerateSizeTable(void);
static void __THPHuffGenerateCodeTable(void);
static void __THPHuffGenerateDecoderTables(u8 tabIndex);
static void __THPRestartDefinition(void);
static void __THPPrepBitStream(void);
static void __THPDecompressYUV(void*, void*, void*);
static void __THPGQRRestore(void);
static void __THPDecompressiMCURow512x448(void);
static void __THPDecompressiMCURow640x480(void);
static void __THPDecompressiMCURowNxN(void);
static void __THPInverseDCTNoYPos(THPCoeff*, u32);
static void __THPHuffDecodeDCTCompY(THPFileInfo*, THPCoeff*);
static void __THPHuffDecodeDCTCompU(THPFileInfo*, THPCoeff*);
static void __THPHuffDecodeDCTCompV(THPFileInfo*, THPCoeff*);

#ifdef __cplusplus
}
#endif

#endif

u32 PPCMfhid2(void);
void DCZeroRange(void*, u32);
u32 LCStoreData(void*, void*, u32);
void LCQueueWait(u32);
void OSRegisterVersion(const char*);
#define OSRoundUp32B(x) (((u32)(x) + 31) & ~31)
