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
	ON_BN_CLICKED(IDC_BUTTON3, &Plants::GetProps)
	ON_BN_CLICKED(IDC_PLANTSPEED, &Plants::PlantSpeed)
	ON_BN_CLICKED(IDC_BUTTON4, &Plants::SetPlant)
	ON_BN_CLICKED(IDC_FLOWEREAT, &Plants::FlowerEat)
	ON_BN_CLICKED(IDC_BUTTON5, &Plants::ChangePlantColor)
	ON_BN_CLICKED(IDC_BUTTON6, &Plants::RestorePlantColor)
	ON_BN_CLICKED(IDC_CHANGEZOMBIE, &Plants::ChangeZombie)
	ON_BN_CLICKED(IDC_CHANGEPEA, &Plants::ChangePea)

	ON_BN_CLICKED(IDC_CHANGENUT, &Plants::ChangeNut)
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

	::SendMessage(GetDlgItem(IDC_EDIT1)->GetSafeHwnd(), EM_SETCUEBANNER, TRUE, (LPARAM)L"红 (0-255)");

	::SendMessage(GetDlgItem(IDC_EDIT2)->GetSafeHwnd(), EM_SETCUEBANNER, TRUE, (LPARAM)L"绿 (0-255)");

	::SendMessage(GetDlgItem(IDC_EDIT3)->GetSafeHwnd(), EM_SETCUEBANNER, TRUE, (LPARAM)L"蓝 (0-255)");

	::SendMessage(GetDlgItem(IDC_EDIT4)->GetSafeHwnd(), EM_SETCUEBANNER, TRUE, (LPARAM)L"植物列");

	::SendMessage(GetDlgItem(IDC_EDIT5)->GetSafeHwnd(), EM_SETCUEBANNER, TRUE, (LPARAM)L"植物行");

	::SendMessage(GetDlgItem(IDC_EDIT6)->GetSafeHwnd(), EM_SETCUEBANNER, TRUE, (LPARAM)L"植物ID");

	::SendMessage(GetDlgItem(IDC_EDIT7)->GetSafeHwnd(), EM_SETCUEBANNER, TRUE, (LPARAM)L"僵尸行数");

	::SendMessage(GetDlgItem(IDC_EDIT8)->GetSafeHwnd(), EM_SETCUEBANNER, TRUE, (LPARAM)L"僵尸ID");

	::SendMessage(GetDlgItem(IDC_EDIT9)->GetSafeHwnd(), EM_SETCUEBANNER, TRUE, (LPARAM)L"道具ID");
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
	int Row = GetDlgItemInt(IDC_EDIT7, NULL, FALSE);
	int zType = GetDlgItemInt(IDC_EDIT8, NULL, FALSE);
	pvzManager pvzManager;
	pvzManager.AddZombies(Row, zType);
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

void Plants::GetProps()
{
	// TODO: 在此添加控件通知处理程序代码
	int zType = GetDlgItemInt(IDC_EDIT9, NULL, FALSE);
	pvzManager pvzManager;
	pvzManager.GetProps(zType);
}

void Plants::PlantSpeed()
{
	// TODO: 在此添加控件通知处理程序代码
	int state = ((CButton*)GetDlgItem(IDC_PLANTSPEED))->GetCheck();

	if (state == 1) {
		// 勾选：调用开启函数
		pvzManager pvzManager;
		pvzManager.EnablePlantSpeed();
	}
	else {
		// 取消勾选：调用还原函数
		pvzManager pvzManager;
		pvzManager.DisablePlantSpeed();
	}
}

void Plants::SetPlant()
{
	// TODO: 在此添加控件通知处理程序代码
	int Column = GetDlgItemInt(IDC_EDIT4, NULL, FALSE);
	int Row = GetDlgItemInt(IDC_EDIT5, NULL, FALSE);
	int pType = GetDlgItemInt(IDC_EDIT6, NULL, FALSE);
	pvzManager pvzManager;
	pvzManager.SetPlant(Column, Row, pType);
}

void Plants::FlowerEat()
{
	// TODO: 在此添加控件通知处理程序代码

	int state = ((CButton*)GetDlgItem(IDC_FLOWEREAT))->GetCheck();

	if (state == 1) {
		// 勾选：调用开启函数
		pvzManager pvzManager;
		pvzManager.EnableFlowerEat();
	}
	else {
		// 取消勾选：调用还原函数
		pvzManager pvzManager;
		pvzManager.DisableFlowerEat();
	}
}

void Plants::ChangePlantColor()
{
	// TODO: 在此添加控件通知处理程序代码
	int Red = GetDlgItemInt(IDC_EDIT1, NULL, FALSE);
	int Green = GetDlgItemInt(IDC_EDIT2, NULL, FALSE);
	int Blue = GetDlgItemInt(IDC_EDIT3, NULL, FALSE);
	pvzManager pvzManager;
	pvzManager.ChangePlantColor(Red, Green, Blue);
}

void Plants::RestorePlantColor()
{
	// TODO: 在此添加控件通知处理程序代码
	pvzManager pvzManager;
	pvzManager.restorePlantColor();
}


void Plants::ChangeZombie()
{
	// TODO: 在此添加控件通知处理程序代码
	int state = ((CButton*)GetDlgItem(IDC_CHANGEZOMBIE))->GetCheck();
	if (state == 1) {
		pvzManager pvzManager;
		pvzManager.EnableChangeZombie(0,0);
	}
	else {
		pvzManager pvzManager;
		pvzManager.DisableChangeZombie();
	}
}

void Plants::ChangePea()
{
	// TODO: 在此添加控件通知处理程序代码
	int state = ((CButton*)GetDlgItem(IDC_CHANGEPEA))->GetCheck();
	if (state == 1) {
		pvzManager pvzManager;
		pvzManager.EnableChangePea(1);
	}
	else {
		pvzManager pvzManager;
		pvzManager.DisableChangePea();
	}
}

void Plants::ChangeNut()
{
	// TODO: 在此添加控件通知处理程序代码
	int state = ((CButton*)GetDlgItem(IDC_CHANGENUT))->GetCheck();
	if (state == 1) {
		pvzManager pvzManager;
		pvzManager.EnableChangeNut();
	}
	else {
		pvzManager pvzManager;
		pvzManager.DisableChangeNut();
	}
}
