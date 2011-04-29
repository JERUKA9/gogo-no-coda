/*
 *   part of this code is origined from
 *   GOGO-no-coda
 *
 *   Copyright(C) 2001,2002,2003 gogo-developer
 */

#ifndef GLOBAL_H_
#define GLOBAL_H_

#include "common.h"
#include "gogo.h"
#include "l3side.h"
#include "thread.h"

#ifdef _GOGO_C_
	#define EXT
#else
	#define EXT extern
#endif

typedef struct  {
		size_t		nSize;	// size of file or MC_INPDEV_MEMORY_NOSIZE if unknown
					        // �ե����륵����������λ��� MC_INPDEV_MEMORY_NOSIZE�����
		int			nBit;	// nBit = 8 or 16 ; PCM�ӥåȿ��٤����
		int			nFreq;	// input frequency ; ���ϼ��ȿ��λ���
		int			nChn;	// number of channel(1 or 2) ; ����ͥ��
} PCM_FORMAT;

//	�ǥХ����ޤ���¾�ΥǥХ�����ե��륿�����Ƽ��餬�ǥХ����Τ褦�˿��񤦥ե��륿���ؤΥϥ�ɥ�
//	�ʹߤϡ��ä��Ǥ�ʤ��¤ꡤ�嵭��������ǥХ�������Τ���
typedef	void*	DEVICE_HANDLE;

//	�ǥХ�����������Ϥޤ��Ͻ��Ϥ򤹤�
//	������
//		nLength �Х��Ȥ�ǥХ������� buf ���ɤ߹��ࡥ
//		����˽�λ������ nLenght ���֤���
//		EOF �䥨�顼�� nLength �Х����ɤ߹���ʤ��ä��顤
//		�ºݤ��ɤ᤿�Х��ȿ����֤���
//	������
//		buf ���� nLength �Х��Ȥ�ǥХ����ؽ񤭹���
//		����˽�λ������ nLenght ���֤���
//		���顼�ʤɤ� nLength �Х��Ƚ񤭹���ʤ��ä���
//		�ºݤ˽񤭹��᤿�Х��ȿ����֤���
typedef size_t	(*IO_DEVICE_FUNC)(DEVICE_HANDLE handle, void* buf, size_t nLength);

//	�ǥХ�������������Ϥ��Ĥ���
typedef void  	(*CLOSE_DEVICE_FUNC)(DEVICE_HANDLE handle);

//	���ϥǥХ�����ǥХ�����Ƭ�إ���������
//	���������� ME_NOERR, ���Ԥ����� ME_CANNOT_SEEK ���֤�
typedef MERET  	(*SEEK_TOP_OUTPUT_DEVICE_FUNC)(DEVICE_HANDLE handle);

//	���ϥǥХ����򥪡��ץ󤹤�
//	*read, *close �˥ǥХ��������ɤ߹���ؿ�, �Ĥ���ؿ��������(ɬ��)
//	*handle �˥ǥХ����Υϥ�ɥ�������(ɬ��)
//	*pcm_format �� PCM �Ȥ��ƤΥե�����ե����ޥåȤ������
//	���������� ME_NOERR, ���Ԥ�������ͳ�˹�碌�� ME_* ���֤�
//	�ǥХ��������ץ�Τ����ɬ�פʥѥ�᡼����­��ʤ���С�
//	�������������ꤷ�Ƥ�������
//	���ۥ�ȤΥǥХ���
//		*handle == 0 �ǸƤФ��
//		PCM �ե����ޥåȤ��狼��ʤ���� *pcm_format �����֤��Ƥ��ɤ�
//	���ե��륿���ǥХ���
//		*handle, *read, *close, *pcm_format ����̣��
//		���ʤΥǥХ����ޤ��ϥե��륿�����֤����ͤ����Τޤ����äƤ���
//		���Τޤޤ��ɤ���Ф�����ʤ��Ƥ��ɤ�
typedef MERET	(*OPEN_INPUT_DEVICE_FUNC)(DEVICE_HANDLE* handle, const char* file_name, PCM_FORMAT* pcm_format, IO_DEVICE_FUNC* read, CLOSE_DEVICE_FUNC* close);

//	���ϥǥХ����򥪡��ץ󤹤�
//	*write, *close �˥ǥХ����˽񤭹���ؿ�, �Ĥ���ؿ��������(ɬ��)
//	*seek_top �ˤϥǥХ�������Ƭ���᤹�ؿ��������(Ǥ��)
//	*handle �˥ǥХ����Υϥ�ɥ�������(ɬ��)
//	���������� ME_NOERR, ���Ԥ�������ͳ�˹�碌�� ME_* ���֤�
//	�ǥХ��������ץ�Τ����ɬ�פʥѥ�᡼����­��ʤ���С�
//	�������������ꤷ�Ƥ�������
//	���ۥ�ȤΥǥХ���
//		*handle == 0 �ǸƤФ��
//	���ե��륿���ǥХ���
//		*handle, *write, *close, *seek_top ����̣��
//		���ʤΥǥХ����ޤ��ϥե��륿�����֤����ͤ����Τޤ����äƤ���
//		���Τޤޤ��ɤ���Ф�����ʤ��Ƥ��ɤ�
typedef MERET	(*OPEN_OUTPUT_DEVICE_FUNC)(DEVICE_HANDLE* handle, const char* file_name, IO_DEVICE_FUNC* write, SEEK_TOP_OUTPUT_DEVICE_FUNC* seek_top, CLOSE_DEVICE_FUNC* close);

//	�ܤ����Ϲͤ��Ƥʤ����ɡ�����ʴ����ǥ��֥Х�ɥե��륿���⳰�˽Ф������ʡ��ȡ�
typedef void 	(*SUBBAND_FILTER_FUNC)(float subband[18][SBLIMIT]);

enum vbr_mode_e {
  vbr_off=0,
  vbr_rh,
  vbr_abr,
  vbr_default=vbr_rh  /* change this to change the default VBR mode of LAME */ 
};


/**
 *  ATH related stuff, if something new ATH related has to be added,
 *  please plugg it here into the ATH_t struct
 */
typedef struct ath_t
{
    int     use_adjust;     // do we want to use the auto adjustment yes/no
    FLOAT8  adjust;         // lowering based on peak volume, 1 = no lowering
    FLOAT8  adjust_limit;   // limit for dynamic ATH adjust
    FLOAT8  decay;          // determined to lower x dB each second
    FLOAT8  l[SBMAX_l];     // ATH for sfbs in long blocks
    FLOAT8  s[SBMAX_s];     // ATH for sfbs in short blocks
    FLOAT8  cb[CBANDS];     // ATH for convolution bands
} ATH_t;


/**
 * "bit_stream.h" Type Definitions 
 */
/* maximum size of mp3buffer needed if you encode at most 1152 samples for
   each call to lame_encode_buffer.  see lame_encode_buffer() below  
   (LAME_MAXMP3BUFFER is now obsolete)  */
#define LAME_MAXMP3BUFFER   16384
typedef struct  bit_stream_struc {
    unsigned char buf[LAME_MAXMP3BUFFER];         /* bit stream buffer */
    unsigned char *buf_byte_ptr;   /* pointer to top byte in buffer */
    int         bit_idx;        /* top bit length of top byte in buffer */
} Bit_stream_struc;

/**
 *  VBR_seek_info_t
 */
typedef struct vbr_seek_info_t
{
    int sum;    // what we have seen so far
    int seen;   // how many frames we have seen in this chunk
    int want;   // how many frames we want to collect into one chunk
    int pos;    // actual position in our bag
    int size;   // size of our bag
    int bag[400];   // bag
} VBR_seek_info_t;

#define MAX_HEADER_BUF 256
#define MAX_HEADER_LEN 40 /* max size of header is 38 */
/**
 * variables for bitstream.c 
 * mpeg1: buffer=511 bytes  smallest frame: 96-38(sideinfo)=58
 * max number of frames in reservoir:  8 
 * mpeg2: buffer=255 bytes.  smallest frame: 24-23bytes=1
 * with VBR, if you are encoding all silence, it is possible to
 * have 8kbs/24khz frames with 1byte of data each, which means we need
 * to buffer up to 255 headers!
 * also, max_header_buf has to be a power of two */
typedef struct header_buf_t {
	int			write_period;
	unsigned char		buf[MAX_HEADER_LEN];
	struct header_buf_t	*next;
} Header_buf_t;

typedef struct abr_t {
	float a;
	float b;
	float r;
} Abr_t;

/**
 *  riffInfo_t
 */
typedef struct riffInfo_t 
{
	int		riffInfosLen;
	char	*pRiffInfos;
} RiffInfo_t;

typedef struct addtag_t 
{
	int		addtagLen;
	char	*pAddtagInfos;
} Addtag_t;


/**
 * the following variables are constant(Read Only) in encoding 
 * Don't change them except in gogo.c 
 * �����ѿ��ϥ��󥳡����������Ǥ��� 
 * gogo.c�ʳ��ǤϽ񤭹���ǤϤ����ʤ� 
 */
typedef struct ro_t {
/*  variables to be aligned (align ��ɬ�פʥ���ã) */
/*  i386 �ǳƥ��Ф� size �� 16 ���ܿ��ˤʤ�褦�ˤ��뤳�� */
  /* fft.c    */
  FLOAT window[BLKSIZE];  // 4096 bytes
  FLOAT window_s[BLKSIZE_s/2]; // 512 bytes 

  /* DATA FROM PSYMODEL.C */
/* The static variables "r", "phi_sav", "new", "old" and "oldest" have    */
/* to be remembered for the unpredictability measure.  For "r" and        */
/* "phi_sav", the first index from the left is the channel select and     */
/* the second index is the "age" of the data.                             */
  FLOAT8	minval[CBANDS];                    // 256 bytes
  FLOAT8 s3_s[CBANDS][CBANDS];                     // 16384 bytes
  FLOAT8 s3_l[CBANDS][CBANDS];                     // 16384 bytes

  /* Scale Factor Bands    */
//  FLOAT8	w1_l[SBMAX_l], w2_l[SBMAX_l]; // RO
//  FLOAT8	w1_s[SBMAX_s], w2_s[SBMAX_s]; // RO /* always 0.5 */
  int	s3ind[CBANDS][2];  // 512 bytes
  int	s3ind_s[CBANDS][2]; // 512 bytes
  FLOAT8 SNR_s[CBANDS]; // 256 bytes

  int	numlines_s[CBANDS]; // 256 bytes
  int	numlines_l[CBANDS]; // 256 bytes

  FLOAT8 mld_l[SBMAX_l+2];  // 88+ 8 bytes
  FLOAT8 mld_s[SBMAX_s+3];  // 52+12 bytes
  int	 bu_l[SBMAX_l+2];   // 88+ 8 bytes 
  int    bo_l[SBMAX_l+2];   // 88+ 8 bytes
  int	 bu_s[SBMAX_s+3];   // 52+12 bytes
  int    bo_s[SBMAX_s+3];   // 52+12 bytes
/*  align ��ɬ�פʥ���ã����� */

/*	�ǥե��������ʤ饨�󥳡�����˻��Ѥ������ã */
    /* iteration functions */
    void (*iteration_loop)(gogo_thread_data *tl, FLOAT8 pe[2][2], FLOAT8 ms_ratio[2], int *mean_bits);
    void (*iteration_finish)(int l3_enc  [2][2][576], III_side_info_t *l3_side,
             III_scalefac_t  scalefac[2][2], const int mean_bits );
	void (*getframebits)(gogo_thread_data *tl, int *bitsPerFrame, int *mean_bits);
 
 	/* internal variables */
	int bitsPerFrame;
	int nSample;				/* ����ץ���������� 0 or ���������Ȥ��Ƥ������� */
	int framesize;
	int	nChannel;
	int out_samplerate;         /* output_samp_rate.
                                   default: LAME picks best value 
                                   at least not used for MP3 decoding:
                                   Remember 44.1 kHz MP3s and AC97           */
	int	channels_out;	/* number of channels in the output data stream */ // RO
	int	mode_gr;
	/* RO.lowpass_band == 22 && RO.highpass_band == -1 �ΤȤ� 416 ����¾ 576 */
	/* �����������ix/xr��0 */
	int ixend;

	/* CPU */
	int nCPU;

	/* Thread */
	int	nThread;
	gogo_thread_data	*tl;

	/* etc */
	void	(*printf)(const char *, ...);

	/* used for padding */
	int frac_SpF; 

	/* from quantize_pvt.h */
	#define IXMAX_VAL 8206  /* ix always <= 8191+15.    see count_bits() */
	/* buggy Winamp decoder cannot handle values > 8191 */
	/* #define IXMAX_VAL 8191 */
	#define Q_MAX 330
	#define PRECALC_SIZE (IXMAX_VAL+2)	
	float	pow20[Q_MAX];
	float	ipow20[Q_MAX];
	float	pow43[PRECALC_SIZE];

	/* variables used by quantize.c */
	FLOAT8 decay; 

	int sideinfo_len;

	scalefac_struct scalefac_band; 

	int cw_upper_index; 
	int	npart_l,npart_s; 
	int	npart_l_orig,npart_s_orig;
	int npart_l_pre_max;

	int	emphasis;
	int samplerate_index;  

	/*	�� IO ��Ϣ */
	DEVICE_HANDLE	input_device_handle;
	DEVICE_HANDLE	output_device_handle;

	IO_DEVICE_FUNC	read_input_device;
	IO_DEVICE_FUNC	write_output_device;
/*	�ǥե��������ʤ饨�󥳡�����˻��Ѥ������ã����� */

/*	ASM �ؿ��ؤΥݥ���ã */
#ifdef CPU_I386
#endif // CPU_I386
/*	ASM �ؿ��ؤΥݥ���ã����� */

/*	�ե饰Ū����ã */
	/* internal variables */
	unsigned char	mode;		/* mode = STEREO, JOINT_STEREO, MONO */
	unsigned char	version;                    /* 0=MPEG-2  1=MPEG-1  (2=MPEG-2.5)     */
    unsigned char	lame_encode_init;     
	unsigned char	noise_shaping;      /* 0 = none 1 = ISO AAC model (2 = allow scalefac_select=1) */
	unsigned char	noise_shaping_amp;	/*  0 = ISO model: amplify all distorted bands
											1 = amplify only most distorted band
											2 = amplify bands using? 
											3 = amplify bands using? */ 
	unsigned char	noise_shaping_stop;	/*	0 = stop at over=0, all scalefacs amplified or
												a scalefac has reached max value
											1 = stop when all scalefacs amplified or        
												a scalefac has reached max value
											2 = stop when all scalefacs amplified  */
	unsigned char	use_best_huffman;	/* 0 = no. 1=outside loop */
	unsigned char	use_filtering;		/* 0 = no. 1=filtering(lowpass or highpass or both) */
	unsigned char	use_psy;			/* 0 = no. 1=psychoacoustic model */
	/* VBR control */
    char	VBR;
	signed char	bWriteVbrTag;
	char	bWriteLameTag;
	/* etc */
	char	debug;
	char	silent;
	unsigned char	dummybyte1;
	unsigned char	dummybyte2;
//	unsigned char	dummybyte3;
/*	�ե饰Ū����ã����� */

/*	-v �� -q ���ץ����ˤ�äƤϥ��󥳡�����˻��Ѥ������ã */
	/*
	 * set either brate>0  or compression_ratio>0, LAME will compute
     * the value of the variable not set.
     * Default is compression_ratio = 11.025
     */
	int brate;              /* bitrate */

	int VBR_min_bitrate;            /* min bitrate index */ // RO
	int VBR_max_bitrate;            /* max bitrate index */ // RO

	float VBR_dbQ;
/*	-v �� -q ���ץ����ˤ�äƤϥ��󥳡�����˻��Ѥ������ã����� */

/*	����¾����ˤ�äƤϥ��󥳡�����˻��Ѥ������ã */
	// int fill_buffer_resample_init; // ����̤���� resampling �����������褹�뤫��
//	int encFreqHz;
//	int outFreqHz;

  /* polyphase filter */
  FLOAT8 amp_lowpass[32]; // 128 bytes
  FLOAT8 amp_highpass[32]; // 128 bytes
  int lowpass_band;          /* zero bands >= lowpass_band in the polyphase filterbank */  // RO
  int highpass_band;         /* zero bands <= highpass_band */  // RO
  int lowpass_start_band;    /* amplify bands between start */  // RO
  int lowpass_end_band;      /* and end for lowpass */ // RO
  int highpass_start_band;   /* amplify bands between start */ // RO
  int highpass_end_band;     /* and end for highpass */ // RO

	/* CPU */
#ifdef CPU_I386
	int originalFpuState;
#endif // CPU_I386
/*	����¾����ˤ�äƤϥ��󥳡�����˻��Ѥ������ã����� */

	/*	�� IO ��Ϣ̤�����ѿ� */
	//	SUBBAND_FILTER_FUNC	subband_filter;
} RO_t;

/**
 * the following variables are for only Beging and Ending of encode
 * �����ѿ��Ͻ������������λ�����ǤΤ߻Ȥ���
 */
typedef struct be_t {
	int	quality;	/* 2:slow, 5:default, 7:fast */

	int inpFreqHz;
	int rateKbps;
	int CBR_bitrate;

	/* CPU */
	int unit;

	/* VBR control */
    int VBR_q;
    int VBR_min_bitrate_kbps;
    int VBR_max_bitrate_kbps;

	/* file */
	char inFileName[MAX_FILE_LEN];
	char outFileName[MAX_FILE_LEN];

	/* VBR tag */
	int nZeroStreamSize;
	int TotalFrameSize;

	/* RIFF RMP */
	RiffInfo_t riffInfo;

	/* for MC_ADDTAG */
	Addtag_t addtagInfo;

	// ���Τ������ɬ�פʤΡ� --> �ӥåȥ졼�Ȥ˱����ƥե��륿�Υ��åȥ����ͤ����ꤹ��ɬ�פ�����Τ��פ� 
    /* resampling and filtering */
    int lowpassfreq;        /* freq in Hz. 0=gogo choses.  -1=no filter  */
    int highpassfreq;       /* freq in Hz. 0=gogo choses.  -1=no filter  */
    int lowpasswidth;       /* freq width of filter, in Hz (default=15%) */
    int highpasswidth;      /* freq width of filter, in Hz (default=15%) */

	/* lowpass and highpass filter control */
	float lowpass1,lowpass2;        /* normalized frequency bounds of passband */  // RO
	float highpass1,highpass2;      /* normalized frequency bounds of passband */  // RO

	/*	�� IO ��Ϣ */
 	OPEN_INPUT_DEVICE_FUNC	open_input_device;
	CLOSE_DEVICE_FUNC		close_input_device;

	OPEN_INPUT_DEVICE_FUNC	open_input_format;
	OPEN_INPUT_DEVICE_FUNC	open_input_filters[16];
	int						input_filter_count;

	OPEN_OUTPUT_DEVICE_FUNC	open_output_device;
	SEEK_TOP_OUTPUT_DEVICE_FUNC	seek_top_output_device;
	CLOSE_DEVICE_FUNC		close_output_device;

	OPEN_OUTPUT_DEVICE_FUNC	open_output_format;
} BE_t;

/**
 * �����ѿ��ϥ��󥳡�������ѿ��Ǥ��� 
 * �ޥ������åɥ��󥳡��ɤΤȤ��϶�ͭ������֤����٤��ѿ��Ǥ��� 
 * ���饤���Ȥ䥭��å����������� 
 */
typedef struct rw_t {
	/* variables for newmdct.c */
	float	subband_buf[2][18][SBLIMIT];	/* PFB -> MDCT(shared part) */
	short	sample_buf[2*2*1152];	/* sample input -> shiftin(shared part) */
	/* psymodel.c */
	FLOAT	cw[HBLKSIZE*4]; // shared ��¾OK
	III_psy_xmin	thm[4]; // shared ��¾OK
	III_psy_xmin	en[4];  // shared ��¾OK
	float	tot_ener[4];	// shared
	/* ratios  */
	float	pe[4]; // shared ��¾OK
	float	nb_12[4][CBANDS*2];/* 2i=>nb_1, 2i+1=>nb_2 */	// shared ��¾OK

	short	*fr0, *fr1, *fr2, *fr3; // shared

  /*  
   * Some remarks to the Class_ID field:
   * The Class ID is an Identifier for a pointer to this struct.
   * It is very unlikely that a pointer to lame_global_flags has the same 32 bits 
   * in it's structure (large and other special properties, for instance prime).
   *
   * To test that the structure is right and initialized, use:
   *     if ( gfc -> Class_ID == LAME_ID ) ...
   * Other remark:
   *     If you set a flag to 0 for uninit data and 1 for init data, the right test
   *     should be "if (flag == 1)" and NOT "if (flag)". Unintended modification
   *     of this element will be otherwise misinterpreted as an init.
   */
  
	unsigned int	num_samples_read; // shared
	unsigned int	num_samples_padding;
	int		num_samples_to_encode;  // shared

	int frameNum;                   /* number of frames encoded             */ // shared
	int totalframes; // shared

	/* psycho acoustics */
  FLOAT8 ms_ratio[2];  // shared
  /* used for padding */
  int slot_lag; // shared(modefied in lame_encode_mp3_frame()) ��¾OK

  /* variables used by quantize.c */
  int OldValue[2]; // shared	quantize.c
  int CurrentStep; // shared	quantize.c

  char bv_scf[576]; // shared	takehiro.c
  
  int sfb21_extra; /* will be set in lame_init_params */  // shared	quantize.c, quantize_pvt.c
  
  Header_buf_t	header[MAX_HEADER_BUF]; // shared
  Header_buf_t	*h_ptr; // shared
  Header_buf_t	*w_ptr; // shared

  int ancillary_flag; // shared
  

// �����ޤ���¾����OK
/* �����
	ResvSize ���ޥ���
*/

	Bit_stream_struc   bs;  // shared ��¾OK
  int ResvSize; /* in bits */ // shared	ResvFrameBegin(), ResvMaxBits()�ǻ��ȡ�ResvAdjust(), ResvFrameEnd(), bitstream.c���ѹ�
  int ResvMax;  /* in bits */ // shared ��¾OK(mutex_mp3out, mutex_l3enc����¾���뤳��)
	int	main_data_begin;	// shared ��¾OK(mutex_mp3out, mutex_l3enc����¾���뤳��)

  /* DATA FROM PSYMODEL.C */
/* The static variables "r", "phi_sav", "new", "old" and "oldest" have    */
/* to be remembered for the unpredictability measure.  For "r" and        */
/* "phi_sav", the first index from the left is the channel select and     */
/* the second index is the "age" of the data.                             */

  
  /* unpredictability calculation
   */
  Abr_t sav[2][6][4]; /* 6 = cw_lower_idx */ // shared ��¾OK


  FLOAT8 ms_ratio_s_old,ms_ratio_l_old; // shared ��¾OK

  /* block type */
  int	blocktype_old[2]; // shared ��¾OK(psysse.nas���int�Ȥ��ƻȤäƤ�)

  ATH_t	ATH;   // all ATH related stuff // RO ����VBR����RW�����

	/*	�� IO ��Ϣ */
	size_t		OutputDoneSize;
#ifdef	MT_ENCODER
	/* mutex */
#define	MAX_CRITICAL_REGION	9
	gogo_mutex	mutex[MAX_CRITICAL_REGION];

#define SEMAPHORE_STARTENCODE	0
#define SEMAPHORE_GETPCM_IN		1
#define SEMAPHORE_GETPCM_OUT	2
#define MAX_SEMAPHORE			3
	gogo_semaphore semaphore[MAX_SEMAPHORE];

/*	gogo_thread_data *end_tl;	*/
	int trackencode_flag;
	int termencode_flag;
	int getpcm_status;
#endif

  /* VBR tag */
  VBR_seek_info_t VBR_seek_table; 
} RW_t;

#ifdef CPU_I386
// i386 �Ǥ� vars.nas ����������
extern RO_t RO;
extern RW_t RW;
#else
// i386���ʳ��Ǥ� main.c �����
EXT RO_t RO;
EXT RW_t RW;
#endif

EXT BE_t BE;

#define IS_MPEG1		(RO.version)

/* mark as original, always 1            */
#define ORIGINAL		(1)

/* mark as copyright, always 0           */
#define COPYRIGHT		(0)

/* 0=no padding, 1=always pad,
   2=adjust padding, always 2            */
#define PADDING_TYPE	(2)

/* uses:
	*15bit SIMD instructions
	*23bit fdiv
*/
#define	USE_LOW_PRECISIOIN	(8 <= BE.quality)

#endif /* GLOBAL_H_ */
