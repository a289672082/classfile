
#ifdef MYBMP_H
#define  MYBMP_H
#endif


HBITMAP plIamgeToDIB(IplImage *pImg,int Size)  ;//������SIZE=1
IplImage* hBitmap2Ipl(HBITMAP hBmp);
IplImage* hBitmap3Ipl(HBITMAP hBmp);
IplImage* hBitmapToIpl(HBITMAP hBmp);//�Ϻ���
HBITMAP Hdc2Hbitmap(HDC hDC,DWORD BitWidth, DWORD BitHeight);
bool SaveBMPToFile(HBITMAP hBitmap, char*  lpFileName) ;//hBitmap Ϊ�ղŵ���Ļλͼ���,lpFileName Ϊλͼ�ļ���


/*
ʾ��
IplImage* pSrcImage = pDoc->GetCVImage();
CRect r;
GetClientRect (&r);
if (pSrcImage)
{
	//  ˢ����ͼ����
	LPBITMAPINFO m_lpBmi = CtreateMapInfo(pSrcImage) ;
	if (m_lpBmi)
	{
		StretchDIBits(pDC->m_hDC,
			0, 0, pSrcImage->width, pSrcImage->height,
			0, 0, pSrcImage->width, pSrcImage->height,
			pSrcImage->imageData, m_lpBmi, DIB_RGB_COLORS, SRCCOPY);
	}
}*/
LPBITMAPINFO   CtreateMapInfo(IplImage* workImg);    //  ����λͼ��Ϣ





