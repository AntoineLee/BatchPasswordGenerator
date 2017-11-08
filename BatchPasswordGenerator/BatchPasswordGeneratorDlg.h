// BatchPasswordGeneratorDlg.h : ͷ�ļ�
//

#pragma once
#include "afxcmn.h"
#include "afxwin.h"


// CBatchPasswordGeneratorDlg �Ի���
class CBatchPasswordGeneratorDlg : public CDialog
{
// ����
public:
	CBatchPasswordGeneratorDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_BATCHPASSWORDGENERATOR_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��
    CToolTipCtrl m_Tip;

// ʵ��
protected:
	HICON m_hMaxIcon;
    HICON m_hMinIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
    // ������ʾ����
    CSliderCtrl m_wndSliderItem;
public:
    virtual BOOL PreTranslateMessage(MSG* pMsg);
public:
    // ��Ҫ���ɵ�����λ��
    UINT m_nItemData;
public:
    afx_msg void OnEnKillfocusEdit1();
public:
    afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
public:
    afx_msg void OnEnUpdateEdit1();
    //************************************    
    // �������ƣ�GetDigitalData    
    // ����˵������ȡ�������    
    // �������ߣ�Robin    
    // �������ڣ�2015/04/12    
    // �� �� ֵ��    
    // ��    ��:     
    //************************************    
    int GetDigitalData(int nBit);

    //************************************    
    // �������ƣ�DataMaxLetter();    
    // ����˵�������ɴ�д��ĸ�����ĸ    
    // �������ߣ�Robin    
    // �������ڣ�2015/04/12    
    // �� �� ֵ���ַ�    
    // ��    ��:     
    //************************************    
    UCHAR DataMaxLetter();
    
    //************************************    
    // �������ƣ�DataMaxLetter();    
    // ����˵��������Сд��ĸ�����ĸ    
    // �������ߣ�Robin    
    // �������ڣ�2015/04/12    
    // �� �� ֵ���ַ�    
    // ��    ��:     
    //************************************    
    UCHAR DataMinLetter();
    
    //************************************    
    // �������ƣ�DataCharacter();    
    // ����˵������������ַ�    
    // �������ߣ�Robin    
    // �������ڣ�2015/04/12    
    // �� �� ֵ���ַ�    
    // ��    ��:     
    //************************************    
    UCHAR DataCharacter();
    
    //************************************    
    // �������ƣ�DataDigitalChar    
    // ����˵������ȡ�����ַ�    
    // �������ߣ�Robin    
    // �������ڣ�2015/04/12    
    // �� �� ֵ��    
    // ��    ����    
    //************************************    
    UCHAR DataDigitalChar();

    //************************************    
    // �������ƣ�GetPasswordBit    
    // ����˵������ȡ�����λ��    
    // �������ߣ�Robin    
    // �������ڣ�2015/04/12    
    // �� �� ֵ��    
    // ��    ��:     
    //************************************    
    int GetPasswordBit();
    


public:
    afx_msg void OnBnClickedNew();
public:
    // ������ʾλ��
    CEdit m_wndPassword;
public:
    // Сд��ĸ
    BOOL m_bMinLetter;
public:
    // ��д��ĸ
    BOOL m_bMaxLetter;
public:
    //������Ҫ���ļ���·��
    CString m_strFilePath;
public:
    // ����
    BOOL m_bDigital;
public:
    // �����ַ�
    BOOL m_bSpecialChar;
public:
    CEdit m_wndEdit1;
public:
    afx_msg void OnBnClickedMinletter();
public:
    afx_msg void OnBnClickedMaxletter();
public:
    afx_msg void OnBnClickedDigital();
public:
    afx_msg void OnBnClickedSpecialchar();
public:
    // ��������ʱ��Ľ�����
    CProgressCtrl m_wndProgress;
public:
    // ��ȡ�������ɵ�����
    CEdit m_wndBatchData;
public:
    CButton m_wndOpenFile;
public:
    CButton m_wndCreateData;
    //************************************    
    // �������ƣ�JudgeBatch    
    // ����˵�����ж��Ƿ���������������    
    // �������ߣ�Robin    
    // �������ڣ�2015/04/12    
    // �� �� ֵ��    
    // ��    ����    
    //************************************    
    void JudgeBatch();
public:
    // �Ƿ���������������
    BOOL m_bBatch;
public:
    afx_msg void OnBnClickedBatch();
public:
    // �������밴ť
    CButton m_wndNew;
public:
    CButton m_wndCopy;
public:
    afx_msg void OnBnClickedOpenfile();
    //************************************    
    // �������ƣ�Write    
    // ����˵����д�������    
    // �������ߣ�Robin    
    // �������ڣ�2015/04/12    
    // �� �� ֵ��    
    // ��    ����    
    //************************************    
    void Write(CString& strText);
public:
    afx_msg void OnBnClickedCopy();

    //************************************    
    // �������ƣ�ThreadProc    
    // ����˵����MFC�����̴߳�����    
    // �������ߣ�Robin    
    // �������ڣ�2015/04/12    
    // �� �� ֵ��    
    // ��    ����    
    //************************************    
    static UINT ThreadProc(LPVOID pParam);

    //************************************    
    // �������ƣ�GetPassword()    
    // ����˵������ȡ�������    
    // �������ߣ�Robin    
    // �������ڣ�2015/04/12    
    // �� �� ֵ�����ɺ������    
    // ��    ����    
    //************************************    
    CString GetPassword();

public:
    afx_msg void OnBnClickedCreate();
public:
    virtual void AssertValid() const;
};
