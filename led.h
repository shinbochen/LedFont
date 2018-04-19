/*
将数据横向处理
HL LK
HL LK
变为
HH LL
LL KK
*/
// 24*90 3色
#ifndef   LED_20111212_H
#define   LED_20111212_H


extern	unsigned char nVirtualLED[24*3][12];
// 16*16点阵显示160字 (16*2字节)
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
将字的点阵数据移入buffer,最多显示160字
返回字符所占用的像素长度(也就是Y的位置)
*/
int		TextOut( unsigned char *pText, unsigned char nLen, unsigned char nColor );
/*
取单色显示区域的某一点
*/
bool		  GetSPoint(unsigned char *p, int x, int y );
void		  SetCPoint(unsigned char *p,int x, int y, char nColor );
/*
设置COLOR显示区哉的某一点
*/
/*
将textpanle的数据移位至显示缓存
输入参数
1: 开始的列数  (0-MAX_TEXT_BIT)
2: 移入的总列数
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
