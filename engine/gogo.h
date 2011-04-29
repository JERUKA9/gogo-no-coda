/* -*- TABSIZE = 4 -*- */
/*
 *   part of this code is origined from
 *   GOGO-no-coda
 *
 *   Copyright(C) 1999-2003 gogo-developer
 */


#ifndef GOGO_H_
#define GOGO_H_

typedef int MERET;

/* for only compatibility */
#define MUPARAM UPARAM

typedef	unsigned long			UPARAM;

#define	ME_NOERR					(0)		// return normally;���ｪλ
#define	ME_EMPTYSTREAM				(1)		// stream becomes empty;���ȥ꡼�ब�Ǹ��ã����
#define	ME_HALTED					(2)		// stopped by user;(�桼�����μ�ˤ��)���Ǥ��줿
#define	ME_MOREDATA					(3)	
#define	ME_INTERNALERROR			(10)	// internal error; �������顼
#define	ME_PARAMERROR				(11)	// parameters error;����ǥѥ�᡼�������顼
#define	ME_NOFPU					(12)	// no FPU;FPU�����夷�Ƥ��ʤ�!!
#define	ME_INFILE_NOFOUND			(13)	// can't open input file;���ϥե�����������������ʤ�
#define	ME_OUTFILE_NOFOUND			(14)	// can't open output file;���ϥե�����������������ʤ�
#define	ME_FREQERROR				(15)	// frequency is not good;�����ϼ��ȿ����������ʤ�
#define	ME_BITRATEERROR				(16)	// bitrate is not good;���ϥӥåȥ졼�Ȥ��������ʤ�
#define	ME_WAVETYPE_ERR				(17)	// WAV format is not good;�������֥����פ��������ʤ�
#define	ME_CANNOT_SEEK				(18)	// can't seek;����������������ʤ�
#define	ME_BITRATE_ERR				(19)	// only for compatibility;�ӥåȥ졼�����꤬�������ʤ�
#define	ME_BADMODEORLAYER			(20)	// mode/layer not good;�⡼�ɡ��쥤�������۾�
#define	ME_NOMEMORY					(21)	// fail to allocate memory;���ꥢ�������������
#define	ME_CANNOT_SET_SCOPE			(22)	// thread error;����å�°�����顼(pthread only)
#define	ME_CANNOT_CREATE_THREAD		(23)	// fail to create thear;����å��������顼
#define	ME_WRITEERROR				(24)	// lock of capacity of disk;�������Τ�������­


// definition of call-back function for user;�桼�����Υ�����Хå��ؿ����
typedef	MERET	(*MPGE_USERFUNC)(void *buf, unsigned long nLength );
#define MPGE_NULL_FUNC (MPGE_USERFUNC)NULL

///////////////////////////////////////////////////////////////////////////
// Configuration
///////////////////////////////////////////////////////////////////////////
// for INPUT
#define		MC_INPUTFILE			(1)
	// para1 choice of input device
	#define		MC_INPDEV_FILE		(0)	// input device is file;���ϥǥХ����ϥե�����
	#define		MC_INPDEV_STDIO		(1)	//                 stdin;���ϥǥХ�����ɸ������
	#define		MC_INPDEV_USERFUNC	(2)	//       defined by user;���ϥǥХ����ϥ桼�������
	#define		MC_INPDEV_LIBSND	(3) // input device is file via LIBSND ;���ϥǥХ����� LIBSND ��ͳ�ǥե�����
	// para2 (ɬ�פǤ����)�ե�����̾���ݥ��󥿤���ꤹ��
	// �����ꥨ�󥳡��ɤλ��ϰʲ��ι�¤�ΤΥݥ��󥿤���ꤹ��.
	struct MCP_INPDEV_USERFUNC {
		MPGE_USERFUNC	pUserFunc;		// pointer to user-function for call-back or MPGE_NULL_FUNC if none
											// ������Хå��оݤΥ桼�����ؿ���̤�����MPGE_NULL_FUNC������
		unsigned int	nSize;			// size of file or MC_INPDEV_MEMORY_NOSIZE if unknown
											// �ե����륵����������λ��� MC_INPDEV_MEMORY_NOSIZE�����
		int				nBit;	// nBit = 8 or 16 ; PCM�ӥåȿ��٤����
		int				nFreq;	// input frequency ; ���ϼ��ȿ��λ���
		int				nChn;	// number of channel(1 or 2) ; ����ͥ��
	};
	#define		MC_INPDEV_MEMORY_NOSIZE		(0xffffffff)
/*
  Using userfunction input;
  �桼�����ؿ����ѻ��ε�ư
  ^^^^^^^^^^^^^^^^^^^^^^^^

  �桼��������Ͽ�����ؿ� UsefFunc���Ф��ơ�DLL����ɤ߹����׵᤬�Ԥ��롣
  MERET	UserFunc_input(void *buf, unsigned long nLength );

  �׵���������ݤ�
     ��void *buf �ˤ� nLength �Х���ʬ�Υǡ������Ǽ�� return ME_NOERR��ȴ����
	 ���ե�����κǸ��ã���ơ�nLengthʬ�ɤ߹���ʤ�(���ľ��ʤ��Ȥ�1�Х��Ȱʾ��ɤ߹����)��硢
	    memset( buf + �ɤ߹�����ǡ���byte, 0, nLength - �ɤ߹�����ǡ���������) ;
	   �Ȥ��� return ME_NOERR ���롣
	 �����Х��Ȥ��ɤ�ʤ����ϡ����⤻�� return ME_EMPTYSTREAM; ��ȴ����
*/

///////////////////////////////////////////////////////////////////////////
// for OUTPUT ( now stdout is not support )
#define		MC_OUTPUTFILE			(2)
// para1 choice of output device
	#define		MC_OUTDEV_FILE		(0)	// output device is file;���ϥǥХ����ϥե�����
	#define		MC_OUTDEV_STDOUT	(1)	//                  stdout; ���ϥǥХ�����ɸ�����
	#define		MC_OUTDEV_USERFUNC	(2)	//        defined by user;���ϥǥХ����ϥ桼�������
	#define		MC_OUTDEV_USERFUNC_WITHVBRTAG	(3)	//       defined by user;���ϥǥХ����ϥ桼�������/VBR�����񤭽Ф�
// para2 pointer to file if necessary ;(ɬ�פǤ����)�ե�����̾���ݥ��󥿻���

/*
  Using userfunction output
  �桼�����ؿ����ѻ��ε�ư
  ^^^^^^^^^^^^^^^^^^^^^^^^

  �桼��������Ͽ�����ؿ� UsefFunc���Ф��ơ�DLL��������׵᤬�Ԥ��롣
  MERET	UserFunc_output(void *buf, unsigned long nLength );

  �׵���������ݤ�
     ��void *buf �ˤ� nLength �Х���ʬ�Υǡ�������Ǽ����Ƥ���Τ� 
	   fwrite( buf, 1, nLength, fp );���ͤˤ��ƽ񤭽Ф�return ME_NOERR��ȴ����.
	   �񤭽Ф��˼��Ԥ������ϡ�return ME_WRITEERROR;��ȴ����.
  ���󥳡��ɽ�λ������/������MC_OUTDEV_USERFUNC��MC_OUTDEV_USERFUNC_WITHVBRTAG�ǰۤʤ�
	(MC_OUTDEV_USERFUNC�ξ��)
	 ���Ǹ�� buf == NULL��1�ٸƤӽФ����. return �ͤϲ��Ǥ��ɤ���
	(MC_OUTDEV_USERFUNC_WITHVBRTAG�ξ��)
	 ��buf == NULL�ǸƤӽФ����.���κݤ˥ե��������Ƭ�إ���������
	   �ե��������ΤΥ������� return���ͤȤ��롣filesize<=0�λ��Ͻ�λ��
	   (��ä� return ME_NOERR; ��ȴ���ʤ��ͤ����!! )
	 ��XING-VBR�����ǡ����� buf�ˡ�XINGVBR�����Υ������� nLength�˳�Ǽ����ƸƤӽФ����Τ�
	   �ե�������Ƭ���餽���񤭹���.
	 ���Ǹ�ˤ⤦����buf == NULL�ǸƤӽФ����. return �ͤϲ��Ǥ��ɤ���
*/

///////////////////////////////////////////////////////////////////////////
// mode of encoding ;���󥳡��ɥ�����
#define		MC_ENCODEMODE			(3)
// para1 mode;�⡼������
	#define		MC_MODE_MONO		(0)		// mono;��Υ��
	#define		MC_MODE_STEREO		(1)		// stereo;���ƥ쥪
	#define		MC_MODE_JOINT		(2)		// joint-stereo;���祤���
	#define		MC_MODE_MSSTEREO	(3)		// mid/side stereo;�ߥåɥ�����
	#define		MC_MODE_DUALCHANNEL	(4)		// dual channel;�ǥ奢�����ͥ�

///////////////////////////////////////////////////////////////////////////
// bitrate;�ӥåȥ졼������
#define		MC_BITRATE				(4)
// para1 bitrate;�ӥåȥ졼�� ¨�ͻ���


///////////////////////////////////////////////////////////////////////////
// frequency of input file (force);���Ϥ��Ѥ��륵��ץ���ȿ��ζ�������
#define		MC_INPFREQ				(5)
// para1 frequency;�����Ϥ��Ѥ���ǡ���

///////////////////////////////////////////////////////////////////////////
// frequency of output mp3 (force);���Ϥ��Ѥ��륵��ץ���ȿ��ζ�������
#define		MC_OUTFREQ				(6)
// para1 frequency;�����Ϥ��Ѥ���ǡ���

///////////////////////////////////////////////////////////////////////////
// size ofheader if you ignore WAV-header (for example cda);���󥳡��ɳ��ϰ��֤ζ�������(�إå���̵�뤹���)
#define		MC_STARTOFFSET			(7)

///////////////////////////////////////////////////////////////////////////
// psycho-acoustics ON/OFF;�������� ON/OFF
#define		MC_USEPSY				(8)
// PARA1 boolean(TRUE/FALSE)

///////////////////////////////////////////////////////////////////////////
// 16kHz low-pass filter ON/OFF;16KHz���Ӱ�ե��륿 ON/OFF
#define		MC_USELPF16				(9)
// PARA1 boolean(TRUE/FALSE)

///////////////////////////////////////////////////////////////////////////
// use special UNIT, para1:boolean; ��˥åȻ��� para1:BOOL��
#define		MC_USEMMX				(10)	// MMX
#define		MC_USE3DNOW				(11)	// 3DNow!
#define		MC_USESSE				(12)	// SSE(KNI)
#define		MC_USEKNI				MC_USESSE	// ���2�Ȥθߴ���
#define		MC_USEE3DNOW			(13)	// Enhanced 3D Now!
#define		MC_USECMOV				(38)	// CMOV
#define		MC_USEEMMX				(39)	// EMMX
#define		MC_USESSE2				(40)	// SSE2
/* #define 	MC_USECLFLUSH				(43)	// CLFLUSH */
#define 	MC_USEALTIVEC				(44)	// ALTIVEC
#define		MC_USESPC1				(14)	// special switch for debug
#define		MC_USESPC2				(15)	// special switch for debug

///////////////////////////////////////////////////////////////////////////
// addition of TAG; �ե����륿�������ղ�
#define		MC_ADDTAG				(16)
// dwPara1  length of TAG;����Ĺ  
// dwPara2  pointer to TAG;�����ǡ����Υݥ���

///////////////////////////////////////////////////////////////////////////
// emphasis;����ե����������פ�����
#define		MC_EMPHASIS				(17)	
// para1 type of emphasis;����ե����������פ�����
	#define		MC_EMP_NONE			(0)		// no empahsis;����ե������ʤ�(dflt)
	#define		MC_EMP_5015MS		(1)		// 50/15ms    ;����ե�����50/15ms
	#define		MC_EMP_CCITT		(3)		// CCITT      ;����ե�����CCITT

///////////////////////////////////////////////////////////////////////////
// use VBR;VBR�����פ�����
#define		MC_VBR					(18)

///////////////////////////////////////////////////////////////////////////
// SMP support para1: interger
#define		MC_CPU					(19)

///////////////////////////////////////////////////////////////////////////
// for RAW-PCM; �ʲ�4�Ĥ�RAW-PCM������Τ���
// byte swapping for 16bitPCM; PCM���ϻ���low, high bit �Ѵ�
#define		MC_BYTE_SWAP			(20)

///////////////////////////////////////////////////////////////////////////
// for 8bit PCM
#define		MC_8BIT_PCM				(21)

///////////////////////////////////////////////////////////////////////////
// for mono PCM
#define		MC_MONO_PCM				(22)

///////////////////////////////////////////////////////////////////////////
// for Towns SND
#define		MC_TOWNS_SND			(23)

///////////////////////////////////////////////////////////////////////////
// BeOS & Win32 Encode thread priority
#define		MC_THREAD_PRIORITY		(24)
// (WIN32) dwPara1 MULTITHREAD Priority (THREAD_PRIORITY_**** at WinBASE.h )

///////////////////////////////////////////////////////////////////////////
// BeOS Read thread priority
//#if	defined(USE_BTHREAD)
#define		MC_READTHREAD_PRIORITY	(25)
//#endif

///////////////////////////////////////////////////////////////////////////
// output format 
#define		MC_OUTPUT_FORMAT		(26)
// para1 
	#define		MC_OUTPUT_NORMAL	(0)		// mp3+TAG(see MC_ADDTAG)
	#define		MC_OUTPUT_RIFF_WAVE	(1)		// RIFF/WAVE
	#define		MC_OUTPUT_RIFF_RMP	(2)		// RIFF/RMP

///////////////////////////////////////////////////////////////////////////
// LIST/INFO chunk of RIFF/WAVE or RIFF/RMP 
#define		MC_RIFF_INFO			(27)
// para1 size of info(include info name)
// para2 pointer to info
//   byte offset       contents
//   0..3              info name
//   4..size of info-1 info

///////////////////////////////////////////////////////////////////////////
// verify and overwrite
#define		MC_VERIFY				(28)

///////////////////////////////////////////////////////////////////////////
// output directory
#define		MC_OUTPUTDIR			(29)

///////////////////////////////////////////////////////////////////////////
// VBR�κ���/�ǹ�ӥåȥ졼�Ȥ�����
#define		MC_VBRBITRATE			(30)
// para1 ����ӥåȥ졼�� (kbps)
// para2 �ǹ�ӥåȥ졼�� (kbps)


///////////////////////////////////////////////////////////////////////////
// ��ĥ�ե��륿�λ��� LPF1, LPF2
#define		MC_ENHANCEDFILTER		(31)
// para1 LPF1 (0-100)	, dflt=auto setting by outfreq
// para2 LPF2 (0-100)	, dflt=auto setting by outfreq


///////////////////////////////////////////////////////////////////////////
// Joint-stereo�ˤ����롢���ƥ쥪/MS���ƥ쥪���ڤ��ؤ�������
#define		MC_MSTHRESHOLD	 		(32)
// para1 threshold  (0-100)	, dflt=auto setting by outfreq
// para2 mspower    (0-100) , dflt=auto setting by outfreq

///////////////////////////////////////////////////////////////////////////
// Language
#define		MC_LANG					(33)
// t_lang defined in message.h

///////////////////////////////////////////////////////////////////////////
// �ɤ߹��ߥǡ����κ��祵�������� / max data length ( byte )
#define		MC_MAXFILELENGTH		(34)
// para1 maxfilesize (PCM body length, not include wave heaher size.)
//       (0-0xfffffffd)		// as byte
		#define		MC_MAXFLEN_IGNORE		(ULONG_MAX)		// DEFAULT
		#define		MC_MAXFLEN_WAVEHEADER	(ULONG_MAX-1)	// WAVE�إå����ͤ����


///////////////////////////////////////////////////////////////////////////
// ���ϥ��ȥ꡼��ΥХåե���󥰥ե饰
#define		MC_OUTSTREAM_BUFFERD	(35)
// para1  enable(=1) or disable(=0), dflt=enable
		#define		MC_OBUFFER_ENABLE		1				// DEFAULT
		#define		MC_OBUFFER_DISABLE		0

// �ʲ��Ϥפ���忷��

///////////////////////////////////////////////////////////////////////////
// quality (same as lame-option `-q')
#define		MC_ENCODE_QUALITY		(36)
// 1(high quality) <= para1 <= 9(low quality)
// 2:-h
// 5:default
// 7:-f



///////////////////////////////////////////////////////////////////////////
// use ABR;ABR�����פ�����
#define		MC_ABR					(37)

///////////////////////////////////////////////////////////////////////////
// ���ߤ��줿CPU�����פ�����
// defined in `use special UNIT'
//#define		MC_USECMOV				(38)	// CMOV �������Ѥ�
//#define		MC_USEEMMX				(39)	// EMMX �������Ѥ�
//#define		MC_USESSE2				(40)	// SSE2 �������Ѥ�

///////////////////////////////////////////////////////////////////////////
// LAME�����ν������� (ʻ����VBR�����ν񤭽Ф���ͭ���ˤ��Ƥ�������)
#define		MC_WRITELAMETAG					(41)
/// para1: 0 = disable (default)
///        1 = enable

///////////////////////////////////////////////////////////////////////////
// VBR�����ν������� (CBR�Ǥʤ�����lametag̵�������������Ƥ˴ط��ʤ�̵���Ǥ�)
#define		MC_WRITEVBRTAG					(42)
/// para1: 0 = disable 
///        1 = enable (default)


///////////////////////////////////////////////////////////////////////////
//  Functions
///////////////////////////////////////////////////////////////////////////
#ifdef GOGO_DLL_EXPORTS
#define		EXPORT				__declspec(dllexport) __cdecl	
#define		EXPORT_VB			__declspec(dllexport) __stdcall	
#else
#define		EXPORT
#define		EXPORT_VB
#endif

MERET	EXPORT	MPGE_initializeWork(void);
MERET	EXPORT	MPGE_setConfigure(UPARAM mode, UPARAM dwPara1, UPARAM dwPara2);
MERET	EXPORT	MPGE_getConfigure(UPARAM mode, void *para1);
MERET	EXPORT	MPGE_detectConfigure(void);
MERET	EXPORT	MPGE_processFrame(void);
MERET	EXPORT	MPGE_closeCoder(void);
MERET	EXPORT	MPGE_endCoder(void);
MERET	EXPORT	MPGE_getUnitStates( unsigned long *unit );
MERET	EXPORT	MPGE_processTrack(void);

// This function is effective for gogo.dll;���Υե��󥯥�����DLL�С������Τ�ͭ��
MERET	EXPORT	MPGE_getVersion( unsigned long *vercode,  char *verstring );
#define MGV_BUFLENGTH 260
// vercode = 0x125 ->  version 1.25
// verstring       ->  "ver 1.25 1999/09/25" (allocate abobe 260bytes buffer)


////////////////////////////////////////////////////////////////////////////
// for getting configuration
////////////////////////////////////////////////////////////////////////////

#define		MG_INPUTFILE			(1)		// name of input file ;���ϥե�����̾����
#define		MG_OUTPUTFILE			(2)		// name of output file;���ϥե�����̾����
#define		MG_ENCODEMODE			(3)		// type of encoding   ;���󥳡��ɥ⡼��
#define		MG_BITRATE				(4)		// bitrate            ;�ӥåȥ졼��
#define		MG_INPFREQ				(5)		// input frequency    ;���ϼ��ȿ�
#define		MG_OUTFREQ				(6)		// output frequency   ;���ϼ��ȿ�
#define		MG_STARTOFFSET			(7)		// offset of input PCM;�������ȥ��ե��å�
#define		MG_USEPSY				(8)		// psycho-acoustics   ;�������Ϥ���Ѥ���/���ʤ�
#define		MG_USEMMX				(9)		// MMX
#define		MG_USE3DNOW				(10)	// 3DNow!
#define		MG_USESSE				(11)	// SSE(KNI)
#define		MG_USEKNI				MG_USESSE	// ���2�Ȥθߴ���
#define		MG_USEE3DNOW			(12)	// Enhanced 3DNow!
#define		MG_USECMOV				(20)	// CMOV
#define		MG_USEEMMX				(21)	// EMMX
#define		MG_USESSE2				(22)	// SSE2
#define 	MG_CLFLUSH				(23)	// CLFLUSH
#define 	MG_USEALTIVEC				(24)	// ALTIVEC
#define		MG_USESPC1				(13)	// special switch for debug
#define		MG_USESPC2				(14)	// special switch for debug
#define		MG_COUNT_FRAME			(15)	// amount of frame
#define		MG_NUM_OF_SAMPLES		(16)	// number of sample for 1 frame;1�ե졼�ढ����Υ���ץ��
#define		MG_MPEG_VERSION			(17)	// MPEG VERSION
#define		MG_READTHREAD_PRIORITY	(18)	// thread priority to read for BeOS
#define		MG_FRAME				(19)	// frame number
//#define		MG_USECMOV				(20)	// CMOV �������Ѥ�
//#define		MG_USEEMMX				(21)	// EMMX �������Ѥ�
//#define		MG_USESSE2				(22)	// SSE2 �������Ѥ�



////////////////////////////////////////////////////////////////////////////
//  for MPGE_getUnitStates()
////////////////////////////////////////////////////////////////////////////
// x86 - Spec
#define		MU_tFPU					(1<<0)
#define		MU_tMMX					(1<<1)
#define		MU_t3DN					(1<<2)
#define		MU_tSSE					(1<<3)
#define		MU_tCMOV				(1<<4)
#define		MU_tE3DN				(1<<5)	/* for Athlon(Externd 3D Now!) */
#define 	MU_tEMMX				(1<<6)  /* EMMX = E3DNow!_INT = SSE_INT  */
#define		MU_tSSE2				(1<<7)
#define 	MU_tCLFLUSH				(1<<18)
#define 	MU_tMULTI				(1<<12)	/* for Multi-threaded encoder. Never set on UP or in the binary linked w/o multithread lib. */

// x86 - Vendor
#define 	MU_tINTEL				(1<<8)
#define 	MU_tAMD					(1<<9)
#define 	MU_tCYRIX				(1<<10)
#define 	MU_tIDT					(1<<11)
#define 	MU_tUNKNOWN				(1<<15)	/* unknown vendor */

// x86 - Special
#define 	MU_tSPC1 				(1<<16)	/* special flag */
#define 	MU_tSPC2 				(1<<17)	/* freely available */
// x86 - CPU TYPES
#define 	MU_tFAMILY4				(1<<20)	/* 486 vendor maybe isn't correct */
#define 	MU_tFAMILY5				(1<<21)	/* 586 (P5, P5-MMX, K6, K6-2, K6-III) */
#define 	MU_tFAMILY6				(1<<22)	/* 686 above P-Pro, P-II, P-III, Athlon */
#define 	MU_tFAMILY7				(1<<23) /* Pentium IV ? */

// for PPC arc
#define 	MU_tPPC					(1<<0)
#define 	MU_tGRAP				(1<<1)	/* fres, frsqrte, fsel */
#define 	MU_tFSQRT				(1<<2)	/* fsqrt, fsqrts */
#define 	MU_tALTIVEC				(1<<3)	/* AltiVec */


#endif /* GOGO_H_ */
