// BatchPasswordGeneratorDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "BatchPasswordGenerator.h"
#include "BatchPasswordGeneratorDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// CBatchPasswordGeneratorDlg �Ի���




CBatchPasswordGeneratorDlg::CBatchPasswordGeneratorDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CBatchPasswordGeneratorDlg::IDD, pParent)
    , m_nItemData(1)
    , m_bMinLetter(TRUE)
    , m_bMaxLetter(FALSE)
    , m_bDigital(TRUE)
    , m_bSpecialChar(FALSE)
    , m_bBatch(FALSE)
{
	m_hMaxIcon = AfxGetApp()->LoadIcon(IDI_MAX);
    m_hMinIcon = AfxGetApp()->LoadIcon(IDI_MIN);
    

}

void CBatchPasswordGeneratorDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_SLIDER, m_wndSliderItem);
    DDX_Text(pDX, IDC_EDIT1, m_nItemData);
    DDV_MinMaxUInt(pDX, m_nItemData, 1, 256);
    DDX_Control(pDX, IDC_EDIT2, m_wndPassword);
    DDX_Check(pDX, IDC_MINLETTER, m_bMinLetter);
    DDX_Check(pDX, IDC_MAXLETTER, m_bMaxLetter);
    DDX_Check(pDX, IDC_DIGITAL, m_bDigital);
    DDX_Check(pDX, IDC_SPECIALCHAR, m_bSpecialChar);
    DDX_Control(pDX, IDC_EDIT1, m_wndEdit1);
    DDX_Control(pDX, IDC_PROGRESS, m_wndProgress);
    DDX_Control(pDX, IDC_BATCHDATA, m_wndBatchData);
    DDX_Control(pDX, IDC_OPENFILE, m_wndOpenFile);
    DDX_Control(pDX, IDC_CREATE, m_wndCreateData);
    DDX_Check(pDX, IDC_BATCH, m_bBatch);
    DDX_Control(pDX, IDC_NEW, m_wndNew);
    DDX_Control(pDX, IDC_COPY, m_wndCopy);
}

BEGIN_MESSAGE_MAP(CBatchPasswordGeneratorDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
    ON_EN_KILLFOCUS(IDC_EDIT1, &CBatchPasswordGeneratorDlg::OnEnKillfocusEdit1)
    ON_WM_HSCROLL()
    ON_EN_UPDATE(IDC_EDIT1, &CBatchPasswordGeneratorDlg::OnEnUpdateEdit1)
    ON_BN_CLICKED(IDC_NEW, &CBatchPasswordGeneratorDlg::OnBnClickedNew)
    ON_BN_CLICKED(IDC_MINLETTER, &CBatchPasswordGeneratorDlg::OnBnClickedMinletter)
    ON_BN_CLICKED(IDC_MAXLETTER, &CBatchPasswordGeneratorDlg::OnBnClickedMaxletter)
    ON_BN_CLICKED(IDC_DIGITAL, &CBatchPasswordGeneratorDlg::OnBnClickedDigital)
    ON_BN_CLICKED(IDC_SPECIALCHAR, &CBatchPasswordGeneratorDlg::OnBnClickedSpecialchar)
    ON_BN_CLICKED(IDC_BATCH, &CBatchPasswordGeneratorDlg::OnBnClickedBatch)
    ON_BN_CLICKED(IDC_OPENFILE, &CBatchPasswordGeneratorDlg::OnBnClickedOpenfile)
    ON_BN_CLICKED(IDC_COPY, &CBatchPasswordGeneratorDlg::OnBnClickedCopy)
    ON_BN_CLICKED(IDC_CREATE, &CBatchPasswordGeneratorDlg::OnBnClickedCreate)
END_MESSAGE_MAP()


// CBatchPasswordGeneratorDlg ��Ϣ�������

BOOL CBatchPasswordGeneratorDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hMaxIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hMinIcon, FALSE);		// ����Сͼ��

	// ��ʼ������
    //���û������ʼλ������ֹλ��
    m_wndSliderItem.SetRange(1,256);
    EnableToolTips(TRUE);
    m_Tip.Create(this);
    m_Tip.Activate(TRUE);

    
    m_Tip.AddTool(GetDlgItem(IDC_BATCHDATA),TEXT("��д������������ĸ���")); //���


    //��ʼ�� �Ƿ�������������Ϣ
    JudgeBatch();

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CBatchPasswordGeneratorDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CBatchPasswordGeneratorDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ��������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hMaxIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù����ʾ��
//
HCURSOR CBatchPasswordGeneratorDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hMaxIcon);
}


BOOL CBatchPasswordGeneratorDlg::PreTranslateMessage(MSG* pMsg)
{
    if(pMsg->message==WM_MOUSEMOVE)
        m_Tip.RelayEvent(pMsg);
    
    return CDialog::PreTranslateMessage(pMsg);
}
//ʧȥ���뽹��,�����ַ������
void CBatchPasswordGeneratorDlg::OnEnKillfocusEdit1()
{   
    //���ؼ������ݷ��뵽����
    UpdateData();
    //�ƶ�����λ��
    m_wndSliderItem.SetPos(m_nItemData);
}
//************************************    
// �������ƣ�OnHScroll    
// ����˵�������ˮƽ������    
// �������ߣ�Robin    
// �������ڣ�2015/04/12    
// �� �� ֵ��    
// ��    ��:     
//************************************    
void CBatchPasswordGeneratorDlg::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
    //��ȡ�����ϵ�ˮƽ����
    CSliderCtrl* pSlider = (CSliderCtrl*)pScrollBar;
    //��ȡ����λ��
    int nPosData = pSlider->GetPos();
    //�����λ�����õ�Edit����
    CString str;
    str.Format(TEXT("%d"),nPosData);
    //���¿ؼ����� �����������ݷ���ؼ�
    m_wndEdit1.SetWindowText(str);
    CDialog::OnHScroll(nSBCode, nPos, pScrollBar);
}
//************************************    
// �������ƣ�OnEnUpdateEdit1    
// ����˵��������λ��������ʾ    
// �������ߣ�Robin    
// �������ڣ�2015/04/12    
// �� �� ֵ��    
// ��    ��:     
//************************************    
void CBatchPasswordGeneratorDlg::OnEnUpdateEdit1()
{
    //��ȡ�±���
    UpdateData();
    //�ƶ�����λ��
    m_wndSliderItem.SetPos(m_nItemData);
}

//************************************    
// �������ƣ�GetDigitalData    
// ����˵������ȡ�������    
// �������ߣ�Robin    
// �������ڣ�2015/04/12    
// �� �� ֵ�����������    
// ��    ��:     
//************************************    
int CBatchPasswordGeneratorDlg::GetDigitalData(int nBit)
{
    int nData;
    //���и�ʽ�� nBit : 51 ��0~50
    nData = rand()%nBit;
    return nData;
}

//************************************    
// �������ƣ�DataMaxLetter();    
// ����˵�������ɴ�д��ĸ�����ĸ    
// �������ߣ�Robin    
// �������ڣ�2015/04/12    
// �� �� ֵ��    
// ��    ��:     
//************************************ 
UCHAR CBatchPasswordGeneratorDlg::DataMaxLetter()
{
    //A��65��ʼ
    UCHAR cChar = 65;
    //��ȡ����� 0~25
    int nData = GetDigitalData(26);
    //A+��ȡ���������,���������д��ĸ
    cChar += nData;
    //���������д��ĸ 
    return cChar;
}

//************************************    
// �������ƣ�DataMaxLetter();    
// ����˵��������Сд��ĸ�����ĸ    
// �������ߣ�Robin    
// �������ڣ�2015/04/12    
// �� �� ֵ���ַ�    
// ��    ��:     
//************************************    
UCHAR CBatchPasswordGeneratorDlg::DataMinLetter()
{
    //a��97��ʼ
    UCHAR cChar = 97;
    //��ȡ����� 0~25
    int nData = GetDigitalData(26);
    //a+��ȡ���������,�������Сд��ĸ
    cChar += nData;
    //�������Сд��ĸ 
    return cChar;
}

//************************************
// �������ƣ�DataDigitalChar    
// ����˵������ȡ�����ַ�    
// �������ߣ�Robin    
// �������ڣ�2015/04/12    
// �� �� ֵ��    
// ��    ����    
//************************************
UCHAR CBatchPasswordGeneratorDlg::DataDigitalChar()
{
    //A��65��ʼ
    UCHAR cChar = 48;
    //��ȡ�����0~9
    int nData = GetDigitalData(10);
    //A+��ȡ���������,���������д��ĸ
    cChar += nData;
    //���������д��ĸ 
    return cChar;
}

//************************************    
// �������ƣ�DataCharacter();    
// ����˵������������ַ�    
// �������ߣ�Robin    
// �������ڣ�2015/04/12    
// �� �� ֵ���ַ�    
// ��    ��:     
//************************************    
UCHAR CBatchPasswordGeneratorDlg::DataCharacter()
{
    //��ȡ�����
    int nData= GetDigitalData(32);
    switch(nData)
    {
        case 0://!
            return 33;
            break;
        case 1://"
            return 34; 
            break;
        case 2://#
            return 35;
            break;
        case 3://$
            return 36;
            break;
        case 4://%
            return 37;
            break;
        case 5://&
            return 38;
            break;
        case 6://'
            return 39;
            break;
        case 7://(
            return 40;
            break;
        case 8://)
            return 41;
            break;
        case 9://*
            return 42;
            break;
        case 10://+
            return 43;
            break;
        case 11://
            return 44;
            break;
        case 12://-
            return 45;
            break;
        case 13://.
            return 46;
            break;
        case 14:///
            return 47;
            break;
        case 15://:
            return 58;
            break;
        case 16://;
            return 59;
            break;
        case 17://<
            return 60;
            break;
        case 18://=
            return 61;
            break;
        case 19://>
            return 62;
            break;
        case 20://?
            return 63;
            break;
        case 21://@
            return 64;
            break;
        case 22://[
            return 91;
            break;
        case 23:/*/*/
            return 92;
            break;
        case 24://]
            return 93;
            break;
        case 25://^
            return 94;
            break;
        case 26://_
            return 95;
            break;
        case 27://`
            return 96;
            break;
        case 28://{
            return 123;
            break;
        case 29://|
            return 124;
            break;
        case 30://}
            return 125;
            break;
        case 31://~
            return 126;
            break;
    }
    //���������Ƿ���!�ַ�
    return 33;
}

//************************************    
// �������ƣ�OnBnClickedNew    
// ����˵��������°�ť    
// �������ߣ�Robin    
// �������ڣ�2015/04/12    
// �� �� ֵ��    
// ��    ��:     
//************************************    
void CBatchPasswordGeneratorDlg::OnBnClickedNew()
{
    CString strPassword = GetPassword();
    //���ַ������õ�Edit��
    m_wndPassword.SetWindowText(strPassword);
}
//************************************    
// �������ƣ�GetPasswordBit    
// ����˵������ȡ�����λ��    
// �������ߣ�Robin    
// �������ڣ�2015/04/12    
// �� �� ֵ�����������λ��    
// ��    ��:     
//************************************    
int CBatchPasswordGeneratorDlg::GetPasswordBit()
{
    //��������λ��
    return m_nItemData;
}

//���Сд��ĸѡ��
void CBatchPasswordGeneratorDlg::OnBnClickedMinletter()
{
    //��ȡ����������
    UpdateData();
    //�ж����������Ƿ�ѡ
    /*
    if (m_bMaxLetter!=TRUE||m_bDigital!=TRUE||m_bSpecialChar!=TRUE)
    {
        AfxMessageBox(TEXT("������ʲô������ѡ,����������!������ѡ��:Сд��ĸ|��д��ĸ|����|�����ַ�"));
    }
    */

}
//�����д��ĸѡ��
void CBatchPasswordGeneratorDlg::OnBnClickedMaxletter()
{
    // TODO: �ڴ���ӿؼ�֪ͨ����������
}
//�������ѡ��
void CBatchPasswordGeneratorDlg::OnBnClickedDigital()
{
    // TODO: �ڴ���ӿؼ�֪ͨ����������
}
//��������ַ�
void CBatchPasswordGeneratorDlg::OnBnClickedSpecialchar()
{
    // TODO: �ڴ���ӿؼ�֪ͨ����������
}

//************************************ 
// �������ƣ�JudgeBatch    
// ����˵�����ж��Ƿ���������������    
// �������ߣ�Robin    
// �������ڣ�2015/04/12    
// �� �� ֵ��    
// ��    ����    
//************************************ 
void CBatchPasswordGeneratorDlg::JudgeBatch()
{
    //��ȡ�Ի������������
    UpdateData();
    //�ж��Ƿ�ѡ������ť
    if(m_bBatch!=TRUE)
    {//û�й�ѡ��������
        //��ʾ�������������Ϣ 
        //��ʾ����Edit��
        m_wndPassword.ShowWindow(SW_SHOW);
        //��ʾ������ť
        m_wndCopy.ShowWindow(SW_SHOW);
        //��ʾ�������밴ť
        m_wndNew.ShowWindow(SW_SHOW);
   
        //���������������Ϣ
        //���ؽ�����
        m_wndProgress.ShowWindow(SW_HIDE);
        //�������ɰ�ť
        m_wndCreateData.ShowWindow(SW_HIDE);
        //�����������ɶ�������������
        m_wndBatchData.ShowWindow(SW_HIDE);
        //���ش��ļ���ť
        m_wndOpenFile.ShowWindow(SW_HIDE);
    }else
    {//��ѡ��������
        //���ط������������Ϣ 
        //��������Edit��
        m_wndPassword.ShowWindow(SW_HIDE);
        //���ؿ�����ť
        m_wndCopy.ShowWindow(SW_HIDE);
        //���ظ������밴ť
        m_wndNew.ShowWindow(SW_HIDE);

        //��ʾ�����������Ϣ
        //��ʾ������
        m_wndProgress.ShowWindow(SW_SHOW);
        //��ʾ���ɰ�ť
        m_wndCreateData.ShowWindow(SW_SHOW);
        //��ʾ�������ɶ�������������
        m_wndBatchData.ShowWindow(SW_SHOW);
        //��ʾ���ļ���ť
        m_wndOpenFile.ShowWindow(SW_SHOW);
    }
}
//���������ť
void CBatchPasswordGeneratorDlg::OnBnClickedBatch()
{
    JudgeBatch();
}
//���ѡ��Ҫ������ļ�λ��
void CBatchPasswordGeneratorDlg::OnBnClickedOpenfile()
{
    //�����ļ��Ի���
    CFileDialog FileDialog(FALSE,TEXT("*.txt"),TEXT("PasswordData.txt"),OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,TEXT("�ı��ļ�(*.txt)|*.txt||"),GetDlgItem(IDD_BATCHPASSWORDGENERATOR_DIALOG));
    //��ʾ���� ���ж��Ƿ�������
    if (FileDialog.DoModal()!=IDOK)
    {//���ǵ������
        return ;//����
    }
    //���洰������
    CString strWindowsName;
    WCHAR szText[100] = {0};
    //��ȡ��������
    LoadString(AfxGetApp()->m_hInstance,IDS_WINDOWSNAME,szText,100);
    strWindowsName.Format(TEXT("%s"),szText);
    //��ȡ������ļ�������
    CString strFileName = FileDialog.GetFileTitle();
    //�����´�������
    CString strNewWinName;
    //�����´�������
    strNewWinName.Format(TEXT("%s   %s"),strWindowsName,strFileName);
    //���´����������õ�����
    SetWindowText(strNewWinName);
    //��ȡ�ļ���ȫ·��,���Ƶ�������
    m_strFilePath = FileDialog.GetPathName();

}
//************************************    
// �������ƣ�Write    
// ����˵����д�������    
// �������ߣ�Robin    
// �������ڣ�2015/04/12    
// �� �� ֵ��    
// ��    ����    
//************************************    
void CBatchPasswordGeneratorDlg::Write(CString& strText)
{
       /*
    OpenClipboard�򿪼��а壺ָ���������򿪵ļ��а�Ĵ��ھ��������NULL��ʾ��������ǰ����ÿ��ֻ����һ
    �����̴򿪲����ʡ�ÿ��һ�ξ�Ҫ�رգ��������������޷����ʼ��а塣
    EmptyClipboard��ռ��а壺д��ǰ��������գ��õ�ռ��Ȩ
    */
    if (::OpenClipboard(m_hWnd) &&::EmptyClipboard())
    {
        //���ݻ���������ȡ���ݳ���
        size_t cbStr = (strText.GetLength() + 1) * sizeof(TCHAR);

        //�ڶ��϶�̬�������ֽ�Ϊ��λ��ȫ���ڴ����򡣳ɹ���ָ����ڴ棬ʧ��NULL��������1.�����ڴ����ԣ�2.��С
        HGLOBAL hMem = GlobalAlloc(GMEM_MOVEABLE, cbStr); 

        if (hMem == NULL) 
        {
            //�رռ��а�,�ͷż��а�����Ȩ���رպ�Ͳ���д������
            CloseClipboard();
            return; 
        }

        //������GlobalAlloc������ڴ棬�����ڴ���������������+1���ɹ�����ָ���ڴ������ʼ��ַ��ָ�롣ʧ��NULL
        LPTSTR lpDest = (LPTSTR)GlobalLock(hMem);
        /*
        ϵͳΪÿ��ȫ���ڴ����ά��һ����������������ʼΪ0��GlobalLockʹ������+1��
        */

        //�������ݵ��������ڴ档
        memcpy_s(lpDest, cbStr, strText.LockBuffer(), cbStr);
        strText.UnlockBuffer();

        //����ڴ�������������ΪGMEM_MOVEABLE���ڴ���������-1.
        GlobalUnlock(hMem); 
        /*
        GlobalUnLock������-1.һ��������ֵ����0������ڴ����򽫲������ƶ���ɾ����ֻ
        �е�Ϊ0ʱ���Ž��������ڴ���������������ʱGMEM_FIXED���ԣ�������һֱΪ0

        */

        //���ݻ��������������ݸ�ʽ
        UINT uiFormat = (sizeof(TCHAR) == sizeof(WCHAR))?CF_UNICODETEXT:CF_TEXT;

        //�������ݵ������塣ִ�гɹ����������ݾ�������򷵻�NULL
        if(SetClipboardData(uiFormat, hMem) == NULL)
        {
            CloseClipboard();
            return;
        }

        CloseClipboard();
    }
}
//������ư�ť
void CBatchPasswordGeneratorDlg::OnBnClickedCopy()
{
    //��ȡ����
    CString strPassword;
    m_wndPassword.GetWindowText(strPassword);
    //�жϻ�ȡ���������Ƿ�Ϊ��
    if (strPassword==TEXT(""))
    {
        //����Ϊ��,�޷�����
        AfxMessageBox(TEXT("����Ϊ��,���ܽ��и���"));
        return ;
    }
    //�����������
    Write(strPassword);
}
//************************************    
// �������ƣ�ThreadProc    
// ����˵����MFC�����̴߳�����    
// �������ߣ�Robin    
// �������ڣ�2015/04/12    
// �� �� ֵ��    
// ��    ����    
//************************************    
UINT CBatchPasswordGeneratorDlg::ThreadProc(LPVOID pParam)
{
    //��ȡָ��
    CBatchPasswordGeneratorDlg* pDlg =  (CBatchPasswordGeneratorDlg*)pParam;
    //��ȡ��Ҫ���ɶ���
    CString strBatchData;
    //��ȡ����
    pDlg->m_wndBatchData.GetWindowText(strBatchData);
    int nData = _ttoi(strBatchData);
    //���ý�������ʼ����ֹ
    pDlg->m_wndProgress.SetRange32(0,nData);
    //���ļ�
    if (pDlg->m_strFilePath==TEXT(""))//�ж��Ƿ�����Ŀ¼
    {
        AfxMessageBox(TEXT("��û��ѡ���ļ������λ��,������...����ť,ѡ���ļ����λ��"));
        return 0;
    }
    
    CFile File;
    //��д��ķ�ʽ���ļ�
    File.Open(pDlg->m_strFilePath,CFile::modeCreate | CFile::modeWrite);
    //�������ɰ�ť��ɫ
    pDlg->m_wndCreateData.EnableWindow(FALSE);
    //���ڱ�������
    for (int nIndex = 0;nIndex<nData;nIndex++)
    {
        //205
        CString strPassword;
        strPassword = pDlg->GetPassword();
        //��ȡ��Unicode ����ַ���
        char szText[MAX_PATH] = {0};
        strPassword+= TEXT("\r\n");
        //ת����Ascii��
        WideCharToMultiByte(CP_ACP,WC_COMPOSITECHECK,strPassword, -1,szText,sizeof(szText), NULL,NULL);
        //д�뵽�ļ�
        File.Write(szText,strlen(szText));
        //���ӽ�����
        //��ȡ��������ǰλ��
        int nPos = pDlg->m_wndProgress.GetPos();
        //����һ������
        nPos++;
        //���ý�������λ��
        pDlg->m_wndProgress.SetPos(nPos);
    }
    //�����ɰ�ťȡ����ɫ
    pDlg->m_wndCreateData.EnableWindow(TRUE);
    //�ر��ļ�
    File.Close();
    //���������������
    AfxMessageBox(TEXT("���������������"));
    return 0;
    
}

//************************************    
// �������ƣ�GetPassword()    
// ����˵������ȡ�������    
// �������ߣ�Robin    
// �������ڣ�2015/04/12    
// �� �� ֵ�����ɺ������    
// ��    ����    
//************************************    
CString CBatchPasswordGeneratorDlg::GetPassword()
{
    UpdateData(TRUE);//���ؼ����ݷ��õ�����
    //�ж��ĸ�ѡ���Ƿ�ѡ��
    //if (m_bMinLetter==FALSE||m_bMaxLetter==FALSE||m_bDigital==FALSE||m_bSpecialChar==FALSE)
    //{//ȫ����û�й�ѡ
    //    AfxMessageBox(TEXT("������ѡ��һ��,������ѡ��:Сд��ĸ|��д��ĸ|����|�����ַ�"));
    //    return NULL;
    //}
    //��ȡ�����λ��
    int nPasswordBit =  GetPasswordBit();
    CString str1;//��¼�ַ���
    CString str2;//��ʱ�ַ���
    //ѭ����ȡ�ַ�
    for (int nIndex = 0;nIndex<nPasswordBit;nIndex++)
    {

        int nItem = GetDigitalData(4); //��ȡ�����0~3
        switch(nItem)
        {
        case 0:
            {
                //�ж��Ƿ��ܻ�ȡСд��ĸ
                if(m_bMinLetter==TRUE)
                {//ѡ��
                    //��ȡСд��ĸ
                    str2 = (char)DataMinLetter();
                }else
                {//û�й�ѡ��
                    //�������ε��ж�
                    nIndex--;
                    //����ѭ��
                    continue;
                }
            }
            break;
        case 1:
            {
                //�ж��Ƿ��ܻ�ȡ��д��ĸ
                if(m_bMaxLetter==TRUE)
                {
                    //��ȡ��д��ĸ
                    str2 = (char)DataMaxLetter();
                }else
                {//û�й�ѡ��
                    //�������ε��ж�
                    nIndex--;
                    //����ѭ��
                    continue;
                }
            }
            break;
        case 2:
            {
                //�ж��Ƿ��ܻ�ȡ����
                if(m_bDigital==TRUE)
                {   
                    //��ȡ�����ַ�
                    str2 = (char)DataDigitalChar();

                }else
                {//û�й�ѡ��
                    //�������ε��ж�
                    nIndex--;
                    //����ѭ��
                    continue;
                }
            }
            break;
        case 3:
            {
                //�ж��Ƿ��ܻ�ȡ�����ַ�
                if(m_bSpecialChar==TRUE)
                {
                    //��ȡ�����ַ�
                    str2 = (char)DataCharacter();
                }else
                {//û�й�ѡ��
                    //�������ε��ж�
                    nIndex--;
                    //����ѭ��
                    continue;
                }
            }
            break;
        }

        str1 += str2;//����ʱ�����¼���ַ������
    }
    return str1;
}
void CBatchPasswordGeneratorDlg::OnBnClickedCreate()
{
    AfxBeginThread(ThreadProc,this);
}


void CBatchPasswordGeneratorDlg::AssertValid() const
{
//    CDialog::AssertValid();
//        if (m_hWnd == NULL)
//        return;     // null (unattached) windows are valid
//
//// check for special wnd??? values
//    ASSERT(HWND_TOP == NULL);       // same as desktop
//    if (m_hWnd == HWND_BOTTOM)
//        ASSERT(this == &CWnd::wndBottom);
//    else if (m_hWnd == HWND_TOPMOST)
//        ASSERT(this == &CWnd::wndTopMost);
//    else if (m_hWnd == HWND_NOTOPMOST)
//        ASSERT(this == &CWnd::wndNoTopMost);
//    else
//    {
//        // should be a normal window
//        ASSERT(::IsWindow(m_hWnd));

// should also be in the permanent or temporary handle map
/*        CHandleMap* pMap = afxMapHWND();
        ASSERT(pMap != NULL);

CObject* p;
        ASSERT((p = pMap->LookupPermanent(m_hWnd)) != NULL ||
            (p = pMap->LookupTemporary(m_hWnd)) != NULL);
        ASSERT((CWnd*)p == this);   // must be us
*/
    // TODO: �ڴ����ר�ô����/����û���
        // Note: if either of the above asserts fire and you are
        // writing a multithreaded application, it is likely that
        // you have passed a C++ object from one thread to another
        // and have used that object in a way that was not intended.
        // (only simple inline wrapper functions should be used)
        //
        // In general, CWnd objects should be passed by HWND from
        // one thread to another.  The receiving thread can wrap
        // the HWND with a CWnd object by using CWnd::FromHandle.
        //
        // It is dangerous to pass C++ objects from one thread to
        // another, unless the objects are designed to be used in
        // such a manner.
   // }
}
