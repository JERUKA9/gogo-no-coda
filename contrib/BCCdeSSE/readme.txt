
2001 Oct. 9

fixu32.c alignes variables to 16bytes for SSE insted of BCC-linker,
which is programmed by Sava.

usage:
	fixu32 [-u] [-c] [-padding16] [-padding32] [-v] objfile [output_objfile]
	   -u   	Update objfile
	   -c   	validate Checksum
	   -padding16	force segment length aligned by 16bytes
	   -padding32	                     aligned by 32bytes
	   -v   	Verbose mode


���Υץ�����16byte alignment�����꤬�Ǥ��ʤ�BCC�����ä�
obj����Ū�˽񤭴����뤳�Ȥ�SSE���б�������ץ����Ǥ���
����� ���� ����ˤ���ޤ���

ư�����Ϥ���ޤ���������̵�ݾڤǤ��ΤǼ��ʤ���Ǥ�ˤ��������Ѥ��Ƥ���������
