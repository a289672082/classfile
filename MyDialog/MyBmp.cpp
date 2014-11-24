#include "stdafx.h"
#include<opencv\highgui.h>
#include<opencv\cv.h> 
#include <opencv2\opencv.hpp>
// HBITMAP ת��IplImage
IplImage* hBitmap2Ipl(HBITMAP hBmp)
{
	BITMAP bmp;
	::GetObject(hBmp,sizeof(BITMAP),&bmp);
	int nChannels = bmp.bmBitsPixel == 1 ? 1 : bmp.bmBitsPixel/8 ;
	int depth = bmp.bmBitsPixel == 1 ? IPL_DEPTH_1U : IPL_DEPTH_8U;
	IplImage* img = cvCreateImageHeader( cvSize(bmp.bmWidth, bmp.bmHeight)
		, depth, nChannels );
	img->imageData =
		(char*)malloc(bmp.bmHeight*bmp.bmWidth*nChannels*sizeof(char));
	memcpy(img->imageData,(char*)(bmp.bmBits),bmp.bmHeight*bmp.bmWidth*nChannels);
	return img;
}

IplImage* hBitmap3Ipl(HBITMAP hBmp)
{
	BITMAP bmp;
	::GetObject(hBmp,sizeof(BITMAP),&bmp);
	int nChannels = bmp.bmBitsPixel == 1 ? 1 : bmp.bmBitsPixel/8 ;
	int depth =bmp.bmBitsPixel == 1 ? IPL_DEPTH_1U : IPL_DEPTH_8U;
	IplImage*img = cvCreateImage( cvSize(bmp.bmWidth, bmp.bmHeight), depth,nChannels);
//	img->imageData =(char*)malloc(bmp.bmHeight*bmp.bmWidth*nChannels*sizeof(char));
	memcpy(img->imageData,(char*)(bmp.bmBits),bmp.bmHeight*bmp.bmWidth*nChannels);
	return img;
}
/*

void createDIB(IplImage* &pict){
	IplImage * Red=cvCreateImage( cvSize(IMAGE_WIDTH,IMAGE_HEIGHT),
		IPL_DEPTH_8U, 1 );
	IplImage * Green=cvCreateImage( cvSize(IMAGE_WIDTH,IMAGE_HEIGHT),
		IPL_DEPTH_8U, 1 );
	IplImage * Blue=cvCreateImage( cvSize(IMAGE_WIDTH,IMAGE_HEIGHT),
		IPL_DEPTH_8U, 1 );
	cvSetImageCOI( pict, 3);
	cvCopy(pict,Red);
	cvSetImageCOI( pict, 2);
	cvCopy(pict,Green);
	cvSetImageCOI(pict, 1);
	cvCopy(pict,Blue);
	//Initialize the BMP display buffer
	bmi = (BITMAPINFO*)buffer;
	bmih = &(bmi->bmiHeader);
	memset( bmih, 0, sizeof(*bmih));
	bmih->biSize = sizeof(BITMAPINFOHEADER);
	bmih->biWidth = IMAGE_WIDTH;
	bmih->biHeight = IMAGE_HEIGHT; // -IMAGE_HEIGHT;
	bmih->biPlanes = 1;
	bmih->biCompression = BI_RGB;
	bmih->biBitCount = 24;
	palette = bmi->bmiColors;
	for( int i = 0; i < 256; i++ ){
		palette[i].rgbBlue = palette[i].rgbGreen = palette[i].rgbRed =
			(BYTE)i;
		palette[i].rgbReserved = 0;
	}
	cvReleaseImage(&Red);
	cvReleaseImage(&Green);
	cvReleaseImage(&Blue);
}
*/
 
// HBITMAPת��DIB
HBITMAP plIamgeToDIB(IplImage *pImg,int Size)  
{  
	HDC hDC = ::CreateCompatibleDC(0);  
	BYTE tmp[sizeof(BITMAPINFO)+255*4];  
	BITMAPINFO *bmi = (BITMAPINFO*)tmp;  
	HBITMAP hBmp;  
	int i;  
	memset(bmi,0,sizeof(BITMAPINFO));  
	bmi->bmiHeader.biSize = sizeof(BITMAPINFOHEADER);  
	bmi->bmiHeader.biWidth = pImg->width;  
	bmi->bmiHeader.biHeight = -pImg->height;  
	bmi->bmiHeader.biPlanes = Size;  
	bmi->bmiHeader.biBitCount = pImg->nChannels * pImg->depth;  

	bmi->bmiHeader.biCompression = BI_RGB;  
	bmi->bmiHeader.biSizeImage = pImg->width*pImg->height*1;  
	bmi->bmiHeader.biClrImportant =0 ;  
	switch(pImg->nChannels * pImg->depth)  
	{  
	case 8 :  
		for(i=0 ; i < 256 ; i++)  
		{  
			bmi->bmiColors[i].rgbBlue = i;  
			bmi->bmiColors[i].rgbGreen= i;  
			bmi->bmiColors[i].rgbRed= i;  
		}  
		break;  
	case 32:  
	case 24:  
		((DWORD*) bmi->bmiColors)[0] = 0x00FF0000; /* red mask */ 
		((DWORD*) bmi->bmiColors)[1] = 0x0000FF00; /* green mask */ 
		((DWORD*) bmi->bmiColors)[2] = 0x000000FF; /* blue mask */ 
		break;  
	}  
	hBmp = ::CreateDIBSection(hDC,bmi,DIB_RGB_COLORS,NULL,0,0);  
	SetDIBits(hDC,hBmp,0,pImg->height,pImg->imageData,bmi,DIB_RGB_COLORS);  
	::DeleteDC(hDC);  
	return hBmp;  

} 





HBITMAP Hdc2Hbitmap(HDC hDC,DWORD BitWidth, DWORD BitHeight)
{
	HDC hBufDC;
	HBITMAP hBitmap, hBitTemp;
	//�����豸������(HDC)
	hBufDC = CreateCompatibleDC(hDC);
	//����HBITMAP
	hBitmap = CreateCompatibleBitmap(hDC, BitWidth, BitHeight);
	hBitTemp = (HBITMAP) SelectObject(hBufDC, hBitmap);
	//�õ�λͼ������
	StretchBlt(hBufDC, 0, 0, BitWidth, BitHeight,
		hDC, 0, 0, BitWidth, BitHeight, SRCCOPY);
	//�õ����յ�λͼ��Ϣ
	hBitmap = (HBITMAP) SelectObject(hBufDC, hBitTemp);
	//�ͷ��ڴ�
	DeleteObject(hBitTemp);
	::DeleteDC(hBufDC);
	return hBitmap;
}










bool SaveBMPToFile(HBITMAP hBitmap, char*  lpFileName) //hBitmap Ϊ�ղŵ���Ļλͼ���,lpFileName Ϊλͼ�ļ���
{
	HDC hDC; //�豸������
	int iBits; //��ǰ��ʾ�ֱ�����ÿ��������ռ�ֽ���
	WORD wBitCount; //λͼ��ÿ��������ռ�ֽ���
	//�����ɫ���С�� λͼ�������ֽڴ�С ��  λͼ�ļ���С �� д���ļ��ֽ���
	DWORD  dwPaletteSize=0,dwBmBitsSize,dwDIBSize, dwWritten;
	BITMAP			   Bitmap;  //λͼ���Խṹ
	BITMAPFILEHEADER   bmfHdr;  //λͼ�ļ�ͷ�ṹ
	BITMAPINFOHEADER   bi;		//λͼ��Ϣͷ�ṹ 
	LPBITMAPINFOHEADER lpbi;	//ָ��λͼ��Ϣͷ�ṹ

	HANDLE fh, hDib, hPal;
	HPALETTE hOldPal=NULL; //�����ļ��������ڴ�������ɫ����

	//����λͼ�ļ�ÿ��������ռ�ֽ���
	hDC = CreateDC(_T("DISPLAY"),NULL,NULL,NULL);
	iBits = GetDeviceCaps(hDC, BITSPIXEL) * GetDeviceCaps(hDC, PLANES);
	DeleteDC(hDC);
	if (iBits <= 1)  wBitCount = 1;
	else if (iBits <= 4) wBitCount = 4;
	else if (iBits <= 8) wBitCount = 8;
	else if (iBits <= 24) wBitCount = 24;
	else wBitCount = 32;
	//�����ɫ���С
	if (wBitCount <= 8) dwPaletteSize = (1<<wBitCount) * sizeof(RGBQUAD);

	//����λͼ��Ϣͷ�ṹ
	GetObject(hBitmap, sizeof(BITMAP), (LPSTR)&Bitmap);
	bi.biSize           =  sizeof(BITMAPINFOHEADER);
	bi.biWidth          =  Bitmap.bmWidth;
	bi.biHeight         =  Bitmap.bmHeight;
	bi.biPlanes         =  1;
	bi.biBitCount       =  wBitCount;
	bi.biCompression    =  BI_RGB;
	bi.biSizeImage      =  0;
	bi.biXPelsPerMeter  =  0;
	bi.biYPelsPerMeter  =  0;
	bi.biClrUsed        =  0;
	bi.biClrImportant   =  0;

	dwBmBitsSize = ((Bitmap.bmWidth*wBitCount+31)/32)*4*Bitmap.bmHeight; //Ϊλͼ���ݷ����ڴ�

	/*xxxxxxxx����λͼ��С�ֽ�һ��(����һ����������)xxxxxxxxxxxxxxxxxxxx 
	//ÿ��ɨ������ռ���ֽ���Ӧ��Ϊ4���������������㷨Ϊ:
	int biWidth = (Bitmap.bmWidth*wBitCount) / 32;
	if((Bitmap.bmWidth*wBitCount) % 32)
	biWidth++; //�����������ļ�1
	biWidth *= 4;//���������õ���Ϊÿ��ɨ���е��ֽ�����
	dwBmBitsSize = biWidth * Bitmap.bmHeight;//�õ���С
	xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx*/


	hDib = GlobalAlloc(GHND,dwBmBitsSize+dwPaletteSize+sizeof(BITMAPINFOHEADER));
	lpbi = (LPBITMAPINFOHEADER)GlobalLock(hDib);
	*lpbi = bi;
	// �����ɫ��   
	hPal = GetStockObject(DEFAULT_PALETTE);
	if (hPal)
	{
		hDC = ::GetDC(NULL);
		hOldPal=SelectPalette(hDC,(HPALETTE)hPal,FALSE);
		RealizePalette(hDC);
	}
	// ��ȡ�õ�ɫ�����µ�����ֵ
	GetDIBits(hDC,hBitmap,0,(UINT)Bitmap.bmHeight,(LPSTR)lpbi+sizeof(BITMAPINFOHEADER)+dwPaletteSize, (BITMAPINFO *)lpbi,DIB_RGB_COLORS);
	//�ָ���ɫ��   
	if (hOldPal)
	{
		SelectPalette(hDC, hOldPal, TRUE);
		RealizePalette(hDC);
		::ReleaseDC(NULL, hDC);
	}
	//����λͼ�ļ�    
	fh=CreateFileA(lpFileName, GENERIC_WRITE,0, NULL, CREATE_ALWAYS,FILE_ATTRIBUTE_NORMAL | FILE_FLAG_SEQUENTIAL_SCAN, NULL);
	if (fh==INVALID_HANDLE_VALUE)
		return false;
	// ����λͼ�ļ�ͷ
	bmfHdr.bfType = 0x4D42;  // "BM"
	dwDIBSize = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER) + dwPaletteSize+dwBmBitsSize;  
	bmfHdr.bfSize = dwDIBSize;
	bmfHdr.bfReserved1 = 0;
	bmfHdr.bfReserved2 = 0;
	bmfHdr.bfOffBits = (DWORD)sizeof(BITMAPFILEHEADER) + (DWORD)sizeof(BITMAPINFOHEADER) + dwPaletteSize;
	// д��λͼ�ļ�ͷ
	WriteFile(fh, (LPSTR)&bmfHdr, sizeof(BITMAPFILEHEADER), &dwWritten, NULL);
	// д��λͼ�ļ���������
	WriteFile(fh, (LPSTR)lpbi, sizeof(BITMAPINFOHEADER)+dwPaletteSize+dwBmBitsSize , &dwWritten, NULL); 
	//���   
	GlobalUnlock(hDib);
	GlobalFree(hDib);
	CloseHandle(fh);
	return true;
}





// hbitmap convert to IplImage
IplImage* hBitmapToIpl(HBITMAP hBmp)
{
	BITMAP bmp;
	GetObject(hBmp,sizeof(BITMAP),&bmp);

	// get channels which equal 1 2 3 or 4
	// bmBitsPixel :
	// Specifies the number of bits
	// required to indicate the color of a pixel.
	int nChannels = bmp.bmBitsPixel == 1 ? 1 : bmp.bmBitsPixel/8 ;

	// get depth color bitmap or grayscale
	int depth = bmp.bmBitsPixel == 1 ? IPL_DEPTH_1U : IPL_DEPTH_8U;


	// create header image
	IplImage* img = cvCreateImage(cvSize(bmp.bmWidth,bmp.bmHeight),depth,nChannels);

	// allocat memory for the pBuffer
	BYTE *pBuffer = new BYTE[bmp.bmHeight*bmp.bmWidth*nChannels];

	// copies the bitmap bits of a specified device-dependent bitmap into a buffer
	GetBitmapBits(hBmp,bmp.bmHeight*bmp.bmWidth*nChannels,pBuffer);

	// copy data to the imagedata
	memcpy(img->imageData,pBuffer,bmp.bmHeight*bmp.bmWidth*nChannels);
	delete pBuffer;

	// create the image
	IplImage *dst = cvCreateImage(cvGetSize(img),img->depth,3);
	// convert color
	cvCvtColor(img,dst,CV_BGRA2BGR);
	cvReleaseImage(&img);
	return dst;
}  








LPBITMAPINFO   CtreateMapInfo(IplImage* workImg)    //  ����λͼ��Ϣ
{                                          
	BITMAPINFOHEADER BIH={40,1,1,1,8,0,0,0,0,0,0};
	LPBITMAPINFO lpBmi;
	int          wid, hei, bits, colors,i;
	RGBQUAD  VgaColorTab[256];
	wid =workImg->width;     hei =workImg->height;
	bits=workImg->depth*workImg->nChannels;
	if (bits>8) colors=0;
	else colors=1<<bits;
	lpBmi=(LPBITMAPINFO) malloc(40+4*colors);
	BIH.biWidth   =wid;     BIH.biHeight  =hei;
	BIH.biBitCount=(BYTE) bits;
	memcpy(lpBmi,&BIH,40);                   //  ����λͼ��Ϣͷ
	if (bits==8) {                           //  256 ɫλͼ
		for (i=0;i<256;i++)  {                //  ���ûҽ׵�ɫ��
			VgaColorTab[i].rgbRed   = (BYTE) i;  
			VgaColorTab[i].rgbGreen = (BYTE) i;  
			VgaColorTab[i].rgbBlue  = (BYTE) i;  
		}
		memcpy(lpBmi->bmiColors, VgaColorTab, 1024);
	}
	return(lpBmi);
}
