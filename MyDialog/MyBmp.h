
#ifdef MYBMP_H
#define  MYBMP_H
#endif


HBITMAP plIamgeToDIB(IplImage *pImg,int Size)  ;//可用用SIZE=1
IplImage* hBitmap2Ipl(HBITMAP hBmp);
IplImage* hBitmap3Ipl(HBITMAP hBmp);
IplImage* hBitmapToIpl(HBITMAP hBmp);//较好用
HBITMAP Hdc2Hbitmap(HDC hDC,DWORD BitWidth, DWORD BitHeight);
bool SaveBMPToFile(HBITMAP hBitmap, char*  lpFileName) ;//hBitmap 为刚才的屏幕位图句柄,lpFileName 为位图文件名


/*
示例
IplImage* pSrcImage = pDoc->GetCVImage();
CRect r;
GetClientRect (&r);
if (pSrcImage)
{
	//  刷新视图窗口
	LPBITMAPINFO m_lpBmi = CtreateMapInfo(pSrcImage) ;
	if (m_lpBmi)
	{
		StretchDIBits(pDC->m_hDC,
			0, 0, pSrcImage->width, pSrcImage->height,
			0, 0, pSrcImage->width, pSrcImage->height,
			pSrcImage->imageData, m_lpBmi, DIB_RGB_COLORS, SRCCOPY);
	}
}*/
LPBITMAPINFO   CtreateMapInfo(IplImage* workImg);    //  建立位图信息





