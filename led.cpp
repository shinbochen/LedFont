
#include "StdAfx.h"
#include "led.h"
//////////////////////////////////////////////////////////////////////////
// 24*90 3ɫ
unsigned char	nVirtualLED[24*3][12];
unsigned char   nTextPanel[16][MAX_TEXT];


unsigned char	gFontColor = 0;
unsigned char	BIT[8]={0x01,0x02,0x04,0x08,0x10,0x20,0x40,0x80};

//////////////////////////////////////////////////////////////////////////
//�����ݺ�����
//HL LK
//HL LK
//��Ϊ
//HH LL
//LL KK
// nMaxΪ���ת���ֽ�
unsigned int  HConvertV( unsigned char *pDest, unsigned char *pSrc, unsigned char nL, unsigned char nH ){

	int 				nLen;
	unsigned char 		l,h;
	unsigned char		*pData;
	
	nLen = 0;
	pData = (unsigned char*)malloc(nH);	
	
	for( l = 0; l < nL; l++ ){		
		for( h = 0; h < nH; h++ ){
			*(pData+h) = *(pSrc+(h*nL)+l);
		}		
		nLen += HConvertV_2( pDest+nLen, pData, nH );
	}
	if( pData ){
		free(pData);
	}
	return nLen;
}
//////////////////////////////////////////////////////////////////////////
//
unsigned int HConvertV_2( unsigned char *pDest, unsigned char *pSrc, int nLen ){
	
	unsigned char 		l,i;
	unsigned char		nTmp,nData;
	unsigned char		nBit;
	unsigned int		nCnt;
	
	
	nData = 0;
	nCnt = 0;
	nBit = 0;

	
	for( l = 0; l < 8; l++ ){
		for( i = 0; i < nLen; i++ ){
			nTmp = *(pSrc+i);
			if( nTmp & BIT[7-l] ){
				nData |= BIT[nBit];
			}
			nBit++;
			if( nBit == 8){
				*(pDest+nCnt++) = nData;
				nBit = 0;
				nData = 0;
			}
		}		
	}	
	if( nBit != 0 ){
		*(pDest+nCnt++) = nData;

	}
	return nCnt;
}
//////////////////////////////////////////////////////////////////////////
// ���ֵĵ�����������buffer,�����ʾ160��
// ������ռ�õ����س���(Ҳ����Y��λ��)
int		TextOut( unsigned char *pText, unsigned char nLen, unsigned char nColor ){
	
	int							nCnt = 0;
	unsigned int				nChar = 0;
	int							nCnt2 = 0;
	unsigned char 				nFont[32];
	unsigned char				*pFont = NULL;
	
	gFontColor = nColor;
	if( nLen >= 160 ){
		nLen = 160;
	}	
	memset( nTextPanel, 0x00, sizeof( nTextPanel ) );
	for( nCnt = 0; nCnt < nLen;  ){
		
		if( *(pText+nCnt) > 128 ){
			GetGBCodeToLedData( nFont, pText+nCnt);
			pFont = &nFont[0];
			nCnt += 2;
			for( unsigned char i = 0; i < 16; i++ ){
				nTextPanel[i][nCnt2] = *pFont++;
				nTextPanel[i][nCnt2+1] = *pFont++;
			}
			nCnt2+=2;	
		}
		else{
			if( *(pText+nCnt) > 0x00 ){
				GetGBCodeToLedData( nFont, pText+nCnt);
				pFont = &nFont[0];
				nCnt++;
					
				for( unsigned char i = 0; i < 16; i++ ){
					nTextPanel[i][nCnt2] = *pFont++;
				}
			}
			nCnt2++;
		}
	}
	return nCnt2*8;
}
//////////////////////////////////////////////////////////////////////////
//
bool GetSPoint( unsigned char *p, int x, int y ){
	
	int						xbyte = 0;
	unsigned char xbit;
	
	xbyte = x/8;	
	xbit = x%8;
	
	if( (*(p+y*MAX_TEXT+xbyte)) & BIT[7-xbit] ){
		return true;
	}
	return false;
	
}
//////////////////////////////////////////////////////////////////////////
//
// ����COLOR��ʾ���յ�ĳһ��
void SetCPoint( unsigned char *p, int x, int y, char nColor ){
	
	int				xbyte,ybyte;
	unsigned char	xbit;

	xbyte = x/8;
	xbit = x%8;
	//ybyte = y;
	ybyte = y*3;
	
	if( nColor&BIT[0] ){
		*(p+ybyte*12+xbyte) |= BIT[7-xbit];
	}
	else{
		*(p+ybyte*12+xbyte)	&= (~BIT[7-xbit])&0xFF;
		
	}
	if( nColor&BIT[1] ){
		*(p+(ybyte+1)*12+xbyte)	|= BIT[7-xbit];
	}
	else{
		*(p+(ybyte+1)*12+xbyte)	&= (~BIT[7-xbit])&0xFF;
		
	}
	if( nColor&BIT[2] ){
		*(p+(ybyte+2)*12+xbyte)	|= BIT[7-xbit];
	}
	else{
		*(p+(ybyte+2)*12+xbyte)	&= (~BIT[7-xbit])&0xFF;		
	}
	return;	
}
//////////////////////////////////////////////////////////////////////////
//
//0, 4, 90,     24, 
//0, 0, 160*2*8,16
//��textpanle��������λ����ʾ����
//�������
//1: ��ʼ������  (0-MAX_TEXT_BIT)
//2: �����������
//3: color
//4:
//_________________
//| B B
//|
//|
//|
//|
//|
//ȡ��ɫ��ʾ�����ĳһ��

void TextMove( unsigned char *pDest, int x1, int y1,	int x1Max, int y1Max,
			   unsigned char *pSrc, int x2, int y2,  int	x2Max, int y2Max, unsigned char nColor ){
	
	int		ix1,ix2,iy1,iy2;

	for( ix1=x1, ix2=x2; (ix1<x1Max)&&(ix2<x2Max); ix1++,ix2++ ){
	
		for( iy1=y1, iy2=y2; (iy1<y1Max)&&(iy2<y2Max); iy1++,iy2++ ){
	
		
			if( GetSPoint( pSrc, ix2, iy2 ) ){
				SetCPoint(pDest, ix1, iy1, nColor );
			}
			else{
				//SetCPoint(pDest, ix1, iy1, LED_BLACK );				
			}	
		}	
	}
}	