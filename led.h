/*
�����ݺ�����
HL LK
HL LK
��Ϊ
HH LL
LL KK
*/
// 24*90 3ɫ
#ifndef   LED_20111212_H
#define   LED_20111212_H


extern	unsigned char nVirtualLED[24*3][12];
// 16*16������ʾ160�� (16*2�ֽ�)
#define 	MAX_TEXT			160*2
#define		MAX_TEXT_BIT		MAX_TEXT*8
#define		MAX_TRUE_LED_BYTE	9*90

extern	unsigned char nTextPanel[16][MAX_TEXT];


enum{
	LED_BLACK = 0,
	LED_BLUE,	// 001
	LED_GREEN,
	LED_CYAN,
	LED_RED,
	LED_FUCHSIN,
    LED_YELLOW,
	LED_WHITE
};
extern unsigned char  gFontColor;

extern unsigned char  BIT[8];

unsigned int  HConvertV( unsigned char *pDest, unsigned char *pSrc, unsigned char nL, unsigned char nH );
unsigned int  HConvertV_2( unsigned char *pDest, unsigned char *pSrc, int nLen );
/*
���ֵĵ�����������buffer,�����ʾ160��
�����ַ���ռ�õ����س���(Ҳ����Y��λ��)
*/
int		TextOut( unsigned char *pText, unsigned char nLen, unsigned char nColor );
/*
ȡ��ɫ��ʾ�����ĳһ��
*/
bool		  GetSPoint(unsigned char *p, int x, int y );
void		  SetCPoint(unsigned char *p,int x, int y, char nColor );
/*
����COLOR��ʾ���յ�ĳһ��
*/
/*
��textpanle��������λ����ʾ����
�������
1: ��ʼ������  (0-MAX_TEXT_BIT)
2: �����������
3: color
4: 
_________________
| B B
|
|
|
|
|

*/

void TextMove( unsigned char *pDest, int x1, int y1,	int x1Max, int y1Max,
			   unsigned char *pSrc, int x2, int y2,  int	x2Max, int y2Max, unsigned char nColor );

bool  GetGBCodeToLedData( unsigned char *pDest,  unsigned char *pSrc);
#endif //   LED_20111212_H
