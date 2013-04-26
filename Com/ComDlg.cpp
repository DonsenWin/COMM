
// ComDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Com.h"
#include "ComDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CComDlg �Ի���




CComDlg::CComDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CComDlg::IDD, pParent)

	, m_rdata(_T(""))

	//, m_send_data(0)
	, m_send(_T(""))
	, m_port(6)
	, m_band(19200)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CComDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_MSCOMM1, m_com);

	DDX_Text(pDX, IDC_EDIT2, m_rdata);

	DDX_Control(pDX, IDC_EDIT2, m_show_data);
	//DDX_Text(pDX, IDC_EDIT4, m_send_data);
	DDX_Text(pDX, IDC_EDIT4, m_send);
	DDX_Text(pDX, IDC_EDIT1, m_port);
	DDV_MinMaxShort(pDX, m_port, 0, 30);
	DDX_Text(pDX, IDC_EDIT3, m_band);
	//DDX_Control(pDX, IDC_BUTTON2, m_button2);
	DDX_Control(pDX, IDC_BUTTON2, m_button2);
	//DDX_Control(pDX, IDC_COMBO2, m_combox);
}

BEGIN_MESSAGE_MAP(CComDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON2, &CComDlg::OnBnClickedButton2)
	//	ON_WM_CREATE()
	//ON_EN_CHANGE(IDC_EDIT1, &CComDlg::OnEnChangeEdit1)
	ON_BN_CLICKED(IDC_BUTTON3, &CComDlg::OnBnClickedButton3)
	//ON_EN_CHANGE(IDC_EDIT1, &CComDlg::OnEnChangeEdit1)
	ON_BN_CLICKED(IDC_BUTTON1, &CComDlg::OnBnClickedButton1)
END_MESSAGE_MAP()


// CComDlg ��Ϣ�������

BOOL CComDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	//CBitmap   m_Nextmap;
	//m_Nextmap.LoadBitmap(IDB_BITMAP3);
	//HBITMAP   hBitmap   =   (HBITMAP)   m_Nextmap.GetSafeHandle(); 
	// m_button2.SetBitmap(hBitmap); 


	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CComDlg::OnPaint()
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
HCURSOR CComDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CComDlg::OnBnClickedButton2()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CString m_band0;
	UpdateData(TRUE);
	m_band0.Format(_T("%d,n,8,1"),m_band);

	if(!m_com.get_PortOpen())
	{

		m_com.put_Settings(m_band0);
		m_com.put_CommPort(m_port);
		m_com.put_PortOpen(TRUE);  //�򿪴���
		m_button2.SetWindowTextW(_T("�رմ���"));
		//m_button2.SetBitmap(::LoadBitmap(NULL, MAKEINTRESOURCE(IDB_BITMAP1)));
		//UpdateData(FALSE);
	}
	else
	{
		m_com.put_PortOpen(FALSE);//�򿪴���
		m_button2.SetWindowTextW(_T("�򿪴���"));
		//m_button2.SetBitmap(::LoadBitmap(NULL, MAKEINTRESOURCE(IDB_BITMAP2)));

	}
}


//int CComDlg::OnCreate(LPCREATESTRUCT lpCreateStruct)
//{
//	if (CDialogEx::OnCreate(lpCreateStruct) == -1)
//		return -1;
//
//	// TODO:  �ڴ������ר�õĴ�������
//
//	return 0;
//}
BEGIN_EVENTSINK_MAP(CComDlg, CDialogEx)
	ON_EVENT(CComDlg, IDC_MSCOMM1, 1, CComDlg::OnCommMscomm1, VTS_NONE)
END_EVENTSINK_MAP()


void CComDlg::OnCommMscomm1()
{
	// TODO: �ڴ˴������Ϣ����������
	VARIANT variant_inp;
	COleSafeArray safearray_inp;
	LONG len,k;
	BYTE rxdata[2048]; //����BYTE���� An 8-bit integerthat is not signed.
	CString strtemp;//
	//if(m_com.get_CommEvent()==2) //�¼�ֵΪ2��ʾ���ջ����������ַ�
	//{
	variant_inp=m_com.get_Input(); //��������
	safearray_inp=variant_inp; //VARIANT�ͱ���ת��ΪColeSafeArray�ͱ���
	len=safearray_inp.GetOneDimSize(); //�õ���Ч���ݳ���
	for(k=0;k <len;k++)
		safearray_inp.GetElement(&k,rxdata+k);//ת��ΪBYTE������
	for(k=0;k <len;k++) //������ת��ΪCstring�ͱ���
	{
		BYTE bt=*(char*)(rxdata+k); //�ַ���
		strtemp.Format(_T("%02x"),bt);//���ַ�������ʱ����strtemp���

		//m_strRXData+=strtemp; //������ձ༭���Ӧ�ַ���

		//	}
	}

	UpdateData(TRUE); //���±༭������ 
	m_rdata+=" ";
	m_rdata+=strtemp;
	UpdateData(FALSE);
	m_show_data.LineScroll(m_show_data.GetLineCount());

}


//void CComDlg::OnEnChangeEdit1()
//{
//	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
//	// ���ʹ�֪ͨ��������д CDialogEx::OnInitDialog()
//	// ���������� CRichEditCtrl().SetEventMask()��
//	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�
//
//	// TODO:  �ڴ���ӿؼ�֪ͨ����������
//}


void CComDlg::OnBnClickedButton3()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE); //��ȡ�༭������

	CByteArray hexdata;
	String2Hex(m_send,hexdata); //�˴����ص�len�������ڼ��㷢���˶��ٸ�ʮ��������
	m_com.put_Output(COleVariant(hexdata)); //����ʮ����������



}



/*   UpdateData(TRUE);

CByteArray sendArr; 
WORD Length;

Length=m_send.GetLength();
sendArr.SetSize(Length);
for(int i =0; i<Length; i++)
{
sendArr.SetAt(i, m_send.GetAt(i));
}
m_com.put_Output(COleVariant(sendArr));
*/



//void CComDlg::OnEnChangeEdit1()
//{
//	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
//	// ���ʹ�֪ͨ��������д CDialogEx::OnInitDialog()
//	// ���������� CRichEditCtrl().SetEventMask()��
//	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�
//
//	// TODO:  �ڴ���ӿؼ�֪ͨ����������
//}


void CComDlg::OnBnClickedButton1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CString xx("221");
	m_rdata.Empty();
	UpdateData(FALSE);
	//m_combox.ShowDropDown( TRUE);
}


// �������ת�������ĸ�ʽ���ƣ��ڷ��Ϳ��е�ʮ�����ַ�Ӧ��ÿ�����ַ�֮�����һ���ո�
int CComDlg::String2Hex(CString str, CByteArray & senddata)
{
	int hexdata,lowhexdata;
	int hexdatalen=0;
	int len=str.GetLength();
	senddata.SetSize(len/2);
	for(int i=0;i<len;)
	{
		char lstr,hstr=str[i];
		if(hstr==' ')
		{
			i++;
			continue;
		}
		i++;
		if(i>=len)
			break;
		lstr=str[i];
		hexdata=ConvertHexChar(hstr);
		lowhexdata=ConvertHexChar(lstr);
		if((hexdata==16)||(lowhexdata==16))
			break;
		else 
			hexdata=hexdata*16+lowhexdata;
		i++;
		senddata[hexdatalen]=(char)hexdata;
		hexdatalen++;
	}
	senddata.SetSize(hexdatalen);
	return hexdatalen;
}


// ���ܣ�������0-F֮����ַ�����ת��Ϊ��Ӧ��ʮ�������ַ������򷵻�-1
char CComDlg::ConvertHexChar(char ch)
{
	if((ch>='0')&&(ch<='9'))
		return ch-0x30;
	else if((ch>='A')&&(ch<='F'))
		return ch-'A'+10;
	else if((ch>='a')&&(ch<='f'))
		return ch-'a'+10;
	else return (-1);
}
