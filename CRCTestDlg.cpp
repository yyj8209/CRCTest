
// CRCTestDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "CRCTest.h"
#include "CRCTestDlg.h"
#include "afxdialogex.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif

using namespace std;

// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
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

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CCRCTestDlg �Ի���



CCRCTestDlg::CCRCTestDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CCRCTestDlg::IDD, pParent)
	, sInput(_T(""))
	, sOutput(_T(""))
	, bCrc16(false)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CCRCTestDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	//  DDX_Text(pDX, IDC_EDIT_IN, sInput);
	//  DDX_Text(pDX, IDC_EDIT_OUT, sOutput);
	DDX_Radio(pDX, IDC_RADIO_CRC16, bCrc16);
	DDX_Control(pDX, IDC_EDIT_IN, edit_Input);
	DDX_Control(pDX, IDC_EDIT_OUT, edit_Output);
	//  DDX_Control(pDX, IDC_RADIO_CRC16, radioCRC);
	DDX_Control(pDX, IDCANCEL, radio_CRC);
}

BEGIN_MESSAGE_MAP(CCRCTestDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_GENERATE, &CCRCTestDlg::OnBnClickedButtonGenerate)

	ON_BN_CLICKED(IDC_RADIO_CRC16, &CCRCTestDlg::OnClickedRadioCrc16)
	ON_BN_CLICKED(IDC_RADIO_CRC32, &CCRCTestDlg::OnBnClickedRadioCrc32)
END_MESSAGE_MAP()


// CCRCTestDlg ��Ϣ�������

BOOL CCRCTestDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO:  �ڴ���Ӷ���ĳ�ʼ������

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CCRCTestDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CCRCTestDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CCRCTestDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CCRCTestDlg::OnBnClickedButtonGenerate()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	uint8_t* pMsg;
	uint16_t crc16;
	uint32_t crc32;
	size_t nLen;
	edit_Input.GetWindowTextW(sInput);
	sInput.Replace(_T(" "), _T(""));
	CT2CA pszName(sInput);
	
	string tmp(pszName);
	pMsg = (uint8_t*)(tmp.data());
	nLen = tmp.size();
//	tmp.Format("%u", sInput);
	if (!bCrc16)
	{
		crc16 = crc16Calc(pMsg, nLen);
		sOutput.Format(_T("%0X"), crc16);
	}
	else
	{
		crc32 = crc32Calc(pMsg, nLen);
		sOutput.Format(_T("%0X"), crc32);
	}
	edit_Output.SetWindowTextW(sOutput);

}



void CCRCTestDlg::OnClickedRadioCrc16()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	bCrc16 = false;
}


void CCRCTestDlg::OnBnClickedRadioCrc32()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	bCrc16 = true;
}

/******************* CRC Calculationns *********************/
/*
int
CCRCTestDlg::crcHeadCheck(uint8_t* pMsg, size_t nLen)
{
	return crc16Calc(pMsg, nLen);
}

int
CCRCTestDlg::crcTailCheck(uint8_t* pMsg, size_t nLen)
{
	return crc32Calc(pMsg, nLen);
}

void
CCRCTestDlg::calculateCRC(void* p_data)
{
	OpenHeader* p_head = (OpenHeader*)p_data;
	uint8_t*    p_byte = (uint8_t*)p_data;
	uint32_t    index_of_crc32;


	p_head->crc = crc16Calc(p_byte, OpenProtocol::CRCHeadLen);

	if (p_head->length >= OpenProtocol::PackageMin)
	{
		index_of_crc32 = p_head->length - OpenProtocol::CRCData;
		_SDK_U32_SET(p_byte + index_of_crc32, crc32Calc(p_byte, index_of_crc32));
	}
}
*/
uint16_t
CCRCTestDlg::crc16Update(uint16_t crc, uint8_t ch)
{
	uint16_t tmp;
	uint16_t msg;

	msg = 0x00ff & static_cast<uint16_t>(ch);
	tmp = crc ^ msg;
	crc = (crc >> 8) ^ crc_tab16[tmp & 0xff];

	return crc;
}

uint32_t
CCRCTestDlg::crc32Update(uint32_t crc, uint8_t ch)
{
	uint32_t tmp;
	uint32_t msg;

	msg = 0x000000ffL & static_cast<uint32_t>(ch);
	tmp = crc ^ msg;
	crc = (crc >> 8) ^ crc_tab32[tmp & 0xff];
	return crc;
}

uint16_t
CCRCTestDlg::crc16Calc(const uint8_t* pMsg, size_t nLen)
{
	size_t   i;
	uint16_t wCRC = CRC_INIT;

	for (i = 0; i < nLen; i++)
	{
		wCRC = crc16Update(wCRC, pMsg[i]);
	}

	return wCRC;
}

uint32_t
CCRCTestDlg::crc32Calc(const uint8_t* pMsg, size_t nLen)
{
	size_t   i;
	uint32_t wCRC = CRC_INIT;

	for (i = 0; i < nLen; i++)
	{
		wCRC = crc32Update(wCRC, pMsg[i]);
	}

	return wCRC;
}


