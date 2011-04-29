/*
 *   part of this code is origined from
 *   GOGO-no-coda
 *
 *   Copyright(C) 2001,2002,2003 gogo-developer
 */

#ifndef THREAD_H_
#define THREAD_H_

/* �ץ�åȥۡ������¸ */

typedef void* (*gogo_thread_func)(void *); 

/*
 *	�ޥ������åɤ��б�������ϡ�
 *	���Υץ�åȥۡ���˹�碌�ưʲ��η��ȴؿ��ޤ��ϥޥ�����Ѱդ��뤳��
 *
 *	�ץ�åȥۡ����¸�η� 
 *
 *	gogo_thread	����åɾ�����Ǽ���뷿
 *	gogo_mutex	�ߥ塼�ƥå���������Ǽ���뷿
 *  gogo_semaphore ���ޥե�������Ǽ���뷿
 *
 *	�ץ�åȥۡ����¸�δؿ��ޤ��ϥޥ��� 
 *	int ���֤��ؿ������ｪλ�� 0 ���֤����۾ｪλ���� 0 ���֤����ȡ�
 *
 *	����åɴط��ν������¾�Υ���åɴط��ؿ���Ȥ����˰��٤����ƤФ�롣
 *	int gogo_initialize_thread_unit(void)
 *
 *	����åɴط��ν�λ���������٤����ƤФ�롣�����Ƥ���塢¾�Υ���åɴؿ�����Ƥ�ǤϤ����ʤ���
 *	int gogo_finalize_thread_unit(void)
 *
 *	����åɤ��������롣
 *	int gogo_create_thread(gogo_thread* pthread, gogo_thread_func func, void *data)
 *
 *	����åɤν�λ���Ԥġ�
 *	int gogo_join_thread(gogo_thread* pthread)
 *
 *	����åɤ��˴����롣�˴��������˽�λ���ԤĤ��ȡ�
 *	int gogo_destroy_thread(gogo_thread* pthread)
 *
 *	�ߥ塼�ƥå������������롣
 *	�Ƶ��ߥ塼�ƥå������ɤ����ϥץ�åȥۡ����¸�ʤΤǡ��Ƶ����ɤ����˰�¸���ʤ��褦�˻Ȥ����ȡ�
 *	int gogo_create_mutex(gogo_mutex* pmutex)
 *
 *	�ߥ塼�ƥå������˴����롣
 *	int gogo_destroy_mutex(gogo_mutex* pmutex)
 *
 *	�ߥ塼�ƥå�����������롣��������Ǥ���ޤǱʱ���Ԥġ�
 *	int gogo_lock_mutex(gogo_mutex* pmutex)
 *
 *	�ߥ塼�ƥå�����������롣
 *	int gogo_unlock_mutex(gogo_mutex* pmutex)
 *
 *	���ޥե����������롣
 *	�����0��2�ͥ��ޥե���
 *  int gogo_create_semaphore(gogo_semaphore* pSemaphore)
 *
 *	���ޥե����˴����롣
 *  int gogo_destroy_semaphore(gogo_semaphore* pSemaphore)
 *
 *	���ޥե���������롣��������Ǥ���ޤǱʱ���Ԥġ�
 *  int gogo_lock_semaphore(gogo_semaphore* pSemaphore)
 *
 *	���ޥե���������롣
 *  int gogo_unlock_semaphore(gogo_semaphore* pSemaphore)
 *
 *	���ޥե���������롣�����Ǥ���ޤ� timeout �ߥ����Ԥġ�
 *  �����Ǥ����� 0 ���֤������顼�ޤ��� timeout �����顢��0���֤���
 *  int gogo_trylocktimeout_semaphore(gogo_semaphore* pSemaphore, int timeout)
 *
 *	¾�Υ���åɤ˼¹Ը���Ϳ���롣
 *  void gogo_yield_thread()						
 *
 *	CPU �ο��� *pCPUs �ˡ��������륹��åɿ��� *pTHREADs ���֤���
 *	�狼��ʤ�����ξ��ɬ��1�ˤ��뤳�ȡ�
 *	int gogo_get_cpu_count(int *pCPUs, int *pTHREADs)
 *
 *	����åɥ�����ǡ�����¤�Τ��֤������ѿ�������С�
 *	������� GOGO_THREAD_VARIABLES ��������Ƥ���������
 *
 */

#define	MT_ENCODER

#if		defined(USE_WINTHREAD)
#  include	"../win/thread_win.h"
#elif	defined(USE_PTHREAD)
#  include	"../pthread/thread_pthread.h"
#elif defined(USE_BTHREAD)
#  include	"../be/thread_be.h"
#elif defined(USE_OS2THREAD)
#  include	"../os2/thread_os2.h"
#elif defined(USE_RFORK)
#  include	"../rfork/thread_rfork.h"
#else
#  undef	MT_ENCODER
#  define	ST_ENCODER
#  define	gogo_get_cpu_count(pCPU,pTHREADs) ((*(pCPU)=1),(*(pTHREADs)=1),0)
#endif

typedef unsigned int uint32;

/**
 * �ץ�åȥۡ������¸�������ѿ�
 */
typedef struct gogo_thread_data_s {
/* �ץ�åȥۡ������¸�������ѿ� */
	float	mfbuf[2][4][576];	/* ->FFT, ->PFB */

  /* variables for newmdct.c */
        float	(*sb[4])[18][SBLIMIT];
        float	sb_sample[3][2][18][SBLIMIT];  /* PFB -> MDCT */

        float	xr[2][2][576];         /* MDCT -> Non-Linear Quantization  */
	uint32	xr_sign[2][2][576];

        float	xrpow[2][2][576];      /* Non-Linear Quantization -> Iteration Loop */
	float	work_xrpow[576]; //, save_xrpow[576], best_xrpow[576];	/* quantize.c */
        float	xrpow_sum[2][2];
        float	xrpow_max[2][2];

	int	l3_enc[2][2][576];
	III_scalefac_t	scalefac[2][2];

	int	ath_over[2][2];		/* calc_xmin() -> calc_noise() */
	III_psy_xmin	l3_xmin[2][2];	/* calc_xmin() -> calc_noise() */

	/* fft and energy calculation    */
        float	wsamp_L[2 /*granule*/][2 /*channel*/][BLKSIZE];     /* fft() -> L3psycho_anal() */
        float	wsamp_S[2 /*granule*/][2 /*channel*/][3][BLKSIZE_s];/* fft() -> L3psycho_anal() */
/* BLKSIZE=1024, BLKSIZE_s = 256 => max(BLKSIZE,BLKSIZE_s*3) = 1024 */
//		float	psywork[BLKSIZE*4];		/* wsampl_{L,S} 4��ʬ(energy�ȶ��Ѥ����ۤ����褤��?) */
		float	psywork[576*2*4*4];		/* FFT�Ǥ�work(576*2*4*4*4byte)�Ȥ��ƻȤ� */
		                                /* ��̿���Ťʤ�ʤ� quantize.c �� distort �Ǥⶦ�Ѥ��ƻȤ� */
        float	energy[HBLKSIZE*4];              /* �ΰ��4�ܤˤ����FFT��ˤޤȤ�ƽ�����ǽ */
        float	energy_s[3][HBLKSIZE_s*4];       /* �ΰ��4�ܤˤ����FFT��ˤޤȤ�ƽ�����ǽ */

	/* psycho acoustics */
	float	tot_ener[4];	/* private copy of RW.tot_ener */
	III_side_info_t	l3_side;

/* �ץ�åȥۡ����¸����åɥ������ѿ� */
#ifdef GOGO_THREAD_VARIABLES
	GOGO_THREAD_VARIABLES;
#endif

/* ���饤���ȴط��ʤ���ΤϤ������鲼�� */
	struct gogo_thread_data_s	*next;
	void	*unaligned;
	int	tid;

	int	padding;		  /* padding for the current frame? */
	int	mode_ext;

	int	bitrate_index;
	int	ResvSize;

	// WMP6.4�б��Τ��� ancillary ���ä� part2_3_length ���ɲä��Ƥ���Τ�����
	// �����ɲä���ӥåȿ�
	int additional_part2_3_length[2 /*granule*/][2 /*channel*/]; 

#ifdef	MT_ENCODER
	int	exit_status;
	gogo_thread	thread;
	gogo_mutex	*critical_region;
#endif
} gogo_thread_data;	// <- gogo2��encodeframe_arg_t����

#endif // THREAD_H_

