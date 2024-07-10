// HSGdiplusDraw.h: interface for the CHSGdiplusDraw class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_HSGDIPLUSDRAW_H__908ACF29_2C0A_40CF_BB7E_A4279BB232C2__INCLUDED_)
#define AFX_HSGDIPLUSDRAW_H__908ACF29_2C0A_40CF_BB7E_A4279BB232C2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

enum VIDEOSHOW_QUALITY
{
    VIDEOSHOW_QUALITY_LOW,             // ��Ƶ������
    VIDEOSHOW_QUALITY_DEFAULT,         // ��Ƶ����Ĭ��
    VIDEOSHOW_QUALITY_HIGH             // ��Ƶ������
};

class CHSGdiplusDraw
{
public:
	CHSGdiplusDraw();
	CHSGdiplusDraw(const CHSGdiplusDraw &hDraw);
	CHSGdiplusDraw operator = (const CHSGdiplusDraw &hDraw);
	CHSGdiplusDraw(int iWidth, int iHeight, int iPixelFormat = PixelFormat32bppARGB);
	virtual ~CHSGdiplusDraw();

	static BOOL GetEncoderClsid(const WCHAR *pFormat, CLSID *pCLSID);
	static void SaveJPGImage(const TCHAR *pszPath, const LPBITMAPINFO lpBitmap, void *pData);

    void ShowVideo(CDC *pDC, CRect &rect);
	void ZoomImage(CDC *pDC, CRect &rect, float fZoom, int iX, int iY);
    
	void DrawLine(int iStartX, int iStartY, int iEndX, int iEndY);
	void DrawLine(const CPoint &startPt, const CPoint &endPt, COLORREF crColor, int iLineWidth);
	void DrawLineWithCap(const CPoint &startPt, const CPoint &endPt, COLORREF crColor, int iLineWidth, LineCap cap);
	
	void DrawRectangle(const CRect &drawRect, COLORREF crPenColor, int iWidth);
	void DrawRectangle(int iX, int iY, int iWitdh, int iHeight, COLORREF crPenColor, int iWidth);
	
	void DrawPoint(int iX, int iY);
	void DrawPoint(int iX, int iY, COLORREF crColor);
	
	void DrawRect(const CRect &drawRect,COLORREF crPenColor, COLORREF crBrushColor);
    
    void DrawString(const char *pszText, const CPoint &ptPosition, COLORREF crColor, int iSize);
    
    void DrawImage(const LPBITMAPINFO lpBitmap, void *pData, const CRect &drawRect);
    void DrawImage(const HBITMAP &hBitmap, const CRect &drawRect);
	void DrawImage(const char *pszPath, const CRect &drawRect);
	//�˺���Ϊ͸�����ͼƬ,crTransColor-͸��ɫ(Ҫ���˵���ɫ)
	void DrawImage(const HBITMAP &hBitmap, const CRect &drawRect, COLORREF crTransColor);

    void SetVideoQuality(int iQuality);	
	void SaveGdiBmpToJpg(const TCHAR *pszPath);
	BOOL SaveGdiBmpZoomToJpg(const TCHAR *pszPath, int iZoomW, int iZoomH);

private:
    // GDI+����
    Bitmap *m_pBigBitmap;                 // ��Ӧ������Ƶ��ʾ����ͼ��
    Graphics *m_pBigPicShow;              // ����������Ƶ��ʾ����GDI����
	
//  CLSID m_SaveCLSID;                  // ����jpgͼƬ�ı���

};

#endif // !defined(AFX_HSGDIPLUSDRAW_H__908ACF29_2C0A_40CF_BB7E_A4279BB232C2__INCLUDED_)
