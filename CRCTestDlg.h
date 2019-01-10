
// CRCTestDlg.h : 头文件
//

#pragma once
#include "afxwin.h"
#include "dji_crc.h"
#include <string>

// CCRCTestDlg 对话框
class CCRCTestDlg : public CDialogEx
{
// 构造
public:
	CCRCTestDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_CRCTEST_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonGenerate();
	CString sInput;
	CString sOutput;
	BOOL bCrc16;
	CEdit edit_Input;
	CEdit edit_Output;
	CButton radio_CRC;

	afx_msg void OnClickedRadioCrc16();
	afx_msg void OnBnClickedRadioCrc32();


	/********************************** CRC **********************************/
private:
	uint16_t crc16Update(uint16_t crc, uint8_t ch);
	uint32_t crc32Update(uint32_t crc, uint8_t ch);
	uint16_t crc16Calc(const uint8_t* pMsg, size_t nLen);
	uint32_t crc32Calc(const uint8_t* pMsg, size_t nLen);


};
