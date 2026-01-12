// Plants.cpp: 实现文件
//

#include "pch.h"
#include "MFC_PVZ_Version.h"
#include "afxdialogex.h"
#include "Plants.h"
#include "Global.h"
#include "./module/manage/pvzManager.h"


// Plants 对话框

IMPLEMENT_DYNAMIC(Plants, CDialogEx)

Plants::Plants(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG1, pParent)
{

}

Plants::~Plants()
{
}

void Plants::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(Plants, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &Plants::SetSun)
	ON_BN_CLICKED(IDC_BUTTON2, &Plants::AddZombies)
	ON_BN_CLICKED(IDC_COOLDOWN, &Plants::Cooldown)
	ON_BN_CLICKED(IDC_AUTOCOLLECT, &Plants::AutoCollect)
	ON_BN_CLICKED(IDC_PEADAMAGE, &Plants::PeaDamage)
	ON_BN_CLICKED(IDC_NOPAUSE, &Plants::NoPause)
END_MESSAGE_MAP()


// Plants 消息处理程序

BOOL Plants::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	if (VersionResult == 0) {
		SetWindowText(L"植物大战僵尸辅助 - 中文版/原版");
	}
	else if(VersionResult == 1) {
		SetWindowText(L"植物大战僵尸辅助 - Steam年度版");
	}
	else if(VersionResult == 2) {
		SetWindowText(L"植物大战僵尸辅助 - 年度版");
	}
	else {
		SetWindowText(L"植物大战僵尸辅助 - 未知版本");
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void Plants::SetSun()
{
	// TODO: 在此添加控件通知处理程序代码
	pvzManager pvzManager;
	pvzManager.SetSunlight(9999);
}

void Plants::AddZombies()
{
	// TODO: 在此添加控件通知处理程序代码
	pvzManager pvzManager;
	pvzManager.AddZombies(0, 0);
}

void Plants::Cooldown()
{
	// TODO: 在此添加控件通知处理程序代码
	int state = ((CButton*)GetDlgItem(IDC_COOLDOWN))->GetCheck();

	if (state == 1) {
		// 勾选：调用开启函数
		pvzManager pvzManager;
		pvzManager.EnableNoCooldown();
	}
	else {
		// 取消勾选：调用还原函数
		pvzManager pvzManager;
		pvzManager.DisableNoCooldown();
	}
}

void Plants::AutoCollect()
{
	// TODO: 在此添加控件通知处理程序代码
	int state = ((CButton*)GetDlgItem(IDC_AUTOCOLLECT))->GetCheck();

	if (state == 1) {
		// 勾选：调用开启函数
		pvzManager pvzManager;
		pvzManager.EnableAutoCollect();
	}
	else { 
		// 取消勾选：调用还原函数
		pvzManager pvzManager;
		pvzManager.DisableAutoCollect();
	}
}

void Plants::PeaDamage()
{
	// TODO: 在此添加控件通知处理程序代码
	int state = ((CButton*)GetDlgItem(IDC_PEADAMAGE))->GetCheck();

	if (state == 1) {
		// 勾选：调用开启函数
		pvzManager pvzManager;
		pvzManager.EnablePeaDamage();
	}
	else {
		// 取消勾选：调用还原函数
		pvzManager pvzManager;
		pvzManager.DisablePeaDamage();
	}
}

void Plants::NoPause()
{
	// TODO: 在此添加控件通知处理程序代码
	int state = ((CButton*)GetDlgItem(IDC_NOPAUSE))->GetCheck();

	if (state == 1) {
		// 勾选：调用开启函数
		pvzManager pvzManager;
		pvzManager.EnableNoPause();
	}
	else {
		// 取消勾选：调用还原函数
		pvzManager pvzManager;
		pvzManager.DisableNoPause();
	}
}
